#include <iostream>
#include <gflags/gflags.h>
#include <butil/logging.h>
#include <brpc/server.h>

int main() {
    brpc::Server server;
    std::cout << "server declared\n";
    return 0;
}
