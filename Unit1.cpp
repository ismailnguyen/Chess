#define __WIN__
#include "mysql.h"
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "echiquier.h"
#include "joueur.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <fstream>
using namespace std;
MYSQL *mySQL;
//---------------------------------------------------------------------------

TForm1 *Form1;
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
mySQL = mysql_init(NULL);

// association de chaque case Image à une cellule du tableau lacase[ligne][colonne]
lacase[0][0] = Image1;
lacase[0][1] = Image2;
lacase[0][2] = Image3;
lacase[0][3] = Image4;
lacase[0][4] = Image5;
lacase[0][5] = Image6;
lacase[0][6] = Image7;
lacase[0][7] = Image8;

lacase[1][0] = Image9;
lacase[1][1] = Image10;
lacase[1][2] = Image11;
lacase[1][3] = Image12;
lacase[1][4] = Image13;
lacase[1][5] = Image14;
lacase[1][6] = Image15;
lacase[1][7] = Image16;

lacase[2][0] = Image17;
lacase[2][1] = Image18;
lacase[2][2] = Image19;
lacase[2][3] = Image20;
lacase[2][4] = Image21;
lacase[2][5] = Image22;
lacase[2][6] = Image23;
lacase[2][7] = Image24;

lacase[3][0] = Image25;
lacase[3][1] = Image26;
lacase[3][2] = Image27;
lacase[3][3] = Image28;
lacase[3][4] = Image29;
lacase[3][5] = Image30;
lacase[3][6] = Image31;
lacase[3][7] = Image32;

lacase[4][0] = Image33;
lacase[4][1] = Image34;
lacase[4][2] = Image35;
lacase[4][3] = Image36;
lacase[4][4] = Image37;
lacase[4][5] = Image38;
lacase[4][6] = Image39;
lacase[4][7] = Image40;

lacase[5][0] = Image41;
lacase[5][1] = Image42;
lacase[5][2] = Image43;
lacase[5][3] = Image44;
lacase[5][4] = Image45;
lacase[5][5] = Image46;
lacase[5][6] = Image47;
lacase[5][7] = Image48;

lacase[6][0] = Image49;
lacase[6][1] = Image50;
lacase[6][2] = Image51;
lacase[6][3] = Image52;
lacase[6][4] = Image53;
lacase[6][5] = Image54;
lacase[6][6] = Image55;
lacase[6][7] = Image56;

lacase[7][0] = Image57;
lacase[7][1] = Image58;
lacase[7][2] = Image59;
lacase[7][3] = Image60;
lacase[7][4] = Image61;
lacase[7][5] = Image62;
lacase[7][6] = Image63;
lacase[7][7] = Image64;

for(int a=0; a<8; a++)
{
        for(int b=0; b<8; b++)
        {
                if(MonEchiquier.LitTabEchiquier(a, b) != ' ')
                {
                        lacase[a][b]->DragCursor; // affecter le cursor de drag&drop à toutes les images non vides
                }
        }
}

TraitBlanc->Picture->LoadFromFile("assets/piece/traitblanc.bmp");
TraitNoir->Picture->LoadFromFile("assets/piece/traitnoir.bmp");

ImageFondPromotion->Visible = false;

TraitBlanc->Picture->LoadFromFile("assets/piece/traitblanc.bmp");
TraitNoir->Picture->LoadFromFile("assets/piece/traitnoir.bmp");
fondMode->Picture->LoadFromFile("assets/bg51.jpg");

MonEchiquier.InitEchiquier(); //après avoir attribué chaque emplacement TImage, on initialise les positions de nos pièces
ChargeFormEchiquier(MonEchiquier); //on charge chaque images respectivement à son caractère associé au tableau par la fonction ChargeFormEchiquier

Button1Click(NULL); //on initialise le RichEdit avec le contenu de l'échiquier

JBlanc.DonneTrait(); // droit de jouer aux blancs
JNoir.RetireTrait(); //on enlève le droit de jouer aux noirs
TraitBlanc->Visible = true; //affichage blanc
TraitNoir->Visible = false; //affichage noir

demicoupsaffiche = 0; //initialisation de demicoupsaffiche

JeuInterdit = false;

