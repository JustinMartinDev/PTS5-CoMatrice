#include "CMatriceException.h"

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
CMatriceException::CMatriceException(unsigned int uiErreur, const char* message) : CException(uiErreur) {
	std::cout << message << std::endl;
	message = message;
}
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
CMatriceException::~CMatriceException() {
	delete(message);
}