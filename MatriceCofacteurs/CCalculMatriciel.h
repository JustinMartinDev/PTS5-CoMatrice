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
		****   pour retourner un nombre et "==". Et la matrice doit être carrée                         ****
		**** Entrée: CMatrice<MType> : MATParam => Matrice sujet au calcul du déterminant              ****
		****         MType : mValeurRechercheCalculDeterminant => Valeur de recherche permettant       ****
		****                 l'éxécution de la version améliorée de la méthode de Laplace (cf rapport) ****
		**** Entraîne: Lève une CMatriceException si la matrice passée en paramètre n'est pas carrée   ****
		**** Sortie: double : déterminant de la matrice passée en paramètre                            ****
		**************************************************************************************************/
		double CALCalculerDeterminant(CMatrice<MType> MATParam, MType mValeurRechercheCalculDeterminant);
	

		double CALCalculerDeterminant(CMatrice<MType> MATParam);

		/************************************************************************************************
		**** Nom: CMatrice<double> CALCalculerComatrice(CMatrice<MType> MATParam)                    ****
		*************************************************************************************************
		**** Renvoie la Comatrice correspondante à la matrice passée en paramètre                    ****
		*************************************************************************************************
		**** Précondition: Si MType est une classe d'Object alors elle doit surcharger l'opérateur   ****
		****    "*" pour retourner un nombre et "=". La matrice doit être carrée                     ****
		**** Entrée: MATParam : CMatrice<MType>  => Matrice à traiter pour renvoyer sa commatrice    ****
		****         MType : mValeurRechercheCalculDeterminant => Valeur de recherche permettant     ****
		****              l'éxécution de la version améliorée de la méthode de Laplace (cf rapport)  ****
		**** Entraîne: Lève une CMatriceException si la matrice passée en paramètre n'est pas carrée ****
		**** Sortie: CMatrice<double> => Commatrice correspondant à la matrice passé en paramètre    ****
		************************************************************************************************/
		CMatrice<double> CALCalculerComatrice(CMatrice<MType> MATParam, MType mValeurRechercheCalculDeterminant);
	
		/************************************************************************************************
		**** Nom: CMatrice<double> CALCalculerComatrice(CMatrice<MType> MATParam)                    ****
		*************************************************************************************************
		**** Renvoie la Comatrice correspondante à la matrice passée en paramètre                    ****
		*************************************************************************************************
		**** Précondition: Si MType est une classe d'Object alors elle doit surcharger l'opérateur   ****
		****    "*". La matrice doit être carrée                                                     ****
		**** Entrée: MATParam : CMatrice<MType>  => Matrice à traiter pour renvoyer sa commatrice    ****
		**** Entraîne: Lève une CMatriceException si la matrice passée en paramètre n'est pas carrée ****
		**** Sortie: CMatrice<double> => Comatrice correspondante à la matrice passé en paramètre    ****
		************************************************************************************************/
		CMatrice<double> CALCalculerComatrice(CMatrice<MType> MATParam);
	private :

		/*************************************************************************************************
		**** Nom: int* CALTrouverMeilleurCibleDeterminant(CMatrice<MType> MATParam, MType             ****
		****    mValeurRechercheCalculDeterminant)                                                    ****
		**************************************************************************************************
		**** Recherche dans la matrice passé en paramètre la ligne, ou colonne qui contient le plus   ****
		****    d'occurence de la 2nd valeur passé en paramètre                                       ****
		**************************************************************************************************
		**** Précondition: Si MType est une classe d'Objet alors elle doit surcharger l'opérateur "=" ****
		**** Entrée: CMatrice<MType> : MATParam => Matrice à tratier                                  ****
		****    MType : mValeurRechercheCalculDeterminant => Valeur a rechercher                      ****
		**** Entraîne:                                                                                ****
		**** Sortie: int* => tableau contenant l'index de la meilleure ligne ou colonne.              ****
		****    {indexLigne, indexColonne} si c'est une colonne qui a le plus d'occurence alors       ****
		****    indexLigne sera égale à -1 et vice versa                                              ****
		****                                                                                          ****
		*************************************************************************************************/
		int* CALTrouverMeilleurCibleDeterminant(CMatrice<MType> MATParam, MType mValeurRechercheCalculDeterminant);
		
		/**************************************************************************************************
		**** Nom: double CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int         ****
		****    iColonneCible, MType mValeurRechercheCalculDeterminant)                                ****
		***************************************************************************************************
		**** Fonction récursive permettant de calculer le determinant d'une matrice en utilisation la  ****
		****    version optimisé                                                                       ****
		***************************************************************************************************
		**** Précondition: Si MType est une classe d'Objet alors elle doit surcharger l'opérateur "*"  ****
		****    pour retrouner une nombre et "=="                                                      ****
		**** Entrée: CMatrice<MType> : MATParam => Matrice à traiter                                   ****
		****    int : iLigneCible => index de la ligne cible                                           ****
		****    int iColonneCible => index de la colonne cible                                         ****
		****    MType : mValeurRechercheCalculDeterminant => Valeur a rechercher                       ****
		****                                                                                           ****
		**** Entraîne: Peut lever une CMatriceException si aucune ligne ou colonne n'est indiquée      ****
		****    comme cible ou alors que l'index est supérieur à la taille de la matrice               ****
		**** Sortie: double => determinant de la matrice passé en paramètre                            ****
		**************************************************************************************************/
		double CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int iColonneCible, MType mValeurRechercheCalculDeterminant);

		/*************************************************************************************************
		**** Nom: double CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int        ****
		****    iColonneCible);                                                                       ****
		**************************************************************************************************
		**** Fonction récursive permettant de calculer le determinant d'une matrice                   ****
		**************************************************************************************************
		**** Précondition: Si MType est une classe d'Objet alors elle doit surcharger l'opérateur "*" ****
		****    pour retrouner une nombre et "=="                                                     ****
		**** Entrée: CMatrice<MType> : MATParam => Matrice à traiter                                  ****
		****    int : iLigneCible => index de la ligne cible                                          ****
		****    int iColonneCible => index de la colonne cible                                        ****
		**** Entraîne: Peut lever une CMatriceException si aucune ligne ou colonne n'est indiquée     ****
		****    comme cible ou alors que l'index est supérieur à la taille de la matrice              ****
		**** Sortie: double => determinant de la matrice passé en paramètre                           ****
		*************************************************************************************************/
		double CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int iColonneCible);

		/**************************************************************************************************
		**** Nom: CMatrice<MType> CALCalculerSousMatrice(CMatrice<MType> MATParam, unsigned int        ****
		****    uiLigne, unsigned int uiColonne);                                                      ****
		***************************************************************************************************
		**** Permet d'extraire la sous matrice d'une matrice passé en paramètre en excluent les lignes ****
		****    et colonnes passées en paramètres                                                      ****
		***************************************************************************************************
		**** Précondition:                                                                             ****
		**** Entrée: CMatrice<MType> : MATParam => Matrice à traiter                                   ****
		****    int : iLigneCible => index de la ligne a supprimer                                     ****
		****    int iColonneCible => index de la colonne a supprimer                                   ****
		**** Entraîne: Peut lever une CMatriceException si la matrice n'est pas carrée                 ****
		**** Sortie: CMatrice<MType> => Sous matrice de la matrice passé en paramètre                  ****
		**************************************************************************************************/
		CMatrice<MType> CALCalculerSousMatrice(CMatrice<MType> MATParam, unsigned int uiLigne, unsigned int uiColonne);

		/**************************************************************************************************
		**** Nom: int* CALComparerCible(unsigned int* piNbLigne, unsigned int* piNbColonne, unsigned   ****
		****    int uiTaille)                                                                          ****
		***************************************************************************************************
		**** Permet de comparer le nombre de ligne et de colonne afin de choisir quel index de colonne ****
		****    ou cible doit être utiliser pour la version améliorée du calcule de déterminant        ****
		***************************************************************************************************
		**** Précondition:                                                                             ****
		**** Entrée: unsigned int* : piNbLigne => Tableau contenant le nombre d'occurence de valeur    ****
		****    recherchée sur chaque ligne                                                            ****
		****    unsigned int* : piNbColonne => Tableau contenant le nombre d'occurence de valeur       ****
		****    recherchée sur chaque colonne                                                          ****
		****    unsigned int : uiTaille => Taille de la matrice                                        ****
		**** Entraîne:                                                                                 ****
		**** Sortie: int* => Tableau contenant l'index de la ligne ou de la matrice contenant le plus  ****
		****    d'occurence (par défaut la 1ère ligne)                                                 ****
		**************************************************************************************************/
		int* CALComparerCible(unsigned int* piNbLigne, unsigned int* piNbColonne, unsigned int uiTaille);
};


#include "CCalculMatriciel.cpp"
#endif // CCalculMatriciel_H
