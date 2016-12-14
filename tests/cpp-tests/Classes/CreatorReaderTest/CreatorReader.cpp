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

    cocos2d::Node* node = createTree(nodeTree);

    return static_cast<cocos2d::Scene*>(node);
}

std::string CreatorReader::getVersion() const
{
    return _version;
}

cocos2d::Node* CreatorReader::createTree(const buffers::NodeTree* tree) const
{
    cocos2d::Node *node = nullptr;

    const void* buffer = tree->object();
    buffers::AnyNode bufferType = tree->object_type();
    
    switch (bufferType) {
        case buffers::AnyNode_NONE:
            break;
        case buffers::AnyNode_Label:
            node = createLabel(static_cast<const buffers::Label*>(buffer));
        case buffers::AnyNode_Sprite:
            node = createSprite(static_cast<const buffers::Sprite*>(buffer));
        case buffers::AnyNode_TileMap:
            node = createTileMap(static_cast<const buffers::TileMap*>(buffer));
        case buffers::AnyNode_Particle:
            node = createParticle(static_cast<const buffers::Particle*>(buffer));
        case buffers::AnyNode_Scene:
            node = createScene(static_cast<const buffers::Scene*>(buffer));
        case buffers::AnyNode_Node:
            node = createNode(static_cast<const buffers::Node*>(buffer));
    }

    // recursively add its children
    const auto& children = tree->children();
    for(const auto& childBuffer: *children) {
        cocos2d::Node* child = createTree(childBuffer);
        node->addChild(child);
    }

    return node;
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
    cocos2d::Label* label = nullptr;
    auto text = labelBuffer->labelText();
    auto fontSize = labelBuffer->fontSize();
    auto fontName = labelBuffer->fontName();

    auto fontType = labelBuffer->fontType();
    switch (fontType) {
        case buffers::FontType_TTF:
            label = cocos2d::Label::createWithTTF(text->str(), fontName->str(), fontSize);
            break;
        case buffers::FontType_BMFont:
            label = cocos2d::Label::createWithBMFont(fontName->str(), text->str());
            label->setBMFontSize(fontSize);
            break;
        case buffers::FontType_System:
            label = cocos2d::Label::createWithSystemFont(text->str(), "arial", fontSize);
            break;
    }

    parseLabel(label, labelBuffer);
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
    const auto& lineHeight = labelBuffer->lineHeight();
    const auto& verticalA = labelBuffer->verticalAlignment();
    const auto& horizontalA = labelBuffer->horizontalAlignment();
    label->setVerticalAlignment(static_cast<cocos2d::TextVAlignment>(verticalA));
    label->setHorizontalAlignment(static_cast<cocos2d::TextHAlignment>(horizontalA));
    label->setLineHeight(lineHeight);
}

void CreatorReader::parseScene(cocos2d::ParticleSystemQuad* partile, const buffers::Particle* particleBuffer) const
{

}
