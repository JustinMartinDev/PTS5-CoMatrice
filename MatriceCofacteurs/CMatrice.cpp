//#ifndef ERROR_MAX_SIZE 
#define ERROR_MAX_SIZE 256
//#endif

/**************************************************************************
**** Nom: CMatrice<MType>();                                           ****
***************************************************************************
**** Constructeur par default de CMatrice, créer une matrice carré 2x2 ****
***************************************************************************
**** Précondition:                                                     ****
**** Entrée:                                                           ****
**** Entraîne:                                                         ****
**** Sortie:                                                           ****
**************************************************************************/
template <class MType>
CMatrice<MType>::CMatrice() {	
	uiMATNbLigne = 2;
	uiMATNbColonne = 2;

	MATAllouer(2, 2);
};

/*********************************************************************************************
**** Nom: CMatrice<MType>(unsigned int uiTaille);                                         ****
**********************************************************************************************
**** Constructeur de confort de CMatrice, créer une matrice carré avec la taille passé en ****
****    paramètre                                                                         ****
**********************************************************************************************
**** Précondition:                                                                        ****
**** Entrée: uiTaille : unsigned int => taille de la matrice                              ****
**** Entraîne:                                                                            ****
**** Sortie:                                                                              ****
*********************************************************************************************/
template <class MType>
CMatrice<MType>::CMatrice(const unsigned int uiTaille) {
	uiMATNbColonne = uiTaille;
	uiMATNbLigne = uiTaille;

	MATAllouer(uiMATNbLigne, uiMATNbColonne);
}

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
template <class MType>
CMatrice<MType>::CMatrice(const unsigned int uiLigne, const unsigned int uiColonne) {
	uiMATNbLigne = uiLigne;
	uiMATNbColonne = uiColonne;

	MATAllouer(uiMATNbLigne, uiMATNbColonne);
};

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
template <class MType>
CMatrice<MType>::CMatrice(const CMatrice<MType> &pMATParam) {
	uiMATNbColonne = pMATParam.uiMATNbColonne;
	uiMATNbLigne = pMATParam.uiMATNbLigne;

	MATAllouer(uiMATNbLigne, uiMATNbColonne);
	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLigne; uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < uiMATNbColonne; uiColonne++) { //on recopie chaque élément de la matrice via sa référence
			pMATvaleurs[uiLigne][uiColonne] = pMATParam.pMATvaleurs[uiLigne][uiColonne];
		}
	}
};

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
template <class MType>
CMatrice<MType>::~CMatrice() {
	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLigne; uiLigne++) { //on désaloue toutes les lignes de notre matrice
		delete pMATvaleurs[uiLigne];
	}
}

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
template <class MType>
void CMatrice<MType>::MATAfficherMatrice() {
	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLigne; uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < uiMATNbColonne; uiColonne++) {
			std::cout << MATLireElement(uiLigne, uiColonne) << " "; //Pour chaque élément d'une ligne on l'affiche suivit d'un espace et en fin de ligne on fait un retour à la ligne
		}
		std::cout << std::endl;
	}
}

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
#define MATRICE_ERROR_SIZE_ACCESS 1
template <class MType>
void CMatrice<MType>::MATModifierElement(unsigned int uiLigne, unsigned int uiColonne, MType MTValeur) {
	if (uiLigne > MATLireNbLigne()) { //On leve une exception si on tente de modifier un élément à une ligne qui n'existe pas
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est différent du nombre de ligne de la seconde (%d)", MATRICE_ERROR_SIZE_ACCESS, uiLigne, MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_SIZE_ACCESS, message);
	}
	else if (uiColonne > MATLireNbColonne()) { //On leve une exception si on tente de modifier un élément à une colonnne qui n'existe pas
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est différent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_SIZE_ACCESS, uiColonne, MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_SIZE_ACCESS, message);
	}
	pMATvaleurs[uiLigne][uiColonne] = MTValeur;
}

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
template <class MType>
void CMatrice<MType>::MATAllouer(unsigned int uiNbLigne, unsigned int uiNbColonne) {
	pMATvaleurs = new MType*[uiNbLigne];

	for (unsigned int uiLigne = 0; uiLigne < uiNbLigne; uiLigne++) { //Allocation de chaque élément
		pMATvaleurs[uiLigne] = new MType[uiNbColonne];
	}
}

