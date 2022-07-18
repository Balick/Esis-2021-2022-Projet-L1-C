// Inclusion des donn�es d�finies
#include "Personne.h"
#include "fonctions_affichage.h"


int Acquisition(Personne* personne) {

    char nom_personne[TAILLE_CHAINES]; // Nom de la personne
    char telephone_personne[TAILLE_CHAINES]; // T�l�phone de la personne

    printf("*-> Entrer le nom de la personne que vous voulez ajouter : "); // ceci est un message

    scanf("%s", &nom_personne); // La machine attend qu'une valeur soit saisie
    // Mis en forme du nom en mettant la premi�re lettre en majuscule et les autres en miniscule
    Mettre_en_forme_nom(nom_personne);

    printf("*-> Entrer le numero de la personne que vous voulez ajouter : "); // ceci est un message

    scanf("%s", &telephone_personne); // La machine attend qu'une valeur soit saisie
    printf("\n"); // Saut de ligne pour un bon affichage

    // Si le nom saisi poss�de plus de 30 caract�res
    if (strlen(nom_personne) > 30) {
        Message_erreur_nom(); // ceci est un message
        return 0; // 0 est retourn� pour dire que l'acquisition n'a pas r�ussi
    }

    // Si le num�ro saisi poss�de plus de 10 chiffres et
    // si le num�ro de t�l�phone commence avec 08 ou 09 ce qui veut dire que le premier chiffre doit etre 0 et le deuxi�me 8 ou 9
    // Si toutes les conditions ci-dessus sont remplis, alors le num�ro de t�l�phone est valide
    if (strlen(telephone_personne) == 10 && telephone_personne[0] == '0' && (telephone_personne[1] == '8' || telephone_personne[1] == '9')) {
        // et si le num�ro de t�l�phone contient le caract�re '-'
        if (strstr(telephone_personne, "-") == NULL) {
            // Copie de la valeur de nom_personne dans l'attribut nom de la structure personne
            strcpy(personne->nom, nom_personne);
            // Copie de la valeur de telephone_personne dans l'attribut telephone de la structure personne
            strcpy(personne->telephone, telephone_personne);
            return 1; // 1 est retourn� pour dire que l'acquisition a r�ussi
        }
    }

    // Dans le cas contraire de la condition ci-haut, le num�ro n'est pas valide
    Message_erreur_telephone(); // Message d'erreur
    return 0; // 0 est retourn� pour dire que l'acquisition n'a pas r�ussi
}


void Ajoute(int *nombre_total_personnes, Personne *annuaire) {
    Personne personne_a_ajouter; // Personne � ajouter dans l'annuaire

    // D�finition des valeurs des attributs pour personne_a_ajouter
    // et stockage de la valeur de retour dans la variable acquisition_reussi
    // Pour rappel, la fonction Acquisition renvoie 1 en cas de r�ussite et 0 dans le cas contraire
    int acquisition_reussi = Acquisition(&personne_a_ajouter);

    if (acquisition_reussi) {
        // Si le tableau annuaire est plein, il est agrandi gr�ce � la fonction realloc
        // Cette derni�re prend en param�tre l'adresse du tableau � agrandir ainsi que la nouvelle taille.
        if (*nombre_total_personnes > NOMBRE_PERSONNES_ANNUAIRE) {
            annuaire = realloc(annuaire, NOMBRE_PERSONNES_ANNUAIRE * 2);
        }

        annuaire[*nombre_total_personnes] = personne_a_ajouter; // Ajout de la personne dans le tableau annuaire
        (*nombre_total_personnes)++; // Incr�mentation du nombre total des personnes dans l'annuaire

        Trier_tableau_annuaire(annuaire, *nombre_total_personnes); // Trie du tableau par ordre alphab�tique
    }
}


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


