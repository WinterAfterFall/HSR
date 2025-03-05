#ifndef Setup_H
#define Setup_H
#include<bits/stdc++.h>
#include"Basic_function.cpp"

#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
#define K_const 10000
//Defination
void Setup();

void Start_game();
void Start_wave(int WAVE);
void Reset();
bool Reroll_substats(Ally *ptr);



void Setup(){
    if(Driver_Type!="None"&&(Driver_num==0||Driver_num>Total_ally)){
        cout<<"Driver issue faq u bitch eiei";
        exit(0);
    }
    for(int i=1;i<=Total_ally;i++){
        // Ally_unit[i]->Atk_flat["None"] = 0;
        // Ally_unit[i]->Atk_percent["None"] = 0;
        // Ally_unit[i]->Hp_flat["None"] = 0;
        // Ally_unit[i]->Hp_percent["None"] = 0;
        // Ally_unit[i]->Def_flat["None"] = 0;
        // Ally_unit[i]->Def_percent["None"] = 0;
        // Ally_unit[i]->Dmg_bonus["None"] = 0;
        // Ally_unit[i]->Crit_rate["None"] = 0;
        // Ally_unit[i]->Crit_dam["None"] = 0;
        // Ally_unit[i]->Def_shred["None"] = 0;
        // Ally_unit[i]->Respen["None"] = 0;
        // Ally_unit[i]->Vul["None"] = 0;
        // Ally_unit[i]->Break_effect["None"] = 0;
        // Ally_unit[i]->Mitigation["None"] = 0;
        // Ally_unit[i]->Weakness_Break_Efficiency["None"] = 0;
        // Ally_unit[i]->Toughness_reduction["None"] = 0;

        Ally_unit[i]->Current_substats=Ally_unit[i]->Total_substats;
        Ally_unit[i]->StatsType_Compare_MAX_MIN.first = -1;
        Ally_unit[i]->StatsType_Compare_MAX_MIN.second = 1e9;
        Ally_unit[i]->TotalSubstats_Compare_MAX_MIN.first = -1;
        Ally_unit[i]->TotalSubstats_Compare_MAX_MIN.second = 1e9;


        Ally_unit[i]->Normal_Damage.resize(Total_enemy+1);
        Ally_unit[i]->Dot_damage.resize(Total_enemy+1);
        Ally_unit[i]->Break_damage.resize(Total_enemy+1);
        Ally_unit[i]->Superbreak_damage.resize(Total_enemy+1);
        
        cout<<endl;
        Ally_unit[i]->Max_Damage.resize(Total_enemy+1);
        Ally_unit[i]->Max_Dot_damage.resize(Total_enemy+1);
        Ally_unit[i]->Max_Break_damage.resize(Total_enemy+1);
        Ally_unit[i]->Max_Superbreak_damage.resize(Total_enemy+1);




    }
}

