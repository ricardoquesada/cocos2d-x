/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

Copyright (c) 2011 HKASoftware

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

/*
 Original rewrite of TMXLayer was based on HKTMXTiledMap by HKASoftware http://hkasoftware.com
 Further info: http://www.cocos2d-iphone.org/forums/topic/hktmxtiledmap/

 It was rewritten again, and only a small part of the original HK ideas/code remains in this implementation

 */
#include "2d/CCTMXLayer2.h"
#include "2d/CCTMXXMLParser.h"
#include "2d/CCTMXTiledMap.h"
#include "2d/CCSprite.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCRenderer.h"
#include "ccCArray.h"
#include "base/CCDirector.h"
#include "deprecated/CCString.h"

NS_CC_BEGIN

// TMXLayer2 - init & alloc & dealloc

TMXLayer2 * TMXLayer2::create(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
{
    TMXLayer2 *ret = new TMXLayer2();
    if (ret->initWithTilesetInfo(tilesetInfo, layerInfo, mapInfo))
    {
        ret->autorelease();
        return ret;
    }
    return nullptr;
}
bool TMXLayer2::initWithTilesetInfo(TMXTilesetInfo *tilesetInfo, TMXLayerInfo *layerInfo, TMXMapInfo *mapInfo)
{    

    if( tilesetInfo )
    {
        _texture = Director::getInstance()->getTextureCache()->addImage(tilesetInfo->_sourceImage);
        _texture->retain();
    }

    // layerInfo
    _layerName = layerInfo->_name;
    _layerSize = layerInfo->_layerSize;
    _tiles = layerInfo->_tiles;
    setOpacity( layerInfo->_opacity );
    setProperties(layerInfo->getProperties());

    // tilesetInfo
    _tileSet = tilesetInfo;
    CC_SAFE_RETAIN(_tileSet);

    // mapInfo
    _mapTileSize = mapInfo->getTileSize();
    _layerOrientation = mapInfo->getOrientation();

    // offset (after layer orientation is set);
    Point offset = this->calculateLayerOffset(layerInfo->_offset);
    this->setPosition(CC_POINT_PIXELS_TO_POINTS(offset));

    this->setContentSize(CC_SIZE_PIXELS_TO_POINTS(Size(_layerSize.width * _mapTileSize.width, _layerSize.height * _mapTileSize.height)));

    // shader, and other stuff
    setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

    return true;
}

TMXLayer2::TMXLayer2()
:_layerName("")
,_layerSize(Size::ZERO)
,_mapTileSize(Size::ZERO)
,_tiles(nullptr)
,_tileSet(nullptr)
,_layerOrientation(TMXOrientationOrtho)
,_previousRect(0,0,0,0)
,_verticesToDraw(0)
{}

TMXLayer2::~TMXLayer2()
{
    CC_SAFE_RELEASE(_tileSet);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_DELETE_ARRAY(_tiles);
}

void TMXLayer2::draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(TMXLayer2::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void TMXLayer2::onDraw(const Mat4 &transform, bool transformUpdated)
{
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
    GL::bindTexture2D( _texture->getName() );


    // tex coords + indices
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);


    if( transformUpdated ) {
    
        Size s = Director::getInstance()->getWinSize();
		auto rect = Rect(0, 0, s.width, s.height);

        Mat4 inv = transform.getInversed();
        rect = RectApplyTransform(rect, inv);

        if( !rect.equals(_previousRect) ) {

            V2F_T2F_Quad *quads = (V2F_T2F_Quad*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
            GLushort *indices = (GLushort *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

            _verticesToDraw = updateTiles(rect, quads, indices);

            glUnmapBuffer(GL_ARRAY_BUFFER);
            glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

            _previousRect = rect;
        }

        // don't draw more than 65535 vertices since we are using GL_UNSIGNED_SHORT for indices
        _verticesToDraw = std::min(_verticesToDraw, 65535);
    }

    if(_verticesToDraw > 0) {

        getGLProgram()->use();
        getGLProgram()->setUniformsForBuiltins(_modelViewTransform);

        // vertices
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_T2F), (GLvoid*) offsetof(V2F_T2F, vertices));

        // tex coords
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_T2F), (GLvoid*) offsetof(V2F_T2F, texCoords));

        // color
        glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, _displayedColor.r/255.0f, _displayedColor.g/255.0f, _displayedColor.b/255.0f, _displayedOpacity/255.0f);

        glDrawElements(GL_TRIANGLES, _verticesToDraw, GL_UNSIGNED_SHORT, NULL);
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_verticesToDraw);
    }

    // cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int TMXLayer2::updateTiles(const Rect& culledRect, V2F_T2F_Quad *quads, GLushort *indices)
{
    int tilesUsed = 0;

    Rect visibleTiles;

    Size tileSize = _mapTileSize; //CC_SIZE_PIXELS_TO_POINTS(_mapTileSize);

    // Only valid for ortho
    visibleTiles.origin.x = +culledRect.origin.x;
    visibleTiles.origin.x = floor(visibleTiles.origin.x / tileSize.width);

    visibleTiles.origin.y = +culledRect.origin.y;
    visibleTiles.origin.y = floor(visibleTiles.origin.y / tileSize.height); // -ceil(_tileSet->_tileSize.height/_mapTileSize.height;

    visibleTiles.size.width = culledRect.size.width;
    visibleTiles.size.width = ceil(visibleTiles.size.width / tileSize.width) + 1;

    visibleTiles.size.height = culledRect.size.height;
    visibleTiles.size.height = ceil(visibleTiles.size.height / tileSize.height) + 1;

    int max_rows = _layerSize.height-1;
    int rows_per_tile = ceil(_tileSet->_tileSize.height / _mapTileSize.height) - 1;

    Size texSize = _tileSet->_imageSize;
    for (int y = visibleTiles.origin.y + visibleTiles.size.height - 1; y >= visibleTiles.origin.y - rows_per_tile; y--)
    {
        if(y<0 || y >= _layerSize.height)
            continue;
        for (int x = visibleTiles.origin.x; x < visibleTiles.origin.x + visibleTiles.size.width; x++)
        {
            if(x<0 || x >= _layerSize.width)
                continue;

            uint32_t tileGID = _tiles[x + (max_rows-y) * (int)_layerSize.width];

            // GID==0 empty tile
            if(tileGID!=0) {

                V2F_T2F_Quad *quad = &quads[tilesUsed];

                float left, right, top, bottom;

                // vertices
                left = x * _mapTileSize.width;
                right = left + _tileSet->_tileSize.width;
                bottom = y * _mapTileSize.height;
                top = bottom + _tileSet->_tileSize.height;

                // 1-t
                std::swap(top, bottom);

                if(tileGID & kTMXTileVerticalFlag)
                    std::swap(top, bottom);
                if(tileGID & kTMXTileHorizontalFlag)
                    std::swap(left, right);

                if(tileGID & kTMXTileDiagonalFlag)
                {
                    // XXX: not working correcly
                    quad->bl.vertices.x = left;
                    quad->bl.vertices.y = bottom;
                    quad->br.vertices.x = left;
                    quad->br.vertices.y = top;
                    quad->tl.vertices.x = right;
                    quad->tl.vertices.y = bottom;
                    quad->tr.vertices.x = right;
                    quad->tr.vertices.y = top;
                }
                else
                {
                    quad->bl.vertices.x = left;
                    quad->bl.vertices.y = bottom;
                    quad->br.vertices.x = right;
                    quad->br.vertices.y = bottom;
                    quad->tl.vertices.x = left;
                    quad->tl.vertices.y = top;
                    quad->tr.vertices.x = right;
                    quad->tr.vertices.y = top;
                }

                // texcoords
                Rect tileTexture = _tileSet->getRectForGID(tileGID);
                left   = (tileTexture.origin.x / texSize.width);
                right  = left + (tileTexture.size.width / texSize.width);
                bottom = (tileTexture.origin.y / texSize.height);
                top    = bottom + (tileTexture.size.height / texSize.height);

                quad->bl.texCoords.u = left;
                quad->bl.texCoords.v = bottom;
                quad->br.texCoords.u = right;
                quad->br.texCoords.v = bottom;
                quad->tl.texCoords.u = left;
                quad->tl.texCoords.v = top;
                quad->tr.texCoords.u = right;
                quad->tr.texCoords.v = top;


                GLushort *idxbase = indices + tilesUsed * 6;
                int vertexbase = tilesUsed * 4;

                idxbase[0] = vertexbase;
                idxbase[1] = vertexbase + 1;
                idxbase[2] = vertexbase + 2;
                idxbase[3] = vertexbase + 3;
                idxbase[4] = vertexbase + 2;
                idxbase[5] = vertexbase + 1;

                tilesUsed++;
            }
        } // for x
    } // for y

    return tilesUsed * 6;
}

