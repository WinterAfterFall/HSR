
#ifndef Izumo_H
#define Izumo_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Planar{
    void Izumo(Ally *ptr);
    void Izumo(Ally *ptr){
        
        ptr->Planar.Name = "Izumo";
        ptr->Planar.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=12;
        };
        ptr->Planar.When_Combat_func = [](Ally *ptr){

            for(int i=1;i<=Total_ally;i++){
                if(ptr->Sub_Unit_ptr[0]->Atv_stats->Char_Name==Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Char_Name)continue;
                for(auto e1:Ally_unit[i]->Path){
                    for(auto e2:ptr->Path){
                        if(e2==e1){
                            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=12;
                            return;
                        }
                    }
                }
            }
        };
        
       
    }
}
#endif