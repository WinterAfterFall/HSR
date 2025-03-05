
#ifndef Gallagher_H
#define Gallagher_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Gallagher{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Basic_Atk(Ally *ptr);
    void Enchance_Basic_Atk(Ally *ptr);
    void Skill_func(Ally *ptr);
    void Ult_func(Ally *ptr);//*
    void Tune_stats(Ally *ptr);
    void After_turn(Ally *ptr);
    void Start_game(Ally *ptr);
    
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->Sub_Unit_ptr[0]->Base_hp = 1305;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_atk = 529;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_def = 441;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Base_speed = 98;
        Ally_unit[num]->Max_energy = 110;
        Ally_unit[num]->Ult_cost = 110;
        Ally_unit[num]->Eidolon = E;
        Ally_unit[num]->Sub_Unit_ptr[0]->Element_type.push_back("Fire");
        Ally_unit[num]->Path.push_back("Abundance");
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_num = num;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Char_Name = "Gallagher";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_Name = "Gallagher";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->ptr_to_unit = Ally_unit[num]->Sub_Unit_ptr[0].get();
        Ally_unit[num]->Ult_priority +=2;
        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        
        Ally_unit[num]->Sub_Unit_ptr[0]->Turn_func = Turn_func;
        Ally_unit[num]->Ult_func = Ult_func;
        Ally_unit[num]->Char_func.Reset_func = Reset;
        Ally_unit[num]->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->Char_func.Tune_stats_func = Tune_stats;
        Ally_unit[num]->Char_func.Start_game_func = Start_game;

        //substats
        Ally_unit[num]->Total_substats=20;
        Ally_unit[num]->Separate_sub=20;

        Ally_unit[num]->Substats.push_back({"Break_effect",20});

        Ally_unit[num]->Max_damage_Substats.resize(Ally_unit[num]->Substats.size());
        
    }
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]+=13.3;
        ptr->Sub_Unit_ptr[0]->Stats_type["hp%"]["None"]+=18;

        //relic
        // bonus heal +35.7
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Energy_recharge+=19.4;
        
        

        //substats
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=ptr->Sub_Speed_use;
        if(ptr->Eidolon>=6){
            ptr->Sub_Unit_ptr[0]->Stats_type["Weakness_Break_Efficiency"]["None"]+=20;
            ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]+=20;

        }

    }
    void Tune_stats(Ally *ptr){
        Cal_Speed_Needed(ptr,150);
    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        
        if(ptr->Atv_stats->turn_cnt%8==1){
            
            Skill_func(ally_ptr->ptr_to_unit);
        }else{
            
            if(ally_ptr->Buff_check["Gallagher_enchance_basic_atk"] ==1){
                Enchance_Basic_Atk(ally_ptr->ptr_to_unit);
            }else{
                Basic_Atk(ally_ptr->ptr_to_unit);
            }
        }
    }
    void Basic_Atk(Ally *ptr){
        Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
        Increase_energy(ptr,20);
        Combat_data data_ = Combat_data();
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");
        data_.Add_Target_Main();
        data_.Turn_reset = 1;
        data_.Damage_spilt.Main.push_back({55,0,0,5});
        data_.Damage_spilt.Main.push_back({55,0,0,5});
        Action_bar.push(data_);
    }
    void Enchance_Basic_Atk(Ally *ptr){
        Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
        Increase_energy(ptr,20);
        if(!Debuff_check(Enemy_unit[Main_Enemy_num].get(),"Nectar_Blitz")){
            Enemy_unit[Main_Enemy_num]->Debuff["Nectar_Blitz"] = 1;
            ++Enemy_unit[Main_Enemy_num]->Total_debuff;
            
        }
        Apply_debuff(ptr->Sub_Unit_ptr[0].get(),Enemy_unit[Main_Enemy_num].get());
        Extend_Debuff_single_target(Enemy_unit[Main_Enemy_num].get(),"Nectar_Blitz",2);
        ptr->Sub_Unit_ptr[0]->Buff_check["Gallagher_enchance_basic_atk"] =0;
        Combat_data data_ = Combat_data();
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");
        data_.Add_Target_Main();
        data_.Turn_reset = 1;
        data_.Damage_spilt.Main.push_back({62.5,0,0,7.5});
        data_.Damage_spilt.Main.push_back({37.5,0,0,4.5});
        data_.Damage_spilt.Main.push_back({150,0,0,18});
        Action_bar.push(data_);
        

    }
    void Skill_func(Ally *ptr){

        Skill_point(ptr->Sub_Unit_ptr[0].get(),-1);
        Increase_energy(ptr,30);
        Combat_data data_ = Combat_data();
        data_.Skill_set(ptr->Sub_Unit_ptr[0].get(),"Single_target","Heal");
        data_.Add_Buff_Single_Target(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()));
        data_.Turn_reset = 1;
        data_.Buff_type.push_back("Heal");
        Action_bar.push(data_);
    }
    void Ult_func(Ally *ptr){
        if(Ult_After_Turn==0||ptr->Sub_Unit_ptr[0]->Atv_stats->atv==0||!Ult_use_check(ptr))return;
        Action_forward(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),100);
        ptr->Sub_Unit_ptr[0]->Buff_check["Gallagher_enchance_basic_atk"] = 1;
        Debuff_All_Enemy_Apply_ver(ptr->Sub_Unit_ptr[0].get(),"Vul","Break_dmg","None",13.2,"Besotted");
        if(ptr->Eidolon>=4){
            Extend_Debuff_All_Enemy("Besotted",3);
        }else{
            Extend_Debuff_All_Enemy("Besotted",2);
        }

        Combat_data data_ = Combat_data();
        data_.Ultimate_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
        data_.Add_Target_Other();
        data_.Damage_spilt.Main.push_back({165,0,0,20});
        data_.Damage_spilt.Adjacent.push_back({165,0,0,20});
        data_.Damage_spilt.Other.push_back({165,0,0,20});
        Action_bar.push(data_);
        Deal_damage();
        

    }
    void After_turn(Ally *ptr){
        if(turn->Side =="Enemy"){
            if(Debuff_end(Enemy_unit[turn->Unit_num].get(),"Besotted")){
                Debuff_single_target(Enemy_unit[turn->Unit_num].get(),"Vul","Break_dmg","None",-13.2);
                Enemy_unit[turn->Unit_num]->Debuff["Besotted"]=0;
                --Enemy_unit[turn->Unit_num]->Total_debuff;
            }
            if(Debuff_end(Enemy_unit[turn->Unit_num].get(),"Nectar_Blitz")){
                --Enemy_unit[turn->Unit_num]->Total_debuff;
                Enemy_unit[Main_Enemy_num]->Debuff["Nectar_Blitz"] = 0;
            }
        }
    }
    void Start_game(Ally *ptr){
        if(ptr->Eidolon>=1){
            Increase_energy(ptr,20);
        }
    }
}
#endif
