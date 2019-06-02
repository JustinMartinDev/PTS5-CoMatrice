#include "CParseurException.h"


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
CParseurException::CParseurException(unsigned int uiErreur, const char * message) : CException(uiErreur)
{
	pcPAEMessage = _strdup(message);
}

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
CParseurException::~CParseurException()
{
	delete pcPAEMessage;
}
