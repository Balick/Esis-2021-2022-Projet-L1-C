/**
 * @author Théo Balick
 */

#include "Personne.h"

/**
 * Enregistre les informations dans la variable personne passée en paramètre.
 * Les informations seront fournies au clavier par l'utilisateur
 * @param personne est la variable dans laquelle on veut stocker les informations
 * @return 1 si les donnees entrées par l'utilisateur ont été stoqué avec succès
 * dans les propriétées (nom et telephone) de la personne, sinon elle retourne 0 en cas d'echec
 */
int Acquisition(Personne* personne) {
    // Déclaration de la variable qui va stocker le nom de la personne
    char nom[TAILLE_MAX];
    /* Déclaration de la variable telephone qui va
     * stocker le numéro de la personne */
    char telephone[TAILLE_MAX];
    /* Déclaration de la variable taille_nom et taille_telephone
     * qui vont stocker respectivement la taille du nom saisie au clavier
     * et celle du numéro de téléphone*/
    int taille_nom, taille_telephone;

    printf("\nNom de la personne à ajouter : "); // Affiche le message "NOM :" à l'écran
    scanf("%s", &nom); // Demande à l'utilisateur d'entrer son nom
    Formatter_nom(nom);

    printf("Numéro de téléphone : "); // Affiche le message "Téléphone :" à l'écran
    scanf("%s", &telephone); // Demande à l'utilisateur d'entrer son numéro de téléphone
    printf("\n");

    /* La fonction strlen prend en paramètre une chaine de caractère
     * et renvoie la taille de cette chaine. Le résultat de la taille du nom
     * est stocké dans la variable taille_nom, et celui de la taille du
     * numéro de téléphone est stocké dans la variable taille_telephone*/
    taille_nom = (int) strlen(nom);
    taille_telephone = (int) strlen(telephone);

    /* On vérifie si la taille dépasse 30, ce qui veut dire que le nom
     * que l'utilisateur a entré dépasse 30 caractères, si c'est le cas,
     * un message d'erreur est affiché et on retourne 0 */
    if (taille_nom > 30) {
        printf("!!! ERREUR: Le nom ne doit pas dépassé 30 caractères !!!\n\n");
        return 0;
    }

    if (taille_telephone == 10) {
        /*
         * On commence d'abord par vérifier si le numéro entré commence bien par 08 ou 09
         * La condition ci-dessous vérifie si le premier caractère du numéro est bien 0
         * et si le deuxième caractère est 8 ou 9
         */
        if (telephone[0] == '0' && (telephone[1] == '8' || telephone[1] == '9')) {
            for (int i = 0; i < strlen(telephone) ; ++i) {
                const char element_courant = telephone[i];
                // Si le compilateur rencontre un signe -, on quitte la fonction
                if (element_courant == '-') {
                    printf("!!! Erreur : Le numéro de téléphone n'est pas valide !!!\n\n");
                    return 0;
                }
            }

            // Le nom et le téléphone saisis au clavier sont stocké dans la personne
            strcpy(personne->nom, nom);
            strcpy(personne->telephone, telephone);
            return 1;
        } else {
            printf("!!! Erreur : Le numéro de téléphone n'est pas valide !!!\n\n");
            return 0;
        }
    } else {
        printf("!!! Erreur : Le numéro de téléphone n'est pas valide !!!\n\n");
        return 0;
    }
}

/**
 * Ajoute une personne dans l'annuaire. Les données de la personne seront fourni
 * par la fonction Acquisition
 * @param annuaire       est le tableau qui contient toutes les personnes
 * @param nb_personnes   est le nombre des personnes présentes dans le tableau annuaire
 */
void Ajoute(int *nb_personnes, Personne *annuaire) {
    Personne personne;
    // Contient un entier qui vaut 0 si l'acquisition des informations
    // de la personne a échoué, sinon elle vaut 1 en cas de succès.
    int reussi = Acquisition(&personne);

    // Si l'acquisition a échoué, on quitte la fonction avec return.
    if (reussi == 0) {
        return;
    } else { // Dans le cas contraire, on ajoute la personne dans l'annuaire.
        if (*nb_personnes < T_ANNUAIRE) {
            annuaire[*nb_personnes] = personne;
            (*nb_personnes)++;
        } else {
            annuaire = realloc(&annuaire, *nb_personnes + 1);
            (*nb_personnes)++;
        }
    }

    // À la fin, le tableau est trié par rapport au nom
    Trier(annuaire, *nb_personnes);
}

/**
 * Liste toutes les personnes présentes dans l'annuaire
 * @param annuaire       est le tableau qui contient toutes les personnes
 * @param nb_personnes   est le nombre des personnes présentes dans le tableau annuaire
 */
void Affiche(int nb_personnes, Personne *annuaire) {
    printf("\n==> ANNUAIRE DES PERSONNES <==\n--------------------------------\n");

    if (nb_personnes == 0) {
        printf("    Aucune personne n'est enregistré\n\n");
        return;
    }
    else {
        for (int i = 0; i < nb_personnes ; ++i) {
            printf("    %d. %s : %s\n", (i+1), &annuaire[i].nom, &annuaire[i].telephone);
        }
        printf("=================================\n\n");
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
        Formatter_nom(nom);

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
    Formatter_nom(nom);

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
void Trier(Personne *annuaire, int nb_personnes) {
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
void Formatter_nom(char *nom) {
    nom[0] = (char) toupper(nom[0]);
    for (int i = 1; i < strlen(nom); ++i) {
        nom[i] = (char) tolower(nom[i]);
    }
}