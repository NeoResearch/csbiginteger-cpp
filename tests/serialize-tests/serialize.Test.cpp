#include <catch2/catch.hpp>

// system
#include <limits>

// core includes
#include <BigInteger.h>

using namespace std;
using namespace csbiginteger;

// basics

// =======================
// memory management tests
// =======================

TEST_CASE("csBIMemoryTests:  BigInteger_Length_zero_is_one")
{
   BigInteger big;
   REQUIRE(big.Length() == 1);
}

TEST_CASE("csBIMemoryTests:  BigInteger_CopyTo_Good_0x010203")
{
   byte b[4];
   b[0] = 0;
   b[1] = 0;
   b[2] = 0;
   b[3] = 0;
   vbyte vb = { 0x01, 0x02, 0x03 };
   BigInteger big(vb);
   REQUIRE(big.Length() == 3);
   REQUIRE(big.CopyTo(b, 4));
   REQUIRE(b[0] == 0x01);
   REQUIRE(b[1] == 0x02);
   REQUIRE(b[2] == 0x03);
   REQUIRE(b[3] == 0x00);
}

TEST_CASE("csBIMemoryTests:  BigInteger_CopyTo_Bad")
{
   byte b[1];
   b[0] = 0;
   vbyte vb = { 0x01, 0x02, 0x03 };
   BigInteger big(vb);
   REQUIRE(big.Length() == 3);
   REQUIRE(big.CopyTo(b, 1) == false);
}

// ===========================

// from csBigInteger.js

//test('constructor csBigInteger() equals zero', () => {
//  expect(new csBigInteger().valueOf()).toBe(0);
//});

TEST_CASE("csBISerializeTests:  ConstrutorEmpty_Equals_Zero")
{
   BigInteger big;
   REQUIRE(big.toInt() ==  0);
}

//test('constructor csBigInteger("123") equals 123', () => {
//  expect(new csBigInteger("123").valueOf()).toBe(123);
//});

TEST_CASE("csBISerializeTests:  ConstrutorStr123_Equals_123")
{
   BigInteger big("123");
   REQUIRE(big.toInt() ==  123);
}

//test('constructor csBigInteger(123) equals 123', () => {
//  expect(new csBigInteger(123).valueOf()).toBe(123);
//});

TEST_CASE("csBISerializeTests:  Construtor123_Equals_123")
{
   BigInteger big(123);
   REQUIRE(big.toInt() ==  123);
}

//test('constructor csBigInteger(127) equals 127', () => {
//  expect(new csBigInteger(127).valueOf()).toBe(127);
//});

TEST_CASE("csBISerializeTests:  Construtor127_Equals_127")
{
   BigInteger big(127);
   REQUIRE(big.toInt() ==  127);
}

//test('constructor csBigInteger(128) equals 128', () => {
//  expect(new csBigInteger(128).valueOf()).toBe(128);
//});

TEST_CASE("csBISerializeTests:  Construtor128_Equals_128")
{
   BigInteger big(128);
   REQUIRE(big.toInt() ==  128);
}

// ADVANCED THIS TEST. WILL REPEAT IT LATER (TODO: REMOVE)
//test('constructor csBigInteger(-1).toHexString() equals "ff"', () => {
//  expect(new csBigInteger(-1).toHexString()).toBe("ff");
//});
TEST_CASE("csBISerializeTests:  ConstrutorM1_toHexString_ff")
{
   BigInteger big(-1);
   REQUIRE(big.toHexStr() ==  "ff");
}

//test('constructor csBigInteger(-1) equals -1', () => {
//  expect(new csBigInteger(-1).valueOf()).toBe(-1);
//});

TEST_CASE("csBISerializeTests:  ConstructorM1_Equals_M1")
{
   BigInteger big(-1);
   REQUIRE(big.toInt() ==  -1);
}

//test('constructor csBigInteger(csBigInteger(10)) equals 10', () => {
//  var b = new csBigInteger(10);
//  expect(new csBigInteger(b).valueOf()).toBe(10);
//});

TEST_CASE("csBISerializeTests:  Constructor10_Equals_10")
{
   BigInteger big(10);
   REQUIRE(big.toInt() ==  10);
}

//test('constructor csBigInteger([5]) equals 5', () => {
//  expect(new csBigInteger([5]).valueOf()).toBe(5);
//});

TEST_CASE("csBISerializeTests:  Constructorv5_Equals_5")
{
   BigInteger big(vbyte(1, 0x05));
   REQUIRE(big.toInt() ==  5);
}

//test('constructor csBigInteger([127]) equals 127', () => {
//  expect(new csBigInteger([127]).valueOf()).toBe(127);
//});

TEST_CASE("csBISerializeTests:  Constructorv127_Equals_127")
{
   BigInteger big(vbyte(1, 127));
   REQUIRE(big.toInt() ==  127);
}

//test('constructor csBigInteger([128]) equals -128', () => {
//  expect(new csBigInteger([128]).valueOf()).toBe(-128);
//});

TEST_CASE("csBISerializeTests:  Constructorv128_Equals_M128")
{
   BigInteger big(vbyte(1, 128));
   REQUIRE(big.toInt() ==  -128);
}

//test('constructor csBigInteger([251]) equals -5', () => {
//  expect(new csBigInteger([251]).valueOf()).toBe(-5);
//});

