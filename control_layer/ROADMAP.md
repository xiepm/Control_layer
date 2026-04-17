# han 库实施路线图

> **目标**:用 AI 辅助,按规范完整实现 `han` 库。
> **预计总周期**:取决于你的节奏,全部走完约 15-25 个有效工作日。

---

## 阶段 0:准备(0.5 天)

- [ ] 把 `docs/SPEC.md` 放进项目
- [ ] `git init` + 首次 commit(`chore: add SPEC`)
- [ ] 搭建开发环境:CMake ≥ 3.20 / C++20 编译器 / Pinocchio / Eigen / GoogleTest
- [ ] 建立本地验证脚本 `scripts/lint_check.sh`(见 `prompts/99_audit.md`)

---

## 阶段 1:骨架(0.5 天)

**使用**:`prompts/01_skeleton.md`

- [ ] 走一轮骨架生成对话
- [ ] 验证 `cmake -B build && cmake --build build` 返回 0
- [ ] 验证 `./build/examples/00_smoke` 运行正常
- [ ] 运行 `scripts/lint_check.sh`,确保无违反
- [ ] `git commit -m "feat: project skeleton"`

**如果编译失败**:贴错误给 AI 让它修,修完重跑。不通过不进入阶段 2。

---

## 阶段 2:模块实现(主要耗时,12-20 天)

### 实现顺序(严格自底向上)

| 轮次 | 模块                              | 复杂度 | 提示词                          |
|------|-----------------------------------|--------|---------------------------------|
| 1    | `core::Result` + `Error`          | 中     | `02_core_result.md`             |
| 2    | `core::Units`                     | 低     | 用 `template_module.md` 填      |
| 3    | `core::Logger`                    | 中     | 用 `template_module.md` 填      |
| 4    | `core::RealtimeGuard` + `Assert`  | 中     | 用 `template_module.md` 填      |
| 5    | `types::aliases`                  | 低     | 用 `template_module.md` 填      |
| 6    | `types::JointState`               | 低     | 用 `template_module.md` 填      |
| 7    | `types::Pose`                     | 中     | 用 `template_module.md` 填      |
| 8    | `types::Twist` + `Wrench`         | 低     | 用 `template_module.md` 填      |
| 9    | `model::RobotModel`(pimpl)       | 高     | 用 `template_module.md` 填      |
| 10   | `model::Payload`                  | 中     | 用 `template_module.md` 填      |
| 11   | `model::ActuatorModel`            | 中     | 用 `template_module.md` 填      |
| 12   | `model::PresetRegistry`           | 中     | 用 `template_module.md` 填      |
| 13   | `kin::Jacobian`                   | 中     | 用 `template_module.md` 填      |
| 14   | `kin::ForwardKinematics`          | 中     | 用 `template_module.md` 填      |
| 15   | `kin::Singularity`                | 低     | 用 `template_module.md` 填      |
| 16   | `kin::InverseKinematics`          | 高     | 用 `template_module.md` 填      |
| 17   | `dyn::rne` + `crba`               | 中     | 用 `template_module.md` 填      |
| 18   | `dyn::inverse_dynamics`           | 低     | 用 `template_module.md` 填      |
| 19   | `dyn::ExtForceObserver`           | 高     | 用 `template_module.md` 填      |

### 每轮标准流程

1. 用对应提示词开新对话
2. 等 AI 复述 3 个问题,答对再开始
3. STEP 1 → 我确认 → STEP 2 → 我确认 → STEP 3
4. 本地跑测试,通过后提交
5. `git commit -m "feat(<layer>): implement <module>"`
6. **每 3 轮插入一次"自审闸口"**(见下)

### 自审闸口(每 3 轮一次)

**使用**:`prompts/99_audit.md`

- [ ] 开新会话,贴 SPEC + 当前所有代码
- [ ] 让 AI 按 R1-R10 逐条审查
- [ ] 跑 `scripts/lint_check.sh`
- [ ] Top 3 违反项修复,每个独立 commit

---

## 阶段 3:集成审查(1-2 天)

所有模块完成后:

- [ ] 完整自审(`99_audit.md`)
- [ ] 端到端测试:写一个 `examples/full_pipeline.cpp`
  - 加载 URDF → FK → IK → RNE → 外力估计
  - 数值验证:与 Pinocchio 原生 API 结果对比
- [ ] Benchmark:
  - 实时路径(FK / Jacobian / RNE / CRBA)在预分配 workspace 下的耗时
  - 对比无分配 / 有分配的开销差异
- [ ] 覆盖率检查:`gcov` / `llvm-cov`,目标 ≥ 85%
- [ ] `git commit -m "test: integration and benchmarks"`

---

## 阶段 4:文档与发布(1-2 天)

- [ ] `docs/architecture.md`:分层图、依赖关系、设计决策
- [ ] `docs/realtime.md`:实时路径清单、预分配指南、禁用 API
- [ ] `docs/coding_style.md`:从 SPEC §4 提炼
- [ ] `docs/examples.md`:典型用法
- [ ] 更新 `README.md`:完整的 quickstart
- [ ] 可选:Doxygen 配置 + 生成 API 文档
- [ ] `git tag v0.1.0`

---

## 风险清单与应对

| 风险                                | 征兆                            | 应对                                    |
|-------------------------------------|---------------------------------|-----------------------------------------|
| AI 跨会话风格漂移                   | 新模块命名突然变了              | 每轮都完整贴 SPEC,不偷懒               |
| AI 过度设计                         | 给出 CRTP / 5 层模板            | 在提示词"禁止事项"里明确不要           |
| 长文件后半段质量下降                | 一个文件 > 400 行                | 拆成骨架 + 实现两轮                     |
| pimpl 实现错误导致符号泄漏          | 链接下游时报 Pinocchio 符号     | 立刻用 `nm` 检查 `.so` 导出符号        |
| `noexcept` 标注错误导致运行时崩溃   | 异常逸出 → `std::terminate`     | 每个 `noexcept` 函数必须审查内部调用链 |
| IK 求解不收敛                       | 测试偶发失败                    | 测试用容差 + 固定随机种子,标注已知局限|

---

## 每日工作节奏建议

**上午(专注 AI 协作)**:
- 1-2 个模块实现(每个 ~1.5 小时)
- 按 STEP 1→2→3 严格走

**下午(人工活儿)**:
- 跑测试 / 修错
- 必要时手写关键数值算法(AI 在数值领域容易犯错,自己验算)
- 写 benchmark / 做性能分析

**睡前 10 分钟**:
- git log 回顾当天产出
- 标记明天第一个要做的模块

---

## 什么情况该**停下**重新规划

遇到以下任何一条,不要硬刚,停下想想:

1. **同一个模块 3 次对话都不通过测试**:接口设计可能有问题,回到 SPEC 重新思考
2. **自审闸口连续 2 次出现同类违反**:SPEC 不够清晰,补充规则
3. **Benchmark 实时路径超出预算**:预分配策略设计有问题,可能需要重构 `Workspace`
4. **AI 反复建议加"小优化"导致偏离架构**:切断该会话,开新会话严格按 SPEC 重来

---

## 最后的话

这套流程的核心是**把隐式共识变成显式规范**。SPEC 写得越细,AI 漂移空间越小。但规范也别写成天书,每条规则都要对应"违反时的具体症状",否则 AI 读不懂。

当你发现某条规则反复被违反,不是 AI 笨,是规则表达不够精确。**改 SPEC,不要改 AI**。
