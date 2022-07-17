/**
 * @author Théo Balick
 */

// Inclusion des données définies
#include "Personne.h"
#include "fonctions_affichage.h"

/**
 * Définition des valeurs des attributs de la structure Personne
 * @param personne personne dans laquelle les attributs sont définis
 * @return 1 en cas de succès, sinon 0
 * @version 2
 */
int Acquisition(Personne* personne) {

    char nom_personne[TAILLE_CHAINES]; // Nom de la personne
    char telephone_personne[TAILLE_CHAINES]; // Téléphone de la personne

    printf("*-> Entrer le nom de la personne que vous voulez ajouter : "); // ceci est un message

    scanf("%s", &nom_personne); // La machine attend qu'une valeur soit saisie
    // Mis en forme du nom en mettant la première lettre en majuscule et les autres en miniscule
    Mettre_en_forme_nom(nom_personne);

    printf("*-> Entrer le numero de la personne que vous voulez ajouter : "); // ceci est un message

    scanf("%s", &telephone_personne); // La machine attend qu'une valeur soit saisie
    printf("\n"); // Saut de ligne pour un bon affichage

    // Si le nom saisi possède plus de 30 caractères
    if (strlen(nom_personne) > 30) {
        Message_erreur_nom(); // ceci est un message
        return 0; // 0 est retourné pour dire que l'acquisition n'a pas réussi
    }

    // Si le numéro saisi possède plus de 10 chiffres et
    // si le numéro de téléphone commence avec 08 ou 09 ce qui veut dire que le premier chiffre doit etre 0 et le deuxième 8 ou 9
    // Si toutes les conditions ci-dessus sont remplis, alors le numéro de téléphone est valide
    if (strlen(telephone_personne) == 10 && telephone_personne[0] == '0' && (telephone_personne[1] == '8' || telephone_personne[1] == '9')) {
        // et si le numéro de téléphone contient le caractère '-'
        if (strstr(telephone_personne, "-") == NULL) {
            // Copie de la valeur de nom_personne dans l'attribut nom de la structure personne
            strcpy(personne->nom, nom_personne);
            // Copie de la valeur de telephone_personne dans l'attribut telephone de la structure personne
            strcpy(personne->telephone, telephone_personne);
            return 1; // 1 est retourné pour dire que l'acquisition a réussi
        }
    }

    // Dans le cas contraire de la condition ci-haut, le numéro n'est pas valide
    Message_erreur_telephone(); // Message d'erreur
    return 0; // 0 est retourné pour dire que l'acquisition n'a pas réussi
}

/**
 * Ajoute une personne dans le tableau annuaire.
 * @param annuaire tableau dans lequel une personne est ajoutée
 * @param nombre_total_personnes personnes disponible dans le tableau annuaire
 * * @version 2
 */
void Ajoute(int *nombre_total_personnes, Personne *annuaire) {
    Personne personne_a_ajouter; // Personne à ajouter dans l'annuaire

    // Définition des valeurs des attributs pour personne_a_ajouter
    // et stockage de la valeur de retour dans la variable acquisition_reussi
    // Pour rappel, la fonction Acquisition renvoie 1 en cas de réussite et 0 dans le cas contraire
    int acquisition_reussi = Acquisition(&personne_a_ajouter);

    if (acquisition_reussi) {
        // Si le tableau annuaire est plein, il est agrandi grâce à la fonction realloc
        // Cette dernière prend en paramètre l'adresse du tableau à agrandir ainsi que la nouvelle taille.
        if (*nombre_total_personnes > NOMBRE_PERSONNES_ANNUAIRE) {
            annuaire = realloc(annuaire, NOMBRE_PERSONNES_ANNUAIRE * 2);
        }

        annuaire[*nombre_total_personnes] = personne_a_ajouter; // Ajout de la personne dans le tableau annuaire
        (*nombre_total_personnes)++; // Incrémentation du nombre total des personnes dans l'annuaire

        Trier_tableau_annuaire(annuaire, *nombre_total_personnes); // Trie du tableau par ordre alphabétique
    }
}

/**
 * Liste toutes les personnes présentes dans l'annuaire
 * @param annuaire tableau des éléments à afficher
 * @param nombre_total_personnes nombre total des personnes disponible dans le tableau annuaire
 * * @version 2
 */
void Affiche(int nombre_total_personnes, Personne *annuaire) {
    printf("*-> ANNUAIRE | Nombre total des personnes : %d\n", nombre_total_personnes);
    if (nombre_total_personnes == 0) {
        printf("*-> Aucune personne n'est enregistre dans l'annuaire\n\n");
    } else {
        printf("*------------------------------------------------*\n");
        for (int i = 0; i < nombre_total_personnes ; ++i) {
            printf("|   %d. %s : %s\n", (i+1), &annuaire[i].nom, &annuaire[i].telephone);
        }

        printf("*------------------------------------------------*\n\n");
    }
}

/**
 * Efface une personne dans le tableau annuaire
 * @param annuaire contient les éléments à effacés
 * @param nombre_total_personnes nombre total des personnes disponible dans le tableau annuaire
 * @return 1 si la suppression a réussi, sinon retourne 0
 * * @version 2
 */