TEST_CASE("csBISerializeTests:  Constructorv251_Equals_M5")
{
   BigInteger big(vbyte(1, 251));
   REQUIRE(big.toInt() ==  -5);
}

//test('constructor csBigInteger("fb", 16) equals -5', () => {
//  expect(new csBigInteger("fb", 16).valueOf()).toBe(-5);
//});

TEST_CASE("csBISerializeTests:  ConstructorSfb_Equals_M5")
{
   BigInteger big("fb", 16);
   REQUIRE(big.toInt() ==  -5);
}

TEST_CASE("csBISerializeTests:  ConstructorS0xfb_Equals_M5")
{
   BigInteger big("0xfb", 16);
   REQUIRE(big.toInt() ==  -5);
}

//test('constructor csBigInteger([251, 0]) equals 251', () => {
//  expect(new csBigInteger([251, 0]).valueOf()).toBe(251);
//});

TEST_CASE("csBISerializeTests:  Constructorv251v0_Equals_251")
{
   vbyte v = { 251, 0 };
   BigInteger big(v);
   REQUIRE(big.toInt() ==  251);
}

//test('constructor csBigInteger("fb00", 16) equals 251', () => {
//  expect(new csBigInteger("fb00", 16).valueOf()).toBe(251);
//});

TEST_CASE("csBISerializeTests:  ConstructorS00fb_Equals_251")
{
   BigInteger big("00fb", 16);
   REQUIRE(big.toInt() ==  251);
}

TEST_CASE("csBISerializeTests:  ConstructorS0x00fb_Equals_251")
{
   BigInteger big("0x00fb", 16);
   REQUIRE(big.toInt() ==  251);
}

//test('constructor csBigInteger("251", 10) equals 251', () => {
//  expect(new csBigInteger("251", 10).valueOf()).toBe(251);
//});

TEST_CASE("csBISerializeTests:  ConstructorS251_Equals_251")
{
   BigInteger big("251", 10);
   REQUIRE(big.toInt() ==  251);
}

//test('constructor csBigInteger("255", 10) equals 255', () => {
//  expect(new csBigInteger("255", 10).valueOf()).toBe(255);
//});

TEST_CASE("csBISerializeTests:  ConstructorS255_Equals_255")
{
   BigInteger big("255", 10);
   REQUIRE(big.toInt() ==  255);
}

//test('constructor csBigInteger("256", 10) equals 256', () => {
//  expect(new csBigInteger("256", 10).valueOf()).toBe(256);
//});

TEST_CASE("csBISerializeTests:  ConstructorS256_Equals_256")
{
   BigInteger big("256", 10);
   REQUIRE(big.toInt() ==  256);
}

//test('constructor csBigInteger("-256", 10) equals -256', () => {
//  expect(new csBigInteger("-256", 10).valueOf()).toBe(-256);
//});

TEST_CASE("csBISerializeTests:  ConstructorSM256_Equals_M256")
{
   BigInteger big("-256", 10);
   REQUIRE(big.toInt() ==  -256);
}

//test('constructor csBigInteger("1", 10) equals 1', () => {
//  expect(new csBigInteger("1", 10).valueOf()).toBe(1);
//});

TEST_CASE("csBISerializeTests:  ConstructorS1_Equals_1")
{
   BigInteger big("1", 10);
   REQUIRE(big.toInt() ==  1);
}

//test('constructor csBigInteger("-1", 10) equals -1', () => {
//  expect(new csBigInteger("-1", 10).valueOf()).toBe(-1);
//});

TEST_CASE("csBISerializeTests:  ConstructorSM1_Equals_M1")
{
   BigInteger big("-1", 10);
   REQUIRE(big.toInt() ==  -1);
}

//test('constructor csBigInteger("0", 10) equals 0', () => {
//  expect(new csBigInteger("0", 10).valueOf()).toBe(0);
//});

TEST_CASE("csBISerializeTests:  ConstructorS0_Equals_0")
{
   BigInteger big("0", 10);
   REQUIRE(big.toInt() ==  0);
}

//test('constructor csBigInteger("-0", 10) equals 0', () => {
//  expect(new csBigInteger("-0", 10).valueOf()).toBe(0);
//});

TEST_CASE("csBISerializeTests:  ConstructorSM0_Equals_0")
{
   BigInteger big("-0", 10);
   REQUIRE(big.toInt() ==  0);
}

//test('constructor csBigInteger(5).toHexString() equals "05"', () => {
//  var b = new csBigInteger(5);
//  expect(b.toHexString()).toBe("05");
//});

TEST_CASE("csBISerializeTests:  BigInteger5_toHexStr_S05")
{
   BigInteger big(5);
   REQUIRE(big.toHexStr() ==  "05");
}

//test('constructor csBigInteger(1).toHexString() equals "01"', () => {
//  expect(new csBigInteger(1).toHexString()).toBe("01");
//});

TEST_CASE("csBISerializeTests:  BigInteger1_toHexStr_S01")
{
   BigInteger big(1);
   REQUIRE(big.toHexStr() ==  "01");
}

//test('constructor csBigInteger([]).toHexString() equals "00"', () => {
//  expect(new csBigInteger([]).toHexString()).toBe("00");
//});

