
#ifndef Sunday_H
#define Sunday_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Sunday{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Skill(Ally *ptr);
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void Before_attack(Ally *ptr, Combat_data &data_);
    void Start_game(Ally *ptr);
    void Ult_func(Ally *ptr);//*
    void Buff_func(Ally *ptr, Combat_data &data_);
    void Tune_stats(Ally *ptr);
    bool ult_condition(Ally *ptr);
    


    
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"]+=37.3;
        ptr->Sub_Unit_ptr[0]->Stats_type["Def%"]["None"]+=12.5;

        //relic
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"]+=64.8;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        ptr->Sub_Unit_ptr[0]->Stats_type["Hp%"]["None"]+=43.2;
        ptr->Energy_recharge+=19.4;

        //substats
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=ptr->Sub_Speed_use;
    }
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->Sub_Unit_ptr[0]->Base_hp = 1242;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_atk = 640;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_def = 533;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Base_speed = 96;
        Ally_unit[num]->Max_energy = 130;
        Ally_unit[num]->Ult_cost = 130;
        Ally_unit[num]->Eidolon = E;
        Ally_unit[num]->Sub_Unit_ptr[0]->Element_type.push_back("Imaginary");
        Ally_unit[num]->Path.push_back("Harmony");
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_num = num;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Char_Name = "Sunday";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->ptr_to_unit = Ally_unit[num]->Sub_Unit_ptr[0].get();
        Ally_unit[num]->Ult_priority +=3;

        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        Ally_unit[num]->Sub_Unit_ptr[0]->Turn_func = Turn_func;
        Ally_unit[num]->Ult_func = Ult_func;
        Ally_unit[num]->Char_func.Reset_func = Reset;
        Ally_unit[num]->Char_func.Before_turn_func = Before_turn;
        Ally_unit[num]->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->Char_func.Before_attack_func = Before_attack;
        Ally_unit[num]->Char_func.Start_game_func = Start_game;
        Ally_unit[num]->Char_func.Tune_stats_func = Tune_stats;
        Ally_unit[num]->Char_func.Buff_func = Buff_func;

        Ally_unit[num]->Total_substats=20;
        Ally_unit[num]->Separate_sub=20;
        Ally_unit[num]->Speed_tune_value=133.4;
        Ally_unit[num]->Substats.push_back({"Crit_dam",20});



    }
    void Tune_stats(Ally *ptr){
        Cal_Speed_Needed(ptr,ptr->Speed_tune_value);
    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        Skill(ally_ptr->ptr_to_unit);
    }
    void Skill(Ally *ptr){
        
        Skill_point(ptr->Sub_Unit_ptr[0].get(),-1);
        Increase_energy(ptr,30);

        Combat_data temp = Combat_data();
        temp.Skill_set(ptr->Sub_Unit_ptr[0].get(),"Single_target","Buff");
        temp.Add_Buff_Single_Target(Choose_Character_Buff(ptr->Sub_Unit_ptr[0].get()));
        temp.Turn_reset=true;
        Action_bar.push(temp);
        Buff_single_with_all_memo_each(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"Crit_rate","None","None",20,"The_Sorrowing_Body");
        if(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Summon_ptr.size()!=0||Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr.size()>1){
        Buff_single_with_all_memo_each(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"Dmg%","None","None",50,"Benison_of_Paper_and_Rites");
        }else{
        Buff_single_with_all_memo_each(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"Dmg%","None","None",30,"Benison_of_Paper_and_Rites");
        }
        
        if(ptr->Eidolon>=1){
            if(!Buff_check(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr[0].get(),"Sunday_E1")){
                Buff_single_target(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr[0].get(),"Def_shred","None","None",16);
                Buff_single_target(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr[0].get(),"Def_shred","Summon","None",24);
                Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr[0]->Buff_check["Sunday_E1"]=1;
            }
            Buff_single_with_all_memo_each(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"Def_shred","None","None",40,"Sunday_E1");
        }
        
        if(ptr->Technique==1&&ptr->Sub_Unit_ptr[0]->Buff_check["Technique_use"]==0){
            Buff_single_with_all_memo_each(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"Dmg%","None","None",50,"The_Glorious_Mysteries");
            ptr->Sub_Unit_ptr[0]->Buff_check["Technique_use"]=1;
            Extend_Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"The_Glorious_Mysteries",2);
        }
        
        Extend_Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"The_Sorrowing_Body",3);
        Extend_Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"Benison_of_Paper_and_Rites",2);
        
        
        
        for(int i=0;i<Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr.size();i++){
            Action_forward(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr[i]->Atv_stats.get(),100);
        }
        for(int i=0;i<Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Summon_ptr.size();i++){
            Action_forward(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Summon_ptr[i]->Atv_stats.get(),100);
        }
        Action_forward(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr[0]->Atv_stats.get(),100);
    }

    void Ult_func(Ally *ptr){
        //if(turn->Name!=Ally_unit[ptr->stats->Target_num]->Atv_stats->Name&&Driver_Type=="Swap_pull")return ;
        if(ult_condition(ptr))return;
        if(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Max_energy<=200&&Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Max_energy - Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Current_energy<30&&Buff_check(ptr->Sub_Unit_ptr[0].get(),"Ode_to_Caress_and_Cicatrix"))return ;
        if(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Max_energy>=200&&Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Max_energy - Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Current_energy<Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Max_energy*0.2&&(Buff_check(ptr->Sub_Unit_ptr[0].get(),"Ode_to_Caress_and_Cicatrix")))return ;
        if(!Ult_use_check(ptr))return;
        if(ptr->Print)cout<<"-------------------------------------------------- Sunday ult at "<<Current_atv<<endl;
        Combat_data data_ = Combat_data();
        data_.Ultimate_set(ptr->Sub_Unit_ptr[0].get(),"Buff","Single_target");
        data_.Add_Buff_Single_Target(Choose_Character_Buff(ptr->Sub_Unit_ptr[0].get()));
        Action_bar.push(data_);
        if(ptr->Eidolon>=2){
            if(ptr->Sub_Unit_ptr[0]->Buff_check["Ult_first_time"]==0){
                ptr->Sub_Unit_ptr[0]->Buff_check["Ult_first_time"]=1;
                Skill_point(ptr->Sub_Unit_ptr[0].get(),2);
            }
            
        }
        if(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Max_energy>200){
            Increase_energy(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),20,0);
        }else{
            Increase_energy(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),0,40);
        }
        if(!Buff_check(ptr->Sub_Unit_ptr[0].get(),"Ode_to_Caress_and_Cicatrix")){
            if(ptr->Eidolon>=2){
            Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"Dmg%","None","None",30);

            }
            ptr->Sub_Unit_ptr[0]->Buff_note["Ode_to_Caress_and_Cicatrix"] = ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"]*0.3+12;
            ptr->Sub_Unit_ptr[0]->Buff_check["Ode_to_Caress_and_Cicatrix"] = 1;

            Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"Crit_dam","None","None",ptr->Sub_Unit_ptr[0]->Buff_note["Ode_to_Caress_and_Cicatrix"]);
        }
        Extend_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Ode_to_Caress_and_Cicatrix",3);
        Deal_damage();
    }
    void Ult_Buff(Ally *ptr){
        if(Buff_check(ptr->Sub_Unit_ptr[0].get(),"Ode_to_Caress_and_Cicatrix")){
            Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"Crit_dam","None","None",-ptr->Sub_Unit_ptr[0]->Buff_note["Ode_to_Caress_and_Cicatrix"]);
            ptr->Sub_Unit_ptr[0]->Buff_note["Ode_to_Caress_and_Cicatrix"] = ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"]*0.3+12;
            Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"Crit_dam","None","None",ptr->Sub_Unit_ptr[0]->Buff_note["Ode_to_Caress_and_Cicatrix"]);

        }
    }
    void Before_turn(Ally *ptr){
        Ult_Buff(ptr);
        
        if(Buff_end(ptr->Sub_Unit_ptr[0].get(),"Ode_to_Caress_and_Cicatrix")){
            Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"Crit_dam","None","None",-ptr->Sub_Unit_ptr[0]->Buff_note["Ode_to_Caress_and_Cicatrix"]);

            if(ptr->Eidolon>=2){
            Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num].get(),"Dmg%","None","None",-30);

            }
            ptr->Sub_Unit_ptr[0]->Buff_check["Ode_to_Caress_and_Cicatrix"] = 0;
            if(ptr->Print)cout<<"-------------------------------------------------- Sunday ult end at "<<Current_atv<<endl;
        }
    }
    void After_turn(Ally *ptr){
        if(turn->Side!="Ally"&&turn->Side!="Memosprite")return;
        if(turn->Unit_num != ptr->Sub_Unit_ptr[0]->Target_num)return;
        Sub_Unit *Temp_stats = dynamic_cast<Sub_Unit*>(turn->ptr_to_unit);
        if(!Temp_stats)return;
        if(Buff_end(Temp_stats,"Benison_of_Paper_and_Rites")){
            if(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Summon_ptr.size()!=0||Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr.size()>1){
            Buff_single_target(Temp_stats,"Dmg%","None","None",-50);
            }else{
            Buff_single_target(Temp_stats,"Dmg%","None","None",-30);
            }
            Temp_stats->Buff_check["Benison_of_Paper_and_Rites"]=0;
            if(ptr->Eidolon>=1){
                if(turn->Side=="Memosprite"){
                    Buff_single_target(Temp_stats,"Def_shred","None","None",-40);
                }else{
                    Buff_single_target(Temp_stats,"Def_shred","None","None",-16);
                    Buff_single_target(Temp_stats,"Def_shred","Summon","None",-24);

                }
        Temp_stats->Buff_check["Sunday_E1"]=0;

                
        }
        }
        if(Buff_end(Temp_stats,"The_Sorrowing_Body")){
            Buff_single_target(Temp_stats,"Crit_rate","None","None",-20);
            Temp_stats->Buff_check["The_Sorrowing_Body"]=0;
        }
        
        if(Buff_end(Temp_stats,"The_Glorious_Mysteries")){
            Buff_single_target(Temp_stats,"Dmg%","None","None",-50);
        }
    }
    void Start_game(Ally *ptr){
        Increase_energy(ptr,25);
    }
    void Before_attack(Ally *ptr, Combat_data &data_){
        
        Ult_Buff(ptr);
    }
    void Buff_func(Ally *ptr, Combat_data &data_){
        
        if(Buff_check(ptr->Sub_Unit_ptr[0].get(),"Ode_to_Caress_and_Cicatrix")&&data_.Action_type.second=="Skill"&&turn->Char_Name=="Sunday"){
            Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
        }
    }
    bool ult_condition(Ally *ptr){
        //if(Current_atv<150&&(Ally_unit[Main_dps_num]->Countdown_ptr[0]->Atv_stats->Base_speed==-1))return true;
        return false;
    }

}
#endif