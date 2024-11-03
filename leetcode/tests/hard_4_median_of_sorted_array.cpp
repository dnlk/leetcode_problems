#pragma once

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/catch_all.hpp>
#include <catch2/generators/catch_generators_range.hpp>


#include "../solutions/common_includes.hpp"

using namespace Catch;


extern double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);


struct TestCase {
    std::vector<int> arr1;
    std::vector<int> arr2;
    double expected_result;

    void run() {
        REQUIRE(findMedianSortedArrays(arr1, arr2) == expected_result);
    }
};


std::vector<int> make_range() {
    return std::vector<int>{0, 1};
}


TEST_CASE("findMedianSortedArrays") {
    auto [arr1, arr2, expected_result] = GENERATE(table<vector<int>, vector<int>, double>({
        // { {}, {}, ... },  throws
        { {1}, {}, 1 },
        { {}, {1}, 1 },
        { {-1}, {-1}, -1},
        { {-33}, {34}, 0.5},
        { {0, 10}, {-1}, 0},
        { {0, 10}, {0}, 0},
        { {0, 10}, {5}, 5},
        { {0, 10}, {10}, 10},
        { {0, 10}, {11}, 10},
        { {-5, 0, 5}, {-1}, -0.5},
        { {-5, 0, 5}, {0}, 0},
        { {-5, 0, 5}, {1}, .5},
        { {-100, -10}, {10, 100}, 0 },
        { {-100, -10}, {-20, 100}, -15 },
        { {-100, -10}, {-210, 100}, -55 },
        { {-100, -10}, {-210, -150}, -125 },
        { { -100, -10 }, {-210, -150}, -125 },
        { { -100, 0, 100 }, {-10, -5}, -5 },
        { { -100, 0, 100 }, {-10, 10}, 0 },
        { { -100, 0, 100 }, {5, 10}, 5 },
        { { -100, -50, 50, 100 }, {-75, 0}, -25 },
        { { -100, -50, 50, 100 }, {-75, 90}, 0 },
        { { -100, -50, 50, 100 }, {0, 75}, 25 },
        { { -100, -50, 50, 100 }, {-10, 8}, -1 },
        { { 1, 5, 7, 12 }, {0, 4, 9, 12}, 6 },  // both medians come from first array
        { {0, 4, 9, 12}, { 1, 5, 7, 12 }, 6 },  // both medians come from second array
    }));

    CAPTURE(arr1, arr2);
    REQUIRE(findMedianSortedArrays(arr1, arr2) == expected_result);
}