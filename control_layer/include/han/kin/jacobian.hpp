#pragma once

#include <string_view>

#include "han/core/realtime_guard.hpp"
#include "han/core/result.hpp"
#include "han/kin/forward_kinematics.hpp"
#include "han/model/robot_model.hpp"
#include "han/types/aliases.hpp"
#include "han/types/joint_state.hpp"

namespace han::kin {

/**
 * @brief Placeholder Jacobian frame selection.
 */
enum class JacobianFrame {
  kBody,
  kWorld,
  kSpatial,
};

/**
 * @brief Placeholder Jacobian API.
 */
class Jacobian {
 public:
  /**
   * @brief Computes a placeholder Jacobian matrix.
   * @param model Placeholder robot model.
   * @param joint_state Placeholder joint state input.
   * @param frame_name Placeholder frame identifier.
   * @param frame Placeholder Jacobian frame selection.
   * @param workspace Placeholder preallocated workspace.
   * @param realtime_tag Placeholder realtime tag.
   * @return Placeholder result containing a Jacobian matrix or an evaluation error.
   * @realtime-safe
   */
  [[nodiscard]] static han::core::Result<han::types::MatrixX> compute(
      const han::model::RobotModel& model,
      const han::types::JointState& joint_state,
      std::string_view frame_name,
      JacobianFrame frame,
      FkWorkspace& workspace,
      han::core::realtime_safe_t realtime_tag = {}) noexcept;
};

}  // namespace han::kin
