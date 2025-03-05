
#ifndef Tingyun_H
#define Tingyun_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Tingyun{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Basic_Atk(Ally *ptr);
    void Skill(Ally *ptr);
    void Ult_func(Ally *ptr);//*
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void After_attack(Ally *ptr, Combat_data &data_);
    void Start_game(Ally *ptr);
    
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->Sub_Unit_ptr[0]->Base_hp = 847;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_atk = 529;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_def = 397;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Base_speed = 112;
        Ally_unit[num]->Max_energy = 130;
        Ally_unit[num]->Ult_cost = 130;
        Ally_unit[num]->Eidolon = E;
        Ally_unit[num]->Sub_Unit_ptr[0]->Element_type.push_back("Lightning");
        Ally_unit[num]->Path.push_back("Harmony");
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_num = num;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Char_Name = "Tingyun";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_Name = "Tingyun";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->ptr_to_unit = Ally_unit[num]->Sub_Unit_ptr[0].get();
        Ally_unit[num]->Technique = 2;
        Ally_unit[num]->Ult_priority +=2;

        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        
        Ally_unit[num]->Sub_Unit_ptr[0]->Turn_func = Turn_func;
        Ally_unit[num]->Ult_func = Ult_func;
        Ally_unit[num]->Char_func.Reset_func = Reset;
        Ally_unit[num]->Char_func.Before_turn_func = Before_turn;
        Ally_unit[num]->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->Char_func.After_attack_func = After_attack;
        Ally_unit[num]->Char_func.Start_game_func = Start_game;


    }
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_each_element["Dmg%"]["Lightning"]["None"]+=8;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=28;
        ptr->Sub_Unit_ptr[0]->Stats_type["Def%"]["None"]+=22.5;


        //relic
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Energy_recharge+=19.4;

        //substats
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=77.76;
        ptr->Sub_Unit_ptr[0]->Stats_type["Dmg%"]["Basic_Attack"]+=40;
    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        if(Choose_Target_buff(ally_ptr)->Buff_check["Benediction"] ==0){
            Skill(ally_ptr->ptr_to_unit);
        }else{
            Basic_Atk(ally_ptr->ptr_to_unit);
        }
    }
    void Skill(Ally *ptr){
        if(ptr->Print){
            cout<<"-----------------------tingyun skill at "<<Current_atv<<endl;
        }
        Skill_point(ptr->Sub_Unit_ptr[0].get(),-1);
        Increase_energy(ptr,30);
        Combat_data data_ = Combat_data();
        data_.Skill_set(ptr->Sub_Unit_ptr[0].get(),"Single_target","Buff");
        data_.Add_Buff_Single_Target(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()));
        data_.Turn_reset = 1;
        Action_bar.push(data_);
        if(!Buff_check(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Benediction")){
            Buff_single_target(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Atk%","None","None",55);
            Choose_Target_buff(ptr->Sub_Unit_ptr[0].get())->Buff_check["Benediction"] = 1;
        }
        Extend_Buff_single_target(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Benediction",3);
    }
    void Basic_Atk(Ally *ptr){
        Combat_data data_ = Combat_data();
        Increase_energy(ptr,20);
        Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");
        data_.Add_Target(Choose_Enemy_target(ptr->Sub_Unit_ptr[0].get()));
        data_.Turn_reset = 1;
        data_.Damage_spilt.Main.push_back({33,0,0,3});
        data_.Damage_spilt.Main.push_back({77,0,0,7});
        Action_bar.push(data_);
    }
    void Ult_func(Ally *ptr){
        if(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Max_energy - Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Current_energy<=30)return ;

        if(!Ult_use_check(ptr))return;
        Combat_data data_ = Combat_data();
        data_.Ultimate_set(ptr->Sub_Unit_ptr[0].get(),"Single_target","Buff");
        data_.Add_Buff_Single_Target(ptr->Sub_Unit_ptr[0].get());
        Action_bar.push(data_);

        Increase_energy(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),0,50);
        if(ptr->Eidolon>=6){
            Increase_energy(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),0,10);
        }
        if(ptr->Eidolon>=1){
            Speed_Buff(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get())->Atv_stats.get(),20,0);
            Extend_Buff_single_target(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Windfall_of_Lucky_Springs",1);
            }
        if(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr[0]->Buff_check["Rejoicing_Clouds"]==0){
            Buff_single_target(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Dmg%","None","None",56);
            Choose_Target_buff(ptr->Sub_Unit_ptr[0].get())->Buff_check["Rejoicing_Clouds"] = 1;
        }
        if(turn->Char_Name==Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr[0]->Atv_stats->Char_Name&&Ult_After_Turn==0){
            Extend_Buff_single_target(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Rejoicing_Clouds",1);
        }else{
            Extend_Buff_single_target(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Rejoicing_Clouds",2);
        }
        

        Deal_damage();
    }
    void Before_turn(Ally *ptr){
        if(turn->Char_Name!="Tingyun")return;
        Increase_energy(ptr,5);
    }
    void After_turn(Ally *ptr){
        if(turn->Char_Name=="Tingyun"){
            if(Buff_end(ptr->Sub_Unit_ptr[0].get(),"Nourished_Joviality")){
            Speed_Buff(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),-20,0);
        }
        }
        if(Buff_end(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Benediction")){
            Choose_Target_buff(ptr->Sub_Unit_ptr[0].get())->Buff_check["Benediction"] = 0;
            Buff_single_target(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Atk%","None","None",-55);
        
        }
        
        if(Buff_end(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Windfall_of_Lucky_Springs")){
             Speed_Buff(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get())->Atv_stats.get(),-20,0);
        }
        
        if(Buff_end(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Rejoicing_Clouds")){
            Buff_single_target(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Dmg%","None","None",-56);
            Choose_Target_buff(ptr->Sub_Unit_ptr[0].get())->Buff_check["Rejoicing_Clouds"] = 0;
        }
    }
    void After_attack(Ally *ptr, Combat_data &data_){
        if(Buff_check(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Benediction")){
        if(data_.Attacker->Atv_stats->Unit_Name == ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_Name){
                Combat_data temp = Combat_data();
                temp.Additional_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");
                Cal_Additional_damage(temp,Enemy_unit[Main_Enemy_num].get(),{66,0,0,0});
                
        }else if(data_.Attacker->Atv_stats->Unit_Name == Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr[ptr->Sub_Unit_ptr[0]->Sub_Unit_num]->Atv_stats->Unit_Name){
                Combat_data temp = Combat_data();
                temp.Additional_set(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Single_target");
        
                if(ptr->Eidolon>=4){
                    Cal_Additional_damage(temp,Enemy_unit[Main_Enemy_num].get(),{64,0,0,0});
                }else{
                    Cal_Additional_damage(temp,Enemy_unit[Main_Enemy_num].get(),{44,0,0,0});
                }
        }
        }
        if(data_.Action_type.second=="Skill"&&data_.Attacker->Atv_stats->Char_Name=="Tingyun"){
            Speed_Buff(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),-20,0);
            Extend_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Nourished_Joviality",1);

        }
    }
    void Start_game(Ally *ptr){
        Increase_energy(ptr,0,50*ptr->Technique);
    }
    

    

    
}
#endif
