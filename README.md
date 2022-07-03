Mini-Projet en Langage C 

L1 ESIS

Année 2021-2022

Objectif :
Ce projet a pour objectif l’application directe de notions et concepts vus en 
cours et TD/TP. 

Travail demandé :

1/ Définir un type de données Personne permettant de mémoriser les
informations relatives à une personne telles que son nom et son numéro de
téléphone. 

2/ Définir un tableau de personnes, de taille fixe, nommé Annuaire.

3/ Écrire une fonction Acquisition() qui permet l'acquisition au clavier du
nom de la personne et de son numéro de téléphone.
On vérifiera dans cette fonction que :
✔ le nom de la personne ne dépasse pas 30 caractères
✔ le numéro de téléphone est un nombre positif à 10 chiffres qui
commence soit par 08 ou soit 09
Si ces conditions sont vérifiées, la valeur de retour de la fonction vaut 1, et le
nom et le numéro de la personne sont renvoyés au programme appelant. Dans
le cas contraire, un message d'erreur est envoyé à l'opérateur et la valeur de
retour de la fonction vaut 0.

4/ Écrire une fonction Ajoute() qui ajoute à Annuaire un nom et un numéro de
téléphone associé. Si le nom de la personne ne figurait pas dans Annuaire, un
nouvel élément est ajouté à la liste, s’il figurait déjà, le numéro de téléphone
existant est remplacé par le nouveau numéro de téléphone. Cette fonction doit
également permettre de mettre à jour l’ordre des éléments en fonction de
l’ordre alphabétique. Si le tableau est plein, il faudrait procéder à son
agrandissement (stratégie à définir).

5/ Écrire une fonction Affiche() qui affiche le contenu de l'annuaire dans
l’ordre alphabétique.

7/ Écrire une fonction RechercheTel() qui, pour un nom de personne donné,
affiche :
 son numéro de téléphone si le nom figure dans l'annuaire
 le message « pas de personne à ce nom » si le nom ne figure pas dans
l'annuaire.

8/ Écrire une fonction RechercheNom() (recherche inversée) qui, pour un
numéro de téléphone donné, recherche dans l’annuaire, à quel nom est
associé le numéro , affiche :
 le nom, si le numéro figure dans l'annuaire
 le message « pas ce numéro dans l'annuaire!» sinon. 

9/ Écrire une fonction Efface() qui, pour un nom de personne donné supprime
l’élément de la liste. Si la personne n'existe pas le message «pas de personne
avec ce nom» est affiché.

10/ Écrire un programme principal constitué d'un menu permettant :
1. - d'ajouter une personne à l'annuaire
2. - d'afficher le contenu de l'annuaire dans l'ordre alphabétique
3. - de supprimer une personne de l'annuaire
4. - de consulter le numéro de téléphone d'une personne
5. - de trouver à qui appartient un certain numéro 
6. - de sortir du programme
NB : On supposera qu'il n'y a pas d'homonymes et que chaque personne n’a
qu’un numéro de téléphone. 

Bon courage à toutes et à tous
Prof Musumbu 
