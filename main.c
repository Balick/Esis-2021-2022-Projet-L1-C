/**
 * @author Théo Balick
 */

#include "fonctions_affichage.h"
#include "Personne.h"

int main() {

    // Affichage du message d'accueil
    Message_accueil();

    // Déclaration des variables et autres types

    Personne annuaire[NOMBRE_PERSONNES]; // Annuaire du tableau des personnes
    int num_operation; // Numéro de l'opération
    int nb_personnes; // Nombre des personnes dans le tableau
    char entree_utilisateur[255]; // Donnée entrée au clavier par l'utilisateur

    // Initialisation de la variable nb_personnes
    // Initialisation à 0 parce qu'au début l'annuaire est vide
    nb_personnes = 0;

    // Le programme doit tourner continuellement jusqu'à ce que l'utilisateur décide de
    // quitter, On met en place une boucle pour permettre au programme de tourner en boucle

    while (1) {

        // Affichage des propositions du menu
        Affiche_menu();


        // Message de demande de saisie d'une valeur
        printf("*-------------------------------------------------------------------*\n");
        printf("|  *-> Entrer le numero de l'operation que vous souhaitez effectuer |\n");
        printf("*-------------------------------------------------------------------* : ");

        // La variable entree_utilisateur devrait nécessairement etre une chaine de caractères
        // pour éviter le plantage du programme en cas de saisie d'une valeur d'un type différent de la variable
        // La chaine de caractères justement permet de convertir toutes les saisies de l'utilisateur en chaine de caractères
        // Si par exemple le type de la variable entree_utilisateur était un entier, le programme planterait si l'utilisateur
        // saisi une lettre par exemple ou un caractère qui n'est pas un nombre.

        scanf("%s", &entree_utilisateur); // Attente de la machine pour la saisie d'une valeur

        // Si la saisie entrée au clavier contient plus d'un caractère,
        // un message d'erreur est affiché et le programme continue de tourner en ignorant
        // la suite du fichier et en retournant au point ou le programme demande
        // à l'utilisateur de saisir le numéro de l'opération
        if (strlen(entree_utilisateur) != 1) {
            Message_erreur_operation(entree_utilisateur);
            continue;
        }

        // Conversion de la valeur de la variable entree_utilisateur en un entier
        // pour la stocker dans la variable num_operation
        num_operation = strtol(entree_utilisateur, NULL, 10);

        switch (num_operation) {
            case 1: Ajoute(&nb_personnes, annuaire);
                break;
            case 2: Affiche(nb_personnes, annuaire);
                break;
            case 3: Efface(annuaire, &nb_personnes);
                break;
            case 4: RechercheTel(annuaire, nb_personnes);
                break;
            case 5: RechercheNom(annuaire, nb_personnes);
                break;
            case 6: return 0;
            default:
                // Dans le cas ou l'utilisateur n'a pas saisi un chiffre qui correspond à une opération disponible :
                // Un message d'erreur est affiché
                Message_erreur_operation(entree_utilisateur);
                // et le programme doit continuer de tourner
                continue;
        }

    }
}
