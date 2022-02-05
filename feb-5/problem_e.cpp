/* https://open.kattis.com/contests/nar21practice3/problems/expectingrain */

/*
 * Coding it up sounded like a pain and I ran out of time, but we did figure out
 * a way that we were fairly confident in.
 * 
 * First, do some precomputing, and get an array that gives the expected rain
 * for each second (10,000 seconds).
 * 
 * Now do dynamic programming. At each step, you can either walk forward or stand
 * still. There are 1000 steps, but 10,000 seconds, so there is a total space of 
 * 10,000,000.
 * - You can either do this from front to back via memoization and recursion, or 
 *   from back to front with a lookup table via traditional dynamic programming.
 */

#include <iostream>
#include <vector>

struct Intensity_Changes {
    int start {}; // s_i
    int end {}; // e_i

};

int main() {
    int bus_home_distance {}; // d
    int time_bus_leaves {}; // t
    int cloud_count {}; // c
    int roof_count {}; // r

    std::vector<int> intensity_changes {};
    for (int i {0}; i < cloud_count; i++) {

    }
}