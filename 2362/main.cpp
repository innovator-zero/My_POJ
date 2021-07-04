#include <iostream>
#include <algorithm>
#include <cstring>
#include <functional>

using namespace std;

int sticks[20];
int side, m;
bool visited[20];

bool DFS(int sum, int number, int position) {
    //sum:当前要凑的边的长度
    //number:已经凑出的边数
    //position:下一个尝试的木棍，剪枝策略
    if (number == 3) {
        return true; //已经凑出三条边，剩下的一定可行
    }

    for (int i = position; i < m; i++) {
        if (visited[i] || sum + sticks[i] > side) {
            continue; //这条边不能选
        }
        visited[i] = true;
        if (sum + sticks[i] == side) { //凑出来了
            if (DFS(0, number + 1, 0)) return true; //从0开始凑下一条边
        } else {
            if (DFS(sum + sticks[i], number, i + 1)) return true;
            //这条边可以选，继续选下一条边，不需要从头开始（剪枝：前面的都考虑过了）
        }
        visited[i] = false;
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> m;
        int len = 0;
        for (int j = 0; j < m; j++) {
            cin >> sticks[j];
            len += sticks[j];
        }

        side = len / 4; //正方形的边长
        sort(sticks, sticks + m, greater<int>()); //从大到小排序
        if (len % 4 != 0 || side < sticks[0]) { //总长不能被4整除或最长的木棍比边长长，直接不行
            cout << "no" << endl;
            continue;
        }

        memset(visited, false, sizeof(visited)); //清空visited
        if (DFS(0, 0, 0)) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }

    return 0;
}
