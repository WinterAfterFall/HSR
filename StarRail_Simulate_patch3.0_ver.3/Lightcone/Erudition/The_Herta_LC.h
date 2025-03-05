
#ifndef The_Herta_LC_H
#define The_Herta_LC_H

#include"..\..\Setup.cpp"
namespace Erudition_Lightcone{
    void The_Herta_LC(Ally *ptr);
    void The_Herta_LC(Ally *ptr){
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),953,635,463);
        ptr->Light_cone.Name = "The_Herta_LC";
        ptr->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=12;

        };
        ptr->Light_cone.Buff_func = [](Ally *ptr, Combat_data &data_){
            if(data_.Action_type.second=="Ultimate"&&data_.Attacker->Atv_stats->Unit_Name==ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name){
                if(!Buff_check(ptr->Sub_Unit_ptr[0].get(),"The_Herta_LC_buff")){
                    ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Skill"]+=60;
                    ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Ultimate"]+=60;
                    ptr->Sub_Unit_ptr[0]->Buff_check["The_Herta_LC_buff"] = 1;
                }
                Extend_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"The_Herta_LC_buff",3);
                if(ptr->Ult_cost>=140){
                    Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
                }
                

            }

        };
        ptr->Light_cone.Before_attack_func = [](Ally *ptr, Combat_data &data_){
            if(data_.Action_type.second=="Ultimate"&&data_.Attacker->Atv_stats->Unit_Name==ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name){
                if(!Buff_check(ptr->Sub_Unit_ptr[0].get(),"The_Herta_LC_buff")){
                    ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Skill"]+=60;
                    ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Ultimate"]+=60;
                    ptr->Sub_Unit_ptr[0]->Buff_check["The_Herta_LC_buff"] = 1;
                }
                Extend_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"The_Herta_LC_buff",3);
                if(ptr->Ult_cost>=140){
                    Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
                }
                

            }
        };
        ptr->Light_cone.After_turn_func = [](Ally *ptr){
            if(Buff_end(ptr->Sub_Unit_ptr[0].get(),"The_Herta_LC_buff")){
                ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Skill"]-=60;
                ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Ultimate"]-=60;
                ptr->Sub_Unit_ptr[0]->Buff_check["The_Herta_LC_buff"] = 0;
            }
        };
        
        
    }
}
#endif