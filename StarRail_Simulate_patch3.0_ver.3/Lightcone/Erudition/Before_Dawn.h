
#ifndef Before_Dawn_H
#define Before_Dawn_H

#include"..\..\Setup.cpp"
namespace Erudition_Lightcone{
    void Before_Dawn(Ally *ptr);
    void Before_Dawn(Ally *ptr){
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),1058,582,463);

        ptr->Light_cone.Name = "Before_Dawn";
        ptr->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"]+=36;
            ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Skill"]+=18;
            ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Ultimate"]+=18;
        };
        ptr->Light_cone.Before_attack_func = [](Ally *ptr,Combat_data &data_){
            if(data_.Attacker->Atv_stats->Unit_Name==ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name&&ptr->Sub_Unit_ptr[0]->Stack["Somnus_Corpus"]==1){
                for(auto e:data_.Skill_Type){
                if(e =="Fua"){
                    ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Fua"]+=48;
                    break;
                }
            }
            }
        };
        ptr->Light_cone.After_attack_func = [](Ally *ptr,Combat_data &data_){
            if(data_.Attacker->Atv_stats->Unit_Name!=ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name)return;
            for(auto e:data_.Skill_Type){
                if(e =="Skill"||e =="Ultimate"){
                    ptr->Sub_Unit_ptr[0]->Stack["Somnus_Corpus"]=1;
                    break;
                }
            }
            if(data_.Attacker->Atv_stats->Unit_Name==ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name&&ptr->Sub_Unit_ptr[0]->Stack["Somnus_Corpus"]==1){
                for(auto e:data_.Skill_Type){
                if(e =="Fua"){
                    ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Fua"]-=48;
                    ptr->Sub_Unit_ptr[0]->Stack["Somnus_Corpus"]=0;
                    break;
                }
            }
            }
        };
        
    }
}
#endif