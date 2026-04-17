#pragma once

#include <string_view>

#include "han/core/realtime_guard.hpp"
#include "han/core/result.hpp"
#include "han/model/robot_model.hpp"
#include "han/types/joint_state.hpp"
#include "han/types/pose.hpp"

namespace han::kin {

/**
 * @brief Placeholder workspace for realtime forward kinematics.
 */
class FkWorkspace {
 public:
  /**
   * @brief Constructs an empty FK workspace placeholder.
   * @param None Placeholder parameter documentation.
   * @return Placeholder constructor return documentation.
   */
  FkWorkspace() noexcept;

  FkWorkspace(const FkWorkspace&) = delete;
  FkWorkspace& operator=(const FkWorkspace&) = delete;
  FkWorkspace(FkWorkspace&& other) noexcept;
  FkWorkspace& operator=(FkWorkspace&& other) noexcept;

  /**
   * @brief Destroys the placeholder FK workspace.
   * @param None Placeholder parameter documentation.
   * @return Placeholder destructor return documentation.
   */
  ~FkWorkspace();
};

/**
 * @brief Placeholder forward kinematics API.
 */
class ForwardKinematics {
 public:
  /**
   * @brief Computes a placeholder frame pose.
   * @param model Placeholder robot model.
   * @param joint_state Placeholder joint state input.
   * @param frame_name Placeholder frame identifier.
   * @param workspace Placeholder preallocated workspace.
   * @param realtime_tag Placeholder realtime tag.
   * @return Placeholder result containing a pose or an FK error.
   * @realtime-safe
   */
  [[nodiscard]] static han::core::Result<han::types::Pose> compute(
      const han::model::RobotModel& model,
      const han::types::JointState& joint_state,
      std::string_view frame_name,
      FkWorkspace& workspace,
      han::core::realtime_safe_t realtime_tag = {}) noexcept;
};

}  // namespace han::kin
