
#ifndef DDD_H
#define DDD_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Harmony_Lightcone{
    void DDD(Ally *ptr);
    void DDD(Ally *ptr){
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),953,423,397);
        ptr->Light_cone.Name = "DDD";

        ptr->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Ultimate"){
                All_Action_forward(24);
            }
            
        };
        ptr->Light_cone.Buff_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Ultimate"){
                All_Action_forward(24);
            }
        };
    }
}
#endif