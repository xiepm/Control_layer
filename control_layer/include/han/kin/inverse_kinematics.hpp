#pragma once

#include <cstddef>
#include <string_view>

#include "han/core/result.hpp"
#include "han/model/robot_model.hpp"
#include "han/types/joint_state.hpp"
#include "han/types/pose.hpp"

namespace han::kin {

/**
 * @brief Placeholder iterative inverse kinematics solver.
 */
class InverseKinematics {
 public:
  /**
   * @brief Placeholder solver options.
   */
  struct Options {
    std::size_t max_iterations{0};
    double tolerance{0.0};
  };

  /**
   * @brief Constructs an inverse kinematics solver.
   * @param options Placeholder solver options.
   * @return Placeholder constructor return documentation.
   */
  explicit InverseKinematics(Options options = {}) noexcept;

  /**
   * @brief Solves a placeholder IK problem.
   * @param model Placeholder robot model.
   * @param seed_state Placeholder initial joint state.
   * @param frame_name Placeholder frame identifier.
   * @param target_pose Placeholder target pose.
   * @return Placeholder result containing a joint state or a convergence error.
   * @throws Placeholder documentation for internally handled third-party exceptions.
   */
  [[nodiscard]] han::core::Result<han::types::JointState> solve(
      const han::model::RobotModel& model,
      const han::types::JointState& seed_state,
      std::string_view frame_name,
      const han::types::Pose& target_pose) const;

 private:
  Options options_{};
};

}  // namespace han::kin
