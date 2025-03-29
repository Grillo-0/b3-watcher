/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef __NET_HPP__
#define __NET_HPP__

#include <string>

#include <curl/curl.h>

namespace net {

struct SmtpInfo {
	std::string server_name;
	std::string email;
	std::string password;
};

std::string http_get(CURL *curl, const std::string &url);

void send_email(CURL *curl, const SmtpInfo &smtp_info, const std::string to_email_addr,
		const std::string subject, const std::string message);

} // namespace net

#endif // __NET_HPP__
