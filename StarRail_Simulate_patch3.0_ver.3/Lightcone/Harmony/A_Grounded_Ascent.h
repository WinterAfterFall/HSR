
#ifndef A_Grounded_Ascent_H
#define A_Grounded_Ascent_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Harmony_Lightcone{
    void A_Grounded_Ascent(Ally *ptr);
    void A_Grounded_Ascent(Ally *ptr){
        
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),1164,476,529);
        ptr->Light_cone.Name = "A_Grounded_Ascent";
        ptr->Light_cone.Buff_func = [](Ally *ptr,Combat_data &data_){
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Target_Type == "Single_target"){
                Increase_energy(ptr,6);
                for(auto e:data_.Target_Buff){
                    Stack_Buff_single_target(e,"Dmg%","None","None",15,1,3,"Hymn");
                    Extend_Buff_single_target(e,"Hymn",3);
                }
                ++ptr->Sub_Unit_ptr[0]->Stack["Hymn_cnt"];
                if(ptr->Sub_Unit_ptr[0]->Stack["Hymn_cnt"]==2){
                    Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
                    ptr->Sub_Unit_ptr[0]->Stack["Hymn_cnt"] = 0;
                }
            }
        };
        ptr->Light_cone.After_turn_func = [](Ally *ptr){
        if(turn->Unit_num!=ptr->Sub_Unit_ptr[0]->Target_num)return;
        Sub_Unit *tempstats = dynamic_cast<Sub_Unit*>(turn->ptr_to_unit);
        if(!tempstats)return;
            if(Buff_end(tempstats,"Hymn")){
                Buff_single_target(tempstats,"Dmg%","None","None",-(tempstats->Stack["Hymn"]*15));
                tempstats->Stack["Hymn"]=0;
            }
        };
    }
}
#endif