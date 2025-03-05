#ifndef COMBAT_H
#define COMBAT_H
#include<bits/stdc++.h>
#include"Print.h"
#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
#define K_const 10000


bool Ult_use_check(Ally *ptr){
    if(ptr->Ult_cost<=ptr->Current_energy){
        ptr->Current_energy = ptr->Current_energy - ptr->Ult_cost;
        Increase_energy(ptr,5);
        return true;
    }
    return false;
}
void Attack(Combat_data &data_){
    int Total_hit = 0;
    int temp = 0;
    unordered_map<string,int> Total_hit_each;
    string Current_Attack_Name = data_.Attacker->Atv_stats->Char_Name;
    

    for(int i=0, sz1 = data_.Damage_spilt.Main.size(),sz2 = data_.Damage_spilt.Adjacent.size(),sz3 = data_.Damage_spilt.Other.size();i<sz1;i++){
        if(temp!=data_.Joint.size()&&data_.Joint[temp].first==i){
            data_.Attacker = data_.Joint[temp].second;
            Current_Attack_Name = data_.Attacker->Atv_stats->Char_Name;
            ++temp;
        }
        for(auto Enemy_target : data_.Target_Attack){
            if(Enemy_target->Target_type=="Main"&&(data_.Damage_spilt.Main[i].Atk_ratio!=0||data_.Damage_spilt.Main[i].Hp_ratio!=0||data_.Damage_spilt.Main[i].Def_ratio!=0)){
                Total_hit++;
                Total_hit_each[Current_Attack_Name]++;
            }else if(i<sz2 && Enemy_target->Target_type=="Adjacent"&&(data_.Damage_spilt.Adjacent[i].Atk_ratio!=0||data_.Damage_spilt.Adjacent[i].Hp_ratio!=0||data_.Damage_spilt.Adjacent[i].Def_ratio!=0)){
                Total_hit++;
                Total_hit_each[Current_Attack_Name]++;
            }else if(i<sz3 && Enemy_target->Target_type=="Other"&&(data_.Damage_spilt.Other[i].Atk_ratio!=0||data_.Damage_spilt.Other[i].Hp_ratio!=0||data_.Damage_spilt.Other[i].Def_ratio!=0)){
                Total_hit++;
                Total_hit_each[Current_Attack_Name]++;
            }
        }
        Attack_hit(data_,Total_hit_each[Current_Attack_Name],Total_hit);
        for(auto Enemy_target : data_.Target_Attack){
            if(Enemy_target->Target_type=="Main"){
            Cal_Damage(data_,Enemy_target,data_.Damage_spilt.Main[i]);
            Cal_Toughness_reduction(data_,Enemy_target,data_.Damage_spilt.Main[i].Toughness_ratio);
            }
            
            if(i<sz2 && Enemy_target->Target_type=="Adjacent"){
            Cal_Damage(data_,Enemy_target,data_.Damage_spilt.Adjacent[i]);
            Cal_Toughness_reduction(data_,Enemy_target,data_.Damage_spilt.Adjacent[i].Toughness_ratio);
            }
            
            if(i<sz3 && Enemy_target->Target_type=="Other"){
            Cal_Damage(data_,Enemy_target,data_.Damage_spilt.Other[i]);
            Cal_Toughness_reduction(data_,Enemy_target,data_.Damage_spilt.Other[i].Toughness_ratio);
            }    
        }
    }
}
void Before_turn(){
    Combat_data temp = Combat_data();
    if(turn->Side=="Enemy"){
        Dot_trigger(100,Enemy_unit[turn->Unit_num].get(),"None");
        if(Enemy_unit[turn->Unit_num]->Entanglement != 0){
            temp.Entanglement_set(Ally_unit[Enemy_unit[turn->Unit_num]->Entanglement]->Sub_Unit_ptr[0].get());
            double Const = 0.6*Enemy_unit[turn->Unit_num]->Entanglement_stack;
            Cal_Break_damage(temp,Enemy_unit[turn->Unit_num].get(),Const);
        }
        if(Enemy_unit[turn->Unit_num]->Freeze != 0){
            
            temp.Freeze_set(Ally_unit[Enemy_unit[turn->Unit_num]->Freeze]->Sub_Unit_ptr[0].get());
            
            Cal_Freeze_damage(temp,Enemy_unit[turn->Unit_num].get());
            Action_forward(Enemy_unit[turn->Unit_num]->Atv_stats.get(),-50);
            Turn_Skip=1;
        }
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Char_func.Before_turn_func)
        Ally_unit[i]->Char_func.Before_turn_func(Ally_unit[i].get());

        if(Ally_unit[i]->Light_cone.Before_turn_func)
        Ally_unit[i]->Light_cone.Before_turn_func(Ally_unit[i].get());

        if(Ally_unit[i]->Relic.Before_turn_func)
        Ally_unit[i]->Relic.Before_turn_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->Planar.Before_turn_func)
        Ally_unit[i]->Planar.Before_turn_func(Ally_unit[i].get());
    }
}
void After_turn(){
    if(turn->Side=="Enemy"){
        if(Enemy_unit[turn->Unit_num]->Entanglement != 0){
           Enemy_unit[turn->Unit_num]->Entanglement = 0;
           Enemy_unit[turn->Unit_num]->Entanglement_stack = 0;
           --Enemy_unit[turn->Unit_num]->Total_debuff;
        }
        if(Enemy_unit[turn->Unit_num]->Freeze != 0){
            Enemy_unit[turn->Unit_num]->Freeze = 0;
           --Enemy_unit[turn->Unit_num]->Total_debuff;
        }
        if(Enemy_unit[turn->Unit_num]->Imprisonment != 0){
           Enemy_unit[turn->Unit_num]->Imprisonment = 0;
           Speed_Buff(Enemy_unit[turn->Unit_num]->Atv_stats.get(),10,0);
           --Enemy_unit[turn->Unit_num]->Total_debuff;
        }
        if(Enemy_unit[turn->Unit_num]->Bleed > 0){
           Enemy_unit[turn->Unit_num]->Bleed--;
           if(Enemy_unit[turn->Unit_num]->Bleed==0){
            Enemy_unit[turn->Unit_num]->Bleeder = 0;
            --Enemy_unit[turn->Unit_num]->Total_debuff;
           }
        }
        if(Enemy_unit[turn->Unit_num]->Burn > 0){
           Enemy_unit[turn->Unit_num]->Burn--;
           if(Enemy_unit[turn->Unit_num]->Burn==0){
            Enemy_unit[turn->Unit_num]->Burner = 0;
            --Enemy_unit[turn->Unit_num]->Total_debuff;
           }
        }
        if(Enemy_unit[turn->Unit_num]->Shock > 0){
           Enemy_unit[turn->Unit_num]->Shock--;
           if(Enemy_unit[turn->Unit_num]->Shock==0){
            Enemy_unit[turn->Unit_num]->Shocker = 0;
            --Enemy_unit[turn->Unit_num]->Total_debuff;
           }
        }
        if(Enemy_unit[turn->Unit_num]->Wind_shear > 0){
           Enemy_unit[turn->Unit_num]->Wind_shear--;
           if(Enemy_unit[turn->Unit_num]->Wind_shear==0){
            Enemy_unit[turn->Unit_num]->Wind_shearer = 0;
            Enemy_unit[turn->Unit_num]->Wind_shear_stack = 0;
            --Enemy_unit[turn->Unit_num]->Total_debuff;
           }
        }
    }
    for(int i=1;i<=Total_ally;i++){
        
        if(Ally_unit[i]->Char_func.After_turn_func)
        Ally_unit[i]->Char_func.After_turn_func(Ally_unit[i].get());

        if(Ally_unit[i]->Light_cone.After_turn_func)
        Ally_unit[i]->Light_cone.After_turn_func(Ally_unit[i].get());

        if(Ally_unit[i]->Relic.After_turn_func)
        Ally_unit[i]->Relic.After_turn_func(Ally_unit[i].get());
        
        if(Ally_unit[i]->Planar.After_turn_func)
        Ally_unit[i]->Planar.After_turn_func(Ally_unit[i].get());
    }
}
void Buff(Combat_data &data_){
    for(int i=1;i<=Total_ally;i++){
        
        if(Ally_unit[i]->Char_func.Buff_func)
        Ally_unit[i]->Char_func.Buff_func(Ally_unit[i].get(),data_);
        
        if(Ally_unit[i]->Light_cone.Buff_func)
        Ally_unit[i]->Light_cone.Buff_func(Ally_unit[i].get(),data_);
        if(Ally_unit[i]->Relic.Buff_func)
        Ally_unit[i]->Relic.Buff_func(Ally_unit[i].get(),data_);
        
        if(Ally_unit[i]->Planar.Buff_func)
        Ally_unit[i]->Planar.Buff_func(Ally_unit[i].get(),data_);
    }
}
void Before_attack(Combat_data &data_){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Char_func.Before_attack_func)
        Ally_unit[i]->Char_func.Before_attack_func(Ally_unit[i].get(),data_);

        if(Ally_unit[i]->Light_cone.Before_attack_func)
        Ally_unit[i]->Light_cone.Before_attack_func(Ally_unit[i].get(),data_);

        if(Ally_unit[i]->Relic.Before_attack_func)
        Ally_unit[i]->Relic.Before_attack_func(Ally_unit[i].get(),data_);
        
        if(Ally_unit[i]->Planar.Before_attack_func)
        Ally_unit[i]->Planar.Before_attack_func(Ally_unit[i].get(),data_);
    }
}
void After_attack(Combat_data &data_){
    for(int i=1;i<=Total_ally;i++){
        
        if(Ally_unit[i]->Char_func.After_attack_func)
        Ally_unit[i]->Char_func.After_attack_func(Ally_unit[i].get(),data_);
        if(Ally_unit[i]->Light_cone.After_attack_func)
        Ally_unit[i]->Light_cone.After_attack_func(Ally_unit[i].get(),data_);

        if(Ally_unit[i]->Relic.After_attack_func)
        Ally_unit[i]->Relic.After_attack_func(Ally_unit[i].get(),data_);
        
        if(Ally_unit[i]->Planar.After_attack_func)
        Ally_unit[i]->Planar.After_attack_func(Ally_unit[i].get(),data_);
    }
}
void When_attack(Combat_data &data_){
    
    for(int i=1;i<=Total_ally;i++){
        
        if(Ally_unit[i]->Char_func.When_attack_func)
        Ally_unit[i]->Char_func.When_attack_func(Ally_unit[i].get(),data_);
        if(Ally_unit[i]->Light_cone.When_attack_func)
        Ally_unit[i]->Light_cone.When_attack_func(Ally_unit[i].get(),data_);

        if(Ally_unit[i]->Relic.When_attack_func)
        Ally_unit[i]->Relic.When_attack_func(Ally_unit[i].get(),data_);
        
        if(Ally_unit[i]->Planar.When_attack_func)
        Ally_unit[i]->Planar.When_attack_func(Ally_unit[i].get(),data_);
    }
}
void When_Toughness_break(Combat_data &data_,Enemy *target){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Char_func.Toughness_break_func)
        Ally_unit[i]->Char_func.Toughness_break_func(Ally_unit[i].get(),target,data_.Attacker);

        if(Ally_unit[i]->Light_cone.Toughness_break_func)
        Ally_unit[i]->Light_cone.Toughness_break_func(Ally_unit[i].get(),target,data_.Attacker);

        if(Ally_unit[i]->Relic.Toughness_break_func)
        Ally_unit[i]->Relic.Toughness_break_func(Ally_unit[i].get(),target,data_.Attacker);
        
        if(Ally_unit[i]->Planar.Toughness_break_func)
        Ally_unit[i]->Planar.Toughness_break_func(Ally_unit[i].get(),target,data_.Attacker);
    }
}
void Enemy_hit(double energy,Enemy *target){
    for(int i=1;i<=Total_ally;i++){
            Increase_energy(Ally_unit[i].get(),energy);
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Char_func.Enemy_hit_func)
        Ally_unit[i]->Char_func.Enemy_hit_func(Ally_unit[i].get(),target);

        if(Ally_unit[i]->Light_cone.Enemy_hit_func)
        Ally_unit[i]->Light_cone.Enemy_hit_func(Ally_unit[i].get(),target);

        if(Ally_unit[i]->Relic.Enemy_hit_func)
        Ally_unit[i]->Relic.Enemy_hit_func(Ally_unit[i].get(),target);
        
        if(Ally_unit[i]->Planar.Enemy_hit_func)
        Ally_unit[i]->Planar.Enemy_hit_func(Ally_unit[i].get(),target);
    }
}
void When_Energy_Increase(Ally *target,double Energy){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Char_func.When_Energy_Increase_func)
        Ally_unit[i]->Char_func.When_Energy_Increase_func(Ally_unit[i].get(),target,Energy);

        if(Ally_unit[i]->Light_cone.When_Energy_Increase_func)
        Ally_unit[i]->Light_cone.When_Energy_Increase_func(Ally_unit[i].get(),target,Energy);

        if(Ally_unit[i]->Relic.When_Energy_Increase_func)
        Ally_unit[i]->Relic.When_Energy_Increase_func(Ally_unit[i].get(),target,Energy);
        
        if(Ally_unit[i]->Planar.When_Energy_Increase_func)
        Ally_unit[i]->Planar.When_Energy_Increase_func(Ally_unit[i].get(),target,Energy);
    }
}

