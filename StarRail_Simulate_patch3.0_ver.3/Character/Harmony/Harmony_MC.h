
#ifndef Harmony_MC_H
#define Harmony_MC_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Harmony_MC{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Basic_Atk(Ally *ptr);  
    void Skill_func(Ally *ptr);
    void Ult_func(Ally *ptr);//*
    void E4_func(Ally *ptr);
    void Tune_stats(Ally *ptr);
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void Start_game(Ally *ptr);
    void Toughness_break_func(Ally *ptr,Enemy *target,Sub_Unit *Breaker);
    void After_attack(Ally *ptr, Combat_data &data_);
    void Before_attack(Ally *ptr, Combat_data &data_);
    void Buff_func(Ally *ptr, Combat_data &data_);

    
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->Sub_Unit_ptr[0]->Base_hp = 1087;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_atk = 446;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_def = 679;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Base_speed = 105;
        Ally_unit[num]->Max_energy = 140;
        Ally_unit[num]->Ult_cost = 140;
        Ally_unit[num]->Eidolon = E;
        Ally_unit[num]->Sub_Unit_ptr[0]->Element_type.push_back("Imaginary");
        Ally_unit[num]->Path.push_back("Harmony");
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_num = num;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Char_Name = "Harmony_MC";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_Name = "Harmony_MC";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->ptr_to_unit = Ally_unit[num]->Sub_Unit_ptr[0].get();
        Ally_unit[num]->Ult_priority +=3;

        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        
        Ally_unit[num]->Char_func.Reset_func = Reset;
        Ally_unit[num]->Char_func.Tune_stats_func = Tune_stats;
        Ally_unit[num]->Sub_Unit_ptr[0]->Turn_func = Turn_func;
        Ally_unit[num]->Ult_func = Ult_func;
        Ally_unit[num]->Char_func.Toughness_break_func = Toughness_break_func;
        Ally_unit[num]->Char_func.Start_game_func = Start_game;
        Ally_unit[num]->Char_func.Before_turn_func = Before_turn;
        Ally_unit[num]->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->Char_func.Before_attack_func = Before_attack;
        Ally_unit[num]->Char_func.After_attack_func = After_attack;
        Ally_unit[num]->Char_func.Buff_func = Buff_func;




        //substats
        Ally_unit[num]->Total_substats=20;
        Ally_unit[num]->Separate_sub=20;

        Ally_unit[num]->Substats.push_back({"Break_effect",20});

        Ally_unit[num]->Max_damage_Substats.resize(Ally_unit[num]->Substats.size());
        
    }
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]+=37.3;
        ptr->Sub_Unit_ptr[0]->Stats_each_element["Dmg%"]["Imaginary"]["None"]+=14.4;


        //relic
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Energy_recharge+=19.4;
        
        

        //substats
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=ptr->Sub_Speed_use;

    }
    void Tune_stats(Ally *ptr){
        Cal_Speed_Needed(ptr,145);
    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        if(sp>Sp_Safety||ptr->Atv_stats->turn_cnt==1){
            Skill_func(ally_ptr->ptr_to_unit);           
        }else{
            
            Basic_Atk(ally_ptr->ptr_to_unit);
        }
    }
    void Ult_func(Ally *ptr){
        if(Buff_check(ptr->Sub_Unit_ptr[0].get(),"Harmony_MC_ult")||!Ult_use_check(ptr))return;
        if(!Buff_check(ptr->Sub_Unit_ptr[0].get(),"Harmony_MC_ult")){
            Buff_All_Ally("Break_effect","None","None",33);
        }
        ptr->Sub_Unit_ptr[0]->Buff_check["Harmony_MC_ult"]=1;
        Extend_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Harmony_MC_ult",3);
        Combat_data data_ = Combat_data();
        data_.Ultimate_set(ptr->Sub_Unit_ptr[0].get(),"Aoe","Buff");
        data_.Add_Buff_All_Ally();
        Action_bar.push(data_);
        Deal_damage();
    }
    void Basic_Atk(Ally *ptr){
        Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
        Increase_energy(ptr,20);
        Combat_data data_ = Combat_data();
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");
        data_.Add_Target(Choose_Enemy_target(ptr->Sub_Unit_ptr[0].get()));
        data_.Turn_reset = 1;
        data_.Damage_spilt.Main.push_back({110,0,0,10});
        Action_bar.push(data_);
    }
    void Skill_func(Ally *ptr){
        if(ptr->Sub_Unit_ptr[0]->Atv_stats->turn_cnt==1){

        }else{
            Skill_point(ptr->Sub_Unit_ptr[0].get(),-1);
        }
        
        Increase_energy(ptr,30);
        Combat_data data_ = Combat_data();
        data_.Skill_set(ptr->Sub_Unit_ptr[0].get(),"Bounce");
        data_.Add_Target_Adjacent();
        data_.Turn_reset = 1;
        data_.Damage_spilt.Main.push_back({55,0,0,10});
        data_.Damage_spilt.Main.push_back({55,0,0,5});
        data_.Damage_spilt.Main.push_back({55,0,0,5});
        
        if(Total_enemy==1){
            data_.Damage_spilt.Main.push_back({55,0,0,5});
            data_.Damage_spilt.Main.push_back({55,0,0,5});
            data_.Damage_spilt.Main.push_back({55,0,0,5});
            data_.Damage_spilt.Main.push_back({55,0,0,5});
        }else if(Total_enemy==2){
            data_.Damage_spilt.Main.push_back({55,0,0,5});
            data_.Damage_spilt.Adjacent.push_back({55,0,0,5});
            data_.Damage_spilt.Adjacent.push_back({55,0,0,5});
            data_.Damage_spilt.Adjacent.push_back({55,0,0,5});
        }else if(Total_enemy>=3){
            data_.Damage_spilt.Adjacent.push_back({55,0,0,5});
            data_.Damage_spilt.Adjacent.push_back({55,0,0,5});
        }
        
        Action_bar.push(data_);
    }
    void Toughness_break_func(Ally *ptr,Enemy *target,Sub_Unit *Breaker){
        Increase_energy(ptr,11);
        Action_forward(target->Atv_stats.get(),-30);
    }
    void Start_game(Ally *ptr){
        
        if(ptr->Technique==1){
            Buff_All_Ally("Break_effect","None","None",30);
        }
        ptr->Energy_recharge+=25;
    }
    void E4_func(Ally *ptr){
        Buff_All_Ally_Excluding_Buffer("Break_effect","None","None",-ptr->Sub_Unit_ptr[0]->Buff_note["Harmony_MC_E4"],"Harmony_MC");
        ptr->Sub_Unit_ptr[0]->Buff_note["Harmony_MC_E4"]=((ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"])*0.15);
        Buff_All_Ally_Excluding_Buffer("Break_effect","None","None",ptr->Sub_Unit_ptr[0]->Buff_note["Harmony_MC_E4"],"Harmony_MC");
    }
    void Before_turn(Ally *ptr){
        if(turn->Char_Name=="Harmony_MC"&&Buff_end(ptr->Sub_Unit_ptr[0].get(),"Harmony_MC_ult")){
            Buff_All_Ally("Break_effect","None","None",-33);
            ptr->Sub_Unit_ptr[0]->Buff_check["Harmony_MC_ult"]=0;
            
        }
        E4_func(ptr);
        

        
    }
    void After_turn(Ally *ptr){
        if(turn->Char_Name=="Harmony_MC"&&turn->turn_cnt==3){
            ptr->Energy_recharge-=25;
        }
        if(turn->Side=="Ally"||turn->Side=="Memosprite"){
            if(turn->turn_cnt==2&&ptr->Technique==1){
                Buff_single_target(Ally_unit[turn->Unit_num]->Sub_Unit_ptr[0].get(),"Break_effect","None","None",-30);

            }
            
        }
        E4_func(ptr);

        
    }
    void After_attack(Ally *ptr, Combat_data &data_){
        E4_func(ptr);

        if(ptr->Sub_Unit_ptr[0]->Buff_check["Harmony_MC_ult"]==1){
            Superbreak_trigger(data_,100*(1.7-(0.1*Total_enemy)));
        }
    }
    void Buff_func(Ally *ptr, Combat_data &data_){
        E4_func(ptr);

    }
    void Before_attack(Ally *ptr, Combat_data &data_){
        E4_func(ptr);

    }
}
#endif
