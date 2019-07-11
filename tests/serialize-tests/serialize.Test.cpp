#include <gtest/gtest.h>

// core includes
#include <BigInteger.h>

using namespace std;
using namespace csBigInteger;

// from csBigInteger.js

//test('constructor csBigInteger() equals zero', () => {
//  expect(new csBigInteger().valueOf()).toBe(0);
//});

TEST(csBISerializeTests, ConstrutorEmpty_Equals_Zero)
{
   BigInteger big;
   EXPECT_EQ(big.toInt(), 0);
}

//test('constructor csBigInteger("123") equals 123', () => {
//  expect(new csBigInteger("123").valueOf()).toBe(123);
//});

TEST(csBISerializeTests, ConstrutorStr123_Equals_123)
{
   BigInteger big("123");
   EXPECT_EQ(big.toInt(), 123);
}

//test('constructor csBigInteger(123) equals 123', () => {
//  expect(new csBigInteger(123).valueOf()).toBe(123);
//});

TEST(csBISerializeTests, Construtor123_Equals_123)
{
   BigInteger big(123);
   EXPECT_EQ(big.toInt(), 123);
}

//test('constructor csBigInteger(127) equals 127', () => {
//  expect(new csBigInteger(127).valueOf()).toBe(127);
//});

TEST(csBISerializeTests, Construtor127_Equals_127)
{
   BigInteger big(127);
   EXPECT_EQ(big.toInt(), 127);
}

//test('constructor csBigInteger(128) equals 128', () => {
//  expect(new csBigInteger(128).valueOf()).toBe(128);
//});

TEST(csBISerializeTests, Construtor128_Equals_128)
{
   BigInteger big(128);
   EXPECT_EQ(big.toInt(), 128);
}

// ADVANCED THIS TEST. WILL REPEAT IT LATER (TODO: REMOVE)
//test('constructor csBigInteger(-1).toHexString() equals "ff"', () => {
//  expect(new csBigInteger(-1).toHexString()).toBe("ff");
//});
TEST(csBISerializeTests, ConstrutorM1_toHexString_ff)
{
   BigInteger big(-1);
   EXPECT_EQ(big.toHexStr(), "ff");
}

//test('constructor csBigInteger(-1) equals -1', () => {
//  expect(new csBigInteger(-1).valueOf()).toBe(-1);
//});

TEST(csBISerializeTests, ConstructorM1_Equals_M1)
{
   BigInteger big(-1);
   EXPECT_EQ(big.toInt(), -1);
}

//test('constructor csBigInteger(csBigInteger(10)) equals 10', () => {
//  var b = new csBigInteger(10);
//  expect(new csBigInteger(b).valueOf()).toBe(10);
//});

TEST(csBISerializeTests, Constructor10_Equals_10)
{
   BigInteger big(10);
   EXPECT_EQ(big.toInt(), 10);
}

//test('constructor csBigInteger([5]) equals 5', () => {
//  expect(new csBigInteger([5]).valueOf()).toBe(5);
//});

TEST(csBISerializeTests, Constructorv5_Equals_5)
{
   BigInteger big(vbyte(1, 0x05));
   EXPECT_EQ(big.toInt(), 5);
}

//test('constructor csBigInteger([127]) equals 127', () => {
//  expect(new csBigInteger([127]).valueOf()).toBe(127);
//});

TEST(csBISerializeTests, Constructorv127_Equals_127)
{
   BigInteger big(vbyte(1, 127));
   EXPECT_EQ(big.toInt(), 127);
}

//test('constructor csBigInteger([128]) equals -128', () => {
//  expect(new csBigInteger([128]).valueOf()).toBe(-128);
//});

TEST(csBISerializeTests, Constructorv128_Equals_M128)
{
   BigInteger big(vbyte(1, 128));
   EXPECT_EQ(big.toInt(), -128);
}

//test('constructor csBigInteger([251]) equals -5', () => {
//  expect(new csBigInteger([251]).valueOf()).toBe(-5);
//});

