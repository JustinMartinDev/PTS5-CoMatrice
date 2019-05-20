#pragma once
#ifndef CMatrice_H
#define CMatrice_H

#include <iostream>
#include <stdio.h>
#include "CMatriceException.h"

template <class MType = int>
class CMatrice { //int comme type par defaut
public:
	/**************************************************************************
	**** Nom: CMatrice<MType>();                                           ****
	***************************************************************************
	**** Constructeur par default de CMatrice, créer une matrice carrée 2x2****
	***************************************************************************
	**** Précondition:                                                     ****
	**** Entrée:                                                           ****
	**** Entraîne:                                                         ****
	**** Sortie:                                                           ****
	**************************************************************************/
	CMatrice<MType>(); //par defaut une 2x2

	/*********************************************************************************************
	**** Nom: CMatrice<MType>(unsigned int uiTaille);                                         ****
	**********************************************************************************************
	**** Constructeur de confort de CMatrice, créer une matrice carrée avec la taille passé en****
	****    paramètre                                                                         ****
	**********************************************************************************************
	**** Précondition:                                                                        ****
	**** Entrée: uiTaille : unsigned int => taille de la matrice                              ****
	**** Entraîne:                                                                            ****
	**** Sortie:                                                                              ****
	*********************************************************************************************/
	CMatrice<MType>(const unsigned int uiTaille);

	/*************************************************************************************************
	**** Nom: CMatrice<MType>(unsigned int uiLigne, unsigned int uiColonne)                       ****
	**************************************************************************************************
	**** Constructeur de confort de CMatrice, créer une matrice avec la taille passé en paramètre ****
	**************************************************************************************************
	**** Précondition:                                                                            ****
	**** Entrée: uiLigne : unsigned int => nombre de ligne de la matrice                          ****
	****    uiColonne : unsigned int => nombre de ligne de la matrice                             ****
	**** Entraîne:                                                                                ****
	**** Sortie:                                                                                  ****
	*************************************************************************************************/
	CMatrice<MType>(const unsigned int uiLigne, const unsigned int uiColonne);

	/****************************************************************************************
	**** Nom: CMatrice<MType>(const CMatrice<MType> &pMATParam)                          ****
	*****************************************************************************************
	**** Constructeur de recopie de CMatrice                                             ****
	*****************************************************************************************
	**** Précondition:                                                                   ****
	**** Entrée: pMATParam : const CMatrice<MType> & => référence de la matrice à copier ****
	**** Entraîne:                                                                       ****
	**** Sortie:                                                                         ****
	****************************************************************************************/
	CMatrice<MType>(const CMatrice<MType> &pMATParam);


	/**************************************************************************************************
	**** Nom: ~CMatrice()                                                                          ****
	***************************************************************************************************
	**** Destructeur de la classe CMatrice, permet de desallouer toutes les valeurs de la matrices ****
	***************************************************************************************************
	**** Précondition:                                                                             ****
	**** Entrée:                                                                                   ****
	**** Entraîne:                                                                                 ****
	**** Sortie:                                                                                   ****
	**************************************************************************************************/
	~CMatrice();
	/********************************************************************************************
	**** Nom: void MATAfficherMatrice()                                                      ****
	*********************************************************************************************
	**** Permet d'afficher la matrice dans la console                                        ****
	*********************************************************************************************
	**** Précondition: Si vous utiliser une matrice d'objet, vous devez vous assurez d'avoir ****
	****    surchargé l'opérateur "<<" de cette classe                                       ****
	**** Entrée:                                                                             ****
	**** Entraîne:                                                                           ****
	**** Sortie:                                                                             ****
	********************************************************************************************/
	void MATAfficherMatrice();

