#include<bits/stdc++.h>
#include <stdlib.h>

#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
using std::cout ;
using std::vector;
//#include"Setup.cpp"
#include"Calculate_damage.cpp"
#include".\Character\All_Character.h"
#include".\Lightcone\All_Lighcone.h"
#include".\Planar\All_Planar.h"
#include".\Relic\All_Relic.h"
void Print();
void Print_damage();
void Print(){
    if(!Print_Atv)return;
    cout<<"Atv = "<<Current_atv<<" ";
    cout<<""<<turn->Char_Name<<" ";
    cout<<turn->turn_cnt<<" ";
    // cout<<""<<Ally_unit[2]->Sub_Unit_ptr[0]->Atv_stats->Max_atv<<" ";
    // cout<<""<<Ally_unit[2]->Sub_Unit_ptr[0]->Atv_stats->Speed_percent<<" ";
    cout<<""<<Ally_unit[3]->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"]<<" ";

    //Ally_unit[2]->Char_func.Print_Func(Ally_unit[2].get());


    //cout<<sp<<" ";


    


    
    
    // cout<<Ally_unit[1]->Sub_Unit_ptr[0]->Atv_stats->Speed_percent<<" ";
    // cout<<Ally_unit[1]->Sub_Unit_ptr[1]->Atv_stats->Flat_speed<<" ";
    
    
    
    cout<<endl;
}
void Print_damage(){
    double Temp_sum = 0;
    for(int i=1;i<=Total_ally;i++){
        Temp_sum = 0;
        for(auto e:Ally_unit[i]->Average_damage_instance){
            Temp_sum += e;
        }
        Ally_unit[i]->Average_Damage = Temp_sum/Ally_unit[i]->Average_damage_instance.size();
    }
    long long sum=0;
    for(int j=1;j<=Total_ally;j++){
    double temp = 0;
    cout<<Ally_unit[j]->Sub_Unit_ptr[0]->Atv_stats->Char_Name<<endl;
    
    //cout<<Ally_unit[j]->stats->Normal_Damage[1]<<" ";
    // for(int i=1;i<=Total_enemy;i++){
    //     temp+=Ally_unit[j]->stats->Total_Damage[i];
        
    // }
    // cout<<static_cast<long long>(temp)<<" ";
    // for(int i=1;i<=Total_enemy;i++){
    //     temp+=Ally_unit[j]->stats->Total_Break_damage[i];
        
    // }
    // cout<<static_cast<long long>(temp)<<" ";
    // for(int i=1;i<=Total_enemy;i++){
    //     temp+=Ally_unit[j]->stats->Total_Dot_damage[i];
        
    // }
    // cout<<static_cast<long long>(temp)<<" ";
    // for(int i=1;i<=Total_enemy;i++){
    //     temp+=Ally_unit[j]->stats->Total_Superbreak_damage[i];
        
    // }
    cout<<"Total Damage : ";
    if(Ally_unit[j]->Max==0){
        cout<<static_cast<long long>(Ally_unit[j]->Total_damage)<<" ";
    }else{
        cout<<static_cast<long long>(Ally_unit[j]->Max)<<" ";
    }
    
    cout<<"Avg Damage : ";
    if(Ally_unit[j]->Max_Average_Damage==0){
        cout<<static_cast<long long>(Ally_unit[j]->Average_Damage)<<endl;
        sum+=static_cast<long long>(Ally_unit[j]->Average_Damage);

    }else{
        cout<<static_cast<long long>(Ally_unit[j]->Max_Average_Damage)<<endl;
        sum+=static_cast<long long>(Ally_unit[j]->Max_Average_Damage);
    }
    
    


    cout<<"Substats : ";
    if(Ally_unit[j]->Max_damage_Substats.size()==0){
        for(auto e:Ally_unit[j]->Substats){
        cout<<e.second<<" ";
    }
    }else{
        for(auto e:Ally_unit[j]->Max_damage_Substats){
        cout<<e<<" ";
    }
    }
    
    cout<<"Total Turn : ";
    cout<<Ally_unit[j]->Sub_Unit_ptr[0]->Atv_stats->turn_cnt<<" ";
    cout<<endl;
    }
    cout<<sum;
    // cout<<static_cast<long long>(Ally_unit[1]->Normal_Damage[1])<<endl;
    // cout<<static_cast<long long>(Ally_unit[1]->Normal_Damage[2])<<endl;
    // cout<<static_cast<long long>(Ally_unit[1]->Normal_Damage[3])<<endl;
}
void Print_All_Substats(){
    for(auto e:Ally_unit[1]->StatsType_Compare){
        cout<<e.first<<" ";
        cout<<e.second.first<<endl;
    }
    cout<<Ally_unit[1]->StatsType_Compare_MAX_MIN.first<<" "<<Ally_unit[1]->StatsType_Compare_MAX_MIN.second<<endl;
    for(auto e:Ally_unit[1]->TotalSubstats_Compare){
        cout<<e.first<<" ";
        cout<<e.second.first<<endl;
    }
    cout<<Ally_unit[1]->TotalSubstats_Compare_MAX_MIN.first<<" "<<Ally_unit[1]->TotalSubstats_Compare_MAX_MIN.second<<endl;
    return;
    // for(auto e:Ally_unit[1]->Damage_data){
    //     int index = e.first;
    //     cout<<"{ ";
    //     for(int i=Ally_unit[1]->Substats.size()-1;i>=0;i--){
    //         int temp = pow(Ally_unit[1]->Total_substats+1,i);
    //         cout<<index/temp<<" ";
    //         index = index % temp;
    //     }
    //     cout<<"} "<<e.second<<endl;
    // }
}
void Calculate_All_Substats(){
    for(auto e:Ally_unit[1]->Damage_data){
        int index = e.first;
        for(int i=Ally_unit[1]->Substats.size()-1;i>=0;i--){
            int temp = pow(Ally_unit[1]->Total_substats+1,i);
            Ally_unit[1]->Substats[i].second=index/temp;
            index = index % temp;
        }
        for(int i=1;i<Ally_unit[1]->Substats.size();i++){
            if(Ally_unit[1]->Substats[i].second==0)continue;
            index = Ally_unit[1]->Substats[0].second+1;
            for(int j=1;j<Ally_unit[1]->Substats.size();j++){
                int temp = pow(Ally_unit[1]->Total_substats+1,j);
                if(i==j){
                    index+=(Ally_unit[1]->Substats[j].second-1)*temp;
                }else{
                    index+=(Ally_unit[1]->Substats[j].second)*temp;
                }   
            }
            Ally_unit[1]->StatsType_Compare[Ally_unit[1]->Substats[i].first].first=
            ((Ally_unit[1]->StatsType_Compare[Ally_unit[1]->Substats[i].first].first*Ally_unit[1]->StatsType_Compare[Ally_unit[1]->Substats[i].first].second)+(100*e.second/Ally_unit[1]->Damage_data[index]))
            /((double)Ally_unit[1]->StatsType_Compare[Ally_unit[1]->Substats[i].first].second+1);
            if(Ally_unit[1]->StatsType_Compare_MAX_MIN.first<100*e.second/Ally_unit[1]->Damage_data[index])Ally_unit[1]->StatsType_Compare_MAX_MIN.first = 100*e.second/Ally_unit[1]->Damage_data[index];
            if(Ally_unit[1]->StatsType_Compare_MAX_MIN.second>100*e.second/Ally_unit[1]->Damage_data[index])Ally_unit[1]->StatsType_Compare_MAX_MIN.second = 100*e.second/Ally_unit[1]->Damage_data[index];
            Ally_unit[1]->StatsType_Compare[Ally_unit[1]->Substats[i].first].second++;
        }
        if(Calculate_All_possible_mode){
        for(int i=0;i<Ally_unit[1]->Substats.size();i++){
            if(Ally_unit[1]->Substats[i].second==0)continue;
            index = e.first - pow(Ally_unit[1]->Total_substats+1,i);
            cout<<e.second<<" "<<Ally_unit[1]->Damage_data[index]<<endl;
            cout<<e.first<<" "<<index<<" "<<Ally_unit[1]->Substats[i].second<<endl;
            
            Ally_unit[1]->TotalSubstats_Compare[Ally_unit[1]->Substats[i].first].first=
            ((Ally_unit[1]->TotalSubstats_Compare[Ally_unit[1]->Substats[i].first].first*Ally_unit[1]->TotalSubstats_Compare[Ally_unit[1]->Substats[i].first].second)+(100*e.second/Ally_unit[1]->Damage_data[index]))
            /((double)Ally_unit[1]->TotalSubstats_Compare[Ally_unit[1]->Substats[i].first].second+1);
            if(Ally_unit[1]->TotalSubstats_Compare_MAX_MIN.first<100*e.second/Ally_unit[1]->Damage_data[index])Ally_unit[1]->TotalSubstats_Compare_MAX_MIN.first = 100*e.second/Ally_unit[1]->Damage_data[index];
            if(Ally_unit[1]->TotalSubstats_Compare_MAX_MIN.second>100*e.second/Ally_unit[1]->Damage_data[index])Ally_unit[1]->TotalSubstats_Compare_MAX_MIN.second = 100*e.second/Ally_unit[1]->Damage_data[index];
            Ally_unit[1]->TotalSubstats_Compare[Ally_unit[1]->Substats[i].first].second++;
        }
        }
    }
}