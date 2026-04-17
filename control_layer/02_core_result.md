# 提示词 02:实现 han::core::Result<T>

> **使用场景**:阶段 2 第一个模块。完成后按相同模式实现其他模块。
> **前置条件**:骨架已通过 `cmake --build`,`include/han/core/result.hpp` 是空壳。
> **预期耗时**:1 轮对话,按 STEP 1→2→3 分步交付。
> **成功标准**:`test_result` 全部通过 + 自审闸口无违反项。

---

## 复制以下内容给 AI

承接已有项目 `han`。项目规范见 `<SPEC>`,已完成的骨架见 `<EXISTING>`。

```
<SPEC>
[此处粘贴 docs/SPEC.md 的完整内容]
</SPEC>
```

```
<EXISTING>
// include/han/core/error.hpp 当前内容(空壳)
[粘贴当前 error.hpp 全文]

// include/han/core/result.hpp 当前内容(空壳)
[粘贴当前 result.hpp 全文]

// src/core/CMakeLists.txt 当前内容
[粘贴当前文件]

// tests/core/CMakeLists.txt 当前内容
[粘贴当前文件]
</EXISTING>
```

---

## 本轮任务

实现 `han::core::Result<T, E = Error>`(**仅此一个类**)以及它依赖的最小 `Error` / `ErrorCode` 实现。

### 范围边界

**本轮做**:
- `ErrorCode` 枚举(只填充 R3 需要的最小集:`kOk` / `kInvalidArgument` / `kInternalError`)
- `Error` 类(构造、`code()`、`message()`、`where()`)
- `Result<T, E>` 类模板(完整接口,见下)

**本轮不做**:
- 其他 `ErrorCode` 值(留给后续模块需要时添加)
- `Units` / `Logger` / `RealtimeGuard`(后续轮次)
- `Result<void>` 特化(如果需要,本轮告诉我,下一轮单独处理)

### 接口要求

```cpp
// Result<T, E = Error>
// 构造(静态工厂)
static Result ok(T value) noexcept;
static Result err(E error) noexcept;

// 禁用默认构造(强制显式语义)
Result() = delete;

// 移动语义,禁用拷贝
Result(Result&&) noexcept;
Result& operator=(Result&&) noexcept;
Result(const Result&) = delete;
Result& operator=(const Result&) = delete;

// 查询
bool is_ok() const noexcept;
bool is_err() const noexcept;
explicit operator bool() const noexcept;

// 访问(前置条件:is_ok() / is_err() 为真;违反是 UB,用 HAN_ASSERT 保护)
const T& value() const & noexcept;
T&& take() && noexcept;
const E& error() const & noexcept;

// 组合子
template <class F> auto map(F&& f) &&;         // T -> U  =>  Result<U, E>
template <class F> auto and_then(F&& f) &&;    // T -> Result<U, E>
template <class F> auto or_else(F&& f) &&;     // E -> Result<T, E>
```

### 实现约束

- 必须遵守 R1 - R10 的所有规则
- 内部存储用 `std::variant<T, E>` **或** 手写 union + discriminator,二选一(告诉我你选哪种及原因)
- `noexcept` 覆盖所有不抛异常的路径
- `[[nodiscard]]` 必须加在类上
- `HAN_ASSERT` 宏若不存在,在本轮补一个最小实现(放在 `include/han/core/detail/assert.hpp`)

---

## 分 3 步交付,每步我确认后再进行下一步

### STEP 1:设计确认

产出以下内容,**不写代码实现**:

1. 列出所有成员函数的完整签名(含 `noexcept` / `const` / 引用限定符)
2. 每个函数说明:
   - 前置条件(preconditions)
   - 后置条件(postconditions)
   - 错误情形(如有)
3. 说明内部存储方案(`variant` vs 手写 union),给出选择理由
4. 列出需要的 `#include`(按 R4 顺序)
5. 指出 2-3 个"容易出错点"(你认为实现时最容易踩的坑)

**完成 STEP 1 后停下,等我说"进入 STEP 2"。**

### STEP 2:单元测试

先写测试,后写实现。产出 `tests/core/test_result.cpp`,覆盖:

**正常路径**:
- `Result<int>::ok(42)` 正确构造,`value() == 42`
- `Result<int>::err(...)` 正确构造,`error().code() == kInvalidArgument`
- 移动构造和移动赋值正确
- `is_ok()` / `is_err()` / `bool` 转换一致

**组合子**:
- `map`:ok 路径变换值,err 路径原样传递
- `and_then`:ok 链式返回 Result,err 短路
- `or_else`:err 恢复为 ok,ok 原样传递

**错误路径 / 边界**:
- `Result<std::string>`(非平凡移动类型)
- `Result<std::unique_ptr<int>>`(仅移动类型)
- 禁用拷贝:`static_assert(!std::is_copy_constructible_v<Result<int>>)`

**不测**:
- 访问违反前置条件的情形(UB,靠 `HAN_ASSERT` 保护)

完成后同步更新 `tests/core/CMakeLists.txt`,注册 `test_result` 到 CTest。

**完成 STEP 2 后停下,等我说"进入 STEP 3"。**

### STEP 3:实现

产出:
1. `include/han/core/error.hpp`(完整)
2. `src/core/error.cpp`(如需要)
3. `include/han/core/result.hpp`(完整)
4. `include/han/core/detail/assert.hpp`(若本轮新增)
5. `src/core/CMakeLists.txt` 更新(若需要添加源文件)

每个文件给出完整内容。实现后,用**注释**说明:
- 为什么这样实现能通过 STEP 2 的每组测试
- 哪些路径是 `noexcept`,哪些不是,原因
- 是否有任何已知限制(例如 `T` 必须满足哪些 concept)

---

## 开始前必须先复述以下 3 个问题

**不要**开始 STEP 1,先回答:

1. 为什么 `Result` 的 `value()` / `error()` 访问器不返回 `Result<T, E>`?(考察对"访问 vs 查询"的理解)
2. SPEC R5 要求"能 `noexcept` 必须 `noexcept`"。`Result::ok(T value)` 能否总是 `noexcept`?为什么?
3. 本轮是否需要 `Result<void>` 特化?你的判断理由是什么?

回答后,等我说"开始 STEP 1"。
