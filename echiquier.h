#ifndef echiquierH
#define echiquierH
#include <vcl.h>
#include "deplacement.h"
//---------------------------------------------------------------------------

class Echiquier
{
private:	// Déclarations de l'utilisateur
        char TabEchiquier[8][8];
        bool GrandRoqueNoir;
        bool PetitRoqueNoir;
        bool GrandRoqueBlanc;
        bool PetitRoqueBlanc;
        DeplacePion MonPion;
        DeplaceCavalier MonCavalier;
        DeplaceFou MonFou;
        DeplaceTour MaTour;
        DeplaceDame MaDame;
        DeplaceRoi MonRoi;
        
public:		// Déclarations de l'utilisateur
        Echiquier();
        void InitEchiquier();
        void Joker(char couleur);
        void CopieEchiquier(Echiquier EchSource);
        bool EstUnePieceNoire(int ligne, int colonne);
        bool EstUnePieceBlanche(int ligne, int colonne);
        bool EstVide(int ligne, int colonne);
        AnsiString VisuEchiquier();
        void ModifieEchiquier(char Cpiece, int ligne, int colonne);
        bool DeplacementPossible(int idep, int jdep, int iarr, int jarr);
        void EffaceEchiquier();
		bool DiagonaleLibreEntre2cases(int lignedebut, int colonnedebut, int colonnefin);
		bool RangeeLibreEntre2cases(int ligne, int colonnedebut, int colonnefin);
		bool ColonneLibreEntre2cases(int lignedebut, int colonne, int lignefin);
        bool RoiPAT(bool couleur);
        bool CaseEnEchec(int ligne, int colonne, bool couleur);
        bool RoiEnEchec(bool couleur);

        //méthode d'accès
        inline char LitTabEchiquier(int ligne, int colonne){
                return TabEchiquier[ligne][colonne];}
        inline bool GrandRoqueNoirPossible(){
                return GrandRoqueNoir;}
        inline bool PetitRoqueNoirPossible(){
                return PetitRoqueNoir;}
        inline bool GrandRoqueBlancPossible(){
                return GrandRoqueBlanc;}
        inline bool PetitRoqueBlancPossible(){
                return PetitRoqueBlanc;}
        inline void InterditGrandRoqueNoir(){
                GrandRoqueNoir = 0;}
        inline void InterditPetitRoqueNoir(){
                PetitRoqueNoir = 0;}
        inline void InterditGrandRoqueBlanc(){
                GrandRoqueBlanc = 0;}
        inline void InterditPetitRoqueBlanc(){
                PetitRoqueBlanc = 0;}
};

//---------------------------------------------------------------------------
#endif
