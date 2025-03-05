
#ifndef FireFly_LC_H
#define FireFly_LC_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Destruction_Lightcone{
    void FireFly_LC(Ally *ptr);
    void FireFly_LC(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Base_hp += 1164;
        ptr->Sub_Unit_ptr[0]->Base_hp += 476;
        ptr->Sub_Unit_ptr[0]->Base_hp += 529;
        ptr->Light_cone.Name = "FireFly_LC";
        ptr->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]+=60;
                
        };
        ptr->Light_cone.After_attack_func = [](Ally *ptr,Combat_data &data_){
            if(data_.Attacker->Atv_stats->Unit_num!=ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num&&data_.Attacker->Atv_stats->Side!="Ally")return;
            int sz2 = data_.Damage_spilt.Adjacent.size();
            int sz3 = data_.Damage_spilt.Other.size();
            for(int i=1;i<=Total_enemy;i++){

            if(Enemy_unit[i]->Target_type=="Main"){
                if(Enemy_unit[i]->Debuff["FireFly_LC_debuff"]==0){
                    Enemy_unit[i]->Debuff["FireFly_LC_debuff"]=1;
                    Speed_Buff(Enemy_unit[i]->Atv_stats.get(),-20,0);
                    Enemy_unit[i]->Stats_type["Vul"]["Break_dmg"]+=24;
                    Enemy_unit[i]->Total_debuff++;
                }
                Extend_Debuff_single_target(Enemy_unit[i].get(),"FireFly_LC_debuff",2);
                Apply_debuff(ptr->Sub_Unit_ptr[0].get(),Enemy_unit[i].get());
            }
            
            if(0<sz2 && Enemy_unit[i]->Target_type=="Adjacent"){
                if(Enemy_unit[i]->Debuff["FireFly_LC_debuff"]==0){
                    Enemy_unit[i]->Debuff["FireFly_LC_debuff"]=1;
                    Speed_Buff(Enemy_unit[i]->Atv_stats.get(),-20,0);
                    Enemy_unit[i]->Stats_type["Vul"]["Break_dmg"]+=24;
                    Enemy_unit[i]->Total_debuff++;
                }
                Extend_Debuff_single_target(Enemy_unit[i].get(),"FireFly_LC_debuff",2);
                Apply_debuff(ptr->Sub_Unit_ptr[0].get(),Enemy_unit[i].get());
            }
            
            if(0<sz3 && Enemy_unit[i]->Target_type=="Other"){
                if(Enemy_unit[i]->Debuff["FireFly_LC_debuff"]==0){
                    Enemy_unit[i]->Debuff["FireFly_LC_debuff"]=1;
                    Speed_Buff(Enemy_unit[i]->Atv_stats.get(),-20,0);
                    Enemy_unit[i]->Stats_type["Vul"]["Break_dmg"]+=24;
                    Enemy_unit[i]->Total_debuff++;
                }
                Extend_Debuff_single_target(Enemy_unit[i].get(),"FireFly_LC_debuff",2);
                Apply_debuff(ptr->Sub_Unit_ptr[0].get(),Enemy_unit[i].get());
            }
            }
        
            
            
        };
        ptr->Light_cone.After_turn_func = [](Ally *ptr){
            if(turn!=nullptr&&turn->Side=="Enemy"){
                if(Debuff_end(Enemy_unit[turn->Unit_num].get(),"FireFly_LC_debuff")){
                    Enemy_unit[turn->Unit_num]->Debuff["FireFly_LC_debuff"]=0;
                    Speed_Buff(Enemy_unit[turn->Unit_num]->Atv_stats.get(),20,0);
                    Enemy_unit[turn->Unit_num]->Stats_type["Vul"]["Break_dmg"]-=24;
                    Enemy_unit[turn->Unit_num]->Total_debuff--;
                }
            }
        };
    }
}
#endif