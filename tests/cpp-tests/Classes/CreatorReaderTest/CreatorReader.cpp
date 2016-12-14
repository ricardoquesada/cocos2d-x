#include "CreatorReader.h"

#include "CreatorReader_generated.h"

using namespace cocos2d;
using namespace creator;
using namespace creator::buffers;

USING_NS_CCR;

CreatorReader::CreatorReader()
: _scene(nullptr)
, _version("")
{
}

CreatorReader* CreatorReader::createWithFilename(const std::string& filename)
{
    CreatorReader* reader = new(std::nothrow) CreatorReader;
    if (reader && reader->initWithFilename(filename)) {
        reader->autorelease();
        return reader;
    }
    return nullptr;
}

bool CreatorReader::initWithFilename(const std::string& filename)
{
    FileUtils* fileUtils = FileUtils::getInstance();

    const std::string& fullpath = fileUtils->fullPathForFilename(filename);
    if (fullpath.size() == 0)
    {
        CCLOG("CreatorReader: file not found: %s", filename.c_str());
        return false;
    }

    _data = fileUtils->getDataFromFile(fullpath);

    const void* buffer = _data.getBytes();
    auto sceneGraph = GetSceneGraph(buffer);
    _version = sceneGraph->version()->str();
    return true;
}

void CreatorReader::setup()
{
    // XXX TODO
}

cocos2d::Scene* CreatorReader::getSceneGraph() const
{
    const void* buffer = _data.getBytes();

    auto sceneGraph = GetSceneGraph(buffer);
    auto nodeTree = sceneGraph->root();
    CCLOG("NodeTree: %p", nodeTree);

    auto object = nodeTree->object();
    auto object_type = nodeTree->object_type();
    cocos2d::Node* node = getNode(object, object_type);

    return static_cast<cocos2d::Scene*>(node);
}

std::string CreatorReader::getVersion() const
{
    return _version;
}

cocos2d::Node* CreatorReader::getNode(const void* buffer, buffers::AnyNode bufferType) const
{
    switch (bufferType) {
        case buffers::AnyNode_NONE:
            break;
        case buffers::AnyNode_Label:
            return createLabel(static_cast<const buffers::Label*>(buffer));
        case buffers::AnyNode_Sprite:
            return createSprite(static_cast<const buffers::Sprite*>(buffer));
        case buffers::AnyNode_TileMap:
            return createTileMap(static_cast<const buffers::TileMap*>(buffer));
        case buffers::AnyNode_Particle:
            return createParticle(static_cast<const buffers::Particle*>(buffer));
        case buffers::AnyNode_Scene:
            return createScene(static_cast<const buffers::Scene*>(buffer));
        case buffers::AnyNode_Node:
            return createNode(static_cast<const buffers::Node*>(buffer));
    }
    return nullptr;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 *
 * creators
 *
 *=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

cocos2d::Node* CreatorReader::createNode(const buffers::Node* nodeBuffer) const
{
    cocos2d::Node* node = cocos2d::Node::create();
    return node;
}
cocos2d::Sprite* CreatorReader::createSprite(const buffers::Sprite* spriteBuffer) const
{
    cocos2d::Sprite* sprite = cocos2d::Sprite::create();
    return sprite;
}
cocos2d::TMXTiledMap* CreatorReader::createTileMap(const buffers::TileMap* tilemapBuffer) const
{
    cocos2d::TMXTiledMap* tilemap = TMXTiledMap::create("");
    return tilemap;
}
cocos2d::Label* CreatorReader::createLabel(const buffers::Label* labelBuffer) const
{
    cocos2d::Label* label = cocos2d::Label::create();
    return label;
}

cocos2d::ParticleSystemQuad* CreatorReader::createParticle(const buffers::Particle* particleBuffer) const
{
    cocos2d::ParticleSystemQuad* particle = cocos2d::ParticleSystemQuad::create("");
    return particle;
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 *
 * parsers
 *
 *=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
void CreatorReader::parseScene(cocos2d::Scene* scene, const buffers::Scene* sceneBuffer) const
{

}

void CreatorReader::parseNode(cocos2d::Node* node, const buffers::Node* nodeBuffer) const
{

}

void CreatorReader::parseSprite(cocos2d::Sprite* sprite, const buffers::Sprite* spriteBuffer) const
{

}

void CreatorReader::parseTilemap(cocos2d::TMXTiledMap* tilemap, const buffers::TileMap* tilemapBuffer) const
{

}

void CreatorReader::parseLabel(cocos2d::Label* label, const buffers::Label* labelBuffer) const
{

}

void CreatorReader::parseScene(cocos2d::ParticleSystemQuad* partile, const buffers::Particle* particleBuffer) const
{

}
