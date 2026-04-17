#pragma once

namespace han::core {

/**
 * @brief Placeholder strongly typed angle in radians.
 */
class Radian {
 public:
  /**
   * @brief Constructs a radian value.
   * @param value Placeholder scalar value.
   * @return Placeholder constructor return documentation.
   */
  explicit Radian(double value) noexcept;

  /**
   * @brief Returns the stored scalar.
   * @param None Placeholder parameter documentation.
   * @return Placeholder scalar value.
   */
  [[nodiscard]] double value() const noexcept;

 private:
  double value_{0.0};
};

/**
 * @brief Placeholder strongly typed angle in degrees.
 */
class Degree {
 public:
  /**
   * @brief Constructs a degree value.
   * @param value Placeholder scalar value.
   * @return Placeholder constructor return documentation.
   */
  explicit Degree(double value) noexcept;

  /**
   * @brief Returns the stored scalar.
   * @param None Placeholder parameter documentation.
   * @return Placeholder scalar value.
   */
  [[nodiscard]] double value() const noexcept;

 private:
  double value_{0.0};
};

/**
 * @brief Placeholder strongly typed distance in meters.
 */
class Meter {
 public:
  /**
   * @brief Constructs a meter value.
   * @param value Placeholder scalar value.
   * @return Placeholder constructor return documentation.
   */
  explicit Meter(double value) noexcept;

  /**
   * @brief Returns the stored scalar.
   * @param None Placeholder parameter documentation.
   * @return Placeholder scalar value.
   */
  [[nodiscard]] double value() const noexcept;

 private:
  double value_{0.0};
};

}  // namespace han::core
