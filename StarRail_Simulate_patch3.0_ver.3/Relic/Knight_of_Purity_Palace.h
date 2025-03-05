
#ifndef Knight_H
#define Knight_H

#define endl '\n'
#define F first
#define S second
#include"..\Setup.cpp"
namespace Relic{
    void Knight(Ally *ptr);
    void Knight(Ally *ptr){
        ptr->Relic.Name = "Knight";
        ptr->Relic.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Def%"]["None"]+=15;
    
        };
        
    }
}
#endif