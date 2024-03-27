// Local
#include "ipv4_address.h"
#include "utilities.h"

// STL
#include <tuple>

namespace
{
constexpr auto kMinValueOctet = 0;
constexpr auto kMaxValueOctet = 255;

uint32_t GetValueOctet(const std::string& octet)
{
    const auto kValueOctet = std::stoi(octet);

    if (kValueOctet < kMinValueOctet || kValueOctet > kMaxValueOctet)
        throw std::invalid_argument("Decimal value octet must be between " +
                                    std::to_string(kMinValueOctet) + " and " +
                                    std::to_string(kMaxValueOctet));

    return kValueOctet;
}

}  // namespace

Ipv4Address::Ipv4Address(const std::string& ip_adress) : ip_address(0), ip_address_str()
{
    SetIpv4Address(ip_adress);
}

bool Ipv4Address::operator<(const Ipv4Address& other) const
{
    return ip_address < other.ip_address;
}

bool Ipv4Address::operator>(const Ipv4Address& other) const
{
    return ip_address > other.ip_address;
}

bool Ipv4Address::operator<=(const Ipv4Address& other) const
{
    return ip_address <= other.ip_address;
}

bool Ipv4Address::operator>=(const Ipv4Address& other) const
{
    return ip_address >= other.ip_address;
}

bool Ipv4Address::operator==(const Ipv4Address& other) const
{
    return ip_address == other.ip_address;
}

void Ipv4Address::SetIpv4Address(const std::string& string_ip_address)
{
    const auto kSplitAdress = split(string_ip_address, '.');

    if (kSplitAdress.size() < 4)
        throw std::invalid_argument("IPv4 Adress must be include 4 octets separated by dots");

    uint32_t tmp_ip_address = 0;

    tmp_ip_address |= GetValueOctet(kSplitAdress[0]) << 24;
    tmp_ip_address |= GetValueOctet(kSplitAdress[1]) << 16;
    tmp_ip_address |= GetValueOctet(kSplitAdress[2]) << 8;
    tmp_ip_address |= GetValueOctet(kSplitAdress[3]);

    ip_address     = tmp_ip_address;
    ip_address_str = string_ip_address;
}

uint32_t Ipv4Address::GetIpv4Adress() const 
{
    return ip_address; 
}

std::string Ipv4Address::GetIpv4AddressLikeDotDecimalNotation() const 
{
    return ip_address_str;
}