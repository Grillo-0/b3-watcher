/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#include <iostream>

#include "list.hpp"
#include "net.hpp"

List::List()
    : Cmd({
	      .name = "list",
	      .description = "List available B3 stock symbols",
      }) {}

void List::run_impl(Ctx &ctx, cmd::ArgResult &&) {
	nlohmann::json res = nlohmann::json::parse(
		net::http_get(ctx.curl, "https://mfinance.com.br/api/v1/stocks/symbols"));

	for (auto &symbol : res) {
		std::cout << symbol.template get<std::string>() << "\n";
	}
}
