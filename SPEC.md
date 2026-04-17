# han 库设计规范 (SPEC)

> **本文档是项目宪法。所有代码生成必须严格遵守。**
> 每次 AI 对话开始前,请将本文档完整贴给 AI,并要求其复述关键约束。

---

## 0. 项目概述

`han` 是基于 Pinocchio 的机器人学 C++20 库,提供运动学、动力学、模型管理的分层封装。

- **语言**:C++20
- **构建**:CMake ≥ 3.20
- **核心依赖**:Pinocchio, Eigen3, Boost
- **测试**:GoogleTest
- **性能测试**:Google Benchmark

---

## 1. 分层架构

### 1.1 层次划分

```
┌──────────────────────────────────────────────────┐
│  han::kin          han::dyn                      │  运动学 / 动力学层
│  FK / IK / Jac     RNE / CRBA / ID / ExtForceObs │
└────────┬──────────────────┬──────────────────────┘
         │                  │
         ▼                  ▼
┌──────────────────────────────────────────────────┐
│  han::model    RobotModel / Payload /            │  模型层
│                ActuatorModel / PresetRegistry    │
└────────────────────┬─────────────────────────────┘
                     ▼
┌──────────────────────────────────────────────────┐
│  han::types    JointState / Pose / Twist /       │  语义类型层
│                Wrench (alias to Pinocchio/Eigen) │
└────────────────────┬─────────────────────────────┘
                     ▼
┌──────────────────────────────────────────────────┐
│  han::core     Result / Error / Units /          │  基础设施层
│                Logger / RealtimeGuard            │
└────────────────────┬─────────────────────────────┘
                     ▼
           Pinocchio → Eigen → Boost
```

### 1.2 依赖方向(R1)

严格单向:

```
core ← types ← model ← { kin, dyn }
```

- `core` 不依赖任何 han 模块,也不依赖 Pinocchio(仅 Eigen/Boost/STL)
- `types` 依赖 `core` + Eigen/Pinocchio(类型别名)
- `model` 依赖 `types` + `core` + Pinocchio(pimpl 封装)
- `kin` / `dyn` 平级,都依赖 `model` / `types` / `core`
- **`kin` 与 `dyn` 之间禁止互相依赖**

---

## 2. 目录结构

```
han/
├── CMakeLists.txt
├── cmake/
│   ├── hanConfig.cmake.in
│   ├── hanTargets.cmake
│   └── CompileOptions.cmake
├── include/han/
│   ├── core/
│   │   ├── result.hpp
│   │   ├── error.hpp
│   │   ├── units.hpp
│   │   ├── logger.hpp
│   │   ├── realtime_guard.hpp
│   │   └── fwd.hpp
│   ├── types/
│   │   ├── aliases.hpp
│   │   ├── joint_state.hpp
│   │   ├── pose.hpp
│   │   ├── twist.hpp
│   │   ├── wrench.hpp
│   │   └── fwd.hpp
│   ├── model/
│   │   ├── robot_model.hpp
│   │   ├── payload.hpp
│   │   ├── actuator_model.hpp
│   │   ├── preset_registry.hpp
│   │   └── fwd.hpp
│   ├── kin/
│   │   ├── forward_kinematics.hpp
│   │   ├── inverse_kinematics.hpp
│   │   ├── jacobian.hpp
│   │   ├── singularity.hpp
│   │   └── fwd.hpp
│   ├── dyn/
│   │   ├── rne.hpp
│   │   ├── crba.hpp
│   │   ├── inverse_dynamics.hpp
│   │   ├── ext_force_observer.hpp
│   │   └── fwd.hpp
│   └── han.hpp
├── src/                   # 镜像 include 结构
│   ├── core/
│   ├── types/
│   ├── model/
│   ├── kin/
│   └── dyn/
├── tests/                 # 每层一个子目录
├── benchmarks/
├── examples/
└── docs/
```

**路径 ↔ 命名空间映射**:
`include/han/kin/forward_kinematics.hpp` ↔ `han::kin::ForwardKinematics`

---

## 3. 构建系统

### 3.1 Target 划分

| Target        | 类型      | Pinocchio 链接 | 说明                       |
|---------------|-----------|----------------|----------------------------|
| `han_core`    | STATIC    | 不链接         | 基础设施                   |
| `han_types`   | INTERFACE | PUBLIC         | header-only,类型别名传播  |
| `han_model`   | STATIC    | PRIVATE        | pimpl 隐藏 Pinocchio 符号  |
| `han_kin`     | STATIC    | PRIVATE        | 通过 model::Handle 访问    |
| `han_dyn`     | STATIC    | PRIVATE        | 通过 model::Handle 访问    |
| `han`         | INTERFACE | —              | 聚合目标,下游链接 han::han |

