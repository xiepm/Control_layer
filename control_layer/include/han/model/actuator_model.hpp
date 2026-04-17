#pragma once

#include <string>

namespace han::model {

/**
 * @brief Placeholder actuator model description.
 */
class ActuatorModel {
 public:
  /**
   * @brief Constructs an empty actuator model.
   * @param None Placeholder parameter documentation.
   * @return Placeholder constructor return documentation.
   */
  ActuatorModel() noexcept;

  /**
   * @brief Returns the actuator name.
   * @param None Placeholder parameter documentation.
   * @return Placeholder actuator name.
   */
  [[nodiscard]] const std::string& name() const noexcept;

  /**
   * @brief Returns the continuous torque limit.
   * @param None Placeholder parameter documentation.
   * @return Placeholder torque limit.
   */
  [[nodiscard]] double torque_limit() const noexcept;

 private:
  std::string name_;
  double torque_limit_{0.0};
};

}  // namespace han::model
