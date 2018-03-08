#include <iostream>
#include <memory>


int main () {

    std::shared_ptr<std::string> str = std::make_shared<std::string> ();

    int i = 0;
    for (; i < 5; i++) {
        *str += (i + 48);
    }
    // std::cout << *str;
    std::cout << (*str)[2];
    return 0;
}