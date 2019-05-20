#include "CCalculMatriciel.h"

/************************************************
**** Nom: CALTranspose                       ****
*************************************************
**** Calcul et retourne la transposé le la   ****
****    matrice passé en paramètre           ****
*************************************************
**** Précondition:                           ****
**** Entrée: pMATParam : CMatrice, matrice à ****
****    transposer                           ****
**** Entraîne:                               ****
**** Sortie: CMatrice, matrice contenant la  ****
****    transposé                            ****
************************************************/
template <class MType>
CMatrice<MType> CCalculMatriciel::CALTranspose(CMatrice<MType> MATParam) {
	CMatrice<MType> MATTranspose(MATParam.MATLireNbColonne(), MATParam.MATLireNbLigne());

	for (unsigned int uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) { //Pour chaque ligne 
		for (unsigned int uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) { //et chaque colonne 
			MATTranspose.MATModifierElement(uiColonne, uiLigne, MATParam.MATLireElement(uiLigne, uiColonne)); //on inverser les éléments
		}
	}
	return MATTranspose;
}