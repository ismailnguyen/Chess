#ifndef joueurH
#define joueurH
//---------------------------------------------------------------------------

class Joueur
{
private:
        bool Trait;
        char Nom[100];

public:
        Joueur();

        //m�thode d'acc�s
        inline void DonneTrait(){
                Trait = 1;}
        inline void RetireTrait(){
                Trait = 0;}
        inline bool LitTrait(){
                return Trait;}
};

//---------------------------------------------------------------------------
#endif
