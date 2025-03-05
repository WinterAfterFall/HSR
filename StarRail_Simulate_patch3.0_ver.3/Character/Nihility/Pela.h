
#ifndef Pela_H
#define Pela_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Pela{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Basic_Atk(Ally *ptr);
    void Ult_func(Ally *ptr);//*
    void After_turn(Ally *ptr);
    void After_attack(Ally *ptr, Combat_data &data_);
    void Start_game(Ally *ptr);
    void Tune_stats(Ally *ptr);
    void When_Combat(Ally *ptr);
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();
        Ally_unit[num] = make_unique<Ally>();
        SetBaseStats(Ally_unit[num]->Sub_Unit_ptr[0].get(),1087,660,509);
        SetBasicStats(Ally_unit[num].get(),105,110,110,E,"Ice","Nihility",num,"Pela","Ally",0);

        //substats
        Ally_unit[num]->Total_substats=20;
        Ally_unit[num]->Separate_sub=20;
        Ally_unit[num]->Reroll_check=1;

        Ally_unit[num]->Substats.push_back({"Crit_dam",20});
        Ally_unit[num]->Substats.push_back({"Crit_rate",0});
        Ally_unit[num]->Substats.push_back({"Atk%",0});

        Ally_unit[num]->Max_damage_Substats.resize(Ally_unit[num]->Substats.size());



        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        
        Ally_unit[num]->Sub_Unit_ptr[0]->Turn_func = Turn_func;
        Ally_unit[num]->Ult_func = Ult_func;
        Ally_unit[num]->Char_func.Reset_func = Reset;
        Ally_unit[num]->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->Char_func.After_attack_func = After_attack;
        Ally_unit[num]->Char_func.Start_game_func = Start_game;
        Ally_unit[num]->Char_func.Tune_stats_func = Tune_stats;
        Ally_unit[num]->Char_func.When_Combat_func = When_Combat;


        //substats
        Ally_unit[num]->Total_substats=20;
        Ally_unit[num]->Separate_sub=20;

        Ally_unit[num]->Substats.push_back({"Speed",20});

        Ally_unit[num]->Max_damage_Substats.resize(Ally_unit[num]->Substats.size());


    }
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_each_element["Ice"]["None"]["None"]+=22.4;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=18;
        ptr->Sub_Unit_ptr[0]->Stats_type["Ehr"]["None"]+=10;

        //relic
        ptr->Sub_Unit_ptr[0]->Stats_type["Ehr"]["None"]+=43.2;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Energy_recharge+=19.4;

        //substats
        ptr->Sub_Unit_ptr[0]->Stats_type["Ehr"]["None"]+=ptr->Sub_effect_hit_rate_use;
        

    }
    void When_Combat(Ally *ptr){
        Buff_All_Ally("Ehr","None","None",10);
    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        Basic_Atk(ally_ptr->ptr_to_unit);
        
    }
    void Basic_Atk(Ally *ptr){
        Increase_energy(Ally_unit[ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num].get(),20);
        Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
        Combat_data data_ = Combat_data();
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");
        data_.Add_Target(Choose_Enemy_target(ptr->Sub_Unit_ptr[0].get()));
        data_.Turn_reset=true;
        data_.Damage_spilt.Main.push_back({55,0,0,5});
        data_.Damage_spilt.Main.push_back({55,0,0,5});
        Action_bar.push(data_);
    }
    
    void Ult_func(Ally *ptr){
        for(int i=1;i<=Total_enemy;i++){
            if(Enemy_unit[i]->Debuff["Zone_Suppression"]==0)break;
            if(i==Total_enemy)return;
        }
        if(!Ult_use_check(ptr))return;
        Combat_data data_;
        data_.Ultimate_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
        data_.Add_Target_Other();
        data_.Turn_reset=true;
        data_.Damage_spilt.Main.push_back({108,0,0,20});
        data_.Damage_spilt.Adjacent.push_back({108,0,0,20});
        data_.Damage_spilt.Other.push_back({108,0,0,20});
        Action_bar.push(data_);
        
            Debuff_All_Enemy_Apply_ver(ptr->Sub_Unit_ptr[0].get(),"Def_shred","None","None",42,"Zone_Suppression");
            Extend_Debuff_All_Enemy("Zone_Suppression",2);
            Deal_damage();

    }
    void After_turn(Ally *ptr){
        if(turn->Side=="Enemy"){
            if(Enemy_unit[turn->Unit_num]->Debuff_time_count["Zone_Suppression"]==Enemy_unit[turn->Unit_num]->Atv_stats->turn_cnt){
                Enemy_unit[turn->Unit_num]->Debuff["Zone_Suppression"]=0;
                Enemy_unit[turn->Unit_num]->Stats_type["Def_shred"]["None"]-=42;
                --Enemy_unit[turn->Unit_num]->Total_debuff;
            }
            if(Enemy_unit[turn->Unit_num]->Debuff_time_count["Pela_Technique"]==turn->turn_cnt){
                Enemy_unit[turn->Unit_num]->Stats_type["Def_shred"]["None"]-=20;
                --Enemy_unit[turn->Unit_num]->Total_debuff;
            }
        }
    }
    void After_attack(Ally *ptr, Combat_data &data_){
        if(data_.Attacker->Atv_stats->Char_Name!="Pela")return;

        for(auto e:data_.Target_Attack){
            if(e->Total_debuff==0)continue;
            Increase_energy(ptr,11);
            break;
        }
        
        if(ptr->Eidolon>=6){
            Combat_data temp = Combat_data();
            temp.Additional_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");
            for(auto e:data_.Target_Attack){
            Cal_Additional_damage(temp,e,{40,0,0,0});
            }
        }
            
        
    }
    void Start_game(Ally *ptr){
        
        if(ptr->Technique==1){
            Debuff_All_Enemy_Apply_ver(ptr->Sub_Unit_ptr[0].get(),"Def_shred","None","None",20,"Pela_Technique");
            Extend_Debuff_All_Enemy("Pela_Technique",2);
               Increase_energy(ptr,20);
        }

    }
    void Tune_stats(Ally *ptr){
        Cal_effect_hit_rate(ptr,100);
    }
    

    
}

#endif