void Reset(){
    turn = nullptr;
    sp =3;
    Basic_reset();
    Summon_reset();
    Countdown_reset();
    for(int i=1;i<=Total_ally;i++){

        if(Ally_unit[i]->Light_cone.Reset_func)
        Ally_unit[i]->Light_cone.Reset_func(Ally_unit[i].get());

        if(Ally_unit[i]->Relic.Reset_func)
        Ally_unit[i]->Relic.Reset_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->Planar.Reset_func)
        Ally_unit[i]->Planar.Reset_func(Ally_unit[i].get());

        if(Ally_unit[i]->Char_func.Reset_func)
        Ally_unit[i]->Char_func.Reset_func(Ally_unit[i].get());
    }
    Memosprite_reset();
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Light_cone.Setup_Memo_func)
        Ally_unit[i]->Light_cone.Setup_Memo_func(Ally_unit[i].get());

        if(Ally_unit[i]->Relic.Setup_Memo_func)
        Ally_unit[i]->Relic.Setup_Memo_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->Planar.Setup_Memo_func)
        Ally_unit[i]->Planar.Setup_Memo_func(Ally_unit[i].get());

        if(Ally_unit[i]->Char_func.Setup_Memo_func)
        Ally_unit[i]->Char_func.Setup_Memo_func(Ally_unit[i].get());
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Light_cone.When_Combat_func)
        Ally_unit[i]->Light_cone.When_Combat_func(Ally_unit[i].get());

        if(Ally_unit[i]->Relic.When_Combat_func)
        Ally_unit[i]->Relic.When_Combat_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->Planar.When_Combat_func)
        Ally_unit[i]->Planar.When_Combat_func(Ally_unit[i].get());

        if(Ally_unit[i]->Char_func.When_Combat_func)
        Ally_unit[i]->Char_func.When_Combat_func(Ally_unit[i].get());
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Light_cone.Tune_stats_func)
        Ally_unit[i]->Light_cone.Tune_stats_func(Ally_unit[i].get());

        if(Ally_unit[i]->Relic.Tune_stats_func)
        Ally_unit[i]->Relic.Tune_stats_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->Planar.Tune_stats_func)
        Ally_unit[i]->Planar.Tune_stats_func(Ally_unit[i].get());

        if(Ally_unit[i]->Char_func.Tune_stats_func)
        Ally_unit[i]->Char_func.Tune_stats_func(Ally_unit[i].get());
    }
    
    
}

