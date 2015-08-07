/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "DownloaderTest.h"

#include "../testResource.h"

USING_NS_CC;

DownloaderTests::DownloaderTests()
{
    ADD_TEST_CASE(DownloaderAsyncTest);
	ADD_TEST_CASE(DownloaderAsyncTest);
};

std::string DownloaderBaseTest::title() const
{
    return "Downloader Test";
}

//------------------------------------------------------------------
//
// DownloaderAsyncTest
//
//------------------------------------------------------------------

DownloaderAsyncTest::DownloaderAsyncTest()
{
}

void DownloaderAsyncTest::onEnter()
{
    DownloaderBaseTest::onEnter();

    auto menuItem = MenuItemFont::create("start download", [](Ref* sender){
        cocos2d::log("Downloading...");
    });
    auto menu = Menu::create(menuItem, nullptr);
    addChild(menu);
    menu->setNormalizedPosition(Vec2(0.5, 0.5));
}

std::string DownloaderAsyncTest::title() const
{
    return "Downloader";
}

std::string DownloaderAsyncTest::subtitle() const
{
    return "Tap to start downloading";
}



