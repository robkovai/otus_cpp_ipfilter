#include "library.h"

#include <iostream>

using namespace std;

Byte stob(const string &data) {
    return Byte(stoi(data));
}

IP parse_ip(const string &line) {
    string ip = line.substr(0, line.find('\t'));
    vector<Byte> bytes;
    size_t start = 0, end = ip.find('.');
    while (end != string::npos) {
        bytes.push_back(stob(ip.substr(start, end - start)));
        start = end + 1;
        end = ip.find('.', start);
    }
    bytes.push_back(stob(ip.substr(start, end)));
    return IP(bytes[0], bytes[1], bytes[2], bytes[3]);
}

void read_ip_pool(IPPool &ip_pool) {
    string line;
    while (getline(cin, line))
        ip_pool.push_back(parse_ip(line));
    sort_ip_pool(ip_pool);
}

void sort_ip_pool(IPPool &ip_pool) {
    sort(ip_pool.rbegin(), ip_pool.rend());
}

void print_ip(const IP &ip) {
    cout << short(get<0>(ip)) << "." << short(get<1>(ip)) << "." << short(get<2>(ip)) << "." << short(get<3>(ip)) << endl;
}

void print_ip_pool(const IPPool &ip_pool) {
    for (auto ip : ip_pool)
        print_ip(ip);
}
