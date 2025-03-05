
#ifndef Himeko_LC_H
#define Himeko_LC_H

#include"..\..\Setup.cpp"
namespace Erudition_Lightcone{
    void Himeko_LC(Ally *ptr);
    void Himeko_LC(Ally *ptr){
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),1164,582,397);
        ptr->Light_cone.Name = "Himeko_LC";
        ptr->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=9*Total_enemy;
           
        
        };
        ptr->Light_cone.Toughness_break_func = [](Ally *ptr,Enemy *target,Sub_Unit *Breaker){
            if(!Buff_check(ptr->Sub_Unit_ptr[0].get(),"Himeko_LC_buff")){
                ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["None"]+=30;
                ptr->Sub_Unit_ptr[0]->Buff_check["Himeko_LC_buff"] = 1; 
            }
            Extend_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Himeko_LC_buff",1);
        };
        ptr->Light_cone.After_turn_func =[](Ally *ptr){
            if(Buff_end(ptr->Sub_Unit_ptr[0].get(),"Himeko_LC_buff")){
                ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["None"]-=30;
                ptr->Sub_Unit_ptr[0]->Buff_check["Himeko_LC_buff"] = 0; 
            }
        };
        
        
    }
}
#endif