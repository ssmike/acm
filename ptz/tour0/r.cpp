#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    freopen("ratio.in", "r", stdin);
    freopen("ratio.out", "w", stdout);
    double a, b;
    cin >> a >> b;
    if (b == 0) {
        cout << "V predyduschej zadache uzhe pisali, chto na nol' delit' nel'zya!!!" << endl;
    } else {
        printf("%.6lf", a / b);
    }
}