void Start_game(){
    All_atv_reset();
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Char_func.Start_game_func)
        Ally_unit[i]->Char_func.Start_game_func(Ally_unit[i].get());

        if(Ally_unit[i]->Light_cone.Start_game_func)
        Ally_unit[i]->Light_cone.Start_game_func(Ally_unit[i].get());

        if(Ally_unit[i]->Relic.Start_game_func)
        Ally_unit[i]->Relic.Start_game_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->Planar.Start_game_func)
        Ally_unit[i]->Planar.Start_game_func(Ally_unit[i].get());
    }
}
void EndWave(double Total_atv){
    
    double temp = 0;
    for(int i=1;i<=Total_enemy;i++){
        
        for(int j=1;j<=Total_ally;j++){
            Ally_unit[j]->Normal_Damage[i] *= Cal_Average(Enemy_unit[i].get(),Total_atv);
            Ally_unit[j]->Dot_damage[i]*= Cal_Average(Enemy_unit[i].get(),Total_atv);
            Ally_unit[j]->Total_damage+=(Ally_unit[j]->Dot_damage[i]+Ally_unit[j]->Normal_Damage[i]+Ally_unit[j]->Superbreak_damage[i] +Ally_unit[j]->Break_damage[i]);
            Ally_unit[j]->Last_note = 0;
            
        }
        
    }

    cout<<endl;
    
}
void Start_wave(int WAVE){
    if(WAVE!=0)All_atv_reset();
    for(int i =1;i<=Total_enemy;i++){
        //Enemy_unit[i]->stats->Toughness_status=1;
        //Enemy_unit[i]->stats->Current_toughness=Enemy_unit[i]->Max_toughness;
        Enemy_unit[i]->when_toughness_broken = 0;
        Enemy_unit[i]->Total_toughness_broken_time = 0;
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Char_func.Start_wave_func)
        Ally_unit[i]->Char_func.Start_wave_func(Ally_unit[i].get());

        if(Ally_unit[i]->Light_cone.Start_wave_func)
        Ally_unit[i]->Light_cone.Start_wave_func(Ally_unit[i].get());

        if(Ally_unit[i]->Relic.Start_wave_func)
        Ally_unit[i]->Relic.Start_wave_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->Planar.Start_wave_func)
        Ally_unit[i]->Planar.Start_wave_func(Ally_unit[i].get());
    }
    
}
bool Permutation_Substats(Ally *ptr){
    if(0 == ptr->Reroll_check)return false;
    int index = 0;
        
        for(int i=1;i<=Total_enemy;i++){    
            ptr->Normal_Damage[i] = 0;
        }
        for(int i=1;i<=Total_enemy;i++){
            ptr->Break_damage[i] = 0;
        }
        for(int i=1;i<=Total_enemy;i++){
            ptr->Dot_damage[i] = 0;
        }
        for(int i=1;i<=Total_enemy;i++){
            ptr->Superbreak_damage[i] = 0;
        }
        for(int i=0;i<ptr->Substats.size();i++){
            index+= ptr->Substats[i].second*pow(ptr->Total_substats+1,i);
        }
        ptr->Damage_data[index] = ptr->Average_Damage;
        ptr->Average_Damage = 0;
        ptr->Average_damage_instance.clear();
    if(ptr->Substats[ptr->Substats.size()-1].second==ptr->Current_substats){
        if(Calculate_All_possible_mode){
            ptr->Current_substats--;
            ptr->Substats[0].second = ptr->Current_substats; 
            for(int i=1;i<ptr->Substats.size();i++){
                ptr->Substats[i].second = 0; 
            }
            if(ptr->Current_substats>=0)return true;
        }
        ptr->Reroll_check = 0;
        return false;
    }
    for(int i=0;i<ptr->Substats.size();i++){
        if(ptr->Substats[i].second!=0){
            ptr->Substats[0].second = ptr->Substats[i].second-1;
            if(i!=0){
              ptr->Substats[i].second = 0;  
            }
            ptr->Substats[i+1].second+=1;
            return true;
        }
    }
    return false;
}
void Set_Stats(Ally *ptr){
    for(int i=0,sz = ptr->Substats.size();i<sz;i++){
        if(ptr->Substats[i].first=="Speed"){
            ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=2.3*ptr->Substats[i].second;
            for(int j=1,SZ = ptr->Sub_Unit_ptr.size();j<SZ;j++){
            ptr->Sub_Unit_ptr[j]->Atv_stats->Flat_speed+=(2.3*ptr->Substats[i].second)*(ptr->Sub_Unit_ptr[j]->Unit_Speed_Ratio/100);
            }
            
        }else if(ptr->Substats[i].first=="Hp%"){ 
            for(int j=0,SZ = ptr->Sub_Unit_ptr.size();j<SZ;j++){
            Buff_single_target(ptr->Sub_Unit_ptr[j].get(),"Hp%","None","None",3.888*ptr->Substats[i].second);
            }
        }
        if(ptr->Substats[i].first=="Crit_rate"){
            for(int j=0,SZ = ptr->Sub_Unit_ptr.size();j<SZ;j++){
            Buff_single_target(ptr->Sub_Unit_ptr[j].get(),"Crit_rate","None","None",2.9*ptr->Substats[i].second);
            }

        }else if(ptr->Substats[i].first=="Crit_dam"){
            for(int j=0,SZ = ptr->Sub_Unit_ptr.size();j<SZ;j++){
            Buff_single_target(ptr->Sub_Unit_ptr[j].get(),"Crit_dam","None","None",5.8*ptr->Substats[i].second);
            }
            
        }else if(ptr->Substats[i].first=="Atk%"){
            for(int j=0,SZ = ptr->Sub_Unit_ptr.size();j<SZ;j++){
            Buff_single_target(ptr->Sub_Unit_ptr[j].get(),"Atk%","None","None",3.888*ptr->Substats[i].second);
            }
            
        }else if(ptr->Substats[i].first=="Def%"){
            for(int j=0,SZ = ptr->Sub_Unit_ptr.size();j<SZ;j++){
            Buff_single_target(ptr->Sub_Unit_ptr[j].get(),"Def%","None","None",4.86*ptr->Substats[i].second);
            }
            
        }else if(ptr->Substats[i].first=="Break_effect"){
            for(int j=0,SZ = ptr->Sub_Unit_ptr.size();j<SZ;j++){
            Buff_single_target(ptr->Sub_Unit_ptr[j].get(),"Break_effect","None","None",5.8*ptr->Substats[i].second);
            }
        }
    }
}
bool Reroll_substats(Ally *ptr){
    
    if(0 == ptr->Reroll_check){
        double Temp_mx=0;
        ptr->Average_Damage = 0;
        ptr->Average_damage_instance.clear();
        
        for(int i=1;i<=Total_enemy;i++){    
            Temp_mx+=ptr->Normal_Damage[i];
            ptr->Normal_Damage[i] = 0;
        }
        for(int i=1;i<=Total_enemy;i++){
            Temp_mx+=ptr->Break_damage[i];
            ptr->Break_damage[i] = 0;
        }
        for(int i=1;i<=Total_enemy;i++){
            Temp_mx+=ptr->Dot_damage[i];
            ptr->Dot_damage[i] = 0;
        }
        for(int i=1;i<=Total_enemy;i++){
            Temp_mx+=ptr->Superbreak_damage[i];
            ptr->Superbreak_damage[i] = 0;
        }
        return 0;
    }
    // cout<<ptr->Current_sub_choose<<endl;
    // cout<<ptr->Current_spilt<<endl;
    // cout<<ptr->Total_damage<<endl;


    if(ptr->Current_spilt==0){
        ptr->Current_spilt = 1;
        return 1;
    }
    
    if(ptr->Total_damage > ptr->Max){
        ptr->Max = ptr->Total_damage;
        ptr->Max_Average_Damage = ptr->Average_Damage;
        for(int i=0,sz = ptr->Max_damage_Substats.size();i<sz;i++){
            ptr->Max_damage_Substats[i] = ptr->Substats[i].second;
            ptr->Stop_reroll = 0;
        }
    }
    ptr->Total_damage = 0;
    ptr->Average_Damage = 0;
    ptr->Average_damage_instance.clear();
    
    for(int i=1;i<=Total_enemy;i++){
        ptr->Normal_Damage[i] = 0;
    }
    for(int i=1;i<=Total_enemy;i++){
        ptr->Break_damage[i] = 0;
    }
    for(int i=1;i<=Total_enemy;i++){
        ptr->Dot_damage[i] = 0;
    }
    for(int i=1;i<=Total_enemy;i++){
        ptr->Superbreak_damage[i] = 0;
    }
    
    if(ptr->Current_sub_choose+1==ptr->Current_spilt){
        
        if(1 == ptr->Stop_reroll||ptr->Separate_sub==0){
            ptr->Current_spilt++;
            if(ptr->Current_spilt==ptr->Substats.size()){
                ptr->Reroll_check=0;
                for(int i=0,sz = ptr->Max_damage_Substats.size();i<sz;i++){
                    ptr->Substats[i].second = ptr->Max_damage_Substats[i];
                }
                return 0;
            }
            ptr->Separate_sub = ptr->Total_substats-1;
            ptr->Current_sub_choose = 0;
            ptr->Stop_reroll = 1;

            ptr->Substats[0].second = ptr->Max_damage_Substats[0]-1;
            for(int i=1;i<ptr->Current_spilt;i++){
                ptr->Substats[i].second = ptr->Max_damage_Substats[i];
            }
            ptr->Substats[ptr->Current_spilt].second = ptr->Max_damage_Substats[ptr->Current_spilt]+1;
        
            
        }else{
        --ptr->Separate_sub;
        ptr->Current_sub_choose = 0;
        ptr->Stop_reroll = 1;
        ptr->Substats[0].second = ptr->Max_damage_Substats[0]-1;
        for(int i=1;i<ptr->Current_spilt;i++){
            ptr->Substats[i].second = ptr->Max_damage_Substats[i];
        }
        ptr->Substats[ptr->Current_spilt].second = ptr->Max_damage_Substats[ptr->Current_spilt]+1;
        }
    }else{
        ptr->Substats[ptr->Current_sub_choose].second++;
        ++ptr->Current_sub_choose;
        ptr->Substats[ptr->Current_sub_choose].second--;

    }
    return 1;

}
#endif