/**
 * @author Théo Balick
 */

#include "Personne.h"

int main() {

    /**************************************** Ceci est un message d'accueil **************************************/

    printf("*--------------------------------------------------------------------------------------*\n");
    printf("|                                                                                      |\n");
    printf("|                       Mini-Projet de C pour la promotion L1                          |\n");
    printf("|                                 Copyright 2021-2022                                  |\n");
    printf("|                                                                                      |\n");
    printf("*--------------------------------------------------------------------------------------*\n\n");

    /********************************** Déclaration des variables et autres types *********************************/

    Personne annuaire[NOMBRE_PERSONNES]; // Annuaire du tableau des personnes
    int num_operation; // Numéro de l'opération
    int nb_personnes; // Nombre des personnes dans le tableau

    // Initialisation de la variable nb_personnes
    // Initialisation à 0 parce qu'au début l'annuaire est vide
    nb_personnes = 0;

    // Le programme doit tourner continuellement jusqu'à ce que l'utilisateur décide de
    // quitter, On met en place une boucle pour permettre au programme de tourner en boucle

    while (1) {

        /*********************************** Affichage des propositions du menu ************************************/

        printf("*--------------------------------------------------------------------------------------*\n");
        printf("|             *-> Operations a effectuer :                                             |\n");
        printf("|                                                                                      |\n");
        printf("|             1. Ajouter une personne a l'annuaire                                     |\n");
        printf("|             2. Afficher le contenu de l'annuaire dans l'ordre alphabetique           |\n");
        printf("|             3. Supprimer une personne de l'annuaire                                  |\n");
        printf("|             4. Consulter le numero de telephone d'une personne                       |\n");
        printf("|             5. Trouver a qui appartient un certain numero                            |\n");
        printf("|             6. Sortir du programme                                                   |\n");
        printf("|                                                                                      |\n");
        printf("*--------------------------------------------------------------------------------------*\n\n");


        // Démande à l'utilisateur de saisir une valeur
        printf("*-------------------------------------------------------------------*\n");
        printf("|  *-> Entrer le numero de l'operation que vous souhaitez effectuer |\n");
        printf("*-------------------------------------------------------------------* : ");
        scanf("%d", &num_operation);

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
                printf("\n*-------------------------------------------------------------------*\n");
                printf("|        ERREUR :  Aucune operation ne correspond a ce numero       |=> %d\n", num_operation);
                printf("*-------------------------------------------------------------------*\n\n");
                printf("\a"); // Déclenchement d'un bip sonore lors du message d'erreur
                // et le programme doit continuer de tourner
                continue;
        }

    }
}