// empty bytearray initialization is not considered error (but is zero as default)
TEST_CASE("csBISerializeTests:  BigIntegerEmptyByteArray_toHexStr_S00")
{
   BigInteger big(vbyte(0));
   REQUIRE(big != BigInteger::Error);
   REQUIRE(big.toHexStr() ==  "00");
}

//test('constructor csBigInteger(0).toHexString() equals "00"', () => {
//  expect(new csBigInteger(0).toHexString()).toBe("00");
//});

TEST_CASE("csBISerializeTests:  BigInteger0_toHexStr_S00")
{
   BigInteger big(0);
   REQUIRE(big.toHexStr() ==  "00");
}

//test('constructor csBigInteger(255).toHexString() equals "ff00"', () => {
//  expect(new csBigInteger(255).toHexString()).toBe("ff00");
//});

TEST_CASE("csBISerializeTests:  BigInteger255_toHexStr_Sff00")
{
   BigInteger big(255);
   REQUIRE(big.toHexStr() ==  "ff00");
}

//test('constructor csBigInteger(254).toHexString() equals "fe00"', () => {
//  expect(new csBigInteger(254).toHexString()).toBe("fe00");
//});

TEST_CASE("csBISerializeTests:  BigInteger254_toHexStr_Sfe00")
{
   BigInteger big(254);
   REQUIRE(big.toHexStr() ==  "fe00");
}

//test('constructor csBigInteger(256).toHexString() equals "0001"', () => {
//  expect(new csBigInteger(256).toHexString()).toBe("0001");
//});

TEST_CASE("csBISerializeTests:  BigInteger256_toHexStr_S0001")
{
   BigInteger big(256);
   REQUIRE(big.toHexStr() ==  "0001");
}

//test('constructor csBigInteger(127).toHexString() equals "7f"', () => {
//  expect(new csBigInteger(127).toHexString()).toBe("7f");
//});

TEST_CASE("csBISerializeTests:  BigInteger127_toHexStr_S7f")
{
   BigInteger big(127);
   REQUIRE(big.toHexStr() ==  "7f");
}

//test('constructor csBigInteger(128).toHexString() equals "8000"', () => {
//  expect(new csBigInteger(128).toHexString()).toBe("8000");
//});

TEST_CASE("csBISerializeTests:  BigInteger128_toHexStr_S8000")
{
   BigInteger big(128);
   REQUIRE(big.toHexStr() ==  "8000");
}

//test('constructor csBigInteger(129).toHexString() equals "8100"', () => {
//  expect(new csBigInteger(129).toHexString()).toBe("8100");
//});

TEST_CASE("csBISerializeTests:  BigInteger129_toHexStr_S8100")
{
   BigInteger big(129);
   REQUIRE(big.toHexStr() ==  "8100");
}

//test('constructor csBigInteger(-1).toHexString() equals "ff"', () => {
//  expect(new csBigInteger(-1).toHexString()).toBe("ff");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM1_toHexStr_Sff")
{
   BigInteger big(-1);
   REQUIRE(big.toHexStr() ==  "ff");
}

//test('constructor csBigInteger(-2).toHexString() equals "fe"', () => {
//  expect(new csBigInteger(-2).toHexString()).toBe("fe");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM2_toHexStr_Sfe")
{
   BigInteger big(-2);
   REQUIRE(big.toHexStr() ==  "fe");
}

//test('constructor csBigInteger(-80).toHexString() equals "b0"', () => {
//  expect(new csBigInteger(-80).toHexString()).toBe("b0");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM80_toHexStr_Sb0")
{
   BigInteger big(-80);
   REQUIRE(big.toHexStr() ==  "b0");
}

//test('constructor csBigInteger(-127).toHexString() equals "81"', () => {
//  expect(new csBigInteger(-127).toHexString()).toBe("81");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM127_toHexStr_S81")
{
   BigInteger big(-127);
   REQUIRE(big.toHexStr() ==  "81");
}

//test('constructor csBigInteger(-128).toHexString() equals "80ff"', () => {
//  expect(new csBigInteger(-128).toHexString()).toBe("80ff");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM128_toHexStr_S80")
{
   BigInteger big(-128);
   REQUIRE(big.toHexStr() ==  "80");
}

//test('constructor csBigInteger(-129).toHexString() equals "7fff"', () => {
//  expect(new csBigInteger(-129).toHexString()).toBe("7fff");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM129_toHexStr_S7fff")
{
   BigInteger big(-129);
   REQUIRE(big.toHexStr() ==  "7fff");
}

//test('constructor csBigInteger(-254).toHexString() equals "02ff"', () => {
//  expect(new csBigInteger(-254).toHexString()).toBe("02ff");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM254_toHexStr_S02ff")
{
   BigInteger big(-254);
   REQUIRE(big.toHexStr() ==  "02ff");
}

//test('constructor csBigInteger(-255).toHexString() equals "01ff"', () => {
//  expect(new csBigInteger(-255).toHexString()).toBe("01ff");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM255_toHexStr_S01ff")
{
   BigInteger big(-255);
   REQUIRE(big.toHexStr() ==  "01ff");
}

//test('constructor csBigInteger(-256).toHexString() equals "00ff"', () => {
//  expect(new csBigInteger(-256).toHexString()).toBe("00ff");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM256_toHexStr_S00ff")
{
   BigInteger big(-256);
   REQUIRE(big.toHexStr() ==  "00ff");
}

