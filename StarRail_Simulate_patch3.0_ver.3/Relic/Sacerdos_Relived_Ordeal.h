
#ifndef Sacerdos_H
#define Sacerdos_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Relic{
    void Sacerdos_Relived_Ordeal(Ally *ptr);
    void Sacerdos_Relived_Ordeal(Ally *ptr){
        ptr->Relic.Name = "Sacerdos_Relived_Ordeal";
        ptr->Relic.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Atv_stats->Speed_percent+=6;

        };
        ptr->Relic.Buff_func =[](Ally *ptr, Combat_data &data_){
             if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Target_Type == "Single_target"){
                for(auto e:data_.Target_Buff){
                    Stack_Buff_single_target(e,"Crit_dam","None","None",18,1,2,"Sacerdos");
                    Extend_Buff_single_target(e,"Sacerdos",2);
                }
                }
        };
        
        ptr->Relic.After_turn_func =[](Ally *ptr){
        if(turn->Unit_num!=ptr->Sub_Unit_ptr[0]->Target_num)return;
        Sub_Unit *tempstats = dynamic_cast<Sub_Unit*>(turn->ptr_to_unit);
        if(!tempstats)return;
        if(Buff_end(tempstats,"Sacerdos")){
            Buff_single_target(tempstats,"Crit_dam","None","None",-(tempstats->Stack["Sacerdos"]*18));
            tempstats->Stack["Sacerdos"]=0;
        }
        };
    }
}
#endif