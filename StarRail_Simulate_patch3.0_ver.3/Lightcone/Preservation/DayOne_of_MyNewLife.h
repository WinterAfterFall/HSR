
#ifndef DayOne_of_MyNewLife_H
#define DayOne_of_MyNewLife_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"
namespace Preservation_Lightcone{
    void DayOne_of_MyNewLife(Ally *ptr);
    void DayOne_of_MyNewLife(Ally *ptr){

        SetBaseStats(ptr->Sub_Unit_ptr[0].get(),953,370,463);
        ptr->Light_cone.Name = "DayOne_of_MyNewLife";

        ptr->Light_cone.Reset_func = [](Ally *ptr){
            ptr->Sub_Unit_ptr[0]->Stats_type["Def%"]["None"]+=24;
        };
       
    }
}
#endif