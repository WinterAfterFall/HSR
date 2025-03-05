
#ifndef Battle_Isnt_Over_H
#define Battle_Isnt_Over_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Harmony_Lightcone{
    void But_the_Battle_Isnt_Over(Ally *ptr);
    void But_the_Battle_Isnt_Over(Ally *ptr){
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),1164,529,463);
        ptr->Light_cone.Name = "But_the_Battle_Isnt_Over";

        ptr->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Energy_recharge+=10;
                
        };
        ptr->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Skill"){
                ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_buff"] =1;
            }
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Ultimate"){
                if(ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_cnt"]==0){
                ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_cnt"] = true;
                Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
                }else{
                    ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_cnt"] = false;
                }
            }
        };
        ptr->Light_cone.Buff_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Skill"){
                ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_buff"] =1;
            }
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Ultimate"){
                if(ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_cnt"]==0){
                ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_cnt"] = true;
                Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
                }else{
                    ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_cnt"] = false;
                }
            }
        };
        ptr->Light_cone.Before_turn_func = [](Ally *ptr){
            Sub_Unit *tempstats = dynamic_cast<Sub_Unit*>(turn->ptr_to_unit);
            if(!tempstats)return;
            if(ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_buff"] ==1){
                tempstats->Stats_type["Dmg%"]["None"]+=30;
                ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_buff"]=0;
                ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_buff_check"]=1;
                
            }
        };
        ptr->Light_cone.After_turn_func = [](Ally *ptr){
            Sub_Unit *tempstats = dynamic_cast<Sub_Unit*>(turn->ptr_to_unit);
            if(!tempstats)return;
            if(ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_buff_check"] ==1){
                tempstats->Stats_type["Dmg%"]["None"]-=30;
                ptr->Sub_Unit_ptr[0]->Buff_check["Battle_Isnt_Over_buff_check"]=0;
            }
        };
    }
    
}
#endif