#ifndef CException_H
#define CException_H

class CException
{
  private:
    unsigned int uiEXCErreur;

  public:
    /*************************************************************
    **** Nom: CException                                      ****
    **************************************************************
    **** Constructeur de confort de la classe CException      ****
    **************************************************************
    **** Précondition:                                        ****
    **** Entrée: Valeur à prendre pour l'attribut uiEXCErreur ****
    **** Entraîne:                                            ****
    **** Sortie:                                              ****
    *************************************************************/
    CException(unsigned int uiErreur) { uiEXCErreur = uiErreur; }


    /*******************************************************************
    **** Nom: EXCLireErreur                                         ****
    ********************************************************************
    **** Cette méthode retourne la valeur de l'attribut uiEXCErreur ****
    ********************************************************************
    **** Précondition:                                              ****
    **** Entrée:                                                    ****
    **** Entraîne:                                                  ****
    **** Sortie: Valeur de uiEXCErreur                              ****
    *******************************************************************/
    unsigned int EXCLireErreur() { return uiEXCErreur; }


    /**********************************************************************
    **** Nom: EXCModifierErreur                                        ****
    ***********************************************************************
    **** Cette méthode permet de modifier la valeur de uiEXCErreur     ****
    ***********************************************************************
    **** Précondition:                                                 ****
    **** Entrée: Nouvelle valeur à prendre pour l'attribut uiEXCErreur ****
    **** Entraîne:                                                     ****
    **** Sortie:                                                       ****
    **********************************************************************/
    void EXCModifierErreur(unsigned int uiErreur) { uiEXCErreur = uiErreur; }
};

#endif