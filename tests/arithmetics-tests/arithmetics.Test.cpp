#include <catch2/catch.hpp>

// system
#include <limits>

// core includes
#include <BigInteger.h>

using namespace std;
using namespace csbiginteger;

TEST_CASE("csBIArithmeticsTests:  ZeroNotError")
{
   BigInteger big0(0);
   REQUIRE(big0 != BigInteger::Error);
}

TEST_CASE("csBIArithmeticsTests:  OnePlusOneEqualsTwo")
{
   REQUIRE(BigInteger::One + BigInteger::One == BigInteger(2));
}

TEST_CASE("csBIArithmeticsTests:  OneTimesZeroEqualsZero")
{
   REQUIRE(BigInteger::One * BigInteger::Zero == BigInteger::Zero);
}

TEST_CASE("csBIArithmeticsTests:  OneTimesMinusOneEqualsMinusOne")
{
   REQUIRE(BigInteger::One * BigInteger::MinusOne == BigInteger::MinusOne);
}

TEST_CASE("csBIArithmeticsTests:  OnePlusMinusOneEqualsZero")
{
   REQUIRE(BigInteger::One + BigInteger::MinusOne == BigInteger::Zero);
}

TEST_CASE("csBIArithmeticsTests:  TenDivTwoEqualsFive")
{
   REQUIRE(BigInteger(10) / BigInteger(2) == BigInteger(5));
}

TEST_CASE("csBIArithmeticsTests:  TenModTwoEqualsZero")
{
   REQUIRE(BigInteger(10) % BigInteger(2) == BigInteger(0));
}

TEST_CASE("csBIArithmeticsTests:  TenDivThreeEqualsThree")
{
   REQUIRE(BigInteger(10) / BigInteger(3) == BigInteger(3));
}

TEST_CASE("csBIArithmeticsTests:  TenModThreeEqualsOne")
{
   REQUIRE(BigInteger(10) % BigInteger(3) == BigInteger(1));
}

TEST_CASE("csBIArithmeticsTests:  TenDivZeroEqualsError")
{
   REQUIRE(BigInteger(10) / BigInteger(0) == BigInteger::Error);
}

TEST_CASE("csBIArithmeticsTests:  _255DivOneEquals255")
{
   REQUIRE(BigInteger(255) / BigInteger(1) == BigInteger(255));
}

TEST_CASE("csBIArithmeticsTests:  _255DivMinusOneEqualsM255")
{
   REQUIRE(BigInteger(255) / BigInteger(-1) == BigInteger(-255));
}


TEST_CASE("csBIArithmeticsTests:  OnePlusErrorEqualsError")
{
   REQUIRE(BigInteger(1) + BigInteger::Error == BigInteger::Error);
}

// operator- unary

TEST_CASE("csBIArithmeticsTests:  Minus10IsMinus10")
{
   REQUIRE(-BigInteger(10) == BigInteger(-10));
}

// SHL SHR

TEST_CASE("csBIArithmeticsTests:  EightSHLIsSixteen")
{
   REQUIRE(BigInteger(8) << 1 == BigInteger(16));
}

TEST_CASE("csBIArithmeticsTests:  EightSHRIsFour")
{
   REQUIRE(BigInteger(8) >> 1 == BigInteger(4));
}

TEST_CASE("csBIArithmeticsTests:  EightMinusSHLIsFour")
{
   REQUIRE(BigInteger(8) << -1 == BigInteger(4));
}

TEST_CASE("csBIArithmeticsTests:  EightMinusSHRIsSixteen")
{
   REQUIRE(BigInteger(8) >> -1 == BigInteger(16));
}

TEST_CASE("csBIArithmeticsTests:  TenSHRZeroIsTen")
{
   REQUIRE(BigInteger(10) >> 0 == BigInteger(10));
}

TEST_CASE("csBIArithmeticsTests:  TenSHLZeroIsTen")
{
   REQUIRE(BigInteger(10) << 0 == BigInteger(10));
}

// ---------- error
TEST_CASE("csBIArithmeticsTests:  ZeroAddErrorIsError")
{
   REQUIRE(BigInteger(0) + BigInteger::Error == BigInteger::Error);
}

TEST_CASE("csBIArithmeticsTests:  ZeroMinusErrorIsError")
{
   REQUIRE(BigInteger(0) - BigInteger::Error == BigInteger::Error);
}

TEST_CASE("csBIArithmeticsTests:  ZeroMulErrorIsError")
{
   REQUIRE(BigInteger(0) * BigInteger::Error == BigInteger::Error);
}

TEST_CASE("csBIArithmeticsTests:  ZeroDivErrorIsError")
{
   REQUIRE(BigInteger(0) / BigInteger::Error == BigInteger::Error);
}

