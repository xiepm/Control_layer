#pragma once

#include "han/core/error.hpp"

namespace han::core {

/**
 * @brief Placeholder result type for fallible APIs.
 */
template <class T, class E = Error>
class Result {
 public:
  /**
   * @brief Constructs a successful result.
   * @param value Placeholder success value.
   * @return Placeholder successful result.
   */
  [[nodiscard]] static Result ok(T value);

  /**
   * @brief Constructs an error result.
   * @param error Placeholder error payload.
   * @return Placeholder error result.
   */
  [[nodiscard]] static Result err(E error);

  /**
   * @brief Reports whether the result contains a value.
   * @param None Placeholder parameter documentation.
   * @return True when a value is present.
   */
  [[nodiscard]] bool has_value() const noexcept;

  /**
   * @brief Returns the stored value.
   * @param None Placeholder parameter documentation.
   * @return Placeholder stored value.
   */
  [[nodiscard]] const T& value() const &;

  /**
   * @brief Returns the stored value.
   * @param None Placeholder parameter documentation.
   * @return Placeholder stored value.
   */
  [[nodiscard]] T& value() &;

  /**
   * @brief Moves the stored value.
   * @param None Placeholder parameter documentation.
   * @return Placeholder moved value.
   */
  [[nodiscard]] T&& value() &&;

  /**
   * @brief Returns the stored error.
   * @param None Placeholder parameter documentation.
   * @return Placeholder stored error.
   */
  [[nodiscard]] const E& error() const noexcept;
};

}  // namespace han::core
