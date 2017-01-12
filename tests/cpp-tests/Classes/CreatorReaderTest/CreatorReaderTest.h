/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org

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

#pragma once

#include "cocos2d.h"
#include "../BaseTest.h"
#include <string>

DEFINE_TEST_SUITE(CreatorReaderTests);

class CreatorReaderTestDemo : public TestCase
{
protected:
    std::string    _title;

public:
};

class CreatorReaderTest1 : public CreatorReaderTestDemo
{
public:
    CREATE_FUNC(CreatorReaderTest1);
    CreatorReaderTest1();
    virtual std::string title() const override;
};

class CreatorReaderTest2 : public CreatorReaderTestDemo
{
public:
    CREATE_FUNC(CreatorReaderTest2);
    CreatorReaderTest2();
    virtual std::string title() const override;
};

class CreatorReaderTest3 : public CreatorReaderTestDemo
{
public:
    CREATE_FUNC(CreatorReaderTest3);
    CreatorReaderTest3();
    virtual std::string title() const override;
};

class CreatorReaderTest4 : public CreatorReaderTestDemo
{
public:
    CREATE_FUNC(CreatorReaderTest4);
    CreatorReaderTest4();
    virtual std::string title() const override;
};

class CreatorReaderTest5 : public CreatorReaderTestDemo
{
public:
    CREATE_FUNC(CreatorReaderTest5);
    CreatorReaderTest5();
    virtual std::string title() const override;
};
