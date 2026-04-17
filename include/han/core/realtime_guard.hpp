#pragma once

namespace han::core {

/**
 * @brief Placeholder tag for realtime-safe overloads.
 */
struct realtime_safe_t {};

/**
 * @brief Placeholder realtime scope guard.
 */
class RealtimeGuard {
 public:
  /**
   * @brief Enters a placeholder realtime-safe scope.
   * @param None Placeholder parameter documentation.
   * @return Placeholder constructor return documentation.
   */
  RealtimeGuard() noexcept;

  /**
   * @brief Leaves a placeholder realtime-safe scope.
   * @param None Placeholder parameter documentation.
   * @return Placeholder destructor return documentation.
   */
  ~RealtimeGuard() noexcept;
};

}  // namespace han::core
