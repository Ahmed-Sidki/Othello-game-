#define VIDE -1
#define NOIR 0
#define BLANC 1
#define DISPONIBLE 2

int random_joueur() {
    return random_int(0, 1);
}

int random_int(int min, int max) {
    return rand() % (max - min) + min + 1;
}

void joueur_humain(char *joueur, int tour, int adversaire, char *selection, int othellier[][8]) {

    // declaration des variables

    int n, r, x, y, pas_x, pas_y;

    int k[8][2] = {{-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}};           // definir les 8 combinaisons de pas possibles
    int svg_x[8] = {-1,-1,-1,-1,-1,-1,-1,-1};                                               // tables de stockage temporaire des abscisses (x) des cases
    int svg_y[8] = {-1,-1,-1,-1,-1,-1,-1,-1};                                               // tables de stockage temporaire des ordonnees (y) des case

    // demander au joueur de selectionner une case
    do {
        printf("\nTour du joueur :  %s ( %c )", joueur, symbole(tour));
        printf("\nSelectionner une position: ");
        scanf("%s", selection);
        convertir_en_coordonnees(selection, &x, &y);    // convertir la selection en coordonnees pour la table othelier

        // s'il y a eu un selection et la case selectionnee n'etait pas correcte, afficher un message d'avertissement ou d'erreur
        if ((x == VIDE) || (y == VIDE)) {
            printf("\n[ Erreur ] : ");
            printf("\nVous avez joue: %s", selection);
            printf("\nAucune case correspond a votre selection !! Veuillez reessayer.");
            printf("\n\nNote: Une case se compose d'une lettre de A a H (majuscule ou miniscule) attachee a un chiffre entre 1 et 8 (inclus). ");
            printf("L'ordre n'est pas important.\n(exp: A1 ; C7 ; 3f ; e2 ; 6H ...)\n\n\n\n");
        }

        else if (othellier[x][y] != DISPONIBLE) {
            printf("\n[ Avertissement ] : ");
            printf("\nVous avez joue: %s", selection);
            printf("\nCette case n'est pas valable %d !! Veuillez selectionner une autre case.\n\n\n\n", tour);
        }
    }

    // repeter si la case n'est pas valable
    while ((x == VIDE) || (y == VIDE) || (othellier[x][y] != DISPONIBLE));

    // quand la case selectionnee est une case valable
    othellier[x][y] = tour;

    // verifier toutes les positions
    for (n=0; n<8; n++) {                       // pour chaque combinaison de pas {x', y'}

        pas_x = x+k[n][0];                      // pas_x stock l'abscisse de la case x + x'
        pas_y = y+k[n][1];                      // pas_y stock l'ordonnee de la case y + y'
                                                // x et y sont les coordonnees de la case jouee

        r = 0;                                  // index pour svg_x et svg_y

        while (pas_valide(pas_x, pas_y) && (othellier[pas_x][pas_y] == adversaire)) {       // tant que le pas est valide et correspond a un adversaire
            svg_x[r] = pas_x;                                                               // sauvegarder temporairement les coordonnees de ce pas
            svg_y[r] = pas_y;
            pas_x = pas_x+k[n][0];                                                          // faire un autre pas {x", y"}
            pas_y = pas_y+k[n][1];                                                          // et incementer (r) pour pouvoir stocker d'autre coordonnees
            r++;                                                                            // sur svg_x et svg_y
        }

        // (r) aussi indique qu'il y au moin une case correspondante a un adversaire si differente de 0
        // la boucle precedente se termine quand il n'y a plus de cases correspondantes a l'adversaire
        // si la case du dernier pas atteint correspond a tour, cela signifie que l'ensemble des cases
        // dont les coordonnees sauvegardees sur svg_x et svg_y sont des cases adversaires encadrees
        // par des cases joueur (tour), et donc considerees comme des cases gagnees.

        if ((r) && pas_valide(pas_x, pas_y) && (othellier[pas_x][pas_y] == tour)) {
            while (r > 0) {
                r--;
                if (pas_valide(svg_x[r], svg_y[r])) {
                    othellier[svg_x[r]][svg_y[r]] = tour;                                   // inverser chaque case gagnee.
                }
                svg_x[r] = svg_y[r] = -1;                                                   // initialiser svg_x et svg_y
            }
        }
    }

    convertir_en_selection(selection, x, y);        // convertir les courdonnees en selection pour qu'elle soit sous la forme "A1"

}


