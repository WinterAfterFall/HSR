
#ifndef Luocha_H
#define Luocha_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Luocha{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Basic_Atk(Ally *ptr);
    void Talent(Ally *ptr);
    void Abyss_Flower(Ally *ptr);
    void Ult_func(Ally *ptr);//*
    void After_turn(Ally *ptr);
    void Start_game(Ally *ptr);
    
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->Sub_Unit_ptr[0]->Base_hp = 1280;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_atk = 756;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_def = 363;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Base_speed = 101;
        Ally_unit[num]->Max_energy = 100;
        Ally_unit[num]->Ult_cost = 100;
        Ally_unit[num]->Eidolon = E;
        Ally_unit[num]->Sub_Unit_ptr[0]->Element_type.push_back("Imaginary");
        Ally_unit[num]->Path.push_back("Abundance"); 
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_num = num;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Char_Name = "Luocha";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_Name = "Luocha";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->ptr_to_unit = Ally_unit[num]->Sub_Unit_ptr[0].get();
        Ally_unit[num]->Ult_priority =0;

        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        
        Ally_unit[num]->Sub_Unit_ptr[0]->Turn_func = Turn_func;
        Ally_unit[num]->Ult_func = Ult_func;
        Ally_unit[num]->Char_func.Reset_func = Reset;
        Ally_unit[num]->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->Char_func.Start_game_func = Start_game;
    }
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"] +=28;
        ptr->Sub_Unit_ptr[0]->Stats_type["Hp%"]["None"] +=18;
        ptr->Sub_Unit_ptr[0]->Stats_type["Def%"]["None"] +=12.5;


        //relic
        // bonus heal +35.7
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"] +=43.2;
        ptr->Energy_recharge+=19.4;
        
        

        //substats
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"] +=19.44; //5

        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=34.5; //15


    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        Basic_Atk(ally_ptr->ptr_to_unit);
            
    }
    void Talent(Ally *ptr){
        Increase_energy(ptr,30);
        ++ptr->Sub_Unit_ptr[0]->Stack["Abyss_Flower"];
        Abyss_Flower(ptr);
        
    }
    void Abyss_Flower(Ally *ptr){
        if(ptr->Sub_Unit_ptr[0]->Stack["Abyss_Flower"]==2){
        Extend_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Cycle_of_Life",2);
        if(ptr->Eidolon>=1){
            Buff_All_Ally("Atk%","None","None",20);
        }
        }
    }
    void Basic_Atk(Ally *ptr){
        Increase_energy(ptr,20);
        Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
        Combat_data data_ = Combat_data();
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");
        data_.Add_Target_Main();
        data_.Turn_reset = 1;
        data_.Damage_spilt.Main.push_back({30,0,0,3});
        data_.Damage_spilt.Main.push_back({30,0,0,3});
        data_.Damage_spilt.Main.push_back({40,0,0,4});
        Action_bar.push(data_);
        if(ptr->Sub_Unit_ptr[0]->Atv_stats->turn_cnt%2==1){
            Talent(ptr);
        }
    }
    void Ult_func(Ally *ptr){
        if(ptr->Sub_Unit_ptr[0]->Stack["Abyss_Flower"]>=2)return;
        if(!Ult_use_check(ptr))return;
        Combat_data data_ = Combat_data();
        data_.Ultimate_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
        data_.Add_Target_Other();
        data_.Damage_spilt.Main.push_back({200,0,0,20});
        data_.Damage_spilt.Adjacent.push_back({200,0,0,20});
        data_.Damage_spilt.Other.push_back({200,0,0,20});
        Action_bar.push(data_);
        ++ptr->Sub_Unit_ptr[0]->Stack["Abyss_Flower"];
        Abyss_Flower(ptr);
        Deal_damage();
    }
    void After_turn(Ally *ptr){
        if(turn->Char_Name=="Luocha"){
            if(Buff_end(ptr->Sub_Unit_ptr[0].get(),"Cycle_of_Life")){
                if(ptr->Eidolon>=1){
                    Buff_All_Ally("Atk%","None","None",-20);
                }
                ptr->Sub_Unit_ptr[0]->Stack["Abyss_Flower"]=0;
            }
        }
    }
    void Start_game(Ally *ptr){
        if(ptr->Technique==1){
            ptr->Sub_Unit_ptr[0]->Stack["Abyss_Flower"]=2;
            Abyss_Flower(ptr);
        }
    }

    

    
}
#endif
