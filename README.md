# 排序算法实验

本项目包含三种（冒泡、选择、快速）未优化的排序算法，多种构型测试数据（正序、逆序、均匀分布、正态分布、结构体）生成方法，以及运行时间测试方法。

## 项目结构

- `Sorts.c/h`: 包含整数和浮点数的排序算法实现
- `SortString.c`: 包含字符串排序算法实现
- `Score.c/h`: 结构体排序相关代码
- `MyRand.c/h`: 随机数生成相关代码
- `Test.c`: 测试主程序
- `Debug/`: Debug版本构建目录
- `Release/`: Release版本构建目录

## 编译和运行

### 使用Makefile

1. 编译Debug版本:
   ```
   make debug
   ```

2. 编译Release版本:
   ```
   make release
   ```

3. 编译所有版本:
   ```
   make
   ```

4. 清理编译文件:
   ```
   make clean
   ```

### 运行程序

1. 运行Debug版本:
   ```
   cd Debug
   ./run.sh
   ```

2. 运行Release版本:
   ```
   cd Release
   ./run.sh
   ```

3. 查看结果:
   ```
   cd Debug  # 或 cd Release
   ./open.sh
   ```

### 使用VSCode

本项目已配置VSCode任务和调试配置，可以直接使用:

1. 按 `Ctrl+Shift+B` 构建Debug版本
2. 按 `F5` 启动调试
3. 在任务面板中选择 "Run Debug" 或 "Run Release" 运行程序
4. 在任务面板中选择 "Open Debug Results" 或 "Open Release Results" 查看结果

## 已完成的任务

1. 实现了两个字符串排序函数:
   - `BubbleA`: 用于排序二维字符数组形式的字符串
   - `BubbleB`: 用于排序字符串指针数组形式的字符串

## 注意事项

- 本项目已适配Linux环境，替换了原Windows批处理文件
- 使用GCC编译器进行编译
- 结果将保存在对应构建目录的results.txt文件中