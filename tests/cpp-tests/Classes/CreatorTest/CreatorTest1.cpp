////// AUTOGENERATED:BEGIN //////
////// DO     NOT     EDIT //////

#include <ui/CocosGUI.h>

USING_NS_CC;

bool CreatorTest1_init()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    auto frameSize = glview->getFrameSize();
    glview->setDesignResolutionSize(frameSize.width / (frameSize.height / 640), frameSize.height / (frameSize.height / 640), ResolutionPolicy::NO_BORDER);

    // BEGIN SpriteFrame loading
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    // Files from .plist
    // creator_assets/test_polygon.plist processed manually. No need to include it in the assets folder

    // Files from .png
    auto sf_grossinis_sister2_png = SpriteFrame::create("creator_assets/test_polygon.png", Rect(279, 26, 55, 130), false, Vec2(0, -2), Size(56, 138));
    spriteFrameCache->addSpriteFrame(sf_grossinis_sister2_png, "grossinis_sister2.png");
    auto sf_test_polygon = SpriteFrame::create("creator_assets/test_polygon.png", Rect(4, 2, 380, 152), false, Vec2(0.5, 0.5), Size(387, 157));
    spriteFrameCache->addSpriteFrame(sf_test_polygon, "test_polygon");
    auto sf_default_btn_normal = SpriteFrame::create("creator_assets/image/default_btn_normal.png", Rect(0, 0, 40, 40), false, Vec2(0, 0), Size(40, 40));
    sf_default_btn_normal->setCenterRect(Rect(3,7,34,30));
    spriteFrameCache->addSpriteFrame(sf_default_btn_normal, "default_btn_normal");
    auto sf_default_scrollbar_bg = SpriteFrame::create("creator_assets/image/default_scrollbar_bg.png", Rect(0, 0, 30, 15), false, Vec2(0, 0), Size(30, 15));
    sf_default_scrollbar_bg->setCenterRect(Rect(10,0,10,15));
    spriteFrameCache->addSpriteFrame(sf_default_scrollbar_bg, "default_scrollbar_bg");
    auto sf_default_panel = SpriteFrame::create("creator_assets/image/default_panel.png", Rect(0, 0, 20, 20), false, Vec2(0, 0), Size(20, 20));
    sf_default_panel->setCenterRect(Rect(4,3,12,14));
    spriteFrameCache->addSpriteFrame(sf_default_panel, "default_panel");
    auto sf_arial16 = SpriteFrame::create("creator_assets/arial16.png", Rect(0, 0, 510, 61), false, Vec2(-1, 225.5), Size(512, 512));
    spriteFrameCache->addSpriteFrame(sf_arial16, "arial16");
    auto sf_default_scrollbar_vertical = SpriteFrame::create("creator_assets/image/default_scrollbar_vertical.png", Rect(2, 0, 11, 30), false, Vec2(0, 0), Size(15, 30));
    sf_default_scrollbar_vertical->setCenterRect(Rect(0,5,11,20));
    spriteFrameCache->addSpriteFrame(sf_default_scrollbar_vertical, "default_scrollbar_vertical");
    auto sf_default_sprite = SpriteFrame::create("creator_assets/image/default_sprite.png", Rect(0, 2, 40, 36), false, Vec2(0, 0), Size(40, 40));
    spriteFrameCache->addSpriteFrame(sf_default_sprite, "default_sprite");
    auto sf_default_btn_disabled = SpriteFrame::create("creator_assets/image/default_btn_disabled.png", Rect(0, 0, 40, 40), false, Vec2(0, 0), Size(40, 40));
    sf_default_btn_disabled->setCenterRect(Rect(4,8,32,28));
    spriteFrameCache->addSpriteFrame(sf_default_btn_disabled, "default_btn_disabled");
    auto sf_default_btn_pressed = SpriteFrame::create("creator_assets/image/default_btn_pressed.png", Rect(0, 0, 40, 40), false, Vec2(0, 0), Size(40, 40));
    sf_default_btn_pressed->setCenterRect(Rect(3,4,34,32));
    spriteFrameCache->addSpriteFrame(sf_default_btn_pressed, "default_btn_pressed");
    auto sf_default_scrollbar_vertical_bg = SpriteFrame::create("creator_assets/image/default_scrollbar_vertical_bg.png", Rect(0, 0, 15, 30), false, Vec2(0, 0), Size(15, 30));
    sf_default_scrollbar_vertical_bg->setCenterRect(Rect(0,8,15,15));
    spriteFrameCache->addSpriteFrame(sf_default_scrollbar_vertical_bg, "default_scrollbar_vertical_bg");
    auto sf_default_progressbar = SpriteFrame::create("creator_assets/image/default_progressbar.png", Rect(0, 0, 30, 15), false, Vec2(0, 0), Size(30, 15));
    sf_default_progressbar->setCenterRect(Rect(5,0,20,15));
    spriteFrameCache->addSpriteFrame(sf_default_progressbar, "default_progressbar");
    auto sf_default_sprite_splash = SpriteFrame::create("creator_assets/image/default_sprite_splash.png", Rect(0, 0, 2, 2), false, Vec2(0, 0), Size(2, 2));
    spriteFrameCache->addSpriteFrame(sf_default_sprite_splash, "default_sprite_splash");
    auto sf_island_polygon_png = SpriteFrame::create("creator_assets/test_polygon.png", Rect(1, 1, 287, 152), false, Vec2(16, 7), Size(320, 200));
    spriteFrameCache->addSpriteFrame(sf_island_polygon_png, "island_polygon.png");
    auto sf_grossini_dance_08 = SpriteFrame::create("creator_assets/grossini_dance_08.png", Rect(17, 7, 51, 109), false, Vec2(0, -1), Size(85, 121));
    spriteFrameCache->addSpriteFrame(sf_grossini_dance_08, "grossini_dance_08");
    auto sf_default_scrollbar = SpriteFrame::create("creator_assets/image/default_scrollbar.png", Rect(0, 2, 30, 11), false, Vec2(0, 0), Size(30, 15));
    sf_default_scrollbar->setCenterRect(Rect(10,0,10,11));
    spriteFrameCache->addSpriteFrame(sf_default_scrollbar, "default_scrollbar");
    auto sf_grossinis_sister1_png = SpriteFrame::create("creator_assets/test_polygon.png", Rect(336, 1, 50, 116), false, Vec2(0, -11), Size(52, 139));
    sf_grossinis_sister1_png->setCenterRect(Rect(7,71,34,39));
    spriteFrameCache->addSpriteFrame(sf_grossinis_sister1_png, "grossinis_sister1.png");
    auto sf_default_progressbar_bg = SpriteFrame::create("creator_assets/image/default_progressbar_bg.png", Rect(0, 0, 60, 15), false, Vec2(0, 0), Size(60, 15));
    sf_default_progressbar_bg->setCenterRect(Rect(5,0,50,15));
    spriteFrameCache->addSpriteFrame(sf_default_progressbar_bg, "default_progressbar_bg");
    auto sf_iso_test = SpriteFrame::create("creator_assets/iso-test.png", Rect(2, 1, 319, 116), false, Vec2(-94.5, 69), Size(512, 256));
    spriteFrameCache->addSpriteFrame(sf_iso_test, "iso-test");
    // END SpriteFrame loading

    return true;
}
Node* CreatorTest1_create()
{
    // New node
    auto scene_0_0 = Scene::create();
    scene_0_0->setAnchorPoint(Vec2(0, 0));
    scene_0_0->setColor(Color3B(255, 255, 255));
    scene_0_0->setLocalZOrder(0);
    scene_0_0->setGlobalZOrder(0);
    scene_0_0->setOpacity(255);
    scene_0_0->setOpacityModifyRGB(false);
    scene_0_0->setCascadeOpacityEnabled(true);
    scene_0_0->setTag(-1);
    scene_0_0->setContentSize(Size(0, 0));
    // New node
    auto tmxtiledmap_1_1 = TMXTiledMap::create("creator_assets/iso-test.tmx");
    tmxtiledmap_1_1->setAnchorPoint(Vec2(0.5, 0.5));
    tmxtiledmap_1_1->setScaleY(1);
    tmxtiledmap_1_1->setScaleX(1);
    tmxtiledmap_1_1->setColor(Color3B(255, 255, 255));
    tmxtiledmap_1_1->setName("iso-test");
    tmxtiledmap_1_1->setLocalZOrder(0);
    tmxtiledmap_1_1->setGlobalZOrder(0);
    tmxtiledmap_1_1->setOpacity(255);
    tmxtiledmap_1_1->setOpacityModifyRGB(false);
    tmxtiledmap_1_1->setCascadeOpacityEnabled(true);
    tmxtiledmap_1_1->setSkewX(0);
    tmxtiledmap_1_1->setTag(-1);
    tmxtiledmap_1_1->setContentSize(Size(4096, 2048));
    tmxtiledmap_1_1->setSkewY(0);
    tmxtiledmap_1_1->setRotationSkewY(0);
    tmxtiledmap_1_1->setPosition(Vec2(494, 231));
    tmxtiledmap_1_1->setRotationSkewX(0);
    scene_0_0->addChild(tmxtiledmap_1_1);
    // New node
    auto particlesystemquad_1_2 = ParticleSystemQuad::create("creator_assets/Galaxy.plist");
    particlesystemquad_1_2->setAnchorPoint(Vec2(0.5, 0.5));
    particlesystemquad_1_2->setScaleY(1);
    particlesystemquad_1_2->setScaleX(1);
    particlesystemquad_1_2->setColor(Color3B(255, 255, 255));
    particlesystemquad_1_2->setName("Galaxy");
    particlesystemquad_1_2->setLocalZOrder(0);
    particlesystemquad_1_2->setGlobalZOrder(0);
    particlesystemquad_1_2->setOpacity(255);
    particlesystemquad_1_2->setOpacityModifyRGB(false);
    particlesystemquad_1_2->setCascadeOpacityEnabled(true);
    particlesystemquad_1_2->setSkewX(0);
    particlesystemquad_1_2->setTag(-1);
    particlesystemquad_1_2->setContentSize(Size(0, 0));
    particlesystemquad_1_2->setSkewY(0);
    particlesystemquad_1_2->setRotationSkewY(0);
    particlesystemquad_1_2->setPosition(Vec2(115, 251));
    particlesystemquad_1_2->setRotationSkewX(0);
    scene_0_0->addChild(particlesystemquad_1_2);
    // New node
    auto sprite_1_3 = Sprite::create();
    sprite_1_3->setSpriteFrame("grossini_dance_08");
    sprite_1_3->setAnchorPoint(Vec2(0.5, 0.5));
    sprite_1_3->setScaleY(3);
    sprite_1_3->setScaleX(2);
    sprite_1_3->setColor(Color3B(255, 255, 255));
    sprite_1_3->setName("New Sprite (Splash)");
    sprite_1_3->setLocalZOrder(0);
    sprite_1_3->setGlobalZOrder(0);
    sprite_1_3->setOpacity(255);
    sprite_1_3->setOpacityModifyRGB(false);
    sprite_1_3->setCascadeOpacityEnabled(true);
    sprite_1_3->setSkewX(0);
    sprite_1_3->setTag(-1);
    sprite_1_3->setContentSize(Size(51, 109));
    sprite_1_3->setSkewY(0);
    sprite_1_3->setRotationSkewY(0);
    sprite_1_3->setPosition(Vec2(263, 542));
    sprite_1_3->setRotationSkewX(0);
    scene_0_0->addChild(sprite_1_3);
    // New node
    auto sprite_1_4 = Sprite::create();
    sprite_1_4->setSpriteFrame("grossini_dance_08");
    sprite_1_4->setAnchorPoint(Vec2(0.5, 0.5));
    sprite_1_4->setScaleY(1);
    sprite_1_4->setScaleX(1);
    sprite_1_4->setColor(Color3B(255, 255, 255));
    sprite_1_4->setName("grossini_dance_08");
    sprite_1_4->setLocalZOrder(0);
    sprite_1_4->setGlobalZOrder(0);
    sprite_1_4->setOpacity(255);
    sprite_1_4->setOpacityModifyRGB(false);
    sprite_1_4->setCascadeOpacityEnabled(true);
    sprite_1_4->setSkewX(0);
    sprite_1_4->setTag(-1);
    sprite_1_4->setContentSize(Size(51, 109));
    sprite_1_4->setSkewY(0);
    sprite_1_4->setRotationSkewY(0);
    sprite_1_4->setPosition(Vec2(100, 407));
    sprite_1_4->setRotationSkewX(0);
    scene_0_0->addChild(sprite_1_4);
    // New node
    auto label_1_5 = Label::createWithSystemFont("This is a label", "arial", 40);
    label_1_5->setAnchorPoint(Vec2(0.5, 0.5));
    label_1_5->setScaleY(1);
    label_1_5->setScaleX(1);
    label_1_5->setColor(Color3B(255, 255, 255));
    label_1_5->setName("Label_1");
    label_1_5->setVerticalAlignment(TextVAlignment::CENTER);
    label_1_5->setLocalZOrder(0);
    label_1_5->setGlobalZOrder(0);
    label_1_5->setOpacity(255);
    label_1_5->setOpacityModifyRGB(false);
    label_1_5->setCascadeOpacityEnabled(true);
    label_1_5->setHorizontalAlignment(TextHAlignment::CENTER);
    label_1_5->setSkewX(0);
    label_1_5->setTag(-1);
    label_1_5->setContentSize(Size(244.55, 40));
    label_1_5->setSkewY(0);
    label_1_5->setRotationSkewY(0);
    label_1_5->setPosition(Vec2(437, 606));
    label_1_5->setRotationSkewX(0);
    scene_0_0->addChild(label_1_5);
    // New node
    auto label_1_6 = Label::createWithSystemFont("This is another label", "arial", 40);
    label_1_6->setAnchorPoint(Vec2(0.5, 0.5));
    label_1_6->setScaleY(1);
    label_1_6->setScaleX(1);
    label_1_6->setColor(Color3B(255, 255, 255));
    label_1_6->setName("Label_2");
    label_1_6->setVerticalAlignment(TextVAlignment::CENTER);
    label_1_6->setLocalZOrder(0);
    label_1_6->setGlobalZOrder(0);
    label_1_6->setOpacity(255);
    label_1_6->setOpacityModifyRGB(false);
    label_1_6->setCascadeOpacityEnabled(true);
    label_1_6->setHorizontalAlignment(TextHAlignment::CENTER);
    label_1_6->setSkewX(0);
    label_1_6->setTag(-1);
    label_1_6->setContentSize(Size(357.97, 40));
    label_1_6->setSkewY(0);
    label_1_6->setRotationSkewY(0);
    label_1_6->setPosition(Vec2(107, 289));
    label_1_6->setRotationSkewX(0);
    scene_0_0->addChild(label_1_6);
    return scene_0_0;
}
////// AUTOGENERATED:END//////
