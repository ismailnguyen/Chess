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
        NumCoups=1; //le nombre de coups joué est à 1

        SuiteEchiquier[0].InitEchiquier(); //au début de la partie, on initialise le premier échiquier
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
        SuiteEchiquier[NumDemiCoups].CopieEchiquier(EchSource); //on récupère l'échiquier correspondant au demi coups donné, et on la copie dans EchSource

        NumDemiCoups++; //on incrémente le nombre de demi coups
        NumCoups = (NumDemiCoups+1)/2; //on incrémente le nombre de coups
}
//---------------------------------------------------------------------------
/*AnsiString Partie::VisuEchiquier(int num)
{
        //RichEdit1->Lines->Clear(); //on vide le cadre
        //RichEdit1->Lines->Add(SuiteEchiquier[num].VisuEchiquier()); //puis on y ajoute le contenu de la chaine de VisuEchiquier de l'objet SuiteEchiquier
}*/
