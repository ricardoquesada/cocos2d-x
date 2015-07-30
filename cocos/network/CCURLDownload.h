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

#pragma once

#include <string>
#include <curl/curl.h>

#include "network/CCIURLDownload.h"
#include "platform/CCPlatformMacros.h"

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network
{
    class URLDownload : public IURLDownload
    {
    public:
        URLDownload(const std::string& url);
        virtual ~URLDownload();

        // Overrides
        virtual int performDownload(const WritterCallback& writterCallback,
                                    const ProgressCallback& progressCallback
                                    ) override;
        virtual int getHeader(HeaderInfo* headerInfo) override;

        virtual std::string getStrError() const override;
        virtual bool checkOption(Options option);

        //
        const WritterCallback& getWritterCallback() const { return _writterCallback; }
        const ProgressCallback& getProgressCallback() const { return _progressCallback; }

    private:
        std::string _url;
        WritterCallback _writterCallback;
        ProgressCallback _progressCallback;

        void* _curlHandle;
        CURLcode _lastErrCode;
    };

} // namespace network

NS_CC_END

// end group
/// @}
