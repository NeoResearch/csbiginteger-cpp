#include <gtest/gtest.h>

// system
#include <limits>

// core includes
#include <BigInteger.h>

using namespace std;
using namespace csbiginteger;

TEST(csBIArithmeticsTests, ZeroNotError)
{
   BigInteger big0(0);
   EXPECT_EQ(big0 != BigInteger::Error, true);
}

TEST(csBIArithmeticsTests, OnePlusOneEqualsTwo)
{
   EXPECT_EQ(BigInteger::One + BigInteger::One, BigInteger(2));
}

TEST(csBIArithmeticsTests, OneTimesZeroEqualsZero)
{
   EXPECT_EQ(BigInteger::One * BigInteger::Zero, BigInteger::Zero);
}

TEST(csBIArithmeticsTests, OneTimesMinusOneEqualsMinusOne)
{
   EXPECT_EQ(BigInteger::One * BigInteger::MinusOne, BigInteger::MinusOne);
}

TEST(csBIArithmeticsTests, OnePlusMinusOneEqualsZero)
{
   EXPECT_EQ(BigInteger::One + BigInteger::MinusOne, BigInteger::Zero);
}

TEST(csBIArithmeticsTests, TenDivTwoEqualsFive)
{
   EXPECT_EQ(BigInteger(10) / BigInteger(2), BigInteger(5));
}

TEST(csBIArithmeticsTests, TenModTwoEqualsZero)
{
   EXPECT_EQ(BigInteger(10) % BigInteger(2), BigInteger(0));
}

TEST(csBIArithmeticsTests, TenDivThreeEqualsThree)
{
   EXPECT_EQ(BigInteger(10) / BigInteger(3), BigInteger(3));
}

TEST(csBIArithmeticsTests, TenModThreeEqualsOne)
{
   EXPECT_EQ(BigInteger(10) % BigInteger(3), BigInteger(1));
}

TEST(csBIArithmeticsTests, TenDivZeroEqualsError)
{
   EXPECT_EQ(BigInteger(10) / BigInteger(0), BigInteger::Error);
}

TEST(csBIArithmeticsTests, OnePlusErrorEqualsError)
{
   EXPECT_EQ(BigInteger(1) + BigInteger::Error, BigInteger::Error);
}

// operator- unary

TEST(csBIArithmeticsTests, Minus10IsMinus10)
{
   EXPECT_EQ(-BigInteger(10), BigInteger(-10));
}

// SHL SHR

TEST(csBIArithmeticsTests, EightSHLIsSixteen)
{
   EXPECT_EQ(BigInteger(8) << 1, BigInteger(16));
}

TEST(csBIArithmeticsTests, EightSHRIsFour)
{
   EXPECT_EQ(BigInteger(8) >> 1, BigInteger(4));
}

TEST(csBIArithmeticsTests, EightMinusSHLIsFour)
{
   EXPECT_EQ(BigInteger(8) << -1, BigInteger(4));
}

TEST(csBIArithmeticsTests, EightMinusSHRIsSixteen)
{
   EXPECT_EQ(BigInteger(8) >> -1, BigInteger(16));
}

TEST(csBIArithmeticsTests, TenSHRZeroIsTen)
{
   EXPECT_EQ(BigInteger(10) >> 0, BigInteger(10));
}

TEST(csBIArithmeticsTests, TenSHLZeroIsTen)
{
   EXPECT_EQ(BigInteger(10) << 0, BigInteger(10));
}

// ---------- error
TEST(csBIArithmeticsTests, ZeroAddErrorIsError)
{
   EXPECT_EQ(BigInteger(0) + BigInteger::Error, BigInteger::Error);
}

TEST(csBIArithmeticsTests, ZeroMinusErrorIsError)
{
   EXPECT_EQ(BigInteger(0) - BigInteger::Error, BigInteger::Error);
}

TEST(csBIArithmeticsTests, ZeroMulErrorIsError)
{
   EXPECT_EQ(BigInteger(0) * BigInteger::Error, BigInteger::Error);
}

TEST(csBIArithmeticsTests, ZeroDivErrorIsError)
{
   EXPECT_EQ(BigInteger(0) / BigInteger::Error, BigInteger::Error);
}

TEST(csBIArithmeticsTests, ZeroModErrorIsError)
{
   EXPECT_EQ(BigInteger(0) % BigInteger::Error, BigInteger::Error);
}

TEST(csBIArithmeticsTests, ZeroSHLErrorIsError)
{
   EXPECT_EQ(BigInteger(0) << BigInteger::Error, BigInteger::Error);
}

TEST(csBIArithmeticsTests, ZeroSHRErrorIsError)
{
   EXPECT_EQ(BigInteger(0) >> BigInteger::Error, BigInteger::Error);
}

// ========= compare

