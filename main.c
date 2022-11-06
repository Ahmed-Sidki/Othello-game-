#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"

#define NOIR 0
#define BLANC 1

int main() {

    // declaration des variables :
    // ---------------------------

    int mode,mode1;
    char rejouer;                                       // rejouer ?
    char joueur_1[20] = "", joueur_2[20] = "";                    // variables stockant les noms des joueurs
    char joueur[2][20];                                 // tables stockant les noms des joueurs par couleur
    char selection[3];                                  // variable stockant la case jouee
    int tour, adversaire;                               // variables indiquant le joueur ayant le tour et son adversaire
    int cases_disponibles;                              // variable indiquant s'il y a des cases a jouer
    int othellier[8][8];                                // table stockant les valeurs de chaque case de l'othellier


    // afficher le message d'accueil :
    // -------------------------------

    printf("*** BIENVENUE DANS LE JEU OTHELLO ***");
    printf("\n*** Auteur:           Ahmed Sidki ***");


    // -------------------------------------------
    // ----------- commencement du jeu -----------
    // -------------------------------------------

    do {

        // initialisation :
        // ----------------

            // sélectionner mode de jeu (joueur x joueur / joueur x ordinateur):
            // ----------------------------------

            printf("\n\nSelectionner le mode de jeu !");
            printf("\n\n\nMode :    0: Joueur x Joueur    1: Joueur x Ordinateur\nSelection: ");
            scanf("%d", &mode);
            if(mode){
                 printf("\n\nSelectionner le mode de difficulte !");
                 printf("\n\n\nNiveau:     0: Facile    1: Moyen\nSelection: ");
                 scanf("%d",&mode1);
            }


            // sauvegarder les noms des joueurs :
            // ----------------------------------

            if (!strcmp(joueur_1, "")) {
                printf("\n\nQuel est votre nom joueur 1 : ");
                scanf("%s", joueur_1);
            }

            if (mode) {
                sprintf(joueur_2, "PC");
            }

            else {
                if (!strcmp(joueur_2, "")) {
                    printf("\n\nQuel est votre nom joueur 2 : ");
                    scanf("%s", joueur_2);
                }
            }

            // definition du joueur noir et du joueur blanc aleatoirement

            if (random_joueur()) {
                sprintf(joueur[NOIR], joueur_1);
                sprintf(joueur[BLANC], joueur_2);
            }

            else {
                sprintf(joueur[NOIR], joueur_2);
                sprintf(joueur[BLANC], joueur_1);
            }


            // initialisation des variables :

            cases_disponibles = 1;          // au depart il y a des cases disponibles a jouer
            tour = NOIR;                    // le tour commence par le noir
            adversaire = BLANC;             // donc l'adversaire c'est le blanc


            // initialisation de l'othellier

            initialiser_othellier(othellier);



        // commencement de la partie :
        // ---------------------------

            dessiner_othellier(othellier);              // dessiner l'othellier avec les positions initiales
            afficher_score(joueur, othellier);          // afficher le score actuel (2 - 2)

            // ----------------------------------------------------------------------------------

            while (cases_disponibles) {                 // tant qu'il y a des cases a jouer, refaire:

                if (mode) {                              // si le mode joueur x ordinateur
                    if(mode1){                           // Facile ou moyen
                        if (!strcmp(joueur[tour], joueur_1)) {
                            joueur_humain(joueur_1, tour, adversaire, selection, othellier);      // le joueur humain joue son tour
                            }

                        else if (!strcmp(joueur[tour], joueur_2)) {
                            delay_ms(2000);
                            joueur_ordinateur_intelligent(joueur_2, tour, adversaire, selection, othellier); // le joueur ordinateur joue son tour
                            }
                    }
                    else {
                        if (!strcmp(joueur[tour], joueur_1)) {
                            joueur_humain(joueur_1, tour, adversaire, selection, othellier);      // le joueur humain joue son tour
                            }

                        else if (!strcmp(joueur[tour], joueur_2)) {
                            delay_ms(2000);
                            joueur_ordinateur(joueur_2, tour, adversaire, selection, othellier); // le joueur ordinateur joue son tour
                            }
                    }
                }

                else {                                                                        // si le mode joueur x joueur
                    joueur_humain(joueur[tour], tour, adversaire, selection, othellier);      // le joueur 1 ou 2 joue son tour
                }
                // -----------------------------------------------------------------

                dessiner_othellier(othellier);                          // dessiner l'othllier actualise
                afficher_score(joueur, othellier);                      // afficher le nouveau score
                afficher_case_selectionne(selection);                   // afficher la derniere case jouee

                // -----------------------------------------------------------------

                joueur_suivant(&tour, &adversaire, othellier, &cases_disponibles);     // passer le tour au joueur suivant en calculant les cases possibles

            }

        // fin de la partie - rejouer ? :
        // ------------------------------

            afficher_score_final(mode, joueur, othellier);                // afficher le score final

            printf("\n\nRejouer (O/N) ? : ");                       // demander si les joueurs veulent jouer une autre partie
            rejouer = getchar();
            rejouer = getchar();

    }
    while ((rejouer == 'o') || (rejouer == 'O'));                   // rejouer une autre partie tant que la reponse est oui

    // message de fin :
    // -----------------

    printf("\n\nMerci d'avoir joue a Othello !!\nAurevoir\n");

    return 0;
}
