#ifndef ERROR_MAX_SIZE 
#define ERROR_MAX_SIZE 256
#endif

//PUBLIC

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
CMatrice<MType> CCalculMatriciel<MType>::CALTranspose(CMatrice<MType> MATParam) {
	CMatrice<MType> MATTranspose(MATParam.MATLireNbColonne(), MATParam.MATLireNbLigne());

	for (unsigned int uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) { //Pour chaque ligne 
		for (unsigned int uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) { //et chaque colonne 
			MATTranspose.MATModifierElement(uiColonne, uiLigne, MATParam.MATLireElement(uiLigne, uiColonne)); //on inverser les éléments
		}
	}
	return MATTranspose;
}

	
#define MATRICE_ERROR_NON_CARREE 10
template <class MType>
double CCalculMatriciel<MType>::CALCalculerDeterminant(CMatrice<MType> MATParam, MType mValeurRechercheCalculDeterminant) {
	if (MATParam.MATLireNbColonne() != MATParam.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur la matrice n'est pas carrée => nombre de ligne : %d, nombre de colonne : %d\0", MATRICE_ERROR_NON_CARREE, MATParam.MATLireNbLigne(), MATParam.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_NON_CARREE, message);
	}

	int* puiLigneEtColonneCible = CALTrouverMeilleurCibleDeterminant(MATParam, mValeurRechercheCalculDeterminant); //On va chercher la meilleur cible (amélioration de Laplace)
	return CALCalculerDeterminant(MATParam, puiLigneEtColonneCible[0], puiLigneEtColonneCible[1]);
}

/**************************************************************************************************
**** Nom: CALDeterminantMatrice(CMatrice<MType> MATParam)                                      ****
***************************************************************************************************
**** Permet de calculer le déterminant d'une matrice carrée passée en paramètre                ****
***************************************************************************************************
**** Précondition: Si MType est une classe d'Objet alors elle doit surcharger l'opérateur "*"  ****
****    La matrice doit être carrée                                                            ****
**** Entrée: CMatrice<MType> : MATParam => Matrice sujet au calcul du déterminant              ****
**** Entraîne: Lève une CMatriceException si la matrice passé en paramètre n'est pas carrée    ****
**** Sortie: double : déterminant de la matrice passé en paramètre                             ****/
template <class MType>
double CCalculMatriciel<MType>::CALCalculerDeterminant(CMatrice<MType> MATParam) {
	if (MATParam.MATLireNbColonne() != MATParam.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur la matrice n'est pas carrée => nombre de ligne : %d, nombre de colonne : %d\0", MATRICE_ERROR_NON_CARREE, MATParam.MATLireNbLigne(), MATParam.MATLireNbColonne());
		throw CMatriceException(MATRICE_ERROR_NON_CARREE, message);
	}

	int puiLigneEtColonneCible[2] = {0, -1};
	return CALCalculerDeterminant(MATParam, puiLigneEtColonneCible[0], puiLigneEtColonneCible[1]);
}

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
**** Sortie: CMatrice<double> => Comatrice correspondante à la matrice passé en paramètre    ****
************************************************************************************************/
template <class MType>
CMatrice<double> CCalculMatriciel<MType>::CALCalculerComatrice(CMatrice<MType> MATParam, MType mValeurRechercheCalculDeterminant) {
	CMatrice<double> dMATComatrice(MATParam.MATLireNbColonne());

	unsigned int uiLigne;
	unsigned int uiColonne;

	for (uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) {
		for (uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			double dValeur = std::pow(-1, uiLigne + uiColonne) * (CALCalculerDeterminant(CALCalculerSousMatrice(MATParam, uiLigne, uiColonne), mValeurRechercheCalculDeterminant));
			dMATComatrice.MATModifierElement(uiLigne, uiColonne, dValeur); // (-1)^(i+j) * determinant des sous matrices
		}
	}
	return dMATComatrice;
}

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
template <class MType>
CMatrice<double> CCalculMatriciel<MType>::CALCalculerComatrice(CMatrice<MType> MATParam) {
	CMatrice<double> dMATComatrice(MATParam.MATLireNbColonne());

	unsigned int uiLigne;
	unsigned int uiColonne;

	for (uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) {
		for (uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			double dValeur = std::pow(-1, uiLigne + uiColonne) * (CALCalculerDeterminant(CALCalculerSousMatrice(MATParam, uiLigne, uiColonne)));
			dMATComatrice.MATModifierElement(uiLigne, uiColonne, dValeur); // (-1)^(i+j) * determinant des sous matrices
		}
	}
	return dMATComatrice;
}
//PRIVATE

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
template <class MType>
int* CCalculMatriciel<MType>::CALTrouverMeilleurCibleDeterminant(CMatrice<MType> MATParam, MType valeurRecherchee) {
	unsigned int* piNbLigne = new unsigned int[MATParam.MATLireNbLigne()];
	unsigned int* piNbColonne = new unsigned int[MATParam.MATLireNbColonne()];

	unsigned int uiLigne = 0;
	unsigned int uiColonne = 0;

	for (uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) {
		piNbLigne[uiLigne] = 0;
		piNbColonne[uiLigne] = 0;
	}

	for (uiLigne = 0; uiLigne < MATParam.MATLireNbLigne(); uiLigne++) {
		for (uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			if (MATParam.MATLireElement(uiLigne, uiColonne) == valeurRecherchee) {
				piNbLigne[uiLigne] += 1; //incrementation quand trouvé
				piNbColonne[uiColonne] += 1;
			}
		}
	}

	return CALComparerCible(piNbLigne, piNbColonne, MATParam.MATLireNbLigne());
}