void TMXLayer2::setupVBO()
{
    glGenBuffers(2, &_buffersVBO[0]);

    // 10922 = 65536/6
    int total = std::min(_layerSize.width * _layerSize.height, 10922.f);

    // Vertex + Tex Coords
    glBindBuffer(GL_ARRAY_BUFFER, _buffersVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, total * sizeof(V2F_T2F_Quad), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, total * 6 * sizeof(GLushort), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    CHECK_GL_ERROR_DEBUG();
}

// TMXLayer2 - setup Tiles
void TMXLayer2::setupTiles()
{    
    // Optimization: quick hack that sets the image size on the tileset
    _tileSet->_imageSize = _texture->getContentSizeInPixels();

    // By default all the tiles are aliased
    // pros: easier to render
    // cons: difficult to scale / rotate / etc.
    _texture->setAliasTexParameters();

    //CFByteOrder o = CFByteOrderGetCurrent();

    // Parse cocos2d properties
//    this->parseInternalProperties();

    Size screenSize = Director::getInstance()->getWinSize();

    switch (_layerOrientation)
    {
        case TMXOrientationOrtho:
            _screenGridSize.width = ceil(screenSize.width / _mapTileSize.width) + 1;
            _screenGridSize.height = ceil(screenSize.height / _mapTileSize.height) + 1;

            // tiles could be bigger than the grid, add additional rows if needed
            _screenGridSize.height += _tileSet->_tileSize.height / _mapTileSize.height;
            break;
        case TMXOrientationIso:
            _screenGridSize.width = ceil(screenSize.width / _mapTileSize.width) + 2;
            _screenGridSize.height = ceil(screenSize.height / (_mapTileSize.height/2)) + 4;
            break;
        case TMXOrientationHex:
            break;
    }

    _screenTileCount = _screenGridSize.width * _screenGridSize.height;

    setupVBO();
}

// removing / getting tiles
Sprite* TMXLayer2::getTileAt(const Point& tileCoordinate)
{
    return nullptr;
}

void TMXLayer2::removeTileAt(const Point& tileCoordinate)
{

}

// TMXLayer2 - Properties
Value TMXLayer2::getProperty(const std::string& propertyName) const
{
    if (_properties.find(propertyName) != _properties.end())
        return _properties.at(propertyName);
    
    return Value();
}

void TMXLayer2::parseInternalProperties()
{
    auto vertexz = getProperty("cc_vertexz");
    if (!vertexz.isNull())
    {
        log("cc_vertexz is not supported in TMXLayer2. Use TMXLayer instead");
    }
}


//CCTMXLayer2 - obtaining positions, offset
Point TMXLayer2::calculateLayerOffset(const Point& pos)
{
    Point ret = Point::ZERO;
    switch (_layerOrientation) 
    {
    case TMXOrientationOrtho:
        ret = Point( pos.x * _mapTileSize.width, -pos.y *_mapTileSize.height);
        break;
    case TMXOrientationIso:
        ret = Point((_mapTileSize.width /2) * (pos.x - pos.y),
                  (_mapTileSize.height /2 ) * (-pos.x - pos.y));
        break;
    case TMXOrientationHex:
        CCASSERT(pos.equals(Point::ZERO), "offset for hexagonal map not implemented yet");
        break;
    }
    return ret;    
}


std::string TMXLayer2::getDescription() const
{
    return StringUtils::format("<TMXLayer2 | tag = %d, size = %d,%d>", _tag, (int)_mapTileSize.width, (int)_mapTileSize.height);
}

NS_CC_END

