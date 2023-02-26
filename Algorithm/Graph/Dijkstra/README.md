# dijkstra

## 普通版本
[代码](https://github.com/c2hpxq/UCASI/blob/main/Algorithm/Graph/Dijkstra/dijkstra.cpp)

###复杂度分析
 $O(V^2)$
- 算法最多运行 $V-1$ 轮，每轮选出未被访问过的节点 $O(V)$ ： $O(V^2)$
- 每条边最多松弛一次，而 $E = O(V^2)$ 。

## 优先队列版本
[代码](https://github.com/c2hpxq/UCASI/blob/main/Algorithm/Graph/Dijkstra/dijkstra_heap.cpp)

### 复杂度分析
 $O(ElogE)$
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

## C++ features

### std::greater
```c++
template<typename _Tp>
struct greater : public binary_function<_Tp, _Tp, bool>
{
    _GLIBCXX14_CONSTEXPR
    bool
    operator()(const _Tp& __x, const _Tp& __y) const
    { return __x > __y; }
};
```
- 模板类。需要传入的类型支持`>`。
- 由于重载了`operator()`，该类的实例可以像函数那样调用。故称**function objects**。
- [ref](https://cplusplus.com/reference/functional/greater/)

### std::greater<>
```c++
template<>
struct greater<void>
{
    template <typename _Tp, typename _Up>
constexpr auto
operator()(_Tp&& __t, _Up&& __u) const
noexcept(noexcept(std::forward<_Tp>(__t) > std::forward<_Up>(__u)))
-> decltype(std::forward<_Tp>(__t) > std::forward<_Up>(__u))
{
    return _S_cmp(std::forward<_Tp>(__t), std::forward<_Up>(__u),
        __ptr_cmp<_Tp, _Up>{});
}
```
- greater模板的一个特化，允许参与比较的参数具有不同类型。返回值类型为2种类型`operator>`的返回类型。
- [示例代码](https://github.com/c2hpxq/UCASI/blob/main/Algorithm/Graph/Dijkstra/show_case_greater_specialization.cpp)

## 试验区
[leetcode 743.网络延迟时间](https://leetcode.cn/problems/network-delay-time/)