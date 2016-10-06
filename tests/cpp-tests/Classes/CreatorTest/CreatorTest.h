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

#ifndef _CREATOR_TEST_H_
#define _CREATOR_TEST_H_

#include "cocos2d.h"
#include "../BaseTest.h"
#include <string>


DEFINE_TEST_SUITE(CreatorTests);

class CreatorTestsBase : public TestCase
{
protected:
    std::string    _title;

public:
};

class CreatorTest1 : public CreatorTestsBase
{
public:
    CREATE_FUNC(CreatorTest1);
    CreatorTest1();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};

class CreatorLabels : public CreatorTestsBase
{
public:
    CREATE_FUNC(CreatorLabels);
    CreatorLabels();
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
};


#endif // _CREATOR_TEST_H_
