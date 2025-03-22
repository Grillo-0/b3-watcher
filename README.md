# B3 watcher

A CLI application for tracking B3 stocks

## Dependencies

- [meson][] (build system)

## How to build it

This program uses [meson][] for its build system, to build it follow the
instructions below:

Clone the repo and enter the created directory.

```sh
git clone https://github.com/Grillo-0/b3-watcher.git && cd b3-watcher
```

Create a build directory.

```sh
meson setup build
```

Compile the application.

```sh
meson compile -C build
```

After that, you can directly run the application compiled inside the build
directory.

```sh
./build/b3-watcher <arguments>
```

If you want the application in your PATH, you can install it with command below.

```sh
meson install -C build
```

[meson]: https://mesonbuild.com/