//test('constructor csBigInteger(-257).toHexString() equals "fffe"', () => {
//  expect(new csBigInteger(-257).toHexString()).toBe("fffe");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM257_toHexStr_Sfffe")
{
   BigInteger big(-257);
   REQUIRE(big.toHexStr() ==  "fffe");
}

//test('constructor csBigInteger(-258).toHexString() equals "fefe"', () => {
//  expect(new csBigInteger(-258).toHexString()).toBe("fefe");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM258_toHexStr_Sfefe")
{
   BigInteger big(-258);
   REQUIRE(big.toHexStr() ==  "fefe");
}

//test('constructor csBigInteger(-259).toHexString() equals "fdfe"', () => {
//  expect(new csBigInteger(-259).toHexString()).toBe("fdfe");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM259_toHexStr_Sfdfe")
{
   BigInteger big(-259);
   REQUIRE(big.toHexStr() ==  "fdfe");
}

//test('constructor csBigInteger(-1000000).toHexString() equals "c0bdf0"', () => {
//  expect(new csBigInteger(-1000000).toHexString()).toBe("c0bdf0");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM1000000_toHexStr_Sc0bdf0")
{
   BigInteger big(-1000000);
   REQUIRE(big.toHexStr() ==  "c0bdf0");
}

//test('constructor csBigInteger(1000000).toHexString() equals "40420f"', () => {
//  expect(new csBigInteger(1000000).toHexString()).toBe("40420f");
//});

TEST_CASE("csBISerializeTests:  BigInteger1000000_toHexStr_S40420f")
{
   BigInteger big(1000000);
   REQUIRE(big.toHexStr() ==  "40420f");
}

//test('constructor csBigInteger(4293967296).toHexString() equals "c0bdf0ff00"', () => {
//  expect(new csBigInteger(4293967296).toHexString()).toBe("c0bdf0ff00");
//});

TEST_CASE("csBISerializeTests:  BigInteger4293967296_toHexStr_Sc0bdf0ff00")
{
   BigInteger big(4293967296);
   REQUIRE(big.toHexStr() ==  "c0bdf0ff00");
}

//test('constructor csBigInteger(10).toHexString() equals [10]', () => {
//  expect(new csBigInteger(10).toByteArray()).toEqual([10]);
//});

TEST_CASE("csBISerializeTests:  BigInteger10_ToByteArray_v10")
{
   BigInteger big(10);
   REQUIRE(big.ToByteArray() == vbyte(1, 10));
}

//test('constructor csBigInteger(-1).toHexString() equals [255]', () => {
//  expect(new csBigInteger(-1).toByteArray()).toEqual([255]);
//});

TEST_CASE("csBISerializeTests:  BigIntegerM1_ToByteArray_v255")
{
   BigInteger big(-1);
   REQUIRE(big.ToByteArray() == vbyte(1, 255));
}

//test('constructor csBigInteger(0).toHexString() equals [0]', () => {
//  expect(new csBigInteger(0).toByteArray()).toEqual([0]);
//});

TEST_CASE("csBISerializeTests:  BigInteger0_ToByteArray_v0")
{
   BigInteger big(0);
   REQUIRE(big.ToByteArray() == vbyte(1, 0));
}

//test('csBigInteger(100000000).toHexString() equals "00e1f505"', () => {
//  expect(new csBigInteger(100000000).toHexString()).toEqual("00e1f505");
//});

TEST_CASE("csBISerializeTests:  BigInteger100000000_toHexStr_S00e1f505")
{
   BigInteger big(100000000);
   REQUIRE(big.toHexStr() ==  "00e1f505");
}

//test('test 255: csBigInteger(0.00000255*100000000).toHexString() equals "ff00"', () => {
//  expect(new csBigInteger(0.00000255*100000000).toHexString()).toEqual("ff00");
//});

TEST_CASE("csBISerializeTests:  BigInteger0p00000255MUL100000000_toHexStr_Sff00")
{
   BigInteger big((int64)(0.00000255 * 100000000));
   REQUIRE(big.toHexStr() ==  "ff00");
}

// =========================================
// toString()

//test('constructor csBigInteger(5).toString(16) equals "0x05"', () => {
//  var b = new csBigInteger(5);
//  expect(b.toString(16)).toBe("0x05");
//});

TEST_CASE("csBISerializeTests:  BigInteger5_ToString_S0x05")
{
   BigInteger big(5);
   REQUIRE(big.ToString() ==  "0x05");
}

//test('constructor csBigInteger(1).toString(16) equals "0x01"', () => {
//  expect(new csBigInteger(1).toString(16)).toBe("0x01");
//});

TEST_CASE("csBISerializeTests:  BigInteger1_ToString_S0x01")
{
   BigInteger big(1);
   REQUIRE(big.ToString() ==  "0x01");
}

//test('constructor csBigInteger([]).toString(16) equals "0x00"', () => {
//  expect(new csBigInteger([]).toString(16)).toBe("0x00");
//});

// empty byte array is not considered error here (default is zero value)
TEST_CASE("csBISerializeTests:  BigIntegerEmptyByteArray_ToString_S0x00")
{
   BigInteger big(vbyte(0));
   REQUIRE(big != BigInteger::Error);
   REQUIRE(big.ToString() ==  "0x00");
}

