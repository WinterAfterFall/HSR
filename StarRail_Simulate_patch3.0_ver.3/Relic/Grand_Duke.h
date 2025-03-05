
#ifndef Grand_Duke_H
#define Grand_Duke_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Relic{
    void Grand_Duke(Ally *ptr);
    void Grand_Duke(Ally *ptr){
        ptr->Relic.Name = "Grand_Duke";
        ptr->Relic.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Fua"]+=20;
            

        };
        ptr->Relic.Hit_func = [](Ally *ptr,Combat_data &data_,int Hit_cnt,int Total_Hit_cnt){
            bool check=0;
            if(data_.Attacker->Atv_stats->Unit_Name!=ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name)return;
            for(auto e:data_.Skill_Type){
                if(e == "Fua")check=1;
            }
            if(check==1){

            if(Hit_cnt>8){
                Hit_cnt = 8;
            }
            data_.Attacker->Stats_type["Atk%"]["None"] -= data_.Attacker->Stack["Grand_Duke"]*6;
            data_.Attacker->Stack["Grand_Duke"] = Hit_cnt;
            data_.Attacker->Stats_type["Atk%"]["None"] += data_.Attacker->Stack["Grand_Duke"]*6;
            Extend_Buff_single_target(data_.Attacker,"Grand_Duke",3);
            }
            
        };
        ptr->Relic.After_turn_func = [](Ally *ptr){
        if(turn->Char_Name!=ptr->Sub_Unit_ptr[0]->Atv_stats->Char_Name)return;
        if(Buff_end(ptr->Sub_Unit_ptr[0].get(),"Grand_Duke")){
            ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"] -= ptr->Sub_Unit_ptr[0]->Stack["Grand_Duke"]*6;
            ptr->Sub_Unit_ptr[0]->Stack["Grand_Duke"] = 0;
        }
        };
        
    }
}
#endif