#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <malloc.h>

using namespace std;

typedef struct Noeud {
    struct Noeud* fdroite;
    struct Noeud* fgauche;

    int n_data;
} Noeud;

typedef struct arbre_binaire {

    Noeud* racine;

} arbre_binaire;




arbre_binaire initialisation(arbre_binaire pArbre, int n_data) {

    Noeud* newNoeud = (Noeud*)malloc(sizeof(Noeud));
    newNoeud->fgauche = nullptr;
    newNoeud->fdroite = nullptr;
    newNoeud->n_data = n_data;
    pArbre.racine = newNoeud;
    return pArbre;
}

void affichage(Noeud* racine) {

    if (racine != nullptr) {
        affichage(racine->fgauche);
        printf(" %d ", racine->n_data);
        affichage(racine->fdroite);
    }
    return;
}

int ProfondeurArbre(Noeud* racine)
{
    int profDroite, profGauche, profondeur;

    //si l'arbre est vide on retourne -1
    if (racine == nullptr)
    {
        profondeur = -1;
    }
    else
    {
        //calcul de la profondeur du sous arbre droit
        profDroite = ProfondeurArbre(racine->fdroite);
        //calcul de la profondeur du sous arbre gauche
        profGauche = ProfondeurArbre(racine->fgauche);

        profondeur = 1 + (profGauche > profDroite ? profGauche : profDroite);
    }
    return profondeur;
}

int compterNoeud(Noeud* racine) {
    if (racine == NULL)
        return 0;
    return 1 + compterNoeud(racine->fdroite) + compterNoeud(racine->fgauche);
}

int compterNoeudDroite(Noeud* racine) {
    if (racine == NULL)
        return 0;
    return 1 + compterNoeudDroite(racine->fdroite);
}

int compterNoeudGauche(Noeud* racine) {
    if (racine == NULL)
        return 0;
    return 1 + compterNoeudGauche(racine->fgauche);
}


int hauteurArbre(Noeud* racine) {
    if (racine == NULL)
        return 0;
    else
        return 1 + max(hauteurArbre(racine->fgauche), hauteurArbre(racine->fdroite));
}


int inserArbreVide(arbre_binaire* pArbre, int n_val) {

    Noeud* newNoeud = nullptr;
    newNoeud = (Noeud*)malloc(sizeof(Noeud));

    if (newNoeud == nullptr) {
        return 0;
    }
    else {
        newNoeud->n_data = n_val;

        newNoeud->fgauche = nullptr;
        newNoeud->fdroite = nullptr;
        pArbre->racine = newNoeud;

        return 1;

    }

}



int ajoutNoeud(Noeud* racine, int n_val)
{
    Noeud* newNoeud = nullptr;
    newNoeud = (Noeud*)malloc(sizeof(Noeud));

    // Verif si newNoeud existe
    if (newNoeud == nullptr) return -1;

    newNoeud->fdroite = nullptr;
    newNoeud->fgauche = nullptr;
    newNoeud->n_data = n_val;

    Noeud* courant = racine;

    // Verif si courant existe
    if (courant == nullptr) return -1;

    if (courant->n_data > newNoeud->n_data) {
        if (courant->fgauche == nullptr) courant->fgauche = newNoeud;
        else ajoutNoeud(courant->fgauche, n_val);
    }
    else {
        if (courant->fdroite == nullptr) courant->fdroite = newNoeud;
        else ajoutNoeud(courant->fdroite, n_val);
    }

    /*
    // On avance jusqu'à trouver une place
    while (courant)
    {
        precedent = courant;
        if (newNoeud->n_data < courant->n_data)
            courant = courant->fgauche;
        else
            courant = courant->fdroite;
    }

    // on a trouvé une place libre, et
   // precedent pointe vers le parent de notre
   // noeud à replacer.
    if (newNoeud->n_data < precedent->n_data)
        precedent->fgauche = newNoeud;
    else
        precedent->fdroite = newNoeud;
    */
    return 1;
}


void rotationDroite(Noeud* noeud, arbre_binaire* pArbre) {

    Noeud* Y = noeud;
    Noeud* X = Y->fgauche;
    Noeud* B = nullptr;

    if (X != nullptr) {

        B = X->fdroite;
        pArbre->racine = X;
        X->fdroite = Y;
    }

    Y->fgauche = B;
}



void rotationGauche(Noeud* noeud, arbre_binaire* pArbre) {

    Noeud* Y = noeud;
    Noeud* X = Y->fdroite;
    Noeud* B = nullptr;

    if (X != nullptr) {

        B = X->fgauche;
        pArbre->racine = X;
        X->fgauche = Y;
    }

    Y->fdroite = B;
}



void equilibrage(Noeud* noeud, arbre_binaire* pArbre) {

    bool isEquilibre = false;

    while (!isEquilibre) {

        int NbDroite = compterNoeudDroite(noeud);
        int NbGauche = compterNoeudGauche(noeud);

        cout << "\nLe nombre de noeud a droite est de " << NbDroite << endl;

        cout << "\nLe nombre de noeud a gauche est de " << NbGauche << endl;

        int equilibre = NbDroite - NbGauche;

        //cout << equilibre << endl;

        if (equilibre >= -1 && equilibre <= 1) {
            isEquilibre = true;
            cout << "\nL'arbre n'est qu'equilibre" << endl;
        }
        else {
            if (equilibre < -1)
                rotationDroite(noeud, pArbre);
            if (equilibre > 1)
                rotationGauche(noeud, pArbre);
        }
    }
}



int main() {

    // arbre_binaire arbre;
    // arbre.racine = nullptr;
    arbre_binaire pArbre;
    pArbre.racine = nullptr;
    //arbre_binaire* pArbre = nullptr;
    // arbre = initialisation(arbre, 21);

    // affichage(arbre.racine);
    // pArbre = initialisation(pArbre, 24);
    cout << "\nLe nombre de noeud est de " << compterNoeud(pArbre.racine) << endl;

    inserArbreVide(&pArbre, 10);
    ajoutNoeud(pArbre.racine, 20);
    ajoutNoeud(pArbre.racine, 8);
    ajoutNoeud(pArbre.racine, 5);
    ajoutNoeud(pArbre.racine, 6);
    ajoutNoeud(pArbre.racine, 4);
    ajoutNoeud(pArbre.racine, 3);
    ajoutNoeud(pArbre.racine, 1);
    ajoutNoeud(pArbre.racine, 100);

    cout << "\nLe nombre de noeud est de " << compterNoeud(pArbre.racine) << endl;
    affichage(pArbre.racine);

    equilibrage(pArbre.racine, &pArbre);

}

