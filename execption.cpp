#include <iostream>
#include <exception>
#include <stdexcept>

void failure() {
    throw std::runtime_error("Failure");
}

void call() {
    failure();
    std::cout << "point" << std::endl;
}
int main() {
    try {
        call();
    }  catch(const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}