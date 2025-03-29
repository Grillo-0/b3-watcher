/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <format>
#include <iostream>
#include <memory>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include "cmd.hpp"
#include "util.hpp"

namespace cmd {

void Cmd::add_subcmd(std::unique_ptr<Cmd> subcmd) {
	subcmd->data.father_cmd_prefix = std::string();
	if (data.father_cmd_prefix)
		*subcmd->data.father_cmd_prefix += *data.father_cmd_prefix + " ";
	*subcmd->data.father_cmd_prefix += data.name;

	data.subcmds.push_back(std::move(subcmd));
}

std::string Cmd::get_usage_str(std::optional<std::string> prg_name) {
	std::string res;

	auto print_usage_prefix = [this, &res, &prg_name]() {
		if (prg_name) {
			res += *prg_name;
		} else {
			if (data.father_cmd_prefix)
				res += *data.father_cmd_prefix + " ";

			res += data.name;
		}
	};

	print_usage_prefix();

	if (!data.args.empty()) {
		for (const auto &a : data.args) {
			res += std::format(" <{}>", a.name);
		}
	}

	if (!data.is_pure_meta_cmd) {
		res += "\n   or: ";
		print_usage_prefix();
	}

	res += " <COMMAND>";

	return res;
}

void show_args(std::vector<Arg> args) {
	int max_arg_len = std::ranges::max(args | std::views::transform(&Arg::name) |
					   std::views::transform(&std::string::length));

	for (const auto &a : args) {
		std::cout << std::format("  {:<{}}  {}\n", a.name + ':', max_arg_len + 1,
					 a.description);
	}
}

void Cmd::show_help() {
	std::cout << data.description << "\n\n";

	std::cout << std::format("Usage: {}\n", get_usage_str());

	std::vector<Arg> args(data.args);
	if (!args.empty()) {
		std::cout << "\n";

		std::cout << "Arguments:\n";
		show_args(args);
	}

	std::cout << "\n";
	std::cout << "Commands:\n";
	size_t max_subcmd_len = sizeof("help") - 1;
	if (!data.subcmds.empty()) {

		max_subcmd_len = std::max(
			max_subcmd_len,
			std::ranges::max(data.subcmds |
					 std::views::transform([](const std::unique_ptr<Cmd> &cmd) {
						 return cmd->data.name;
					 }) |
					 std::views::transform(&std::string::length)));

		for (const auto &c : data.subcmds) {
			std::cout << std::format("  {:<{}}  {}\n", c->data.name + ':',
						 max_subcmd_len + 1, c->data.description);
		}
	}
	std::cout << std::format("  {:<{}}  {}\n", "help:", max_subcmd_len + 1, "Show this help");
}

std::optional<ArgResult> Cmd::parse_args(std::vector<std::string_view> args) {
	ArgResult res;
	size_t args_i = 0;
	for (auto a : args) {
		res.args.emplace(data.args[args_i].name, a);
		args_i++;
	}

	if (args_i < data.args.size()) {
		util::log(util::LOG_ERROR, "Wrong number of arguments");
		return {};
	}

	return res;
}

void Cmd::run(Ctx &ctx) {
	auto run_cmd = [this](Ctx &ctx) {
		auto args = parse_args(ctx.args);

		if (!args) {
			show_help();
			exit(-1);
		}

		run_impl(ctx, std::move(*args));
	};

	if (ctx.args.empty()) {
		util::log(util::LOG_DEBUG, "Running cmd {} with no args", data.name);
		run_cmd(ctx);
		return;
	}

	std::string_view subcmd = ctx.args[0];

	if (subcmd == "help") {
		show_help();
		return;
	}

	if (const auto cmd = std::ranges::find(
		    data.subcmds, subcmd,
		    [](const std::unique_ptr<Cmd> &cmd) { return cmd->data.name; });
	    cmd != data.subcmds.end()) {
		util::log(util::LOG_DEBUG, "Found subcmd {}", subcmd);
		ctx.args.erase(ctx.args.begin());
		(*cmd)->run(ctx);
	} else {
		util::log(util::LOG_DEBUG, "Running cmd {} with args", data.name);
		run_cmd(ctx);
	}
}
} // namespace cmd
