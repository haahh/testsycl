# ---------------------------------------------------------------------------
# The MIT License (MIT)
#
# Copyright (c) 2015 Jakub Szuppe
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# ---------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.1)

# Project name
project(TestSYCL)

# list of required boost components
#set(BOOST_COMPONENTS)

# find Boost
#find_package(Boost 1.48 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
#include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

# TriSYCL
find_path(SYCL_INCLUDE_DIRS SYCL NO_DEFAULT_PATH)
include_directories(SYSTEM ${SYCL_INCLUDE_DIRS})

# so pedantic!
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Werror -Wno-variadic-macros -Wno-long-long -Wno-shadow")

# support for c++14 required
option(TSYCL_USE_CPP14 "Use C++14 features" ON)
if(NOT MSVC)
  if(${TSYCL_USE_CPP14})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  endif()
endif()

option(TSYCL_BUILD_TESTS "Build tests" ON)
if(${TSYCL_BUILD_TESTS})
  enable_testing()
  add_subdirectory(test)
endif()

# only for clion, so it finds all headers
FILE (GLOB_RECURSE clion_all_headers ${CMAKE_SOURCE_DIR}/*.hpp)
ADD_CUSTOM_TARGET(all_clion
        SOURCES ${clion_all_headers}
)

add_executable (main main.cpp)
target_include_directories (main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})