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
CMatriceException::CMatriceException(unsigned int uiErreur, const char* cpcMessage) : CException(uiErreur) {
	pcMEMessage = _strdup(cpcMessage);
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
	delete(pcMEMessage);
}

void CMatriceException::MATEAfficher() {
	if (pcMEMessage != NULL)
		std::cerr << pcMEMessage << std::endl;
}