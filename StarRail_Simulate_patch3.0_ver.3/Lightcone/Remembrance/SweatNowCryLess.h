
#ifndef SweatNowCryLess_H
#define SweatNowCryLess_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Remembrance_Lightcone{
    void SweatNowCryLess(Ally *ptr);
    void SweatNowCryLess(Ally *ptr){
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),1058,529,198);
        ptr->Light_cone.Name = "SweatNowCryLess";

        ptr->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"] +=20;
                
        };
        ptr->Light_cone.Before_turn_func = [](Ally *ptr){

            if(!Buff_check(ptr->Sub_Unit_ptr[0].get(),"SweatNowCryLess")&&ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed>-1){
                Buff_single_with_all_memo(ptr,"Dmg%","None","None",36);
                ptr->Sub_Unit_ptr[0]->Buff_check["SweatNowCryLess"]=1;
            }
            
        };
    }
    
}
#endif