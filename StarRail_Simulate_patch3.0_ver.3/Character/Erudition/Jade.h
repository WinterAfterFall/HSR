
#ifndef Jade_H
#define Jade_H

#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Jade{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);

    void Basic_Atk(Ally *ptr);
    void Skill(Ally *ptr);

    void Ult_func(Ally *ptr);
    void Tune_stats(Ally *ptr);
    void When_attack(Ally *ptr,Combat_data &data_);
    void Start_game(Ally *ptr);
    void Before_turn(Ally *ptr);
    void Before_attack(Ally *ptr,Combat_data &data_);
    void After_attack(Ally *ptr,Combat_data &data_);
    void Enemy_Death(Ally *ptr,Enemy *target,Sub_Unit *Killer);


//temp
    void Jade_Fua(Ally *ptr);
    void Jade_Talent(Ally *ptr,int amount);\
    void Fua(Ally *ptr);
    void Fua_Enchance(Ally *ptr);


    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();
        SetBaseStats(Ally_unit[num]->Sub_Unit_ptr[0].get(),1087,660,509);
        SetBasicStats(Ally_unit[num].get(),103,140,140,E,"Quantum","Erudition",num,"Jade","Ally",-2);

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
        Ally_unit[num]->Char_func.Tune_stats_func = Tune_stats;
        Ally_unit[num]->Char_func.When_attack_func = When_attack;
        Ally_unit[num]->Char_func.Start_game_func = Start_game;
        Ally_unit[num]->Char_func.Enemy_Death_func = Enemy_Death;
        Ally_unit[num]->Char_func.Before_turn_func = Before_turn;
        Ally_unit[num]->Char_func.Before_attack_func = Before_attack;
        Ally_unit[num]->Char_func.After_attack_func = After_attack;



        
    }
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=18;
        ptr->Sub_Unit_ptr[0]->Stats_each_element["Dmg%"]["Quantum"]["None"]+=22.4;



        //relic
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=32.4;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        ptr->Sub_Unit_ptr[0]->Stats_each_element["Dmg%"]["Quantum"]["None"]+=38.8;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;


        //substats
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=ptr->Sub_Speed_use;


        
    }
    void Tune_stats(Ally *ptr){
        Cal_Speed_Needed(ptr,143);

    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        if(Buff_check(ally_ptr,"Jade_Skill")){
            Basic_Atk(ally_ptr->ptr_to_unit);
        }else{
            Skill(ally_ptr->ptr_to_unit);
        }
    }
    void Basic_Atk(Ally *ptr){
        Increase_energy(Ally_unit[ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num].get(),20);
        Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
        Combat_data data_ = Combat_data();
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Blast");
        data_.Add_Target_Adjacent();
        data_.Turn_reset=true;
        data_.Damage_spilt.Main.push_back({90,0,0,10});
        data_.Damage_spilt.Adjacent.push_back({30,0,0,5});

        Action_bar.push(data_);
    }
    void Skill(Ally *ptr){
        Increase_energy(Ally_unit[ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num].get(),30);
        Skill_point(ptr->Sub_Unit_ptr[0].get(),-1);
        Combat_data data_ = Combat_data();
        data_.Skill_set(ptr->Sub_Unit_ptr[0].get(),"Single_target","Buff");
        data_.Add_Buff_Single_Target(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()));
        data_.Turn_reset=true;
        Speed_Buff(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get())->Atv_stats.get(),0,30);
        ptr->Sub_Unit_ptr[0]->Buff_check["Jade_Skill"]=1;
        Extend_Buff_single_target(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get()),"Jade_Skill",3);
        Action_bar.push(data_);
    }

    void Ult_func(Ally *ptr){
        if(!Ult_use_check(ptr))return;
            Combat_data data_ = Combat_data();
            data_.Ultimate_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
            data_.Add_Target_Other();
            data_.Damage_spilt.Main.push_back({240,0,0,20});
            data_.Damage_spilt.Adjacent.push_back({240,0,0,20});
            data_.Damage_spilt.Other.push_back({240,0,0,20});
            Action_bar.push(data_);
            ptr->Sub_Unit_ptr[0]->Stack["Jade_Ultimate_stack"]=2;
            Deal_damage();
        }
            
        
    void When_attack(Ally *ptr,Combat_data &data_){
        if(data_.Attacker->Atv_stats->Unit_Name=="Jade"&&data_.Action_type.second == "Fua"){
            Jade_Talent(ptr,5);
            return;
        }
        if(ptr->Sub_Unit_ptr[0]->Buff_check["Jade_Skill"]==0)return;
        if(data_.Attacker->Atv_stats->Unit_Name!="Jade"&&data_.Attacker->Atv_stats->Unit_Name!=Choose_Target_buff(ptr->Sub_Unit_ptr[0].get())->Atv_stats->Unit_Name)return;
        
        
        int temp = data_.Target_Attack.size();
        if(ptr->Eidolon>=1&&temp<3)temp = 3;
        ptr->Sub_Unit_ptr[0]->Stack["Jade_Talent"]+=temp;
        Jade_Fua(ptr);
        
    }
    void Jade_Fua(Ally *ptr){

        while(ptr->Sub_Unit_ptr[0]->Stack["Jade_Talent"]>8){
            ptr->Sub_Unit_ptr[0]->Stack["Jade_Talent"]-=8;
            if(ptr->Sub_Unit_ptr[0]->Stack["Jade_Ultimate_stack"]>0){
                Fua_Enchance(ptr);
                ptr->Sub_Unit_ptr[0]->Stack["Jade_Ultimate_stack"]--;             
            }else{
                Fua(ptr);
            }    
        }
    }
    void Fua(Ally *ptr){
        Combat_data data_ = Combat_data();
        data_.Fua_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
        data_.Add_Target_Other();
        data_.Damage_spilt.Main.push_back({18,0,0,10});
        data_.Damage_spilt.Main.push_back({18,0,0,10});
        data_.Damage_spilt.Main.push_back({18,0,0,10});
        data_.Damage_spilt.Main.push_back({18,0,0,10});
        data_.Damage_spilt.Main.push_back({48,0,0,10});

        data_.Damage_spilt.Adjacent.push_back({18,0,0,10});
        data_.Damage_spilt.Adjacent.push_back({18,0,0,10});
        data_.Damage_spilt.Adjacent.push_back({18,0,0,10});
        data_.Damage_spilt.Adjacent.push_back({18,0,0,10});
        data_.Damage_spilt.Adjacent.push_back({48,0,0,10});

        data_.Damage_spilt.Other.push_back({18,0,0,10});
        data_.Damage_spilt.Other.push_back({18,0,0,10});
        data_.Damage_spilt.Other.push_back({18,0,0,10});
        data_.Damage_spilt.Other.push_back({18,0,0,10});
        data_.Damage_spilt.Other.push_back({48,0,0,10});
        Action_bar.push(data_);
        
    }
    void Fua_Enchance(Ally *ptr){
        Combat_data data_ = Combat_data();
        data_.Fua_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
        data_.Add_Target_Other();
        data_.Damage_spilt.Main.push_back({20,0,0,10});
        data_.Damage_spilt.Main.push_back({20,0,0,10});
        data_.Damage_spilt.Main.push_back({20,0,0,10});
        data_.Damage_spilt.Main.push_back({20,0,0,10});
        data_.Damage_spilt.Main.push_back({120,0,0,10});

        data_.Damage_spilt.Adjacent.push_back({20,0,0,10});
        data_.Damage_spilt.Adjacent.push_back({20,0,0,10});
        data_.Damage_spilt.Adjacent.push_back({20,0,0,10});
        data_.Damage_spilt.Adjacent.push_back({20,0,0,10});
        data_.Damage_spilt.Adjacent.push_back({120,0,0,10});

        data_.Damage_spilt.Other.push_back({20,0,0,10});
        data_.Damage_spilt.Other.push_back({20,0,0,10});
        data_.Damage_spilt.Other.push_back({20,0,0,10});
        data_.Damage_spilt.Other.push_back({20,0,0,10});
        data_.Damage_spilt.Other.push_back({120,0,0,10});
        Action_bar.push(data_);
    }
    void Jade_Talent(Ally *ptr,int amount){
        Stack_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Atk%","None","None",0.5,amount,50,"Atk_Pawned_Asset");
        Stack_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Crit_dam","None","None",2.4,amount,50,"Crit_Pawned_Asset");
        if(ptr->Eidolon>=2&&ptr->Sub_Unit_ptr[0]->Buff_check["Jade_E2"]==0&&ptr->Sub_Unit_ptr[0]->Stack["Atk_Pawned_Asset"]>=15){
            ptr->Sub_Unit_ptr[0]->Buff_check["Jade_E2"]=1;
            Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Crit_rate","None","None",18);

        }

    }
    void Before_turn(Ally *ptr){
        if(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get())->Atv_stats->Char_Name==turn->Char_Name){
        Jade_Talent(ptr,3);
        }
        if(Buff_end(ptr->Sub_Unit_ptr[0].get(),"Jade_Skill")){
            Speed_Buff(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get())->Atv_stats.get(),0,-30);
            ptr->Sub_Unit_ptr[0]->Buff_check["Jade_Skill"]=0;
        }
    }
    void Before_attack(Ally *ptr,Combat_data &data_){
        if(ptr->Eidolon>=1&&data_.Attacker->Atv_stats->Unit_Name=="Jade"&&data_.Action_type.second == "Fua"){
            Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Dmg%","None","None",32);
        }
    }
    void After_attack(Ally *ptr,Combat_data &data_){
        if(ptr->Eidolon>=1&&data_.Attacker->Atv_stats->Unit_Name=="Jade"&&data_.Action_type.second == "Fua"){
            Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Dmg%","None","None",-32);
        }
    }
    void Start_game(Ally *ptr){
        Jade_Talent(ptr,Total_enemy);
        Action_forward(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),50);
        if(ptr->Technique==1){
            Jade_Talent(ptr,15);
            Combat_data data_ =Combat_data();
            data_.Technique_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
            data_.Add_Target_Other();
            data_.Damage_spilt.Main.push_back({50,0,0,0});
            data_.Damage_spilt.Adjacent.push_back({50,0,0,0});
            data_.Damage_spilt.Other.push_back({50,0,0,0});

            Action_bar.push(data_);
            Deal_damage();
        }
    }
    void Enemy_Death(Ally *ptr,Enemy *target,Sub_Unit *Killer){
        Jade_Talent(ptr,1);
    }
}
#endif