/**
 * @author Théo Balick
 */

#include "Personne.h"

int main() {

    // Message d'accueil
    printf("/==================================================================/\n");
    printf("/                       Mini-Projet C L1                           /\n");
    printf("/                  Année scolaire : 2021-2022                     /\n");
    printf("/==================================================================/\n");

    // Création du tableau annuaire qui doit contenir des données de type personne
    Personne annuaire[T_ANNUAIRE];
    // Variable qui va contenir le numéro de l'opération entré par l'utilisateur
    int operation;
    // Contient les nombres des personnes present dans l'annuaire. Au début du programme il vaut 0
    int nombre_personnes = 0;

    while (1) {

        // Affichage des propositions du menu
        printf("==============>      Opérations disponibles      <================\n");
        printf("--------------------------------------------------------------------\n");
        printf("    1. Ajouter une personne à l'annuaire\n");
        printf("    2. Afficher le contenu de l'annuaire dans l'ordre alphabétique\n");
        printf("    3. Supprimer une personne de l'annuaire\n");
        printf("    4. Consulter le numéro de téléphone d'une personne\n");
        printf("    5. Trouver à qui appartient un certain numéro\n");
        printf("    6. Sortir du programme\n");
        printf("==================================================================\n");

        // Démande à l'utilisateur de saisir une valeur
        printf("==> Opération : ");
        scanf("%d", &operation);

        switch (operation) {
            case 1: Ajoute(&nombre_personnes, annuaire);
                break;
            case 2: Affiche(nombre_personnes, annuaire);
                break;
            case 3: Efface(annuaire, &nombre_personnes);
                break;
            case 4: RechercheTel(annuaire, nombre_personnes);
                break;
            case 5: RechercheNom(annuaire, nombre_personnes);
                break;
            case 6: return 0;
            default: printf("\n!!! ERREUR : Opération invalide !!!\n\n");
                continue;
        }
    }
}
