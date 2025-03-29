#!/bin/env bash
#
# Copyright Arthur Grillo (c) 2025
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

set -xe

find . \( -name '*.cpp' -o -name '*.hpp' \) -exec clang-format -i {} \;
