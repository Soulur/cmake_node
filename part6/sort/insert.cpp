#include "sort.h"
void insert (std::vector<int> & nums) {
    
    std::sort(nums.begin() , nums.end());
    for (auto & v : nums) std::cout << v << ',';
}