//https://blog.csdn.net/lyy289065406/article/details/6647917
#include<iostream>

using namespace std;

int mod[524286];  //保存每次mod n的余数

int main() {
    int i, n;
    while (cin >> n) {
        if (!n)
            break;

        mod[1] = 1;  //初始化，n倍数的最高位必是1

        for (i = 2; mod[i - 1] != 0; i++) {
            //利用同余模定理，从前一步的余数mod[i/2]得到下一步的余数mod[i]
            //i<<1相当于取除最后一位外的
            mod[i] = (mod[i >> 1] * 10 + i % 2) % n;
        }
        //mod[i/2]*10+i%2模拟了BFS的双入口搜索
        //当i为偶数时，+0，即取当前位数字为0,为奇数时，则+1,即取当前位数字为1

        i--;
        int j = 0;
        while (i) {
            mod[j++] = i & 1;   //i的二进制表示就是所求的数
            i >>= 1;
        }
        while (j) {
            cout << mod[--j];  //倒序输出
        }
        cout << endl;
    }
    return 0;
}
