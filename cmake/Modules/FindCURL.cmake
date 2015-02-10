#.rst:
# FindCURL
# --------
#
# Find curl
#
# Find the native CURL headers and libraries.
#
# ::
#
#   CURL_INCLUDE_DIRS   - where to find curl/curl.h, etc.
#   CURL_LIBRARIES      - List of libraries when using curl.
#   CURL_FOUND          - True if curl found.
#   CURL_VERSION_STRING - the version of curl found (since CMake 2.8.8)

#=============================================================================
# Copyright 2006-2009 Kitware, Inc.
# Copyright 2012 Rolf Eike Beer <eike@sf-mail.de>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

find_path(CURL_INCLUDE_DIR curl.h
    HINTS
    ENV CURL_DIR
    PATH_SUFFIXES include/curl include
    )

set(CURL_NAMES ${CURL_NAMES} curl)
find_library(CURL_LIBRARY
    NAMES ${CURL_NAMES}
    HINTS
    ENV CURL_DIR
    PATH_SUFFIXES lib
    )

# handle the QUIETLY and REQUIRED arguments and set CURL_FOUND to TRUE if
# all listed variables are TRUE
include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CURL DEFAULT_MSG CURL_LIBRARY CURL_INCLUDE_DIR)

if(CURL_FOUND)
  set(CURL_INCLUDE_DIRS ${CURL_INCLUDE_DIR})
  set(CURL_LIBRARIES ${CURL_LIBRARY})
endif()

mark_as_advanced(CURL_LIBRARY CURL_INCLUDE_DIRS )
