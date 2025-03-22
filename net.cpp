/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#include <chrono>

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

size_t curl_read_sv_callback(char *buffer, size_t size, size_t nitems, void *userdata) {
	auto real_size = size * nitems;
	auto *sv = static_cast<std::string_view *>(userdata);

	if (real_size > sv->size()) {
		real_size = sv->size();
	}

	sv->copy(buffer, real_size);
	sv->remove_prefix(real_size);

	return real_size;
}

std::string get_curent_time_for_email() {
	using namespace std::chrono;
	auto now = system_clock::now();
	return std::format("{:%a, %d %m %Y %H:%M:%S %z}", now);
}

std::string gen_message_id() {
	using namespace std::chrono;
	auto now = system_clock::now();
	auto epoch = system_clock::to_time_t(now);
	auto r = rand();
	return std::format("<{}-{}@b3-watcher>", epoch, r);
}

std::string build_email_payload(const SmtpInfo &smtp_info, const std::string &to_email,
				const std::string &subject, const std::string &message) {

	std::string payload;
	payload += "Date: " + get_curent_time_for_email() + "\r\n";
	payload += "To: " + to_email + "\r\n";
	payload += "From: " + smtp_info.email + "\r\n";
	payload += "Cc: \r\n";
	payload += "Message-ID: " + gen_message_id() + "\r\n";
	payload += "Subject: " + subject + "\r\n";
	payload += "\r\n";

	std::istringstream stream(message);

	for (std::string line; std::getline(stream, line);) {
		payload += line;
		payload += "\r\n";
	}

	return payload;
}

void send_email(CURL *curl, const SmtpInfo &smtp_info, const std::string to_email_addr,
		const std::string subject, const std::string message) {
	util::log(util::LOG_INFO, "Sending email to {}", to_email_addr);

	curl_easy_reset(curl);
	auto payload = build_email_payload(smtp_info, to_email_addr, subject, message);

	struct curl_slist *recipients = NULL;

	curl_easy_setopt(curl, CURLOPT_USERNAME, smtp_info.email.data());
	curl_easy_setopt(curl, CURLOPT_PASSWORD, smtp_info.password.data());
	curl_easy_setopt(curl, CURLOPT_URL, ("smtps://" + smtp_info.server_name).data());

	curl_easy_setopt(curl, CURLOPT_MAIL_FROM, smtp_info.email.data());
	recipients = curl_slist_append(recipients, to_email_addr.data());
	curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

	curl_easy_setopt(curl, CURLOPT_READFUNCTION, curl_read_sv_callback);

	auto payload_sv = std::string_view(payload);
	curl_easy_setopt(curl, CURLOPT_READDATA, &payload_sv);
	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	auto res = curl_easy_perform(curl);

	if (res != CURLE_OK) {
		util::log(util::LOG_ERROR, "Something went wrong sending email");
		util::log(util::LOG_DEBUG, "{}", curl_easy_strerror(res));
	}

	curl_slist_free_all(recipients);
}

} // namespace net