### 3.2 别名目标

```cmake
add_library(han::han   ALIAS han)
add_library(han::core  ALIAS han_core)
add_library(han::types ALIAS han_types)
add_library(han::model ALIAS han_model)
add_library(han::kin   ALIAS han_kin)
add_library(han::dyn   ALIAS han_dyn)
```

### 3.3 编译选项(统一)

- `-Wall -Wextra -Wpedantic -Werror`
- C++20 标准,`-std=c++20`
- Release 默认 `-O2 -DNDEBUG`
- Debug 启用 AddressSanitizer 可选开关

---

## 4. 硬性规则(R1 - R10)

**违反任意一条视为该轮产出失败。**

### R1:依赖方向

- 严格遵守 §1.2 的方向
- 禁止反向 `#include`
- `kin` 与 `dyn` 互不包含对方头文件

### R2:命名规范

| 类别         | 规则                         | 示例                      |
|--------------|------------------------------|---------------------------|
| 类 / 结构体  | `PascalCase`                 | `RobotModel`, `JointState`|
| 函数 / 方法  | `snake_case`                 | `compute_jacobian`        |
| 常量 / 枚举值| `k` + `PascalCase`           | `kMaxIterations`, `kOk`   |
| 模板参数     | `PascalCase`                 | `template<class Scalar>`  |
| 成员变量     | `snake_case_`(尾下划线)     | `model_`, `data_`         |
| 命名空间     | 全小写                       | `han::kin`                |
| 宏           | `HAN_` + `UPPER_SNAKE`       | `HAN_ASSERT`              |
| 文件名       | `snake_case.hpp` / `.cpp`    | `robot_model.hpp`         |

**禁用前缀**:`get_` / `set_`(访问器直接用属性名,如 `translation()` 而非 `get_translation()`)

### R3:错误处理

- 不抛异常跨 API 边界
- 可失败函数必须返回 `han::core::Result<T>`
- 第三方(Pinocchio / Eigen)可能抛出的异常,必须在 `model` / `kin` / `dyn` 的 `.cpp` 边界捕获并转为 `Result::err`
- 禁止用 `-1` / 空 `optional` / 空指针表示失败(`optional` 仅用于"合法的缺省",不用于错误)
- 禁止 `assert(false)` 代替错误返回

### R4:头文件

- 顶部必须 `#pragma once`(不用 `#ifndef` guard)
- public 头(`include/han/**`)禁止 `#include <Eigen/Dense>`,用 `<Eigen/Core>` 等最小集
- public 头禁止 `using namespace`
- public 头禁止 `inline` 全局变量(`inline constexpr` 常量除外)
- 包含顺序:
  1. 本 `.cpp` 配对的 `.hpp`
  2. C 标准库(`<cstdint>` 等)
  3. C++ 标准库(`<string>` 等)
  4. 第三方(Eigen / Pinocchio / Boost)
  5. han 其他层
  6. 本层其他头文件

### R5:函数签名

- 输入:`const T&` 或 `std::span<const T>`
- 输出:返回值 优先;必要时 `T& out` 作为输出参数
- **禁止** `T*` 作为输出参数(空指针语义不清)
- 能 `noexcept` 必须 `noexcept`
- 不能 `noexcept` 时,在 `@throws` 文档注释中说明
- 实时路径带 `han::core::realtime_safe_t` tag 参数

### R6:Pinocchio 暴露策略

- `han::types` 可在 public 头中直接别名 Pinocchio 类型(`SE3`/`Motion`/`Force`)
- `han::model::RobotModel` 必须用 **pimpl** 隐藏 `pinocchio::Model`
- `han::kin` / `han::dyn` 的 public 头禁止出现任何 `pinocchio::` 符号
- 内部需要访问 Pinocchio `Model` / `Data` 时,通过 `han::model::RobotModel::Handle` 半透明句柄

### R7:实时性(软实时)

- 实时路径:预分配 `Workspace` 后,调用时不得 `new` / `malloc` / 加锁
- 实时函数必须 `noexcept`,错误通过 `Result` 返回
- 实时函数签名末尾带 `han::core::realtime_safe_t = {}` tag
- 非实时函数(如 IK 迭代)不强制 `noexcept`,但禁止未处理异常逸出

### R8:所有权与拷贝

- 重型对象(`RobotModel`, `Workspace`)禁用拷贝构造(`= delete`),仅支持移动
- 句柄类型(`Handle`, `span`)可拷贝,语义为浅引用
- 禁止裸 `new` / `delete`,使用 `std::unique_ptr` / `std::make_unique`

### R9:测试

