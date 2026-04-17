#pragma once

#include "han/types/aliases.hpp"

namespace han::types {

/**
 * @brief Placeholder wrench wrapper.
 */
class Wrench {
 public:
  /**
   * @brief Constructs an empty wrench placeholder.
   * @param None Placeholder parameter documentation.
   * @return Placeholder constructor return documentation.
   */
  Wrench() noexcept;

  /**
   * @brief Constructs from a Pinocchio force value.
   * @param value Placeholder force value.
   * @return Placeholder constructor return documentation.
   */
  explicit Wrench(const Force& value) noexcept;

  /**
   * @brief Returns the stored force.
   * @param None Placeholder parameter documentation.
   * @return Placeholder force value.
   */
  [[nodiscard]] const Force& force() const noexcept;

 private:
  Force value_;
};

}  // namespace han::types
