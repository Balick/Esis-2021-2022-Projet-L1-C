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
 * @param annuaire tableau dans lequel une personne est ajoutée
 * @param nombre_total_personnes personnes disponible dans le tableau annuaire
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
 * Retire une personne dans l'annuaire. Elle demande un nom à l'utilisateur et la première
 * personne qui porte ce nom sera supprimé de l'annuaire.
 * @param annuaire       est le tableau qui contient toutes les personnes
 * @param nb_personnes   est le nombre des personnes présentes dans le tableau annuaire
 * @return 1 si la suppression a réussi, sinon retourne 0
 */
int Efface(Personne *annuaire, int *nb_personnes) {

    // Si l'annuaire est vide
    if (*nb_personnes == 0)
    {
        printf("\n     L'annuaire est vide, aucune personne à supprimé.\n\n");
        return 0;
    }
    // Si l'annuaire contient au moins une personne
    else if (*nb_personnes >= 1) {
        // Conteneur du nom à supprimer
        char nom[50];
        // Demande à l'utilisateur d'entrer le nom à supprimer
        printf("\n==> Entrer le nom de la personne que vous voulez enlever de l'annuaire : ");
        scanf("%s", &nom);
        printf("\n\n");
        Mettre_en_forme_nom(nom);

        // Position dans l'annuaire de la personne à supprimé
        int position_personne = 0;

        // Si l'annuaire ne contient qu'une personne
        if (*nb_personnes == 1) {
            *nb_personnes -= 1;
            return 1;
        }

        // Mise en place d'une boucle qui va tourner jusqu'à ce qu'elle tombe sur
        // l'élément courant et l'indice de cet élément sera stocké dans la variable position_personne
        for (int i = 0; i < *nb_personnes; ++i) {
            // Si la personne porte le nom saisi par l'utilisateur
            if (strcmp(annuaire[i].nom, nom) == 0) {
                position_personne = i;
                // La boucle n'a plus besoin de tourner lorsque la position a été trouvé
                break;
            }
        }

        // À partir de la position de la personne à supprimer,
        // on remplace chaque personne par son suivant
        for (int i = position_personne; i < *nb_personnes; ++i) {
            annuaire[i] = annuaire[i+1];
        }

        *nb_personnes -= 1;
    }

    return 1;
}

/**
 * Recherche le nom de la personne associé au numéro que l'utilisateur saisira au clavier
 * @param annuaire       est le tableau qui contient toutes les personnes
 * @param nb_personnes   est le nombre des personnes présentes dans le tableau annuaire
 */
void RechercheTel(Personne *annuaire, int nb_personnes) {
    // Variable qui va contenir le nom pour lequel l'utilisateur veut obtenir le numéro
    char nom[50];
    // Demande à l'utilisateur d'entrer le nom à supprimer
    printf("\n==> Nom de la personne à qui appartient le numéro : ");
    scanf("%s", &nom);
    Mettre_en_forme_nom(nom);

    for (int i = 0; i < nb_personnes; ++i) {
        if (strcmp(annuaire[i].nom, nom) == 0) {
            printf("    Numéro de téléphone : %s\n\n", &annuaire[i].telephone);
            return;
        }
    }
    printf("Pas de personne à ce nom\n\n");
}

/**
 * Recherche le numéro de téléphone associé au nom que l'utilisateur saisira au clavier
 * @param annuaire       est le tableau qui contient toutes les personnes
 * @param nb_personnes   est le nombre des personnes présentes dans le tableau annuaire
 */
void RechercheNom(Personne *annuaire, int nb_personnes) {
    // Variable qui va contenir le téléphone pour lequel l'utilisateur veut obtenir le nom
    char numero[50];
    // Demande à l'utilisateur d'entrer le nom à supprimer
    printf("\n==> Numéro de téléphone de la personne : ");
    scanf("%s", &numero);

    for (int i = 0; i < nb_personnes; ++i) {
        if (strcmp(annuaire[i].telephone, numero) == 0) {
            printf("    Propriétaire : %s\n\n", &annuaire[i].nom);
            return;
        }
    }
    printf("    Pas ce numéro dans l'annuaire!\n\n");
}

/**
 * Permet de trier un tableau de personnes par rapport à leurs nom. Le trie se
 * fait en ordre croissant, c'est-à-dire, du plus petits aux plus grand caractères.
 * @param annuaire      est le tableau qui contient toutes les personnes
 * @param nb_personnes  est le nombre des personnes présentes dans le tableau annuaire
 */
void Trier_tableau_annuaire(Personne *annuaire, int nb_personnes) {
    // Variable temporaire qui permettra d'échanger les valeurs
    Personne temp;

    for (int i = 0; i < nb_personnes; ++i) {
        for (int j = 0; j <= nb_personnes; ++j) {
            // La condition vérifie si le nom de la personne actuelle dans la boucle pour j
            // est inférieure au nom de la personne dans la boucle pour i
            if (strcmp(annuaire[i].nom, annuaire[j].nom) == -1) {
                // Echange des valeurs des variables
                temp = annuaire[i];
                annuaire[i] = annuaire[j];
                annuaire[j] = temp;
            }
        }
    }
}

/**
 * Permet de formatter un nom en mettant le premier caractère en
 * majuscule et les autres en minuscules
 * @param nom est le nom à formatter
 */
void Mettre_en_forme_nom(char *nom) {
    nom[0] = (char) toupper(nom[0]);
    for (int i = 1; i < strlen(nom); ++i) {
        nom[i] = (char) tolower(nom[i]);
    }
}