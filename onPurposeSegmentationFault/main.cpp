#include <csignal>
#include <iostream>


void signal_handler(int signal) {
    std::cout << "du loser" << std::endl;
    std::exit(5);
}

int main() {
    std::signal(SIGSEGV, signal_handler);
    *(int*) nullptr = 0;
}

