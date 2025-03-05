
#ifndef The_Day_The_Cosmos_Fell_H
#define The_Day_The_Cosmos_Fell_H

#include"..\..\Setup.cpp"
namespace Erudition_Lightcone{
    void Cosmos_Fell(Ally *ptr);
    void Cosmos_Fell(Ally *ptr){
        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),953,476,331);
        ptr->Light_cone.Name = "Cosmos_Fell";
        ptr->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"]+=40;
            ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=24;

        };
        
        
    }
}
#endif