#pragma once

#include <string_view>

namespace han::core {

/**
 * @brief Placeholder asynchronous logger facade.
 */
class Logger {
 public:
  /**
   * @brief Returns the process-wide logger instance.
   * @param None Placeholder parameter documentation.
   * @return Placeholder logger instance.
   */
  [[nodiscard]] static Logger& instance() noexcept;

  /**
   * @brief Writes a placeholder log message.
   * @param message Placeholder log message.
   * @return Placeholder return documentation.
   */
  void log(std::string_view message) noexcept;

  /**
   * @brief Flushes pending placeholder log messages.
   * @param None Placeholder parameter documentation.
   * @return Placeholder return documentation.
   */
  void flush() noexcept;
};

}  // namespace han::core
