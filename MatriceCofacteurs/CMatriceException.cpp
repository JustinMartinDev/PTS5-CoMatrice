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
CMatriceException::CMatriceException(unsigned int uiErreur, const char* cpcMessage) : CException(uiErreur) {
	pcMEMessage = _strdup(cpcMessage);
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
	delete(pcMEMessage);
}

void CMatriceException::MATEAfficher() {
	if (pcMEMessage != NULL)
		std::cerr << pcMEMessage << std::endl;
}