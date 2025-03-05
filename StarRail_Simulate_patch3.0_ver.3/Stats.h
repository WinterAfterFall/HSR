#ifndef STATS_H
#define STATS_H
#include <bits/stdc++.h>
#include "Control_panel.h"
using namespace std;
#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12



class Func{
    public:
    string Name;
    function<void(Ally *x)> Reset_func ;
    function<void(Ally *ptr)> Setup_Memo_func ;
    function<void(Ally *ptr)> When_Combat_func ;
    function<void(Ally *ptr)> Tune_stats_func ;
    function<void(Ally *ptr)> Start_game_func ;
    function<void(Ally *ptr)> Start_wave_func ;
    function<void(Ally *ptr)> Before_turn_func ;
    function<void(Ally *ptr)> After_turn_func ;
    function<void(Ally *ptr,Combat_data &data_)> Before_attack_func ;
    function<void(Ally *ptr,Combat_data &data_)> After_attack_func ;
    function<void(Ally *ptr,Combat_data &data_)> When_attack_func ;
    function<void(Ally *ptr,Combat_data &data_)> Buff_func ;
    function<void(Enemy* target,Ally *ptr,double Dot_ratio,string Dot_type)> Dot_func ;
    function<void(Ally *ptr,Enemy *target,Sub_Unit *Breaker)> Toughness_break_func ;
    function<void(Ally *ptr,Enemy *target)> Enemy_hit_func ;
    function<void(Ally *ptr,Enemy* target,Sub_Unit *Applier)> Apply_debuff_func ;
    function<void(Ally *ptr,Sub_Unit *SP_maker,int SP)> Skill_point_func ;
    function<void(Ally *ptr,Combat_data &data_,int Hit_cnt,int Total_Hit_cnt)> Hit_func ;
    function<void(Ally *ptr,Enemy *target,Sub_Unit *Killer)> Enemy_Death_func ;
    function<void(Ally *ptr,Ally *target,double Energy)> When_Energy_Increase_func ;


    function<void(Ally *ptr)> Print_Func;
};
// Action value stats for a unit (atv)
class Action_value_stats {
public:
    double Base_speed = 0.01;//*
    double Flat_speed = 0;
    double Speed_percent = 0;
    double atv ;//*
    double Max_atv;//*
    int turn_cnt = 0;
    int Unit_num = 0;//*
    string Side;//Memosprite Ally Summon
    int priority = 0;
    string Char_Name;
    string Unit_Name;

    Unit* ptr_to_unit = nullptr; //* // This will be set to point back to the unit (Ally or Enemy)
};
// Base Unit class
class Unit {
public:
    unique_ptr<Action_value_stats> Atv_stats;  // Moved Atv_stats here to be shared by both Ally and Enemy
    function<void(Unit *ptr)> Turn_func ;
    Common_stats_each_element Stats_each_element;//Ice Quantum
    Common_stats_type Stats_type;// Atk% Flat_Atk Def% Dmg% Crit_rate Crit_dam Def_shred Respen Vul Break_effect Weakness_Break_Efficiency 
    // Constructor to initialize Atv_stats and set ptr_to_unit to 'this'
    Unit() {
        Atv_stats = make_unique<Action_value_stats>();  // Create Atv_stats in Unit
        Atv_stats->ptr_to_unit = this;  // Set ptr_to_unit to this object (Unit, Ally, or Enemy)
    }
       
    //double Mitigation = 0;
    
    
    virtual ~Unit() {}  // Virtual destructor to ensure proper cleanup of derived classes
};

// Common stats for all units
// Common stats for elements



// Ally stats
class Sub_Unit : public Unit {
public:
    double Unit_Speed_Ratio = 0;
    double Unit_Hp_Ratio = 0 ;
    double Base_atk;//*
    double Base_hp;//*
    double Base_def;//*
    
    unordered_map<string,int> Stack;
    unordered_map<string,double> Buff_note;
    unordered_map<string,int> Buff_countdown;
    unordered_map<string,bool> Buff_check;
    
    vector<string> Element_type ;//*
    