void Deal_damage(){
    while(!Action_bar.empty()){
        Combat_data temp = Action_bar.front();
        
        if(temp.Action_type.first =="Attack"){
            
            Before_attack(temp);
            
            Attack(temp);
            
            if(temp.Turn_reset ==1){
                atv_reset(turn);
            }
            
            for(int i=0;i<temp.Attack_trigger;i++){
                temp.Attacker = temp.All_Attacker[i];
                When_attack(temp);
            }
            temp.Attacker = temp.All_Attacker[0];
            After_attack(temp);  
            
            
              
            


        }else if(temp.Action_type.first =="Buff"){
            
            if(temp.Turn_reset ==1){
                atv_reset(turn);
            }
            
            Buff(temp);
            
        }
        Action_bar.pop();
    }
    if(turn!=nullptr&&turn->Side=="Enemy"){
        atv_reset(turn);
    }
}
void Take_action(){
    
    ++(turn->turn_cnt);
    Ult_After_Turn = 0;
    After_Turn_Check = 0;
    Before_turn();
    All_ult_check();
    
    Print();
    if(Turn_Skip==0){
        
        turn->ptr_to_unit->Turn_func(turn->ptr_to_unit);  
        Deal_damage();
        
        
    }
    
    Ult_After_Turn = 1;
    
    
    All_ult_check();
    After_Turn_Check = 1;
    
    After_turn();
    

}
void All_ult_check(){
    ult_priority = 3;
    for(int j=ult_priority*(-1);j<=ult_priority;ult_priority--){
        for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Ult_priority==ult_priority)Ally_unit[i]->Ult_func(Ally_unit[i].get());
    }
    }
}
void Skill_point(Sub_Unit *ptr,int p){
    
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Char_func.Skill_point_func)
        Ally_unit[i]->Char_func.Skill_point_func(Ally_unit[i].get(),ptr,p);

        if(Ally_unit[i]->Light_cone.Skill_point_func)
        Ally_unit[i]->Light_cone.Skill_point_func(Ally_unit[i].get(),ptr,p);
        
        if(Ally_unit[i]->Relic.Skill_point_func)
        Ally_unit[i]->Relic.Skill_point_func(Ally_unit[i].get(),ptr,p);
        
        if(Ally_unit[i]->Planar.Skill_point_func)
        Ally_unit[i]->Planar.Skill_point_func(Ally_unit[i].get(),ptr,p);
    }
    sp+=p;
    if(sp>Max_sp){
        sp = Max_sp;
    }
    return ;
}
void Attack_hit(Combat_data &data_,int Hit_cnt,int Total_Hit_cnt){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Char_func.Hit_func)
        Ally_unit[i]->Char_func.Hit_func(Ally_unit[i].get(),data_,Hit_cnt,Total_Hit_cnt);

        if(Ally_unit[i]->Light_cone.Hit_func)
        Ally_unit[i]->Light_cone.Hit_func(Ally_unit[i].get(),data_,Hit_cnt,Total_Hit_cnt);

        if(Ally_unit[i]->Relic.Hit_func)
        Ally_unit[i]->Relic.Hit_func(Ally_unit[i].get(),data_,Hit_cnt,Total_Hit_cnt);

        if(Ally_unit[i]->Planar.Hit_func)
        Ally_unit[i]->Planar.Hit_func(Ally_unit[i].get(),data_,Hit_cnt,Total_Hit_cnt);
    }
}
void Apply_debuff(Sub_Unit *ptr,Enemy* target){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Char_func.Apply_debuff_func)
        Ally_unit[i]->Char_func.Apply_debuff_func(Ally_unit[i].get(),target,ptr);

        if(Ally_unit[i]->Light_cone.Apply_debuff_func)
        Ally_unit[i]->Light_cone.Apply_debuff_func(Ally_unit[i].get(),target,ptr);
        
        if(Ally_unit[i]->Relic.Apply_debuff_func)
        Ally_unit[i]->Relic.Apply_debuff_func(Ally_unit[i].get(),target,ptr);
        
        if(Ally_unit[i]->Planar.Apply_debuff_func)
        Ally_unit[i]->Planar.Apply_debuff_func(Ally_unit[i].get(),target,ptr);
    }
}
void When_Enemy_Death(Sub_Unit *Killer,Enemy *target){
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Char_func.Enemy_Death_func)
        Ally_unit[i]->Char_func.Enemy_Death_func(Ally_unit[i].get(),target,Killer);

        if(Ally_unit[i]->Light_cone.Enemy_Death_func)
        Ally_unit[i]->Light_cone.Enemy_Death_func(Ally_unit[i].get(),target,Killer);
        
        if(Ally_unit[i]->Relic.Enemy_Death_func)
        Ally_unit[i]->Relic.Enemy_Death_func(Ally_unit[i].get(),target,Killer);
        
        if(Ally_unit[i]->Planar.Enemy_Death_func)
        Ally_unit[i]->Planar.Enemy_Death_func(Ally_unit[i].get(),target,Killer);
    }
}
void Superbreak_trigger(Combat_data &data_, double Superbreak_ratio){
    Combat_data data_2 = Combat_data();
    data_2.SuperBreak_set(data_.Attacker,data_.Target_Type);
    
    for(int i=1;i<=Total_enemy;i++){
        double toughness_reduce=0;
        if(Enemy_unit[i]->Toughness_status==1)continue;
        if(Enemy_unit[i]->Target_type=="Main"){
            for(int j=0,sz=data_.Damage_spilt.Main.size();j<sz;j++){
                toughness_reduce+=data_.Damage_spilt.Main[j].Toughness_ratio;
            }
            
        }
            
        if(Enemy_unit[i]->Target_type=="Adjacent"){
            for(int j=0,sz=data_.Damage_spilt.Adjacent.size();j<sz;j++){
                toughness_reduce+=data_.Damage_spilt.Adjacent[j].Toughness_ratio;
            }
            
        }
            
        if(Enemy_unit[i]->Target_type=="Other"){
            for(int j=0,sz=data_.Damage_spilt.Other.size();j<sz;j++){
                toughness_reduce+=data_.Damage_spilt.Other[j].Toughness_ratio;
            }
            
        }
        if(toughness_reduce==0)continue;
        toughness_reduce = Cal_Total_Toughness_Reduce(data_,Enemy_unit[i].get(),toughness_reduce);
        if(Enemy_unit[i]->Current_toughness+toughness_reduce<=0){
        Cal_Superbreak_damage(data_2,Enemy_unit[i].get(),Superbreak_ratio*toughness_reduce/10);
        }else{
        Cal_Superbreak_damage(data_2,Enemy_unit[i].get(),Superbreak_ratio*(-1)*Enemy_unit[i]->Current_toughness/10);
        }
    }
}

