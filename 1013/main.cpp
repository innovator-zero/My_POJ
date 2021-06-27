#include <iostream>
#include <cstring>

using namespace std;

char L[3][7], R[3][7], result[3][7];

bool isfake(char c, bool light) {
    for (int i = 0; i < 3; i++) {
        char *left, *right;
        if (light) { //如果这枚硬币轻，那么右盘上升的话就应该在右盘，右盘下降的话应该在左盘
            left = L[i];
            right = R[i];
        } else { //如果这枚硬币重，情况是反过来的
            left = R[i];
            right = L[i];
        }
        switch (result[i][0]) {
            case 'u':
                if (!strchr(right, c)) return false; //硬币不在右盘里，说明不是假币
                break;
            case 'e':
                if (strchr(left, c) || strchr(right, c)) return false; //硬币只要在左盘或右盘里，就不是假币
                break;
            case 'd':
                if (!strchr(left, c)) return false; //硬币不在左盘里，说明不是假币
                break;
        }
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> L[j] >> R[j] >> result[j];
        }
        for (char c = 'A'; c <= 'L'; c++) { //遍历每一枚硬币
            if (isfake(c, true)) { //假设这枚硬币轻
                cout << c << " is the counterfeit coin and it is light.\n";
                break;
            } else if (isfake(c, false)) { //假设这枚硬币重
                cout << c << " is the counterfeit coin and it is heavy.\n";
                break;
            }
        }
    }
    return 0;
}