    //string Target_Buff = "Ally";
    int Target_num = Main_dps_num;
    int Sub_Unit_num = 0;
    int Enemy_target_num = Main_Enemy_num;
    Ally* ptr_to_unit = nullptr;
    //temp 
    // Constructor now calls the base class constructor to initialize Atv_stats and set ptr_to_unit
    Sub_Unit() : Unit() {
          // Call Unit constructor to initialize Atv_stats and set ptr_to_unit  // Using unique_ptr for stats
    }

    ~Sub_Unit() {}
};
// Enemy stats
// Ally class, derived from Unit
class Ally{
public:


    double Max_energy = -1;//*
    double Current_energy = -1;
    double Energy_recharge = 100;
    double Ult_cost = -1;//*
    Func Light_cone;//*
    Func Char_func;//*
    Func Relic;//*
    Func Planar;//*
    int Eidolon;//*

    vector<double> Normal_Damage;//*
    vector<double> Dot_damage;//*
    vector<double> Break_damage;//*
    vector<double> Superbreak_damage;//*
    vector<double> Max_Damage;//*
    vector<double> Max_Dot_damage;//*
    vector<double> Max_Break_damage;//*
    vector<double> Max_Superbreak_damage;//*

    vector<double> Average_damage_instance;
    double Average_Damage = 0;
    double Max_Average_Damage = 0;
    double Last_note = 0;

    double Total_damage;
    double Max = 0;
    vector<pair<string,int>> Substats;//*
    vector<int> Max_damage_Substats;//*
    bool Reroll_check=0;
    bool Stop_reroll=1;
    int Total_substats = 20;
    int Current_substats = Total_substats;

    int Separate_sub = 20;
    int Current_spilt = 0;
    int Current_sub_choose =0;
    unordered_map<int,double> Damage_data;
    unordered_map<string,pair<double,int>> StatsType_Compare;
    pair<double,double> StatsType_Compare_MAX_MIN;

    unordered_map<string,pair<double,int>> TotalSubstats_Compare;
    pair<double,double> TotalSubstats_Compare_MAX_MIN;


    vector<string> Path ;//*
    function<void(Ally *ptr)> Ult_func ;//*
    vector<unique_ptr<Unit>> Summon_ptr;  //
    vector<unique_ptr<Sub_Unit>> Sub_Unit_ptr;  // 
    vector<unique_ptr<Unit>> Countdown_ptr;  // 

    int Technique = 1;
    int Ult_priority = 0;
    double Sub_effect_hit_rate_use = 0;
    double Sub_Speed_use = 0;

    bool Print =0;
    bool Wait_Other_Buff = 0;
    bool Er_Rope=0;
    bool Speed_Boot = 1;
    bool Element_Orb = 1;
    bool Body_CritDam = 0;
    double Speed_tune_value = 0;

    function<bool(Ally *ptr)> Ult_Condition = [](Ally *ptr){
        return false;
    };
    function<bool(Ally *ptr)> Skill_Condition = [](Ally *ptr){
        return false;
    };

    // Constructor now calls the base class constructor to initialize Atv_stats and set ptr_to_unit
    Ally() {  // Call Unit constructor to initialize Atv_stats and set ptr_to_unit
        Sub_Unit_ptr.resize(1);
        Sub_Unit_ptr[0] = make_unique<Sub_Unit>();
        Sub_Unit_ptr[0]->ptr_to_unit = this;
          // Using unique_ptr for stats
    }

    ~Ally() {}
};

// Enemy class, derived from Unit
class Enemy : public Unit {
public:
    bool Toughness_status = 1;
    double Max_toughness;   //*
    double Current_toughness;
    int Total_debuff = 0;
    unordered_map<string,int> Debuff;
    unordered_map<string,int> Debuff_time_count;
    string Target_type = "";//*
    int Bleed = 0,Bleeder = 0;
    int Burn = 0,Burner = 0;
    int Shock = 0,Shocker = 0;
    int Wind_shear = 0,Wind_shearer = 0;
    int  Wind_shear_stack = 0;
    int Freeze = 0;
    int Entanglement= 0,Entanglement_stack = 0;
    int Imprisonment = 0;
    unordered_map<string,bool> Weakness_type;
    double Energy_gen;
    double Total_toughness_broken_time =0;
    double when_toughness_broken;
 
