#pragma once

#include "cocos2d.h"

#include "CreatorReader_generated.h"

#ifdef __cplusplus
#define NS_CCR_BEGIN                     namespace creator {
#define NS_CCR_END                       }
#define USING_NS_CCR                     using namespace creator
#else
#define NS_CC_BEGIN
#define NS_CC_END
#define USING_NS_CC
#define NS_CC
#endif

NS_CCR_BEGIN

class CreatorReader: public cocos2d::Ref
{
public:
    static CreatorReader* createWithFilename(const std::string& filename);


    /**
     Returns the scenegraph contained in the .ccreator file
     @return A `Scene*`
     */
    cocos2d::Scene* getSceneGraph() const;


    /**
     Returns the FlatBuffers Schema version.
     @return a string containing the flatbuffer's schema version
     */
    std::string getVersion() const;

    /**
     Setup the needed spritesheets and change the design resolution if needed.
     Call it before getting the Scene graph
     */
    void setup();

protected:
    CreatorReader();
    ~CreatorReader();
    bool initWithFilename(const std::string& filename);

    cocos2d::Node* getNode(const void* buffer, buffers::AnyNode bufferType) const;

    cocos2d::Scene* createScene(const buffers::Scene* sceneBuffer) const;
    void parseScene(cocos2d::Scene* scene, const buffers::Scene* sceneBuffer) const;

    cocos2d::Node* createNode(const buffers::Node* nodeBuffer) const;
    void parseNode(cocos2d::Node* node, const buffers::Node* nodeBuffer) const;

    cocos2d::Sprite* createSprite(const buffers::Sprite* spriteBuffer) const;
    void parseSprite(cocos2d::Sprite* sprite, const buffers::Sprite* spriteBuffer) const;

    cocos2d::TMXTiledMap* createTileMap(const buffers::TileMap* tilemapBuffer) const;
    void parseTilemap(cocos2d::TMXTiledMap* tilemap, const buffers::TileMap* tilemapBuffer) const;

    cocos2d::Label* createLabel(const buffers::Label* labelBuffer) const;
    void parseLabel(cocos2d::Label* label, const buffers::Label* labelBuffer) const;

    cocos2d::ParticleSystemQuad* createParticle(const buffers::Particle* particleBuffer) const;
    void parseScene(cocos2d::ParticleSystemQuad* partile, const buffers::Particle* particleBuffer) const;


    // variables
    cocos2d::Scene* _scene;
    cocos2d::Data _data;
    std::string _version;
};

NS_CCR_END
