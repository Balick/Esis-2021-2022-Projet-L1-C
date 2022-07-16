/**
 * @author Théo Balick
 */

#ifndef PROJET_C_L1_PERSONNE_H
#define PROJET_C_L1_PERSONNE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAILLE_MAX 255
#define NOMBRE_PERSONNES 10

static char tab[TAILLE_MAX][50] = {{}};

typedef struct Personne Personne;
struct Personne {
    char nom[TAILLE_MAX];
    char telephone[TAILLE_MAX];
};

int Acquisition(Personne* personne);
void Ajoute(int* nb_personnes, Personne *annuaire);
void Affiche(int nb_personnes, Personne *annuaire);
int Efface(Personne *annuaire, int *nb_personnes);
void RechercheTel(Personne *annuaire, int nb_personnes);
void RechercheNom(Personne *annuaire, int nb_personnes);
void Trier(Personne *annuaire, int nb_personnes);
void Formatter_nom(char *nom);

#endif