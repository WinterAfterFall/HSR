#ifndef ATV_H
#define ATV_H
#include<bits/stdc++.h>
#include"Stats.h"
#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
#define K_const 10000


bool compareActionValueStats(Action_value_stats* a, Action_value_stats* b) {
    return a->atv > b->atv; // Sort by `atv` in descending order
}
void Update_Max_atv(Action_value_stats *ptr) {
    if(ptr->Base_speed<=0){
        ptr->Max_atv = 1e6;
        return;
    }
    ptr->Max_atv = K_const / (ptr->Base_speed + ptr->Base_speed * ptr->Speed_percent/100 + ptr->Flat_speed);
    
}
void atv_reset(Action_value_stats *ptr) {

    ptr->atv = ptr->Max_atv;
    
}
void All_atv_reset() {
    for(int i=1;i<=Total_enemy;i++){
        Update_Max_atv(Enemy_unit[i]->Atv_stats.get());
        atv_reset(Enemy_unit[i]->Atv_stats.get());
    }
    
    for(int i=1;i<=Total_ally;i++){
        for(int j=0,sz = Ally_unit[i]->Summon_ptr.size();j<sz;j++){
        Update_Max_atv(Ally_unit[i]->Summon_ptr[j]->Atv_stats.get());
        atv_reset(Ally_unit[i]->Summon_ptr[j]->Atv_stats.get());
        }
    }
    for(int i=1;i<=Total_ally;i++){
        for(int j=0,sz = Ally_unit[i]->Countdown_ptr.size();j<sz;j++){
        Update_Max_atv(Ally_unit[i]->Countdown_ptr[j]->Atv_stats.get());
        atv_reset(Ally_unit[i]->Countdown_ptr[j]->Atv_stats.get());
        }
    }
    for(int i=1;i<=Total_ally;i++){
        for(int j=0,sz = Ally_unit[i]->Sub_Unit_ptr.size();j<sz;j++){
        Update_Max_atv(Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats.get());
        atv_reset(Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats.get());
        }
    }
       
    
}
void Action_forward(Action_value_stats *ptr,double fwd) {
    if(ptr->Base_speed<=0)return;
    if(ptr->Unit_num==0){
        return ;
    }
    if (ptr->atv <= ptr->Max_atv*fwd/100 ) {
        ptr->atv = 0;
        ptr->priority = ++Turn_priority;
        return ;
    } else {
        ptr->atv = ptr->atv - ptr->Max_atv*fwd/100;
        return ;
    }
}
void All_Action_forward(double fwd){
    vector<Action_value_stats*> vec;
    for(int i=1;i<=Total_ally;i++){
        for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
            vec.push_back(Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats.get());
        }
    }
    sort(vec.begin(),vec.end(),compareActionValueStats);
    for(int i=0;i<vec.size();i++){
        Action_forward(vec[i],fwd);
      
    }
}


void Speed_Buff(Action_value_stats *ptr,double spd_percent ,double flat_spd ) {
    double x = ptr->Max_atv;
    ptr->Flat_speed += flat_spd;
    ptr->Speed_percent += spd_percent;
    Update_Max_atv(ptr);
    ptr->atv=ptr->atv/x*ptr->Max_atv;
}
void Speed_Buff_All_Ally(double spd_percent ,double flat_spd){
    for(int i=1;i<=Total_ally;i++){
        for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
            Speed_Buff(Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats.get(),spd_percent,flat_spd);
        }
    }
}
void Speed_Buff_All_Ally(double spd_percent ,double flat_spd,string Buff_name){
    for(int i=1;i<=Total_ally;i++){
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                if(Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check[Buff_name]==0){
                    Speed_Buff(Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats.get(),spd_percent,flat_spd);
                    Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check[Buff_name]=1;
                }
            }
    }
}
void Speed_Buff_All_Ally_Exclude_Buffer(double spd_percent ,double flat_spd,string Buffer){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Char_Name==Buffer)continue;
        for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
            Speed_Buff(Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats.get(),spd_percent,flat_spd);
        }
    }
}
void Speed_Buff_All_Ally_Exclude_Buffer(double spd_percent ,double flat_spd,string Buffer,string Buff_name){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Char_Name==Buffer)continue;
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                if(Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check[Buff_name]==0){
                    Speed_Buff(Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats.get(),spd_percent,flat_spd);
                    Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check[Buff_name]=1;
                }
            }
    }
}