- 每个 public 类 / 函数至少一个单元测试
- 每个可失败函数必须有"错误路径"测试(验证返回 `Result::err`)
- 单元测试放在 `tests/<layer>/test_<module>.cpp`
- 每层单独一个 CTest target,可独立运行

### R10:文档注释

- public 类 / 函数必须有 Doxygen 风格注释
- 必须包含:`@brief` / `@param` / `@return`
- 可失败函数必须有 `@return` 说明 `Result` 的错误情形
- 实时函数必须有 `@realtime-safe` 标注
- 非实时函数若可能抛异常,必须有 `@throws` 说明

---

## 5. 每层职责与约束

### 5.1 han::core

**职责**:全项目共享的基础原语,零业务语义。

**模块**:
- `Result<T, E = Error>` — 返回值容器
- `Error` + `ErrorCode` — 统一错误表示
- `Units` — 强类型单位(Radian / Degree / Meter / ...)
- `Logger` — 异步日志(环形缓冲 + 后台 flush)
- `RealtimeGuard` — 实时作用域检查(debug hook malloc)

**约束**:
- 不依赖任何 han 模块
- 不依赖 Pinocchio
- 所有类型 `noexcept` 友好

### 5.2 han::types

**职责**:对外暴露的语义类型。

**模块**:
- `aliases.hpp` — Pinocchio / Eigen 类型别名集中地
- `JointState` / `Pose` / `Twist` / `Wrench` — 业务语义类型

**约束**:
- header-only(`han_types` 是 INTERFACE 库)
- 不定义算法函数,仅类型 + 纯访问器(`norm`, `inverse` 级别)
- 成员满足:默认构造、可移动、`noexcept` 析构

### 5.3 han::model

**职责**:机器人模型的不可变封装 + 负载 / 执行器 / 预设管理。

**模块**:
- `RobotModel` — Pinocchio `Model` 的 pimpl 封装
- `Payload` — 附加负载
- `ActuatorModel` — 执行器建模
- `PresetRegistry` — 内置机型注册表

**约束**:
- `RobotModel` 加载后不可变(immutable)
- 唯一构造入口:`from_urdf` / `from_urdf_string` / `from_preset` 静态工厂
- 可变状态(`q`, `v`, `payload`)由调用方持有,不存于 `RobotModel` 内

### 5.4 han::kin

**职责**:FK / IK(自研)/ Jacobian / 奇异性。

**模块**:
- `ForwardKinematics` + `FkWorkspace`
- `InverseKinematics`(带 `Options` 的类)
- `Jacobian` — body / world / spatial 三种
- `Singularity` — 可操作度 / 最近奇异方向

**约束**:
- 算法优先无状态函数,需要缓存时用 `Workspace`
- 实时路径:FK / Jacobian(传入预分配 `Workspace`)
- 非实时:IK(迭代求解)

### 5.5 han::dyn

**职责**:RNE / CRBA / ID / 外力观测器。

**模块**:
- `recursive_newton_euler`(RNE)
- `mass_matrix`(CRBA)
- `inverse_dynamics`(语义包装)
- `ExtForceObserver`(有状态,带滤波器)

**约束**:
- 与 `kin` 平级,禁止互相依赖
- `ExtForceObserver::update` 为实时路径

---

## 6. 错误码表

```cpp
enum class ErrorCode : std::uint16_t {
  kOk = 0,
  kInvalidArgument,
  kOutOfRange,
  kNotInitialized,
  kModelMismatch,
  kDimensionMismatch,
  kUrdfParseError,
  kPresetNotFound,
  kIkDidNotConverge,
  kSingularConfiguration,
  kJointLimitViolation,
  kRealtimeViolation,
  kInternalError,
};
```

新增错误码须先更新此表,再使用。

---

## 7. 本文档的使用方式

### 7.1 每次对话开始

1. 完整贴入本 `SPEC.md`
2. 贴入当前已完成的代码(作为 `<EXISTING>` 上下文)
3. 明确本轮任务范围(单个模块 / 单个类)
4. 要求 AI 先复述 3 条最容易违反的规则
5. 复述正确后才开始生成代码

### 7.2 每轮交付验收

- [ ] 能编译(`cmake --build` 返回 0)
- [ ] 通过本轮相关的单元测试
- [ ] 用 `grep` 机械检查命名规范
- [ ] 用 `grep` 检查 `public` 头是否漏出 `pinocchio::`(除 types 外)
- [ ] 自审:是否违反 R1 - R10 的任何一条

### 7.3 版本控制

每一轮结束立即 `git commit`。违反规范的产出不 commit,让 AI 重做。

---

**文档版本**:v1.0
**最后更新**:2026-04-17
