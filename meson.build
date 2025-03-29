# Copyright Arthur Grillo (c) 2025
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

project(
  'b3-watcher',
  'cpp',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++20'
  ],
  license: 'Mozilla Public License 2.0',
  license_files: ['LICENSE'],
)

srcs = [
  'b3_watcher.cpp',
  'cmd.cpp',
  'ctx.cpp',
  'net.cpp',
]

deps = [
  dependency('libcurl'),
  dependency('nlohmann_json'),
]

exe = executable(
  'b3-watcher',
  srcs,
  install : true,
  dependencies: deps,
)
