#include "sort.h"

void select (std::vector<int> & nums) {
    std::sort (nums.begin() , nums.end() , [] (auto a , auto b) {
        return a > b;
    });
    for (auto & v : nums) std::cout << v << ',';
}