/*************************************************************************************************
**** Nom: MType& MATLireElement(unsigned int uiLigne, unsigned int uiColonne)                 ****
**************************************************************************************************
**** Renvoie une référence de l'element stocker dans la matrice                               ****
**************************************************************************************************
**** Précondition:                                                                            ****
**** Entrée: uiLigne : unsigned int => ligne de l'élément à récupérer                         ****
****    uiColonne : unsigned int => colonne de l'élément à récupérer                          ****
**** Entraîne: Peut lever une CMatriceException                                               ****
****    si uiLigne ou uiColonne sont supérieurs au nombre de ligne de la matrice ou au nombre ****
****    de la colonne de la matrice                                                           ****
**** Sortie: MType& => Réference vers l'élement                                               ****
**************************************************************************************************/
template <class MType>
MType& CMatrice<MType>::MATLireElement(unsigned int uiLigne, unsigned int uiColonne) {
	if (uiLigne > MATLireNbLigne()) { //On leve une exception si on tente d'accéder à une ligne qui n'existe pas
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est différent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_SIZE_ACCESS, uiLigne, MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_SIZE_ACCESS, message);
	}
	else if (uiColonne > MATLireNbColonne()) { //On leve une exception si on tente d'accéder à une colonnne qui n'existe pas
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est différent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_SIZE_ACCESS, uiColonne, MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_SIZE_ACCESS, message);
	}

	return pMATvaleurs[uiLigne][uiColonne];
}

