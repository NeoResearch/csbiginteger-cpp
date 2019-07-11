#include <gtest/gtest.h>

// system
#include <limits>

// core includes
#include <BigInteger.h>

using namespace std;
using namespace csBigInteger;

// ============================================
// BIG LOOP TEST: ALL NUMBERS FROM -INT TO +INT
// ============================================
TEST(csBIHardTests, BigInteger_big_loop_20000000) // around 200 tests
{
   for (long i = std::numeric_limits<int>::min(); i < std::numeric_limits<int>::max(); i += 20000000) {
      BigInteger big((int)i);
      EXPECT_EQ(big.toInt(), i);
   }
}

// ============================================
// BIG LOOP TEST: ALL NUMBERS FROM -INT TO +INT
// ============================================
TEST(csBIHardTests, BigInteger_big_loop_1000000)
{
   for (long i = std::numeric_limits<int>::min(); i <= std::numeric_limits<int>::max(); i += 1000000) {
      BigInteger big((int)i);
      EXPECT_EQ(big.toInt(), i);
   }
}

// ============================================
// BIG LOOP TEST: ALL NUMBERS FROM -INT TO +INT
// ============================================
TEST(csBIHardTests, BigInteger_big_loop_100000)
{
   for (long i = std::numeric_limits<int>::min(); i <= std::numeric_limits<int>::max(); i += 100000) {
      BigInteger big((int)i);
      EXPECT_EQ(big.toInt(), i);
   }
}

// ============================================
// BIG LOOP TEST: ALL NUMBERS FROM -INT TO +INT
// ============================================
TEST(csBIHardTests, BigInteger_big_loop_10000)
{
   for (long i = std::numeric_limits<int>::min(); i <= std::numeric_limits<int>::max(); i += 10000) {
      BigInteger big((int)i);
      EXPECT_EQ(big.toInt(), i);
   }
}

// ============================================
// BIG LOOP TEST: ALL NUMBERS FROM -INT TO +INT
// ============================================
TEST(csBIHardTests, BigInteger_big_loop_1000)
{
   for (long i = std::numeric_limits<int>::min(); i <= std::numeric_limits<int>::max(); i += 1000) {
      BigInteger big((int)i);
      EXPECT_EQ(big.toInt(), i);
   }
}

/*
// ============================================
// BIG LOOP TEST: ALL NUMBERS FROM -INT TO +INT
// ============================================
TEST(csBIHardTests, BigInteger_big_loop_1)
{
   for (int i = std::numeric_limits<int>::min(); i <= std::numeric_limits<int>::max(); ++i) {
      BigInteger big(i);
      EXPECT_EQ(big.toInt(), i);
   }
}
*/