    // Constructor now calls the base class constructor to initialize Atv_stats and set ptr_to_unit
    Enemy() : Unit() {  // Call Unit constructor to initialize Atv_stats and set ptr_to_unit
    
    }

    ~Enemy() {}
};
//Set base
void SetBaseStats(Sub_Unit *ptr,double BaseHp,double BaseAtk,double BaseDef){
    ptr->Base_hp +=BaseHp;
    ptr->Base_atk +=BaseAtk;
    ptr->Base_def +=BaseDef;

}
void SetBasicStats(Ally *ptr,double BaseSpeed,double Max_Energy,double Ult_cost,int Eidolon,string Element_type,string Path,int num,string Name,string Side,int Ult_priority){
        ptr->Sub_Unit_ptr[0]->Atv_stats->Base_speed = BaseSpeed;
        ptr->Max_energy = Max_Energy;
        ptr->Ult_cost = Ult_cost;
        ptr->Eidolon = Eidolon;
        ptr->Sub_Unit_ptr[0]->Element_type.push_back(Element_type);
        ptr->Path.push_back(Path);
        ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num = num;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Char_Name = Name;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name = Name;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Side = Side;
        //ptr->Sub_Unit_ptr[0]->Atv_stats->ptr_to_unit = ptr->Sub_Unit_ptr[0].get();
        ptr->Ult_priority =Ult_priority + ptr->Ult_priority;

}
void SetMemoStats(Ally *ptr,double Hp_ratio,double Speed_ratio,string Element_type,string Name,string Side){
        int num = ptr->Sub_Unit_ptr.size();
        int Num = ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num;
        
        ptr->Sub_Unit_ptr.push_back(make_unique<Sub_Unit>());
        ptr->Sub_Unit_ptr[num]->Unit_Hp_Ratio = Hp_ratio;
        ptr->Sub_Unit_ptr[num]->Unit_Speed_Ratio = Speed_ratio;
        ptr->Sub_Unit_ptr[num]->Atv_stats->Base_speed = -1;
        ptr->Sub_Unit_ptr[num]->Base_atk = ptr->Sub_Unit_ptr[0]->Base_atk;
        ptr->Sub_Unit_ptr[num]->Base_hp = ptr->Sub_Unit_ptr[0]->Base_hp*(ptr->Sub_Unit_ptr[num]->Unit_Hp_Ratio/100);
        ptr->Sub_Unit_ptr[num]->Base_def = ptr->Sub_Unit_ptr[0]->Base_def;
        ptr->Sub_Unit_ptr[num]->Element_type.push_back(Element_type);
        ptr->Sub_Unit_ptr[num]->Atv_stats->Unit_num = Num;
        ptr->Sub_Unit_ptr[num]->Atv_stats->Char_Name = Name;
        ptr->Sub_Unit_ptr[num]->Atv_stats->Unit_Name = Name;
        ptr->Sub_Unit_ptr[num]->Atv_stats->Side = Side;
        ptr->Sub_Unit_ptr[num]->Atv_stats->ptr_to_unit = ptr->Sub_Unit_ptr[num].get();
        ptr->Sub_Unit_ptr[num]->ptr_to_unit = ptr;

}
void SetCountdownStats(Ally *ptr,string Name){
        int num = ptr->Countdown_ptr.size();
        int Num = ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num;

        ptr->Countdown_ptr.push_back(make_unique<Sub_Unit>());
        ptr->Countdown_ptr[num]->Atv_stats->Base_speed = -1;
        ptr->Countdown_ptr[num]->Atv_stats->Unit_num = Num;
        ptr->Countdown_ptr[num]->Atv_stats->Char_Name = Name;
        ptr->Countdown_ptr[num]->Atv_stats->Unit_Name = Name;
        ptr->Countdown_ptr[num]->Atv_stats->Side = "Countdown";
        ptr->Countdown_ptr[num]->Atv_stats->ptr_to_unit = ptr->Countdown_ptr[num].get();
}
void SetSummonStats(Ally *ptr,double BaseSpeed,string Name){
        int num = ptr->Summon_ptr.size();
        int Num = ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num;

        ptr->Summon_ptr.push_back(make_unique<Sub_Unit>());
        ptr->Summon_ptr[num]->Atv_stats->Base_speed = BaseSpeed;
        ptr->Summon_ptr[num]->Atv_stats->Unit_num = Num;
        ptr->Summon_ptr[num]->Atv_stats->Char_Name = Name;
        ptr->Summon_ptr[num]->Atv_stats->Unit_Name = ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name;
        ptr->Summon_ptr[num]->Atv_stats->Side = "Summon";
        ptr->Summon_ptr[num]->Atv_stats->ptr_to_unit = ptr->Summon_ptr[num].get();
}

