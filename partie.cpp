#pragma hdrstop
#include "partie.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
Partie::Partie()
{
        InitialisePartie();
}
//---------------------------------------------------------------------------
void Partie::InitialisePartie()
{
        NumDemiCoups=1;
        NumCoups=1; //le nombre de coups jou� est � 1

        SuiteEchiquier[0].InitEchiquier(); //au d�but de la partie, on initialise le premier �chiquier
}
//---------------------------------------------------------------------------
void Partie::ModifieNbCoups(int demicoups)
{
        NumDemiCoups = demicoups;
        NumCoups = (demicoups+1)/2;
}
//---------------------------------------------------------------------------
void Partie::SauvegardeEchiquier(Echiquier EchSource)
{
        SuiteEchiquier[NumDemiCoups].CopieEchiquier(EchSource); //on r�cup�re l'�chiquier correspondant au demi coups donn�, et on la copie dans EchSource

        NumDemiCoups++; //on incr�mente le nombre de demi coups
        NumCoups = (NumDemiCoups+1)/2; //on incr�mente le nombre de coups
}
//---------------------------------------------------------------------------
/*AnsiString Partie::VisuEchiquier(int num)
{
        //RichEdit1->Lines->Clear(); //on vide le cadre
        //RichEdit1->Lines->Add(SuiteEchiquier[num].VisuEchiquier()); //puis on y ajoute le contenu de la chaine de VisuEchiquier de l'objet SuiteEchiquier
}*/
