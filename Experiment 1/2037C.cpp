#include <iostream>
using namespace std;

void solve() {
    int p;
    cin >> p;

    if (p < 5) {
        cout << -1 << endl;
        return;
    }

    for (int i = 1; i <= p; i += 2) {
        if (i != 5) {
            cout << i << " ";
        }
    }

    cout << "5 4 ";

    for (int i = 2; i <= p; i += 2) {
        if (i != 4) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        solve();
    }
    return 0;
}