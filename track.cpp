/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#include <thread>

#include "net.hpp"
#include "track.hpp"
#include "util.hpp"

Track::Track()
    : Cmd({.name = "track",
	   .description =
		   "Track the price of a stock and send emails if it crosses the sell/buy price",
	   .args = {
		   {.name = "stock_symbol", .description = "B3 stock symbol"},
		   {.name = "sell_price", .description = "Minimum price to hold selling the stock"},
		   {.name = "buy_price", .description = "Minimum price to hold buying the stock"},
	   }}) {}

std::optional<float> get_current_stock_price(CURL *curl, std::string_view stock_symbol) {
	util::log(util::LOG_INFO, "Getting current stock price for {}", stock_symbol);

	auto url = std::format("https://mfinance.com.br/api/v1/stocks/{}", stock_symbol);
	auto result_str = net::http_get(curl, url);
	auto json = nlohmann::json::parse(result_str);

	if (!json.contains("lastPrice")) {
		util::log(util::LOG_ERROR, "Could not get {}'s last price from {}", stock_symbol,
			  url);
		return {};
	}

	return json["lastPrice"];
}

void Track::run_impl(Ctx &ctx, cmd::ArgResult &&args) {
	std::string_view stock_symbol = args.args["stock_symbol"];

	float sell_price = std::stof(args.args["sell_price"]);
	float buy_price = std::stof((args.args["buy_price"]));

	std::string to_email_addr = ctx.config["to_email_addr"];

	net::SmtpInfo smtp_info = {
		.server_name = ctx.config["smtp"]["server_name"],
		.email = ctx.config["smtp"]["email"],
		.password = ctx.config["smtp"]["password"],
	};

	while (true) {
		using namespace std::chrono_literals;
		auto curr_price_opt = get_current_stock_price(ctx.curl, stock_symbol);

		if (!curr_price_opt)
			continue;

		float curr_price = curr_price_opt.value();

		util::log(util::LOG_INFO, "Current price: {}", curr_price);

		if (curr_price <= buy_price) {
			auto subject = std::format("[B3-WATCHER] Buy {} stock!", stock_symbol);
			auto message = std::format("The stock {} is bellow the buy price of "
						   "{:.2f}, now it is at {:.2f}, buy now!",
						   stock_symbol, buy_price, curr_price);

			util::log(util::LOG_INFO, "{}", message);
			net::send_email(ctx.curl, smtp_info, to_email_addr, subject, message);
		}

		if (curr_price >= sell_price) {
			auto subject = std::format("[B3-WATCHER] Sell {} stock!", stock_symbol);
			auto message = std::format("The stock {} is above the sell price of "
						   "{:.2f}, now it is at {:.2f}, sell now!",
						   stock_symbol, sell_price, curr_price);
			util::log(util::LOG_INFO, "{}", message);

			net::send_email(ctx.curl, smtp_info, to_email_addr, subject, message);
		}

		std::this_thread::sleep_for(15min);
	}
}
