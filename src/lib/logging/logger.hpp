////////////////////////////////////////////////////////////////////////
// Crystal Server - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef USE_PRECOMPILED_HEADERS
	#include <fmt/format.h>
#endif

#define LOG_LEVEL_TRACE \
	std::string {       \
		"trace"         \
	}
#define LOG_LEVEL_DEBUG \
	std::string {       \
		"debug"         \
	}
#define LOG_LEVEL_INFO \
	std::string {      \
		"info"         \
	}
#define LOG_LEVEL_WARNING \
	std::string {         \
		"warning"         \
	}
#define LOG_LEVEL_ERROR \
	std::string {       \
		"error"         \
	}
#define LOG_LEVEL_CRITICAL \
	std::string {          \
		"critical"         \
	}

class Logger {
public:
	Logger() = default;
	virtual ~Logger() = default;

	// Ensures that we don't accidentally copy it
	Logger(const Logger &) = delete;
	virtual Logger &operator=(const Logger &) = delete;

	virtual void setLevel(const std::string &name) = 0;
	[[nodiscard]] virtual std::string getLevel() const = 0;
	virtual void log(const std::string &lvl, fmt::basic_string_view<char> msg) const = 0;

	template <typename... Args>
	void trace(const fmt::format_string<Args...> &fmt, Args &&... args) {
		trace(fmt::format(fmt, std::forward<Args>(args)...));
	}

	template <typename... Args>
	void debug(const fmt::format_string<Args...> &fmt, Args &&... args) {
		debug(fmt::format(fmt, std::forward<Args>(args)...));
	}

	template <typename... Args>
	void info(fmt::format_string<Args...> fmt, Args &&... args) {
		info(fmt::format(fmt, std::forward<Args>(args)...));
	}

	template <typename... Args>
	void warn(const fmt::format_string<Args...> &fmt, Args &&... args) {
		warn(fmt::format(fmt, std::forward<Args>(args)...));
	}

	template <typename... Args>
	void error(const fmt::format_string<Args...> fmt, Args &&... args) {
		error(fmt::format(fmt, std::forward<Args>(args)...));
	}

	template <typename... Args>
	void critical(const fmt::format_string<Args...> fmt, Args &&... args) {
		critical(fmt::format(fmt, std::forward<Args>(args)...));
	}

	template <typename T>
	void trace(const T &msg) {
		log(LOG_LEVEL_TRACE, msg);
	}

	template <typename T>
	void debug(const T &msg) {
		log(LOG_LEVEL_DEBUG, msg);
	}

	template <typename T>
	void info(const T &msg) {
		log(LOG_LEVEL_INFO, msg);
	}

	template <typename T>
	void warn(const T &msg) {
		log(LOG_LEVEL_WARNING, msg);
	}

	template <typename T>
	void error(const T &msg) {
		log(LOG_LEVEL_ERROR, msg);
	}

	template <typename T>
	void critical(const T &msg) {
		log(LOG_LEVEL_CRITICAL, msg);
	}
};
