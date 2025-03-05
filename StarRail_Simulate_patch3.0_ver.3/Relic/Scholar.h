
#ifndef Scholar_H
#define Scholar_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Relic{
    void Scholar(Ally *ptr);
    void Scholar(Ally *ptr){
        ptr->Relic.Name = "Scholar";
        ptr->Relic.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=8;
            ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Ultimate"]+=20;
            ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Skill"]+=20;
        };
        ptr->Relic.Before_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Ultimate"){
                 if(!Buff_check(ptr->Sub_Unit_ptr[0].get(),"Scholar_buff")){
                    ptr->Sub_Unit_ptr[0]->Buff_check["Scholar_buff"]= 1;
                    ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Skill"]+=25;
                 }
                 
            }
            
        };
        ptr->Relic.After_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Skill"){
                 if(Buff_check(ptr->Sub_Unit_ptr[0].get(),"Scholar_buff")){
                    ptr->Sub_Unit_ptr[0]->Buff_check["Scholar_buff"]= 0;
                    ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Skill"]-=25;
                 }
                 
            }
            
        };
        ptr->Relic.Buff_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Ultimate"){
                 if(!Buff_check(ptr->Sub_Unit_ptr[0].get(),"Scholar_buff")){
                    ptr->Sub_Unit_ptr[0]->Buff_check["Scholar_buff"]= 1;
                    ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Skill"]+=25;
                 }
                 
            }
        };
        
    }
}
#endif