//normal buff/debuff
// 
Sub_Unit* Choose_Target_buff(Sub_Unit *ptr){
    return Ally_unit[ptr->Target_num]->Sub_Unit_ptr[ptr->Sub_Unit_num].get();
}
Ally* Choose_Character_Buff(Sub_Unit *ptr){
    return Ally_unit[ptr->Target_num].get();
}
Enemy* Choose_Enemy_target(Sub_Unit *ptr){
    return Enemy_unit[ptr->Enemy_target_num].get();
}
void Buff_single_target(Sub_Unit *ptr,string stats_type,string Attack_type,string Element,double Value){
    
    if(Element=="None"){
        ptr->Stats_type[stats_type][Attack_type] += Value;
        
    }else{
        ptr->Stats_each_element[stats_type][Element][Attack_type] += Value;
    }
}
void Buff_single_with_all_memo(Ally *ptr,string stats_type,string Attack_type,string Element,double Value){
    
    if(Element=="None"){
        for(int i=0;i<ptr->Sub_Unit_ptr.size();i++){
                ptr->Sub_Unit_ptr[i]->Stats_type[stats_type][Attack_type] += Value;
        }
    }else{
        for(int i=0;i<ptr->Sub_Unit_ptr.size();i++){
                ptr->Sub_Unit_ptr[i]->Stats_each_element[stats_type][Element][Attack_type] += Value;
            }
    }
}
void Buff_single_with_all_memo_each(Ally *ptr,string stats_type,string Attack_type,string Element,double Value,string Buff_name){
    
    if(Element=="None"){
        for(int i=0;i<ptr->Sub_Unit_ptr.size();i++){
            if(ptr->Sub_Unit_ptr[i]->Buff_check[Buff_name]==0){
                ptr->Sub_Unit_ptr[i]->Stats_type[stats_type][Attack_type] += Value;
                ptr->Sub_Unit_ptr[i]->Buff_check[Buff_name]= 1;
            }
            }
    }else{
        for(int i=0;i<ptr->Sub_Unit_ptr.size();i++){
             if(ptr->Sub_Unit_ptr[i]->Buff_check[Buff_name]==0){
                ptr->Sub_Unit_ptr[i]->Stats_each_element[stats_type][Element][Attack_type] += Value;
                ptr->Sub_Unit_ptr[i]->Buff_check[Buff_name]= 1;
             }
            }
    }
}
void Buff_All_Ally(string stats_type,string Attack_type,string Element,double Value){
    if(Element=="None"){    
        for(int i=1;i<=Total_ally;i++){
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                Ally_unit[i]->Sub_Unit_ptr[j]->Stats_type[stats_type][Attack_type] += Value;
            }
        }
    }else{
        for(int i=1;i<=Total_ally;i++){
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                Ally_unit[i]->Sub_Unit_ptr[j]->Stats_each_element[stats_type][Element][Attack_type] += Value;
            }
        }
    }
}
void Buff_All_Ally_Each_Ally(string stats_type,string Attack_type,string Element,double Value,string Buff_name){
    if(Element=="None"){    
        for(int i=1;i<=Total_ally;i++){
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                if(Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check[Buff_name]==0){
                Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check[Buff_name] = 1;
                Ally_unit[i]->Sub_Unit_ptr[j]->Stats_type[stats_type][Attack_type] += Value;
                }
            }
        }
    }else{
        for(int i=1;i<=Total_ally;i++){
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                if(Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check[Buff_name]==0){
                Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check[Buff_name] = 1;
                Ally_unit[i]->Sub_Unit_ptr[j]->Stats_each_element[stats_type][Element][Attack_type] += Value;
                }
            }
        }
    }
}
void Buff_All_Ally_Excluding_Buffer(string stats_type,string Attack_type,string Element,double Value,string Buffer_name){
    if(Element=="None"){    
        for(int i=1;i<=Total_ally;i++){
            if(Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Char_Name==Buffer_name)continue;
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                Ally_unit[i]->Sub_Unit_ptr[j]->Stats_type[stats_type][Attack_type] += Value;
            }
        }
    }else{
        for(int i=1;i<=Total_ally;i++){
            if(Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Char_Name==Buffer_name)continue;
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                Ally_unit[i]->Sub_Unit_ptr[j]->Stats_each_element[stats_type][Element][Attack_type] += Value;
            }
        }
    }
}
void Buff_All_Ally_Each_Ally_Excluding_Buffer(string stats_type,string Attack_type,string Element,double Value,string Buff_name,string Buffer_name){
    if(Element=="None"){    
        for(int i=1;i<=Total_ally;i++){
            if(Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Char_Name==Buffer_name)continue;
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                if(Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check[Buff_name]==0){
                    Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check[Buff_name] = 1;
                Ally_unit[i]->Sub_Unit_ptr[j]->Stats_type[stats_type][Attack_type] += Value;
                }
            }
        }
    }else{
        for(int i=1;i<=Total_ally;i++){
            if(Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Char_Name==Buffer_name)continue;
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                if(Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check[Buff_name]==0){
                Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check[Buff_name]=1;
                Ally_unit[i]->Sub_Unit_ptr[j]->Stats_each_element[stats_type][Element][Attack_type] += Value;
                }
            }
        }
    }
}
void Debuff_single_target(Enemy *ptr,string stats_type,string Attack_type,string Element,double Value){
    if(Element=="None"){
        ptr->Stats_type[stats_type][Attack_type] += Value;
    }else{
        ptr->Stats_each_element[stats_type][Element][Attack_type] += Value;
    }
}
void Debuff_All_Enemy_Apply_ver(Sub_Unit *ptr,string stats_type,string Attack_type,string Element,double Value,string Debuff_Name){
    for(int i=1;i<=Total_enemy;i++){
        Apply_debuff(ptr,Enemy_unit[i].get());
        if(Enemy_unit[i]->Debuff[Debuff_Name]!=0)continue;
        Enemy_unit[i]->Debuff[Debuff_Name] = 1;
        Enemy_unit[i]->Total_debuff++;
        if(Element=="None"){
            Enemy_unit[i]->Stats_type[stats_type][Attack_type] += Value;
        }else{
            Enemy_unit[i]->Stats_each_element[stats_type][Element][Attack_type] += Value;
        }
    }

}
//stack buff/debuff
void Stack_Buff_single_target(Sub_Unit *ptr,string stats_type,string Attack_type,string Element,double Value_per_stack,int Stack_increase,int Stack_limit,string Stack_Name){
    if(ptr->Stack[Stack_Name]>=Stack_limit)return;
    if(ptr->Stack[Stack_Name]+Stack_increase>Stack_limit){
        Stack_increase = Stack_limit - ptr->Stack[Stack_Name];
    }

    if(Element=="None"){
        ptr->Stats_type[stats_type][Attack_type] += Stack_increase*Value_per_stack;
        ptr->Stack[Stack_Name]+=Stack_increase;
    }else{
        ptr->Stats_each_element[stats_type][Element][Attack_type] += Stack_increase*Value_per_stack;
        ptr->Stack[Stack_Name]+=Stack_increase;
    }
}
void Stack_Buff_single_with_all_memo(Ally *ptr,string stats_type,string Attack_type,string Element,double Value_per_stack,int Stack_increase,int Stack_limit,string Stack_Name){
    int original_increase = Stack_increase;
    if(Element=="None"){
        for(int i=0;i<ptr->Sub_Unit_ptr.size();i++){
            if(ptr->Sub_Unit_ptr[i]->Stack[Stack_Name]<Stack_limit){
                if(ptr->Sub_Unit_ptr[i]->Stack[Stack_Name]+Stack_increase>Stack_limit){
                Stack_increase = Stack_limit - ptr->Sub_Unit_ptr[i]->Stack[Stack_Name];
                }
                ptr->Sub_Unit_ptr[i]->Stats_type[stats_type][Attack_type] += Stack_increase*Value_per_stack;
                ptr->Sub_Unit_ptr[i]->Stack[Stack_Name]+=Stack_increase;

                Stack_increase = original_increase;
            }
        }
    }else{
        for(int i=0;i<ptr->Sub_Unit_ptr.size();i++){
            if(ptr->Sub_Unit_ptr[i]->Stack[Stack_Name]<Stack_limit){
                if(ptr->Sub_Unit_ptr[i]->Stack[Stack_Name]+Stack_increase>Stack_limit){
                Stack_increase = Stack_limit - ptr->Sub_Unit_ptr[i]->Stack[Stack_Name];
                }
                ptr->Sub_Unit_ptr[i]->Stats_each_element[stats_type][Element][Attack_type] += Stack_increase*Value_per_stack;
                ptr->Sub_Unit_ptr[i]->Stack[Stack_Name]+=Stack_increase;
                Stack_increase = original_increase;
            }
        }
    }
}
void Stack_Buff_All_Ally(string stats_type,string Attack_type,string Element,double Value_per_stack,int Stack_increase,int Stack_limit,string Stack_Name){
    int original_increase = Stack_increase;
    if(Element=="None"){    
        for(int i=1;i<=Total_ally;i++){
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                if(Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name]<Stack_limit){
                    if(Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name]+Stack_increase>Stack_limit){
                    Stack_increase = Stack_limit - Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name];
                    }
                    Ally_unit[i]->Sub_Unit_ptr[j]->Stats_type[stats_type][Attack_type] += Stack_increase*Value_per_stack;
                    Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name] += Stack_increase;
                    Stack_increase = original_increase;
                }
            }
        }
    }else{
        for(int i=1;i<=Total_ally;i++){
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                if(Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name]<Stack_limit){
                    if(Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name]+Stack_increase>Stack_limit){
                    Stack_increase = Stack_limit - Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name];
                    }
                    Ally_unit[i]->Sub_Unit_ptr[j]->Stats_each_element[stats_type][Element][Attack_type] += Stack_increase*Value_per_stack;
                    Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name] += Stack_increase;
                    Stack_increase = original_increase;
                }
            }
        }
    }
}
void Stack_Buff_All_Ally_Excluding_Buffer(string stats_type,string Attack_type,string Element,string Buffer_name,double Value_per_stack,int Stack_increase,int Stack_limit,string Stack_Name){
    int original_increase = Stack_increase;
    if(Element=="None"){    
        for(int i=1;i<=Total_ally;i++){
            if(Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Char_Name==Buffer_name)continue;
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                if(Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name]<Stack_limit){
                    if(Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name]+Stack_increase>Stack_limit){
                    Stack_increase = Stack_limit - Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name];
                    }
                    Ally_unit[i]->Sub_Unit_ptr[j]->Stats_type[stats_type][Attack_type] += Stack_increase*Value_per_stack;
                    Stack_increase = original_increase;
                }
            }
        }
    }else{
        for(int i=1;i<=Total_ally;i++){
            if(Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Char_Name==Buffer_name)continue;
            for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
                if(Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name]<Stack_limit){
                    if(Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name]+Stack_increase>Stack_limit){
                    Stack_increase = Stack_limit - Ally_unit[i]->Sub_Unit_ptr[j]->Stack[Stack_Name];
                    }
                    Ally_unit[i]->Sub_Unit_ptr[j]->Stats_each_element[stats_type][Element][Attack_type] += Stack_increase*Value_per_stack;
                    Stack_increase = original_increase;
                }
            }
        }
    }
}
void Stack_Debuff_single_target(Enemy *ptr,string stats_type,string Attack_type,string Element,double Value_per_stack,int Stack_increase,int Stack_limit,string Stack_Name){
    if(ptr->Debuff[Stack_Name]>=Stack_limit)return;
    if(ptr->Debuff[Stack_Name]+Stack_increase>Stack_limit){
        Stack_increase = Stack_limit - ptr->Debuff[Stack_Name];
    }
    if(ptr->Debuff[Stack_Name]==0)ptr->Total_debuff++;
    if(Element=="None"){
        ptr->Stats_type[stats_type][Attack_type] += Stack_increase*Value_per_stack;
        ptr->Debuff[Stack_Name]+=Stack_increase;
    }else{
        ptr->Stats_each_element[stats_type][Element][Attack_type] += Stack_increase*Value_per_stack;
        ptr->Debuff[Stack_Name]+=Stack_increase;
    }
}
void Stack_Debuff_All_Enemy(Sub_Unit *ptr,string stats_type,string Attack_type,string Element,double Value_per_stack,int Stack_increase,int Stack_limit,string Stack_Name){
    int original_increase = Stack_increase;
    for(int i=1;i<=Total_enemy;i++){
        Apply_debuff(ptr,Enemy_unit[i].get());
        if(Enemy_unit[i]->Debuff[Stack_Name]<Stack_limit){
            if(Enemy_unit[i]->Debuff[Stack_Name]==0)Enemy_unit[i]->Total_debuff++;
            if(Enemy_unit[i]->Debuff[Stack_Name]+Stack_increase>Stack_limit){
            Stack_increase = Stack_limit - Enemy_unit[i]->Debuff[Stack_Name];
            }
            Enemy_unit[i]->Debuff[Stack_Name]+=Stack_increase;
            if(Element=="None"){
                Enemy_unit[i]->Stats_type[stats_type][Attack_type] += Stack_increase*Value_per_stack;
            }else{
                Enemy_unit[i]->Stats_each_element[stats_type][Element][Attack_type] += Stack_increase*Value_per_stack;
            }
            Stack_increase = original_increase;
        }
        
    }

}
//normal extend buff / debuff
void Extend_Buff_single_target(Sub_Unit *ptr,string Buff_name,int Turn_extend){
    ptr->Buff_countdown[Buff_name] = ptr->Atv_stats->turn_cnt+Turn_extend;
}
void Extend_Buff_single_with_all_memo(Ally *ptr,string Buff_name,int Turn_extend){
    for(int i=0;i<ptr->Sub_Unit_ptr.size();i++){
        ptr->Sub_Unit_ptr[i]->Buff_countdown[Buff_name] = ptr->Sub_Unit_ptr[i]->Atv_stats->turn_cnt+Turn_extend;
    }
}
void Extend_Buff_All_Ally(string Buff_name,int Turn_extend){
    for(int i=1;i<=Total_ally;i++){
        for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
            Ally_unit[i]->Sub_Unit_ptr[j]->Buff_countdown[Buff_name] = Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->turn_cnt + Turn_extend;
        }
    }
}
void Extend_Buff_All_Ally_Excluding_Buffer(string Buff_name,int Turn_extend,string Buffer_name){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Char_Name==Buffer_name)continue;

        for(int j=0;j<Ally_unit[i]->Sub_Unit_ptr.size();j++){
            Ally_unit[i]->Sub_Unit_ptr[j]->Buff_countdown[Buff_name] = Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->turn_cnt + Turn_extend;
        }
    }
}
void Extend_Debuff_single_target(Enemy *ptr,string Debuff_name,int Turn_extend){
    ptr->Debuff_time_count[Debuff_name] = ptr->Atv_stats->turn_cnt+Turn_extend;
}
void Extend_Debuff_All_Enemy(string Debuff_name,int Turn_extend){
    for(int i=1;i<=Total_enemy;i++){
        Enemy_unit[i]->Debuff_time_count[Debuff_name] = Enemy_unit[i]->Atv_stats->turn_cnt + Turn_extend;
    }
}

bool Buff_end(Sub_Unit *ptr,string Buff_name){
    if(ptr->Atv_stats->turn_cnt==ptr->Buff_countdown[Buff_name]&&turn->Char_Name==ptr->Atv_stats->Char_Name){
        return true;
    }
    return false;
}
bool Debuff_end(Enemy *ptr,string Debuff_name){
    if(ptr->Atv_stats->turn_cnt==ptr->Debuff_time_count[Debuff_name]&&turn->Char_Name==ptr->Atv_stats->Char_Name){
        return true;
    }
    return false;
}
bool Buff_check(Sub_Unit *ptr,string Buff_name){
    if(ptr->Buff_check[Buff_name]==1){
        return true;
    }
    return false;
}
bool Debuff_check(Enemy *ptr,string Debuff_name){
    if(ptr->Debuff[Debuff_name]==1){
        return true;
    }
    return false;
}
#endif