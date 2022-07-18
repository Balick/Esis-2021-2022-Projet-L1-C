#ifndef PROJET_C_L1_PERSONNE_H
#define PROJET_C_L1_PERSONNE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Constante. Représente la taille maximale des chaines de caractères
#define TAILLE_CHAINES 255
// Constante. Représente la taille maximale du tableau des personnes
#define NOMBRE_PERSONNES_ANNUAIRE 1

typedef struct Personne Personne; // Question 1
struct Personne {
    // Nom de la personne
    char nom[TAILLE_CHAINES];
    // Téléphone de la personne
    char telephone[TAILLE_CHAINES];
};


int Acquisition(Personne* personne); // Question 3
void Ajoute(int* nombre_total_personnes, Personne *annuaire);
void Affiche(int nombre_total_personnes, Personne *annuaire);
void Efface(Personne *annuaire, int *nombre_total_personnes);
void RechercheTel(Personne *annuaire, int nombre_total_personnes);
void RechercheNom(Personne *annuaire, int nombre_total_personnes);
void Trier_tableau_annuaire(Personne *annuaire, int nombre_total_personnes);
void Mettre_en_forme_nom(char *nom_personne);

#endif
