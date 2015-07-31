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
static const int HTTP_CODE_SUPPORT_RESUME = 206;

URLDownload::URLDownload(const std::string& url)
: IURLDownload(url)
, _curlHandle(nullptr)
, _lastErrCode(CURLE_OK)
, _url(url)
{
    _curlHandle = curl_easy_init();
    curl_easy_setopt(_curlHandle, CURLOPT_URL, _url.c_str());
}
URLDownload::~URLDownload()
{
    if (_curlHandle)
        curl_easy_cleanup(_curlHandle);
}

size_t fileWriteFunc(void *ptr, size_t size, size_t nmemb, URLDownload* this_)
{
    return this_->getWritterCallback()(ptr, size, nmemb);
}

int static downloadProgressFunc(URLDownload* this_, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
    this_->getProgressCallback()(totalToDownload, nowDownloaded);
    return 0;
}

std::string URLDownload::getStrError() const
{
    return curl_easy_strerror(_lastErrCode);
}

int URLDownload::performDownload(const WritterCallback& writterCallback,
                            const ProgressCallback& progressCallback
                            )
{
    // Download pacakge
    curl_easy_setopt(_curlHandle, CURLOPT_WRITEFUNCTION, fileWriteFunc);
    curl_easy_setopt(_curlHandle, CURLOPT_WRITEDATA, this);

    curl_easy_setopt(_curlHandle, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(_curlHandle, CURLOPT_PROGRESSFUNCTION, downloadProgressFunc);
    curl_easy_setopt(_curlHandle, CURLOPT_PROGRESSDATA, this);

    curl_easy_setopt(_curlHandle, CURLOPT_FAILONERROR, true);
    curl_easy_setopt(_curlHandle, CURLOPT_CONNECTTIMEOUT, DEFAULT_TIMEOUT);
    curl_easy_setopt(_curlHandle, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(_curlHandle, CURLOPT_LOW_SPEED_LIMIT, LOW_SPEED_LIMIT);
    curl_easy_setopt(_curlHandle, CURLOPT_LOW_SPEED_TIME, LOW_SPEED_TIME);

    _writterCallback = writterCallback;
    _progressCallback = progressCallback;
    _lastErrCode = curl_easy_perform(_curlHandle);
    return _lastErrCode;
}

int URLDownload::performBatchDownload(const DownloadUnits& units)
{
    return -1;
}

int URLDownload::getHeader(HeaderInfo* headerInfo)
{
    CC_ASSERT(_curlHandle && "not initialized");
    CC_ASSERT(headerInfo && "headerInfo must not be null");

    curl_easy_setopt(_curlHandle, CURLOPT_HEADER, 1);
    curl_easy_setopt(_curlHandle, CURLOPT_NOBODY, 1);
    curl_easy_setopt(_curlHandle, CURLOPT_NOSIGNAL, 1);
    if ((_lastErrCode=curl_easy_perform(_curlHandle)) == CURLE_OK)
    {
        char *effectiveUrl;
        char *contentType;
        curl_easy_getinfo(_curlHandle, CURLINFO_EFFECTIVE_URL, &effectiveUrl);
        curl_easy_getinfo(_curlHandle, CURLINFO_CONTENT_TYPE, &contentType);
        curl_easy_getinfo(_curlHandle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &headerInfo->contentSize);
        curl_easy_getinfo(_curlHandle, CURLINFO_RESPONSE_CODE, &headerInfo->responseCode);

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

bool URLDownload::checkOption(Options option)
{
    CC_ASSERT(_curlHandle && "not initialized");

    HeaderInfo headerInfo;
    // Make a resume request

    if (option == Options::RESUME) {
        curl_easy_setopt(_curlHandle, CURLOPT_RESUME_FROM_LARGE, 0);
        if (getHeader(&headerInfo) == 0 && headerInfo.valid)
        {
            return (headerInfo.responseCode == HTTP_CODE_SUPPORT_RESUME);
        }
    }
    return false;
}