TEST_CASE("csBIArithmeticsTests:  ZeroModErrorIsError")
{
   REQUIRE(BigInteger(0) % BigInteger::Error == BigInteger::Error);
}

TEST_CASE("csBIArithmeticsTests:  ZeroSHLErrorIsError")
{
   REQUIRE(BigInteger(0) << BigInteger::Error == BigInteger::Error);
}

TEST_CASE("csBIArithmeticsTests:  ZeroSHRErrorIsError")
{
   REQUIRE(BigInteger(0) >> BigInteger::Error == BigInteger::Error);
}

// ========= compare

TEST_CASE("csBIArithmeticsTests:  ZeroLessThanOne")
{
   cout << "will compare 0 and 1" << endl;
   BigInteger big0(0);
   BigInteger big1(1);
   REQUIRE(big0.operator<(big1));
}

TEST_CASE("csBIArithmeticsTests:  OneGreaterThanZero")
{
   REQUIRE(BigInteger(1) > BigInteger(0));
}

TEST_CASE("csBIArithmeticsTests:  NotZeroGreaterThanOne")
{
   REQUIRE(!(BigInteger(0) > BigInteger(1)));
}

TEST_CASE("csBIArithmeticsTests:  ZeroLeqOne")
{
   REQUIRE(BigInteger(0) <= BigInteger(1));
}

TEST_CASE("csBIArithmeticsTests:  NotZeroGeqOne")
{
   REQUIRE(!(BigInteger(0) >= BigInteger(1)));
}

TEST_CASE("csBIArithmeticsTests:  ZeroLessThanErrorIsFalse")
{
   REQUIRE(!(BigInteger(0) < BigInteger::Error));
}

TEST_CASE("csBIArithmeticsTests:  ZeroGreaterThanErrorIsFalse")
{
   REQUIRE(!(BigInteger(0) > BigInteger::Error));
}

// ============ special

TEST_CASE("csBIArithmeticsTests:  SpecialDiv")
{
   cout << "oi" << endl;
   BigInteger b1 = BigInteger("41483775933600000000");
   //EXPECT_EQ(b1.ToString(10), "41483775933600000000");
   //EXPECT_EQ(b1.ToString(16), "0x023fb3fa6bd0206800");
   BigInteger b2 = BigInteger("414937759336");
   //EXPECT_EQ(b2.ToString(10), "414937759336");
   //EXPECT_EQ(b2.ToString(16), "0x609c37be68");
   BigInteger b3 = b1 / b2;
   REQUIRE(b3.ToString(10) == "99975899");
   //EXPECT_EQ(b1 / b2, BigInteger("99975899"));
}

TEST_CASE("csBIArithmeticsTests:  SpecialDiv2")
{
   BigInteger b1 = BigInteger("-11001000000");
   BigInteger b2 = BigInteger(86400);
   REQUIRE(b1 / b2 == BigInteger(-127326));
}

TEST_CASE("csBIArithmeticsTests:  SpecialMod")
{
   BigInteger b1 = BigInteger("20195283520469175757");
   BigInteger b2 = BigInteger("1048576");
   REQUIRE(b1 % b2 == BigInteger("888269"));
}

// 860593 % -201 is 112
TEST_CASE("csBIArithmeticsTests:  SpecialModNeg")
{
   REQUIRE(BigInteger(860593) % BigInteger(-201) == BigInteger(112));
}

TEST_CASE("csBIArithmeticsTests:  SpecialModNeg2")
{
   REQUIRE(BigInteger("-18224909727634776050312394179610579601844989529623334093909233530432892596607") % BigInteger("14954691977398614017") == BigInteger("-3100049211437790421"));
}

// ======================= Pow =======================

TEST_CASE("csBIArithmeticsTests:  Pow3_2_9")
{
   REQUIRE(BigInteger::Pow(BigInteger(3), 2) == BigInteger(9));
}

TEST_CASE("csBIArithmeticsTests:  Pow3_0_9")
{
   REQUIRE(BigInteger::Pow(BigInteger(3), 0) == BigInteger::One);
}

TEST_CASE("csBIArithmeticsTests:  Pow3_0_Negative_Error")
{
   REQUIRE(BigInteger::Pow(BigInteger(3), -2) == BigInteger::Error);
}

// ======================= Online tests =======================

// from: https://docs.microsoft.com/en-us/dotnet/api/system.numerics.biginteger.divide?view=netframework-4.8

