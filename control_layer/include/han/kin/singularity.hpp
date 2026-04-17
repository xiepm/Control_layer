#pragma once

#include <string_view>

#include "han/core/result.hpp"
#include "han/model/robot_model.hpp"
#include "han/types/aliases.hpp"
#include "han/types/joint_state.hpp"

namespace han::kin {

/**
 * @brief Placeholder singularity analysis API.
 */
class Singularity {
 public:
  /**
   * @brief Computes a placeholder manipulability measure.
   * @param model Placeholder robot model.
   * @param joint_state Placeholder joint state input.
   * @param frame_name Placeholder frame identifier.
   * @return Placeholder result containing a manipulability score or an analysis error.
   */
  [[nodiscard]] static han::core::Result<double> manipulability(
      const han::model::RobotModel& model,
      const han::types::JointState& joint_state,
      std::string_view frame_name);

  /**
   * @brief Computes a placeholder nearest singular direction.
   * @param model Placeholder robot model.
   * @param joint_state Placeholder joint state input.
   * @param frame_name Placeholder frame identifier.
   * @return Placeholder result containing a direction vector or an analysis error.
   */
  [[nodiscard]] static han::core::Result<han::types::VectorX> nearest_direction(
      const han::model::RobotModel& model,
      const han::types::JointState& joint_state,
      std::string_view frame_name);
};

}  // namespace han::kin
