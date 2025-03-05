
#ifndef Reminiscence_H
#define Reminiscence_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Remembrance_Lightcone{
    void Reminiscence(Ally *ptr);
    void Reminiscence(Ally *ptr){
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),635,423,265);
        ptr->Light_cone.Name = "Reminiscence";

        ptr->Light_cone.Before_turn_func = [](Ally *ptr){
            for(auto &e:ptr->Sub_Unit_ptr){
                if(e->Atv_stats->Side=="Memosprite"&&e->Atv_stats->Base_speed<=0){
                    Buff_single_with_all_memo(ptr,"Dmg%","None","None",-12*e->Stack["Reminiscence"]);
                    for(auto &f:ptr->Sub_Unit_ptr){
                        f->Stack["Reminiscence"] = 0;
                    }
                    return;
                }
            }
            
            if(turn->Unit_num==ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num&&turn->Side=="Memosprite"){
                Stack_Buff_single_with_all_memo(ptr,"Dmg%","None","None",12,1,4,"Reminiscence");
            }
            
        };
    }
    
}
#endif