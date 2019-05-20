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
	**** Pr�condition:                                          ****
	**** Entr�e: Valeur � prendre pour l'attribut uiEXCErreur   ****
	**** Entra�ne:                                              ****
	**** Sortie:                                                ****
	***************************************************************/
	CMatriceException(unsigned int uiErreur) : CException(uiErreur) {}

	/***************************************************************************
	**** Nom: CMatriceException(unsigned int uiErreur, const char* message) ****
	****************************************************************************
	**** Constructeur de confort de la classe CMatriceException             ****
	****************************************************************************
	**** Pr�condition:                                                      ****
	**** Entr�e: uiErreur : unsigned int => Code de l'erreur                ****
	****    message : const char* => Message � afficher                     ****
	**** Entra�ne:                                                          ****
	**** Sortie:                                                            ****
	***************************************************************************/
	CMatriceException(unsigned int uiErreur, const char* message);

	/***************************************************
	**** Nom: ~CMatriceException()                  ****
	****************************************************
	**** Destructeur de la classe CMatriceException ****
	****************************************************
	**** Pr�condition:                              ****
	**** Entr�e:                                    ****
	**** Entra�ne:                                  ****
	**** Sortie:                                    ****
	***************************************************/
	~CMatriceException();

	/************************************************
	**** Nom: void MATEAfficher()                ****
	*************************************************
	**** Affiche l'erreur sur la sortie d'erreur ****
	*************************************************
	**** Pr�condition:                           ****
	**** Entr�e:                                 ****
	**** Entra�ne:                               ****
	**** Sortie:                                 ****
	************************************************/
	void MATEAfficher() {
		if (message != NULL)
			std::cout << message << std::endl;
	};
};

#endif