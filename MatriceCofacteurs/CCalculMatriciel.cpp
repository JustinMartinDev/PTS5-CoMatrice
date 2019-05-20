#include "CCalculMatriciel.h"

/************************************************
**** Nom: CALTranspose                       ****
*************************************************
**** Calcul et retourne la transpos� le la   ****
****    matrice pass� en param�tre           ****
*************************************************
**** Pr�condition:                           ****
**** Entr�e: pMATParam : CMatrice, matrice � ****
****    transposer                           ****
**** Entra�ne:                               ****
**** Sortie: CMatrice, matrice contenant la  ****
****    transpos�                            ****
************************************************/
template <class MType>
CMatrice<MType> CCalculMatriciel::CALTranspose(CMatrice<MType> MATParam) {
	CMatrice<MType> MATTranspose(MATParam.MATLireNbColonne(), MATParam.MATLireNbLigne());

	for (unsigned int uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) { //Pour chaque ligne 
		for (unsigned int uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) { //et chaque colonne 
			MATTranspose.MATModifierElement(uiColonne, uiLigne, MATParam.MATLireElement(uiLigne, uiColonne)); //on inverser les �l�ments
		}
	}
	return MATTranspose;
}