/******************************************************************************************
**** Nom: CMatrice<double> operator+(CMatrice<> pMATParam)                             ****
*******************************************************************************************
**** Permet de calculer pour deux matrices A+B et de renvoyer la matrice resultante    ****
*******************************************************************************************
**** Précondition: Si MType est un objet avec vous devez surcharger son opérateur "+"  ****
**** pour retourner un nombre                                                          ****
**** Entrée:  pMATParam: CMatrice<> => matrice à additionner (B)                       ****
**** Entraîne:                                                                         ****
**** Sortie: CMatrice<double> => renvoie une matrice de double résultat de l'opération ****
******************************************************************************************/
#define MATRICE_ERROR_OPERATION_SIZE 3
template <class MType>
CMatrice<MType> CMatrice<MType>::operator+(CMatrice<MType> MATParam) {
	if (MATLireNbLigne() != MATParam.MATLireNbLigne()) { //On leve une exception si on tente d'additionner des matrices de taille différentes
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de ligne de la 1ere matrice (%d) est différent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATLireNbLigne(), MATParam.MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	else if (MATLireNbColonne() != MATParam.MATLireNbColonne()) {
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est différent du nombre de colonne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATLireNbColonne(), MATParam.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	CMatrice<MType> dMmatrice(uiMATNbLigne, uiMATNbColonne);

	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLigne; uiLigne++) { //chaque élément de la matrice A est additionné à l'élément correspondant dans la matrice B
		for (unsigned int uiColonne = 0; uiColonne < uiMATNbColonne; uiColonne++) {
			MType newValue = MATLireElement(uiLigne, uiColonne) + MATParam.MATLireElement(uiLigne, uiColonne); 
			dMmatrice.MATModifierElement(uiLigne, uiColonne, newValue); //Le résultat est stocké dans la nouvelle matrice
		}
	}
	return dMmatrice;
}

/******************************************************************************************
**** Nom: CMatrice<double> operator-(CMatrice<> pMATParam)                             ****
*******************************************************************************************
**** Permet de calculer pour deux matrices A-B et de renvoyer la matrice resultante    ****
*******************************************************************************************
**** Précondition: Si MType est un objet avec vous devez surcharger son opérateur "-"  ****
**** pour retourner un nombre                                                          ****
**** Entrée:  pMATParam: CMatrice<> => matrice à soustraire (B)                        ****
**** Entraîne:                                                                         ****
**** Sortie: CMatrice<double> => renvoie une matrice de double résultat de l'opération ****
******************************************************************************************/
template <class MType>
CMatrice<MType> CMatrice<MType>::operator-(CMatrice<MType> MATParam) { 
	if (MATLireNbLigne() != MATParam.MATLireNbLigne()) {  //On leve une exception si on tente de soustraire des matrices de taille différentes
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de ligne de la 1ere matrice (%d) est différent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATLireNbLigne(), MATParam.MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	else if (MATLireNbColonne() != MATParam.MATLireNbColonne()) {
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est différent du nombre de colonne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATLireNbColonne(), MATParam.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	CMatrice<MType> dMmatrice(uiMATNbLigne, uiMATNbColonne);

	for (unsigned int uiLigne = 0; uiLigne < uiMATNbLigne; uiLigne++) { //chaque élément de la matrice A est soustrait à l'élément correspondant dans la matrice B
		for (unsigned int uiColonne = 0; uiColonne < uiMATNbColonne; uiColonne++) {
			MType newValue = MATLireElement(uiLigne, uiColonne) - MATParam.MATLireElement(uiLigne, uiColonne);
			dMmatrice.MATModifierElement(uiLigne, uiColonne, newValue); //Le résultat est stocké dans la nouvelle matrice
		}
	}
	return dMmatrice;
}

/******************************************************************************************
**** Nom: CMatrice<double> operator*(CMatrice<> pMATParam)                             ****
*******************************************************************************************
**** Permet de calculer pour deux matrices A*B et de renvoyer la matrice resultante    ****
*******************************************************************************************
**** Précondition: Si MType est un objet avec vous devez surcharger son opérateur "*"  ****
**** pour retourner un object MType                                                    ****
**** Entrée:  pMATParam: CMatrice<> => matrice à multiplier (B)                        ****
**** Entraîne: Peut lever une CMatriceException                                        ****
****    si le nombre de colonne de A est différent du nombre de ligne de B (code 2)    ****
**** Sortie: CMatrice<double> => renvoie une matrice de double résultat de l'opération ****
******************************************************************************************/
#define MATRICE_ERROR_MULTIPLICATION_SIZE 2
template <class MType>
CMatrice<MType> CMatrice<MType>::operator*(CMatrice<MType> MATParam) {
	if (MATLireNbColonne() != MATParam.MATLireNbLigne()) { //On leve une exception si on tente de multiplier des matrices dont le nombre de ligne de A n'est pas égale au nombre de colonne de B
		/* Formation du message d'exception */
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est différent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_MULTIPLICATION_SIZE, MATLireNbColonne(), MATParam.MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_MULTIPLICATION_SIZE, message);
	}
	CMatrice<MType> MATResultat(MATLireNbLigne(), MATParam.MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			MType MTSomme = 0;
			for (unsigned int uiCalcIncrement = 0; uiCalcIncrement < MATLireNbColonne(); uiCalcIncrement++) {
				MTSomme += MATLireElement(uiLigne, uiCalcIncrement) * MATParam.MATLireElement(uiCalcIncrement, uiColonne);
			}
			MATResultat.MATModifierElement(uiLigne, uiColonne, MTSomme);
		}
	}
	return MATResultat;
}


/*******************************************************************************************
**** Nom: CMatrice<double> operator/(double dDiviseur)                                  ****
********************************************************************************************
**** Permet de calculer pour une matrice et une constante M/c et de renvoyer la matrice ****
****    résultante                                                                      ****
********************************************************************************************
**** Précondition: Si MType est un objet, vous devez surcharger son opérateur "/" pour  ****
****    retourner un double                                                             ****
**** Entrée: dDiviseur : double => diviseur de la matrice (c)                           ****
**** Entraîne: Peut lever une CMatriceException si dDiviseur est égale à 0 (code 4)     ****
**** Sortie: CMatrice<Double> => renvoie une matrice de double résultat de l'opération  ****
*******************************************************************************************/
#define MATRICE_ERROR_DIVISEUR_0 4
template <class MType>
CMatrice<double> CMatrice<MType>::operator/(double dDiviseur) {
	if (dDiviseur == 0) {
		throw CMatriceException(MATRICE_ERROR_DIVISEUR_0);
	}

	CMatrice<double> dMATResult(MATLireNbLigne(), MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATLireNbColonne(); uiColonne++) {
			double dCalcValeur = MATLireElement(uiLigne, uiColonne)/dDiviseur;
			dMATResult.MATModifierElement(uiLigne, uiColonne, dCalcValeur);
		}
	}
	return dMATResult;
}

