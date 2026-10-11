# tishot

Take a screenshot of a **TI-Nspire** plugged in over USB with a single command, on Linux (tested on Fedora 44).
You get a 640×480 PNG saved in `~/Pictures`.

```
$ tishot
/home/you/Pictures/ti-20261008-140628.png
$ tishot my-screen.png      # custom file name
```

## Installation (Fedora)

```bash
# 1. TiLP2 (also installs the libti* libraries you need)
sudo dnf install tilp

# 2. Build dependencies + Python Pillow
sudo dnf install gcc pkgconf-pkg-config tilibs-devel glib2-devel python3-pillow

# 3. Build and install
git clone https://github.com/Foxof7207/tishot.git
cd tishot
./install.sh
```

Make sure `~/.local/bin` is in your `PATH` (it is by default on Fedora).

Then plug in your calculator, turn it on, and run `tishot`.

## How it works

`shot.c` uses `libticalcs2` / `libticables2` (the libraries behind TiLP) to open
the USB cable, ask the calculator for its screen (`ticalcs_calc_recv_screen_rgb888`), and write
a PPM file. The `tishot` script then converts it to PNG with Pillow.
TiLP itself is a graphical app with no command-line screenshot mode, which is why this small program exists.

## Troubleshooting

- **"Échec" (failure)**: the calculator is off or unplugged, or another program
  (TiLP, TI-Nspire CX Student Software…) is using the USB connection (`Resource busy`).
- If USB access is denied, check that the `libticables` udev rules are installed
  (`/usr/lib/udev/rules.d/69-libticables.rules`, provided by the Fedora package).
- Other models: in `shot.c`, change `CALC_NSPIRE` and `CABLE_USB` (untested).

## Credits

- **[TiLP / tilibs](http://lpg.ticalc.org/prj_tilp)** — `libticalcs2`, `libticables2`, `libtifiles2`, `libticonv` and TiLP2, which make
  it possible to talk to TI calculators (by the **LPG** team, the *ticalc.org Linux Program Group*). Source code: <https://github.com/debrouxl/tilibs>. Authors, according to the project's `AUTHORS` file:
  - [Lionel Debroux](https://github.com/debrouxl) — maintainer since 2009
  - Romain Liévin ("roms") — [creator of TiLP](http://lpg.ticalc.org/prj_tilp), maintainer 1999–2009, lead developer. Passed away on February 10, 2025
    ([tribute on LinuxFr.org](https://linuxfr.org/users/illwieckz/journaux/deces-de-romain-lievin-auteur-de-tilp-et-acteur-incontournable-de-la-scene-ti-sous-linux), in French)
  - [Julien Blache](https://github.com/jblache) — Mac OS X port, Debian package, first libusb support
  - [Tijl Coosemans](https://github.com/TijlCoosemans) — BSD port, concepts behind `ticables-2`
  - [Kevin Kofler](https://github.com/kkofler) — various improvements, Fedora packages
  - Benjamin Moody ("FloppusMaximus") — [TilEm project](http://lpg.ticalc.org/prj_tilem/index.html), TI-8x character sets, TI-Z80 support
  - Jesse Palmer ("jp3d") — icons; Tyler Cassidy ("tylerc") — group manager (GFM)
- **Fedora maintainers** of the `tilp` and `tilibs` packages (installation and development headers).
- **Claude Code** (Anthropic, Claude Sonnet 5.5 model) — wrote the program and scripts at the author's request.
- **Foxof7207** — idea, testing hardware, and putting it all together.

## License

GPL-2.0-or-later, the same as the tilibs libraries (GPL version 2 or later) that the program links against. The license text (GPL v2) is in [LICENSE](LICENSE); each source file carries the header "version 2 or, at your option, any later version".
