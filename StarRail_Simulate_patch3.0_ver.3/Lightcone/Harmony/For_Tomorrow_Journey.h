
#ifndef For_Tomorrow_Journey_H
#define For_Tomorrow_Journey_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Harmony_Lightcone{
    void For_Tomorrow_Journey(Ally *ptr);
    void For_Tomorrow_Journey(Ally *ptr){
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),953,476,331);
        ptr->Light_cone.Name = "For_Tomorrow_Journey";

        ptr->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=32;
        };
        ptr->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Ultimate"){
                
                if(ptr->Sub_Unit_ptr[0]->Buff_check["For_Tomorrow_Journey_Buff"] ==0){
                    ptr->Sub_Unit_ptr[0]->Buff_check["For_Tomorrow_Journey_Buff"] = 1;
                    ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["None"]+=30;

                }
                Extend_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"For_Tomorrow_Journey_Buff",1);
            }
            
        };
        ptr->Light_cone.Buff_func = [](Ally *ptr, Combat_data &data_){
            
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Ultimate"){
                
                if(ptr->Sub_Unit_ptr[0]->Buff_check["For_Tomorrow_Journey_Buff"] ==0){
                    ptr->Sub_Unit_ptr[0]->Buff_check["For_Tomorrow_Journey_Buff"] = 1;
                    ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["None"]+=30;

                }
                Extend_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"For_Tomorrow_Journey_Buff",1);
            }
        };
        ptr->Light_cone.After_turn_func = [](Ally *ptr){
            if(Buff_end(ptr->Sub_Unit_ptr[0].get(),"For_Tomorrow_Journey_Buff")){
                ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["None"]-=30;
                ptr->Sub_Unit_ptr[0]->Buff_check["For_Tomorrow_Journey_Buff"] = 0;
            }
        };
    }
}
#endif