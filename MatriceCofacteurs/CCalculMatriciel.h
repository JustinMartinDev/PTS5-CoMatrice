#pragma once
#ifndef CCalculMatriciel_H
#define CCalculMatriciel_H

#include "CMatrice.h"

class CCalculMatriciel {
	public :
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
		static CMatrice<MType> CALTranspose(CMatrice<MType> MATParam);

		//Destructeur virtuel pure permettant de rendre la classe abstraite et non instanciable
		virtual ~CCalculMatriciel() = 0;
};

#endif // CCalculMatriciel_H
