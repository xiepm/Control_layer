#pragma once

#include "han/core/realtime_guard.hpp"
#include "han/core/result.hpp"
#include "han/model/robot_model.hpp"
#include "han/types/aliases.hpp"
#include "han/types/joint_state.hpp"
#include "han/types/wrench.hpp"

namespace han::dyn {

/**
 * @brief Placeholder external force observer.
 */
class ExtForceObserver {
 public:
  /**
   * @brief Placeholder observer options.
   */
  struct Options {
    double cutoff_frequency_hz{0.0};
  };

  /**
   * @brief Constructs a placeholder observer.
   * @param options Placeholder observer options.
   * @return Placeholder constructor return documentation.
   */
  explicit ExtForceObserver(Options options = {}) noexcept;

  /**
   * @brief Updates the placeholder observer state.
   * @param model Placeholder robot model.
   * @param joint_state Placeholder joint state input.
   * @param commanded_torque Placeholder commanded torque input.
   * @param realtime_tag Placeholder realtime tag.
   * @return Placeholder result containing an estimated wrench or an observer error.
   * @realtime-safe
   */
  [[nodiscard]] han::core::Result<han::types::Wrench> update(
      const han::model::RobotModel& model,
      const han::types::JointState& joint_state,
      const han::types::VectorX& commanded_torque,
      han::core::realtime_safe_t realtime_tag = {}) noexcept;

 private:
  Options options_{};
};

}  // namespace han::dyn
