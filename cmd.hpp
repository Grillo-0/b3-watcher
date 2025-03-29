/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef __CMD_HPP__
#define __CMD_HPP__

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "ctx.hpp"

namespace cmd {

struct Arg {
	std::string name;
	std::string description;
};

struct ArgResult {
	std::unordered_map<std::string, std::string> args;
};

struct Cmd {
	struct Data {
		std::string name;
		std::string description;
		bool is_pure_meta_cmd = false;
		std::optional<std::string> father_cmd_prefix = {};
		std::vector<std::unique_ptr<Cmd>> subcmds = {};
		std::optional<size_t> alias_cmd_idx = {};
		std::vector<Arg> args = {};
	};
	Data data;

	Cmd(Data &&d) : data(std::move(d)) {};
	virtual ~Cmd() = default;

	void add_subcmd(std::unique_ptr<Cmd> subcmd, bool alias = false);

	void show_help();

	void run(Ctx &ctx);
	virtual void run_impl(Ctx &ctx, ArgResult &&args) = 0;

      private:
	std::optional<ArgResult> parse_args(std::vector<std::string_view> args);
	std::string get_usage_str(std::optional<std::string> prg_name = {});
};
} // namespace cmd

#endif // __CMD_HPP__
