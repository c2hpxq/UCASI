# dijkstra
## 优先队列版本
### 复杂度分析
- 每条边只松弛一次： $O(E)$
- 每次松弛至多往优先队列中加入一项
    - 优先队列中元素个数： $O(E)$
    - 加入复杂度： $O(ElogE)$
    - 每一轮取优先队列中的最小项： $O(ElogE)$
### 注意点
- 图中同一个节点可能在算法的不同轮次中被多次加入优先队列。
- 本实现不判断节点 $v$是否已经出现在优先队列中
    - 只要松弛更新的结果优于现有结果（边 $(u, v)$， $d_u + w_{u, v} < d_v$）就将 $v$加入优先队列
    - 从优先队列中取当前距离源节点最近的未访问节点时进行判断

### C++ features
#### std::greater
- 模板类。需要传入的类型支持`>`。
- 由于重载了`operator()`，该类的实例可以像函数那样调用。故称**function objects**。
- [ref](https://cplusplus.com/reference/functional/greater/)

#### std::greater<>
- greater模板的一个特化，允许参与比较的参数具有不同类型。返回值类型为2种类型`operator>`的返回类型。
- 示例代码见：
## 试验区
[leetcode 743.网络延迟时间](https://leetcode.cn/problems/network-delay-time/)