void joueur_ordinateur(char *joueur, int tour, int adversaire, char *selection, int othellier[][8]) {

    // declaration des variables

    int n, r, x, y, pas_x, pas_y;

    int k[8][2] = {{-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}};           // definir les 8 combinaisons de pas possibles
    int svg_x[8] = {-1,-1,-1,-1,-1,-1,-1,-1};                                               // tables de stockage temporaire des abscisses (x) des cases
    int svg_y[8] = {-1,-1,-1,-1,-1,-1,-1,-1};                                               // tables de stockage temporaire des ordonnees (y) des case

    // selection aleatoire d'une case
    selection_aleatoire(&x, &y, othellier);

    // quand la case selectionnee est une case valable
    othellier[x][y] = tour;

    // verifier toutes les positions
    for (n=0; n<8; n++) {                       // pour chaque combinaison de pas {x', y'}

        pas_x = x+k[n][0];                      // pas_x stock l'abscisse de la case x + x'
        pas_y = y+k[n][1];                      // pas_y stock l'ordonnee de la case y + y'
                                                // x et y sont les coordonnees de la case jouee

        r = 0;                                  // index pour svg_x et svg_y

        while (pas_valide(pas_x, pas_y) && (othellier[pas_x][pas_y] == adversaire)) {       // tant que le pas est valide et correspond a un adversaire
            svg_x[r] = pas_x;                                                               // sauvegarder temporairement les coordonnees de ce pas
            svg_y[r] = pas_y;
            pas_x = pas_x+k[n][0];                                                          // faire un autre pas {x", y"}
            pas_y = pas_y+k[n][1];                                                          // et incementer (r) pour pouvoir stocker d'autre coordonnees
            r++;                                                                            // sur svg_x et svg_y
        }

        // (r) aussi indique qu'il y au moin une case correspondante a un adversaire si differente de 0
        // la boucle precedente se termine quand il n'y a plus de cases correspondantes a l'adversaire
        // si la case du dernier pas atteint correspond a tour, cela signifie que l'ensemble des cases
        // dont les coordonnees sauvegardees sur svg_x et svg_y sont des cases adversaires encadrees
        // par des cases joueur (tour), et donc considerees comme des cases gagnees.

        if ((r) && pas_valide(pas_x, pas_y) && (othellier[pas_x][pas_y] == tour)) {
            while (r > 0) {
                r--;
                if (pas_valide(svg_x[r], svg_y[r])) {
                    othellier[svg_x[r]][svg_y[r]] = tour;                                   // inverser chaque case gagnee.
                }
                svg_x[r] = svg_y[r] = -1;                                                   // initialiser svg_x et svg_y
            }
        }
    }

    convertir_en_selection(selection, x, y);        // convertir les courdonnees en selection pour qu'elle soit sous la forme "A1"

}
void joueur_ordinateur_intelligent(char *joueur, int tour, int adversaire, char *selection, int othellier[][8]) {

    // declaration des variables

    int n, r, x, y, pas_x, pas_y;

    int k[8][2] = {{-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}};           // definir les 8 combinaisons de pas possibles
    int svg_x[8] = {-1,-1,-1,-1,-1,-1,-1,-1};                                               // tables de stockage temporaire des abscisses (x) des cases
    int svg_y[8] = {-1,-1,-1,-1,-1,-1,-1,-1};                                               // tables de stockage temporaire des ordonnees (y) des case

    // selection aleatoire d'une case
    selection_intelligente(&x, &y, tour, adversaire, othellier);

    // quand la case selectionnee est une case valable
    othellier[x][y] = tour;

    // verifier toutes les positions
    for (n=0; n<8; n++) {                       // pour chaque combinaison de pas {x', y'}

        pas_x = x+k[n][0];                      // pas_x stock l'abscisse de la case x + x'
        pas_y = y+k[n][1];                      // pas_y stock l'ordonnee de la case y + y'
                                                // x et y sont les coordonnees de la case jouee

        r = 0;                                  // index pour svg_x et svg_y

        while (pas_valide(pas_x, pas_y) && (othellier[pas_x][pas_y] == adversaire)) {       // tant que le pas est valide et correspond a un adversaire
            svg_x[r] = pas_x;                                                               // sauvegarder temporairement les coordonnees de ce pas
            svg_y[r] = pas_y;
            pas_x = pas_x+k[n][0];                                                          // faire un autre pas {x", y"}
            pas_y = pas_y+k[n][1];                                                          // et incementer (r) pour pouvoir stocker d'autre coordonnees
            r++;                                                                            // sur svg_x et svg_y
        }

        // (r) aussi indique qu'il y au moin une case correspondante a un adversaire si differente de 0
        // la boucle precedente se termine quand il n'y a plus de cases correspondantes a l'adversaire
        // si la case du dernier pas atteint correspond a tour, cela signifie que l'ensemble des cases
        // dont les coordonnees sauvegardees sur svg_x et svg_y sont des cases adversaires encadrees
        // par des cases joueur (tour), et donc considerees comme des cases gagnees.

        if ((r) && pas_valide(pas_x, pas_y) && (othellier[pas_x][pas_y] == tour)) {
            while (r > 0) {
                r--;
                if (pas_valide(svg_x[r], svg_y[r])) {
                    othellier[svg_x[r]][svg_y[r]] = tour;                                   // inverser chaque case gagnee.
                }
                svg_x[r] = svg_y[r] = -1;                                                   // initialiser svg_x et svg_y
            }
        }
    }

    convertir_en_selection(selection, x, y);        // convertir les courdonnees en selection pour qu'elle soit sous la forme "A1"

}
void selection_intelligente(int *x, int *y, int tour, int adversaire, int othellier[][8]) {

    int i, j, n, r, pas_x, pas_y, nombre_pas, nombre_sens, nombre_pas_temp, nombre_sens_temp;                                                           // declaration des variables
    int k[8][2] = {{-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}};           // definir les 8 combinaisons de pas possibles

    nombre_pas = 0;
    nombre_sens = 0;

    for (i=0; i<8; i++) {                               // pour les 64 cases de l'othellier
        for (j=0; j<8; j++) {                           //

            if (othellier[i][j] == DISPONIBLE) {                 // si la valeur de la case est egale a -1 (valable)

                nombre_pas_temp = 0;
                nombre_sens_temp = 0;

                for (n=0; n<8; n++) {                   // pour chaque combinaison de pas {x', y'}

                    pas_x = i+k[n][0];                  // pas_x stock l'abscisse de la case i + x'
                    pas_y = j+k[n][1];                  // pas_y stock l'ordonnee de la case j + y'
                                                        // i et j sont les coordonnees d'une case

                    r = 0;                              // ici (r) indique qu'il y au moin une case correspondante a l'adversaire

                    while (pas_valide(pas_x, pas_y) && (othellier[pas_x][pas_y] == adversaire)) {  // tant que le pas est valide et correspond a l'adversaire
                        pas_x = pas_x+k[n][0];                                                      // faire un autre pas {x", y"}
                        pas_y = pas_y+k[n][1];
                        r++;
                    }

                    // la boucle precedente se termine quand il n'y a plus de cases correspondantes a l'adversaire
                    // si la case du dernier pas atteint correspond au joueur qui a le tour, cela signifie que ce joueur
                    // peut jouer la case dont les coordonnees sont {i, j}

                    if ((r) && pas_valide(pas_x, pas_y) && (othellier[pas_x][pas_y] == tour)) {
                        nombre_pas_temp += r;
                        nombre_sens_temp++;
                    }
                }

                if (nombre_sens_temp > nombre_sens) {
                    nombre_sens = nombre_sens_temp;
                    *x = i;
                    *y = j;
                }

                else if (nombre_sens_temp == nombre_sens) {
                    if (nombre_pas_temp > nombre_pas) {
                        nombre_pas = nombre_pas_temp;
                        *x = i;
                        *y = j;
                    }
                }
            }
        }
    }
}

