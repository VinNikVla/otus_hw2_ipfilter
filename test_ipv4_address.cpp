#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "ipv4_address.h"

TEST(IpAdress, test_ipv4_address)
{
    ASSERT_EQ(Ipv4Address("1.2.3.4").GetIpv4AddressLikeDotDecimalNotation(), "1.2.3.4");
    ASSERT_EQ(Ipv4Address("1.2.3.4").GetIpv4Adress(), 1U << 24 | 2U << 16 | 3U << 8 | 4U);
    ASSERT_EQ(Ipv4Address("1.2.3.4").GetIpv4Adress(), (1U << 24) + (2U << 16) + (3U << 8) + 4U);

    ASSERT_EQ(Ipv4Address("1.2.3.4"), Ipv4Address("1.2.3.4"));
    ASSERT_GT(Ipv4Address("1.2.3.5"), Ipv4Address("1.2.3.4"));
    ASSERT_GE(Ipv4Address("1.2.3.4"), Ipv4Address("1.2.3.4"));
    ASSERT_GE(Ipv4Address("1.2.3.5"), Ipv4Address("1.2.3.4"));
    ASSERT_LT(Ipv4Address("1.2.3.3"), Ipv4Address("1.2.3.4"));
    ASSERT_LE(Ipv4Address("1.2.3.4"), Ipv4Address("1.2.3.4"));
    ASSERT_LE(Ipv4Address("1.2.3.3"), Ipv4Address("1.2.3.4"));

    EXPECT_THROW(Ipv4Address("1.2.3,4"), std::invalid_argument);
    EXPECT_THROW(Ipv4Address("1.2.3.289"), std::invalid_argument);
    EXPECT_THROW(Ipv4Address("1.2.3.-1"), std::invalid_argument);
}