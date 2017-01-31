//
//  AnimationClipProperties.hpp
//  cocos2d_tests
//
//  Created by Ricardo Quesada on 1/30/17.
//
//

#pragma once

#include "cocos2d.h"

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

struct AnimPropRotation
{
    float frame;
    float value;
};

struct AnimPropPosition
{
    float frame;
    cocos2d::Vec2 value;
    std::vector<float> motionPath;
};

struct AnimPropPositionX
{
    float frame;
    float value;
};

struct AnimPropPositionY
{
    float frame;
    float value;
};

struct AnimPropScaleX
{
    float frame;
    float value;
};

struct AnimPropScaleY
{
    float frame;
    float value;
};

struct AnimPropWidth
{
    float frame;
    float value;
};

struct AnimPropHeight
{
    float frame;
    float value;
};

struct AnimPropColor
{
    float frame;
    cocos2d::Color4B color;
};

struct AnimPropOpacity
{
    float frame;
    cocos2d::Color4B opacity;
};

struct AnimPropAnchorX
{
    float frame;
    float value;
};

struct AnimPropAnchorY
{
    float frame;
    float value;
};

struct AnimPropSkewX
{
    float frame;
    float value;
};

struct AnimPropSkewY
{
    float frame;
    float value;
};

struct AnimProperties
{
    std::vector<AnimPropRotation> animRotation;
    std::vector<AnimPropPosition> animPosition;
    std::vector<AnimPropPositionX> animPositionX;
    std::vector<AnimPropPositionY> animPositionY;
    std::vector<AnimPropSkewX> animSkewX;
    std::vector<AnimPropSkewY> animSkewY;
    std::vector<AnimPropAnchorX> animAnchorX;
    std::vector<AnimPropAnchorY> animAnchorY;
    std::vector<AnimPropColor> animColor;
    std::vector<AnimPropOpacity> animOpacity;
    std::vector<AnimPropWidth> animWidth;
    std::vector<AnimPropHeight> animHeight;
};

NS_CCR_END
