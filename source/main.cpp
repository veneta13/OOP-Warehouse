#include <iostream>
#include "executor.hpp"

int main() {
    Executor executor;
    executor.setToday(std::cout, std::cin);
    while (executor.enter(std::cout, std::cin)) {}
    return 0;
}
