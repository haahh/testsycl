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

include_directories(../include)

if(DEFINED ${BOOST_COMPONENTS})
  set(BOOST_COMPONENTS ${BOOST_COMPONENTS} unit_test_framework)
else(DEFINED ${BOOST_COMPONENTS})
  set(BOOST_COMPONENTS unit_test_framework)
endif(DEFINED ${BOOST_COMPONENTS})

if(${TSYCL_USE_CPP14})
  add_definitions(-DTSYCL_USE_CPP14)
endif()

find_package(Boost 1.48 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
add_definitions(-DBOOST_TEST_DYN_LINK)

function(add_sycl_test TEST_NAME TEST_SOURCE)
  get_filename_component(TEST_TARGET ${TEST_SOURCE} NAME_WE)
  add_executable(${TEST_TARGET} ${TEST_SOURCE})
  target_link_libraries(${TEST_TARGET}
    ${Boost_LIBRARIES}
  )
  
  add_test(${TEST_NAME} ${TEST_TARGET})
endfunction()

add_sycl_test(test_basic_sycl test_basic_sycl.cpp)