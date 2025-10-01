#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 1, M = 1e6 + 10;  // 节点个数 颜色个数
int n, m;
int h[M], e[N], ne[N], idx;          // h[M] 每种颜色头结点 这些数组存所有节点
int col[N], sz[M], p[M];             // 每个节点颜色 每种颜色集合大小 映射：每种颜色对应哪个编号
int ans = 0;                         // 颜色段数量

// 向链表中添加节点
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    sz[a]++;
}

// 启发式合并两个颜色集合
void merge(int& x, int& y) {
    // 如果颜色相同，无需合并
    if (x == y) return;
    
    // 启发式合并：将小集合合并到大集合中
    if (sz[x] > sz[y]) swap(x, y);
    
    // 计算合并后会减少的颜色段数量
    for (int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        // 如果当前节点的相邻节点颜色是y，合并后颜色段会减少
        ans -= (col[j - 1] == y) + (col[j + 1] == y);
    }

    // 实际进行颜色变更和链表合并
    for (int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        col[j] = y;  // 将颜色x的节点改为颜色y
        
        // 当遍历到最后一个节点时，将x的链表连接到y的链表上
        if (ne[i] == -1) {
            ne[i] = h[y], h[y] = h[x];  // 将x下拉链表头插入y的下拉链表中
            break;
        }
    }
    
    // 更新集合大小并清空x集合
    sz[y] += sz[x], sz[x] = 0;
    h[x] = -1;  // 清空x集合
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);  // 初始化链表头节点为-1
    
    // 读入初始颜色序列并统计初始颜色段数量
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &col[i]);
        // 如果当前颜色与前一个不同，则颜色段数增加
        if (col[i] != col[i - 1]) ++ans;
        // 将位置i加入到颜色col[i]的链表中
        add(col[i], i);
    }

    // 初始化颜色映射关系
    for (int i = 0; i < M; ++i) p[i] = i;
    
    // 处理m次操作
    while (m--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            // 操作1：将颜色x全部修改为颜色y
            int x, y;
            scanf("%d%d", &x, &y);
            merge(p[x], p[y]);  // 通过映射关系进行合并
        } else {
            // 操作2：查询当前颜色段数量
            printf("%d\n", ans);
        }
    }

    return 0;
}