this->TimerFini = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::arriveCase(TObject *Sender, TObject *Source, int X,
      int Y, TDragState State, bool &Accept)
{
        Accept = true;  //autorisation du Drag&Drop
}
//---------------------------------------------------------------------------
void __fastcall TForm1::quitteCase(TObject *Sender, TObject *Source, int X,
      int Y)
{
int idep, jdep, iarr, jarr; //déclaration des valeurs pour les coordonnées dep:départ et arr:arrivée

if(Sender != Source)
{
	for(int i=0; i<=7; i++) //boucle pour parcourir toute les lignes de l'echiquier
	{
		for(int j=0; j<=7; j++) //colonnes
		{
			if(Source == lacase[i][j]) //si la pièce de la boucle correspond à la pièce de départ
			{
                                //attribution des coordonnées
				idep = i;
				jdep = j;
			}

			if(Sender == lacase[i][j]) //si la pièce de la boucle correspond à la pièce d'arrivée
			{
				iarr = i;
				jarr = j;
			}
		}
	}
        if (     (!JeuInterdit) && ( MonEchiquier.DeplacementPossible(idep, jdep, iarr, jarr))) //on vérifie que la couleur de départ n'est pas la même que la couleur d'arrivée
        {
                if((MonEchiquier.EstUnePieceBlanche(idep, jdep) && JBlanc.LitTrait()) || (MonEchiquier.EstUnePieceNoire(idep, jdep) && JNoir.LitTrait()))
                {
                        if((iarr == 5)
                        && (jarr == jdep+1) /* prise en passant d'un pion noir avec blanc à droite */
                        && (MonEchiquier.LitTabEchiquier(4, jdep) == 'p')
                        && (MonEchiquier.LitTabEchiquier(4, jdep+1) == 'P')
                        && (idep == 4))
                                {
                                        if((MaPartie.LitTabEchiquier(4, jdep+1, demicoupsaffiche-1) == ' ')
                                        && (MaPartie.LitTabEchiquier(5, jdep+1, demicoupsaffiche-1) == ' ')
                                        && (MaPartie.LitTabEchiquier(6, jdep+1, demicoupsaffiche-1) == 'P'))
                                        {
                                                MonEchiquier.ModifieEchiquier(' ', 4, jdep+1); //le pion sur le coté meurt
                                                MonEchiquier.ModifieEchiquier(' ', 4, jdep); //le pion est enlevé de sa case pour aller manger
                                                MonEchiquier.ModifieEchiquier('p', 5, jarr); //le pion prend sa nouvelle place
                                        }
                                        else { AfficheErreur("Déplacement impossible"); return; }
                        }
                        else if((iarr == 5) /* prise en passant d'un pion noir avec blanc à gauche */
                                && (jarr == jdep-1)
                                && (MonEchiquier.LitTabEchiquier(4, jdep) == 'p')
                                && (MonEchiquier.LitTabEchiquier(4, jdep-1) == 'P')
                                && (idep == 4))
                                {
                                        if((MaPartie.LitTabEchiquier(4, jdep-1, demicoupsaffiche-1) == ' ')
                                        && (MaPartie.LitTabEchiquier(5, jdep-1, demicoupsaffiche-1) == ' ')
                                        && (MaPartie.LitTabEchiquier(6, jdep-1, demicoupsaffiche-1) == 'P'))
                                        {
                                                MonEchiquier.ModifieEchiquier(' ', 4, jdep-1); //le pion sur le coté meurt
                                                MonEchiquier.ModifieEchiquier(' ', 4, jdep); //le pion est enlevé de sa case pour aller manger
                                                MonEchiquier.ModifieEchiquier('p', 5, jarr); //le pion prend sa nouvelle place
                                        }
                                        else { AfficheErreur("Déplacement impossible"); return; }
                        }
                        else if((iarr == 2) /* prise en passant d'un pion blanc avec noir à droite */
                                && (jarr == jdep+1)
                                && (MonEchiquier.LitTabEchiquier(3, jdep) == 'P')
                                && (MonEchiquier.LitTabEchiquier(3, jdep+1) == 'p')
                                && (idep == 3))
                                {
                                        if((MaPartie.LitTabEchiquier(3, jdep+1, demicoupsaffiche-1) == ' ')
                                        && (MaPartie.LitTabEchiquier(2, jdep+1, demicoupsaffiche-1) == ' ')
                                        && (MaPartie.LitTabEchiquier(1, jdep+1, demicoupsaffiche-1) == 'p'))
                                        {
                                                MonEchiquier.ModifieEchiquier(' ', 3, jdep+1); //le pion sur le coté meurt
                                                MonEchiquier.ModifieEchiquier(' ', 3, jdep); //le pion est enlevé de sa case pour aller manger
                                                MonEchiquier.ModifieEchiquier('P', 2, jarr); //le pion prend sa nouvelle place
                                        }
                                        else { AfficheErreur("Déplacement impossible"); return; }
                        }
                        else if((iarr == 2) /* prise en passant d'un pion blanc avec noir à gauche */
                                && (jarr == jdep-1)
                                && (MonEchiquier.LitTabEchiquier(3, jdep) == 'P')
                                && (MonEchiquier.LitTabEchiquier(3, jdep-1) == 'p')
                                && (idep == 3))
                                {
                                        if((MaPartie.LitTabEchiquier(3, jdep-1, demicoupsaffiche-1) == ' ')
                                        && (MaPartie.LitTabEchiquier(2, jdep-1, demicoupsaffiche-1) == ' ')
                                        && (MaPartie.LitTabEchiquier(1, jdep-1, demicoupsaffiche-1) == 'p'))
                                        {
                                                MonEchiquier.ModifieEchiquier(' ', 3, jdep-1); //le pion sur le coté meurt
                                                MonEchiquier.ModifieEchiquier(' ', 3, jdep); //le pion est enlevé de sa case pour aller manger
                                                MonEchiquier.ModifieEchiquier('P', 2, jarr); //le pion prend sa nouvelle place
                                        }
                                        else { AfficheErreur("Déplacement impossible"); return; }
                        }
                        else if((MonEchiquier.LitTabEchiquier(idep, jdep) == 'R') //grand roque blanc
                                && (idep == 7)
                                && (jdep == 4)
                                && (iarr == 7)
                                && (jarr == 2))
                        {
                                if(MonEchiquier.GrandRoqueBlancPossible())
                                {
                                        MonEchiquier.ModifieEchiquier(' ', 7, 4);
                                        MonEchiquier.ModifieEchiquier('R', 7, 2);
                                        MonEchiquier.ModifieEchiquier('T', 7, 3);
                                        MonEchiquier.ModifieEchiquier(' ', 7, 0);
                                        MonEchiquier.InterditGrandRoqueBlanc();
                                }
                                else { AfficheErreur("Déplacement impossible"); return; }
                        }
                        else if((MonEchiquier.LitTabEchiquier(idep, jdep) == 'R') //petit roque blanc
                                && (idep == 7)
                                && (jdep == 4)
                                && (iarr == 7)
                                && (jarr == 6))
                        {
                                if(MonEchiquier.PetitRoqueBlancPossible())
                                {
                                        MonEchiquier.ModifieEchiquier(' ', 7, 4);
                                        MonEchiquier.ModifieEchiquier('R', 7, 6);
                                        MonEchiquier.ModifieEchiquier('T', 7, 5);
                                        MonEchiquier.ModifieEchiquier(' ', 7, 7);
                                        MonEchiquier.InterditPetitRoqueBlanc();
                                }
                                else { AfficheErreur("Déplacement impossible"); return; }
                        }
                        else if((MonEchiquier.LitTabEchiquier(idep, jdep) == 'r') //grand roque noir
                                && (idep == 0)
                                && (jdep == 4)
                                && (iarr == 0)
                                && (jarr == 2))
                        {
                                if(MonEchiquier.GrandRoqueNoirPossible())
                                {
                                        MonEchiquier.ModifieEchiquier(' ', 0, 4);
                                        MonEchiquier.ModifieEchiquier('r', 0, 2);
                                        MonEchiquier.ModifieEchiquier('t', 0, 3);
                                        MonEchiquier.ModifieEchiquier(' ', 0, 0);
                                        MonEchiquier.InterditGrandRoqueNoir();
                                }
                                else { AfficheErreur("Déplacement impossible"); return; }
                        }
                        else if((MonEchiquier.LitTabEchiquier(idep, jdep) == 'r') //petit roque noir
                                && (idep == 0)
                                && (jdep == 4)
                                && (iarr == 0)
                                && (jarr == 6))
                        {
                                if(MonEchiquier.PetitRoqueNoirPossible())
                                {
                                        MonEchiquier.ModifieEchiquier(' ', 0, 4);
                                        MonEchiquier.ModifieEchiquier('r', 0, 6);
                                        MonEchiquier.ModifieEchiquier('t', 0, 5);
                                        MonEchiquier.ModifieEchiquier(' ', 0, 7);
                                        MonEchiquier.InterditPetitRoqueNoir();
                                }
                                else { AfficheErreur("Déplacement impossible"); return; }
                        }
                        else if((MonEchiquier.CaseEnEchec(iarr, jarr, 1) && (MonEchiquier.LitTabEchiquier(idep, jdep) == 'r'))
                                || (MonEchiquier.CaseEnEchec(iarr, jarr, 0) && (MonEchiquier.LitTabEchiquier(idep, jdep) == 'R')))
                        {
                                return;
                        }
                        else
                        {

                                char Cpiece2 = MonEchiquier.LitTabEchiquier(iarr, jarr); //caractère de la pièce d'arrivée

                                char Cpiece = MonEchiquier.LitTabEchiquier(idep, jdep); //on cherche le caractère de la pièce de départ qu'on souhaite déplacer
                                MonEchiquier.ModifieEchiquier(Cpiece, iarr, jarr);//la nouvelle case du tableau prend la lettre de la pièce à deplacer
                                MonEchiquier.ModifieEchiquier(' ', idep, jdep); //la lettre de la pièce à déplacer devient un espace

                                if((Cpiece == 'r') && (idep == 0) && (jdep == 4))
                                {
                                        MonEchiquier.InterditGrandRoqueNoir();
                                        MonEchiquier.InterditPetitRoqueNoir();
                                }
                                if((Cpiece == 'R') && (idep == 7) && (jdep == 4))
                                {
                                        MonEchiquier.InterditGrandRoqueBlanc();
                                        MonEchiquier.InterditPetitRoqueBlanc();
                                }
                                if((Cpiece == 't') && (idep == 0) && (jdep == 0))
                                {
                                        this->MonEchiquier.InterditGrandRoqueNoir();
                                }
                                if((Cpiece == 't') && (idep == 0) && (jdep == 7))
                                {
                                        this->MonEchiquier.InterditPetitRoqueNoir();
                                }
                                if((Cpiece == 'T') && (idep == 7) && (jdep == 0))
                                {
                                        this->MonEchiquier.InterditGrandRoqueBlanc();
                                }
                                if((Cpiece == 'T') && (idep == 7) && (jdep == 7))
                                {
                                        this->MonEchiquier.InterditPetitRoqueBlanc();
                                }



                                if(Cpiece2 == 'r')
                                {
                                        ShowMessage("Echec et Mat\n\nLe Joueur 1 remporte la partie !");
                                        
                                        JBlanc.DonneTrait();
                                        JNoir.RetireTrait();
                                        MonEchiquier.InitEchiquier();
                                }
                                else if(Cpiece2 == 'R')
                                {
                                        ShowMessage("Echec et Mat\n\nLe Joueur 2 remporte la partie !");
                                        
                                        JBlanc.DonneTrait();
                                        JNoir.RetireTrait();
                                        MonEchiquier.InitEchiquier();
                                }

                                if((MonEchiquier.LitTabEchiquier(0, jarr) == 'P') || (MonEchiquier.LitTabEchiquier(7, jarr) == 'p'))
                                {
                                        ImageFondPromotion->Visible = true;

                                        this->LabelSocket->Caption = "Promotion";

                                        this->PromotionDame->Visible = true;
                                        this->PromotionDame->Picture->LoadFromFile("assets/promoDame.bmp");

                                        this->PromotionFou->Visible = true;
                                        this->PromotionFou->Picture->LoadFromFile("assets/promoFou.bmp");

                                        this->PromotionCavalier->Visible = true;
                                        this->PromotionCavalier->Picture->LoadFromFile("assets/promoCavalier.bmp");

                                        this->PromotionTour->Visible = true;
                                        this->PromotionTour->Picture->LoadFromFile("assets/promoTour.bmp");

                                        JeuInterdit = true;
                                }
                        }
                        ImageNotificationClick(NULL);
                        ImageErreurClick(NULL);

                        ChargeFormEchiquier(MonEchiquier);

                        if(MonEchiquier.RoiEnEchec(1)) ShowMessage("Le Roi blanc en echec !");
                        if(MonEchiquier.RoiEnEchec(0)) ShowMessage("Le Roi noir en echec !");

                        ChangeTrait(); //on change les droits de jouer
                        demicoupsaffiche++; //incrémentation du demi coups joué
                        MaPartie.SauvegardeEchiquier(MonEchiquier); //on sauvegarde l'échiquier présent a chaque demi coups joué

                        Button1Click(NULL); //actualisation, on appel la fonction du bouton sans y cliquer dessus à chaque déplacement
                        EnvoiCoup();
                }
                else { AfficheErreur("Déplacement impossible"); return; }
        }
        else { AfficheErreur("Déplacement impossible"); return; }
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
RichEdit1->Lines->Clear(); //on vide le cadre
RichEdit1->Lines->Add(MonEchiquier.VisuEchiquier()); //puis on y ajoute le contenu de la chaine de VisuEchiquier de l'objet MonEchiquier
}
//---------------------------------------------------------------------------
void TForm1::EnvoiCoup()
{
        //Envoyer une ligne contenant les caractères de notre échiquier à l'adversaire
        AnsiString EchiquierSurUneLigne = "";

        for(int i=0; i<8; i++)
                for(int j=0; j<8; j++)
                        EchiquierSurUneLigne = EchiquierSurUneLigne + MonEchiquier.LitTabEchiquier(i, j);

        if(mode == 1)
        {
                this->ClientSocket1->Socket->SendText(EchiquierSurUneLigne);
                JeuInterdit = true;
        }
        else if(mode == 2)
        {
                MonClientSocket->SendText(EchiquierSurUneLigne);
                JeuInterdit = false;
        }
}
//---------------------------------------------------------------------------
void TForm1::RecoitCoup(AnsiString TexteRecu)
{
        //Extraire les pions envoyés par l'adversaire
        if(TexteRecu.Length() >= 64)
        {
                for(int i=0; i<64; i++)
                        MonEchiquier.ModifieEchiquier(TexteRecu.c_str()[i], i/8, i%8);

                MaPartie.SauvegardeEchiquier(MonEchiquier);
                demicoupsaffiche++;
                ChargeFormEchiquier(MonEchiquier);
                ChangeTrait();
                JeuInterdit = false;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click2(TObject *Sender)
{
        if(RichEdit1->Visible)
        {
                RichEdit1->Visible = false;
                VisuRichEdit->Picture->LoadFromFile("assets/visualiser.bmp");
        }
        else
        {
                RichEdit1->Visible = true;
                VisuRichEdit->Picture->LoadFromFile("assets/masquer.bmp");
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
        if(demicoupsaffiche > 0)
        {
                demicoupsaffiche--; //on va au demi coups joué précedemment
                MaPartie.ExtraitPosition(MonEchiquier, demicoupsaffiche); //on récupere l'échiquier correspondant au demi coups donné ci-dessus
                MaPartie.ModifieNbCoups(demicoupsaffiche+1); //on modifie le nombre de coups avec le demi coups de départ ((-1) + 1)
                ChargeFormEchiquier(MonEchiquier); //on charge l'échiquier qu'on vient de récupérer
                ChangeTrait(); //on donne les nouvelles permissions
                Button1Click(NULL); //on actualise l'affichage des deplacement
           }
}
//---------------------------------------------------------------------------

void TForm1::ChargeFormEchiquier(Echiquier UnEchiquier)
{
    for(int i=0; i<=7; i++) //boucle pour parcourir toute les lignes de l'echiquier
    {
		for(int j=0; j<=7; j++) //colonnes
		{
                        switch (MonEchiquier.LitTabEchiquier(i, j)) //on récpere le caractère de chaque pièce
                        {
                                //on associe l'image correspondante à la pièce au caractère trouvé
                                case 't' : lacase[i][j]->Picture->LoadFromFile("assets/piece/t2.bmp"); break;
                                case 'T' : lacase[i][j]->Picture->LoadFromFile("assets/piece/t1.bmp"); break;
                                case 'c' : lacase[i][j]->Picture->LoadFromFile("assets/piece/c2.bmp"); break;
                                case 'C' : lacase[i][j]->Picture->LoadFromFile("assets/piece/c1.bmp"); break;
                                case 'f' : lacase[i][j]->Picture->LoadFromFile("assets/piece/f2.bmp"); break;
                                case 'F' : lacase[i][j]->Picture->LoadFromFile("assets/piece/f1.bmp"); break;
                                case 'd' : lacase[i][j]->Picture->LoadFromFile("assets/piece/d2.bmp"); break;
                                case 'D' : lacase[i][j]->Picture->LoadFromFile("assets/piece/d1.bmp"); break;
                                case 'r' : lacase[i][j]->Picture->LoadFromFile("assets/piece/r2.bmp"); break;
                                case 'R' : lacase[i][j]->Picture->LoadFromFile("assets/piece/r1.bmp"); break;
                                case 'p' : lacase[i][j]->Picture->LoadFromFile("assets/piece/p2.bmp"); break;
                                case 'P' : lacase[i][j]->Picture->LoadFromFile("assets/piece/p1.bmp"); break;
                                case ' ' : lacase[i][j]->Picture = NULL; break;
                        }
		}
	}
}
//---------------------------------------------------------------------------
void TForm1::ChangeTrait()
{
        if(JBlanc.LitTrait() == 1) //le blanc vient de jouer, on passe au noir
        {
                JBlanc.RetireTrait(); //le blanc ne peut plus jouer
                JNoir.DonneTrait(); //le noir va pouvoir jouer
                TraitNoir->Visible = true; //afficher : "Au noir de jouer"
                TraitBlanc->Visible = false; //cacher l'indication de jouer au blanc
        }
        else if(JNoir.LitTrait() == 1) //le noir vient de jouer, on passe au blanc
        {
                JBlanc.DonneTrait(); //le noir ne peut plus jouer
                JNoir.RetireTrait(); //le blanc va pouvoir jouer
                TraitNoir->Visible = false; //cacher l'indication de jouer au noir
                TraitBlanc->Visible = true; //afficher : "Au blanc de jouer"
        }
}
//---------------------------------------------------------------------------
void TForm1::EffaceFormEchiquier()
{
    for(int i=0; i<=7; i++) //boucle pour parcourir toute les lignes de l'echiquier
	{
		for(int j=0; j<=7; j++) //colonnes
		{
                //case vide à chaque cellule de chaque ligne
                lacase[i][j]->Picture->LoadFromFile("assets/piece/vide.bmp");
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Radio1Click(TObject *Sender) //Promotion en Dame
{
                        this->ImageFondPromotion->Visible = false;
                        PromotionDame->Visible = false;
                        PromotionFou->Visible = false;
                        PromotionCavalier->Visible = false;
                        PromotionTour->Visible = false;

                for(int i=0; i<=7; i++)
                {
                        if(MonEchiquier.LitTabEchiquier(0, i) == 'P')
                        {
                                MonEchiquier.ModifieEchiquier('D', 0, i);
                        }
                        else if(MonEchiquier.LitTabEchiquier(7, i) == 'p')
                        {
                                MonEchiquier.ModifieEchiquier('d', 7, i);
                        }
                }

                        JeuInterdit = false;
                        ChargeFormEchiquier(MonEchiquier);
                        MaPartie.SauvegardeEchiquier(MonEchiquier);
                        Button1Click(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Radio2Click(TObject *Sender) //Promotion en Fou
{
                        this->ImageFondPromotion->Visible = false;
                        PromotionDame->Visible = false;
                        PromotionFou->Visible = false;
                        PromotionCavalier->Visible = false;
                        PromotionTour->Visible = false;

                for(int i=0; i<=7; i++)
                {
                        if(MonEchiquier.LitTabEchiquier(0, i) == 'P')
                        {
                                MonEchiquier.ModifieEchiquier('F', 0, i);
                        }
                        else if(MonEchiquier.LitTabEchiquier(7, i) == 'p')
                        {
                                MonEchiquier.ModifieEchiquier('f', 7, i);
                        }
                }

                        JeuInterdit = false;
                        ChargeFormEchiquier(MonEchiquier);
                        MaPartie.SauvegardeEchiquier(MonEchiquier);
                        Button1Click(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Radio3Click(TObject *Sender) //Promotion en Cavalier
{
                        this->ImageFondPromotion->Visible = false;
                        PromotionDame->Visible = false;
                        PromotionFou->Visible = false;
                        PromotionCavalier->Visible = false;
                        PromotionTour->Visible = false;

                for(int i=0; i<=7; i++)
                {
                        if(MonEchiquier.LitTabEchiquier(0, i) == 'P')
                        {
                                MonEchiquier.ModifieEchiquier('C', 0, i);
                        }
                        else if(MonEchiquier.LitTabEchiquier(7, i) == 'p')
                        {
                                MonEchiquier.ModifieEchiquier('c', 7, i);
                        }
                }

                        JeuInterdit = false;
                        ChargeFormEchiquier(MonEchiquier);
                        MaPartie.SauvegardeEchiquier(MonEchiquier);
                        Button1Click(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Radio4Click(TObject *Sender) //Promotion en Tour
{
                        this->ImageFondPromotion->Visible = false;
                        PromotionDame->Visible = false;
                        PromotionFou->Visible = false;
                        PromotionCavalier->Visible = false;
                        PromotionTour->Visible = false;

                for(int i=0; i<=7; i++)
                {
                        if(MonEchiquier.LitTabEchiquier(0, i) == 'P')
                        {
                                MonEchiquier.ModifieEchiquier('T', 0, i);
                        }
                        else if(MonEchiquier.LitTabEchiquier(7, i) == 'p')
                        {
                                MonEchiquier.ModifieEchiquier('t', 7, i);
                        }
                }

                        JeuInterdit = false;
                        ChargeFormEchiquier(MonEchiquier);
                        MaPartie.SauvegardeEchiquier(MonEchiquier);
                        Button1Click(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioGroupModeClick(TObject *Sender)
{
        mode = this->RadioGroupMode->ItemIndex;

        if(mode == 1) //mode client
        {
                AfficheNotification("Rentre les informations du serveur\net choisis ta couleur");
                this->GroupBoxParametrage->Visible = true;
                this->RadioGroupCouleur->Visible = true;
                this->EditIP->Visible = true;
                this->EditPort->Visible = true;
                this->EditPortServeur->Visible = false;
                this->ImageParametrageOk->Visible = true;
                this->EditIP->Text = "Adresse IP serveur";
                this->EditPort->Text = "Port serveur";

                //ImageNotificationClick(NULL);
        }
        else if(mode == 2) //mode serveur
        {
                AfficheNotification("Configure ton serveur");
                this->GroupBoxParametrage->Visible = true;
                this->RadioGroupCouleur->Visible = false;
                this->EditIP->Visible = false;
                this->EditPort->Visible = false;
                this->EditPortServeur->Visible = true;
                this->ImageParametrageOk->Visible = true;
                this->EditPortServeur->Text = "Port serveur";

                //ImageNotificationClick(NULL);
        }
        else //jeu en local
        {
                this->GroupBoxParametrage->Visible = false;
                this->RadioGroupMode->Visible = false;
                this->fondMode->Visible = false;
                LabelSocket->Caption = "";

                AfficheNotification("A toi de jouer");

                //ImageNotificationClick(NULL);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditPortChange(TObject *Sender)
{
        this->EditPort->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditIPChange(TObject *Sender)
{
        this->EditIP->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditPortServeurChange(TObject *Sender)
{
        this->EditPortServeur->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButtonParametrageClick(TObject *Sender)
{
        if(mode == 1) //mode client
        {
                this->ClientSocket1->Host = this->EditIP->Text;
                this->ClientSocket1->Port = this->EditPort->Text.ToInt();
                this->ClientSocket1->Active = true;
        }
        else if(mode == 2) //mode serveur
        {
                this->ServerSocket1->Port = this->EditPortServeur->Text.ToInt();
                this->ServerSocket1->Active = true;
                this->LabelSocket->Caption = "Serveur lancé sur le port " + this->EditPortServeur->Text;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        this->GroupBoxParametrage->Visible = false;
        this->RadioGroupMode->Visible = false;
        this->fondMode->Visible = false;
        
        MonClientSocket = Socket;
        this->LabelSocket->Caption = "Un client vient de se connecter ("+MonClientSocket->RemoteAddress+")";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Connecting(TObject *Sender,
      TCustomWinSocket *Socket)
{
        this->LabelSocket->Caption = "Connexion en cours... ("+this->EditIP->Text+")";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Connect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        this->GroupBoxParametrage->Visible = false;
        this->RadioGroupMode->Visible = false;
        this->fondMode->Visible = false;

        this->LabelSocket->Caption = "Connecté à un serveur";

        if(RadioGroupCouleur->ItemIndex == 0)
        {
                CouleurClient = 0;
                JeuInterdit = false; //les blancs jouent
                this->ClientSocket1->Socket->SendText("Blancs");
                AfficheNotification("Vous avez les Blancs");
        }
        else
        {
                CouleurClient = 1;
                JeuInterdit = true;
                this->ClientSocket1->Socket->SendText("Noirs");
                AfficheNotification("Vous avez les Noirs");
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
        AfficheErreur("Erreur lors de la connexion...");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        AfficheErreur("Le client s'est déconnecté");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        if(this->ServerSocket1->Active) this->ServerSocket1->Active = false;

        if(this->ClientSocket1->Active) this->ClientSocket1->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerSocket1ClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        AnsiString message = Socket->ReceiveText();

        if(message == "Blancs")
        {
                AfficheNotification("Vous avez les Bleus");
                MonEchiquier.InitEchiquier();
                ChargeFormEchiquier(MonEchiquier);
                JeuInterdit = true;
        }
        else if(message == "Noirs")
        {
                AfficheNotification("Vous avez les Jaunes");
                MonEchiquier.InitEchiquier();
                ChargeFormEchiquier(MonEchiquier);
                JeuInterdit = false;
        }
        else if(message.Length() >= 64)
        {
                this->RecoitCoup(message);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClientSocket1Read(TObject *Sender,
      TCustomWinSocket *Socket)
{
        AnsiString message = Socket->ReceiveText();
        this->RecoitCoup(message);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if((Key == 32) || (Key == 13)) //si la touche ESPACE ou ENTREE est appuyé
        {
                this->ImageStart->Visible = false;
                this->EditPseudo->Visible = true;
                this->EditPasse->Visible = true;
                this->ImageUser->Visible = true;

                AfficheNotification("Veuillez vous identifier");

                //pas de connexion, lancement du jeu en pressant sur ESPACE
                this->ImageUserClick(NULL); //on lance la connexion comme s'il avait appuyé sur le bouton de validation
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ImageStartClick(TObject *Sender)
{
        this->ImageStart->Visible = false;
        this->EditPseudo->Visible = false;
        this->EditPasse->Visible = false;
        this->ImageUser->Visible = true;

        AfficheNotification("Bienvenue..");

        //pas de connexion, lancement du jeu en pressant sur ESPACE
        this->ImageUserClick(NULL); //on lance la connexion comme s'il avait appuyé sur le bouton de validation
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        this->LabelSocket->Caption = "Connecte toi";
        this->RadioGroupMode->Visible = false;

        JeuStart = 0;

        PostMessage(FindWindow("Shell_TrayWnd", NULL), WM_COMMAND, 415, 0); // réduit toutes les autres fenetres windows
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LabelCopyrightClick(TObject *Sender)
{
        if(this->ImageCredit->Visible == false)
                this->ImageCredit->Visible = true;
        else
                this->ImageCredit->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ImageCreditClick(TObject *Sender)
{
        this->ImageCredit->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ImageUserClick(TObject *Sender)
{
       /*
        ----------------------------------------------------------------------------
        créer une page web contenant les infos de la table utilisateur
        et accéder à cette page via c++ builder pour récuperer et traiter ces infos
        ----------------------------------------------------------------------------
       */
       /*
       if (!mysql_real_connect(mySQL, "127.0.0.1", "root", "", "chess8", 0, NULL, 0))
                AfficheErreur("Connexion à la base donnée échoué");

        MYSQL_RES *result;
        MYSQL_ROW elementsColonne;
        int nb_user;

        mysql_query(mySQL, "SELECT * FROM utilisateur"); // WHERE login='"+EditPseudo->Text.c_str()+"' renvois 'Invalid pointer'
        result = mysql_store_result(mySQL);
        if(result)
        {
                while(elementsColonne == mysql_fetch_row(result))
                {
                        if((strcmp(elementsColonne[4], this->EditPasse->Text.c_str()) == 0)
                        && (strcmp(elementsColonne[3], this->EditPseudo->Text.c_str()) == 0))  //si le login et mdp correspondent aux Edit
                        {
                                pseudo = elementsColonne[3];
                                nom = elementsColonne[1];
                                prenom = elementsColonne[2];

                                this->LabelNom->Caption = elementsColonne[1];
                                this->EditPseudo->Visible = false;
                                this->LabelNom->Visible = true;

                                this->LabelPrenom->Caption = elementsColonne[2];
                                this->EditPasse->Visible = false;
                                this->LabelPrenom->Visible = true;
                                this->ImageUser->Picture->LoadFromFile("assets/user.bmp");

                                this->LabelSocket->Caption = "Choisis un mode de jeu";
                                AfficheNotification("Bienvenue "+nom+" "+prenom+" !");
                                this->ImageErreurClick(NULL);
                                this->RadioGroupMode->Visible = true;

                                break; //on stop sinon la boucle continuera a chercher des utilisateurs
                        }
                        else
                        {
                                AfficheErreur("Login/Mot de passe incorrect");
                                break; //on stop sinon la boucle continuera a chercher des utilisateurs
                        }
                }
        } mysql_free_result(result); //on libere la mémoire pour pas avoir un echec de connexion à la base de donnée
        */

         /*
        if((strcmp("test", this->EditPasse->Text.c_str()) == 0)
           && (strcmp("test", this->EditPseudo->Text.c_str()) == 0))
           {  */

           if(!JeuStart) //si le jeu n'a pas deja commencé
           {
           pseudo = "test";
           nom = "NGUYEN";
           prenom = "Ismail";

           this->LabelSocket->Caption = " ";

           JeuStart = 1;

           this->LabelNom->Caption = nom;
           this->EditPseudo->Visible = false;
           this->LabelNom->Visible = true;

           this->LabelPrenom->Caption = prenom;
           this->EditPasse->Visible = false;
           this->LabelPrenom->Visible = true;
           this->ImageUser->Picture->LoadFromFile("assets/user.bmp");

           this->LabelSocket->Caption = "Choisis un mode de jeu";
           AfficheNotification("Bienvenue "+nom+" "+prenom+" !");
           this->ImageErreurClick(NULL);
           this->RadioGroupMode->Visible = true;
           }

          /* }
           else
           {
           AfficheErreur("Login/Mot de passe incorrect");
           }   */
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditPseudoChange(TObject *Sender)
{
        this->EditPseudo->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ImageNotificationClick(TObject *Sender)
{
        this->ImageNotification->Visible = false; //cache la notification en bas à droite
        this->LabelNotification->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LabelNotificationClick(TObject *Sender)
{
        ImageNotificationClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditPasseChange(TObject *Sender)
{
        this->EditPasse->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditPasseKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 13) //si la touche Entrée est appuyée
                this->ImageUserClick(NULL); //on lance la connexion comme s'il avait appuyé sur le bouton de validation
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditPseudoKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 13) //si la touche Entrée est appuyée
                this->ImageUserClick(NULL); //on lance la connexion comme s'il avait appuyé sur le bouton de validation
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditIPKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 13) //si la touche Entrée est appuyée
                SpeedButtonParametrageClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditPortServeurKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 13) //si la touche Entrée est appuyée
                SpeedButtonParametrageClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EditPortKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 13) //si la touche Entrée est appuyée
                SpeedButtonParametrageClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ImageErreurClick(TObject *Sender)
{
        this->ImageErreur->Visible = false; //cache la notification d'erreur en haut au milieu
        this->LabelErreur->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LabelErreurClick(TObject *Sender)
{
        ImageErreurClick(NULL);
}
//---------------------------------------------------------------------------
void TForm1::AfficheErreur(AnsiString msg)
{
        this->ImageErreur->Visible = true; //afficher l'erreur en haut au milieu
        this->LabelErreur->Visible = true;
        this->LabelErreur->Caption = msg;
}
//---------------------------------------------------------------------------
void TForm1::AfficheNotification(AnsiString msg)
{
        this->ImageNotification->Visible = true; //affiche la notification en bas à droite
        this->LabelNotification->Visible = true;
        this->LabelNotification->Caption = msg;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::JokerBlancClick(TObject *Sender)
{
        MonEchiquier.Joker('b');
        ChargeFormEchiquier(MonEchiquier);
        ChangeTrait();
        demicoupsaffiche++;
        MaPartie.SauvegardeEchiquier(MonEchiquier);
        Button1Click(NULL);
        EnvoiCoup();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::JokerNoirClick(TObject *Sender)
{
        MonEchiquier.Joker('n');
        ChargeFormEchiquier(MonEchiquier);
        ChangeTrait();
        demicoupsaffiche++;
        MaPartie.SauvegardeEchiquier(MonEchiquier);
        Button1Click(NULL);
        EnvoiCoup();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerStartTimer(TObject *Sender)
{
        if(!TimerFini)
        {
                //this->JeuStart = 0;
                this->TimerFini = 1;
                ImageStartClick(NULL);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LogoPlusMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        if((X-LogoPlus->Width/2+LogoPlus->Left-BevelLogo->Left>=0)
        &&(X-LogoPlus->Width/2+LogoPlus->Left-BevelLogo->Left<=BevelLogo->Width-LogoPlus->Width))
                LogoPlus->Left = +X-LogoPlus->Width/2+LogoPlus->Left;

        if((Y-LogoPlus->Height/2+LogoPlus->Top-BevelLogo->Top>=0)
        &&(Y-LogoPlus->Height/2+LogoPlus->Top-BevelLogo->Top<=BevelLogo->Height-LogoPlus->Height))
                LogoPlus->Top = +Y-LogoPlus->Height/2+LogoPlus->Top;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerSocketWebClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        this->LabelSocket->Caption = "Un spectateur vient de se connecter ("+Socket->RemoteAddress+")";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerSocketWebClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        int lg;
        AnsiString message, page, httpOK, httpOKetLg, monImage;

        message = Socket->ReceiveText();
        //this->LabelSocket->Caption = Socket->RemoteAddress+" dit: "+message;

        page = "<html><head>\n";
        page += "<title>Chess 8</title>\n";
        page += "<script type=\"text/JavaScript\">\n";
        page += "<!--\n";
        page += "function timedRefresh(timeoutPeriod) {\n";
        page += "setTimeout(\"location.reload(true);\",timeoutPeriod);\n";
        page += "}\n";
        page += "//   -->\n";
        page += "</script>\n";
        page += "<style>\ntable {\n";
        page += "border: medium solid #00c8ff;border-collapse: collapse;}\n";
        page += "td {font-family: sans-serif;border: thin solid #00c8ff;width: 50;\n";
        page += "padding: 5px;text-align: center;background-color: rgb(28, 175, 230); }\n";
        page += "</style>\n</head>\n";
        page += "<body onload=\"JavaScript:timedRefresh(2000);\">\n<div align='center'>\n";
        page += "<noscript>";
        page += "<img src='/r.bmp' onclick='javascript:location.reload();'><br><br>\n";
        page += "</noscript>";
        page += "<table>\n";

        for(int i=0; i<8; i++)
        {
                page += "<tr>\n";
                for(int j=0; j<8; j++)
                {
                        page += "<td>\n";

                        if(MonEchiquier.LitTabEchiquier(i, j) == 't')
                                page += "<img src='/t2.bmp'>\n";
                        else if(MonEchiquier.LitTabEchiquier(i, j) == 'f')
                                page += "<img src='/f2.bmp'>\n";
                        else if(MonEchiquier.LitTabEchiquier(i, j) == 'c')
                                page += "<img src='/c2.bmp'>\n";
                        else if(MonEchiquier.LitTabEchiquier(i, j) == 'd')
                                page += "<img src='/d2.bmp'>\n";
                        else if(MonEchiquier.LitTabEchiquier(i, j) == 'r')
                                page += "<img src='/r2.bmp'>\n";
                        else if(MonEchiquier.LitTabEchiquier(i, j) == 'p')
                                page += "<img src='/p2.bmp'>\n";
                        else if(MonEchiquier.LitTabEchiquier(i, j) == 'T')
                                page += "<img src='/t1.bmp'>\n";
                        else if(MonEchiquier.LitTabEchiquier(i, j) == 'F')
                                page += "<img src='/f1.bmp'>\n";
                        else if(MonEchiquier.LitTabEchiquier(i, j) == 'C')
                                page += "<img src='/c1.bmp'>\n";
                        else if(MonEchiquier.LitTabEchiquier(i, j) == 'D')
                                page += "<img src='/d1.bmp'>\n";
                        else if(MonEchiquier.LitTabEchiquier(i, j) == 'R')
                                page += "<img src='/r1.bmp'>\n";
                        else if(MonEchiquier.LitTabEchiquier(i, j) == 'P')
                                page += "<img src='/p1.bmp'>\n";
                        else
                                page += "<img src='/vide.bmp'>\n";

                        page += "</td>\n";

                }
                page += "</tr>\n";
        }
         
        page += "</table>\n</div>\n</body>\n</html>\n";

        lg = page.Length();

        httpOK = "HTTP/1.1 200 OK\r\nDate: unedate\r\nServer: unServeur\r\nX-Powered-By: UnRad\r\nContent-Length: ";
        httpOKetLg = httpOK + (AnsiString) lg + "\r\nKeep-Alive: timeout=5, max=100\r\nConnection: Keep-Alive\r\nContent-Type: text/html\r\n\r\n";

        if(message.Pos("GET / HTTP") != 0)
        {
                Socket->SendText(httpOKetLg+page); //envoi de la page
        }
        else
        {
                int pos = message.Pos(".bmp");
                AnsiString nomFichier = "assets/piece/"+message.SubString(6, pos-2);
                char entete[50000];
                int i=0, j, finentete;
                ifstream fichier;
                unsigned char octetimg[50000];
                fichier.open(nomFichier.c_str(), fstream::binary);
                while(!fichier.eof()) octetimg[i++] = fichier.get();
                lg = i-1;
                fichier.close();

                httpOKetLg = httpOK + (AnsiString) lg + "\r\nKeep-Alive: timeout=5, max=100\r\nConnection: Keep-Alive\r\nContent-Type: image/jpg\r\n\r\n";
                strcpy(entete, httpOKetLg.c_str());
                finentete = strlen(entete);
                for(j=0; j<lg; j++) entete[finentete+j] = octetimg[j];
                Socket->SendBuf(entete, finentete+lg);

        }
}
//---------------------------------------------------------------------------
