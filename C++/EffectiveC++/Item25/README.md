
- c++ compiler会优先查找同一namespace中的swap函数；如若不存在，才会使用std中的swap。
- 具体到swap的场合，现在有move，一般而言应该使用move ctor来完成资源交换