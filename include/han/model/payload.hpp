#pragma once

#include "han/types/pose.hpp"

namespace han::model {

/**
 * @brief Placeholder payload description.
 */
class Payload {
 public:
  /**
   * @brief Constructs an empty payload.
   * @param None Placeholder parameter documentation.
   * @return Placeholder constructor return documentation.
   */
  Payload() noexcept;

  /**
   * @brief Returns the payload mass.
   * @param None Placeholder parameter documentation.
   * @return Placeholder payload mass.
   */
  [[nodiscard]] double mass() const noexcept;

  /**
   * @brief Returns the payload pose.
   * @param None Placeholder parameter documentation.
   * @return Placeholder payload pose.
   */
  [[nodiscard]] const han::types::Pose& pose() const noexcept;

 private:
  double mass_{0.0};
  han::types::Pose pose_;
};

}  // namespace han::model
