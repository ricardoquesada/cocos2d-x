/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.

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

#include "CreatorReaderTest.h"
#include "CreatorReader.h"

USING_NS_CC;
USING_NS_CCR;

CreatorReaderTests::CreatorReaderTests()
{
    ADD_TEST_CASE(CreatorReaderTest1);
    ADD_TEST_CASE(CreatorReaderTest2);
    ADD_TEST_CASE(CreatorReaderTest3);
    ADD_TEST_CASE(CreatorReaderTest4);
    ADD_TEST_CASE(CreatorReaderTest5);
};

//------------------------------------------------------------------
//
// CreatorReaderTest1
//
//------------------------------------------------------------------

CreatorReaderTest1::CreatorReaderTest1()
{
    CreatorReader* reader = CreatorReader::createWithFilename("creator/CreatorLabels.ccreator");
    CCLOG("Version: %s", reader->getVersion().c_str());

    // will create the needed spritesheets, design resolution
    reader->setup();
    Scene* scene = reader->getSceneGraph();
    addChild(scene);
}

std::string CreatorReaderTest1::title() const
{
    return "Reading labels";
}

//------------------------------------------------------------------
//
// CreatorReaderTest2
//
//------------------------------------------------------------------

CreatorReaderTest2::CreatorReaderTest2()
{
    CreatorReader* reader = CreatorReader::createWithFilename("creator/CreatorSprites.ccreator");
    CCLOG("Version: %s", reader->getVersion().c_str());

    // will create the needed spritesheets, design resolution
    reader->setup();
    Scene* scene = reader->getSceneGraph();
    addChild(scene);
}

std::string CreatorReaderTest2::title() const
{
    return "Reading sprites";
}


//------------------------------------------------------------------
//
// CreatorReaderTest3
//
//------------------------------------------------------------------

CreatorReaderTest3::CreatorReaderTest3()
{
    CreatorReader* reader = CreatorReader::createWithFilename("creator/CreatorUI.ccreator");
    CCLOG("Version: %s", reader->getVersion().c_str());

    // will create the needed spritesheets, design resolution
    reader->setup();
    Scene* scene = reader->getSceneGraph();
    addChild(scene);
}

std::string CreatorReaderTest3::title() const
{
    return "Reading UI";
}

//------------------------------------------------------------------
//
// CreatorReaderTest4
//
//------------------------------------------------------------------

CreatorReaderTest4::CreatorReaderTest4()
{
    CreatorReader* reader = CreatorReader::createWithFilename("creator/CreatorTilemap.ccreator");
    CCLOG("Version: %s", reader->getVersion().c_str());

    // will create the needed spritesheets, design resolution
    reader->setup();
    Scene* scene = reader->getSceneGraph();
    addChild(scene);
}

std::string CreatorReaderTest4::title() const
{
    return "Reading Tilemaps";
}

//------------------------------------------------------------------
//
// CreatorReaderTest5
//
//------------------------------------------------------------------

CreatorReaderTest5::CreatorReaderTest5()
{
    CreatorReader* reader = CreatorReader::createWithFilename("creator/CreatorAnim.ccreator");
    CCLOG("Version: %s", reader->getVersion().c_str());

    // will create the needed spritesheets, design resolution
    reader->setup();
    Scene* scene = reader->getSceneGraph();
    addChild(scene);
}

std::string CreatorReaderTest5::title() const
{
    return "Reading Animations";
}

