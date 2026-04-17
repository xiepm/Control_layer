#pragma once

#include "han/types/aliases.hpp"

namespace han::types {

/**
 * @brief Placeholder rigid pose wrapper.
 */
class Pose {
 public:
  /**
   * @brief Constructs an identity pose placeholder.
   * @param None Placeholder parameter documentation.
   * @return Placeholder constructor return documentation.
   */
  Pose() noexcept;

  /**
   * @brief Constructs from a Pinocchio SE3 value.
   * @param value Placeholder pose value.
   * @return Placeholder constructor return documentation.
   */
  explicit Pose(const SE3& value) noexcept;

  /**
   * @brief Returns the stored SE3 value.
   * @param None Placeholder parameter documentation.
   * @return Placeholder SE3 value.
   */
  [[nodiscard]] const SE3& se3() const noexcept;

  /**
   * @brief Returns the inverse pose.
   * @param None Placeholder parameter documentation.
   * @return Placeholder inverse pose.
   */
  [[nodiscard]] Pose inverse() const;

 private:
  SE3 value_;
};

}  // namespace han::types
