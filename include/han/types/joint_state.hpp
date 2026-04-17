#pragma once

#include <cstddef>

#include "han/types/aliases.hpp"

namespace han::types {

/**
 * @brief Placeholder semantic joint state container.
 */
class JointState {
 public:
  /**
   * @brief Constructs an empty joint state.
   * @param None Placeholder parameter documentation.
   * @return Placeholder constructor return documentation.
   */
  JointState() noexcept;

  /**
   * @brief Returns the configured degrees of freedom.
   * @param None Placeholder parameter documentation.
   * @return Placeholder degree-of-freedom count.
   */
  [[nodiscard]] std::size_t dof() const noexcept;

  /**
   * @brief Returns the joint positions.
   * @param None Placeholder parameter documentation.
   * @return Placeholder joint positions.
   */
  [[nodiscard]] const VectorX& position() const noexcept;

  /**
   * @brief Returns the joint velocities.
   * @param None Placeholder parameter documentation.
   * @return Placeholder joint velocities.
   */
  [[nodiscard]] const VectorX& velocity() const noexcept;

  /**
   * @brief Returns the joint efforts.
   * @param None Placeholder parameter documentation.
   * @return Placeholder joint efforts.
   */
  [[nodiscard]] const VectorX& effort() const noexcept;

 private:
  std::size_t dof_{0};
  VectorX position_;
  VectorX velocity_;
  VectorX effort_;
};

}  // namespace han::types
