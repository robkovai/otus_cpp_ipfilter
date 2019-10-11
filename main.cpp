#include <iostream>

#include "library.h"

using namespace std;

int main() {
    try {
        IPPool ip_pool;
        read_ip_pool(ip_pool);

        print_ip_pool(ip_pool);
        print_ip_pool(filter(ip_pool, 1));
        print_ip_pool(filter(ip_pool, 46, 70));
        print_ip_pool(filter_any(ip_pool, 46));

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
    return 0;
}