void Dot_trigger(double Dot_ratio,Enemy *target,string Dot_type){
    Combat_data data_;
    data_.Skill_Type.push_back("Dot");
    
    data_.Action_type.first = "Attack";
    data_.Action_type.second = "Dot";
    data_.Target_Type = "Single_target";
    
    if(target->Bleed > 0&&Dot_type=="None"&&"Physical"){
        data_.Attacker=Ally_unit[target->Bleeder]->Sub_Unit_ptr[0].get();
        data_.Damage_element = "Physical";
        data_.Skill_Type.push_back("Bleed");
        Cal_Dot_Toughness_break_damage(data_,target,Dot_ratio*2*(0.5+target->Max_toughness/40));
    }
    if(target->Burn > 0&&Dot_type=="None"&&"Fire"){
        data_.Attacker=Ally_unit[target->Burner]->Sub_Unit_ptr[0].get();
        data_.Damage_element = "Fire";
        data_.Skill_Type.resize(0);
        data_.Skill_Type.push_back("Burn");
        Cal_Dot_Toughness_break_damage(data_,target,Dot_ratio*1);
    }
    if(target->Shock > 0&&Dot_type=="None"&&"Lightning"){
        data_.Attacker=Ally_unit[target->Shocker]->Sub_Unit_ptr[0].get();
        
        data_.Damage_element = "Lightning";
        data_.Skill_Type.resize(0);
        data_.Skill_Type.push_back("Shock");
        Cal_Dot_Toughness_break_damage(data_,target,Dot_ratio*2);
    }
    if(target->Wind_shear > 0&&Dot_type=="None"&&"Wind"){
        data_.Attacker=Ally_unit[target->Wind_shearer]->Sub_Unit_ptr[0].get();
        data_.Skill_Type.resize(0);
        data_.Damage_element = "Wind";
        data_.Skill_Type.push_back("Wind_shear");
        Cal_Dot_Toughness_break_damage(data_,target,Dot_ratio*1*target->Wind_shear_stack);
    }
    for(int i=1;i<=Total_ally;i++){
        if(Ally_unit[i]->Char_func.Dot_func)
        Ally_unit[i]->Char_func.Dot_func(target,Ally_unit[i].get(),Dot_ratio,Dot_type);

        if(Ally_unit[i]->Light_cone.Dot_func)
        Ally_unit[i]->Light_cone.Dot_func(target,Ally_unit[i].get(),Dot_ratio,Dot_type);

        if(Ally_unit[i]->Relic.Dot_func)
        Ally_unit[i]->Relic.Dot_func(target,Ally_unit[i].get(),Dot_ratio,Dot_type);
        
        if(Ally_unit[i]->Planar.Dot_func)
        Ally_unit[i]->Planar.Dot_func(target,Ally_unit[i].get(),Dot_ratio,Dot_type);
    }
}
void Toughness_break(Combat_data &data_,Enemy* target){
    Sub_Unit *temp1;
    string temp2;
    if(Force_break!=0){
        temp1 = data_.Attacker;
        temp2 = data_.Damage_element;
        data_.Attacker = Ally_unit[Force_break]->Sub_Unit_ptr[0].get();
        data_.Damage_element = Ally_unit[Force_break]->Sub_Unit_ptr[0]->Element_type[0];
    }
    double Constant = 0;
    Combat_data data_2 = Combat_data();
    data_2.Break_dmg_set(data_.Attacker);
    ++target->Total_debuff;
    Apply_debuff(data_.Attacker,target);
    

    if(SuperBreak__Mode==1){
        target->Atv_stats->atv=target->Atv_stats->Max_atv*0.5;
    }

    if(data_.Damage_element=="Physical"){
        Action_forward(target->Atv_stats.get(),-25);
        target->Bleed = 2;
        target->Bleeder =data_.Attacker->Atv_stats->Unit_num;
        Constant=2;

    }else if(data_.Damage_element=="Fire"){
        Action_forward(target->Atv_stats.get(),-25);
        target->Burn = 2;
        target->Burner =data_.Attacker->Atv_stats->Unit_num;
        Constant=2;

    }else if(data_.Damage_element=="Ice"){
        Action_forward(target->Atv_stats.get(),-25);
        target->Freeze = data_.Attacker->Atv_stats->Unit_num;
        Constant=1;

    }else if(data_.Damage_element=="Lightning"){
        Action_forward(target->Atv_stats.get(),-25);
        target->Shock = 2;
        target->Shocker =data_.Attacker->Atv_stats->Unit_num;
        Constant=1;

    }else if(data_.Damage_element=="Wind"){
        Action_forward(target->Atv_stats.get(),-25);
        target->Wind_shear = 2;
        target->Wind_shearer =data_.Attacker->Atv_stats->Unit_num;
        if(target->Wind_shear_stack>=3){
            target->Wind_shear_stack=5;
        }else { target->Wind_shear_stack=3;}
        Constant=1.5;

    }else if(data_.Damage_element=="Quantum"){
        Action_forward(target->Atv_stats.get(),-20*Cal_BreakEffect_multiplier(data_,target));
        target->Entanglement = data_.Attacker->Atv_stats->Unit_num;
        target->Entanglement_stack = 0;
        Constant=0.5;

    }else if(data_.Damage_element=="Imaginary"){
        Action_forward(target->Atv_stats.get(),-30*Cal_BreakEffect_multiplier(data_,target));
        Speed_Buff(target->Atv_stats.get(),-10,0);
        target->Imprisonment = data_.Attacker->Atv_stats->Unit_num;
        Constant=0.5;
    }
        
    
    Cal_Break_damage(data_2,target,Constant);
    target->Toughness_status=0;
    When_Toughness_break(data_,target);

    if(Force_break!=0){
        data_.Attacker = temp1;
        data_.Damage_element = temp2;
    }
    
}
#endif