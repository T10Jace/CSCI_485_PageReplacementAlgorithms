
#include <iostream>
#include <vector>

using namespace std;

const int NUM_FRAMES = 6;

int main() {
    vector<int> frames(NUM_FRAMES, -1); // Initialize frames with -1 (empty)
    vector<bool> second_chance(NUM_FRAMES, false);
    int pointer = 0; // Initialize pointer
    vector<int> reference_string = {0, 2, 1, 4, 3, 5, 1, 6, 2, 1, 4, 7, 0, 7, 8};
    int page_faults = 0;

    for (int page : reference_string) {
        bool found = false;
        for (int i = 0; i < NUM_FRAMES; ++i) {
            if (frames[i] == page) {
                second_chance[i] = true; // Page accessed, set second chance
                found = true;
                break;
            }
        }

        if (!found) {
            while (true) {
                if (!second_chance[pointer]) {
                    // Replace page at pointer
                    frames[pointer] = page;
                    second_chance[pointer] = true;
                    pointer = (pointer + 1) % NUM_FRAMES; // Move pointer circularly
                    ++page_faults;
                    break;
                } else {
                    // Give the page a second chance
                    second_chance[pointer] = false;
                    pointer = (pointer + 1) % NUM_FRAMES; // Move pointer circularly
                }
            }
        }
    }

    // Print the  total page faults
    cout << "Total page faults: " << page_faults << endl;

    return 0;
}
