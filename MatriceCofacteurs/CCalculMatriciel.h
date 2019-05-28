#pragma once
#ifndef CCalculMatriciel_H
#define CCalculMatriciel_H

#include "CMatrice.h"
#include <cmath>

template <class MType>
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
		CMatrice<MType> CALTranspose(CMatrice<MType> MATParam);

		/**************************************************************************************************
		**** Nom: CALDeterminantMatrice(CMatrice<MType> MATParam)                                      ****
		***************************************************************************************************
		**** Permet de calculer le déterminant d'une matrice carrée passée en paramètre                ****
		***************************************************************************************************
		**** Précondition: Si MType est une classe d'Objet alors elle doit surcharger l'opérateur "*"  ****
		****    La matrice doit être carrée                                                            ****
		**** Entrée: CMatrice<MType> : MATParam => Matrice sujet au calcul du déterminant              ****
		**** Entraîne: Lève une CMatriceException si la matrice passé en paramètre n'est pas carrée    ****
		**** Sortie: double : déterminant de la matrice passé en paramètre                             ****
		**************************************************************************************************/
		double CALCalculerDeterminant(CMatrice<MType> MATParam);
	
		CMatrice<double> CALCalculerComatrice(CMatrice<MType> MATParam);

	private :
		int* CALTrouverMeilleurCibleDeterminant(CMatrice<MType> MATParam, MType valeurRecherchee);

		double CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int iColonneCible);

		CMatrice<MType> CALCalculerSousMatrice(CMatrice<MType> MATParam, unsigned int uiLigne, unsigned int uiColonne);

		int* CALComparerCible(unsigned int* piNbLigne, unsigned int* piNbColonne, unsigned int uiTaille);
};


#include "CCalculMatriciel.cpp"
#endif // CCalculMatriciel_H