TEST(csBIArithmeticsTests, ZeroLessThanOne)
{
   cout << "will compare 0 and 1" << endl;
   BigInteger big0(0);
   BigInteger big1(1);
   EXPECT_EQ(big0.operator<(big1), true);
}

TEST(csBIArithmeticsTests, OneGreaterThanZero)
{
   EXPECT_EQ(BigInteger(1) > BigInteger(0), true);
}

TEST(csBIArithmeticsTests, NotZeroGreaterThanOne)
{
   EXPECT_EQ(BigInteger(0) > BigInteger(1), false);
}

TEST(csBIArithmeticsTests, ZeroLeqOne)
{
   EXPECT_EQ(BigInteger(0) <= BigInteger(1), true);
}

TEST(csBIArithmeticsTests, NotZeroGeqOne)
{
   EXPECT_EQ(BigInteger(0) >= BigInteger(1), false);
}

TEST(csBIArithmeticsTests, ZeroLessThanErrorIsFalse)
{
   EXPECT_EQ(BigInteger(0) < BigInteger::Error, false);
}

TEST(csBIArithmeticsTests, ZeroGreaterThanErrorIsFalse)
{
   EXPECT_EQ(BigInteger(0) > BigInteger::Error, false);
}

// ============ special

TEST(csBIArithmeticsTests, SpecialDiv)
{
   BigInteger b1 = BigInteger("41483775933600000000");
   BigInteger b2 = BigInteger("414937759336");
   EXPECT_EQ(b1 / b2, BigInteger("99975899"));
}

TEST(csBIArithmeticsTests, SpecialDiv2)
{
   BigInteger b1 = BigInteger("-11001000000");
   BigInteger b2 = BigInteger(86400);
   EXPECT_EQ(b1 / b2, BigInteger(-127326));
}

TEST(csBIArithmeticsTests, SpecialMod)
{
   BigInteger b1 = BigInteger("20195283520469175757");
   BigInteger b2 = BigInteger("1048576");
   EXPECT_EQ(b1 % b2, BigInteger("888269"));
}

// 860593 % -201 is 112
TEST(csBIArithmeticsTests, SpecialModNeg)
{
   EXPECT_EQ(BigInteger(860593) % BigInteger(-201), BigInteger(112));
}

TEST(csBIArithmeticsTests, SpecialModNeg2)
{
   EXPECT_EQ(BigInteger("-18224909727634776050312394179610579601844989529623334093909233530432892596607") % BigInteger("14954691977398614017"), BigInteger("-3100049211437790421"));
}

// ======================= Pow =======================

TEST(csBIArithmeticsTests, Pow3_2_9)
{
   EXPECT_EQ(BigInteger::Pow(BigInteger(3), 2), BigInteger(9));
}

TEST(csBIArithmeticsTests, Pow3_0_9)
{
   EXPECT_EQ(BigInteger::Pow(BigInteger(3), 0), BigInteger::One);
}

// ======================= Online tests =======================

// from: https://docs.microsoft.com/en-us/dotnet/api/system.numerics.biginteger.divide?view=netframework-4.8

TEST(csBIArithmeticsTests, Online_Pack_Divisor)
{
   BigInteger big64max(std::numeric_limits<long>::max());
   EXPECT_EQ(big64max.ToString(10), "9223372036854775807");
   BigInteger divisor = BigInteger::Pow(big64max, 2);
   EXPECT_EQ(divisor.ToString(10), "85070591730234615847396907784232501249");
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
   EXPECT_EQ(dividends[0].ToString(10), "680564693277057719623408366969033850880");

   // 0: Divide 7 remainder 85,070,551,165,415,408,691,630,012,479,406,342,137
   EXPECT_EQ((dividends[0] / divisor).ToString(10), "7");
   EXPECT_EQ((dividends[0] % divisor).ToString(10), "85070551165415408691630012479406342137");

   // 1: Divide 0 remainder 90,612,345,123,875,509,091,827,560,007,100,099
   EXPECT_EQ((dividends[1] / divisor).ToString(10), "0");
   EXPECT_EQ((dividends[1] % divisor).ToString(10), "90612345123875509091827560007100099");

   // 2: Divide 0 remainder 1
   EXPECT_EQ((dividends[2] / divisor).ToString(10), "0");
   EXPECT_EQ((dividends[2] % divisor).ToString(10), "1");

   // 3: Divide 0 remainder 19,807,040,619,342,712,359,383,728,129
   EXPECT_EQ((dividends[3] / divisor).ToString(10), "0");
   EXPECT_EQ((dividends[3] % divisor).ToString(10), "19807040619342712359383728129");

   // 4: Divide 1 remainder 1
   EXPECT_EQ((dividends[4] / divisor).ToString(10), "1");
   EXPECT_EQ((dividends[4] % divisor).ToString(10), "1");
}

// TODO: add these bunch of tests https://github.com/dotnet/corefx/tree/master/src/System.Runtime.Numerics/tests/BigInteger
