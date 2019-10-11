#pragma once

#include <tuple>
#include <vector>
#include <algorithm>

using Byte = unsigned char;
using IP = std::tuple<Byte, Byte, Byte, Byte>;
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
        if (sample.size() > 0 && sample[0] != std::get<0>(ip)) return false;
        if (sample.size() > 1 && sample[1] != std::get<1>(ip)) return false;
        if (sample.size() > 2 && sample[2] != std::get<2>(ip)) return false;
        if (sample.size() > 3 && sample[3] != std::get<3>(ip)) return false;
        return true;
    });
    return result;
};

auto filter_any = [](const IPPool &ip_pool, auto param) {
    IPPool result;
    copy_if(ip_pool.cbegin(), ip_pool.cend(), back_inserter(result), [&param](const IP &ip) {
        return (param == std::get<0>(ip) || param == std::get<1>(ip) || param == std::get<2>(ip) || param == std::get<3>(ip));
    });
    return result;
};
