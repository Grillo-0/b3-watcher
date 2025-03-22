/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#include "ctx.hpp"

Ctx::Ctx(std::string_view prg_name, std::vector<std::string_view> args)
    : prg_name(prg_name), args(args) {}

Ctx::~Ctx() {}

Ctx Ctx::from_args(int argc, char **argv) {
	std::string_view prg_name = argv[0];

	std::vector<std::string_view> args;
	args.reserve(argc - 1);

	for (int i = 1; i < argc; i++) {
		args.emplace_back(argv[i]);
	}

	return Ctx(prg_name, args);
}
