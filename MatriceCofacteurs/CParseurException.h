#pragma once


#ifndef ERROR_MAX_SIZE 
#define ERROR_MAX_SIZE 500
#endif

#include "CException.h"
#include <stdio.h>
#include <iostream>


class CParseurException : public CException
{
private:
	char* pcPAEMessage;

public:
	/***************************************************************
	**** Nom: CParseurException                                 ****
	****************************************************************
	**** Constructeur de confort de la classe CParseurException ****
	****************************************************************
	**** Pr�condition:                                          ****
	**** Entr�e: Valeur � prendre pour l'attribut uiEXCErreur   ****
	**** Entra�ne:                                              ****
	**** Sortie:                                                ****
	***************************************************************/
	CParseurException(unsigned int uiErreur) : CException(uiErreur) {}


	/***************************************************************************
	**** Nom: CParseurException(unsigned int uiErreur, const char* message) ****
	****************************************************************************
	**** Constructeur de confort de la classe CParseurException             ****
	****************************************************************************
	**** Pr�condition:                                                      ****
	**** Entr�e: uiErreur : unsigned int => Code de l'erreur                ****
	****    message : const char* => Message � afficher                     ****
	**** Entra�ne:                                                          ****
	**** Sortie:                                                            ****
	***************************************************************************/
	CParseurException(unsigned int uiErreur, const char* message);


	/***************************************************
	**** Nom: ~CParseurException()                  ****
	****************************************************
	**** Destructeur de la classe CParseurException ****
	****************************************************
	**** Pr�condition:                              ****
	**** Entr�e:                                    ****
	**** Entra�ne:                                  ****
	**** Sortie:                                    ****
	***************************************************/
	~CParseurException();


	/************************************************
	**** Nom: void PAEAfficher()                ****
	*************************************************
	**** Affiche l'erreur sur la sortie d'erreur ****
	*************************************************
	**** Pr�condition:                           ****
	**** Entr�e:                                 ****
	**** Entra�ne:                               ****
	**** Sortie:                                 ****
	************************************************/
	void PAEAfficher() {
		if (pcPAEMessage != NULL)
			std::cout << pcPAEMessage << std::endl;
	};
};

