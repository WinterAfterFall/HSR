
#ifndef Lushaka_H
#define Lushaka_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Planar{
    void Lushaka(Ally *ptr);
    void Lushaka(Ally *ptr){
        
        ptr->Planar.Name="Lushaka";
        
        ptr->Planar.Reset_func = [](Ally *ptr){
            ptr->Energy_recharge += 5;
        };
        ptr->Planar.When_Combat_func = [](Ally *ptr){
            if(ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num!=1){
            Ally_unit[1]->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=12;
            }
        };
       
    }
}
#endif