void Increase_energy(Ally *ptr,double Energy ){
    When_Energy_Increase(ptr,Energy*ptr->Energy_recharge/100);
    if(ptr->Current_energy+Energy*ptr->Energy_recharge/100 > ptr->Max_energy){
        ptr->Current_energy = ptr->Max_energy;
    }else{
        ptr->Current_energy +=  Energy*ptr->Energy_recharge/100;
    }
    
    return ;
}
void Increase_energy(Ally *ptr,double Energy_percent,double Flat_energy){
    When_Energy_Increase(ptr,Energy_percent/100*ptr->Max_energy+Flat_energy);
    if(ptr->Current_energy+Flat_energy+Energy_percent/100*ptr->Max_energy > ptr->Max_energy){
        ptr->Current_energy = ptr->Max_energy;
    }else{
        ptr->Current_energy += Flat_energy+Energy_percent/100*ptr->Max_energy;
    }
    
    return;
}
void Find_turn(){
    pair<double,int> mx;
    turn = nullptr;
    mx.first = 1e9;
    mx.second = 0;
    for(int i=1;i<=Total_enemy;i++){
        if(mx.first > Enemy_unit[i]->Atv_stats->atv){
            mx.first = Enemy_unit[i]->Atv_stats->atv;
            mx.second = Enemy_unit[i]->Atv_stats->priority;
            turn = Enemy_unit[i]->Atv_stats.get();
            continue;
        }
        if(mx.first == Enemy_unit[i]->Atv_stats->atv){
            if(mx.second<Enemy_unit[i]->Atv_stats->priority){
                mx.second = Enemy_unit[i]->Atv_stats->priority;
            turn = Enemy_unit[i]->Atv_stats.get();
            }
        }
    }
    for(int i=1;i<=Total_ally;i++){
        for(int j=0,sz = Ally_unit[i]->Summon_ptr.size();j<sz;j++){ 
        if(mx.first >Ally_unit[i]->Summon_ptr[j]->Atv_stats->atv){
            mx.first = Ally_unit[i]->Summon_ptr[j]->Atv_stats->atv;
            mx.second = Ally_unit[i]->Summon_ptr[j]->Atv_stats->priority;
            turn = Ally_unit[i]->Summon_ptr[j]->Atv_stats.get();
            continue;
        }
        if(mx.first == Ally_unit[i]->Summon_ptr[j]->Atv_stats->atv){
            if(mx.second<Ally_unit[i]->Summon_ptr[j]->Atv_stats->priority){
                mx.second = Ally_unit[i]->Summon_ptr[j]->Atv_stats->priority;
            turn = Ally_unit[i]->Summon_ptr[j]->Atv_stats.get();
            }
        }
    }
    }
    for(int i=1;i<=Total_ally;i++){
        for(int j=0,sz = Ally_unit[i]->Countdown_ptr.size();j<sz;j++){ 
        if(mx.first >Ally_unit[i]->Countdown_ptr[j]->Atv_stats->atv){
            mx.first = Ally_unit[i]->Countdown_ptr[j]->Atv_stats->atv;
            mx.second = Ally_unit[i]->Countdown_ptr[j]->Atv_stats->priority;
            turn = Ally_unit[i]->Countdown_ptr[j]->Atv_stats.get();
            continue;
        }
        if(mx.first == Ally_unit[i]->Countdown_ptr[j]->Atv_stats->atv){
            if(mx.second<Ally_unit[i]->Countdown_ptr[j]->Atv_stats->priority){
                mx.second = Ally_unit[i]->Countdown_ptr[j]->Atv_stats->priority;
            turn = Ally_unit[i]->Countdown_ptr[j]->Atv_stats.get();
            }
        }
    }
    }
    for(int i=1;i<=Total_ally;i++){
        for(int j=0,sz = Ally_unit[i]->Sub_Unit_ptr.size();j<sz;j++){ 
        if(mx.first >Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->atv){
            mx.first = Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->atv;
            mx.second = Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->priority;
            turn = Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats.get();
            continue;
        }
        if(mx.first == Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->atv){
            if(mx.second<Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->priority){
                mx.second = Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->priority;
            turn = Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats.get();
            }
        }
    }
    }
}
void Atv_fix(double Atv_reduce){
    for(int i=1;i<=Total_enemy;i++){
        Enemy_unit[i]->Atv_stats->atv -= Atv_reduce;
    }
    for(int i=1;i<=Total_ally;i++){
        for(int j=0,sz = Ally_unit[i]->Summon_ptr.size();j<sz;j++){
        Ally_unit[i]->Summon_ptr[j]->Atv_stats->atv -= Atv_reduce;
        }
    }
    for(int i=1;i<=Total_ally;i++){
        for(int j=0,sz = Ally_unit[i]->Countdown_ptr.size();j<sz;j++){
        Ally_unit[i]->Countdown_ptr[j]->Atv_stats->atv -= Atv_reduce;
        }
    }
    for(int i=1;i<=Total_ally;i++){
        for(int j=0,sz = Ally_unit[i]->Sub_Unit_ptr.size();j<sz;j++){
        Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->atv -= Atv_reduce;
        }
    }
    Current_atv+=Atv_reduce;
}
#endif