
#ifndef Double_Atk_H
#define Double_Atk_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Relic{
    void Double_Atk(Ally *ptr);
    void Double_Atk(Ally *ptr){
        ptr->Relic.Name = "Double_Atk";

        ptr->Relic.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"] += 24;


        };
        
    }
}
#endif