	/**************************************************************************************************
	**** Nom: void MATModifierElement(unsigned int uiLigne, unsigned int uiColonne, MType          ****
	****    MTValeur);                                                                             ****
	***************************************************************************************************
	**** Permet de modifier un élément du tableau                                                  ****
	***************************************************************************************************
	**** Précondition:                                                                             ****
	**** Entrée:                                                                                   ****
	****	uiLigne : unsigned int => ligne de l'élément à modifier                                ****
	****    uiColonne : unsigned int => colonne de l'élément à modifier                            ****
	****    MTValeur : MType => valeur à sauvegarder                                               ****
	**** Entraîne: Peut lever une MatriceException                                                 ****
	****    si uiLigne ou uiColonne sont supérieurs au nombre de ligne de la matrice  ou au nombre ****
	****    de la colonne de la matrice                                                            ****
	**** Sortie:                                                                                   ****
	**************************************************************************************************/
	void MATModifierElement(unsigned int uiLigne, unsigned int uiColonne, MType MTValeur);

	/*************************************************************************************************
	**** Nom: MType& MATLireElement(unsigned int uiLigne, unsigned int uiColonne)                 ****
	**************************************************************************************************
	**** Renvoie une référence de l'element stocker dans la matrice                               ****
	**************************************************************************************************
	**** Précondition:                                                                            ****
	**** Entrée: uiLigne : unsigned int => ligne de l'élément à récupérer                         ****
	****    uiColonne : unsigned int => colonne de l'élément à récupérer                          ****
	**** Entraîne: Peut lever une MatriceException                                                ****
	****    si uiLigne ou uiColonne sont supérieurs au nombre de ligne de la matrice ou au nombre ****
	****    de la colonne de la matrice                                                           ****
	**** Sortie: MType& => Réference vers l'élement                                               ****
	**************************************************************************************************/
	MType& MATLireElement(unsigned int uiLigne, unsigned int uiColonne);

	/**************************************************************************************************
	**** Nom: MType& operator()(unsigned int uiLigne, unsigned int uiColonne)                      ****
	***************************************************************************************************
	**** Surcharge de l'operateur () permettant de renvoyer une référence d'un élément stocké dans ****
	****    la matrice                                                                             ****
	***************************************************************************************************
	**** Précondition:                                                                             ****
	**** Entrée: uiLigne : unsigned int => ligne de l'élément à récupérer                          ****
	****    uiColonne : unsigned int => ligne de l'élément à récupéer                              ****
	**** Entraîne: Peut lever une MatriceException                                                 ****
	****    si uiLigne ou uiColonne sont supérieurs au nombre de ligne de la matrice ou au nombre  ****
	****    de la colonne de la matrice                                                            ****
	**** Sortie: MType& => Réference vers l'élement                                                ****
	**************************************************************************************************/
	MType& operator()(unsigned int uiLigne, unsigned int uiColonne) { return MATLireElement(uiLigne, uiColonne); };

	/******************************************************************************************
	**** Nom: CMatrice<MType> operator+(CMatrice<> MATParam)                               ****
	*******************************************************************************************
	**** Permet de calculer pour deux matrices A+B et de renvoyer la matrice resultante    ****
	*******************************************************************************************
	**** Précondition: Si MType est un objet avec vous devez surcharger son opérateur "+"  ****
	**** pour retourner un nombre                                                          ****
	**** Entrée:   MATParam: CMatrice<> => matrice à additionner (B)                       ****
	**** Entraîne:                                                                         ****
	**** Sortie: CMatrice<MType> => renvoie une matrice de MType résultat de l'opération   ****
	******************************************************************************************/
	CMatrice<MType> operator+(CMatrice<MType> MATParam);

	/******************************************************************************************
	**** Nom: CMatrice<MType> operator-(CMatrice<MType> MATParam)                          ****
	*******************************************************************************************
	**** Permet de calculer pour deux matrices A-B et de renvoyer la matrice resultante    ****
	*******************************************************************************************
	**** Précondition: Si MType est un objet alors vous devez surcharger son opérateur "-" ****
	**** pour retourner un MType                                                           ****
	**** Entrée:  MATParam: CMatrice<MType> => matrice à soustraire (B)                    ****
	**** Entraîne:                                                                         ****
	**** Sortie: CMatrice<MType> => renvoie une matrice de MType résultat de l'opération   ****
	******************************************************************************************/
	CMatrice<MType> operator-(CMatrice<MType> MATParam);