/*** FUNCTION EN DEHORS DE LA CLASSE ***/
/************************************************************************************************
**** Nom: CMatrice<double> operator*(const double dMultiplicateur, CMatrice<MType> MATParam) ****
*************************************************************************************************
**** Permet de mulplier une constante numérique par une matrice et de renvoyer la matrice    ****
****    resultante                                                                           ****
*************************************************************************************************
**** Précondition: Si MType est un objet avec vous devez surcharger son opérateur "*" pour   ****
****    retourner un nombre                                                                  ****
**** Entrée: dMultiplicateur : const double => constante multiplciateur                      ****
****    MATParam : CMatrice => matrice à multiplier                                          ****
**** Entraîne:                                                                               ****
**** Sortie: CMatrice<double> => matrice resultat dMultiplicateur*MATParam                   ****
************************************************************************************************/
template<class MType>
CMatrice<double> operator*(const double dMultiplicateur, CMatrice<MType> MATParam) {
	CMatrice<double> dMATResult(MATParam.MATLireNbLigne(), MATParam.MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			double dCalcValeur = MATParam.MATLireElement(uiLigne, uiColonne) * dMultiplicateur;
			dMATResult.MATModifierElement(uiLigne, uiColonne, dCalcValeur);
		}
	}
	return dMATResult;
}


/************************************************************************************************
**** Nom: CMatrice<double> operator*(const double dMultiplicateur, CMatrice<MType> MATParam) ****
*************************************************************************************************
**** Permet de mulplier une matrice par une constante numérique et de renvoyer la matrice    ****
****    resultante                                                                           ****
*************************************************************************************************
**** Précondition: Si MType est un objet avec vous devez surcharger son opérateur "*" pour   ****
****    retourner un nombre                                                                  ****
**** Entrée: MATParam : CMatrice => matrice à multiplier                                     ****
****    dMultiplicateur : const double => constante multiplciateur                           ****
**** Entraîne:                                                                               ****
**** Sortie: CMatrice<double> => matrice resultat MATParam*dMultiplicateur                   ****
************************************************************************************************/
template<class MType>
CMatrice<double> operator*(CMatrice<MType> MATParam, const double dMultiplicateur) {
	CMatrice<double> dMATResult(MATParam.MATLireNbLigne(), MATParam.MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			double dCalcValeur = MATParam.MATLireElement(uiLigne, uiColonne) * dMultiplicateur;
			dMATResult.MATModifierElement(uiLigne, uiColonne, dCalcValeur);
		}
	}
	return dMATResult;
}

/******************************************************************************************
**** Nom: CMatrice<double> operator*(CMatrice<MType> MATParamGauche, CMatrice<MType2>  ****
****    MATParamDroite) CMatrice<MType> MATParam)                                      ****
*******************************************************************************************
**** Permet de mulplier 2 matrices et de renvoyer la matrice resultante                ****
*******************************************************************************************
**** Précondition: Si MType et MType2 sont des objets alors vous devez surcharger leur ****
****    opérateur "*" pour retourner un nombre                                         ****
**** Entrée: MATParamGauche : CMatrice => matrice à multiplier à gauche                ****
****    MATParamDroite : CMatrice => matrice à multiplier à droite                     ****
**** Entraîne: Peut lever une CMatriceException                                        ****
****    si le nombre de colonne de A est différent du nombre de ligne de B (code 2)    ****
**** Sortie: CMatrice<double> => matrice resultat MATParamGauche*MATParamDroite        ****
******************************************************************************************/
template <class MType, class MType2>
CMatrice<double> operator*(CMatrice<MType> MATParamGauche, CMatrice<MType2> MATParamDroite) {
	if (MATParamGauche.MATLireNbColonne() != MATParamDroite.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est différent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_MULTIPLICATION_SIZE, MATParamGauche.MATLireNbColonne(), MATParamDroite.MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_MULTIPLICATION_SIZE, message);
	}
	CMatrice<double> dMATResult(MATParamGauche.MATLireNbLigne(), MATParamDroite.MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATParamGauche.MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATParamDroite.MATLireNbColonne(); uiColonne++) {
			double dSomme = 0;
			for (unsigned int uiCalcIncrement = 0; uiCalcIncrement < MATParamGauche.MATLireNbColonne(); uiCalcIncrement++) {
				dSomme += MATParamGauche.MATLireElement(uiLigne, uiCalcIncrement) * MATParamDroite.MATLireElement(uiCalcIncrement, uiColonne);
			}
			dMATResult.MATModifierElement(uiLigne, uiColonne, dSomme);
		}
	}
	return dMATResult;
}

