#pragma once

// STL
#include <cstdint>
#include <string>

class Ipv4Address
{
    uint32_t    ip_address;
    std::string ip_address_str;

public:
    explicit Ipv4Address(const std::string& ip_adress);
    ~Ipv4Address() = default;

    bool operator<(const Ipv4Address& other) const;
    bool operator>(const Ipv4Address& other) const;
    bool operator<=(const Ipv4Address& other) const;
    bool operator>=(const Ipv4Address& other) const;
    bool operator==(const Ipv4Address& other) const;

    void SetIpv4Address(const std::string& string_ip_adress);

    uint32_t GetIpv4Adress() const;
    std::string GetIpv4AddressLikeDotDecimalNotation() const;
};