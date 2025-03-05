
#ifndef Iron_Cavalry_H
#define Iron_Cavalry_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Relic{
    void Iron_Cavalry(Ally *ptr);
    void Iron_Cavalry(Ally *ptr){
        ptr->Relic.Name = "Iron_Cavalry";
        ptr->Relic.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]+=16;

        };
        ptr->Relic.When_Combat_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Def_shred"]["Break_dmg"]+=10;
            ptr->Sub_Unit_ptr[0]->Stats_type["Def_shred"]["Super_break"]+=15;

        };
        
    }
}
#endif