#include <iostream>
#include <vector>
using namespace std;

void findPermutations(vector<int>& combination, int index, int remainingSum, int x, int y) {
    // Base case: if all units are filled and sum equals y
    if (index == x) {
        if (remainingSum == 0) {
            for (int i = 0; i < x; i++) {
                cout << combination[i] << (i == x - 1 ? "\n" : ", ");
            }
        }
        return;
    }

    // Try all possible values for the current unit
    for (int value = 0; value <= y && value <= remainingSum; value++) {
        combination[index] = value;
        findPermutations(combination, index + 1, remainingSum - value, x, y);
    }
}

int main() { 
    int x, y;
    cout << "Enter the number of units (x): ";
    cin >> x;
    cout << "Enter the target sum (y): ";
    cin >> y;

    if (x <= 0 || y < 0) {
        cout << "Invalid input. x should be positive and y should be non-negative." << endl;
        return 1;
    }

    vector<int> combination(x); // Stores the current permutation
    findPermutations(combination, 0, y, x, y);

    return 0;
}
