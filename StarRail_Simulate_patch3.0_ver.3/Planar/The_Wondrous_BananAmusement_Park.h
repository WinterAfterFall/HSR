
#ifndef The_Wondrous_H
#define The_Wondrous_H


#include"..\Setup.cpp"
namespace Planar{
    void The_Wondrous_BananAmusement_Park(Ally *ptr);
    void The_Wondrous_BananAmusement_Park(Ally *ptr){
        
        ptr->Planar.Name="The_Wondrous_BananAmusement_Park"; 
        ptr->Planar.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"] += 16;
        };
        ptr->Planar.When_Combat_func = [](Ally *ptr){
            if(ptr->Summon_ptr.size()!=0||ptr->Sub_Unit_ptr.size()>1){
                ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"] += 32;

            }
        };
       
    }
}
#endif