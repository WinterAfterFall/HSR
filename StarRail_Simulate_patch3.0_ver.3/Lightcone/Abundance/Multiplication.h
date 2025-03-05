
#ifndef Multiplication_H
#define Multiplication_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Abundance_Lightcone{
    void Multiplication(Ally *ptr);
    void Multiplication(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Base_hp += 953;
        ptr->Sub_Unit_ptr[0]->Base_atk += 318;
        ptr->Sub_Unit_ptr[0]->Base_def += 198;
        ptr->Light_cone.Name = "Multiplication";
        ptr->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name&& data_.Action_type.second=="Basic_Attack"){
                Action_forward(turn,20);
            }
            
        };
        ptr->Light_cone.Buff_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name&& data_.Action_type.second=="Basic_Attack"){
                Action_forward(turn,20);
            }
        };
    }
}
#endif