/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <format>
#include <iostream>
#include <sstream>

namespace util {

enum log_type {
	// Useful information for the user, thing that are not the inner working of the code
	LOG_INFO,
	// Useful information for the developer, thing that are the inner working of the code
	LOG_DEBUG,
	// Something has gone wrong
	LOG_ERROR,
};

template <typename... Args> void log(enum log_type type, std::string_view fmt, Args &&...args) {
	std::string log_tag;

	switch (type) {
	case LOG_INFO:
		log_tag = "[INFO]: ";
		break;
	case LOG_DEBUG:
		log_tag = "[DEBUG]: ";
		break;
	case LOG_ERROR:
		log_tag = "[ERROR]: ";
		break;
	}

	auto message = std::vformat(fmt, std::make_format_args(args...));

	std::istringstream stream(message);
	for (std::string line; std::getline(stream, line);) {
		std::cerr << log_tag << line << std::endl;
	}
}

} // namespace util
#endif // __UTILS_HPP__
