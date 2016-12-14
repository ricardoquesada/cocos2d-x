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

CreatorReader::~CreatorReader()
{
    CC_SAFE_RELEASE(_scene);
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
cocos2d::Scene* CreatorReader::createScene(const buffers::Scene* sceneBuffer) const
{
    cocos2d::Scene* scene = cocos2d::Scene::create();
    return scene;
}

cocos2d::Node* CreatorReader::createNode(const buffers::Node* nodeBuffer) const
{
    cocos2d::Node* node = cocos2d::Node::create();
    parseNode(node, nodeBuffer);
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
    //contentSize:Size;
    //enabled:bool = true;
    //name:string;
    //anchorPoint:Vec2;
    //cascadeOpacityEnabled:bool = true;
    //color:RGB;
    //globalZorder:int = 0;
    //localZorder:int = 0;
    //opacity:ubyte = 255;
    //opacityModifyRGB:bool = true;
    //position:Vec2;
    //rotationSkew:Vec2;
    //scale:Vec2;
    //tag:int = 0;

    const auto& contentSize = nodeBuffer->contentSize();
    node->setContentSize(cocos2d::Size(contentSize->w(), contentSize->h()));
//    auto enabled = nodeBuffer->enabled();
    const auto& name = nodeBuffer->name();
    node->setName(name->str());
    const auto& anchorPoint = nodeBuffer->anchorPoint();
    node->setAnchorPoint(cocos2d::Vec2(anchorPoint->x(), anchorPoint->y()));
    const auto& cascadeOpacityEnabled = nodeBuffer->cascadeOpacityEnabled();
    node->setCascadeOpacityEnabled(cascadeOpacityEnabled);
    const auto& color = nodeBuffer->color();
    node->setColor(cocos2d::Color3B(color->r(), color->g(), color->b()));
    const auto& globalZOrder = nodeBuffer->globalZorder();
    node->setGlobalZOrder(globalZOrder);
    const auto& localZOrder = nodeBuffer->localZorder();
    node->setLocalZOrder(localZOrder);
    const auto& opacity = nodeBuffer->opacity();
    node->setOpacity(opacity);
    const auto& opacityModifyRGB = nodeBuffer->opacityModifyRGB();
    node->setOpacityModifyRGB(opacityModifyRGB);
    const auto& position = nodeBuffer->position();
    node->setPosition(position->x(), position->y());
    const auto& rotationSkew = nodeBuffer->rotationSkew();
    node->setRotationSkewX(rotationSkew->x());
    node->setRotationSkewY(rotationSkew->y());
    const auto& scale = nodeBuffer->scale();
    node->setScale(scale->x(), scale->y());
    const auto& tag = nodeBuffer->tag();
    node->setTag(tag);
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