TEST(csBISerializeTests, Constructorv251_Equals_M5)
{
   BigInteger big(vbyte(1, 251));
   EXPECT_EQ(big.toInt(), -5);
}

//test('constructor csBigInteger("fb", 16) equals -5', () => {
//  expect(new csBigInteger("fb", 16).valueOf()).toBe(-5);
//});

TEST(csBISerializeTests, ConstructorSfb_Equals_M5)
{
   BigInteger big("fb", 16);
   EXPECT_EQ(big.toInt(), -5);
}

//test('constructor csBigInteger([251, 0]) equals 251', () => {
//  expect(new csBigInteger([251, 0]).valueOf()).toBe(251);
//});

TEST(csBISerializeTests, Constructorv251v0_Equals_251)
{
   vbyte v = { 251, 0 };
   BigInteger big(v);
   EXPECT_EQ(big.toInt(), 251);
}

//test('constructor csBigInteger("fb00", 16) equals 251', () => {
//  expect(new csBigInteger("fb00", 16).valueOf()).toBe(251);
//});

TEST(csBISerializeTests, ConstructorSfb00_Equals_251)
{
   BigInteger big("fb00", 16);
   EXPECT_EQ(big.toInt(), 251);
}

//test('constructor csBigInteger("251", 10) equals 251', () => {
//  expect(new csBigInteger("251", 10).valueOf()).toBe(251);
//});

TEST(csBISerializeTests, ConstructorS251_Equals_251)
{
   BigInteger big("251", 10);
   EXPECT_EQ(big.toInt(), 251);
}

//test('constructor csBigInteger("255", 10) equals 255', () => {
//  expect(new csBigInteger("255", 10).valueOf()).toBe(255);
//});

TEST(csBISerializeTests, ConstructorS255_Equals_255)
{
   BigInteger big("255", 10);
   EXPECT_EQ(big.toInt(), 255);
}

//test('constructor csBigInteger("256", 10) equals 256', () => {
//  expect(new csBigInteger("256", 10).valueOf()).toBe(256);
//});

TEST(csBISerializeTests, ConstructorS256_Equals_256)
{
   BigInteger big("256", 10);
   EXPECT_EQ(big.toInt(), 256);
}

//test('constructor csBigInteger("-256", 10) equals -256', () => {
//  expect(new csBigInteger("-256", 10).valueOf()).toBe(-256);
//});

TEST(csBISerializeTests, ConstructorSM256_Equals_M256)
{
   BigInteger big("-256", 10);
   EXPECT_EQ(big.toInt(), -256);
}

//test('constructor csBigInteger("1", 10) equals 1', () => {
//  expect(new csBigInteger("1", 10).valueOf()).toBe(1);
//});

TEST(csBISerializeTests, ConstructorS1_Equals_1)
{
   BigInteger big("1", 10);
   EXPECT_EQ(big.toInt(), 1);
}

//test('constructor csBigInteger("-1", 10) equals -1', () => {
//  expect(new csBigInteger("-1", 10).valueOf()).toBe(-1);
//});

TEST(csBISerializeTests, ConstructorSM1_Equals_M1)
{
   BigInteger big("-1", 10);
   EXPECT_EQ(big.toInt(), -1);
}

//test('constructor csBigInteger("0", 10) equals 0', () => {
//  expect(new csBigInteger("0", 10).valueOf()).toBe(0);
//});

TEST(csBISerializeTests, ConstructorS0_Equals_0)
{
   BigInteger big("0", 10);
   EXPECT_EQ(big.toInt(), 0);
}

//test('constructor csBigInteger("-0", 10) equals 0', () => {
//  expect(new csBigInteger("-0", 10).valueOf()).toBe(0);
//});

TEST(csBISerializeTests, ConstructorSM0_Equals_0)
{
   BigInteger big("-0", 10);
   EXPECT_EQ(big.toInt(), 0);
}

//test('constructor csBigInteger(5).toHexString() equals "05"', () => {
//  var b = new csBigInteger(5);
//  expect(b.toHexString()).toBe("05");
//});

