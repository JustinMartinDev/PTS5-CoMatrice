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
	**** Précondition:                                          ****
	**** Entrée: Valeur à prendre pour l'attribut uiEXCErreur   ****
	**** Entraîne:                                              ****
	**** Sortie:                                                ****
	***************************************************************/
	CParseurException(unsigned int uiErreur) : CException(uiErreur) {}


	/***************************************************************************
	**** Nom: CParseurException(unsigned int uiErreur, const char* message) ****
	****************************************************************************
	**** Constructeur de confort de la classe CParseurException             ****
	****************************************************************************
	**** Précondition:                                                      ****
	**** Entrée: uiErreur : unsigned int => Code de l'erreur                ****
	****    message : const char* => Message à afficher                     ****
	**** Entraîne:                                                          ****
	**** Sortie:                                                            ****
	***************************************************************************/
	CParseurException(unsigned int uiErreur, const char* message);


	/***************************************************
	**** Nom: ~CParseurException()                  ****
	****************************************************
	**** Destructeur de la classe CParseurException ****
	****************************************************
	**** Précondition:                              ****
	**** Entrée:                                    ****
	**** Entraîne:                                  ****
	**** Sortie:                                    ****
	***************************************************/
	~CParseurException();


	/************************************************
	**** Nom: void PAEAfficher()                ****
	*************************************************
	**** Affiche l'erreur sur la sortie d'erreur ****
	*************************************************
	**** Précondition:                           ****
	**** Entrée:                                 ****
	**** Entraîne:                               ****
	**** Sortie:                                 ****
	************************************************/
	void PAEAfficher() {
		if (pcPAEMessage != NULL)
			std::cout << pcPAEMessage << std::endl;
	};
};

