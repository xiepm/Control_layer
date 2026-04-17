#pragma once

#include "han/types/aliases.hpp"

namespace han::types {

/**
 * @brief Placeholder twist wrapper.
 */
class Twist {
 public:
  /**
   * @brief Constructs an empty twist placeholder.
   * @param None Placeholder parameter documentation.
   * @return Placeholder constructor return documentation.
   */
  Twist() noexcept;

  /**
   * @brief Constructs from a Pinocchio motion value.
   * @param value Placeholder motion value.
   * @return Placeholder constructor return documentation.
   */
  explicit Twist(const Motion& value) noexcept;

  /**
   * @brief Returns the stored motion.
   * @param None Placeholder parameter documentation.
   * @return Placeholder motion value.
   */
  [[nodiscard]] const Motion& motion() const noexcept;

 private:
  Motion value_;
};

}  // namespace han::types