#ifndef MATRICE_DETERMINANT_INDEX_NOT_DEFINED
#define MATRICE_DETERMINANT_INDEX_NOT_DEFINED 9
#endif // ! MATRICE_DETERMINANT_INDEX_NOT_DEFINED 9

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
template <class MType>
double CCalculMatriciel<MType>::CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int iColonneCible, MType mValeurRechercheCalculDeterminant) {
	double value = 0;
	unsigned int uiColonne = 0;
	unsigned int uiLigne = 0;

	if (MATParam.MATLireNbColonne() < 3)
		return (MATParam.MATLireElement(0, 0)*MATParam.MATLireElement(1, 1) - MATParam.MATLireElement(1, 0)*MATParam.MATLireElement(0, 1)); //Calcule simple du determinant, condition d'arret de la méthode récursive

	if (iLigneCible >= 0 && iLigneCible <= MATParam.MATLireNbLigne() && iColonneCible < 0) { //Si le calcul doit être effectué en fonction des lignes 
		for (uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			CMatrice<MType> sousMatrice = CALCalculerSousMatrice(MATParam, iLigneCible, uiColonne); //On calcul la sousMatrice
			value += std::pow(-1, iLigneCible + uiColonne) * (MATParam.MATLireElement(iLigneCible, uiColonne) * CALCalculerDeterminant(sousMatrice, iLigneCible, iColonneCible, mValeurRechercheCalculDeterminant)); //Formule de Laplace en utilisant un appelle récursife 
		}
	}
	else if (iColonneCible >= 0 && iColonneCible <= MATParam.MATLireNbColonne() && iLigneCible < 0) {
		for (uiLigne = 0; uiLigne < MATParam.MATLireNbColonne(); uiLigne++) {
			CMatrice<MType> sousMatrice = CALCalculerSousMatrice(MATParam, uiLigne, iColonneCible);
			value += std::pow(-1, iColonneCible + uiLigne) * (MATParam.MATLireElement(uiLigne, iColonneCible) * CALCalculerDeterminant(sousMatrice, iLigneCible, iColonneCible, mValeurRechercheCalculDeterminant));
		}
	}
	else {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur vous devez indiquer soit une ligne cible ou une colonne cible pour le calcul du determinant ligne cible : %d, colonne cible : %d\0", MATRICE_DETERMINANT_INDEX_NOT_DEFINED, iLigneCible, iColonneCible);
		throw CMatriceException(ERROR_MAX_SIZE, message);
	}
	std::cout << value << std::endl;
	return value;
}

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
template <class MType>
double CCalculMatriciel<MType>::CALCalculerDeterminant(CMatrice<MType> MATParam, int iLigneCible, int iColonneCible) {
	double value = 0;
	unsigned int uiColonne = 0;
	unsigned int uiLigne = 0;

	if (MATParam.MATLireNbColonne() < 3)
		return (MATParam.MATLireElement(0, 0)*MATParam.MATLireElement(1, 1) - MATParam.MATLireElement(1, 0)*MATParam.MATLireElement(0, 1)); //Calcule simple du determinant, condition d'arret de la méthode récursive

	if (iLigneCible >= 0 && iLigneCible <= MATParam.MATLireNbLigne() && iColonneCible < 0) { //Si le calcul doit être effectué en fonction des lignes 
		for (uiColonne = 0; uiColonne < MATParam.MATLireNbColonne(); uiColonne++) {
			CMatrice<MType> sousMatrice = CALCalculerSousMatrice(MATParam, iLigneCible, uiColonne); //On calcul la sousMatrice
			value += std::pow(-1, iLigneCible + uiColonne) * (MATParam.MATLireElement(iLigneCible, uiColonne) * CALCalculerDeterminant(sousMatrice, iLigneCible, iColonneCible)); //Formule de Laplace en utilisant un appelle récursife 
		}
	}
	else if (iColonneCible >= 0 && iColonneCible <= MATParam.MATLireNbColonne() && iLigneCible < 0) {
		for (uiLigne = 0; uiLigne < MATParam.MATLireNbColonne(); uiLigne++) {
			CMatrice<MType> sousMatrice = CALCalculerSousMatrice(MATParam, uiLigne, iColonneCible);
			value += std::pow(-1, iColonneCible + uiLigne) * (MATParam.MATLireElement(uiLigne, iColonneCible) * CALCalculerDeterminant(sousMatrice, iLigneCible, iColonneCible));
		}
	}
	else {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur vous devez indiquer soit une ligne cible ou une colonne cible pour le calcul du determinant ligne cible : %d, colonne cible : %d\0", MATRICE_DETERMINANT_INDEX_NOT_DEFINED, iLigneCible, iColonneCible);
		throw CMatriceException(ERROR_MAX_SIZE, message);
	}
	std::cout << value << std::endl;
	return value;
}

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
template <class MType>
CMatrice<MType> CCalculMatriciel<MType>::CALCalculerSousMatrice(CMatrice<MType> MATParam, unsigned int uiLigneCible, unsigned int uiColonneCible) {
	if (MATParam.MATLireNbColonne() != MATParam.MATLireNbLigne()) {
		char *message = new char[ERROR_MAX_SIZE];
		sprintf_s(message, ERROR_MAX_SIZE, "ERREUR %d \nErreur la matrice n'est pas carrée => nombre de ligne : %d, nombre de colonne : %d\0", MATRICE_ERROR_NON_CARREE, MATParam.MATLireNbLigne(), MATParam.MATLireNbColonne());
		throw CMatriceException(ERROR_MAX_SIZE, message);
	}

	CMatrice<MType> MATSousMatrice(MATParam.MATLireNbColonne() - 1);

	unsigned int uiSousMatriceLigne = -1;
	unsigned int uiSousMatriceColonne = 0;
	
	unsigned int uiLigne;
	unsigned int uiColonne;

	for (uiLigne=0; uiLigne<MATParam.MATLireNbLigne(); uiLigne++) { //ligne
		uiSousMatriceLigne++;
		if (uiLigne == uiLigneCible) { //si la ligne est celle passé en paramètre on l'ignore
			uiSousMatriceLigne--;
			continue;
		}
		uiSousMatriceColonne = -1;
		for (uiColonne=0; uiColonne<MATParam.MATLireNbColonne(); uiColonne++) { //colonne
			uiSousMatriceColonne++;
			if (uiColonne == uiColonneCible) {
				uiSousMatriceColonne--;
				continue;
			}
			MATSousMatrice.MATModifierElement(uiSousMatriceLigne, uiSousMatriceColonne, MATParam.MATLireElement(uiLigne, uiColonne));
			//MATSousMatrice.MATAfficherMatrice();
		}
	}
	return MATSousMatrice;
}

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
template <class MType>
int* CCalculMatriciel<MType>::CALComparerCible(unsigned int* piNbLigne, unsigned int* piNbColonne, unsigned int uiTaille) {
	unsigned int uiMeilleurCibleLigne = 0;
	unsigned int uiMeilleurCibleColonne = 0;

	unsigned int uiLigne = 0;

	for (int uiBoucle = 0; uiBoucle < uiTaille; uiBoucle++) {
		if (piNbLigne[uiBoucle] > piNbLigne[uiMeilleurCibleLigne])
			uiMeilleurCibleLigne = uiBoucle;

		if (piNbColonne[uiBoucle] > piNbColonne[uiMeilleurCibleColonne])
			uiMeilleurCibleColonne = uiBoucle;
	}

	if (piNbColonne[uiMeilleurCibleColonne] >= piNbLigne[uiMeilleurCibleLigne])
		return new int[2] { static_cast<int>(uiMeilleurCibleColonne), -1};
	else
		return new int[2] {-1, static_cast<int>(uiMeilleurCibleColonne)};
}