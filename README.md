# Checkerboard

## Dependencies

- cmake
- pthreads
- ncurses

## Compile

After unzipping.

```bash
cd build
cmake ..
make
```

## Running

Within project folder (no build folder).

### Server

```bash
bin/server <max games> [<port>]
```

### Client

```bash
bin/client [<ip>] [<port>]
```