//test('constructor csBigInteger(0).toString(16) equals "0x00"', () => {
//  expect(new csBigInteger(0).toString(16)).toBe("0x00");
//});

TEST_CASE("csBISerializeTests:  BigInteger0_ToString_S0x00")
{
   BigInteger big(0);
   REQUIRE(big.ToString() ==  "0x00");
}

//test('constructor csBigInteger(255).toString(16) equals "0x00ff"', () => {
//  expect(new csBigInteger(255).toString(16)).toBe("0x00ff");
//});

TEST_CASE("csBISerializeTests:  BigInteger255_ToString_S0x00ff")
{
   BigInteger big(255);
   REQUIRE(big.ToString() ==  "0x00ff");
}

//test('constructor csBigInteger(254).toString(16) equals "0x00fe"', () => {
//  expect(new csBigInteger(254).toString(16)).toBe("0x00fe");
//});

TEST_CASE("csBISerializeTests:  BigInteger254_ToString_S0x00fe")
{
   BigInteger big(254);
   REQUIRE(big.ToString() ==  "0x00fe");
}

//test('constructor csBigInteger(256).toString(16) equals "0x0100"', () => {
//  expect(new csBigInteger(256).toString(16)).toBe("0x0100");
//});

TEST_CASE("csBISerializeTests:  BigInteger256_ToString_S0x0100")
{
   BigInteger big(256);
   REQUIRE(big.ToString() ==  "0x0100");
}

//test('constructor csBigInteger(127).toString(16) equals "0x7f"', () => {
//  expect(new csBigInteger(127).toString(16)).toBe("0x7f");
//});

TEST_CASE("csBISerializeTests:  BigInteger127_ToString_S0x7f")
{
   BigInteger big(127);
   REQUIRE(big.ToString() ==  "0x7f");
}

//test('constructor csBigInteger(128).toString(16) equals "0x0080"', () => {
//  expect(new csBigInteger(128).toString(16)).toBe("0x0080");
//});

TEST_CASE("csBISerializeTests:  BigInteger128_ToString_S0x0080")
{
   BigInteger big(128);
   REQUIRE(big.ToString() ==  "0x0080");
}

//test('constructor csBigInteger(129).toString(16) equals "0x0081"', () => {
//  expect(new csBigInteger(129).toString(16)).toBe("0x0081");
//});

TEST_CASE("csBISerializeTests:  BigInteger129_ToString_S0x0081")
{
   BigInteger big(129);
   REQUIRE(big.ToString() ==  "0x0081");
}

//test('constructor csBigInteger(-1).toString(16) equals "0xff"', () => {
//  expect(new csBigInteger(-1).toString(16)).toBe("0xff");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM1_ToString_S0xff")
{
   BigInteger big(-1);
   REQUIRE(big.ToString() ==  "0xff");
}

//test('constructor csBigInteger(-2).toString(16) equals "0xfe"', () => {
//  expect(new csBigInteger(-2).toString(16)).toBe("0xfe");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM2_ToString_S0xfe")
{
   BigInteger big(-2);
   REQUIRE(big.ToString() ==  "0xfe");
}

//test('constructor csBigInteger(-80).toString(16) equals "0xb0"', () => {
//  expect(new csBigInteger(-80).toString(16)).toBe("0xb0");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM80_ToString_S0xb0")
{
   BigInteger big(-80);
   REQUIRE(big.ToString() ==  "0xb0");
}

//test('constructor csBigInteger(-127).toString(16) equals "0x81"', () => {
//  expect(new csBigInteger(-127).toString(16)).toBe("0x81");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM127_ToString_S0x81")
{
   BigInteger big(-127);
   REQUIRE(big.ToString() ==  "0x81");
}

//test('constructor csBigInteger(-128).toString(16) equals "0xff80"', () => {
//  expect(new csBigInteger(-128).toString(16)).toBe("0xff80");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM128_ToString_S0x80")
{
   BigInteger big(-128);
   REQUIRE(big.ToString() ==  "0x80");
}

//test('constructor csBigInteger(-129).toString(16) equals "0xff7f"', () => {
//  expect(new csBigInteger(-129).toString(16)).toBe("0xff7f");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM129_ToString_S0xff7f")
{
   BigInteger big(-129);
   REQUIRE(big.ToString() ==  "0xff7f");
}

//test('constructor csBigInteger(-254).toString(16) equals "0xff02"', () => {
//  expect(new csBigInteger(-254).toString(16)).toBe("0xff02");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM254_ToString_S0xff02")
{
   BigInteger big(-254);
   REQUIRE(big.ToString() ==  "0xff02");
}

//test('constructor csBigInteger(-255).toString(16) equals "0xff01"', () => {
//  expect(new csBigInteger(-255).toString(16)).toBe("0xff01");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM255_ToString_S0xff01")
{
   BigInteger big(-255);
   REQUIRE(big.ToString() ==  "0xff01");
}

//test('constructor csBigInteger(-256).toString(16) equals "0xff00"', () => {
//  expect(new csBigInteger(-256).toString(16)).toBe("0xff00");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM256_ToString_S0xff00")
{
   BigInteger big(-256);
   REQUIRE(big.ToString() ==  "0xff00");
}