void selection_aleatoire(int *x, int *y, int othellier[][8]) {

    int i,j;

    do {
        i = random_int(0,7);
        j = random_int(0,7);
    }
    while (othellier[i][j] != DISPONIBLE);

    *x = i;
    *y = j;

}

void joueur_suivant(int *tour, int *adversaire, int othellier[][8], int *cases_disponibles) {

    int i, j, n, r, pas_x, pas_y;                                                           // declaration des variables
    int k[8][2] = {{-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}};           // definir les 8 combinaisons de pas possibles

    int essai = 2;                                      // nombre d'essai avant de declarer la fin du jeux
    *cases_disponibles = 0;                             // on suppose qu'il n'y a plus de cases a jouer

    while (essai) {

        *tour = *adversaire;                            // inverser le tour et puis chercher les cases possibles pour le nouveau joueur ayant le tour
        *adversaire = 1 - *tour;

        for (i=0; i<8; i++) {
            for (j=0; j<8; j++) {
                if (othellier[i][j] == DISPONIBLE) {          // Pour definir les case possibles pour le joueur suivant
                    othellier[i][j] = VIDE;                   // donc mettre toutes les cases possibles precedemment definies -1
                }
            }
        }

        for (i=0; i<8; i++) {                               // pour les 64 cases de l'othellier
            for (j=0; j<8; j++) {                           //

                if (othellier[i][j] == VIDE) {                 // si la valeur de la case est egale a -1 (valable)

                    for (n=0; n<8; n++) {                   // pour chaque combinaison de pas {x', y'}

                        pas_x = i+k[n][0];                  // pas_x stock l'abscisse de la case i + x'
                        pas_y = j+k[n][1];                  // pas_y stock l'ordonnee de la case j + y'
                                                            // i et j sont les coordonnees d'une case

                        r = 0;                              // ici (r) indique qu'il y au moin une case correspondante a l'adversaire

                        while (pas_valide(pas_x, pas_y) && (othellier[pas_x][pas_y] == *adversaire)) {  // tant que le pas est valide et correspond a l'adversaire
                            pas_x = pas_x+k[n][0];                                                      // faire un autre pas {x", y"}
                            pas_y = pas_y+k[n][1];
                            r++;
                        }

                        // la boucle precedente se termine quand il n'y a plus de cases correspondantes a l'adversaire
                        // si la case du dernier pas atteint correspond au joueur qui a le tour, cela signifie que ce joueur
                        // peut jouer la case dont les coordonnees sont {i, j}

                        if ((r) && pas_valide(pas_x, pas_y) && (othellier[pas_x][pas_y] == *tour)) {
                            othellier[i][j] = DISPONIBLE;        // mettre cette case a 2 pour qu'elle soit valable au joueur actuel
                            *cases_disponibles = 1;              // on a donc au moins un case a jouer
                        }
                    }
                }
            }
        }

        // condition de fin des essais:

        if (*cases_disponibles) {
            essai = 0;
        }

        else {
            essai--;
        }

    }
}

