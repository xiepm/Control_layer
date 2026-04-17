#pragma once

#include "han/core/realtime_guard.hpp"
#include "han/core/result.hpp"
#include "han/model/robot_model.hpp"
#include "han/types/aliases.hpp"
#include "han/types/joint_state.hpp"

namespace han::dyn {

/**
 * @brief Computes a placeholder joint-space mass matrix.
 * @param model Placeholder robot model.
 * @param joint_state Placeholder joint state input.
 * @param realtime_tag Placeholder realtime tag.
 * @return Placeholder result containing a mass matrix or a CRBA error.
 * @realtime-safe
 */
[[nodiscard]] han::core::Result<han::types::MatrixX> mass_matrix(
    const han::model::RobotModel& model,
    const han::types::JointState& joint_state,
    han::core::realtime_safe_t realtime_tag = {}) noexcept;

}  // namespace han::dyn
