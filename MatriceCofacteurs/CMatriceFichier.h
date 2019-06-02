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
	**** Précondition:                                                    ****
	**** Entrée:                                                          ****
	****    pcChemin : const char* => Chemin d'accès au fichier à lire.   ****
	**** Entraîne: Peut lever une CMatriceException si :                  ****
	****    - le fichier n'a pas été trouvé                               ****
	****    - une ligne est jugée incorrecte                              ****
	****    - le nombre de lignes ou le nombre de colonnes est jugé       ****
	****    incorrecte                                                    ****
	****    Peut lever une CParseurException si :                         ****
	****    - il manque un signe d'égalité dans la déclaration d'une      ****
	****    variable                                                      ****
	**** Sortie: CMatrice<double>* => Matrice lue à partir du fichier     ****
	*************************************************************************/
	CMatrice<double>* MAFLireFichier(const char* pcChemin);
};

#endif // !CMATRICEFICHIER_H

