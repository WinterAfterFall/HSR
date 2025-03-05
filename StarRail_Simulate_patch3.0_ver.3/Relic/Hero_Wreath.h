
#ifndef Hero_Wreath_H
#define Hero_Wreath_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Relic{
    void Hero_Wreath(Ally *ptr);
    void Hero_Wreath(Ally *ptr){
        ptr->Relic.Name = "Hero_Wreath";
        ptr->Relic.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=12;
        };
        ptr->Relic.Before_turn_func = [](Ally *ptr){
            if(ptr->Sub_Unit_ptr.size()>1&&ptr->Sub_Unit_ptr[0]->Buff_check["Hero_Wreath"]==0){
                for(int i=1;i<ptr->Sub_Unit_ptr.size();i++){
                    if(ptr->Sub_Unit_ptr[i]->Atv_stats->Base_speed!=-1){
                        ptr->Sub_Unit_ptr[0]->Buff_check["Hero_Wreath"]=1;
                        Speed_Buff(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),6,0);
                        break;
                    }
                }
            }
        };
        ptr->Relic.Before_attack_func = [](Ally *ptr,Combat_data &data_){
            if(data_.Attacker->Atv_stats->Side=="Ally"&&ptr->Sub_Unit_ptr.size()>1){
                Buff_single_with_all_memo_each(ptr,"Crit_dam","None","None",30,"Hero_Wreath_buff");
            }
            Extend_Buff_single_with_all_memo(ptr,"Hero_Wreath_buff",2);
        };
        
        
    }
}
#endif