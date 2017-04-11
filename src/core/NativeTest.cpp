//////////////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//
//  Copyright (c) 2017-present, cyder.org
//  All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in the
//  Software without restriction, including without limitation the rights to use, copy,
//  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so, subject to the
//  following conditions:
//
//      The above copyright notice and this permission notice shall be included in all
//      copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//////////////////////////////////////////////////////////////////////////////////////

#include "NativeTest.h"
#include "Matrix.h"
#include "Rectangle.h"
#include "../utils/getTimer.h"
#include "iostream"


void runNative(const short* data, const int TIMES, const int SIZE) {

    auto rect = new Rectangle();
    auto matrix = new Matrix(2, 0, 0, 0.5, 11, 19);
    //Native测试
    auto start = getTimer();
    for (int t = 0; t < TIMES; t++) {
        int index = 0;
        for (int i = 0; i < SIZE; i++) {
            short x = data[index++];
            short y = data[index++];
            short width = data[index++];
            short height = data[index++];
            rect->setTo(x, y, width, height);
            matrix->transformBounds(rect);
        }
    }
    auto nativeTime = getTimer() - start;
    std::cout << "Native耗时:" << (int) nativeTime << "ms\n";

    //Native-NoField测试
    start = getTimer();
    for (int t = 0; t < TIMES; t++) {
        int index = 0;
        for (int i = 0; i < SIZE; i++) {
            short x = data[index++];
            short y = data[index++];
            short width = data[index++];
            short height = data[index++];
            Matrix::transformBoundsNoField(x, y, width, height);
        }
    }
    auto nativeNoPropTime = getTimer() - start;
    std::cout << "Native-NoField耗时:" << (int) nativeTime << "ms\n";
}

