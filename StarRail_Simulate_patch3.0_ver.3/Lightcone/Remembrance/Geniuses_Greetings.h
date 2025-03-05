
#ifndef Geniuses_Greetings_H
#define Geniuses_Greetings_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Remembrance_Lightcone{
    void Geniuses_Greetings(Ally *ptr);
    void Geniuses_Greetings(Ally *ptr){
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),953,476,331);
        ptr->Light_cone.Name = "Geniuses_Greetings";

        ptr->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["ATK%"]["None"] +=32;
                
        };
        ptr->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Ultimate"){
                Buff_single_with_all_memo_each(ptr,"Dmg%","Basic_Attack","None",40,"Geniuses_Greetings");
                Extend_Buff_single_with_all_memo(ptr,"Geniuses_Greetings",3);
            }
            
        };
        ptr->Light_cone.Buff_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Ultimate"){
                Buff_single_with_all_memo_each(ptr,"Dmg%","Basic_Attack","None",40,"Geniuses_Greetings");
                Extend_Buff_single_with_all_memo(ptr,"Geniuses_Greetings",3);
            }
        };
        ptr->Light_cone.After_turn_func = [](Ally *ptr){

            Sub_Unit *tempstats = dynamic_cast<Sub_Unit*>(turn->ptr_to_unit);
            if(!tempstats)return;
            if(Buff_end(tempstats,"Geniuses_Greetings")){
                tempstats->Stats_type["Dmg%"]["Basic_Attack"]-=40;
                tempstats->Buff_check["Geniuses_Greetings"]=0;
            }
        };
    }
    
}
#endif