#include <iostream>
#include <vector>
using namespace std;

int maxCuts;
int minCuts;

void tryCuts(int remaining, int count, const vector<int>& cuts) {
    if (remaining == 0) {

        if (count > maxCuts) maxCuts = count;
        if (count < minCuts) minCuts = count;
        return;
    }
    if (remaining < 0) return;

    for (int i = 0; i < (int)cuts.size(); ++i) {
        tryCuts(remaining - cuts[i], count + 1, cuts);
    }
}

int main() {
    int n;
    cout << "Enter total ribbon length (n): ";
    cin >> n;

    int k;
    cout << "Enter number of possible cut lengths: ";
    cin >> k;

    vector<int> cuts(k);
    cout << "Enter the cut lengths: ";
    for (int i = 0; i < k; ++i) {
        cin >> cuts[i];
        if (cuts[i] <= 0) {
            cout << "Cut lengths must be positive integers.\n";
            return 1;
        }
    }

    maxCuts = -1;
    minCuts = 1000000;

    tryCuts(n, 0, cuts);

    if (maxCuts == -1) {
        cout << "It is not possible to cut the ribbon using the given lengths." << endl;
    }
    else {
        cout << "Maximum number of pieces: " << maxCuts << endl;
        cout << "Minimum number of pieces: " << minCuts << endl;
    }
}

const int num = 1000000;
const int neg_num = -1;

void ribbonCutting(const vector<int>& cutSizes, int totalLength, vector<int>& maxCuts, vector<int>& minCuts, int& maxPieces, int& minPieces) {
    vector<int> Maxpieces(totalLength + 1, neg_num);
    vector<int> Minpieces(totalLength + 1, num);
    Maxpieces[0] = Minpieces[0] = 0;

    maxCuts.assign(totalLength + 1, 0);
    minCuts.assign(totalLength + 1, 0);

    for (int i = 1; i <= totalLength; i++) {
        for (int j = 0; j < cutSizes.size(); j++) {
            int cut = cutSizes[j];
            if (i >= cut) {
                if (Maxpieces[i - cut] != neg_num && Maxpieces[i - cut] + 1 > Maxpieces[i]) {
                    Maxpieces[i] = Maxpieces[i - cut] + 1;
                    maxCuts[i] = cut;
                }
                if (Minpieces[i - cut] != num && Minpieces[i - cut] + 1 < Minpieces[i]) {
                    Minpieces[i] = Minpieces[i - cut] + 1;
                    minCuts[i] = cut;
                }
            }
        }
    }

    if (Maxpieces[totalLength] == neg_num) {
        maxPieces = 0;
    }
    else {
        maxPieces = Maxpieces[totalLength];
    }

    if (Minpieces[totalLength] == num) {
        minPieces = 0;
    }
    else {
        minPieces = Minpieces[totalLength];
    }
}
void printCutSequence(const vector<int>& cuts, int length) {
    if (cuts[length] == 0) {
        cout << "No valid cuts." << endl;
        return;
    }
    cout << "Cut sequence: ";
    while (length > 0) {
        cout << cuts[length] << " ";
        length -= cuts[length];
    }
    cout << endl;
}

int main() {
    int totalLength, numberOfCuts;
    cout << "Enter total ribbon length: ";
    cin >> totalLength;

    cout << "Enter number of cut sizes: ";
    cin >> numberOfCuts;

    vector<int> cutSizes(numberOfCuts);
    cout << "Enter cut sizes: ";
    for (int i = 0; i < numberOfCuts; i++) {
        cin >> cutSizes[i];
    }

    vector<int> maxCuts, minCuts;
    int maxPieces, minPieces;

    ribbonCutting(cutSizes, totalLength, maxCuts, minCuts, maxPieces, minPieces);

    cout << "Maximum pieces: " << maxPieces << endl;
    printCutSequence(maxCuts, totalLength);

    cout << "Minimum pieces: " << minPieces << endl;
    printCutSequence(minCuts, totalLength);

}
