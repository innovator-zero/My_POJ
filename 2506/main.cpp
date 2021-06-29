#include <iostream>
#include <algorithm>

using namespace std;

//递归做法，数据太大不可行
long long tile(int x) {
    if (x == 1) return 1;
    if (x == 2) return 3;
    return tile(x - 1) + 2 * tile(x - 2);
}

//记忆化递归(dp?)，把前面算的都存下来
//数字太大，要用高精度乘法
int a[251][3000];

int main() {
    //a[i][0]：数字的位数
    a[1][0] = 1;
    a[1][1] = 1;
    a[2][0] = 1;
    a[2][1] = 3;

    //把所有的都预先算出来
    for (int i = 3; i <= 250; i++) {
        a[i][0] = max(a[i - 1][0], a[i - 2][0]);
        for (int j = 1; j <= a[i][0]; j++) {
            a[i][j] = a[i - 1][j] + 2 * a[i - 2][j];
        }
        //需要进位
        for (int j = 1; j <= a[i][0]; j++) {
            if (a[i][j] >= 10) {
                a[i][j + 1] += a[i][j] / 10;
                a[i][j] %= 10;
            }
        }
        //最高位有进位，数字的长度加1
        if (a[i][a[i][0] + 1]) {
            a[i][0]++;
        }
    }

    int n;
    while (cin >> n) {
        if (n == 0) { //考虑边界情况
            cout << "1" << endl;
            continue;
        }
        for (int i = a[n][0]; i > 0; i--) {
            cout << a[n][i];
        }
        cout << endl;
    }

    return 0;
}
