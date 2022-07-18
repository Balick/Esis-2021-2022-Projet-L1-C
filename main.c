#include "fonctions_affichage.h"
#include "Personne.h" // Inclusion des donn�es d�finies

int main() {

    // Affichage du message d'accueil
    Message_accueil();

    // D�claration des variables et autres types

    Personne *annuaire = NULL; // Annuaire du tableau des personnes
    annuaire = malloc(NOMBRE_PERSONNES_ANNUAIRE * sizeof(Personne)); // Allocation de la m�moire. Question 2

    if (annuaire == NULL) {
        printf("Erreur, l'allocation de la m�moire a �chou�e !\a");
        exit(EXIT_FAILURE);
    }

    int num_operation; // Num�ro de l'op�ration
    int nb_personnes; // Nombre des personnes dans le tableau
    char entree_utilisateur[255]; // Donn�e entr�e au clavier par l'utilisateur

    // Affectation de la variable nb_personnes
    // Initialisation � 0 parce qu'au d�but l'annuaire est vide
    nb_personnes = 0;

    // Le programme doit tourner continuellement jusqu'� ce que l'utilisateur d�cide de
    // quitter, On met en place une boucle pour permettre au programme de tourner en boucle

    while (1) {

        // Affichage des propositions du menu
        Affiche_menu();


        // Message de demande de saisie d'une valeur
        printf("*-> Entrer le numero de l'operation que vous souhaitez effectuer : ");

        // La variable entree_utilisateur devrait n�cessairement etre une chaine de caract�res
        // pour �viter le plantage du programme en cas de saisie d'une valeur d'un type diff�rent de la variable
        // La chaine de caract�res justement permet de convertir toutes les saisies de l'utilisateur en chaine de caract�res
        // Si par exemple le type de la variable entree_utilisateur �tait un entier, le programme planterait si l'utilisateur
        // saisi une lettre par exemple ou un caract�re qui n'est pas un nombre.

        scanf("%s", &entree_utilisateur); // Attente de la machine pour la saisie d'une valeur
        printf("\n");

        // Si la saisie entr�e au clavier contient plus d'un caract�re,
        // un message d'erreur est affich� et le programme continue de tourner en ignorant
        // la suite du fichier et en retournant au point ou le programme demande
        // � l'utilisateur de saisir le num�ro de l'op�ration
        if (strlen(entree_utilisateur) != 1) {
            Message_erreur_operation(entree_utilisateur);
            continue;
        }

        // Conversion de la valeur de la variable entree_utilisateur en un entier
        // pour la stocker dans la variable num_operation
        num_operation = strtol(entree_utilisateur, NULL, 10);

        if (num_operation == 1) {
            Ajoute(&nb_personnes, annuaire);
        } else if (num_operation == 2) {
            Affiche(nb_personnes, annuaire);
        } else if (num_operation == 3) {
            Efface(annuaire, &nb_personnes);
        } else if (num_operation == 4) {
            RechercheTel(annuaire, nb_personnes);
        } else if (num_operation == 5) {
            RechercheNom(annuaire, nb_personnes);
        } else if (num_operation == 6) {
            break;
        } else {
            // Dans le cas ou l'utilisateur n'a pas saisi un chiffre qui correspond � une op�ration disponible :
            // Un message d'erreur est affich�
            Message_erreur_operation(entree_utilisateur);
            // et le programme doit continuer de tourner
            continue;
        }

    }

    free(annuaire); // Lib�ration de la m�moire allou�e par le tableau annuaire
    exit(EXIT_SUCCESS); // Fin du programme avec un code qui indique que tout s'est bien pass�
}
