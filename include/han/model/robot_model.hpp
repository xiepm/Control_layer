#pragma once

#include <cstddef>
#include <memory>
#include <string_view>

#include "han/core/result.hpp"

namespace han::model {

/**
 * @brief Placeholder immutable robot model facade.
 */
class RobotModel {
 public:
  class Handle;

  /**
   * @brief Creates a robot model from a URDF file.
   * @param urdf_path Placeholder URDF path.
   * @return Placeholder result containing a robot model or a loading error.
   */
  [[nodiscard]] static han::core::Result<RobotModel> from_urdf(std::string_view urdf_path);

  /**
   * @brief Creates a robot model from a URDF string.
   * @param urdf_xml Placeholder URDF XML text.
   * @return Placeholder result containing a robot model or a parsing error.
   */
  [[nodiscard]] static han::core::Result<RobotModel> from_urdf_string(std::string_view urdf_xml);

  /**
   * @brief Creates a robot model from a preset registry entry.
   * @param preset_name Placeholder preset name.
   * @return Placeholder result containing a robot model or a preset lookup error.
   */
  [[nodiscard]] static han::core::Result<RobotModel> from_preset(std::string_view preset_name);

  /**
   * @brief Constructs an empty robot model placeholder.
   * @param None Placeholder parameter documentation.
   * @return Placeholder constructor return documentation.
   */
  RobotModel() noexcept;

  RobotModel(const RobotModel&) = delete;
  RobotModel& operator=(const RobotModel&) = delete;
  RobotModel(RobotModel&& other) noexcept;
  RobotModel& operator=(RobotModel&& other) noexcept;

  /**
   * @brief Destroys the placeholder robot model.
   * @param None Placeholder parameter documentation.
   * @return Placeholder destructor return documentation.
   */
  ~RobotModel();

  /**
   * @brief Returns the model degrees of freedom.
   * @param None Placeholder parameter documentation.
   * @return Placeholder degree-of-freedom count.
   */
  [[nodiscard]] std::size_t dof() const noexcept;

  /**
   * @brief Returns a semi-transparent internal handle.
   * @param None Placeholder parameter documentation.
   * @return Placeholder model handle.
   */
  [[nodiscard]] Handle handle() const noexcept;

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace han::model
