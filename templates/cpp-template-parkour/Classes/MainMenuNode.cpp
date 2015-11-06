/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.

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

#include "MainMenuNode.h"
#include "GameNode.h"

#include "audio/include/SimpleAudioEngine.h"

using namespace cocos2d;

Scene* createSceneWithMainMenu()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'node' is another autorelease object
    auto node = MainMenuNode::create();

    // add mainmenu to the scene
    scene->addChild(node);

    // return the scene
    return scene;
}

MainMenuNode* MainMenuNode::create()
{
    // nothrow doesn't raise exception on error. Instead, return nullptr
    auto node = new (std::nothrow) MainMenuNode();
    if (node && node->init())
    {
        node->autorelease();
    }
    return node;
}

MainMenuNode::MainMenuNode()
{
}

MainMenuNode::~MainMenuNode()
{
}

// on "init" you need to initialize your instance
bool MainMenuNode::init()
{
    // call super
    if ( !Node::init() )
        return false;

    // play background music and preload effects
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
//    audio->playBackgroundMusic("sfx/background.mp3", true);
    audio->preloadEffect("sfx/jump.mp3");
    audio->preloadEffect("sfx/pickup_coin.mp3");
    audio->preloadEffect("sfx/crouch.mp3");


    // nodes has a default size of (0,0).
    // in order to use setNormalizedPosition correctly, we should set a size
    this->setContentSize( Director::getInstance()->getVisibleSize());

    //
    // Background image
    //

    // create background image
    auto image = Sprite::create("menuBackground.png");

    // set it on the center of the screen
    image->setNormalizedPosition(Vec2(0.5,0.5));

    // parent-child
    this->addChild(image);


    //
    // Menu
    //
    // create a menu with a "normal" and a "selected" image
    auto item = MenuItemImage::create("start_n.png", "start_s.png");
    auto menu = Menu::create(item, NULL);

    // set callback for menu using C++11 lambda feature
    item->setCallback([](Ref* sender){
        Director::getInstance()->replaceScene(createSceneWithGame());
    });

    // center menu
    menu->setNormalizedPosition(Vec2(0.5,0.5));

    // parent-child
    this->addChild(menu);


    return true;
}

