#include <gtest/gtest.h>

// core includes
#include <BigInteger.h>

using namespace std;
using namespace csBigInteger;

TEST(csBigIntegerHelperTests, RevertHexString8000_0080)
{
   EXPECT_EQ(BigInteger::revertHexString("8000"), "0080");
}

TEST(csBigIntegerHelperTests, HexToBytes0001)
{
   vbyte vb = BigInteger::HexToBytes("0001");
   EXPECT_EQ(vb[0], 0x00);
   EXPECT_EQ(vb[1], 0x01);
}
