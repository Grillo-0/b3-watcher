/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef __LIST_HPP__
#define __LIST_HPP__

#include "cmd.hpp"

struct List : public cmd::Cmd {
	List();
	void run_impl(Ctx &ctx, cmd::ArgResult &&args) override;
};

#endif // __LIST_HPP__
