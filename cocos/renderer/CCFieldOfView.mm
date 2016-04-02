/****************************************************************************
 Copyright (c) 2016 Google
 Copyright (c) 2016 Chukong Technologies Inc.

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

#include "renderer/CCFieldOfView.h"

NS_CC_BEGIN

FieldOfView::FieldOfView() :
    _left(s_defaultViewAngle),
    _right(s_defaultViewAngle),
    _bottom(s_defaultViewAngle),
    _top(s_defaultViewAngle)
{
}

FieldOfView::FieldOfView(float left, float right, float bottom, float top)
{
    _left = left;
    _right = right;
    _bottom = bottom;
    _top = top;
}

FieldOfView::FieldOfView(FieldOfView *other)
{
    _left = other->_left;
    _right = other->_right;
    _bottom = other->_bottom;
    _top = other->_top;
}

void FieldOfView::setLeft(float left)
{
    _left = left;
}

float FieldOfView::left()
{
    return _left;
}

void FieldOfView::setRight(float right)
{
    _right = right;
}

float FieldOfView::right()
{
    return _right;
}

void FieldOfView::setBottom(float bottom)
{
    _bottom = bottom;
}

float FieldOfView::bottom()
{
    return _bottom;
}

void FieldOfView::setTop(float top)
{
    _top = top;
}

float FieldOfView::top()
{
    return _top;
}

Mat4 FieldOfView::toPerspectiveMatrix(float near, float far)
{
    float left = -tanf(CC_DEGREES_TO_RADIANS(_left)) * near;
    float right = tanf(CC_DEGREES_TO_RADIANS(_right)) * near;
    float bottom = -tanf(CC_DEGREES_TO_RADIANS(_bottom)) * near;
    float top = tanf(CC_DEGREES_TO_RADIANS(_top)) * near;

    Mat4 dst;
    Mat4::createOrthographicOffCenter(left, right, bottom, top, near, far, &dst);
    return dst;
}

bool FieldOfView::equals(FieldOfView *other)
{
    if (other == nullptr)
    {
        return false;
    }
    else if (other == this)
    {
        return true;
    }
    return
    (_left == other->_left)
    && (_right == other->_right)
    && (_bottom == other->_bottom)
    && (_top == other->_top);
}

std::string FieldOfView::toString() const
{
//    return [NSString stringWithFormat:@"{left:%f right:%f bottom:%f top:%f}", _left, _right, _bottom, _top];
    return "";
}

NS_CC_END