TEST_CASE("csBIArithmeticsTests:  Online_Pack_Divisor")
{
   BigInteger big64max(std::numeric_limits<long>::max());
   REQUIRE(big64max.ToString(10) == "9223372036854775807");
   BigInteger divisor = BigInteger::Pow(big64max, 2);
   REQUIRE(divisor.ToString(10) == "85070591730234615847396907784232501249");
   //Divisor:  85,070,591,730,234,615,847,396,907,784,232,501,249

   BigInteger dividends[] = { BigInteger::Multiply(BigInteger(std::numeric_limits<float>::max()), 2),
                              BigInteger("90612345123875509091827560007100099", 10),
                              BigInteger::One,
                              BigInteger::Multiply(BigInteger(std::numeric_limits<int>::max()), BigInteger(std::numeric_limits<long>::max())),
                              divisor + BigInteger::One };

   // Divide each dividend by divisor in three different ways.

   BigInteger quotient;
   BigInteger remainder = 0;

   // Console.WriteLine("Dividend: {0:N0}", dividend);
   // Dividend: 680,564,693,277,057,719,623,408,366,969,033,850,880
   REQUIRE(dividends[0].ToString(10) == "680564693277057719623408366969033850880");

   // 0: Divide 7 remainder 85,070,551,165,415,408,691,630,012,479,406,342,137
   REQUIRE((dividends[0] / divisor).ToString(10) == "7");
   REQUIRE((dividends[0] % divisor).ToString(10) == "85070551165415408691630012479406342137");

   // 1: Divide 0 remainder 90,612,345,123,875,509,091,827,560,007,100,099
   REQUIRE((dividends[1] / divisor).ToString(10) == "0");
   REQUIRE((dividends[1] % divisor).ToString(10) == "90612345123875509091827560007100099");

   // 2: Divide 0 remainder 1
   REQUIRE((dividends[2] / divisor).ToString(10) == "0");
   REQUIRE((dividends[2] % divisor).ToString(10) == "1");

   // 3: Divide 0 remainder 19,807,040,619,342,712,359,383,728,129
   REQUIRE((dividends[3] / divisor).ToString(10) == "0");
   REQUIRE((dividends[3] % divisor).ToString(10) == "19807040619342712359383728129");

   // 4: Divide 1 remainder 1
   REQUIRE((dividends[4] / divisor).ToString(10) == "1");
   REQUIRE((dividends[4] % divisor).ToString(10) == "1");
}

// TODO: add these bunch of tests https://github.com/dotnet/corefx/tree/master/src/System.Runtime.Numerics/tests/BigInteger

// three basic div

TEST_CASE("csBIArithmeticsTests:  Minus5Divides2EqualsMinus2")
{
   REQUIRE(-5 / 2 == -2); // c++ standard, same thing
   REQUIRE(BigInteger(-5) / BigInteger(2) == BigInteger(-2));
}

TEST_CASE("csBIArithmeticsTests:  FiveDividesMinus2EqualsMinus2")
{
   REQUIRE(5 / -2 == -2); // c++ standard, same thing
   REQUIRE(BigInteger(5) / BigInteger(-2) == BigInteger(-2));
}

TEST_CASE("csBIArithmeticsTests:  FiveDivides2Equals2")
{
   REQUIRE(5 / 2 == 2); // c++ standard, same thing
   REQUIRE(BigInteger(5) / BigInteger(2) == BigInteger(2));
}

TEST_CASE("csBIArithmeticsTests:  MinusFiveDividesMinus2Equals2")
{
   REQUIRE(-5 / -2 == 2); // c++ standard, same thing
   REQUIRE(BigInteger(-5) / BigInteger(-2) == BigInteger(2));
}

// three basic mod

TEST_CASE("csBIArithmeticsTests:  Minus10Mod3EqualsMinus1")
{
   REQUIRE(-10 % 3 == -1); // c++ standard, same thing
   REQUIRE(BigInteger(-10) % BigInteger(3) == BigInteger(-1));
}

TEST_CASE("csBIArithmeticsTests:  TenMod3Equals1")
{
   REQUIRE(10 % 3 == 1); // c++ standard, same thing
   REQUIRE(BigInteger(10) % BigInteger(3) == BigInteger(1));
}

// This test is very strange, but it is correct according to C++ and C#
TEST_CASE("csBIArithmeticsTests:  TenModMinus3Equals1")
{
   REQUIRE(10 % -3 == 1); // c++ standard, same thing
   REQUIRE(BigInteger(10) % BigInteger(-3) == BigInteger(1));
}

TEST_CASE("csBIArithmeticsTests:  MinusTenModMinus3EqualsMinus1")
{
   REQUIRE(-10 % -3 == -1); // c++ standard, same thing
   REQUIRE(BigInteger(-10) % BigInteger(-3) == BigInteger(-1));
}

TEST_CASE("csBIArithmeticsTests:  TenModMinus5Equals0")
{
   REQUIRE(10 % -5 == 0); // c++ standard, same thing
   REQUIRE(BigInteger(10) % BigInteger(-5) == BigInteger(0));
}
