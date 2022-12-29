#include <catch2/catch_amalgamated.hpp>

// core includes
#include <csbiginteger/Helper.hpp>

using namespace std;
using namespace csbiginteger;

TEST_CASE("csBigIntegerHelperTests:  RevertHexString8000_0080")
{
   REQUIRE(Helper::revertHexString("8000") == "0080");
}

TEST_CASE("csBigIntegerHelperTests:  HexToBytes0001")
{
   cs_vbyte vb = Helper::HexToBytes("0001");
   REQUIRE(vb[0] == 0x00);
   REQUIRE(vb[1] == 0x01);
}

// =================================================
//  checkNegativeBit

//test('constructor csBigInteger.checkNegativeBit("ff") is true', () => {
//  expect(csBigInteger.checkNegativeBit("ff")).toBe(true);
//});

TEST_CASE("csBigIntegerHelperTests:  BigInteger_checkNegativeBit_Sff_is_true")
{
   REQUIRE(Helper::checkNegativeBit("ff"));
}

//test('constructor csBigInteger.checkNegativeBit("7f") is false', () => {
//  expect(csBigInteger.checkNegativeBit("7f")).toBe(false);
//});

TEST_CASE("csBigIntegerHelperTests:  BigInteger_checkNegativeBit_S7f_is_false")
{
   REQUIRE(!Helper::checkNegativeBit("7f"));
}

//test('constructor csBigInteger.checkNegativeBit("80") is true', () => {
//  expect(csBigInteger.checkNegativeBit("80")).toBe(true);
//});

TEST_CASE("csBigIntegerHelperTests:  BigInteger_checkNegativeBit_S80_is_true")
{
   REQUIRE(Helper::checkNegativeBit("80"));
}

//test('constructor csBigInteger.checkNegativeBit("800") is false', () => {
//  expect(csBigInteger.checkNegativeBit("800")).toBe(false);
//});

TEST_CASE("csBigIntegerHelperTests:  BigInteger_checkNegativeBit_S800_is_false")
{
   REQUIRE(!Helper::checkNegativeBit("800"));
}

//test('constructor csBigInteger.checkNegativeBit("8000") is false', () => {
//  expect(csBigInteger.checkNegativeBit("8000")).toBe(false);
//});

TEST_CASE("csBigIntegerHelperTests:  BigInteger_checkNegativeBit_S8000_is_false")
{
   REQUIRE(!Helper::checkNegativeBit("8000"));
}

TEST_CASE("csBigIntegerHelperTests:  BigInteger_revert_hex_0")
{
   REQUIRE(Helper::revertHexString("0") == "00");
}
