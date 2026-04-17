#pragma once

#include <span>
#include <string_view>

#include "han/core/result.hpp"
#include "han/model/robot_model.hpp"

namespace han::model {

/**
 * @brief Placeholder preset registry facade.
 */
class PresetRegistry {
 public:
  /**
   * @brief Returns the available preset names.
   * @param None Placeholder parameter documentation.
   * @return Placeholder preset name list.
   */
  [[nodiscard]] static std::span<const std::string_view> names() noexcept;

  /**
   * @brief Loads a robot model from a preset entry.
   * @param preset_name Placeholder preset name.
   * @return Placeholder result containing a robot model or a preset lookup error.
   */
  [[nodiscard]] static han::core::Result<RobotModel> load(std::string_view preset_name);
};

}  // namespace han::model
