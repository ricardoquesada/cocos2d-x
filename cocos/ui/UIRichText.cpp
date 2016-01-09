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

#include "UIRichText.h"

#include <vector>

#include "tinyxml2/tinyxml2.h"
#include "platform/CCFileUtils.h"
#include "2d/CCLabel.h"
#include "2d/CCSprite.h"
#include "base/ccUTF8.h"
#include "ui/UIHelper.h"

NS_CC_BEGIN

namespace ui {

    
bool RichElement::init(int tag, const Color3B &color, GLubyte opacity)
{
    _tag = tag;
    _color = color;
    _opacity = opacity;
    return true;
}
    
    
RichElementText* RichElementText::create(int tag, const Color3B &color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize)
{
    RichElementText* element = new (std::nothrow) RichElementText();
    if (element && element->init(tag, color, opacity, text, fontName, fontSize))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool RichElementText::init(int tag, const Color3B &color, GLubyte opacity, const std::string& text, const std::string& fontName, float fontSize)
{
    if (RichElement::init(tag, color, opacity))
    {
        _text = text;
        _fontName = fontName;
        _fontSize = fontSize;
        return true;
    }
    return false;
}

RichElementImage* RichElementImage::create(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath)
{
    RichElementImage* element = new (std::nothrow) RichElementImage();
    if (element && element->init(tag, color, opacity, filePath))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool RichElementImage::init(int tag, const Color3B &color, GLubyte opacity, const std::string& filePath)
{
    if (RichElement::init(tag, color, opacity))
    {
        _filePath = filePath;
        return true;
    }
    return false;
}

RichElementCustomNode* RichElementCustomNode::create(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
{
    RichElementCustomNode* element = new (std::nothrow) RichElementCustomNode();
    if (element && element->init(tag, color, opacity, customNode))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
bool RichElementCustomNode::init(int tag, const Color3B &color, GLubyte opacity, cocos2d::Node *customNode)
{
    if (RichElement::init(tag, color, opacity))
    {
        _customNode = customNode;
        _customNode->retain();
        return true;
    }
    return false;
}
    
RichElementNewLine* RichElementNewLine::create(int tag, const Color3B& color, GLubyte opacity)
{
    RichElementNewLine* element = new (std::nothrow) RichElementNewLine();
    if (element && element->init(tag, color, opacity))
    {
        element->autorelease();
        return element;
    }
    CC_SAFE_DELETE(element);
    return nullptr;
}
    
RichText::RichText():
_formatTextDirty(true),
_leftSpaceWidth(0.0f),
_verticalSpace(0.0f)
{
    
}
    
RichText::~RichText()
{
    _richElements.clear();
}
    
RichText* RichText::create()
{
    RichText* widget = new (std::nothrow) RichText();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

RichText* RichText::createWithXML(const std::string& xml)
{
    RichText* widget = new (std::nothrow) RichText();
    if (widget && widget->initWithXML(xml))
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
    
bool RichText::init()
{
    if (Widget::init())
    {
        return true;
    }
    return false;
}

class MyXMLVisitor: public tinyxml2::XMLVisitor
{
    struct Attributes
    {
        std::string face;
        float fontSize;
        Color3B color;
        bool hasColor;
        int bold;
        int italics;

        void setColor(const Color3B& acolor)
        {
            color = acolor;
            hasColor = true;
        }
        Attributes()
        : bold(-1)
        , italics(-1)
        , hasColor(false)
        , fontSize(-1)
        , face()
        {
        }
    };

    std::vector<Attributes> _fontElements;

    RichText* _richText;

    Color3B getColor() const
    {
        for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
        {
            if (i->hasColor)
                return i->color;
        }
        return Color3B::WHITE;
    }

    float getFontSize() const
    {
        for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
        {
            if (i->fontSize != -1)
                return i->fontSize;
        }
        return 12;
    }

    std::string getFace() const
    {
        for (auto i = _fontElements.rbegin(); i != _fontElements.rend(); ++i)
        {
            if (i->face.size() != 0)
                return i->face;
        }
        return "fonts/Marker Felt.ttf";
    }

public:
    explicit MyXMLVisitor(RichText* richText)
    : _richText(richText)
    , _fontElements(20)
    {}
    virtual ~MyXMLVisitor() {}

    /// Visit an element.
    virtual bool VisitEnter( const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute )
    {
        auto elementName = element.Value();

        if (strcmp(elementName, "font") == 0)
        {
            // supported attributes:
            // size, color, align, face
            auto size = element.Attribute("size");
            auto color = element.Attribute("color");
            auto face = element.Attribute("face");

            Attributes attribs;
            if (size)
                attribs.fontSize = atof(size);
            if (color)
            {
                if (strlen(color) == 7)
                {
                    int r,g,b;
                    sscanf(color, "%*c%2x%2x%2x", &r, &g, &b);
                    attribs.setColor(Color3B(r,g,b));
                }
                else
                    attribs.setColor(Color3B::WHITE);
            }
            if (face)
                attribs.face = face;

            _fontElements.push_back(attribs);
        }
        else if (strcmp(elementName, "b") == 0)
        {
            // no supported attributes
            Attributes attribs;
            attribs.bold = 1;
            _fontElements.push_back(attribs);
        }
        else if (strcmp(elementName, "i") == 0)
        {
            // no supported attributes
            Attributes attribs;
            attribs.italics = 1;
            _fontElements.push_back(attribs);
        }

        else if (strcmp(elementName, "img") == 0)
        {
            // supported attributes:
            // src, height, width
            auto src = element.Attribute("src");
            auto height = element.Attribute("height");
            auto width = element.Attribute("width");

        }
        else if (strcmp(elementName, "a") ==  0)
        {
            // supported attributes:
            // href
            auto href = element.Attribute("href");
        }
        else if (strcmp(elementName, "br") == 0)
        {
            auto color = getColor();
            auto elementNL = RichElementNewLine::create(0, color, 255);
            _richText->pushBackElement(elementNL);
        }

        CCLOG("VisitEnter XMLElement: %s, %s", element.Value(), firstAttribute? firstAttribute->Value() : "");
        return true;
    }
    /// Visit an element.
    virtual bool VisitExit( const tinyxml2::XMLElement& element )
    {
        auto elementName = element.Value();
        if ((strcmp(elementName, "font") == 0) ||
            (strcmp(elementName, "i") == 0) ||
            (strcmp(elementName, "b") == 0))
        {
            _fontElements.pop_back();
        }
        return true;
    }

    /// Visit a text node.
    virtual bool Visit( const tinyxml2::XMLText& text)
    {
        auto color = getColor();
        auto face = getFace();
        auto fontSize = getFontSize();

        auto element = RichElementText::create(0, color, 255, text.Value(), face, fontSize);
        _richText->pushBackElement(element);
        return true;
    }
};

bool RichText::initWithXML(const std::string& origxml)
{
    if (Widget::init())
    {
        tinyxml2::XMLDocument document;

        // solves to issues:
        //  - creates defaults values
        //  - makes sure that the xml well formed and starts with an element
        auto xml = "<font face=\"verdana\" size=\"12\" color=\"black\" align=\"left\">" + origxml + "</font>";

        if (document.Parse(xml.c_str(), xml.length()) == tinyxml2::XML_SUCCESS)
        {
            MyXMLVisitor visitor(this);
            document.Accept(&visitor);
            return true;
        }
    }
    return false;
}
    
void RichText::initRenderer()
{
}

void RichText::insertElement(RichElement *element, int index)
{
    _richElements.insert(index, element);
    _formatTextDirty = true;
}
    
void RichText::pushBackElement(RichElement *element)
{
    _richElements.pushBack(element);
    _formatTextDirty = true;
}
    
void RichText::removeElement(int index)
{
    _richElements.erase(index);
    _formatTextDirty = true;
}
    
void RichText::removeElement(RichElement *element)
{
    _richElements.eraseObject(element);
    _formatTextDirty = true;
}
    
void RichText::formatText()
{
    if (_formatTextDirty)
    {
        this->removeAllProtectedChildren();
        _elementRenders.clear();
        if (_ignoreSize)
        {
            addNewLine();
            for (ssize_t i=0; i<_richElements.size(); i++)
            {
                RichElement* element = _richElements.at(i);
                Node* elementRenderer = nullptr;
                switch (element->_type)
                {
                    case RichElement::Type::TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
                        if (FileUtils::getInstance()->isFileExist(elmtText->_fontName))
                        {
                            elementRenderer = Label::createWithTTF(elmtText->_text, elmtText->_fontName, elmtText->_fontSize);
                        }
                        else
                        {
                            elementRenderer = Label::createWithSystemFont(elmtText->_text, elmtText->_fontName, elmtText->_fontSize);
                        }
                        break;
                    }
                    case RichElement::Type::IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
                        elementRenderer = Sprite::create(elmtImage->_filePath);
                        break;
                    }
                    case RichElement::Type::CUSTOM:
                    {
                        RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
                        elementRenderer = elmtCustom->_customNode;
                        break;
                    }
                    case RichElement::Type::NEWLINE:
                    {
                        addNewLine();
                        break;
                    }
                    default:
                        break;
                }

                if (elementRenderer)
                {
                    elementRenderer->setColor(element->_color);
                    elementRenderer->setOpacity(element->_opacity);
                    pushToContainer(elementRenderer);
                }
            }
        }
        else
        {
            addNewLine();
            for (ssize_t i=0; i<_richElements.size(); i++)
            {
                RichElement* element = static_cast<RichElement*>(_richElements.at(i));
                switch (element->_type)
                {
                    case RichElement::Type::TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
                        handleTextRenderer(elmtText->_text, elmtText->_fontName, elmtText->_fontSize, elmtText->_color, elmtText->_opacity);
                        break;
                    }
                    case RichElement::Type::IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
                        handleImageRenderer(elmtImage->_filePath, elmtImage->_color, elmtImage->_opacity);
                        break;
                    }
                    case RichElement::Type::CUSTOM:
                    {
                        RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
                        handleCustomRenderer(elmtCustom->_customNode);
                        break;
                    }
                    case RichElement::Type::NEWLINE:
                    {
                        addNewLine();
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        formarRenderers();
        _formatTextDirty = false;
    }
}

void RichText::handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B &color, GLubyte opacity)
{
    auto fileExist = FileUtils::getInstance()->isFileExist(fontName);
    Label* textRenderer = nullptr;
    if (fileExist)
    {
        textRenderer = Label::createWithTTF(text, fontName, fontSize);
    } 
    else
    {
        textRenderer = Label::createWithSystemFont(text, fontName, fontSize);
    }
    float textRendererWidth = textRenderer->getContentSize().width;
    _leftSpaceWidth -= textRendererWidth;
    if (_leftSpaceWidth < 0.0f)
    {
        float overstepPercent = (-_leftSpaceWidth) / textRendererWidth;
        std::string curText = text;
        size_t stringLength = StringUtils::getCharacterCountInUTF8String(text);
        int leftLength = stringLength * (1.0f - overstepPercent);
        
        // The adjustment of the new line position
        auto originalLeftSpaceWidth = _leftSpaceWidth + textRendererWidth;
        auto leftStr = Helper::getSubStringOfUTF8String(curText, 0, leftLength);
        textRenderer->setString(leftStr);
        auto leftWidth = textRenderer->getContentSize().width;
        if (originalLeftSpaceWidth < leftWidth) {
            // Have protruding
            for (;;) {
                leftLength--;
                leftStr = Helper::getSubStringOfUTF8String(curText, 0, leftLength);
                textRenderer->setString(leftStr);
                leftWidth = textRenderer->getContentSize().width;
                if (leftWidth <= originalLeftSpaceWidth) {
                    break;
                }
                else if (leftLength <= 0) {
                    break;
                }
            }
        }
        else if (leftWidth < originalLeftSpaceWidth) {
            // A wide margin
            for (;;) {
                leftLength++;
                leftStr = Helper::getSubStringOfUTF8String(curText, 0, leftLength);
                textRenderer->setString(leftStr);
                leftWidth = textRenderer->getContentSize().width;
                if (originalLeftSpaceWidth < leftWidth) {
                    leftLength--;
                    break;
                }
                else if (stringLength <= leftLength) {
                    break;
                }
            }
        }
        
        //The minimum cut length is 1, otherwise will cause the infinite loop.
        if (0 == leftLength) leftLength = 1;
        std::string leftWords = Helper::getSubStringOfUTF8String(curText,0,leftLength);
        std::string cutWords = Helper::getSubStringOfUTF8String(curText, leftLength, stringLength - leftLength);
        if (leftLength > 0)
        {
            Label* leftRenderer = nullptr;
            if (fileExist)
            {
                leftRenderer = Label::createWithTTF(Helper::getSubStringOfUTF8String(leftWords, 0, leftLength), fontName, fontSize);
            }
            else
            {
                leftRenderer = Label::createWithSystemFont(Helper::getSubStringOfUTF8String(leftWords, 0, leftLength), fontName, fontSize);
            }
            if (leftRenderer)
            {
                leftRenderer->setColor(color);
                leftRenderer->setOpacity(opacity);
                pushToContainer(leftRenderer);
            }
        }

        addNewLine();
        handleTextRenderer(cutWords, fontName, fontSize, color, opacity);
    }
    else
    {
        textRenderer->setColor(color);
        textRenderer->setOpacity(opacity);
        pushToContainer(textRenderer);
    }
}
    
void RichText::handleImageRenderer(const std::string& fileParh, const Color3B &color, GLubyte opacity)
{
    Sprite* imageRenderer = Sprite::create(fileParh);
    handleCustomRenderer(imageRenderer);
}
    
void RichText::handleCustomRenderer(cocos2d::Node *renderer)
{
    Size imgSize = renderer->getContentSize();
    _leftSpaceWidth -= imgSize.width;
    if (_leftSpaceWidth < 0.0f)
    {
        addNewLine();
        pushToContainer(renderer);
        _leftSpaceWidth -= imgSize.width;
    }
    else
    {
        pushToContainer(renderer);
    }
}
    
void RichText::addNewLine()
{
    _leftSpaceWidth = _customSize.width;
    _elementRenders.push_back(new Vector<Node*>());
}
    
void RichText::formarRenderers()
{
    if (_ignoreSize)
    {
        float newContentSizeWidth = 0.0f;
        float nextPosY = 0.0f;
        for (auto& element: _elementRenders)
        {
            Vector<Node*>* row = element;
            float nextPosX = 0.0f;
            float maxY = 0.0f;
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                l->setAnchorPoint(Vec2::ZERO);
                l->setPosition(nextPosX, nextPosY);
                this->addProtectedChild(l, 1);
                Size iSize = l->getContentSize();
                newContentSizeWidth += iSize.width;
                nextPosX += iSize.width;
                maxY = MAX(maxY, iSize.height);
            }
            nextPosY -= maxY;
        }
        this->setContentSize(Size(newContentSizeWidth, -nextPosY));
    }
    else
    {
        float newContentSizeHeight = 0.0f;
        float *maxHeights = new (std::nothrow) float[_elementRenders.size()];
        
        for (size_t i=0; i<_elementRenders.size(); i++)
        {
            Vector<Node*>* row = (_elementRenders[i]);
            float maxHeight = 0.0f;
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                maxHeight = MAX(l->getContentSize().height, maxHeight);
            }
            maxHeights[i] = maxHeight;
            newContentSizeHeight += maxHeights[i];
        }
        
        float nextPosY = _customSize.height;
        for (size_t i=0; i<_elementRenders.size(); i++)
        {
            Vector<Node*>* row = (_elementRenders[i]);
            float nextPosX = 0.0f;
            nextPosY -= (maxHeights[i] + _verticalSpace);
            
            for (ssize_t j=0; j<row->size(); j++)
            {
                Node* l = row->at(j);
                l->setAnchorPoint(Vec2::ZERO);
                l->setPosition(nextPosX, nextPosY);
                this->addProtectedChild(l, 1);
                nextPosX += l->getContentSize().width;
            }
        }
        delete [] maxHeights;
    }
    
    size_t length = _elementRenders.size();
    for (size_t i = 0; i<length; i++)
	{
        Vector<Node*>* l = _elementRenders[i];
        l->clear();
        delete l;
	}    
    _elementRenders.clear();
    
    if (_ignoreSize)
    {
        Size s = getVirtualRendererSize();
        this->setContentSize(s);
    }
    else
    {
        this->setContentSize(_customSize);
    }
    updateContentSizeWithTextureSize(_contentSize);
}
    
void RichText::adaptRenderers()
{
    this->formatText();
}
    
void RichText::pushToContainer(cocos2d::Node *renderer)
{
    if (_elementRenders.size() <= 0)
    {
        return;
    }
    _elementRenders[_elementRenders.size()-1]->pushBack(renderer);
}
    
void RichText::setVerticalSpace(float space)
{
    _verticalSpace = space;
}

void RichText::ignoreContentAdaptWithSize(bool ignore)
{
    if (_ignoreSize != ignore)
    {
        _formatTextDirty = true;
        Widget::ignoreContentAdaptWithSize(ignore);
    }
}
    
std::string RichText::getDescription() const
{
    return "RichText";
}

}

NS_CC_END
