# B3 watcher

A CLI application for tracking B3 stocks

## Configuration

A `config.json` file needs to be on the current working directory when executing
the application.

This configuration file will have some parameters needed by the application, you
can find an example configuration on
[config.json.example](./config.json.example)

## Dependencies

>[!TIP]
> You only need to worry about installing [meson][]. During the build process,
> if [meson][] can't find any of the libs it should download and compile itself,
> no extra work needed.

- [meson][] (build system)
- [Nlohmann Json library][nlohmann-json] (lib for dealing with JSON)

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
[nlohmann-json]: https://github.com/nlohmann/json
