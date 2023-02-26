#include<algorithms>
int count_div4 = std::count_if(v.begin(), v.end(), [](int i) { return i % 4 == 0; })
std::count(v.cbegin(), v.cend(), target);
// find, find_if, find_if, copy, copy_if, remove, remove_if
std::reverse(v.begin(), v.end());
auto last = std::unique(v.begin(), v.end()); v.erase(last, v.end()); // range must be sorted.
std::sort(s.begin(), s.end()); /* <- ascend | descend -> */ std::sort(s.begin(), s.end(), std::greater<int>());
std::sort(s.begin(), s.end(), [](int a, int b) {return a > b;}); // Expects <, tries to ascend. This does desecend.
// stable_sort
std::binary_search(haystack.begin(), haystack.end(), needle) // or lambda, should be <, range ascending
// lower_bound for 'not less', upper_bound for 'greater', 
std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dst));
std::inplace_merge(first, middle, last); // These are iterators
std::set_difference(A.begin(), A.end(), V.begin(), V.end(), std::back_inserter(C)) 
// C = A - B, sorted vectors. Optional lambda for <.  // set_union, set_intersection, set_symmetric_difference, includes (A includes B)
is_heap(first, last, [comp]); // make_heap, push_heap(first, last) -- pushes last elt into heap, pop_heap() -- moves top to end (MAX HEAP)
max_element, min_element(first, last, [comp representing <])
clamp(val, low, high);
is_permutation(v1.begin(), v1.end(), v2.begin()); // O(N^2)
next_permutation(v1.begin(), v1.end()); // returns false on reset to sorted range. prev_permutation

#include <random>
std::random_device dev; std::mt19937 rng(dev()); std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);
then use dist6(rng) repeatedly.


