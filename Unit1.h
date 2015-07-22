#ifndef Unit1H
#define Unit1H
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include "echiquier.h"
#include "joueur.h"
#include "partie.h"
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ScktComp.hpp>
#include <MPlayer.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// Composants gérés par l'EDI
        TImage *Image1;
        TImage *Image2;
        TImage *Image3;
        TImage *Image4;
        TImage *Image5;
        TImage *Image6;
        TImage *Image7;
        TImage *Image8;
        TImage *Image9;
        TImage *Image10;
        TImage *Image11;
        TImage *Image12;
        TImage *Image13;
        TImage *Image14;
        TImage *Image15;
        TImage *Image16;
        TImage *Image17;
        TImage *Image18;
        TImage *Image19;
        TImage *Image20;
        TImage *Image21;
        TImage *Image22;
        TImage *Image23;
        TImage *Image24;
        TImage *Image25;
        TImage *Image26;
        TImage *Image27;
        TImage *Image28;
        TImage *Image29;
        TImage *Image30;
        TImage *Image31;
        TImage *Image32;
        TImage *Image33;
        TImage *Image34;
        TImage *Image35;
        TImage *Image36;
        TImage *Image37;
        TImage *Image38;
        TImage *Image39;
        TImage *Image40;
        TImage *Image41;
        TImage *Image42;
        TImage *Image43;
        TImage *Image44;
        TImage *Image45;
        TImage *Image46;
        TImage *Image47;
        TImage *Image48;
        TImage *Image49;
        TImage *Image50;
        TImage *Image51;
        TImage *Image52;
        TImage *Image53;
        TImage *Image54;
        TImage *Image55;
        TImage *Image56;
        TImage *Image57;
        TImage *Image58;
        TImage *Image59;
        TImage *Image60;
        TImage *Image61;
        TImage *Image62;
        TImage *Image63;
        TImage *Image64;
        TImage *ImageEchiquier;
        TRichEdit *RichEdit1;
        TImage *ImageRetour;
        TImage *TraitNoir;
        TImage *TraitBlanc;
        TImage *VisuRichEdit;
        TImage *ImageFond;
        TShape *Shape1;
        TImage *fondMode;
        TRadioGroup *RadioGroupMode;
        TGroupBox *GroupBoxParametrage;
        TEdit *EditIP;
        TEdit *EditPort;
        TEdit *EditPortServeur;
        TClientSocket *ClientSocket1;
        TServerSocket *ServerSocket1;
        TLabel *LabelCopyright;
        TLabel *LabelSocket;
        TRadioGroup *RadioGroupCouleur;
        TImage *ImageParametrageOk;
        TImage *ImageFondPromotion;
        TImage *PromotionFou;
        TImage *ImageCredit;
        TImage *PromotionTour;
        TImage *PromotionCavalier;
        TImage *PromotionDame;
        TImage *ImageStart;
        TImage *ImageUser;
        TLabel *LabelNom;
        TEdit *EditPseudo;
        TMediaPlayer *Media;
        TImage *ImageNotification;
        TLabel *LabelNotification;
        TEdit *EditPasse;
        TLabel *LabelPrenom;
        TImage *ImageErreur;
        TLabel *LabelErreur;
        TImage *JokerBlanc;
        TTimer *TimerStart;
        TImage *JokerNoir;
        TBevel *BevelLogo;
        TImage *LogoPlus;
        TServerSocket *ServerSocketWeb;
        void __fastcall arriveCase(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept);
        void __fastcall quitteCase(TObject *Sender, TObject *Source, int X,
          int Y);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button1Click2(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Radio1Click(TObject *Sender);
        void __fastcall Radio2Click(TObject *Sender);
        void __fastcall Radio3Click(TObject *Sender);
        void __fastcall Radio4Click(TObject *Sender);
        void __fastcall RadioGroupModeClick(TObject *Sender);
        void __fastcall EditPortChange(TObject *Sender);
        void __fastcall EditIPChange(TObject *Sender);
        void __fastcall EditPortServeurChange(TObject *Sender);
        void __fastcall SpeedButtonParametrageClick(TObject *Sender);
        void __fastcall ServerSocket1ClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Connecting(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ServerSocket1ClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ServerSocket1ClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Read(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall LabelCopyrightClick(TObject *Sender);
        void __fastcall ImageCreditClick(TObject *Sender);
        void __fastcall ImageUserClick(TObject *Sender);
        void __fastcall EditPseudoChange(TObject *Sender);
        void __fastcall ImageNotificationClick(TObject *Sender);
        void __fastcall EditPasseChange(TObject *Sender);
        void __fastcall EditPasseKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall EditPseudoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall EditIPKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall EditPortServeurKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall EditPortKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall ImageErreurClick(TObject *Sender);
        void __fastcall JokerBlancClick(TObject *Sender);
        void __fastcall ImageStartClick(TObject *Sender);
        void __fastcall TimerStartTimer(TObject *Sender);
        void __fastcall LabelNotificationClick(TObject *Sender);
        void __fastcall LabelErreurClick(TObject *Sender);
        void __fastcall JokerNoirClick(TObject *Sender);
        void __fastcall LogoPlusMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall ServerSocketWebClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ServerSocketWebClientRead(TObject *Sender,
          TCustomWinSocket *Socket);

private:	// Déclarations de l'utilisateur
        TImage * lacase[8][8];
        Echiquier MonEchiquier;
        Echiquier EchPrecedent;
        Joueur JBlanc, JNoir;
        Partie MaPartie;
        int demicoupsaffiche, mode;
        bool CouleurClient, JeuInterdit, JeuStart, TimerFini;
        AnsiString pseudo, nom, prenom;

public:		// Déclarations de l'utilisateur
        __fastcall TForm1(TComponent* Owner);
        void ChargeFormEchiquier(Echiquier UnEchiquier);
        void EffaceFormEchiquier();
        void ChangeTrait();
        void EnvoiCoup();
        void RecoitCoup(AnsiString TexteRecu);
        void AfficheErreur(AnsiString msg);
        void AfficheNotification(AnsiString msg);
        TCustomWinSocket *MonClientSocket;

        //méthode d'accès
        inline void InitFormEchiquier(){
                MonEchiquier.InitEchiquier();
                ChargeFormEchiquier(MonEchiquier);}
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 