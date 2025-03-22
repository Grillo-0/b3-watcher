/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#include "ctx.hpp"

int main(int argc, char **argv) {
	curl_global_init(CURL_GLOBAL_DEFAULT);

	auto ctx = Ctx::from_args(argc, argv);

	curl_global_cleanup();
	return 0;
}
