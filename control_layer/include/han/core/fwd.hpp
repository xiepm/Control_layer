#pragma once

namespace han::core {

enum class ErrorCode;

class Error;

template <class T, class E = Error>
class Result;

class Logger;

class RealtimeGuard;

struct realtime_safe_t;

class Radian;
class Degree;
class Meter;

}  // namespace han::core
