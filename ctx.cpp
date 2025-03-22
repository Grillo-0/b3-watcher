/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#include <cstdlib>
#include <fstream>

#include "ctx.hpp"
#include "util.hpp"

Ctx::Ctx(std::string_view prg_name, std::vector<std::string_view> args)
    : prg_name(prg_name), args(args), config_filepath("config.json") {

	std::ifstream config_file(config_filepath);
	if (!config_file) {
		util::log(util::LOG_ERROR, "Could not open confile at {}",
			  config_filepath.string());
		exit(-1);
	}
	config = nlohmann::json::parse(config_file);

	curl = curl_easy_init();
}

Ctx::~Ctx() {
	curl_easy_cleanup(curl);
}

Ctx Ctx::from_args(int argc, char **argv) {
	std::string_view prg_name = argv[0];

	std::vector<std::string_view> args;
	args.reserve(argc - 1);

	for (int i = 1; i < argc; i++) {
		args.emplace_back(argv[i]);
	}

	return Ctx(prg_name, args);
}
