/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#include "net.hpp"
#include "util.hpp"

namespace net {

size_t curl_str_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
	auto real_size = size * nmemb;
	auto *return_string = static_cast<std::string *>(userdata);
	return_string->append(ptr, real_size);
	return real_size;
}

std::string http_get(CURL *curl, const std::string &url) {
	util::log(util::LOG_DEBUG, "Doing HTTP GET to {}", url);
	curl_easy_reset(curl);

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_str_write_callback);

	std::string ret_str;

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ret_str);

	auto res = curl_easy_perform(curl);

	if (res != CURLE_OK) {
		util::log(util::LOG_ERROR, "HTTP GET went wrong");
		util::log(util::LOG_DEBUG, "{}", curl_easy_strerror(res));
	}

	return ret_str;
}
} // namespace net