//test('constructor csBigInteger(-257).toString(16) equals "0xfeff"', () => {
//  expect(new csBigInteger(-257).toString(16)).toBe("0xfeff");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM257_ToString_S0xfeff")
{
   BigInteger big(-257);
   REQUIRE(big.ToString() ==  "0xfeff");
}

//test('constructor csBigInteger(-258).toString(16) equals "0xfefe"', () => {
//  expect(new csBigInteger(-258).toString(16)).toBe("0xfefe");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM258_ToString_S0xfefe")
{
   BigInteger big(-258);
   REQUIRE(big.ToString() ==  "0xfefe");
}

//test('constructor csBigInteger(-259).toString(16) equals "0xfefd"', () => {
//  expect(new csBigInteger(-259).toString(16)).toBe("0xfefd");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM259_ToString_S0xfefd")
{
   BigInteger big(-259);
   REQUIRE(big.ToString() ==  "0xfefd");
}

//test('constructor csBigInteger(-1000000).toString(16) equals "0xf0bdc0"', () => {
//  expect(new csBigInteger(-1000000).toString(16)).toBe("0xf0bdc0");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM1000000_ToString_S0xf0bdc0")
{
   BigInteger big(-1000000);
   REQUIRE(big.ToString() ==  "0xf0bdc0");
}

//test('constructor csBigInteger(1000000).toString(16) equals "0x0f4240"', () => {
//  expect(new csBigInteger(1000000).toString(16)).toBe("0x0f4240");
//});

TEST_CASE("csBISerializeTests:  BigInteger1000000_ToString_S0x0f4240")
{
   BigInteger big(1000000);
   REQUIRE(big.ToString() ==  "0x0f4240");
}

// BASE 10 test!

TEST_CASE("csBISerializeTests:  BigIntegerM1_ToString10_SM1")
{
   BigInteger big(-1);
   REQUIRE(big.ToString(10) == "-1");
}

TEST_CASE("csBISerializeTests:  BigIntegerError_ToString_S0x")
{
   REQUIRE(BigInteger::Error.ToString() == "0x");
}

// ================================================================
//                  comparing with Python
// ================================================================
// We will need two zeros after, to avoid mixing with negative

// >>> int.from_bytes(bytes.fromhex("C0BDF0FF"),byteorder='little')
// 4293967296
// >>> int.from_bytes(bytes.fromhex("C0BDF0FF00"),byteorder='little')
// 4293967296

//test('constructor csBigInteger(4293967296).toHexString() equals "c0bdf0ff00"', () => {
//  expect(new csBigInteger(4293967296).toHexString()).toBe("c0bdf0ff00");
//});

TEST_CASE("csBISerializeTests:  BigInteger4293967296_toHexStr_Sc0bdf0ff00_Py")
{
   BigInteger big(4293967296);
   REQUIRE(big.toHexStr() ==  "c0bdf0ff00");
}

//>>> int.from_bytes(bytes.fromhex("C0BDF0"),byteorder='little')
// 15777216
//>>> int.from_bytes(bytes.fromhex("C0BDF000"),byteorder='little')
// 15777216

//test('constructor csBigInteger(15777216).toHexString() equals "c0bdf000"', () => {
//  expect(new csBigInteger(15777216).toHexString()).toBe("c0bdf000");
//});

TEST_CASE("csBISerializeTests:  BigInteger15777216_toHexStr_Sc0bdf000_Py")
{
   BigInteger big(15777216);
   REQUIRE(big.toHexStr() ==  "c0bdf000");
}

//test('constructor csBigInteger(-1000000).toHexString() equals "c0bdf0"', () => {
//  expect(new csBigInteger(-1000000).toHexString()).toBe("c0bdf0");
//});

TEST_CASE("csBISerializeTests:  BigIntegerM1000000_toHexStr_Sc0bdf0_Py")
{
   BigInteger big(-1000000);
   // toHexStr() is little-endian (helper function, remove later)
   REQUIRE(big.toHexStr() ==  "c0bdf0");
   // ToString() is big-endian
   REQUIRE(big.ToString() ==  "0xf0bdc0");
}

TEST_CASE("csBISerializeTests:  BigIntegerS0xf0bdc0_16_toInt_M1000000_Py")
{
   BigInteger big("0xf0bdc0", 16);
   REQUIRE(big.toInt() ==  -1000000);
}

// Python needs to specify precision on twos-complement
//>>> hex(-1000000 & (2**32-1)) # 32-bit
//'0xfff0bdc0'
//>>> hex(-1000000 & (2**64-1)) # 64-bit
//'0xfffffffffff0bdc0'

//test('constructor csBigInteger("c0bdf0ff",16).valueOf() equals -1000000', () => {
//  expect(new csBigInteger("c0bdf0ff",16).valueOf()).toBe(-1000000);
//});

TEST_CASE("csBISerializeTests:  BigIntegerS0xfff0bdc0_16_toInt_M1000000_Py")
{
   BigInteger big("0xfff0bdc0", 16);
   REQUIRE(big.toInt() ==  -1000000);
}

// from javascript:
// c0bdf0ffffffffff will not work currently, because precision is not 64-bit (around ~60 bit)
// So, testing will be done (for now), up to 6-bytes!

//test('constructor csBigInteger("c0bdf0ffffff",16).valueOf() equals -1000000', () => {
//  expect(new csBigInteger("c0bdf0ffffff",16).valueOf()).toBe(-1000000);
//});

