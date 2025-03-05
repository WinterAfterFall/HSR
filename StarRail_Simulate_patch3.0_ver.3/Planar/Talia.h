
#ifndef Talia_H
#define Talia_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Planar{
    void Talia(Ally *ptr);
    void Talia(Ally *ptr){
        
        ptr->Planar.Name = "Talia";
        ptr->Planar.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"] += 16;
        };
        ptr->Planar.When_Combat_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"] += 20;
        };
        
       
    }
}
#endif