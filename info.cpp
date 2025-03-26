/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#include <format>
#include <iostream>

#include "info.hpp"
#include "net.hpp"
#include "util.hpp"

Info::Info()
    : Cmd({
	      .name = "info",
	      .description = "Get information about a B3 stock",
	      .args =
		      {
			      {.name = "stock_symbol", .description = "B3 stock symbol"},
		      },
      }) {}

void list_symbols(const Ctx &ctx) {
	nlohmann::json res = nlohmann::json::parse(
		net::http_get(ctx.curl, "https://mfinance.com.br/api/v1/stocks/symbols"));

	for (auto &symbol : res) {
		std::cout << symbol.template get<std::string>() << "\n";
	}
};

void Info::run_impl(Ctx &ctx, cmd::ArgResult &&args) {
	std::string_view stock_symbol = args.args["stock_symbol"];

	nlohmann::json res = nlohmann::json::parse(net::http_get(
		ctx.curl, std::format("https://mfinance.com.br/api/v1/stocks/{}", stock_symbol)));

	auto print_info_entry = [&res, &stock_symbol](std::string display_name,
						      std::string entry_name) {
		if (res.contains(entry_name)) {
			std::string value;
			if (res[entry_name].is_string())
				value = res[entry_name].get<std::string>();
			else
				value = res[entry_name].dump();

			std::cout << std::format("{:<26}{}\n", display_name + ':', value);
		} else {
			util::log(util::LOG_DEBUG, "Could not get '{}' from res", entry_name);
			util::log(util::LOG_ERROR, "Could not get information for {}",
				  stock_symbol);
			exit(-1);
		}
	};

	std::cout << "Stock Overview:" << "\n\n";
	print_info_entry("Symbol", "symbol");
	print_info_entry("Name", "name");
	print_info_entry("Sector", "sector");
	print_info_entry("Sub-Sector", "subSector");
	print_info_entry("Segment", "segment");
	std::cout << "\n\n" << "Market Data:" << "\n\n";
	print_info_entry("Last Price", "lastPrice");
	print_info_entry("Closing Price", "closingPrice");
	print_info_entry("Change", "change");
	print_info_entry("Open Price", "priceOpen");
	print_info_entry("Day High", "high");
	print_info_entry("Day Low", "low");
	print_info_entry("52-Week High", "lastYearHigh");
	print_info_entry("52-Week Low", "lastYearLow");
	std::cout << "\n\n" << "Volume & Liquidity:" << "\n\n";
	print_info_entry("Volume", "volume");
	print_info_entry("Avg. Volume", "volumeAvg");
	std::cout << "\n\n" << "Financial Health:" << "\n\n";
	print_info_entry("Market Cap", "marketCap");
	print_info_entry("Shares Outstanding", "shares");
	print_info_entry("EPS (Earnings Per Share)", "eps");
	print_info_entry("P/E Ratio", "pe");
	print_info_entry("Dividend Yield", "dividendYield");
}
