
#ifndef Broken_Keel_H
#define Broken_Keel_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Planar{
    void Broken_Keel(Ally *ptr);
    void Broken_Keel(Ally *ptr){
        ptr->Planar.Name="Broken_Keel";
        
        
        ptr->Planar.When_Combat_func = [](Ally *ptr){
            Buff_All_Ally("Crit_dam","None","None",10);
        };
       
    }
}
#endif