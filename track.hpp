/*
 * Copyright Arthur Grillo (c) 2025
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef __TRACK_HPP__
#define __TRACK_HPP__

#include "cmd.hpp"

struct Track : public cmd::Cmd {
	Track();
	void run_impl(Ctx &ctx, cmd::ArgResult &&args) override;
};

#endif // __TRACK_HPP__
