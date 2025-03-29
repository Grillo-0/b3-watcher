/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#include "cmd.hpp"
#include "ctx.hpp"

struct MainCmd : public cmd::Cmd {
	MainCmd()
	    : Cmd({
		      .name = "b3-watcher",
		      .description = "Watch B3 stock prices",
		      .is_pure_meta_cmd = true,
	      }) {}
	void run_impl(Ctx &, cmd::ArgResult &&) override {
		show_help();
	}
};

int main(int argc, char **argv) {
	curl_global_init(CURL_GLOBAL_DEFAULT);

	auto ctx = Ctx::from_args(argc, argv);

	MainCmd main_cmd;
	main_cmd.data.name = ctx.prg_name;

	main_cmd.run(ctx);

	curl_global_cleanup();
	return 0;
}
