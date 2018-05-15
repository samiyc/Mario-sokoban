/*
jeu.h
-----

Par mateo21, pour Le Site du Z�r0 (www.siteduzero.com)

R�le : prototypes des fonctions du jeu.
*/

#ifndef DEF_JEU
#define DEF_JEU

    int jouer(SDL_Surface* ecran, int lvl);
    void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], int tbRep[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
    void deplacerCaisse(int *premiereCase, int *secondeCase);
    int manip(int a, int b, char *un, char *de);
    char conv(int nb);


#endif
