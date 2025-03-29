/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef __INFO_HPP__
#define __INFO_HPP__

#include "cmd.hpp"

struct Info : public cmd::Cmd {
	Info();
	void run_impl(Ctx &ctx, cmd::ArgResult &&args) override;
};

#endif // __INFO_HPP__
