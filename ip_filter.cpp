// Local
#include "ipv4_address.h"
#include "utilities.h"

// STL
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>

int main(int, char const*[])
{
    try
    {
        std::vector<Ipv4Address> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            if (line == "end") 
                break;

            std::vector<std::string> v = split(line, '\t');

            ip_pool.emplace_back(v.at(0));
        }

        // reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<Ipv4Address>());

        for (auto& ip_adress : ip_pool)
        {
            std::cout << ip_adress.GetIpv4AddressLikeDotDecimalNotation() << std::endl;
        }

        // ilter by first byte and output
        // ip = filter(1)
        {
            const auto kUpperLimit = Ipv4Address("1.255.255.255");
            const auto kLowerLimit = Ipv4Address("1.0.0.0");
            
            for (const auto& ip_adress : ip_pool)
            {
                if (ip_adress >= kLowerLimit && ip_adress <= kUpperLimit)
                    std::cout << ip_adress.GetIpv4AddressLikeDotDecimalNotation() << std::endl;
            }
        }

        // filter by first and second bytes and output
        // ip = filter(46, 70)
        {
            const auto kUpperLimit = Ipv4Address("46.70.255.255");
            const auto kLowerLimit = Ipv4Address("46.70.0.0");

            for (const auto& ip_adress : ip_pool)
            {
                if (ip_adress >= kLowerLimit && ip_adress <= kUpperLimit)
                    std::cout << ip_adress.GetIpv4AddressLikeDotDecimalNotation() << std::endl;
            }
        }

        // filter by any byte and output
        // ip = filter_any(46)
        {
            for (auto& ip_adress : ip_pool)
            {
                const auto kIpAddressValue = ip_adress.GetIpv4Adress();
                const auto* ptr_on_octet   = reinterpret_cast<const uint8_t*>(&kIpAddressValue);

                for (size_t i = 0; i < sizeof(kIpAddressValue); i++)
                {
                    if (ptr_on_octet[i] == 46)
                    {
                        std::cout << ip_adress.GetIpv4AddressLikeDotDecimalNotation() << std::endl;
                        break;
                    }
                }
            }
        }
    } catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
