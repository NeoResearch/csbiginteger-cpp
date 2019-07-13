#include <gtest/gtest.h>

// core includes
#include <Helper.hpp>

using namespace std;
using namespace csbiginteger;

TEST(csBigIntegerHelperTests, RevertHexString8000_0080)
{
   EXPECT_EQ(Helper::revertHexString("8000"), "0080");
}

TEST(csBigIntegerHelperTests, HexToBytes0001)
{
   vbyte vb = Helper::HexToBytes("0001");
   EXPECT_EQ(vb[0], 0x00);
   EXPECT_EQ(vb[1], 0x01);
}

// =================================================
//  checkNegativeBit

//test('constructor csBigInteger.checkNegativeBit("ff") is true', () => {
//  expect(csBigInteger.checkNegativeBit("ff")).toBe(true);
//});

TEST(csBigIntegerHelperTests, BigInteger_checkNegativeBit_Sff_is_true)
{
   EXPECT_EQ(Helper::checkNegativeBit("ff"), true);
}

//test('constructor csBigInteger.checkNegativeBit("7f") is false', () => {
//  expect(csBigInteger.checkNegativeBit("7f")).toBe(false);
//});

TEST(csBigIntegerHelperTests, BigInteger_checkNegativeBit_S7f_is_false)
{
   EXPECT_EQ(Helper::checkNegativeBit("7f"), false);
}

//test('constructor csBigInteger.checkNegativeBit("80") is true', () => {
//  expect(csBigInteger.checkNegativeBit("80")).toBe(true);
//});

TEST(csBigIntegerHelperTests, BigInteger_checkNegativeBit_S80_is_true)
{
   EXPECT_EQ(Helper::checkNegativeBit("80"), true);
}

//test('constructor csBigInteger.checkNegativeBit("800") is false', () => {
//  expect(csBigInteger.checkNegativeBit("800")).toBe(false);
//});

TEST(csBigIntegerHelperTests, BigInteger_checkNegativeBit_S800_is_false)
{
   EXPECT_EQ(Helper::checkNegativeBit("800"), false);
}

//test('constructor csBigInteger.checkNegativeBit("8000") is false', () => {
//  expect(csBigInteger.checkNegativeBit("8000")).toBe(false);
//});

TEST(csBigIntegerHelperTests, BigInteger_checkNegativeBit_S8000_is_false)
{
   EXPECT_EQ(Helper::checkNegativeBit("8000"), false);
}

TEST(csBigIntegerHelperTests, BigInteger_revert_hex_0)
{
   EXPECT_EQ(Helper::revertHexString("0"), "00");
}
