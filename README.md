# AHSFNU 2023-2024 Research Based Learning

## 规范

### commit 名称

commit 的时候，用英文写明提交的内容，带上日期与时间。

### branch 命名

每写一个新功能，都必须开一个新的分支，命名为 `feature/功能名称`。

### 代码内注释

注释要清楚。

同时注意，在 `main.cpp` 以外新写了一个函数，须在头文件的声明中注明用途、参数与返回值含义。以下为例子：

```cpp
/**
 * Get the information of a block in the anvil.
 *
 * @param x - x towards the anvil
 * @param y - y
 * @param z - z towards the anvil
 * @return a pointer to Compound of the block.
 */
Compound* query(int x, int y, int z);
```

这样写完，在 Visual Studio 中，调用此函数时，鼠标放上去会有提示。
