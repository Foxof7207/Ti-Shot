#!/bin/bash
# tishot - capture d'écran d'une TI-Nspire via USB
# Copyright (C) 2026 Foxof7207
# SPDX-License-Identifier: GPL-2.0-or-later
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version. This program is distributed WITHOUT ANY WARRANTY; see LICENSE.
# Compile shot.c et installe tishot dans ~/.local (sans sudo, hors dépendances).
set -e
cd "$(dirname "$0")"
inc=$(pkg-config --cflags glib-2.0 ticalcs2 ticables2 tifiles2 ticonv 2>/dev/null) || {
  echo "Il manque les en-têtes: sudo dnf install tilibs-devel glib2-devel" >&2; exit 1; }
mkdir -p ~/.local/share/tishot ~/.local/bin
gcc $inc shot.c -o ~/.local/share/tishot/shot -lticalcs2 -lticables2 -ltifiles2 -lticonv
install -m755 tishot ~/.local/bin/tishot
echo "Installé. Lance: tishot"
