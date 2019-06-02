#include "CParseurException.h"


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
CParseurException::CParseurException(unsigned int uiErreur, const char * message) : CException(uiErreur)
{
	pcPAEMessage = _strdup(message);
}

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
CParseurException::~CParseurException()
{
	delete pcPAEMessage;
}
