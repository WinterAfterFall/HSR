
#ifndef Rutilant_H
#define Rutilant_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Planar{
    void Rutilant(Ally *ptr);
    void Rutilant(Ally *ptr){
        
        ptr->Planar.Name = "Rutilant";
        ptr->Planar.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=8;;



        };
        ptr->Planar.When_Combat_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Skill"]+=20;
            ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Basic_Attack"]+=20;



        };
        
       
    }
}
#endif