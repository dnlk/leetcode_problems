#include "common_includes.hpp"


class IntRangeView
{
public:
    using T = vector<int>;

    IntRangeView(const T& vec) : m_vec(vec), m_begin(0), m_end(vec.size())
    {}

    void drop_from_beginning(size_t n)
    {
        m_begin += n;
    }

    void drop_from_end(size_t n)
    {
        m_end -= n;
    }

    size_t size() const
    {
        return m_end - m_begin;
    }

    T::value_type at(size_t n) const
    {
        return m_vec.at(m_begin + n);
    }

    T new_vector_from_slice(size_t a, size_t b) const
    {
        return T(begin() + a, begin() + b);
    }

    T new_vector() const
    {
        return T(begin(), end());
    }

    T::const_iterator begin() const
    {
        return m_vec.begin() + m_begin;
    }

    T::const_iterator end() const
    {
        return m_vec.begin() + m_end;
    }

private:
    const T& m_vec;
    size_t m_begin;
    size_t m_end;  // end index + 1
};

double to_double(int x)
{
    return static_cast<double>(x);
}

double computeMedian(const IntRangeView& range)
{
    size_t arr_size = range.size();
    if (arr_size <= 0) {
        throw runtime_error("Don't call this with zero length range");
    }

    if (arr_size % 2 == 0) {
        size_t median_lower = range.at(arr_size / 2 - 1);
        size_t median_upper = range.at(arr_size / 2);
        // NOT HANDLED int overflow protection
        return to_double(median_lower + median_upper) / 2;
    }
    else {
        return to_double(range.at(arr_size / 2));
    }
}
double resolveBaseCase(const IntRangeView& range_big, const IntRangeView& range_small) {
    size_t small_arr_size = range_small.size();
    size_t big_arr_size = range_big.size();
    if (small_arr_size > 2) {
        throw runtime_error("Can't do base case where second array is larger than 2");
    }
    if (big_arr_size < 2) {
        throw runtime_error("Can't do base case where second array is less than 2");
    }

    vector<int> minimal_array;
    if (big_arr_size % 2) {
        // Odd. The middle 3 are the only ones that are possibly relevant to the
        // median calculation, after mixing in the 1 or 2 valuese from the small array.
        size_t begin_idx = big_arr_size / 2 - 1;
        minimal_array = range_big.new_vector_from_slice(begin_idx, begin_idx + 3);
    }
    else if (big_arr_size == 2) {
        minimal_array = range_big.new_vector();
    }
    else {
        // Even, > 2. The middle 4 are the only ones that are possibly relevant.
        size_t begin_idx = big_arr_size / 2 - 2;
        minimal_array = range_big.new_vector_from_slice(begin_idx, begin_idx + 4);
    }

    minimal_array.insert(minimal_array.end(), range_small.begin(), range_small.end());
    sort(minimal_array.begin(), minimal_array.end());

    return computeMedian(minimal_array);
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() == 0 and nums2.size() == 0) {
        throw runtime_error("Don't call this with zero values");
    }

    // NOT DONE - check if arrays are disjoint, or only share border values, and avoid work

    IntRangeView big_arr = (nums1.size() >= nums2.size() ? nums1 : nums2);
    IntRangeView small_arr = (nums1.size() >= nums2.size() ? nums2 : nums1);

    // Early exit if one of the arrays is zero length
    if (small_arr.size() == 0) {
        return computeMedian(big_arr);
    }

    if (big_arr.size() == 1) {
        // both arrays have size 1
        return to_double(*big_arr.begin() + *small_arr.begin()) / 2;
    }

    size_t small_arr_size;
    while ((small_arr_size = small_arr.size()) > 2) {
        // TODO possibly check here if the remaining arrays are disjoint

        size_t num_to_discard = small_arr_size / 2;
        if (small_arr_size % 2 == 0) {
            // Want to keep all values used to compute the median, which includes both middle values of an even length array
            num_to_discard -= 1;
        }
        double big_median = computeMedian(big_arr);
        double small_median = computeMedian(small_arr);
        if (big_median == small_median) {
            return big_median;
        }
        else if (big_median > small_median) {
            small_arr.drop_from_beginning(num_to_discard);
            big_arr.drop_from_end(num_to_discard);
        }
        else {
            small_arr.drop_from_end(num_to_discard);
            big_arr.drop_from_beginning(num_to_discard);
        }
    }

    // Now there is one element in the smaller array, and at least one element in the bigger array.
    return resolveBaseCase(big_arr, small_arr);
}

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        return findMedianSortedArrays(nums1, nums2);
    }
};



