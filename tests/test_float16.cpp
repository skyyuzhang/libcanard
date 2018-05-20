/*
 * Copyright (c) 2016 UAVCAN Team
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Contributors: https://github.com/UAVCAN/libcanard/contributors
 */

#include <gtest/gtest.h>
#include <cmath>
#include "canard.h"


TEST(Float16, FromNative)
{
    // Reference values were generated manually with libuavcan and numpy.float16()
    ASSERT_EQ(0b0000000000000000, canardConvertNativeFloatToFloat16(0));
    ASSERT_EQ(0b0011110000000000, canardConvertNativeFloatToFloat16(1));
    ASSERT_EQ(0b1100000000000000, canardConvertNativeFloatToFloat16(-2));
    ASSERT_EQ(0b0111110000000000, canardConvertNativeFloatToFloat16(999999));   // +inf
    ASSERT_EQ(0b1111101111111111, canardConvertNativeFloatToFloat16(-65519));   // -max
    ASSERT_EQ(0b0111111111111111, canardConvertNativeFloatToFloat16(std::nanf("")));  // nan
}


TEST(Float16, ToNative)
{
    // Reference values were generated manually with libuavcan and numpy.float16()
    ASSERT_FLOAT_EQ(0,        canardConvertFloat16ToNativeFloat(0b0000000000000000));
    ASSERT_FLOAT_EQ(1,        canardConvertFloat16ToNativeFloat(0b0011110000000000));
    ASSERT_FLOAT_EQ(-2,       canardConvertFloat16ToNativeFloat(0b1100000000000000));
    ASSERT_FLOAT_EQ(INFINITY, canardConvertFloat16ToNativeFloat(0b0111110000000000));
    ASSERT_FLOAT_EQ(-65504,   canardConvertFloat16ToNativeFloat(0b1111101111111111));

    ASSERT_TRUE(bool(std::isnan(canardConvertFloat16ToNativeFloat(0b0111111111111111))));
}


TEST(Float16, BackAndForth)
{
    float x = -1000.0F;
    while (x <= 1000.0F)
    {
        ASSERT_FLOAT_EQ(x, canardConvertFloat16ToNativeFloat(canardConvertNativeFloatToFloat16(x)));
        x += 0.5F;
    }
}
