# Segno

![segno](http://i.imgur.com/QnPEkWr.png)

## Build

### Dependencies

* `glfw3`
  * On Debian: `libglfw3-dev`
  * On ArchLinux: `glfw-x11` or `glfw-wayland`
* `guile`
  * On Debian: `guile-2.0-dev`
  * On ArchLinux: `guile`

And of course you need `gmake` and a C99 compiler.

### Compile

* `make info` will display building information
* `make segno` will compile program code
* `make clean` will remove the object files
* `make distclean` will remove the object files and the executable binary

The default target is `all`, which is an alias to the `segno` target.

## Usage

```
Usage ./segno: [-h] [-l]

optional arguments:
  -h, --help            show this help message and exit
  -l, --listen PORT     spawn a REPL server (e.g.: -l 1337)
```

## Emacs user?

1. Make sure [Geiser](https://github.com/jaor/geiser) is installed.
2. Run this software with the `--listen` parameter.
3. From Emacs run `M-x connect-to-guile`, then type `127.0.0.1` and finally
   the port you specified to the `--listen` parameter.
   
Now you can livecode right from your favorite editor.

## License

This project is licensed under the GNU General Public License v3.0 - see the
[LICENSE](LICENSE) file for details.