void Efface(Personne *annuaire, int *nombre_total_personnes) {

    // Si le tableau annuaire n'est pas vide
    if (*nombre_total_personnes >= 1) {
        char nom_personne[TAILLE_CHAINES]; // Nom de la personne à supprimer
        int numero_personne = 0; // Position de la personne dans l'annuaire

        printf("*-> Entrer le nom de la personne que vous souhaitez effacer dans l'annuaire : "); // Ceci est un message
        scanf("%s", &nom_personne); // Attente d'une saisie des données au clavier
        printf("\n");
        Mettre_en_forme_nom(nom_personne); // Met la première lettre en majuscule et les autres en miniscule

        // Si l'annuaire ne contient qu'une personne
        // le nombre total des personnes dans le tableau est soustrait de 1 et on quitte la fonction
        if (*nombre_total_personnes == 1) {
            *nombre_total_personnes -= 1;
            return;
        }

       // Parcours du tableau annuaire
        for (int i = 0; i < *nombre_total_personnes; ++i) {
            // Si le nom de la personne de l'itération en cours correspond au nom saisi par l'utilisateur
            // on mémorise le numéro de la personne dans l'annuaire et on quitte la boucle
            if (strcmp(annuaire[i].nom, nom_personne) == 0) {
                numero_personne = i;
                break;
            }
        }

        // À partir du numéro de la personne à supprimer,
        // le numéro de chaque personne est remplacé par son précédent
        // En bref, la position de chaque personne dans le tableau est decallé de -1
        for (int i = numero_personne; i < *nombre_total_personnes; ++i) annuaire[i] = annuaire[i+1];

        *nombre_total_personnes -= 1; // Réduction du nombre des personnes total dans l'annuaire
    } else {
        printf("*-> L'annuaire est vide, il n'y a personne à effacer.\n");
    }
}

/**
 * Recherche le numéro de téléphone d'une personne
 * @param annuaire annuaire des personnes
 * @param nombre_total_personnes nombre total des personnes disponible dans le tableau annuaire
 * * @version 2
 */
void RechercheTel(Personne *annuaire, int nombre_total_personnes) {
    char nom_personne[50]; // Nom de la personne

    printf("*-> Veuillez entrer le nom de personne pour qui vous chercher le numero : "); // Ceci est un message
    scanf("%s", &nom_personne); // Attente d'une valeur
    Mettre_en_forme_nom(nom_personne); // Met la première lettre en majuscule et les autres en miniscule

    // Parcours de l'annuaire
    for (int i = 0; i < nombre_total_personnes; ++i) {
        // Si le nom de la personne courante dans la boucle correspond au nom saisi pas l'utilisateur
        // On affiche son numéro et on quitte la fonction
        if (strcmp(annuaire[i].nom, nom_personne) == 0) {
            printf("*-> %s utilise le numéro de telephone : %s\n\n", nom_personne, &annuaire[i].telephone);
            return;
        }
    }
    printf("*-> Aucun numero n'est enregistre avec le nom %s\n\n", nom_personne);
}

/**
 * Recherche le numéro de téléphone d'une personne
 * @param annuaire annuaire des personnes
 * @param nombre_total_personnes nombre total des personnes disponible dans le tableau annuaire
 * * @version 2
 */
void RechercheNom(Personne *annuaire, int nombre_total_personnes) {
    char telephone_personne[50]; // Nom de la personne

    printf("*-> Veuillez entrer le numero de la personne pour qui vous chercher le nom : "); // Ceci est un message
    scanf("%s", &telephone_personne); // Attente d'une valeur

    // Parcours de l'annuaire
    for (int i = 0; i < nombre_total_personnes; ++i) {
        // Si le numéro de la personne courante dans la boucle correspond au numéro saisi pas l'utilisateur
        // On affiche son nom et on quitte la fonction
        if (strcmp(annuaire[i].telephone, telephone_personne) == 0) {
            printf("*-> Le numero %s appartient a %s \n\n", telephone_personne, &annuaire[i].nom);
            return;
        }
    }
    printf("*-> Aucun nom n'est enregistre a ce numero %s\n\n", telephone_personne);
}

/**
 * Trie le tableau annuaire par ordre alphabétique
 * @param annuaire annuaire des personnes
 * @param nombre_total_personnes nombre total des personnes disponible dans le tableau annuaire
 * * @version 2
 */
void Trier_tableau_annuaire(Personne *annuaire, int nombre_total_personnes) {
    Personne temp; // Ceci est une variable temporaire

    // Principe du trie: Chaque élément courant dans la première boucle est
    // comparé avec tous les éléments de ce que rencontre la deuxième boucle
    // En bref, c'est comme si chaque élément est comparé avec tous les autres éléments du tableau
    // si l'élément courant de la deuxième boucle est plus petit que celui de la première boucle,
    // alors les deux valeurs sont échangées à leurs positions
    // Pour rappel en programmation : le caractère 'a' est plus petit que le caractère 'b'

    for (int i = 0; i < nombre_total_personnes; ++i) {
        for (int j = 0; j <= nombre_total_personnes; ++j) {
            // Si le nom de la deuxième boucle est plus petit que celui de la première boucle
            // Les valeurs de deux sont échangées à l'aide de la variable intermédiaire
            if (strcmp(annuaire[i].nom, annuaire[j].nom) == -1) {
                temp = annuaire[i];
                annuaire[i] = annuaire[j];
                annuaire[j] = temp;
            }
        }
    }
}

/**
 * Formatte le nom_personne en mettant la première lettre en majuscule et les autres en miniscule
 * @param nom_personne nom_personne à mettre en forme
 * * @version 2
 */
void Mettre_en_forme_nom(char *nom_personne) {
    nom_personne[0] = (char) toupper(nom_personne[0]); // Met la première lettre en majuscule

    // Parcours de la chaine
    for (int i = 1; i < strlen(nom_personne); ++i) {
        nom_personne[i] = (char) tolower(nom_personne[i]); // Met le caractère en miniscule
    }
}
