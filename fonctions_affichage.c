
#include "fonctions_affichage.h"

void Message_accueil(void) {
    printf("*--------------------------------------------------------------------------------------*\n");
    printf("|                                                                                      |\n");
    printf("|                       Mini-Projet de C pour la promotion L1                          |\n");
    printf("|                                 Copyright 2021-2022                                  |\n");
    printf("|                                                                                      |\n");
    printf("*--------------------------------------------------------------------------------------*\n\n");
}

void Affiche_menu(void) {
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
}

void Message_demander_operation(void) {
    printf("*-------------------------------------------------------------------*\n");
    printf("|  *-> Entrer le numero de l'operation que vous souhaitez effectuer |\n");
    printf("*-------------------------------------------------------------------* : ");
}

void Message_erreur_operation(char *num_operation) {
    printf("\n*-------------------------------------------------------------------*\n");
    printf("|     ERREUR :  Aucune operation ne correspond a votre entree       |=> %s\n", num_operation);
    printf("*-------------------------------------------------------------------*\n\n");
    printf("\a"); // Déclenchement d'un bip sonore lors du message d'erreur
}