TEST_CASE("csBISerializeTests:  BigIntegerSc0bdf0ffffff_16_toInt_M1000000_Py")
{
   BigInteger big("0xfffffff0bdc0", 16); // big-endian input
   REQUIRE(big.toHexStr() ==  "c0bdf0");  // little-endian (Helper)
   REQUIRE(big.toInt() ==  -1000000);
}

// ====================================================================
//   big-endian input with "0x"

//test('constructor csBigInteger("00", 16) equals 0', () => {
//  expect(new csBigInteger("00", 16).valueOf()).toBe(0);
//});

TEST_CASE("csBISerializeTests:  BigIntegerS00_16_toInt_0")
{
   BigInteger big("00", 16);
   REQUIRE(big.toInt() ==  0);
}

//test('constructor csBigInteger("0x00", 16) equals 0', () => {
//  expect(new csBigInteger("0x00", 16).valueOf()).toBe(0);
//});

TEST_CASE("csBISerializeTests:  BigIntegerS0x00_16_toInt_0")
{
   BigInteger big("0x00", 16);
   REQUIRE(big.toInt() ==  0);
}

//test('constructor csBigInteger("01", 16) equals 1', () => {
//  expect(new csBigInteger("01", 16).valueOf()).toBe(1);
//});

TEST_CASE("csBISerializeTests:  BigIntegerS01_16_toInt_1")
{
   BigInteger big("01", 16);
   REQUIRE(big.toInt() ==  1);
}

//test('constructor csBigInteger("0x01", 16) equals 1', () => {
//  expect(new csBigInteger("0x01", 16).valueOf()).toBe(1);
//});

TEST_CASE("csBISerializeTests:  BigIntegerS0x01_16_toInt_1")
{
   BigInteger big("0x01", 16);
   REQUIRE(big.toInt() ==  1);
}

//test('constructor csBigInteger("fb", 16) equals -5', () => {
//  expect(new csBigInteger("fb", 16).valueOf()).toBe(-5);
//});

TEST_CASE("csBISerializeTests:  BigIntegerSfb_16_toInt_M5")
{
   BigInteger big("fb", 16);
   REQUIRE(big.toInt() ==  -5);
}

//test('constructor csBigInteger("0xfb", 16) equals -5', () => {
//  expect(new csBigInteger("0xfb", 16).valueOf()).toBe(-5);
//});

TEST_CASE("csBISerializeTests:  BigIntegerS0xfb_16_toInt_M5")
{
   BigInteger big("0xfb", 16);
   REQUIRE(big.toInt() ==  -5);
}

//test('constructor csBigInteger("fb00", 16) equals 251', () => {
//  expect(new csBigInteger("fb00", 16).valueOf()).toBe(251);
//});

TEST_CASE("csBISerializeTests:  BigIntegerS00fb_16_toInt_251")
{
   // input is big-endian (always)
   BigInteger big("00fb", 16);
   REQUIRE(big.toInt() ==  251);
}

//test('constructor csBigInteger("0x00fb", 16) equals 251', () => {
//  expect(new csBigInteger("0x00fb", 16).valueOf()).toBe(251);
//});

TEST_CASE("csBISerializeTests:  BigIntegerS0x00fb_16_toInt_251")
{
   BigInteger big("0x00fb", 16);
   REQUIRE(big.toInt() ==  251);
}

// =============== testing javascript number limits (more than 53 bits) =======

//test('csBigInteger(9007199254740991) equals 9007199254740991 (number is safe for JavaScript)', () => {
//  expect(new csBigInteger(9007199254740991).valueOf()).toBe(9007199254740991);
//});

TEST_CASE("csBISerializeTests:  BigInteger9007199254740991_toLong")
{
   BigInteger big(9007199254740991L);
   REQUIRE(big.toLong() ==  9007199254740991);
}

//test('csBigInteger(9007199254740992) to throw exception (number is unsafe for JavaScript)', () => {
//  expect( function(){ new csBigInteger(9007199254740992).valueOf() }).toThrow(new Error("csBigInteger assertion failed: unsafe number"));
//});
// this test passes on c++

TEST_CASE("csBISerializeTests:  BigInteger9007199254740992_toLong")
{
   BigInteger big(9007199254740992L);
   REQUIRE(big.toLong() ==  9007199254740992);
}

//test('csBigInteger(-9007199254740991) equals -9007199254740991 (number is safe for JavaScript)', () => {
//  expect(new csBigInteger(-9007199254740991).valueOf()).toBe(-9007199254740991);
//});

TEST_CASE("csBISerializeTests:  BigIntegerM9007199254740991_toLong")
{
   BigInteger big(-9007199254740991L);
   REQUIRE(big.toLong() ==  -9007199254740991);
}

//test('csBigInteger(-9007199254740992) to throw exception (number is unsafe for JavaScript)', () => {
//  expect( function(){ new csBigInteger(-9007199254740992).valueOf() }).toThrow(new Error("csBigInteger assertion failed: unsafe number"));
//});
// this test passes on c++

TEST_CASE("csBISerializeTests:  BigIntegerM9007199254740992_toLong")
{
   BigInteger big(-9007199254740992L);
   REQUIRE(big.toLong() ==  -9007199254740992);
}

// ============= testing binary (basic tests) =================

