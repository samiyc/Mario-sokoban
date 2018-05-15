/*
main.c
------

Par mateo21, pour Le Site du Zér0 (www.siteduzero.com)

Rôle : menu du jeu. Permet de choisir entre l'éditeur et le jeu lui-même.
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "jeu.h"
#include "editeur.h"



int main(int argc, char *argv[])
{
    // choix du niveau
    char chaine[3] = "";
    char car_a, car_b;
    chaine[0]='1';
    chaine[1]=' ';
    chaine[2]='\0';

    // niv
    int lvl = 1, oldLvl = 0, tch = 'O';

    // surface
    SDL_Surface *ecran = NULL, *menu = NULL, *texte = NULL, *rep = NULL;
    SDL_Rect positionMenu, posRep, posChoix;
    SDL_Event event;

    // police
    TTF_Font *police = NULL;

    // var boucle infini
    int continuer = 1;

    // init video
    SDL_Init(SDL_INIT_VIDEO);

    // texte choix lvl
    TTF_Init();                   // initialisation SDL_ttf
    police = TTF_OpenFont("heroin07.ttf", 25);
    SDL_Color blanc = {255, 255, 255};
    texte = TTF_RenderText_Blended(police, "CHOIX DU NIVEAU:", blanc);
    rep = TTF_RenderText_Blended(police, chaine, blanc);

    // conf de la fenetre
    SDL_WM_SetIcon(IMG_Load("caisse.jpg"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Mario Sokoban", NULL);

    // image de fon du menu
    menu = IMG_Load("menu.jpg");

    // les positions
    positionMenu.x = 0;
    positionMenu.y = 0;
    posRep.x = ((LARGEUR_FENETRE/2)+(texte->w/2)+5);
    posRep.y = 250;
    posChoix.x = ((LARGEUR_FENETRE/2)-(texte->w/2));
    posChoix.y = 250;

    // ##### debut de la boucle infini #####
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        continuer = 0;
                        break;
                    // choix du LVL
                    case SDLK_1:
                        tch = 1;
                        break;
                    case SDLK_2:
                        tch = 2;
                        break;
                    case SDLK_3:
                        tch = 3;
                        break;
                    case SDLK_4:
                        tch = 4;
                        break;
                    case SDLK_5:
                        tch = 5;
                        break;
                    case SDLK_6:
                        tch = 6;
                        break;
                    case SDLK_7:
                        tch = 7;
                        break;
                    case SDLK_8:
                        tch = 8;
                        break;
                    case SDLK_9:
                        tch = 9;
                        break;
                    case SDLK_0:
                        tch = 0;
                        break;
                    case SDLK_BACKSPACE:
                        tch = 'R';
                        break;

                    case SDLK_RETURN: // Demande à jouer
                        if (lvl == 0) lvl = 1;
                        lvl = jouer(ecran, lvl);
                        break;
                    case SDLK_DELETE: // Demande l'éditeur de niveaux
                        editeur(ecran, lvl);
                        break;

                }
                // actualisation des caratères
                lvl = manip(lvl, tch, &car_a, &car_b);
                tch = 'O';
                chaine[0] = car_a;
                chaine[1] = car_b;
                break;

        } // fin sdl_waitevent

        // delay de 20ms
        SDL_Delay(20);

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_BlitSurface(texte, NULL, ecran, &posChoix);
        SDL_BlitSurface(rep, NULL, ecran, &posRep);
        if (lvl != oldLvl)
        {
            oldLvl = lvl;
            SDL_FreeSurface(rep);
            rep = TTF_RenderText_Blended(police, chaine, blanc);
        }

        SDL_Flip(ecran);
    }

    SDL_FreeSurface(menu);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
