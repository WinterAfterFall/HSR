
#ifndef Kalpagni_Lantern_H
#define Kalpagni_Lantern_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Planar{
    void Kalpagni_Lantern(Ally *ptr);
    void Kalpagni_Lantern(Ally *ptr){
        
        ptr->Planar.Name="Kalpagni_Lantern";
        ptr->Planar.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"] += 40;
        };
       
    }
}
#endif