void Efface(Personne *annuaire, int *nombre_total_personnes) {

    // Si le tableau annuaire n'est pas vide
    if (*nombre_total_personnes >= 1) {
        char nom_personne[TAILLE_CHAINES]; // Nom de la personne � supprimer
        int numero_personne = 0; // Position de la personne dans l'annuaire

        printf("*-> Entrer le nom de la personne que vous souhaitez effacer dans l'annuaire : "); // Ceci est un message
        scanf("%s", &nom_personne); // Attente d'une saisie des donn�es au clavier
        printf("\n");
        Mettre_en_forme_nom(nom_personne); // Met la premi�re lettre en majuscule et les autres en miniscule

        // Si l'annuaire ne contient qu'une personne
        // le nombre total des personnes dans le tableau est soustrait de 1 et on quitte la fonction
        if (*nombre_total_personnes == 1) {
            *nombre_total_personnes -= 1;
            return;
        }

       // Parcours du tableau annuaire
        for (int i = 0; i < *nombre_total_personnes; ++i) {
            // Si le nom de la personne de l'it�ration en cours correspond au nom saisi par l'utilisateur
            // on m�morise le num�ro de la personne dans l'annuaire et on quitte la boucle
            if (strcmp(annuaire[i].nom, nom_personne) == 0) {
                numero_personne = i;
                break;
            }
        }

        // � partir du num�ro de la personne � supprimer,
        // le num�ro de chaque personne est remplac� par son pr�c�dent
        // En bref, la position de chaque personne dans le tableau est decall� de -1
        for (int i = numero_personne; i < *nombre_total_personnes; ++i) annuaire[i] = annuaire[i+1];

        *nombre_total_personnes -= 1; // R�duction du nombre des personnes total dans l'annuaire
    } else {
        printf("*-> L'annuaire est vide, il n'y a personne � effacer.\n");
    }
}


void RechercheTel(Personne *annuaire, int nombre_total_personnes) {
    char nom_personne[50]; // Nom de la personne

    printf("*-> Veuillez entrer le nom de personne pour qui vous chercher le numero : "); // Ceci est un message
    scanf("%s", &nom_personne); // Attente d'une valeur
    Mettre_en_forme_nom(nom_personne); // Met la premi�re lettre en majuscule et les autres en miniscule

    // Parcours de l'annuaire
    for (int i = 0; i < nombre_total_personnes; ++i) {
        // Si le nom de la personne courante dans la boucle correspond au nom saisi pas l'utilisateur
        // On affiche son num�ro et on quitte la fonction
        if (strcmp(annuaire[i].nom, nom_personne) == 0) {
            printf("*-> %s utilise le num�ro de telephone : %s\n\n", nom_personne, &annuaire[i].telephone);
            return;
        }
    }
    printf("*-> Aucun numero n'est enregistre avec le nom %s\n\n", nom_personne);
}


void RechercheNom(Personne *annuaire, int nombre_total_personnes) {
    char telephone_personne[50]; // Nom de la personne

    printf("*-> Veuillez entrer le numero de la personne pour qui vous chercher le nom : "); // Ceci est un message
    scanf("%s", &telephone_personne); // Attente d'une valeur

    // Parcours de l'annuaire
    for (int i = 0; i < nombre_total_personnes; ++i) {
        // Si le num�ro de la personne courante dans la boucle correspond au num�ro saisi pas l'utilisateur
        // On affiche son nom et on quitte la fonction
        if (strcmp(annuaire[i].telephone, telephone_personne) == 0) {
            printf("*-> Le numero %s appartient a %s \n\n", telephone_personne, &annuaire[i].nom);
            return;
        }
    }
    printf("*-> Aucun nom n'est enregistre a ce numero %s\n\n", telephone_personne);
}


void Trier_tableau_annuaire(Personne *annuaire, int nombre_total_personnes) {
    Personne temp; // Ceci est une variable temporaire

    // Principe du trie: Chaque �l�ment courant dans la premi�re boucle est
    // compar� avec tous les �l�ments de ce que rencontre la deuxi�me boucle
    // En bref, c'est comme si chaque �l�ment est compar� avec tous les autres �l�ments du tableau
    // si l'�l�ment courant de la deuxi�me boucle est plus petit que celui de la premi�re boucle,
    // alors les deux valeurs sont �chang�es � leurs positions
    // Pour rappel en programmation : le caract�re 'a' est plus petit que le caract�re 'b'

    for (int i = 0; i < nombre_total_personnes; ++i) {
        for (int j = 0; j <= nombre_total_personnes; ++j) {
            // Si le nom de la deuxi�me boucle est plus petit que celui de la premi�re boucle
            // Les valeurs de deux sont �chang�es � l'aide de la variable interm�diaire
            if (strcmp(annuaire[i].nom, annuaire[j].nom) == -1) {
                temp = annuaire[i];
                annuaire[i] = annuaire[j];
                annuaire[j] = temp;
            }
        }
    }
}


void Mettre_en_forme_nom(char *nom_personne) {
    nom_personne[0] = (char) toupper(nom_personne[0]); // Met la premi�re lettre en majuscule

    // Parcours de la chaine
    for (int i = 1; i < strlen(nom_personne); ++i) {
        nom_personne[i] = (char) tolower(nom_personne[i]); // Met le caract�re en miniscule
    }
}
