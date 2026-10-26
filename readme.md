# ProjetC : gestionnaire de formes en C

Programme en C, utilisable dans le terminal, qui permet de **créer, lister, modifier et supprimer des formes géométriques**, puis de les **visualiser dans un fichier SVG**.

Formes disponibles : **carré**, **rectangle**, **cercle**, **ellipse** et **ligne**.

## Fonctionnalités

- Créer une forme en choisissant ses coordonnées, ses dimensions et sa couleur
- Lister les formes d'un type donné, numérotées à partir de 1
- Modifier une forme (position, dimensions ou couleur)
- Supprimer une forme
- Générer et ouvrir automatiquement un fichier `formes.svg` (800 × 600 px, fond blanc)
- Choisir parmi 12 couleurs, affichées en couleur dans le terminal
- Saisies sécurisées : une valeur invalide est simplement redemandée

## Aperçu

```
╭──────────────────────────────╮
│             MENU             │
├──────────────────────────────┤
│ 1 ➜ Créer une forme          │
│ 2 ➜ Lister les formes        │
│ 3 ➜ Modifier une forme       │
│ 4 ➜ Supprimer une forme      │
│ 5 ➜ Afficher le SVG          │
│ 6 ➜ Quitter                  │
╰──────────────────────────────╯
```

Les menus « Créer », « Lister », « Modifier » et « Supprimer » proposent ensuite le choix de la forme (carré, rectangle, cercle, ellipse, ligne) ou un retour au menu principal.

## Prérequis

- `gcc` et `make`
- Un terminal qui gère l'UTF-8 et les couleurs ANSI (pour les cadres et les couleurs)
- Un navigateur ou une application capable d'ouvrir un fichier `.svg`

## Compilation et lancement

```bash
make          # compile le programme
./ProjetC     # lance le programme
```

Autres commandes :

```bash
make clean    # supprime les fichiers compilés et formes.svg
make re       # recompile tout depuis zéro
```
