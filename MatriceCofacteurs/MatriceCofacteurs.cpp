// MatriceCofacteurs.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <iostream>

#include "CMatrice.h"
#include "CCalculMatriciel.h"

int main(){
    CMatrice<int> iMATCarre3(3); //Instancie une matrice carrée d'entier et avec comme taille 3

	iMATCarre3.MATModifierElement(0, 0, 5);
	iMATCarre3.MATModifierElement(0, 1, 6);
	iMATCarre3.MATModifierElement(0, 2, 7); //modifie l'élément à la position 0,2 et le remplace par la valeur 7
	iMATCarre3.MATModifierElement(1, 0, 8);
	iMATCarre3.MATModifierElement(1, 1, 9);
	iMATCarre3.MATModifierElement(1, 2, 10);
	iMATCarre3.MATModifierElement(2, 0, 11);
	iMATCarre3.MATModifierElement(2, 1, 12);
	iMATCarre3.MATModifierElement(2, 2, 14);

	CCalculMatriciel<int>* iCALBoiteAOutil = new CCalculMatriciel<int>();

	try {
		(iCALBoiteAOutil->CALCalculerComatrice(iMATCarre3)).MATAfficherMatrice();
	}
	catch (CMatriceException meException) {
		meException.MATEAfficher();
	}
	
}
