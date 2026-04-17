# 提示词 99:自审与机械检查

> **使用场景**:每完成 2-3 个模块,或阶段 3 集成审查。
> **使用方式**:**开一个全新会话**,不要在已有实现会话里做自审。
> **成功标准**:AI 列出的违反项 = 0,或所有违反项已修复。

---

## 第一部分:机械检查(shell 命令)

在项目根目录运行这些命令。**任何一条有输出都视为违反**。

```bash
#!/bin/bash
# scripts/lint_check.sh

set -e
cd "$(dirname "$0")/.."

violations=0

check() {
  local rule="$1"
  local cmd="$2"
  local result
  result=$(eval "$cmd" 2>/dev/null || true)
  if [ -n "$result" ]; then
    echo "❌ [$rule] 违反:"
    echo "$result" | sed 's/^/    /'
    violations=$((violations + 1))
  else
    echo "✅ [$rule] PASS"
  fi
}

# R2: 禁止 get_ / set_ 前缀
check "R2-no-get-prefix" \
  "grep -rn 'get_[a-z]' include/ src/ --include='*.hpp' --include='*.cpp'"
check "R2-no-set-prefix" \
  "grep -rn 'set_[a-z]' include/ src/ --include='*.hpp' --include='*.cpp'"

# R4: public 头禁用 Eigen/Dense
check "R4-no-eigen-dense" \
  "grep -rn '#include <Eigen/Dense>' include/"

# R4: public 头禁用 using namespace
check "R4-no-using-namespace" \
  "grep -rn 'using namespace' include/"

# R6: kin/dyn 的 public 头禁止出现 pinocchio::
check "R6-no-pinocchio-in-kin-public" \
  "grep -rn 'pinocchio::' include/han/kin/"
check "R6-no-pinocchio-in-dyn-public" \
  "grep -rn 'pinocchio::' include/han/dyn/"

# R6: model 的 public 头禁止出现 pinocchio::Model(应 pimpl)
check "R6-no-pinocchio-model-in-public" \
  "grep -rn 'pinocchio::Model' include/han/model/"

# R1: kin 不依赖 dyn
check "R1-kin-not-depend-dyn" \
  "grep -rn '#include <han/dyn' include/han/kin/ src/kin/"

# R1: dyn 不依赖 kin
check "R1-dyn-not-depend-kin" \
  "grep -rn '#include <han/kin' include/han/dyn/ src/dyn/"

# R1: core 不依赖 Pinocchio
check "R1-core-not-depend-pinocchio" \
  "grep -rn 'pinocchio' include/han/core/ src/core/"

# R4: 每个 .hpp 必须有 #pragma once
check "R4-pragma-once-missing" \
  "for f in \$(find include -name '*.hpp'); do
     head -n 5 \"\$f\" | grep -q 'pragma once' || echo \"\$f: missing #pragma once\";
   done"

# R8: 禁用裸 new / delete(unique_ptr 等除外)
check "R8-no-raw-new" \
  "grep -rn '[^_a-zA-Z]new [A-Z]' src/ --include='*.cpp' | grep -v 'make_unique\\|make_shared'"

echo ""
if [ $violations -eq 0 ]; then
  echo "🎉 所有规则通过"
  exit 0
else
  echo "❌ 共 $violations 条违反,请修复"
  exit 1
fi
```

**用法**:

```bash
chmod +x scripts/lint_check.sh
./scripts/lint_check.sh
```

---

## 第二部分:AI 自审(开新会话)

### 复制以下内容给 AI

你是一个**严格的 C++ code reviewer**。我在开发机器人学库 `han`,项目规范见 `<SPEC>`,当前全部代码见 `<CODE>`。

```
<SPEC>
[粘贴 docs/SPEC.md 全文]
</SPEC>
```

```
<CODE>
[粘贴当前所有 .hpp 和 .cpp 文件内容,按目录树组织]

// ===== include/han/core/result.hpp =====
[文件内容]

// ===== include/han/core/error.hpp =====
[文件内容]

// ...依此类推
</CODE>
```

---

### 你的任务

按 SPEC 的 **R1 - R10** 逐条检查所有代码。

对每一条规则,输出:
- 如果**无违反**:`R_X: PASS`
- 如果**有违反**:列出每一个违反点,格式如下

```
R_X: FAIL
  违反 1:
    文件: include/han/kin/forward_kinematics.hpp
    行号: 第 23 行
    原文: `pinocchio::Model get_model() const;`
    违反原因: R2 禁止 get_ 前缀;R6 禁止在 kin public 头中出现 pinocchio::
    修复建议: 改为 `const Model& model() const;`,且应通过 model::RobotModel::Handle 访问
```

### 严格要求

- **不要夸奖**,不要写"这个设计很好"之类的话
- **不要总结**,不要写"总体来说代码质量不错"
- **不要回避**,每条规则都必须显式给出 PASS 或 FAIL
- **不要脑补**,如果某条规则在本项目中不适用(例如还没写到那层),写 `R_X: N/A(原因)`

### 额外检查项

除了 R1 - R10,额外检查:

1. **接口一致性**:同名概念在不同层是否用同一个类型?例如 `JointState` 是否全程一致?
2. **命名一致性**:同类操作是否命名一致?例如 `from_urdf` / `from_urdf_string` 是否都用 `from_` 前缀?
3. **错误码使用**:返回的 `ErrorCode` 是否贴切?是否有更合适的现有码可用?
4. **`noexcept` 覆盖**:有没有**应该**`noexcept` 但没标的函数?
5. **文档完整性**:public 函数是否都有 `@brief` / `@param` / `@return`?

每项同样用 `PASS` / `FAIL` + 具体违反点。

---

### 输出顺序

1. R1 → R2 → ... → R10
2. 额外检查 1 → 2 → 3 → 4 → 5
3. **汇总表**:

```
| 规则 | 状态 | 违反数 |
|------|------|--------|
| R1   | PASS | 0      |
| R2   | FAIL | 3      |
| ...  | ...  | ...    |
```

4. 最后列出 **Top 3 优先修复项**(按影响大小排序)

---

## 第三部分:修复流程

拿到自审结果后:

1. 按 Top 3 优先级,**一次只修一条规则**
2. 修复时,开回原实现会话或开新会话都可以,但必须贴:
   - 本条违反的所有具体位置
   - 修复后的完整代码(diff 格式)
3. 修完后重跑 `scripts/lint_check.sh`
4. 每修复一条,`git commit -m "fix: R_X violation"`

**避免**:让 AI "一次性修复所有违反"。它会偷改无关代码,难以审查。