void initialiser_othellier(int othellier[][8]) {

    int i,j;                            // declaration des variables de boucles

    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            othellier[i][j] = VIDE;        // mettre tous les cases de l'othellier a -1
        }
    }

    // initialisation des cases

    othellier[3][3] = BLANC;               // case du joueur blanc
    othellier[4][4] = BLANC;               // case du joueur blanc
    othellier[3][4] = NOIR;                // case du joueur noir
    othellier[4][3] = NOIR;                // case du joueur noir

    othellier[2][3] = DISPONIBLE;          // case possible a jouer
    othellier[3][2] = DISPONIBLE;          // case possible a jouer
    othellier[4][5] = DISPONIBLE;          // case possible a jouer
    othellier[5][4] = DISPONIBLE;          // case possible a jouer

}

void dessiner_othellier(int othellier[][8]) {

    int i,j;                            // declaration des variables de boucles

    char colonnes[] = "ABCDEFGH";       // etiquettes des colonnes
    char lignes[] = "12345678";         // etiquettes des lignes

    // -------------------------------------------------------
    printf("\n\n     ");                                                                        // sauter deux lignes
    for (i=0; i<8; i++) { printf("    %c   ", colonnes[i]); }                                   // affhicher les etiquettes des colonnes
    printf("\n");                                                                               // sauter une ligne
    // -------------------------------------------------------
    for (j=0; j<8; j++) {                                                                       // afficher les huit lignes de l'othellier
        // -----------------------------------------------------------------------------
        printf("      ------- ------- ------- ------- ------- ------- ------- ------- \n");
        printf("     |       |       |       |       |       |       |       |       |\n");     // chaque ligne de l'othellier correspond
        // -----------------------------------------------------------------------------        // a trois lignes de la console. la
        printf("   %c ", lignes[j]);                                                            // premiere et la troisieme ligne affichent
        for (i=0; i<8; i++) {
            printf("|   %c   ", symbole(othellier[i][j]));                                               // symboles pions et les barres verticales
        }
        printf("|\n");
        // -----------------------------------------------------------------------------
        printf("     |       |       |       |       |       |       |       |       |\n");
        // -----------------------------------------------------------------------------
    }
    // -----------------------------------------------------------------------------
    printf("      ------- ------- ------- ------- ------- ------- ------- ------- \n\n");   // tracer la derniere ligne horizontale
    // -----------------------------------------------------------------------------
}

