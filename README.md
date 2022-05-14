# Projet Wordle IN104


## Compilation

Pour jouer au jeu :
```
cd wordle
gcc *.c -o wordle.out -lm
```

Pour développer le jeu :

```
cd wordle
gcc -fdiagnostics-color=always -Wall -Werror -Wfatal-errors -g *.c -o wordle.out -lm
```

## Explications

La boucle principale du jeu est dans `main.c`. Le chargement du dictionnaire, la recherche de mot et la vérification de similarité sont effectués dans `word.c`.






## Todo

- Faire une interface console plus jolie (regarder [ncurses](http://hughm.cs.ukzn.ac.za/~murrellh/os/notes/ncurses.html) ou [termbox2](https://github.com/termbox/termbox2))
- Creer un moyen de tester les bots sur tous les mots
- Ajouter le choix du nombre de lettre, le dictonnaire et le nombre de tentative




## Sources

- [3Blue1Brown vidéo sur la theorie de l'information](https://youtu.be/v68zYyaEmEA)



*Par Sébastien Kerbourc'h et Adrien Wallon* 