TEST(csBISerializeTests, BigInteger5_toHexStr_S05)
{
   BigInteger big(5);
   EXPECT_EQ(big.toHexStr(), "05");
}

//test('constructor csBigInteger(1).toHexString() equals "01"', () => {
//  expect(new csBigInteger(1).toHexString()).toBe("01");
//});

TEST(csBISerializeTests, BigInteger1_toHexStr_S01)
{
   BigInteger big(1);
   EXPECT_EQ(big.toHexStr(), "01");
}

/*
//test('constructor csBigInteger([]).toHexString() equals "00"', () => {
//  expect(new csBigInteger([]).toHexString()).toBe("00");
//});

TEST(csBISerializeTests, BigIntegerEmptyByteArray_toHexStr_S00)
{
   BigInteger big(vbyte(0));
   EXPECT_EQ(big.toHexStr(), "00");
}
*/

/*
test('constructor csBigInteger(0).toHexString() equals "00"', () => {
  expect(new csBigInteger(0).toHexString()).toBe("00");
});

test('constructor csBigInteger(255).toHexString() equals "ff00"', () => {
  expect(new csBigInteger(255).toHexString()).toBe("ff00");
});

test('constructor csBigInteger(254).toHexString() equals "fe00"', () => {
  expect(new csBigInteger(254).toHexString()).toBe("fe00");
});

test('constructor csBigInteger(256).toHexString() equals "0001"', () => {
  expect(new csBigInteger(256).toHexString()).toBe("0001");
});

test('constructor csBigInteger(127).toHexString() equals "7f"', () => {
  expect(new csBigInteger(127).toHexString()).toBe("7f");
});

test('constructor csBigInteger(128).toHexString() equals "8000"', () => {
  expect(new csBigInteger(128).toHexString()).toBe("8000");
});

test('constructor csBigInteger(129).toHexString() equals "8100"', () => {
  expect(new csBigInteger(129).toHexString()).toBe("8100");
});

test('constructor csBigInteger(-1).toHexString() equals "ff"', () => {
  expect(new csBigInteger(-1).toHexString()).toBe("ff");
});

test('constructor csBigInteger(-2).toHexString() equals "fe"', () => {
  expect(new csBigInteger(-2).toHexString()).toBe("fe");
});

test('constructor csBigInteger(-80).toHexString() equals "b0"', () => {
  expect(new csBigInteger(-80).toHexString()).toBe("b0");
});

test('constructor csBigInteger(-80).toHexString() equals "b0"', () => {
  expect(new csBigInteger(-80).toHexString()).toBe("b0");
});

test('constructor csBigInteger(-127).toHexString() equals "81"', () => {
  expect(new csBigInteger(-127).toHexString()).toBe("81");
});

test('constructor csBigInteger(-128).toHexString() equals "80ff"', () => {
  expect(new csBigInteger(-128).toHexString()).toBe("80ff");
});

test('constructor csBigInteger(-129).toHexString() equals "7fff"', () => {
  expect(new csBigInteger(-129).toHexString()).toBe("7fff");
});

test('constructor csBigInteger(-254).toHexString() equals "02ff"', () => {
  expect(new csBigInteger(-254).toHexString()).toBe("02ff");
});

test('constructor csBigInteger(-255).toHexString() equals "01ff"', () => {
  expect(new csBigInteger(-255).toHexString()).toBe("01ff");
});

test('constructor csBigInteger(-256).toHexString() equals "00ff"', () => {
  expect(new csBigInteger(-256).toHexString()).toBe("00ff");
});

test('constructor csBigInteger(-257).toHexString() equals "fffe"', () => {
  expect(new csBigInteger(-257).toHexString()).toBe("fffe");
});

test('constructor csBigInteger(-258).toHexString() equals "fefe"', () => {
  expect(new csBigInteger(-258).toHexString()).toBe("fefe");
});

test('constructor csBigInteger(-259).toHexString() equals "fdfe"', () => {
  expect(new csBigInteger(-259).toHexString()).toBe("fdfe");
});

test('constructor csBigInteger(-1000000).toHexString() equals "c0bdf0"', () => {
  expect(new csBigInteger(-1000000).toHexString()).toBe("c0bdf0");
});

test('constructor csBigInteger(1000000).toHexString() equals "40420f"', () => {
  expect(new csBigInteger(1000000).toHexString()).toBe("40420f");
});

test('constructor csBigInteger(4293967296).toHexString() equals "c0bdf0ff00"', () => {
  expect(new csBigInteger(4293967296).toHexString()).toBe("c0bdf0ff00");
});

test('constructor csBigInteger(10).toHexString() equals [10]', () => {
  expect(new csBigInteger(10).toByteArray()).toEqual([10]);
});

test('constructor csBigInteger(-1).toHexString() equals [255]', () => {
  expect(new csBigInteger(-1).toByteArray()).toEqual([255]);
});

test('constructor csBigInteger(0).toHexString() equals [0]', () => {
  expect(new csBigInteger(0).toByteArray()).toEqual([0]);
});

test('csBigInteger(100000000).toHexString() equals "00e1f505"', () => {
  expect(new csBigInteger(100000000).toHexString()).toEqual("00e1f505");
});

test('test 255: csBigInteger(0.00000255*100000000).toHexString() equals "ff00"', () => {
  expect(new csBigInteger(0.00000255*100000000).toHexString()).toEqual("ff00");
});

// =================================================
//  checkNegativeBit

test('constructor csBigInteger.checkNegativeBit("ff") is true', () => {
  expect(csBigInteger.checkNegativeBit("ff")).toBe(true);
});

test('constructor csBigInteger.checkNegativeBit("7f") is false', () => {
  expect(csBigInteger.checkNegativeBit("7f")).toBe(false);
});

test('constructor csBigInteger.checkNegativeBit("80") is true', () => {
  expect(csBigInteger.checkNegativeBit("80")).toBe(true);
});

test('constructor csBigInteger.checkNegativeBit("800") is false', () => {
  expect(csBigInteger.checkNegativeBit("800")).toBe(false);
});

test('constructor csBigInteger.checkNegativeBit("8000") is false', () => {
  expect(csBigInteger.checkNegativeBit("8000")).toBe(false);
});

// =========================================
// toString()

test('constructor csBigInteger(5).toString(16) equals "0x05"', () => {
  var b = new csBigInteger(5);
  expect(b.toString(16)).toBe("0x05");
});

test('constructor csBigInteger(1).toString(16) equals "0x01"', () => {
  expect(new csBigInteger(1).toString(16)).toBe("0x01");
});

test('constructor csBigInteger([]).toString(16) equals "0x00"', () => {
  expect(new csBigInteger([]).toString(16)).toBe("0x00");
});

test('constructor csBigInteger(0).toString(16) equals "0x00"', () => {
  expect(new csBigInteger(0).toString(16)).toBe("0x00");
});

test('constructor csBigInteger(255).toString(16) equals "0x00ff"', () => {
  expect(new csBigInteger(255).toString(16)).toBe("0x00ff");
});

test('constructor csBigInteger(254).toString(16) equals "0x00fe"', () => {
  expect(new csBigInteger(254).toString(16)).toBe("0x00fe");
});

test('constructor csBigInteger(256).toString(16) equals "0x0100"', () => {
  expect(new csBigInteger(256).toString(16)).toBe("0x0100");
});

test('constructor csBigInteger(127).toString(16) equals "0x7f"', () => {
  expect(new csBigInteger(127).toString(16)).toBe("0x7f");
});

test('constructor csBigInteger(128).toString(16) equals "0x0080"', () => {
  expect(new csBigInteger(128).toString(16)).toBe("0x0080");
});

test('constructor csBigInteger(129).toString(16) equals "0x0081"', () => {
  expect(new csBigInteger(129).toString(16)).toBe("0x0081");
});

test('constructor csBigInteger(-1).toString(16) equals "0xff"', () => {
  expect(new csBigInteger(-1).toString(16)).toBe("0xff");
});

test('constructor csBigInteger(-2).toString(16) equals "0xfe"', () => {
  expect(new csBigInteger(-2).toString(16)).toBe("0xfe");
});

test('constructor csBigInteger(-80).toString(16) equals "0xb0"', () => {
  expect(new csBigInteger(-80).toString(16)).toBe("0xb0");
});

test('constructor csBigInteger(-80).toString(16) equals "0xb0"', () => {
  expect(new csBigInteger(-80).toString(16)).toBe("0xb0");
});

test('constructor csBigInteger(-127).toString(16) equals "0x81"', () => {
  expect(new csBigInteger(-127).toString(16)).toBe("0x81");
});

test('constructor csBigInteger(-128).toString(16) equals "0xff80"', () => {
  expect(new csBigInteger(-128).toString(16)).toBe("0xff80");
});

test('constructor csBigInteger(-129).toString(16) equals "0xff7f"', () => {
  expect(new csBigInteger(-129).toString(16)).toBe("0xff7f");
});

test('constructor csBigInteger(-254).toString(16) equals "0xff02"', () => {
  expect(new csBigInteger(-254).toString(16)).toBe("0xff02");
});

test('constructor csBigInteger(-255).toString(16) equals "0xff01"', () => {
  expect(new csBigInteger(-255).toString(16)).toBe("0xff01");
});

test('constructor csBigInteger(-256).toString(16) equals "0xff00"', () => {
  expect(new csBigInteger(-256).toString(16)).toBe("0xff00");
});

test('constructor csBigInteger(-257).toString(16) equals "0xfeff"', () => {
  expect(new csBigInteger(-257).toString(16)).toBe("0xfeff");
});

test('constructor csBigInteger(-258).toString(16) equals "0xfefe"', () => {
  expect(new csBigInteger(-258).toString(16)).toBe("0xfefe");
});

test('constructor csBigInteger(-259).toString(16) equals "0xfefd"', () => {
  expect(new csBigInteger(-259).toString(16)).toBe("0xfefd");
});

test('constructor csBigInteger(-1000000).toString(16) equals "0xf0bdc0"', () => {
  expect(new csBigInteger(-1000000).toString(16)).toBe("0xf0bdc0");
});

test('constructor csBigInteger(1000000).toString(16) equals "0x0f4240"', () => {
  expect(new csBigInteger(1000000).toString(16)).toBe("0x0f4240");
});

// ================================================================
//                  comparing with Python
// ================================================================
// We will need two zeros after, to avoid mixing with negative

// >>> int.from_bytes(bytes.fromhex("C0BDF0FF"),byteorder='little')
// 4293967296
// >>> int.from_bytes(bytes.fromhex("C0BDF0FF00"),byteorder='little')
// 4293967296
test('constructor csBigInteger(4293967296).toHexString() equals "c0bdf0ff00"', () => {
  expect(new csBigInteger(4293967296).toHexString()).toBe("c0bdf0ff00");
});

//>>> int.from_bytes(bytes.fromhex("C0BDF0"),byteorder='little')
// 15777216
//>>> int.from_bytes(bytes.fromhex("C0BDF000"),byteorder='little')
// 15777216
test('constructor csBigInteger(15777216).toHexString() equals "c0bdf000"', () => {
  expect(new csBigInteger(15777216).toHexString()).toBe("c0bdf000");
});

test('constructor csBigInteger(-1000000).toHexString() equals "c0bdf0"', () => {
  expect(new csBigInteger(-1000000).toHexString()).toBe("c0bdf0");
});

// Python needs to specify precision on twos-complement
//>>> hex(-1000000 & (2**32-1)) # 32-bit
//'0xfff0bdc0'
//>>> hex(-1000000 & (2**64-1)) # 64-bit
//'0xfffffffffff0bdc0'

test('constructor csBigInteger("c0bdf0ff",16).valueOf() equals -1000000', () => {
  expect(new csBigInteger("c0bdf0ff",16).valueOf()).toBe(-1000000);
});

// c0bdf0ffffffffff will not work currently, because precision is not 64-bit (around ~60 bit)
// So, testing will be done (for now), up to 6-bytes!

test('constructor csBigInteger("c0bdf0ffffff",16).valueOf() equals -1000000', () => {
  expect(new csBigInteger("c0bdf0ffffff",16).valueOf()).toBe(-1000000);
});

// ====================================================================
//   big-endian input with "0x"

test('constructor csBigInteger("00", 16) equals 0', () => {
  expect(new csBigInteger("00", 16).valueOf()).toBe(0);
});

test('constructor csBigInteger("0x00", 16) equals 0', () => {
  expect(new csBigInteger("0x00", 16).valueOf()).toBe(0);
});

test('constructor csBigInteger("01", 16) equals 1', () => {
  expect(new csBigInteger("01", 16).valueOf()).toBe(1);
});

test('constructor csBigInteger("0x01", 16) equals 1', () => {
  expect(new csBigInteger("0x01", 16).valueOf()).toBe(1);
});

test('constructor csBigInteger("fb", 16) equals -5', () => {
  expect(new csBigInteger("fb", 16).valueOf()).toBe(-5);
});

test('constructor csBigInteger("0xfb", 16) equals -5', () => {
  expect(new csBigInteger("0xfb", 16).valueOf()).toBe(-5);
});

test('constructor csBigInteger("fb00", 16) equals 251', () => {
  expect(new csBigInteger("fb00", 16).valueOf()).toBe(251);
});

test('constructor csBigInteger("0x00fb", 16) equals 251', () => {
  expect(new csBigInteger("0x00fb", 16).valueOf()).toBe(251);
});

// =============== testing javascript number limits (more than 53 bits) =======

test('csBigInteger(9007199254740991) equals 9007199254740991 (number is safe for JavaScript)', () => {
  expect(new csBigInteger(9007199254740991).valueOf()).toBe(9007199254740991);
});

test('csBigInteger(9007199254740992) to throw exception (number is unsafe for JavaScript)', () => {
  expect( function(){ new csBigInteger(9007199254740992).valueOf() }).toThrow(new Error("csBigInteger assertion failed: unsafe number"));
});

test('csBigInteger(-9007199254740991) equals -9007199254740991 (number is safe for JavaScript)', () => {
  expect(new csBigInteger(-9007199254740991).valueOf()).toBe(-9007199254740991);
});

test('csBigInteger(-9007199254740992) to throw exception (number is unsafe for JavaScript)', () => {
  expect( function(){ new csBigInteger(-9007199254740992).valueOf() }).toThrow(new Error("csBigInteger assertion failed: unsafe number"));
});

// ============= testing binary (basic tests) =================

test('csBigInteger(10).toString(2) equals 1010', () => {
  expect(new csBigInteger(10).toString(2)).toBe("1010");
});

// =============== testing internal BN library ===================

test('csBigInteger(BN(100)) equals 100', () => {
  expect(new csBigInteger(new BN(100)).asBN().toNumber()).toBe(100);
});

// ========================= snowy big test ======================

test('csBigInteger(big).ToHexString equals hexbig.length == 129', () => {
  expect(new csBigInteger('17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847\
732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208\
5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215', 10).toHexString().length/2).
toBe(129);
});

test('csBigInteger(big).ToHexString equals hexbig', () => {
  expect(new csBigInteger('17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847\
732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208\
5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215', 10).toHexString()).
toBe('fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\
ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\
fffffffffffffffffffffff00');
});

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

test('csBigInteger(big).sub(1).ToHexString equals hexbig', () => {
  expect(new csBigInteger(new csBigInteger('17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847\
732240753602112011387987139335765878976881441662249284743063947412437776789342486548527630221960124609411945308295208\
5005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215', 10).asBN().sub(new BN(1))).toHexString()).
toBe('fefffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\
ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\
fffffffffffffffffffffff00');
});

*/
