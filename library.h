#pragma once

#include <vector>
#include <algorithm>

using Byte = unsigned char;
using IP = std::vector<Byte>;
using IPPool = std::vector<IP>;

Byte stob(const std::string &data);
IP parse_ip(const std::string &line);
void read_ip_pool(IPPool &ip_pool);
void sort_ip_pool(IPPool &ip_pool);
void print_ip(const IP &ip);
void print_ip_pool(const IPPool &ip_pool);

auto filter = [](const IPPool &ip_pool, auto ...params) {
    IP sample = { (Byte(params))... };
    IPPool result;
    auto begin = std::upper_bound(ip_pool.cbegin(), ip_pool.cend(), sample, [](const IP &sample, const IP &ip) {
        return sample > ip || std::equal(sample.cbegin(), sample.cend(), ip.cbegin());
    });
    auto end = std::lower_bound(begin, ip_pool.cend(), sample, std::greater<IP>());
    std::copy(begin, end, std::back_inserter(result));
    return result;
};

auto filter_any = [](const IPPool &ip_pool, auto param) {
    IPPool result;
    std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(result), [&param](const IP &ip) {
        return std::any_of(ip.begin(), ip.end(), [&param](Byte byte) {
            return param == byte;
        });
    });
    return result;
};
