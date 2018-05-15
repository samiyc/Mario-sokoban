/*
fichiers.c
----------

Par mateo21, pour Le Site du Zér0 (www.siteduzero.com)

Rôle : fonctions de lecture / écriture de fichiers de niveau.
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "fichiers.h"

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR], int *lvl)
{
    FILE* fichier = NULL;
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 5] = {0};
    char lettre;
    int i = 0, j = 0;

    fichier = fopen("niveaux.lvl", "r");
    if (fichier == NULL)
        return 0;

    // calcul longueur fichier et verification de nn depassement
    rewind(fichier);
    while (fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 5, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            i++;
        }
    if (*lvl >= i) *lvl = i;


    // selection du niveau
    rewind(fichier);
    for (i = *lvl ; i > 1.5 ; i--)
    {
        fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 5, fichier);
    }

    fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 5, fichier);

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
            {
                case '0':
                    niveau[j][i] = 0;
                    break;
                case ' ':
                    niveau[j][i] = 0;
                    break;
                case '1':
                    niveau[j][i] = 1;
                    break;
                case '#':
                    niveau[j][i] = 1;
                    break;
                case '2':
                    niveau[j][i] = 2;
                    break;
                case '$':
                    niveau[j][i] = 2;
                    break;
                case '3':
                    niveau[j][i] = 3;
                    break;
                case '.':
                    niveau[j][i] = 3;
                    break;
                case '4':
                    niveau[j][i] = 4;
                    break;
                case '@':
                    niveau[j][i] = 4;
                    break;
                case '5':
                    niveau[j][i] = 5;
                    break;
                case '*':
                    niveau[j][i] = 5;
                    break;
            }
        }
    }

    fclose(fichier);
    return 1;
}

int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR], int lvl)
{
    FILE* fichier = NULL;
    int i = 0, j = 0;

    fichier = fopen("niveaux.lvl", "a"); // "a" comme ajout
    if (fichier == NULL)
        return 0;

    fprintf(fichier, "\n");
    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            fprintf(fichier, "%d", niveau[j][i]);
        }
    }

    // cloture du fichier
    fclose(fichier);
    SDL_Delay(500);
    return 1;
}
