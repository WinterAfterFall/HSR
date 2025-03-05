
#ifndef Rappa_LC_H
#define Rappa_LC_H

#include"..\..\Setup.cpp"
namespace Erudition_Lightcone{
    void Rappa_LC(Ally *ptr);
    void Rappa_LC(Ally *ptr){
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),953,582,529);
        ptr->Light_cone.Name = "Rappa_LC";
        ptr->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]+=60;

        };
        ptr->Light_cone.Start_game_func = [](Ally *ptr){
            Increase_energy(ptr,30);

        };
        ptr->Light_cone.Buff_func = [](Ally *ptr, Combat_data &data_){
            if(data_.Action_type.second=="Ultimate"){
                ptr->Sub_Unit_ptr[0]->Buff_check["Ration"]=1;
                ptr->Sub_Unit_ptr[0]->Stack["Ration"]=0;

            }

        };
        ptr->Light_cone.Before_attack_func = [](Ally *ptr, Combat_data &data_){
            if(data_.Action_type.second=="Ultimate"){
                ptr->Sub_Unit_ptr[0]->Buff_check["Ration"]=1;
                ptr->Sub_Unit_ptr[0]->Stack["Ration"]=0;
            }
        };
        ptr->Light_cone.After_attack_func = [](Ally *ptr, Combat_data &data_){
            if(data_.Action_type.second=="Basic_Attack"&&ptr->Sub_Unit_ptr[0]->Buff_check["Ration"]==1){
                ptr->Sub_Unit_ptr[0]->Stack["Ration"]++;
                if(ptr->Sub_Unit_ptr[0]->Stack["Ration"]==2){
                    Action_forward(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),50);
                    ptr->Sub_Unit_ptr[0]->Buff_check["Ration"]=0;
                }
            }
        };
        
        
    }
}
#endif