/******************************************************************************************
**** Nom: CMatrice<double> operator+(CMatrice<MType> MATParamGauche, CMatrice<MType2>  ****
****    MATParamDroite)                                                                ****
*******************************************************************************************
**** Permet d'aditionner  2 matrices et de renvoyer la matrice resultante              ****
*******************************************************************************************
**** Précondition: Si MType et MType2 sont des objets alors vous devez surcharger leur ****
****    opérateur "+" pour retourner un nombre                                         ****
**** Entrée: MATParamGauche : CMatrice => matrice à additionner (gauche du +)          ****
****    MATParamDroite : CMatrice => matrice à additionner (droite du +)               ****
**** Entraîne: Peut lever une CMatriceException                                        ****
****    si le nombre de colonne de A est différent du nombre de colonne de B ou        ****
****    si le nombre de ligne de A est différent du nombre de ligne de B (code 3)      ****
**** Sortie: CMatrice<double> => matrice resultat MATParamGauche+MATParamDroite        ****
******************************************************************************************/
template <class MType, class MType2>
CMatrice<double> operator+(CMatrice<MType> MATParamGauche, CMatrice<MType2> MATParamDroite) {
	if (MATParamGauche.MATLireNbLigne() != MATParamDroite.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de ligne de la 1ere matrice (%d) est différent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATParamGauche.MATLireNbLigne(), MATParamDroite.MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	else if (MATParamGauche.MATLireNbColonne() != MATParamDroite.MATLireNbColonne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est différent du nombre de colonne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATParamGauche.MATLireNbColonne(), MATParamDroite.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	CMatrice<double> dMATResult(MATParamGauche.MATLireNbLigne(), MATParamGauche.MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATParamGauche.MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATParamDroite.MATLireNbColonne(); uiColonne++) {
			double newValue = MATParamGauche.MATLireElement(uiLigne, uiColonne) + MATParamDroite.MATLireElement(uiLigne, uiColonne);
			dMATResult.MATModifierElement(uiLigne, uiColonne, newValue);
		}
	}
	return dMATResult;
}
/******************************************************************************************
**** Nom: CMatrice<double> operator-(CMatrice<MType> MATParamGauche, CMatrice<MType2>  ****
****    MATParamDroite)                                                                ****
*******************************************************************************************
**** Permet de soustraire 2 matrices et de renvoyer la matrice resultante              ****
*******************************************************************************************
**** Précondition: Si MType et MType2 sont des objets alors vous devez surcharger leur ****
****    opérateur "-" pour retourner un nombre                                         ****
**** Entrée: MATParamGauche : CMatrice => matrice à soustraire (gauche du -)           ****
****    MATParamDroite : CMatrice => matrice à soustraire (droite du -)                ****
**** Entraîne: Peut lever une CMatriceException                                        ****
****    si le nombre de colonne de A est différent du nombre de colonne de B ou        ****
****    si le nombre de ligne de A est différent du nombre de ligne de B (code 3)      ****
**** Sortie: CMatrice<double> => matrice resultat MATParamGauche-MATParamDroite        ****
******************************************************************************************/
template <class MType, class MType2>
CMatrice<double> operator-(CMatrice<MType> MATParamGauche, CMatrice<MType2> MATParamDroite) {
	if (MATParamGauche.MATLireNbLigne() != MATParamDroite.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de ligne de la 1ere matrice (%d) est différent du nombre de ligne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATParamGauche.MATLireNbLigne(), MATParamDroite.MATLireNbLigne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	else if (MATParamGauche.MATLireNbColonne() != MATParamDroite.MATLireNbColonne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur le nombre de colonne de la 1ere matrice (%d) est différent du nombre de colonne de la seconde (%d)\0", MATRICE_ERROR_OPERATION_SIZE, MATParamGauche.MATLireNbColonne(), MATParamDroite.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_OPERATION_SIZE, message);
	}
	CMatrice<double> dMATResult(MATParamGauche.MATLireNbLigne(), MATParamGauche.MATLireNbColonne());

	for (unsigned int uiLigne = 0; uiLigne < MATParamGauche.MATLireNbLigne(); uiLigne++) {
		for (unsigned int uiColonne = 0; uiColonne < MATParamDroite.MATLireNbColonne(); uiColonne++) {
			double newValue = MATParamGauche.MATLireElement(uiLigne, uiColonne) - MATParamDroite.MATLireElement(uiLigne, uiColonne);
			dMATResult.MATModifierElement(uiLigne, uiColonne, newValue);
		}
	}
	return dMATResult;
}