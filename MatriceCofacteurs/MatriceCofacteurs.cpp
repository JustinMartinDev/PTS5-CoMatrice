// MatriceCofacteurs.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <iostream>

#include "CMatrice.h"
#include "CCalculMatriciel.h"
#include "CMatriceFichier.h"

int main(int argc, char**argv){
	CCalculMatriciel<double>* dCALBoiteAOutil = new CCalculMatriciel<double>();
	CMatriceFichier* MAFMatriceLecteurFichier = new CMatriceFichier();
	
	unsigned int uiIndexPath = 0;
	for (uiIndexPath = 1; uiIndexPath < argc; uiIndexPath++) {
		try {
			CMatrice<double> dMATMatrice = *MAFMatriceLecteurFichier->MAFLireFichier(argv[uiIndexPath]);
			CMatrice<double> dMATComatrice = dCALBoiteAOutil->CALCalculerComatrice(dMATMatrice);
			dMATComatrice.MATAfficherMatrice();
			//std::cout << dCALBoiteAOutil->CALCalculerDeterminant(dMATMatrice) << std::endl;
		}catch (CMatriceException meException) {
			meException.MATEAfficher();
		}
	}
	return 0;
}
