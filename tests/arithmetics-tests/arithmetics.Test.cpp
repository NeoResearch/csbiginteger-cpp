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

// TODO: add these bunch of tests https://github.com/dotnet/corefx/tree/master/src/System.Runtime.Numerics/tests/BigInteger
