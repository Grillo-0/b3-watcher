# B3 watcher

A CLI application for tracking B3 stocks that uses the [mfinace API][mfinace].

## Usage

```sh
$ b3-watcher help
Watch B3 stock prices

Usage: b3-watcher <COMMAND>

Commands:
  list:   List available B3 stock symbols
  info:   Get information about a B3 stock
  track:  Track the price of a stock and send emails if it crosses the sell/buy price
  help:   Show this help
```

## Commands

### `list`

```sh
$ b3-watcher list help
List available B3 stock symbols

Usage: b3-watcher list
   or: b3-watcher list <COMMAND>

Commands:
  help:  Show this help
```

### `info`

```sh
$ b3-watcher info help
Get information about a B3 stock

Usage: b3-watcher info <stock_symbol>
   or: b3-watcher info <COMMAND>

Arguments:
  stock_symbol:  B3 stock symbol

Commands:
  help:  Show this help
```

### `track`

>[!TIP]
> This is the default command, this means that you don't need to type
> `b3-watcher track`, just `b3-watcher` works.

```sh
$ b3-watcher track help
Track the price of a stock and send emails if it crosses the sell/buy price

Usage: b3-watcher track <stock_symbol> <sell_price> <buy_price>
   or: b3-watcher track <COMMAND>

Arguments:
  stock_symbol:  B3 stock symbol
  sell_price:    Minimum price to hold selling the stock
  buy_price:     Minimum price to hold buying the stock

Commands:
  help:  Show this help
```

## Configuration

A `config.json` file needs to be on the current working directory when executing
the application.

This configuration file will have some parameters needed by the application, you
can find an example configuration on
[config.json.example](./config.json.example)

The current configuration setting are:

- `to_email_addr`: The email address to send the messages sent by the `track`
  command
- `smtp`: SMTP email configuration to be able to send emails
    - `server_name`: SMTP server name
    - `email`: The email address that is going to be used to send the emails
    - `password`: The password for the email account

## Dependencies

>[!TIP]
> You only need to worry about installing [meson][]. During the build process,
> if [meson][] can't find any of the libs it should download and compile itself,
> no extra work needed.

- [meson][] (build system)
- [libcurl][] (lib for network communication)
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
[libcurl]: https://curl.se/libcurl/
[nlohmann-json]: https://github.com/nlohmann/json
[mfinace]: https://mfinance.com.br/swagger/index.html
