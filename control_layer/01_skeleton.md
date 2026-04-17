# 提示词 01:项目骨架生成

> **使用场景**:项目初始化时,用于生成目录结构、CMakeLists、空壳头文件。
> **前置条件**:已有 `docs/SPEC.md`。
> **预期耗时**:1 轮对话,20-40 分钟。
> **成功标准**:`cmake -B build && cmake --build build` 返回 0。

---

## 复制以下内容给 AI

我在用 C++20 + CMake + Pinocchio 实现一个机器人学库 `han`,分 5 层:
`core` / `types` / `model` / `kin` / `dyn`。

完整设计规范见下方 `<SPEC>` 块。请**严格遵守,不要自由发挥**。

```
<SPEC>
[此处粘贴 docs/SPEC.md 的完整内容]
</SPEC>
```

---

## 本轮任务

生成项目骨架。要求如下。

### 必须产出

1. 按 SPEC §2 的目录结构建立所有目录和空文件(空文件用 `.gitkeep` 占位)
2. 顶层 `CMakeLists.txt` 和每层子目录的 `CMakeLists.txt`
   - 按 SPEC §3.1 的 target 划分实现"分层多 target"结构
   - 顶层提供聚合 target `han::han` 及每层别名 `han::core` / `han::types` / ...
   - Pinocchio 链接策略严格按 SPEC §3.1 表格
3. 每个 public `.hpp` 文件(`include/han/**`)只写:
   - `#pragma once`
   - 正确的 `#include`(遵守 R4 包含顺序)
   - `namespace`
   - 类 / 函数的**声明**(不写实现)
   - Doxygen 注释骨架(`@brief` 占位即可)
4. `examples/00_smoke.cpp`:
   - 只需要 `#include <han/han.hpp>`
   - `main()` 返回 0
   - 用于验证链接正确性
5. `README.md` 最小版:
   - 项目简介
   - 构建命令
   - 目录结构说明

### 禁止事项

- 禁止实现任何算法或业务逻辑
- 禁止引入 SPEC 未列出的第三方库
- 禁止在 public 头中 `#include <Eigen/Dense>`(用 `<Eigen/Core>` 等最小集)
- 禁止在 `han::kin` / `han::dyn` 的 public 头中出现 `pinocchio::` 符号
- 禁止 `RobotModel` 的 public 头暴露 `pinocchio::Model`(必须 pimpl)

### 输出格式

**第 1 步**:先列出所有要创建的文件(树状视图),让我确认结构

**第 2 步**:按以下顺序逐文件给出完整内容,每个文件用代码块包裹,文件路径作为代码块上方的标题:
1. `CMakeLists.txt`(顶层)
2. `cmake/CompileOptions.cmake`
3. `cmake/hanConfig.cmake.in`
4. `include/han/core/*.hpp` → `src/core/CMakeLists.txt`
5. `include/han/types/*.hpp` → `src/types/CMakeLists.txt`
6. `include/han/model/*.hpp` → `src/model/CMakeLists.txt`
7. `include/han/kin/*.hpp` → `src/kin/CMakeLists.txt`
8. `include/han/dyn/*.hpp` → `src/dyn/CMakeLists.txt`
9. `include/han/han.hpp`
10. `examples/00_smoke.cpp` + `examples/CMakeLists.txt`
11. `tests/CMakeLists.txt`(GoogleTest 框架接入,测试用例留空)
12. `README.md`

**第 3 步**:给出"如何验证"章节,包括:
- 具体的 shell 命令序列
- 每条命令的期望输出
- 如果失败,如何排查

---

## 开始前必须先复述以下 3 个问题

**不要**开始写代码,先回答:

1. **依赖方向**是什么?哪一层不能依赖哪一层?
2. 每层的 CMake target 类型(`STATIC` / `SHARED` / `INTERFACE`)分别是什么?
3. Pinocchio 在哪些 target 中是 `PUBLIC` 链接,哪些是 `PRIVATE` 链接?为什么要这样区分?

回答正确后,再等我说"开始",才生成代码。
