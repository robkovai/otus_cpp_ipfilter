#pragma once

#include <tuple>
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
    std::vector<Byte> sample = { (Byte(params))... };
    IPPool result;
    copy_if(ip_pool.cbegin(), ip_pool.cend(), back_inserter(result), [&sample](const IP &ip) {
        return std::equal(sample.cbegin(), sample.cend(), ip.cbegin());
    });
    return result;
};

auto filter_any = [](const IPPool &ip_pool, auto param) {
    IPPool result;
    copy_if(ip_pool.cbegin(), ip_pool.cend(), back_inserter(result), [&param](const IP &ip) {
        return std::any_of(ip.begin(), ip.end(), [&param](Byte byte) {
            return param == byte;
        });
    });
    return result;
};
