#pragma hdrstop
#include "deplacement.h"
#include "echiquier.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
Deplacement::Deplacement()
{
        this->ColonneDepart = -1;
        this->LigneDepart = -1;
        this->NbPositionArrivee = 0;

        for(int i=0; i<=1; i++)
                for(int j=0; j<=62; j++)
                        this->TabPositionArrivee[i][j] = -1;

}
//---------------------------------------------------------------------------
/*int Deplacement::LitColonneArrivee(int NumPosition)
{

}*/
//---------------------------------------------------------------------------
/*int Deplacement::LitLigneArrivee(int NumPosition)
{

}*/
//---------------------------------------------------------------------------
int Deplacement::LitNbPositionArrivee()
{
        int NbPositionArrivee;

        NbPositionArrivee = LitLigneArrivee(TabPositionArrivee[0][NbPositionArrivee]) + LitColonneArrivee(TabPositionArrivee[1][NbPositionArrivee]);

        return NbPositionArrivee;
}
//---------------------------------------------------------------------------
bool Deplacement::ValidePositionArrivee(int iarr, int jarr)
{
        for(int col=0; col<NbPositionArrivee; col++)
                if((TabPositionArrivee[0][col] == iarr) && (TabPositionArrivee[1][col] == jarr))
                        return true;

        return false;
}
//---------------------------------------------------------------------------
DeplacePion::DeplacePion()
{

}
//---------------------------------------------------------------------------
void DeplacePion::CalculPositionArrivee(int idep, int jdep, Echiquier *PE)
{
        NbPositionArrivee = 0;

        if(PE->EstUnePieceNoire(idep, jdep))
        {
                if(PE->EstVide(idep+1, jdep))
                {
                        TabPositionArrivee[0][NbPositionArrivee] = idep+1;
                        TabPositionArrivee[1][NbPositionArrivee++] = jdep;
                }
                if( PE->EstVide(idep+1, jdep) && PE->EstVide(idep+2, jdep) && (idep == 1))
                {
                        TabPositionArrivee[0][NbPositionArrivee] = idep+2;
                        TabPositionArrivee[1][NbPositionArrivee++] = jdep;
                }
                if(PE->EstUnePieceBlanche(idep+1, jdep-1))
                {
                        TabPositionArrivee[0][NbPositionArrivee] = idep+1;
                        TabPositionArrivee[1][NbPositionArrivee++] = jdep-1;
                }
                if(PE->EstUnePieceBlanche(idep+1, jdep+1))
                {
                        TabPositionArrivee[0][NbPositionArrivee] = idep+1;
                        TabPositionArrivee[1][NbPositionArrivee++] = jdep+1;
                }
                if((PE->LitTabEchiquier(idep, jdep+1) == 'P') && (idep == 4))
                {
                        TabPositionArrivee[0][NbPositionArrivee] = idep+1;
                        TabPositionArrivee[1][NbPositionArrivee++] = jdep+1;
                }
                if((PE->LitTabEchiquier(idep, jdep-1) == 'P') && (idep == 4))
                {
                        TabPositionArrivee[0][NbPositionArrivee] = idep+1;
                        TabPositionArrivee[1][NbPositionArrivee++] = jdep-1;
                }
        }
        else if(PE->EstUnePieceBlanche(idep, jdep))
        {
                if(PE->EstVide(idep-1, jdep))
                {
                        TabPositionArrivee[0][NbPositionArrivee] = idep-1;
                        TabPositionArrivee[1][NbPositionArrivee++] = jdep;
                }
                if(PE->EstVide(idep-1, jdep) && PE->EstVide(idep-2, jdep) && (idep == 6))
                {
                        TabPositionArrivee[0][NbPositionArrivee] = idep-2;
                        TabPositionArrivee[1][NbPositionArrivee++] = jdep;
                }
                if(PE->EstUnePieceNoire(idep-1, jdep-1))
                {
                        TabPositionArrivee[0][NbPositionArrivee] = idep-1;
                        TabPositionArrivee[1][NbPositionArrivee++] = jdep-1;
                }
                if(PE->EstUnePieceNoire(idep-1, jdep+1))
                {
                        TabPositionArrivee[0][NbPositionArrivee] = idep-1;
                        TabPositionArrivee[1][NbPositionArrivee++] = jdep+1;
                }
                if((PE->LitTabEchiquier(idep, jdep+1) == 'p') && (idep == 3))
                {
                        TabPositionArrivee[0][NbPositionArrivee] = idep-1;
                        TabPositionArrivee[1][NbPositionArrivee++] = jdep+1;
                }
                if((PE->LitTabEchiquier(idep, jdep-1) == 'p') && (idep == 3))
                {
                        TabPositionArrivee[0][NbPositionArrivee] = idep-1;
                        TabPositionArrivee[1][NbPositionArrivee++] = jdep-1;
                }
        }
}
//---------------------------------------------------------------------------
DeplaceCavalier::DeplaceCavalier()
{

}
//---------------------------------------------------------------------------
void DeplaceCavalier::CalculPositionArrivee(int idep, int jdep, Echiquier *PE)
{
        NbPositionArrivee = 0;
        int dep[8][2] = {{2,1},{1,2},{2,-1},{1,-2},{-2,1},{-1,2},{-2,-1},{-1,-2}};
        int itest, jtest;
        for(int i=0 ; i<8 ; i++)
        {
                itest = idep+dep[i][0];
                jtest = jdep+dep[i][1];
                
                if( (itest>=0) && (itest<=7) && (jtest>=0) && (jtest<=7) &&
                     (PE->EstVide(itest, jtest) ||
                      (PE->EstUnePieceBlanche(idep,jdep) && PE->EstUnePieceNoire(itest, jtest)) ||
                      (PE->EstUnePieceNoire(idep,jdep) && PE->EstUnePieceBlanche(itest, jtest))
                      ) )
                {
                                        TabPositionArrivee[0][NbPositionArrivee] = itest;
                                        TabPositionArrivee[1][NbPositionArrivee++] = jtest;
                }
        }
}
//---------------------------------------------------------------------------
DeplaceFou::DeplaceFou()
{

}
//---------------------------------------------------------------------------
void DeplaceFou::CalculPositionArrivee(int idep, int jdep, Echiquier *PE)
{
        NbPositionArrivee = 0;
        int dep[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
        int itest, jtest;
        bool fin;
        for(int i=0 ; i<4 ; i++)
        {
                fin = false;
                itest = idep+dep[i][0];
                jtest = jdep+dep[i][1];
                do{

                        if(PE->EstVide(itest,jtest) && (itest>=0) && (itest<=7) && (jtest>=0) && (jtest<=7))
                        {
                                TabPositionArrivee[0][NbPositionArrivee] = itest;
                                TabPositionArrivee[1][NbPositionArrivee++] = jtest;
                        }
                        else
                        {
                                if( (PE->EstUnePieceBlanche(idep, jdep) && PE->EstUnePieceNoire(itest,jtest)) ||
                                 (PE->EstUnePieceNoire(idep, jdep) && PE->EstUnePieceBlanche(itest,jtest)) )
                                {
                                        TabPositionArrivee[0][NbPositionArrivee] = itest;
                                        TabPositionArrivee[1][NbPositionArrivee++] = jtest;
                                }
                                fin = true;
                        }
                        itest += dep[i][0];
                        jtest += dep[i][1];
                }while(!fin);
        }
}
//---------------------------------------------------------------------------
DeplaceTour::DeplaceTour()
{

}
//---------------------------------------------------------------------------
void DeplaceTour::CalculPositionArrivee(int idep, int jdep, Echiquier *PE)
{
        NbPositionArrivee = 0;
        int dep[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        int itest, jtest;
        bool fin;
        for(int i=0 ; i<4 ; i++)
        {
                fin = false;
                itest = idep+dep[i][0];
                jtest = jdep+dep[i][1];
                do{

                        if(PE->EstVide(itest,jtest) && (itest>=0) && (itest<=7) && (jtest>=0) && (jtest<=7))
                        {
                                TabPositionArrivee[0][NbPositionArrivee] = itest;
                                TabPositionArrivee[1][NbPositionArrivee++] = jtest;
                        }
                        else
                        {
                                if( (PE->EstUnePieceBlanche(idep, jdep) && PE->EstUnePieceNoire(itest,jtest)) ||
                                 (PE->EstUnePieceNoire(idep, jdep) && PE->EstUnePieceBlanche(itest,jtest)) )
                                {
                                        TabPositionArrivee[0][NbPositionArrivee] = itest;
                                        TabPositionArrivee[1][NbPositionArrivee++] = jtest;
                                }
                                fin = true;
                        }
                        itest += dep[i][0];
                        jtest += dep[i][1];
                }while(!fin);
        }
}
//---------------------------------------------------------------------------
DeplaceDame::DeplaceDame()
{

}
//---------------------------------------------------------------------------
void DeplaceDame::CalculPositionArrivee(int idep, int jdep, Echiquier *PE)
{
        NbPositionArrivee = 0;
        int dep[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
        int itest, jtest;
        bool fin;
        for(int i=0 ; i<8 ; i++)
        {
                fin = false;
                itest = idep+dep[i][0];
                jtest = jdep+dep[i][1];
                do{

                        if(PE->EstVide(itest,jtest) && (itest>=0) && (itest<=7) && (jtest>=0) && (jtest<=7))
                        {
                                TabPositionArrivee[0][NbPositionArrivee] = itest;
                                TabPositionArrivee[1][NbPositionArrivee++] = jtest;
                        }
                        else
                        {
                                if( (PE->EstUnePieceBlanche(idep, jdep) && PE->EstUnePieceNoire(itest,jtest)) ||
                                 (PE->EstUnePieceNoire(idep, jdep) && PE->EstUnePieceBlanche(itest,jtest)) )
                                {
                                        TabPositionArrivee[0][NbPositionArrivee] = itest;
                                        TabPositionArrivee[1][NbPositionArrivee++] = jtest;
                                }
                                fin = true;
                        }
                        itest += dep[i][0];
                        jtest += dep[i][1];
                }while(!fin);
        }
}
//---------------------------------------------------------------------------
DeplaceRoi::DeplaceRoi()
{

}
//---------------------------------------------------------------------------
void DeplaceRoi::CalculPositionArrivee(int idep, int jdep, Echiquier *PE)
{
        NbPositionArrivee = 0;
        int dep[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
        int itest, jtest;
        for(int i=0 ; i<8 ; i++)
        {
                itest = idep+dep[i][0];
                jtest = jdep+dep[i][1];
                
                if( (itest>=0) && (itest<=7) && (jtest>=0) && (jtest<=7) &&
                     (PE->EstVide(itest, jtest) ||
                      (PE->EstUnePieceBlanche(idep,jdep) && PE->EstUnePieceNoire(itest, jtest)) ||
                      (PE->EstUnePieceNoire(idep,jdep) && PE->EstUnePieceBlanche(itest, jtest))
                      ) )
                {
                                        TabPositionArrivee[0][NbPositionArrivee] = itest;
                                        TabPositionArrivee[1][NbPositionArrivee++] = jtest;
                }
        }

        if(PE->EstUnePieceBlanche(idep,jdep)         // grand roque blanc
                && (idep == 7)
                && (jdep == 4)
                && (PE->EstVide(idep, 1))
                && (PE->EstVide(idep, 2))
                && (PE->EstVide(idep, 3))
                && (PE->LitTabEchiquier(7, 0) == 'T')
                )
        {
                TabPositionArrivee[0][NbPositionArrivee] = 7;
                TabPositionArrivee[1][NbPositionArrivee++] = 2;
        }
        if(PE->EstUnePieceBlanche(idep,jdep)         // petit roque blanc
                && (idep == 7)
                && (jdep == 4)
                && (PE->EstVide(idep, 5))
                && (PE->EstVide(idep, 6))
                && (PE->LitTabEchiquier(7, 7) == 'T')
                )
        {
                TabPositionArrivee[0][NbPositionArrivee] = 7;
                TabPositionArrivee[1][NbPositionArrivee++] = 6;
        }

        if(PE->EstUnePieceNoire(idep,jdep)         // petit roque noir
                && (idep == 0)
                && (jdep == 4)
                && (PE->EstVide(idep, 5))
                && (PE->EstVide(idep, 6))
                && (PE->LitTabEchiquier(0, 7) == 't')
                )
        {
                TabPositionArrivee[0][NbPositionArrivee] = 0;
                TabPositionArrivee[1][NbPositionArrivee++] = 6;
        }
        if(PE->EstUnePieceNoire(idep,jdep)         // grand roque noir
                && (idep == 0)
                && (jdep == 4)
                && (PE->EstVide(idep, 1))
                && (PE->EstVide(idep, 2))
                && (PE->EstVide(idep, 3))
                && (PE->LitTabEchiquier(0, 0) == 't')
                )
        {
                TabPositionArrivee[0][NbPositionArrivee] = 0;
                TabPositionArrivee[1][NbPositionArrivee++] = 2;
        }

}
//---------------------------------------------------------------------------
