#ifndef CMatriceException_H
#define CMatriceException_H

#ifndef ERROR_MAX_SIZE 
#define ERROR_MAX_SIZE 500
#endif

#include "CException.h"
#include <stdio.h>
#include <string.h>
#include <iostream>


//Trigrame est devenue un Quadragrame pour ne pas confondre avec CMatrice
class CMatriceException : public CException {
private:
	char* message;
public:
	/***************************************************************
	**** Nom: CMatriceException                                 ****
	****************************************************************
	**** Constructeur de confort de la classe CMatriceException ****
	****************************************************************
	**** Précondition:                                          ****
	**** Entrée: Valeur à prendre pour l'attribut uiEXCErreur   ****
	**** Entraîne:                                              ****
	**** Sortie:                                                ****
	***************************************************************/
	CMatriceException(unsigned int uiErreur) : CException(uiErreur) {}

	/***************************************************************************
	**** Nom: CMatriceException(unsigned int uiErreur, const char* message) ****
	****************************************************************************
	**** Constructeur de confort de la classe CMatriceException             ****
	****************************************************************************
	**** Précondition:                                                      ****
	**** Entrée: uiErreur : unsigned int => Code de l'erreur                ****
	****    message : const char* => Message à afficher                     ****
	**** Entraîne:                                                          ****
	**** Sortie:                                                            ****
	***************************************************************************/
	CMatriceException(unsigned int uiErreur, const char* message);

	/***************************************************
	**** Nom: ~CMatriceException()                  ****
	****************************************************
	**** Destructeur de la classe CMatriceException ****
	****************************************************
	**** Précondition:                              ****
	**** Entrée:                                    ****
	**** Entraîne:                                  ****
	**** Sortie:                                    ****
	***************************************************/
	~CMatriceException();

	/************************************************
	**** Nom: void MATEAfficher()                ****
	*************************************************
	**** Affiche l'erreur sur la sortie d'erreur ****
	*************************************************
	**** Précondition:                           ****
	**** Entrée:                                 ****
	**** Entraîne:                               ****
	**** Sortie:                                 ****
	************************************************/
	void MATEAfficher() {
		if (message != NULL)
			std::cout << message << std::endl;
	};
};

#endif