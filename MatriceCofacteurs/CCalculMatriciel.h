#pragma once
#ifndef CCalculMatriciel_H
#define CCalculMatriciel_H

#include "CMatrice.h"

class CCalculMatriciel {
	public :
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
		static CMatrice<MType> CALTranspose(CMatrice<MType> MATParam);

		//Destructeur virtuel pure permettant de rendre la classe abstraite et non instanciable
		virtual ~CCalculMatriciel() = 0;
};

#endif // CCalculMatriciel_H
