#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int map[16][16], tmp[16][16];
int m[16];
int n, cnt, min_cnt;

// 二进制枚举第一行的所有可能性
void meiju(int x) {
    memset(m, 0, sizeof(m)); // 记得先清零
    int i = 0;
    while (x) {
        m[i++] = x & 1;
        x >>= 1;
    }
}

// 画一格
void paint(int x, int y) {
    tmp[x][y] = !tmp[x][y];
    if (x - 1 >= 0) {
        tmp[x - 1][y] = !tmp[x - 1][y];
    }
    if (y - 1 >= 0) {
        tmp[x][y - 1] = !tmp[x][y - 1];
    }
    if (x + 1 < n) {
        tmp[x + 1][y] = !tmp[x + 1][y];
    }
    if (y + 1 < n) {
        tmp[x][y + 1] = !tmp[x][y + 1];
    }
    cnt++;
}

void check() {
    // 如果上一行的这个列不是黄色，就要在当前位置画
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!tmp[i - 1][j]) {
                paint(i, j);
            }
        }
    }
    // 检查最后一行是否都是黄色
    for (int i = 0; i < n; i++) {
        if (!tmp[n - 1][i]) return; // 这种画法不行
    }
    min_cnt = min(min_cnt, cnt); // 成功，记录最小值
}

int main() {
    int t;
    char c;
    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cin >> c;
                if (c == 'y') map[j][k] = 1;
                else map[j][k] = 0;
            }
        }

        min_cnt = n * n + 1;
        // 枚举第一行的画法，共2^n种，第一行确定了后面也就都确定了
        for (int j = 0; j < (1 << n); j++) {
            cnt = 0;
            memcpy(tmp, map, sizeof(map));
            meiju(j);
            for (int k = 0; k < n; k++) {
                if (m[k]) paint(0, k); // 画第一行
            }
            check();
        }
        if (min_cnt == n * n + 1) {
            cout << "inf" << endl;
        } else {
            cout << min_cnt << endl;
        }
    }
    return 0;
}
