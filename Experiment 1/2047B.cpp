#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int frequency[26] = {0};

    for (int i = 0; i < n; i++) {
        frequency[s[i] - 'a']++;
    }

    vector<pair<int, char>> letters;

    for (int i = 0; i < 26; i++) {
        if (frequency[i] > 0) {
            letters.push_back({frequency[i], char('a' + i)});
        }
    }

    sort(letters.begin(), letters.end());

    char leastFrequent = letters.front().second;
    char mostFrequent = letters.back().second;

    for (int i = 0; i < n; i++) {
        if (s[i] == leastFrequent) {
            s[i] = mostFrequent;
            break;
        }
    }

    cout << s << endl;
}

int main() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        solve();
    }

    return 0;
}
