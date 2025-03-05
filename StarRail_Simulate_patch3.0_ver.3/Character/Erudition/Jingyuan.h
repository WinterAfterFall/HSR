
#ifndef Jingyuan_H
#define Jingyuan_H

#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Jingyuan{
    void Setup_Jingyuan(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Basic_Atk(Ally *ptr);
    void Skill(Ally *ptr);
    void After_turn(Ally *ptr);
    void Start_game(Ally *ptr);
    void Ult_func(Ally *ptr);//*
    void Fix_Slow_Jingyuan(Ally *ptr);
    bool Temp_Turn_Condition(Unit *ptr);
    bool Robin_temp(Ally *ptr);
    bool Temp_ult_Condition(Ally *ptr);

    /*
    void Setup_Jingyuan(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void Before_attack(Ally *ptr, Combat_data &data_);
    void After_attack(Ally *ptr, Combat_data &data_);
    void Buff_func(Ally *ptr, Combat_data &data_);
    void Dot_func(Enemy *target, Ally *ptr, double Dot_ratio);
    void Toughness_break_func(Ally *ptr, Enemy *target, int num);
    void Enemy_hit_func(Ally *ptr, Enemy *target);
    void Start_game(Ally *ptr);
    void Start_wave(Ally *ptr);
    void Apply_debuff_func(Ally *ptr, Enemy *target, int total_debuff);
    void Hit_func(Ally *ptr, int Hit_cnt);
    void Ult_func(Ally *ptr);//*
    */
    void Fix_Slow_Jingyuan(Ally *ptr){

        ptr->Total_substats=20;
        ptr->Separate_sub=20;
        ptr->Substats[0].second = 20;

        ptr->Char_func.Reset_func = [](Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=28;
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=12;
        ptr->Sub_Unit_ptr[0]->Stats_type["Def%"]["None"]+=12.5;


        //relic
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=32.4;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Sub_Unit_ptr[0]->Stats_each_element["Dmg%"]["Lightning"]["None"]+=38.8;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;


        //LL
        ptr->Sub_Unit_ptr[0]->Stack["LL_stack"]=3;
        ptr->Summon_ptr[0]->Atv_stats->Flat_speed=0;
        ptr->Summon_ptr[0]->Atv_stats->Speed_percent=0;
        };

    }
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=28;
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=12;
        ptr->Sub_Unit_ptr[0]->Stats_type["Def%"]["None"]+=12.5;


        //relic
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=32.4;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        ptr->Sub_Unit_ptr[0]->Stats_each_element["Dmg%"]["Lightning"]["None"]+=38.8;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;

        //substats
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=11.5;

        //LL
        ptr->Sub_Unit_ptr[0]->Stack["LL_stack"]=3;
        ptr->Summon_ptr[0]->Atv_stats->Flat_speed=0;
        ptr->Summon_ptr[0]->Atv_stats->Speed_percent=0;

        
    }
    void Setup_Jingyuan(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->Sub_Unit_ptr[0]->Base_hp = 1164;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_atk = 698;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_def = 485;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Base_speed = 99;
        Ally_unit[num]->Max_energy = 130;
        Ally_unit[num]->Ult_cost = 130;
        Ally_unit[num]->Eidolon = E;
        Ally_unit[num]->Sub_Unit_ptr[0]->Element_type.push_back("Lightning");
        Ally_unit[num]->Path.push_back("Erudition");
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_num = num;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Char_Name = "Jingyuan";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_Name = "Jingyuan";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->ptr_to_unit = Ally_unit[num]->Sub_Unit_ptr[0].get();
        Ally_unit[num]->Ult_priority -=2;
        

        //substats
        Ally_unit[num]->Total_substats=15;
        Ally_unit[num]->Separate_sub=15;
        Ally_unit[num]->Reroll_check=1;
        Ally_unit[num]->Substats.push_back({"Crit_dam",15});
        Ally_unit[num]->Substats.push_back({"Crit_rate",0});
        Ally_unit[num]->Substats.push_back({"Atk%",0});

        Ally_unit[num]->Max_damage_Substats.resize(Ally_unit[num]->Substats.size());


        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        Ally_unit[num]->Sub_Unit_ptr[0]->Turn_func = Turn_func;
        Ally_unit[num]->Ult_func = Ult_func;
        Ally_unit[num]->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->Char_func.Start_game_func = Start_game;
        Ally_unit[num]->Char_func.Reset_func = Reset;

        //LL
        Ally_unit[num]->Summon_ptr.resize(1);
        Ally_unit[num]->Summon_ptr[0] =  make_unique<Unit>();
        Ally_unit[num]->Summon_ptr[0]->Atv_stats->Base_speed = 60;
        Ally_unit[num]->Summon_ptr[0]->Atv_stats->Unit_num = num;
        Ally_unit[num]->Summon_ptr[0]->Atv_stats->Char_Name = "LL";
        Ally_unit[num]->Summon_ptr[0]->Atv_stats->Side = "Summon";
        Ally_unit[num]->Summon_ptr[0]->Atv_stats->Unit_Name = "Jingyuan";
        Ally_unit[num]->Summon_ptr[0]->Atv_stats->ptr_to_unit = Ally_unit[num]->Summon_ptr[0].get();
        Ally_unit[num]->Summon_ptr[0]->Turn_func = [](Unit *ptr){
            Ally *ally_ptr = Ally_unit[ptr->Atv_stats->Unit_num].get();
            if(ally_ptr->Sub_Unit_ptr[0]->Stack["LL_stack"]>=6){
                ally_ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["Summon"]+=25;
            }
            Combat_data temp = Combat_data();
            temp.Fua_set(ally_ptr->Sub_Unit_ptr[0].get(),"Bounce");
            temp.Add_Target_Adjacent();
            temp.Skill_Type.push_back("Summon");
            temp.Turn_reset = 1;
            //cout<<"                         LL stack = "<<Ally_unit[1]->stats->Stack["LL_stack"]<<endl;
            for(int i=1;i<=ally_ptr->Sub_Unit_ptr[0]->Stack["LL_stack"];i++){
                temp.Damage_spilt.Main.push_back({66,0,0,5});
                if(ally_ptr->Eidolon>=1){
                    temp.Damage_spilt.Adjacent.push_back({33,0,0,0});
                }else{
                    temp.Damage_spilt.Adjacent.push_back({66*0.25,0,0,0});
                }
                
            }

            if(ally_ptr->Sub_Unit_ptr[0]->Stack["LL_stack"]>=6){
                ally_ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["Summon"]-=25;
            }
    
            turn->Flat_speed = 0;
            ally_ptr->Sub_Unit_ptr[0]->Stack["LL_stack"] = 3;
            
            
            if(ally_ptr->Eidolon>=2){
            Extend_Buff_single_target(ally_ptr->Sub_Unit_ptr[0].get(),"Swing_Skies_Squashed",2);
            
            if(!Buff_check(ally_ptr->Sub_Unit_ptr[0].get(),"Swing_Skies_Squashed")){
                ally_ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Basic_Attack"]+=20;
                ally_ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Skill"]+=20;
                ally_ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Ultimate"]+=20;
                ally_ptr->Sub_Unit_ptr[0]->Buff_check["Swing_Skies_Squashed"] = 1;
            }
            }
            Action_bar.push(temp);
            

        };

        
        

         
            
    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        if((sp<=Sp_Safety && Robin_temp(ally_ptr->ptr_to_unit)||ally_ptr->Atv_stats->turn_cnt==1)&&Sp_status=="Negative"){
            Basic_Atk(ally_ptr->ptr_to_unit);
        }else{
            Skill(ally_ptr->ptr_to_unit);
        }
    }
    void Basic_Atk(Ally *ptr){
        Increase_energy(Ally_unit[ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num].get(),20);
        Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
        Combat_data data_ = Combat_data();
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");
        data_.Add_Target(Choose_Enemy_target(ptr->Sub_Unit_ptr[0].get()));
        data_.Turn_reset=true;
        data_.Damage_spilt.Main.push_back({55,0,0,5.5});
        data_.Damage_spilt.Main.push_back({45,0,0,4.5});
        Action_bar.push(data_);
    }
    void Skill(Ally *ptr){
        Increase_energy(Ally_unit[ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num].get(),30);
        Skill_point(ptr->Sub_Unit_ptr[0].get(),-1);
        Combat_data data_ = Combat_data();
        data_.Skill_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
        data_.Add_Target_Other();
        data_.Turn_reset=true;
        data_.Damage_spilt.Main.push_back({40,0,0,4});
        data_.Damage_spilt.Main.push_back({30,0,0,3});
        data_.Damage_spilt.Main.push_back({30,0,0,3});

        data_.Damage_spilt.Adjacent.push_back({40,0,0,4});
        data_.Damage_spilt.Adjacent.push_back({30,0,0,3});
        data_.Damage_spilt.Adjacent.push_back({30,0,0,3});

        data_.Damage_spilt.Other.push_back({40,0,0,4});
        data_.Damage_spilt.Other.push_back({30,0,0,3});
        data_.Damage_spilt.Other.push_back({30,0,0,3});
        Action_bar.push(data_);
        if(!Buff_check(ptr->Sub_Unit_ptr[0].get(),"War_Marshal")){
            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=10;
            ptr->Sub_Unit_ptr[0]->Buff_check["War_Marshal"]=1;

        }
        Extend_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"War_Marshal",2);
        ptr->Sub_Unit_ptr[0]->Stack["LL_stack"]+=2;
        if(ptr->Sub_Unit_ptr[0]->Stack["LL_stack"]>=10){
            ptr->Summon_ptr[0]->Atv_stats->Flat_speed=70;
            Speed_Buff(ptr->Summon_ptr[0]->Atv_stats.get(),0,0);
        }else{
            Speed_Buff(ptr->Summon_ptr[0]->Atv_stats.get(),0,20);
        }
    }

    void Ult_func(Ally *ptr){
        if(((turn->Char_Name!="Jingyuan"||Ult_After_Turn==1)&&Robin_temp(ptr)) || !Ult_use_check(ptr))return;
            Combat_data data_ = Combat_data();
            if(ptr->Print)cout<<"--------------------------------------------------- Jingyuan Ult"<<endl;
            data_.Ultimate_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
            data_.Add_Target_Other();
            data_.Damage_spilt.Main.push_back({200,0,0,20});
            data_.Damage_spilt.Adjacent.push_back({200,0,0,20});
            data_.Damage_spilt.Other.push_back({200,0,0,20});
            ptr->Sub_Unit_ptr[0]->Stack["LL_stack"]+=3;
            if(ptr->Sub_Unit_ptr[0]->Stack["LL_stack"]>=10){
            ptr->Summon_ptr[0]->Atv_stats->Flat_speed=70;
            Speed_Buff(ptr->Summon_ptr[0]->Atv_stats.get(),0,0);
        }else{
            Speed_Buff(ptr->Summon_ptr[0]->Atv_stats.get(),0,30);
        }
            Action_bar.push(data_);
            Deal_damage();
    }
    void After_turn(Ally *ptr){
        if(!(ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num == turn->Unit_num && turn->Side=="Ally"))return;
        if(Buff_end(ptr->Sub_Unit_ptr[0].get(),"War_Marshal")){
            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]-=10;
            ptr->Sub_Unit_ptr[0]->Buff_check["War_Marshal"];
        }
        if(ptr->Eidolon>=2&&Buff_end(ptr->Sub_Unit_ptr[0].get(),"Swing_Skies_Squashed")){
                ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Basic_Attack"]-=20;
                ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Skill"]-=20;
                ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Ultimate"]-=20;
                ptr->Sub_Unit_ptr[0]->Buff_check["Swing_Skies_Squashed"] = 0;
        }
    }
    void Start_game(Ally *ptr){
        if(ptr->Technique==1){
            ptr->Sub_Unit_ptr[0]->Stack["LL_stack"]+=3;
            Speed_Buff(ptr->Summon_ptr[0]->Atv_stats.get(),0,30);
        }
        Increase_energy(ptr,15);
    }
    bool Temp_Turn_Condition(Unit *ptr){
        return true;
    }
    bool Temp_ult_Condition(Ally *ptr){
        return true;
    }
    bool Robin_temp(Ally *ptr){
        if(Robin_num!=0&&Ally_unit[Robin_num]->Sub_Unit_ptr[0]->Atv_stats->Base_speed==-1){
            return false;
        }
        return true;
    }
}
#endif