//test('csBigInteger(10).toString(2) equals 1010', () => {
//  expect(new csBigInteger(10).toString(2)).toBe("1010");
//});

TEST_CASE("csBISerializeTests:  BigInteger10_ToString_2_1010")
{
   BigInteger big(10);
   REQUIRE(big.ToString(2) == "1010");
}

// =============== testing internal BN library ===================

// NO INTERFACE WITH NATIVE BIGNUM IS PROVIDED ON C++ PORTABLE

//test('csBigInteger(BN(100)) equals 100', () => {
//  expect(new csBigInteger(new BN(100)).asBN().toNumber()).toBe(100);
//});

// ========================= snowy big test ======================

//test('csBigInteger(big).ToHexString equals hexbig.length == 129', () => {
//  expect(new csBigInteger('17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847\
732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208\
5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215', 10).toHexString().length/2).
//toBe(129);
//});

TEST_CASE("csBISerializeTests:  BigInteger_big_toHexStr_length_129_bytes")
{
   BigInteger big("17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847"
                  "732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208"
                  "5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215",
                  10);
   REQUIRE(big.toHexStr().length() / 2 == 129);
}

//test('csBigInteger(big).ToHexString equals hexbig', () => {
//  expect(new csBigInteger('17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847\
732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208\
5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215', 10).toHexString()).
//toBe('fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\
ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\
fffffffffffffffffffffff00');
//});

TEST_CASE("csBISerializeTests:  BigInteger_big_toHexStr_equals_hex")
{
   BigInteger big("17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847"
                  "732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208"
                  "5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215",
                  10);
   REQUIRE(big.toHexStr() ==  "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                             "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                             "fffffffffffffffffffffff00");
}

// WILL NOT TEST INTERNAL BIGNUM ON C++ PORTABLE
/*
// =========================== testing asBN() and BN library =======================

test('csBigInteger(big).asBN()', () => {
  expect(new csBigInteger('17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847\
732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208\
5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215', 10).asBN()).
toEqual(new BN('17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847\
732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208\
5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215', 10));
});

test('csBigInteger(big).asBN().sub(1)', () => {
  expect(new csBigInteger('17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847\
732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208\
5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215', 10).asBN().sub(new BN(1))).
toEqual(new BN('17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847\
732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208\
5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137214', 10));
});
*/

//test('csBigInteger(big).sub(1).ToHexString equals hexbig', () => {
//  expect(new csBigInteger(new csBigInteger('17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847\
732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208\
5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215', 10).asBN().sub(new BN(1))).toHexString()).
//toBe('fefffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\
ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\
fffffffffffffffffffffff00');
//});

TEST_CASE("csBISerializeTests:  BigInteger_big_minus_1_equals_hex")
{
   BigInteger big("17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847"
                  "732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208"
                  "5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215",
                  10);
   BigInteger big1(1);
   BigInteger bigFinal = big - big1;

   REQUIRE(bigFinal.toHexStr() == "fefffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                                  "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
                                  "fffffffffffffffffffffff00");
}

// ==================== special ================

TEST_CASE("csBISerializeTests:  BigInteger_0_padding_hex")
{
   BigInteger big("0", 16);
   REQUIRE(big.toHexStr() ==  "00");
}

TEST_CASE("csBISerializeTests:  BigInteger_Special1")
{
   BigInteger big(128);
   REQUIRE(big.toHexStr() ==  "8000");
}

TEST_CASE("csBISerializeTests:  BigInteger_Special2")
{
   BigInteger big("-48335248028225339427907476932896373492484053930");
   REQUIRE(big.toHexStr().length() / 2 == 20);
}

TEST_CASE("csBISerializeTests:  BigInteger_Special3")
{
   BigInteger big("-399990000");
   REQUIRE(big.toHexStr() ==  "10a328e8");
}

//negative left shift should be positive right shift
TEST_CASE("csBISerializeTests:  BigInteger_Special4")
{
   REQUIRE(BigInteger(8) << BigInteger(-3) == 1);
}

//negative right shift should be positive left shift
TEST_CASE("csBISerializeTests:  BigInteger_Special5")
{
   REQUIRE(BigInteger(8) >> BigInteger(-3) == 64);
}

// limits (2^31-1): max int positive
TEST_CASE("csBISerializeTests:  BigInteger_Limit2147483647")
{
   BigInteger big0;
   BigInteger big1(2147483647);
   REQUIRE(big1.ToString(10) == "2147483647");
   REQUIRE(big1.ToString(16) == "0x7fffffff");
   REQUIRE(big0 < big1);
   REQUIRE(!(big0 > big1));
   REQUIRE(!(big1 < big0));
   REQUIRE(big1 > big0);
   // variants
   REQUIRE(big0 < (big1 - 1));
   REQUIRE(big0 < (big1 - 2));
   REQUIRE(big0 < (big1 + 0));
   REQUIRE(big0 < (big1 + 1));
   REQUIRE(big0 < (big1 + 2));
}

TEST_CASE("csBISerializeTests:  BigInteger_StrangeM61968")
{
   BigInteger big(-61968);
   REQUIRE(big.toInt() ==  -61968);
}

TEST_CASE("csBISerializeTests:  BigInteger_StrangeM16773648")
{
   BigInteger big(-16773648);
   REQUIRE(big.toInt() ==  -16773648);
   REQUIRE(big.ToString() ==  "0xff000df0");
}