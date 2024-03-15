#include "sort.h"
#include "calc.h"

void insert (std::vector<int> & nums) {
    
    std::sort(nums.begin() , nums.end());
    int sum = 0;
    for (auto & v : nums) {
        sum = add(sum , v);
        std::cout << sum << (v != nums.back() ? ',' : '\n');
    }
}