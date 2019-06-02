#pragma once
#ifndef CMATRICEFICHIER_H
#define CMATRICEFICHIER_H

#include "CMatrice.h"
#include "CParseur.h"
#include "CMatriceException.h"
#include <fstream>

class CMatriceFichier
{
public:

	/*************************************************************************
	**** Nom: MAFLireFichier                                              ****
	**************************************************************************
	**** Permet de lire, d'interpreter et de construire une matrice a     ****
	****    partir d'un fichier                                           ****
	**************************************************************************
	**** Pr�condition:                                                    ****
	**** Entr�e:                                                          ****
	****    pcChemin : const char* => Chemin d'acc�s au fichier � lire.   ****
	**** Entra�ne: Peut lever une CMatriceException si :                  ****
	****    - le fichier n'a pas �t� trouv�                               ****
	****    - une ligne est jug�e incorrecte                              ****
	****    - le nombre de lignes ou le nombre de colonnes est jug�       ****
	****    incorrecte                                                    ****
	****    Peut lever une CParseurException si :                         ****
	****    - il manque un signe d'�galit� dans la d�claration d'une      ****
	****    variable                                                      ****
	**** Sortie: CMatrice<double>* => Matrice lue � partir du fichier     ****
	*************************************************************************/
	CMatrice<double>* MAFLireFichier(const char* pcChemin);
};

#endif // !CMATRICEFICHIER_H

