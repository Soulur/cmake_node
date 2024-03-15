#include <iostream>

int main () {
    int a = 0;

#ifdef DEBUG
    std::cout << "not bug\n";
#endif
    return 0;
}