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
#include <functional>
#include <unordered_map>

#include "platform/CCPlatformMacros.h"

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

namespace network
{
    struct HeaderInfo
    {
        bool valid;
        std::string url;
        std::string contentType;
        double contentSize;
        long responseCode;
    };

    struct DownloadUnit
    {
        std::string srcUrl;
        std::string storagePath;
        std::string customId;
        bool resumeDownload;
    };

    typedef std::unordered_map<std::string, DownloadUnit> DownloadUnits;

    class IURLDownload
    {
    public:
        IURLDownload(const std::string& url){}
        virtual ~IURLDownload(){}

        typedef std::function<int(void *ptr, ssize_t, ssize_t)> WritterCallback;
        typedef std::function<int(double, double)> ProgressCallback;

        enum class Options {
            RESUME
        };

        // methods that must be overriden
        virtual int performDownload(const WritterCallback& writterCallback,
                                    const ProgressCallback& progressCallback
                                    ) = 0;

        virtual int performBatchDownload(const DownloadUnits& units) = 0;

        virtual int getHeader(HeaderInfo* headerInfo) = 0;

        virtual bool checkOption(Options option) = 0;

        virtual std::string getStrError() const = 0;
    };
}

NS_CC_END
