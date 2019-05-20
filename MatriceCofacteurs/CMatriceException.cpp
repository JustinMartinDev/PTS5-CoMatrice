#include "CMatriceException.h"

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
CMatriceException::CMatriceException(unsigned int uiErreur, const char* message) : CException(uiErreur) {
	std::cout << message << std::endl;
	message = message;
}
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
CMatriceException::~CMatriceException() {
	delete(message);
}