void afficher_score (char joueur[][20], int othellier[][8]) {

    // variable qui stock le nombre de cases pour chaque joueur
    int nombre_cases[2];

    // afficher le nombre de cases de chaque joueur
    calculer_nombre_cases(nombre_cases, othellier);
    printf("\tScore:      ( %c ) %s : %d      ( %c ) %s : %d\n\n", symbole(NOIR), joueur[NOIR], nombre_cases[NOIR], symbole(BLANC), joueur[BLANC], nombre_cases[BLANC]);

}

void afficher_score_final(int mode, char joueur[][20], int othellier[][8]) {

    int nombre_cases[2];

    calculer_nombre_cases(nombre_cases, othellier);

    if (nombre_cases[NOIR] > nombre_cases[BLANC]) {
        if ((mode) && (!strcmp(joueur[NOIR], "PC"))) {
            printf("\n\n*** Jeu (T_T) perdu %s ***", joueur[BLANC]);
            printf("\n\nVous avez perdu avec un score de %d contre %d", nombre_cases[BLANC], nombre_cases[NOIR]);
        }

        else {
            printf("\n\n*** Felicitation %s ***", joueur[NOIR]);
            printf("\n\nVous avez gagne avec un score de %d contre %d", nombre_cases[NOIR], nombre_cases[BLANC]);
        }
    }

    else if (nombre_cases[NOIR] < nombre_cases[BLANC]) {
        if ((mode) && (!strcmp(joueur[BLANC], "PC"))) {
            printf("\n\n*** Jeu (T_T) perdu %s ***", joueur[NOIR]);
            printf("\n\nVous avez perdu avec un score de %d contre %d", nombre_cases[NOIR], nombre_cases[BLANC]);
        }

        else {
            printf("\n\n*** Felicitation %s ***", joueur[BLANC]);
            printf("\n\nVous avez gagne avec un score de %d contre %d", nombre_cases[BLANC], nombre_cases[NOIR]);
        }
    }

    else {
        printf("\n\n*** Egalite ***");
        printf("\n\nPartie termine avec un score de %d contre %d", nombre_cases[NOIR], nombre_cases[BLANC]);
    }

}

