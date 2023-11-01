/*
 * @file Logger.hpp
 * @author eHonnef
 * @brief Small, simple and modular utility for formatting traces.
 * @date 01/11/2023
 *
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string_view>
#include <source_location>
#include <format>
#include <iostream>
#include <chrono>

namespace eho {
    enum class LogLevel {
        Trace = 0,
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
        None
    };

    template<LogLevel t_eLogLevel>
    static inline constexpr std::string_view LogLevelToString() {
        if constexpr (t_eLogLevel == LogLevel::Trace) {
            return "TRACE";
        } else if constexpr (t_eLogLevel == LogLevel::Debug) {
            return "DEBUG";
        } else if constexpr (t_eLogLevel == LogLevel::Info) {
            return "INFO";
        } else if constexpr (t_eLogLevel == LogLevel::Warning) {
            return "WARNING";
        } else if constexpr (t_eLogLevel == LogLevel::Error) {
            return "ERROR";
        } else if constexpr (t_eLogLevel == LogLevel::Fatal) {
            return "FATAL";
        } else {
            return "NONE";
        }
    }

    class CFormat {
    public:
        template<LogLevel t_eLogLevel, typename... Args>
        void Print(std::string_view strMessage, const std::source_location location, const Args &...args) {
            std::clog << FormatMessage<t_eLogLevel>(strMessage, location, args...) << '\n';
        }

    private:
        template<LogLevel t_eLogLevel, typename... Args>
        std::string
        FormatMessage(std::string_view strMessage, const std::source_location location, const Args &...args) {
            std::string_view strFileName{location.file_name()};
            return std::format("{} {:<11} :: {} :: {}",
                               GetTimeNow(),
                               std::format("[{}]", LogLevelToString<t_eLogLevel>()),
                               std::format("{}:{}[{}]",
                                           strFileName.substr(
                                                   strFileName.find_last_of('/', std::string::npos) == std::string::npos
                                                   ? 0
                                                   : strFileName.find_last_of('/', std::string::npos) + 1),
                                           location.function_name(),
                                           location.line()),
                               std::vformat(strMessage, std::make_format_args(args...)));
        }

        inline std::string GetTimeNow() {
            return std::format("{:%Y-%m-%d %H:%M:%S}",
                               std::chrono::round<std::chrono::microseconds>(std::chrono::system_clock::now()));
        }
    };

    template<LogLevel t_eLL, typename t_Formatter = CFormat>
    class CLogger {
    public:
        template<typename... Args>
        struct Trace {
            Trace(std::string_view strFormat, const Args &...args,
                  const std::source_location &Location = std::source_location::current()) {
                if constexpr (t_eLL <= LogLevel::Trace) {
                    CLogger::Log<LogLevel::Trace>(strFormat, Location, args...);
                }
            }
        };

        template<typename... Args>
        struct Debug {
            Debug(std::string_view strFormat, const Args &...args,
                  const std::source_location &Location = std::source_location::current()) {
                if constexpr (t_eLL <= LogLevel::Debug) {
                    CLogger::Log<LogLevel::Debug>(strFormat, Location, args...);
                }
            }
        };

        template<typename... Args>
        struct Info {
            Info(std::string_view strFormat, const Args &...args,
                 const std::source_location &Location = std::source_location::current()) {
                if constexpr (t_eLL <= LogLevel::Info) {
                    CLogger::Log<LogLevel::Info>(strFormat, Location, args...);
                }
            }
        };

        template<typename... Args>
        struct Warning {
            Warning(std::string_view strFormat, const Args &...args,
                    const std::source_location &Location = std::source_location::current()) {
                if constexpr (t_eLL <= LogLevel::Warning) {
                    CLogger::Log<LogLevel::Warning>(strFormat, Location, args...);
                }
            }
        };

        template<typename... Args>
        struct Error {
            Error(std::string_view strFormat, const Args &...args,
                  const std::source_location &Location = std::source_location::current()) {
                if constexpr (t_eLL <= LogLevel::Error) {
                    CLogger::Log<LogLevel::Error>(strFormat, Location, args...);
                }
            }
        };

        template<typename... Args>
        struct Fatal {
            Fatal(std::string_view strFormat, const Args &...args,
                  const std::source_location &Location = std::source_location::current()) {
                if constexpr (t_eLL <= LogLevel::Fatal) {
                    CLogger::Log<LogLevel::Fatal>(strFormat, Location, args...);
                }
            }
        };

        template<typename... Ts> Trace(std::string_view strFormat, Ts &&...args) -> Trace<Ts...>;
        template<typename... Ts> Debug(std::string_view strFormat, Ts &&...args) -> Debug<Ts...>;
        template<typename... Ts> Info(std::string_view strFormat, Ts &&...args) -> Info<Ts...>;
        template<typename... Ts> Warning(std::string_view strFormat, Ts &&...args) -> Warning<Ts...>;
        template<typename... Ts> Error(std::string_view strFormat, Ts &&...args) -> Error<Ts...>;
        template<typename... Ts> Fatal(std::string_view strFormat, Ts &&...args) -> Fatal<Ts...>;

    private:
        template<LogLevel t_eLogLevel, typename... Args>
        static void Log(std::string_view strMessage, const std::source_location location, const Args &...args) {
            static t_Formatter FormatterInstance{};
            FormatterInstance.template Print<t_eLogLevel>(strMessage, location, args...);
        }
    };
}
