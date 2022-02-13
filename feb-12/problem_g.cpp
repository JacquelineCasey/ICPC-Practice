
#include <iostream>
#include <array>

/*
 * We do this by building up the solution from one stone to many stones.
 * To add each stone: find the lowest empty pit, and fill it with one stone taken
 * from each previous pit, and one new stone. To solve this situation, the first
 * move is from this new pit, which places the new stone in the rumba and adds 
 * one stone to all lower pits, placing the board in a state that we know how to
 * solve.
 * 
 * Note that we only ever need to do up to 2000 stones, with a gaurantee of that
 * taking 80 or fewer pits, so this algorithm (which is something like O(n stones * p pits)
 * is actually quite reasonable (even if there are 200 data sets).
 */

void process_one_data_set() {
    int set_number {};
    int stones {};

    std::cin >> set_number >> stones;

    std::array<int, 80> pits {};

    for (int i {0}; i < stones; i++) {
        int first_empty_index {0};
        while (pits[first_empty_index] != 0)
            first_empty_index++;

         // +1 since array is 0 based (not 1)
        pits[first_empty_index] = first_empty_index + 1;

        for (int j {0}; j < first_empty_index; j++) {
            pits[j]--;
        }
    }
    
    // /* DEBUG */
    // for (int count : pits) 
    //     std::cout << count << ' ';

    // std::cout << "|\n";

    int last_pit {79};
    for (; last_pit >= 0; last_pit--) {
        if (pits[last_pit] != 0)
            break;
    }

    std::cout << set_number << ' ' << last_pit + 1; // 1 based

    for (int i = {0}; i <= last_pit; i++) {
        if (i % 10 == 0)
            std::cout << '\n';
        else
            std::cout << ' ';
        std::cout << pits[i];
    }
}

int main() {
    int k {};
    std::cin >> k;

    for (int i {0}; i < k; i++) {
        process_one_data_set();
        std::cout << '\n';
    }
}