void afficher_case_selectionne (char *selection) {

    // afficher la case selectionnee
    printf("\nCase selectionnee: %s\n", selection);

}

void calculer_nombre_cases(int nombre_cases[], int othellier[][8]) {

    int i,j;                                                // declaration des variables de boucles

    nombre_cases[NOIR] = 0;                                    // initialiser nombre de cases pour le joueur 1
    nombre_cases[BLANC] = 0;                                    // initialiser nombre de cases pour le joueur 2

    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            if (othellier[i][j] == NOIR) {
                nombre_cases[NOIR]++;                          // si la case est 1 incrementer le nombre de cases du joueur 1
            }
            if (othellier[i][j] == BLANC) {
                nombre_cases[BLANC]++;                          // si la case est 2 incrementer le nombre de cases du joueur 2
            }
        }
    }
}

void convertir_en_coordonnees(char *selection, int *x, int *y) {

    int i,j;                                        // declaration des variables de boucles
    char colonnes_min[] = "abcdefgh";               // chaines de texte valable pour la selection
    char colonnes[] = "ABCDEFGH";                   //
    char lignes[] = "12345678";                     //

    // puisque cette fonction doit renvoyer des valeurs pour x et pour y ce qui n'est pas possible
    // on va modifier la valeur des deux variables a travers leurs pointeurs

    *x = VIDE;                                        // initialiser a -1 (abscisse incorrecte)
    *y = VIDE;                                        // initialiser a -1 (abscisse incorrecte)

    for (i=0; i<8; i++) {
        if ((selection[0] == colonnes[i]) || (selection[0] == colonnes_min[i])) {   // si le premier caractere de la selection correspond a une colonne
            for (j=0; j<8; j++) {
                if (selection[1] == lignes[j]) {                                    // si le deuxieme caractere de la selection correspont a une ligne
                    *x = i;                                                         // retourner l'abscisse de la case selectionnee sur x
                    *y = j;                                                         // retourner l'ordonnee de la case selectionnee sur y
                    convertir_en_selection(selection, *x, *y);
                }
            }
        }
        else if ((selection[1] == colonnes[i]) || (selection[1] == colonnes_min[i])) {  // si le deuxieme caractere de la selection correspond a une colonne
            for (j=0; j<8; j++) {
                if (selection[0] == lignes[j]) {                                        // si le premier caractere de la selection correspont a une ligne
                    *x = i;                                                             // retourner l'abscisse de la case selectionnee sur x
                    *y = j;                                                             // retourner l'ordonnee de la case selectionnee sur y
                    convertir_en_selection(selection, *x, *y);
                }
            }
        }
    }
}

void convertir_en_selection(char *selection, int x, int y) {

    char colonnes[] = "ABCDEFGH";
    char lignes[] = "12345678";

    sprintf(selection, "%c%c", colonnes[x], lignes[y]);

}

void delay_ms(int temps) {
    int debut = clock();
    while (clock() < debut + (temps));
}

int pas_valide(int pas_x, int pas_y) {
    int pas_valide = 0;
    if ((pas_x >= 0) && (pas_x < 8) && (pas_y >= 0) && (pas_y < 8)) {       // verifier si les coordonnees du pas correspond a une case
        pas_valide = 1;
    }
    return pas_valide;
}

int symbole(int valeur) {
    char symbole = ' ';
    if (valeur == NOIR) { symbole = 'X'; }                     // renvoyer le symbole a afficher dans une case de l'othellier
    if (valeur == BLANC) { symbole = 'O'; }
    // if (valeur == 2) { symbole = '.'; }
    return symbole;
}



