/*
jeu.c
-----

Par mateo21, pour Le Site du Zér0 (www.siteduzero.com)

Rôle : fonctions du jeu.
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "jeu.h"

int jouer(SDL_Surface* ecran, int lvl)
{
    SDL_Surface *mario[4] = {NULL}; // 4 surfaces pour chacune des directions de mario
    SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL, *repere = NULL, *win = NULL;
    SDL_Rect position, positionJoueur, posWin;
    SDL_Event event;

    int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
    int tbRep[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    // Chargement des sprites (décors, personnage...)
    mur = IMG_Load("mur.jpg");
    caisse = IMG_Load("caisse.jpg");
    caisseOK = IMG_Load("caisse_ok.jpg");
    objectif = IMG_Load("objectif.png");
    repere = IMG_Load("repere.gif");
    win = IMG_Load("bravo.jpg");

    SDL_SetColorKey(repere, SDL_SRCCOLORKEY, SDL_MapRGB(repere->format, 0, 0, 0));
    posWin.x = ((LARGEUR_FENETRE/2)-(win->w/2));
    posWin.y = ((HAUTEUR_FENETRE/2)-(win->h/2));

    mario[BAS] = IMG_Load("mario_bas.gif");
    mario[GAUCHE] = IMG_Load("mario_gauche.gif");
    mario[HAUT] = IMG_Load("mario_haut.gif");
    mario[DROITE] = IMG_Load("mario_droite.gif");

    marioActuel = mario[BAS]; // Mario sera dirigé vers le bas au départ

    // Chargement du niveau
    if (!chargerNiveau(carte, &lvl))
        exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau

    // Recherche de la position de Mario au départ
    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            if (carte[i][j] == MARIO) // Si Mario se trouve à cette position sur la carte
            {
                positionJoueur.x = i;
                positionJoueur.y = j;
                carte[i][j] = VIDE;
            }
        }
    }

    // Activation de la répétition des touches
    SDL_EnableKeyRepeat(150, 150);

    while (continuer)
    {
        SDL_WaitEvent(&event);
switch(event.type)
{
    case SDL_QUIT:
        continuer = 0;
        break;

    case SDL_MOUSEBUTTONUP:
            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT:
                    if (carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] != MUR) tbRep[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = REPR;
                    break;
                case SDL_BUTTON_RIGHT:
                    tbRep[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = RIEN;
                    break;
                default:
                    break;
            }
            break;

    case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            case SDLK_SPACE:
                if (!chargerNiveau(carte, &lvl)) exit(EXIT_FAILURE);
                marioActuel = mario[BAS];
                for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
                {
                    for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
                    {
                        if (carte[i][j] == MARIO) // Si Mario se trouve à cette position sur la carte
                        {
                            positionJoueur.x = i;
                            positionJoueur.y = j;
                            carte[i][j] = VIDE;
                        }
                    }
                }
                break;
            case SDLK_PAGEUP:
                lvl++;
                if (lvl>99) lvl = 99;
                if (!chargerNiveau(carte, &lvl)) exit(EXIT_FAILURE);
                marioActuel = mario[BAS];
                for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
                {
                    for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
                    {
                        if (carte[i][j] == MARIO) // Si Mario se trouve à cette position sur la carte
                        {
                            positionJoueur.x = i;
                            positionJoueur.y = j;
                            carte[i][j] = VIDE;
                        }
                    }
                }

                // remise a zero du tableau des reperes
                for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
                {
                    for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
                    {
                        tbRep[i][j] = 0;
                    }
                }
                break;
            case SDLK_PAGEDOWN:
                lvl--;
                if (lvl<1) lvl = 1;
                if (!chargerNiveau(carte, &lvl)) exit(EXIT_FAILURE);
                marioActuel = mario[BAS];
                for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
                {
                    for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
                    {
                        if (carte[i][j] == MARIO) // Si Mario se trouve à cette position sur la carte
                        {
                            positionJoueur.x = i;
                            positionJoueur.y = j;
                            carte[i][j] = VIDE;
                        }
                    }
                }

                // remise a zero du tableau des reperes
                for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
                {
                    for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
                    {
                        tbRep[i][j] = 0;
                    }
                }
                break;
            case SDLK_UP:
                marioActuel = mario[HAUT];
                deplacerJoueur(carte, tbRep, &positionJoueur, HAUT);
                break;
            case SDLK_DOWN:
                marioActuel = mario[BAS];
                deplacerJoueur(carte, tbRep, &positionJoueur, BAS);
                break;
            case SDLK_RIGHT:
                marioActuel = mario[DROITE];
                deplacerJoueur(carte, tbRep, &positionJoueur, DROITE);
                break;
            case SDLK_LEFT:
                marioActuel = mario[GAUCHE];
                deplacerJoueur(carte, tbRep, &positionJoueur, GAUCHE);
                break;
        }
        break;
}

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 181, 165, 213));

        // Placement des objets à l'écran
        objectifsRestants = 0;

        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOK, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        objectifsRestants = 1;
                        break;
                }
                switch(tbRep[i][j])
                {
                    case REPR:
                        SDL_BlitSurface(repere, NULL, ecran, &position);
                        break;
                    case RIEN:
                        break;
                }
            }
        }

        // Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
        if (!objectifsRestants) // si gagnez soit zero
            {
                SDL_BlitSurface(win, NULL, ecran, &posWin);
                SDL_Flip(ecran);
                SDL_Delay(500);
                do {
                SDL_PollEvent(&event);
                } while ((event.type != SDL_KEYDOWN) && (event.type != SDL_QUIT));
                lvl++;
                if (lvl>99) lvl = 99;
                if (!chargerNiveau(carte, &lvl)) exit(EXIT_FAILURE);
                marioActuel = mario[BAS];
                for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
                {
                    for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
                    {
                        if (carte[i][j] == MARIO) // Si Mario se trouve à cette position sur la carte
                        {
                            positionJoueur.x = i;
                            positionJoueur.y = j;
                            carte[i][j] = VIDE;
                        }
                    }
                }
                // remise a zero du tableau des reperes
                for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
                {
                    for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
                    {
                        tbRep[i][j] = 0;
                    }
                }
            }

        // On place le joueur à la bonne position
        position.x = positionJoueur.x * TAILLE_BLOC;
        position.y = positionJoueur.y * TAILLE_BLOC;
        SDL_BlitSurface(marioActuel, NULL, ecran, &position);



        SDL_Flip(ecran);
    }

    // Désactivation de la répétition des touches (remise à 0)
    SDL_EnableKeyRepeat(0, 0);

    // Libération des surfaces chargées
    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseOK);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(win);
    for (i = 0 ; i < 4 ; i++)
        SDL_FreeSurface(mario[i]);
    return lvl;
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], int tbRep[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction)
{
    switch(direction)
    {
        case HAUT:
            if (pos->y - 1 < 0) // Si le joueur dépasse l'écran, on arrête
                break;
            if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur, on arrête
                break;
            // Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
            if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
                (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
                carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK || tbRep[pos->x][pos->y - 2] == REPR))
                break;

            // Si on arrive là, c'est qu'on peut déplacer le joueur !
            // On vérifie d'abord s'il y a une caisse à déplacer
            deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);

            pos->y--; // On peut enfin faire monter le joueur (oufff !)
            break;


        case BAS:
            if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
                break;
            if (carte[pos->x][pos->y + 1] == MUR)
                break;

            if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) &&
                (pos->y + 2 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == MUR ||
                carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK || tbRep[pos->x][pos->y + 2] == REPR))
                break;


            deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);

            pos->y++;
            break;


        case GAUCHE:
            if (pos->x - 1 < 0)
                break;
            if (carte[pos->x - 1][pos->y] == MUR)
                break;

            if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) &&
                (pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR ||
                carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK || tbRep[pos->x - 2][pos->y] == REPR))
                break;


            deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);

            pos->x--;
            break;


        case DROITE:
            if (pos->x + 1 >= NB_BLOCS_LARGEUR)
                break;
            if (carte[pos->x + 1][pos->y] == MUR)
                break;

            if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) &&
                (pos->x + 2 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == MUR ||
                carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK || tbRep[pos->x + 2][pos->y] == REPR))
                break;

            deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);

            pos->x++;
            break;
    }
}

void deplacerCaisse(int *premiereCase, int *secondeCase)
{
    if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK)
    {
        if (*secondeCase == OBJECTIF)
            *secondeCase = CAISSE_OK;
        else
            *secondeCase = CAISSE;

        if (*premiereCase == CAISSE_OK)
            *premiereCase = OBJECTIF;
        else
            *premiereCase = VIDE;
    }
}

int manip(int a, int b, char *un, char *de)
{
    int nb;
    if (b == 'O')
    {
        if (a > 9)
        {
        *un = conv(a/10);
        *de = conv(a%10);
        }
        else
        {
        *un = conv(a);
        *de = ' ';
        }
        return a;
    }
    if ((a > 9) && (b == 'R'))
    {
        nb = a/10;
        *un = conv(nb);
        *de = ' ';
        return nb;
    }
    if ((a < 10) && (b == 'R'))
    {
        nb = 0;
        *un = ' ';
        *de = ' ';
        return nb;
    }
    if (a < 10)
    {
        nb = ((10*a)+b);
        if (a == 0) *un = ' ';
        else        *un = conv(a);
        *de = conv(b);
        return nb;
    }
    if (a > 9)
    {
        nb = (10*(a/10)+b);
        *un = conv(a/10);
        *de = conv(b);
        return nb;
    }
}

char conv(int nb)
{
    char mot;
    if (nb == 0) mot = '0';
    if (nb == 1) mot = '1';
    if (nb == 2) mot = '2';
    if (nb == 3) mot = '3';
    if (nb == 4) mot = '4';
    if (nb == 5) mot = '5';
    if (nb == 6) mot = '6';
    if (nb == 7) mot = '7';
    if (nb == 8) mot = '8';
    if (nb == 9) mot = '9';
    return mot;
}



