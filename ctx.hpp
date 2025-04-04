/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef __CTX_H__
#define __CTX_H__

#include <string>
#include <vector>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

struct Ctx {
	std::string prg_name;
	std::vector<std::string_view> args;
	std::filesystem::path config_filepath;
	nlohmann::json config;

	CURL *curl;

	Ctx(std::string_view prg_name, std::vector<std::string_view> args);
	~Ctx();

	static Ctx from_args(int argc, char **argv);
};

#endif // __CTX_H__
