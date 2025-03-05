
#ifndef Tribbie_LC_H
#define Tribbie_LC_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Harmony_Lightcone{
    void Tribbie_LC(Ally *ptr);
    void Tribbie_LC(Ally *ptr){
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),1270,529,397);
        ptr->Light_cone.Name = "Tribbie_LC";
        ptr->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"]+=36;
            
        };
        
        ptr->Light_cone.Start_game_func = [](Ally *ptr){
            Increase_energy(ptr,21);
            ptr->Sub_Unit_ptr[0]->Buff_check["Presage"] = 1;
            Extend_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Presage",2);
            Buff_All_Ally("Crit_dam","None","None",48);
        };
        ptr->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Fua"){
                Increase_energy(ptr,12);
                if(!Buff_check(ptr->Sub_Unit_ptr[0].get(),"Presage")){
                    Buff_All_Ally("Crit_dam","None","None",48);
                    ptr->Sub_Unit_ptr[0]->Buff_check["Presage"] = 1;
                }
            }

            
        };
        ptr->Light_cone.Buff_func = [](Ally *ptr, Combat_data &data_){
            
            if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name && data_.Action_type.second=="Fua"){
                Increase_energy(ptr,12);
                if(!Buff_check(ptr->Sub_Unit_ptr[0].get(),"Presage")){
                    Buff_All_Ally("Crit_dam","None","None",48);
                    ptr->Sub_Unit_ptr[0]->Buff_check["Presage"] = 1;
                }
            }
        };
        ptr->Light_cone.After_turn_func = [](Ally *ptr){
            
            if(Buff_end(ptr->Sub_Unit_ptr[0].get(),"Presage")){
                ptr->Sub_Unit_ptr[0]->Buff_check["Presage"] = 0;
                Buff_All_Ally("Crit_dam","None","None",-48);
            }
        };
        ptr->Light_cone.Print_Func = [](Ally *ptr){
            
            cout<<endl;
            cout<<ptr->Sub_Unit_ptr[0]->Atv_stats->Char_Name<<"_LC : ";
            cout<<ptr->Sub_Unit_ptr[0]->Buff_check["Presage"]<<" ";
        };
    }
}
#endif