# tishot

Capture d'écran en une commande d'une **TI-Nspire** branchée en USB, sous Linux (testé sur Fedora 44).
Le résultat est un PNG 640×480 enregistré dans `~/Pictures`.

```
$ tishot
/home/vous/Pictures/ti-20261008-140628.png
$ tishot mon-ecran.png      # nom de fichier personnalisé
```

## Installation (Fedora)

```bash
# 1. TiLP2 (installe aussi les bibliothèques libti* nécessaires)
sudo dnf install tilp

# 2. Dépendances de compilation + Python Pillow
sudo dnf install gcc pkgconf-pkg-config tilibs-devel glib2-devel python3-pillow

# 3. Compiler et installer
git clone https://github.com/Foxof7207/tishot.git
cd tishot
./install.sh
```

`~/.local/bin` doit être dans votre `PATH` (c'est le cas par défaut sur Fedora).

Ensuite : branchez la calculatrice, allumez-la, lancez `tishot`.

## Comment ça marche

`shot.c` utilise `libticalcs2` / `libticables2` (la bibliothèque derrière TiLP) pour ouvrir
le câble USB, demander l'écran à la calculatrice (`ticalcs_calc_recv_screen_rgb888`) et écrire
un fichier PPM. Le script `tishot` le convertit en PNG avec Pillow.
TiLP lui‑même est une interface graphique sans mode capture en ligne de commande, d'où ce petit programme.

## Dépannage

- **« Échec »** : calculatrice éteinte/débranchée, ou ouverte dans un autre logiciel
  (TiLP, TI-Nspire CX Student Software…) qui occupe l'USB (`Resource busy`).
- Si l'accès USB est refusé, vérifiez que les règles udev de `libticables` sont installées
  (`/usr/lib/udev/rules.d/69-libticables.rules`, fournies par le paquet Fedora).
- Autres modèles : dans `shot.c`, changez `CALC_NSPIRE` et `CABLE_USB` (non testé).

## Crédits

- **[TiLP / tilibs](http://lpg.ticalc.org/prj_tilp)** — `libticalcs2`, `libticables2`, `libtifiles2`, `libticonv` et TiLP2, qui rendent
  possible la communication avec les calculatrices TI (équipe **LPG**, *ticalc.org Linux Program Group*). Code source : <https://github.com/debrouxl/tilibs>. Auteurs, d'après le fichier `AUTHORS` du projet :
  - [Lionel Debroux](https://github.com/debrouxl) — mainteneur depuis 2009
  - Romain Liévin (« roms ») — [créateur de TiLP](http://lpg.ticalc.org/prj_tilp), mainteneur 1999–2009, développeur principal. Décédé le 10 février 2025
    ([hommage sur LinuxFr.org](https://linuxfr.org/users/illwieckz/journaux/deces-de-romain-lievin-auteur-de-tilp-et-acteur-incontournable-de-la-scene-ti-sous-linux))
  - [Julien Blache](https://github.com/jblache) — port Mac OS X, paquet Debian, premier support libusb
  - [Tijl Coosemans](https://github.com/TijlCoosemans) — port BSD, concepts de `ticables-2`
  - [Kevin Kofler](https://github.com/kkofler) — améliorations diverses, paquets Fedora
  - Benjamin Moody (« FloppusMaximus ») — [projet TilEm](http://lpg.ticalc.org/prj_tilem/index.html), jeux de caractères TI-8x, support TI-Z80
  - Jesse Palmer (« jp3d ») — icônes ; Tyler Cassidy (« tylerc ») — gestionnaire de groupes (GFM)
- **Mainteneurs Fedora** des paquets `tilp` et `tilibs` (installation et en-têtes de développement).
- **Claude Code** (Anthropic, modèle Claude Sonnet 5.5) — a écrit le programme et les scripts à la demande de l'auteur.
- **Foxof7207** — idée, matériel de test et assemblage.

## Licence

GPL-2.0-or-later, comme les bibliothèques tilibs (GPL version 2 ou ultérieure) auxquelles le programme est lié. Le texte de la licence (GPL v2) est dans [LICENSE](LICENSE) ; chaque fichier source porte l'en-tête « version 2 ou, à votre choix, toute version ultérieure ».
