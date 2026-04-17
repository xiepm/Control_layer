#pragma once

#include <cstdint>
#include <string>

namespace han::core {

/**
 * @brief Placeholder error codes for the han library.
 */
enum class ErrorCode : std::uint16_t {
  kOk = 0,
  kInvalidArgument,
  kOutOfRange,
  kNotInitialized,
  kModelMismatch,
  kDimensionMismatch,
  kUrdfParseError,
  kPresetNotFound,
  kIkDidNotConverge,
  kSingularConfiguration,
  kJointLimitViolation,
  kRealtimeViolation,
  kInternalError,
};

/**
 * @brief Placeholder error object for API boundaries.
 */
class Error {
 public:
  /**
   * @brief Constructs an empty error.
   */
  Error() noexcept;

  /**
   * @brief Constructs an error with code and message.
   * @param code Placeholder error code.
   * @param message Placeholder error message.
   * @return Placeholder constructor return documentation.
   */
  Error(ErrorCode code, std::string message) noexcept;

  /**
   * @brief Returns the error code.
   * @param None Placeholder parameter documentation.
   * @return Placeholder error code.
   */
  [[nodiscard]] ErrorCode code() const noexcept;

  /**
   * @brief Returns the error message.
   * @param None Placeholder parameter documentation.
   * @return Placeholder error message.
   */
  [[nodiscard]] const std::string& message() const noexcept;

 private:
  ErrorCode code_{ErrorCode::kOk};
  std::string message_;
};

}  // namespace han::core
