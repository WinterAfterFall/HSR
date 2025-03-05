#ifndef FireFly_H
#define FireFly_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace FireFly{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Skill_func(Ally *ptr);
    void Enchance_Skill_func(Ally *ptr);
    void Ult_func(Ally *ptr);//*
    void FF_BE_increased(Ally *ptr);
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void Before_attack(Ally *ptr, Combat_data &data_);
    void After_attack(Ally *ptr, Combat_data &data_);
    void Buff_func(Ally *ptr, Combat_data &data_);
    void Toughness_break_func(Ally *ptr,Enemy *target,Sub_Unit *Breaker);
    void Tune_stats(Ally *ptr);
    void Start_wave(Ally *ptr);
    
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->Sub_Unit_ptr[0]->Base_hp = 815;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_atk = 524;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_def = 776;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Base_speed = 104;
        Ally_unit[num]->Max_energy = 240;
        Ally_unit[num]->Ult_cost = 240;
        Ally_unit[num]->Eidolon = E;
        Ally_unit[num]->Sub_Unit_ptr[0]->Element_type.push_back("Fire");
        Ally_unit[num]->Path.push_back("Destruction");
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_num = num;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Char_Name = "FireFly";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_Name = "FireFly";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->ptr_to_unit = Ally_unit[num]->Sub_Unit_ptr[0].get();
        Ally_unit[num]->Ult_priority -=2;

        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        
        Ally_unit[num]->Sub_Unit_ptr[0]->Turn_func = Turn_func;
        Ally_unit[num]->Ult_func = Ult_func;
        Ally_unit[num]->Char_func.Reset_func = Reset;
        Ally_unit[num]->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->Char_func.Before_turn_func = Before_turn;
        Ally_unit[num]->Char_func.Before_attack_func = Before_attack;
        Ally_unit[num]->Char_func.After_attack_func = After_attack;
        Ally_unit[num]->Char_func.Buff_func = Buff_func;
        Ally_unit[num]->Char_func.Toughness_break_func = Toughness_break_func;
        Ally_unit[num]->Char_func.Tune_stats_func = Tune_stats;
        Ally_unit[num]->Char_func.Start_wave_func = Start_wave;

        
        //substats
        Ally_unit[num]->Total_substats=20;
        Ally_unit[num]->Separate_sub=20;
        //Ally_unit[num]->Reroll_check=1;

        Ally_unit[num]->Substats.push_back({"Break_effect",20});
        Ally_unit[num]->Substats.push_back({"Atk%",0});


        Ally_unit[num]->Max_damage_Substats.resize(Ally_unit[num]->Substats.size());

        //countdown
        Ally_unit[num]->Countdown_ptr.resize(1);
        Ally_unit[num]->Countdown_ptr[0] =  make_unique<Unit>();
        Ally_unit[num]->Countdown_ptr[0]->Atv_stats->Base_speed = -1;
        Ally_unit[num]->Countdown_ptr[0]->Atv_stats->Unit_num = num;
        Ally_unit[num]->Countdown_ptr[0]->Atv_stats->Char_Name = "Combustion_state";
        Ally_unit[num]->Countdown_ptr[0]->Atv_stats->Unit_Name = "Combustion_state";
        Ally_unit[num]->Countdown_ptr[0]->Atv_stats->Side = "Countdown";
        Ally_unit[num]->Countdown_ptr[0]->Atv_stats->ptr_to_unit = Ally_unit[num]->Countdown_ptr[0].get();
        Ally_unit[num]->Countdown_ptr[0]->Turn_func = [](Unit *ptr){

            auto ally_ptr = Ally_unit[ptr->Atv_stats->Unit_num].get();
            if(ally_ptr->Print)cout<<"-------------------------------------------- FF Ult End at "<<Current_atv<<endl;
            Buff_single_target(ally_ptr->Sub_Unit_ptr[0].get(),"Weakness_Break_Efficiency","None","None",-50);
            Buff_single_target(ally_ptr->Sub_Unit_ptr[0].get(),"Vul","Break_dmg","None",-20);
            ally_ptr->Countdown_ptr[0]->Atv_stats->Base_speed=-1;
            Speed_Buff(ally_ptr->Sub_Unit_ptr[0]->Atv_stats.get(),0,-60);

            Update_Max_atv(ally_ptr->Countdown_ptr[0]->Atv_stats.get());
            atv_reset(ally_ptr->Countdown_ptr[0]->Atv_stats.get());

        };
    }
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]+=37.3;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=5;

        //relic
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]+=64.8;
        
        

        //substats
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=ptr->Sub_Speed_use;

        //eidolon
        if(ptr->Eidolon>=1){
            ptr->Sub_Unit_ptr[0]->Stats_type["Def_shred"]["None"]+=15;
        }
        ptr->Countdown_ptr[0]->Atv_stats->Base_speed = -1;
        if(ptr->Eidolon>=2){
            ptr->Sub_Unit_ptr[0]->Stack["FireFly_E2"]=2;
        }

    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        if(ally_ptr->ptr_to_unit->Countdown_ptr[0]->Atv_stats->Base_speed==-1){
            Skill_func(ally_ptr->ptr_to_unit);
        }else {
            Enchance_Skill_func(ally_ptr->ptr_to_unit);
        }
    }
    void Skill_func(Ally *ptr){
        Skill_point(ptr->Sub_Unit_ptr[0].get(),-1);
        Increase_energy(ptr,60,0);
        Combat_data data_ = Combat_data();
        data_.Skill_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");
        data_.Add_Target_Main();
        data_.Turn_reset = 1;
        data_.Damage_spilt.Main.push_back({40,0,0,8});
        data_.Damage_spilt.Main.push_back({60,0,0,12});
        Action_bar.push(data_);


    }
    void Enchance_Skill_func(Ally *ptr){
        if(ptr->Eidolon>=1){   
        }else{
           Skill_point(ptr->Sub_Unit_ptr[0].get(),-1); 
        }
        Combat_data data_ = Combat_data();
        double skill_dmg = 0;
        if(ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]>=360){
            skill_dmg = 272;
        }else{
            skill_dmg = 200 + (ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"])*0.2;
        }
        data_.Skill_set(ptr->Sub_Unit_ptr[0].get(),"Blast");
        data_.Add_Target_Adjacent();
        data_.Turn_reset = 1;
        data_.Damage_spilt.Main.push_back({0.15*skill_dmg,0,0,4.5});
        data_.Damage_spilt.Main.push_back({0.15*skill_dmg,0,0,4.5});
        data_.Damage_spilt.Main.push_back({0.15*skill_dmg,0,0,4.5});
        data_.Damage_spilt.Main.push_back({0.15*skill_dmg,0,0,4.5});
        data_.Damage_spilt.Main.push_back({0.4*skill_dmg,0,0,12});

        data_.Damage_spilt.Adjacent.push_back({0.15*skill_dmg*0.5,0,0,2.25});
        data_.Damage_spilt.Adjacent.push_back({0.15*skill_dmg*0.5,0,0,2.25});
        data_.Damage_spilt.Adjacent.push_back({0.15*skill_dmg*0.5,0,0,2.25});
        data_.Damage_spilt.Adjacent.push_back({0.15*skill_dmg*0.5,0,0,2.25  });
        data_.Damage_spilt.Adjacent.push_back({0.2*skill_dmg,0,0,6});
        Action_bar.push(data_);


    }
    void Ult_func(Ally *ptr){
        if(!Ult_use_check(ptr))return;
        Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Weakness_Break_Efficiency","None","None",50);
        Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Vul","Break_dmg","None",20);
        ptr->Countdown_ptr[0]->Atv_stats->Base_speed=70;
        Speed_Buff(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),0,60);
        Action_forward(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),100);

        Update_Max_atv(ptr->Countdown_ptr[0]->Atv_stats.get());
        atv_reset(ptr->Countdown_ptr[0]->Atv_stats.get());
        if(ptr->Print)cout<<"-------------------------------------------- FF Ult Start at "<<Current_atv<<endl;
        
    } 
    void FF_BE_increased(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"] -= ptr->Sub_Unit_ptr[0]->Buff_note["FireFly_ModuleY"];
        ptr->Sub_Unit_ptr[0]->Buff_note["FireFly_ModuleY"] =floor(((ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]/100*ptr->Sub_Unit_ptr[0]->Base_atk+ptr->Sub_Unit_ptr[0]->Base_atk)+ptr->Sub_Unit_ptr[0]->Stats_type["Flat_Atk"]["None"]-1800)/100)*0.8;
        if(ptr->Sub_Unit_ptr[0]->Buff_note["FireFly_ModuleY"]<=0)ptr->Sub_Unit_ptr[0]->Buff_note["FireFly_ModuleY"] = 0;
        ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"] += ptr->Sub_Unit_ptr[0]->Buff_note["FireFly_ModuleY"];

    }
    void After_attack(Ally *ptr, Combat_data &data_){
        FF_BE_increased(ptr);
        if(ptr->Eidolon>=2&&ptr->Sub_Unit_ptr[0]->Stack["FireFly_E2"]>0&&ptr->Countdown_ptr[0]->Atv_stats->Base_speed==70){
            ptr->Sub_Unit_ptr[0]->Stack["FireFly_E2"]--;
            Action_forward(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),100);
        }
        if(data_.Attacker->Atv_stats->Char_Name=="FireFly"){
            if(data_.Action_type.second=="Skill"&&ptr->Countdown_ptr[0]->Atv_stats->Base_speed==-1){            
                Action_forward(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),25);
            }
            if(ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]>=360){
                Superbreak_trigger(data_,50);
            }else if(ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]>=200){
                Superbreak_trigger(data_,35);
            }
        }
    }
    void Before_turn(Ally *ptr){
        FF_BE_increased(ptr);
    }
    void After_turn(Ally *ptr){
        FF_BE_increased(ptr);
    }
    void Before_attack(Ally *ptr, Combat_data &data_){
        FF_BE_increased(ptr);
    }
    void Buff_func(Ally *ptr, Combat_data &data_){
        FF_BE_increased(ptr);
    }
    void Toughness_break_func(Ally *ptr,Enemy *target,Sub_Unit *Breaker){
        if(ptr->Eidolon>=2&&ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num==Breaker->Atv_stats->Unit_num&&ptr->Countdown_ptr[0]->Atv_stats->Base_speed==70){
            ptr->Sub_Unit_ptr[0]->Stack["FireFly_E2"]++;
        }
    }
    void Tune_stats(Ally *ptr){
        Cal_Speed_Needed(ptr,150);
    }
    void Start_wave(Ally *ptr){
        if(ptr->Technique==1){
        Combat_data data_ =Combat_data();
        data_.Technique_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
        data_.Add_Target_Other();
        data_.Damage_spilt.Main.push_back({200,0,0,20});
        data_.Damage_spilt.Adjacent.push_back({200,0,0,20});
        data_.Damage_spilt.Other.push_back({200,0,0,20});

        Action_bar.push(data_);
        Deal_damage();
        }
    }
    
}
#endif