	/******************************************************************************************
	**** Nom: CMatrice<MType> operator*(CMatrice<MType> MATParam)                          ****
	*******************************************************************************************
	**** Permet de calculer pour deux matrices A*B et de renvoyer la matrice resultante    ****
	*******************************************************************************************
	**** Précondition: Si MType est un objet alors vous devez surcharger son opérateur "*" ****
	**** pour retourner un MType                                                           ****
	**** Entrée:  MATParam: CMatrice<MType> => matrice à soustraire (B)                    ****
	**** Entraîne:                                                                         ****
	**** Sortie: CMatrice<MType> => renvoie une matrice de MType résultat de l'opération   ****
	******************************************************************************************/
	CMatrice<MType> operator*(CMatrice<MType> MATParam); //warning new

	/*******************************************************************************************
	**** Nom: CMatrice<double> operator/(double dDiviseur)                                  ****
	********************************************************************************************
	**** Permet de calculer pour une matrice et une constante M/c et de renvoyer la matrice ****
	****    résultante                                                                      ****
	********************************************************************************************
	**** Précondition: Si MType est un objet, vous devez surcharger son opérateur "/" pour  ****
	****    retourner un double                                                             ****
	**** Entrée: dDiviseur : double => diviseur de la matrice (c)                           ****
	**** Entraîne: Peut lever une CMatriceException dDiviseur = 0                           ****
	**** Sortie: CMatrice<Double> => renvoie une matrice de double résultat de l'opération  ****
	*******************************************************************************************/
	CMatrice<double> operator/(double dDiviseur); //warning new

	/**************************************************************************************************
	**** Nom: unsigned int MATLireNbLigne()                                                        ****
	***************************************************************************************************
	**** Accésseur en lecture de l'attribut uiMATnbLigne, renvoie le nombre de ligne de la matrice ****
	***************************************************************************************************
	**** Précondition: Si MType est un objet avec vous devez surcharger son opérateur+             ****
	**** pour retourner un nombre                                                                  ****
	**** Entrée:                                                                                   ****
	**** Entraîne:                                                                                 ****
	**** Sortie: unsigned int => renvoie le nombre de ligne de la matrice                          ****
	**************************************************************************************************/
	unsigned int MATLireNbLigne() { return uiMATNbLigne; }

	/**********************************************************************************************
	**** Nom: unsigned int MATLireNbColonne()                                                  ****
	***********************************************************************************************
	**** Accésseur en lecture de l'attribut uiMATnbColonne, renvoie le nombre de colonne de la ****
	****    matrice                                                                            ****
	***********************************************************************************************
	**** Précondition:                                                                         ****
	**** Entrée:                                                                               ****
	**** Entraîne:                                                                             ****
	**** Sortie: unsigned int => renvoie le nombre de colonne de la matrice                    ****
	**********************************************************************************************/
	unsigned int MATLireNbColonne() { return uiMATNbColonne; }


	/*****************************************************************************************
	**** Nom: void MATAllouer(unsigned int uiNbLigne, unsigned int uiNbColonne)           ****
	******************************************************************************************
	**** Permet d'allouer en mémoire le tableau de pointeur pMATvaleurs pour recevoir les ****
	****    différents éléments                                                           ****
	******************************************************************************************
	**** Précondition:                                                                    ****
	**** Entrée: unsigned int uiNbLigne => nombre de ligne à allouer                      ****
	****    unsigned int uiNbColonne => nombre de colonne à allouer                       ****
	**** Entraîne:                                                                        ****
	**** Sortie:                                                                          ****
	*****************************************************************************************/
	void MATAllouer(unsigned int uiNbLigne, unsigned int uiNbColonne);
private:
	unsigned int uiMATNbLigne;
	unsigned int uiMATNbColonne;

	MType **pMATvaleurs; //tableau 2D;
};

#include "CMatrice.cpp"

#endif