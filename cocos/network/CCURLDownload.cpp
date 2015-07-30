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

#include "network/CCURLDownload.h"

#include <curl/curl.h>

USING_NS_CC;
using namespace cocos2d::network;

static const long LOW_SPEED_LIMIT = 1;
static const long LOW_SPEED_TIME = 5;
static const int DEFAULT_TIMEOUT = 5;

URLDownload::URLDownload()
: _curl(nullptr)
{
    _curl = curl_easy_init();
}
URLDownload::~URLDownload()
{
    if (_curl)
        curl_easy_cleanup(_curl);
}

size_t fileWriteFunc(void *ptr, size_t size, size_t nmemb, URLDownload* this_)
{
    this_->getWritterCallback()();
    return size;
}

int static downloadProgressFunc(URLDownload* this_, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
    this_->getProgressCallback()();
    return 0;
}

int URLDownload::performDownload(const std::string& url,
                            const std::function<void()>& writterCallback,
                            const std::function<void()>& progressCallback
                            )
{
    // Download pacakge
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, fileWriteFunc);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, this);

    curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, downloadProgressFunc);
    curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, this);

    curl_easy_setopt(_curl, CURLOPT_FAILONERROR, true);
    curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, DEFAULT_TIMEOUT);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_LIMIT, LOW_SPEED_LIMIT);
    curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_TIME, LOW_SPEED_TIME);

    _writterCallback = writterCallback;
    _progressCallback = progressCallback;
    CURLcode res = curl_easy_perform(_curl);
    return res;
}

int URLDownload::getHeader(const std::string& url, HeaderInfo* headerInfo)
{
    CC_ASSERT(_curl && "not initialized");
    CC_ASSERT(headerInfo && "headerInfo must not be null");

    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(_curl, CURLOPT_HEADER, 1);
    curl_easy_setopt(_curl, CURLOPT_NOBODY, 1);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1);
    if (curl_easy_perform(_curl) == CURLE_OK)
    {
        char *effectiveUrl;
        char *contentType;
        curl_easy_getinfo(_curl, CURLINFO_EFFECTIVE_URL, &effectiveUrl);
        curl_easy_getinfo(_curl, CURLINFO_CONTENT_TYPE, &contentType);
        curl_easy_getinfo(_curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &headerInfo->contentSize);
        curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &headerInfo->responseCode);

        if (contentType == nullptr || headerInfo->contentSize == -1 || headerInfo->responseCode >= 400)
        {
            headerInfo->valid = false;
        }
        else
        {
            headerInfo->url = effectiveUrl;
            headerInfo->contentType = contentType;
            headerInfo->valid = true;
        }

        return 0;
    }

    return -1;
}
