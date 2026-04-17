#pragma once

#include "han/core/realtime_guard.hpp"
#include "han/core/result.hpp"
#include "han/model/robot_model.hpp"
#include "han/types/aliases.hpp"
#include "han/types/joint_state.hpp"

namespace han::dyn {

/**
 * @brief Computes placeholder recursive Newton-Euler torques.
 * @param model Placeholder robot model.
 * @param joint_state Placeholder joint state input.
 * @param joint_acceleration Placeholder joint acceleration input.
 * @param realtime_tag Placeholder realtime tag.
 * @return Placeholder result containing joint torques or a dynamics error.
 * @realtime-safe
 */
[[nodiscard]] han::core::Result<han::types::VectorX> recursive_newton_euler(
    const han::model::RobotModel& model,
    const han::types::JointState& joint_state,
    const han::types::VectorX& joint_acceleration,
    han::core::realtime_safe_t realtime_tag = {}) noexcept;

}  // namespace han::dyn
