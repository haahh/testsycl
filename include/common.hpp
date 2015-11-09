//---------------------------------------------------------------------------//
// The MIT License (MIT)
//
// Copyright (c) 2015 Jakub Szuppe
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------//

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <exception>
#include <string>
#include <vector>
#include <random>
#include <type_traits>

namespace common
{

inline void print_exception(const std::exception& e)
{
    std::cerr << "Exception: " << e.what() << std::endl;
    try {
        std::rethrow_if_nested(e);
    } catch (const std::exception& e) {
        print_exception(e);
    } catch (...) {

    }
}

inline std::string get_file_content(const std::string filename)
{
    std::ifstream in;
    in.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try {
        in.open(filename.c_str(), std::ios::in | std::ios::binary);
        if(in.is_open()) {
            in.exceptions(std::ifstream::badbit);
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return contents;
        }
        else {
            throw std::logic_error("Error occurred while opening file: " + filename);
        }
    } catch (...) {
        throw std::logic_error("Error occurred while opening file: " + filename);
    }
}

template <typename T,
          typename = std::enable_if<std::is_integral<T>::value>>
inline std::vector<T> generate_random_vector(size_t size)
{
    // set random generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dis(0, size);

    // fill host vector with random ints
    std::vector<T> random(size) ;
    std::generate(random.begin(), random.end(), [&]{ return dis(gen); });

    return random;
}

}

#endif /* COMMON_HPP_ */
