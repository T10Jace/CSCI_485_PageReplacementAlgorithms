#include <iostream>
#include <vector>
#include <unordered_map> // For tracking page access order

using namespace std;

const int NUM_FRAMES = 3;

int main() {
    vector<int> frames(NUM_FRAMES, -1); // Initialize frames with -1 (empty)
    unordered_map<int, int> page_index; // Map to store page index in frames
    int pointer = 0; // Initialize pointer
    vector<int> reference_string = {0, 2, 1, 4, 3, 5, 1, 6, 2, 1, 4, 7, 0, 7, 8};
    int page_faults = 0;

    for (int page : reference_string) {
        if (page_index.find(page) != page_index.end()) {
            // Page already exists in frames, update its index
            int index = page_index[page];
            page_index[page] = pointer;
            frames[index] = page;
        } else {
            // Page not in frames, replace LRU page
            int lru_page = frames[pointer];
            page_index.erase(lru_page); // Remove LRU page from map
            frames[pointer] = page;
            page_index[page] = pointer;
            pointer = (pointer + 1) % NUM_FRAMES; // Move pointer circularly
            ++page_faults;
        }
    }

    // Print the total page faults
    cout << "Total page faults: " << page_faults << endl;

    return 0;
}