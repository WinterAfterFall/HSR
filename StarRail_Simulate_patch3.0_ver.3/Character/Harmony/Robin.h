
#ifndef Robin_H
#define Robin_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Robin{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    
    void Turn_func(Unit *ptr);
    void Ult_func(Ally *ptr);
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void When_Combat(Ally *ptr);
    void Before_attack(Ally *ptr, Combat_data &data_);
    void When_attack(Ally *ptr,Combat_data &data_);
    void Start_game(Ally *ptr);
    void Start_wave(Ally *ptr);
    
    //temp
    void Basic_Atk(Ally *ptr);
    void Skill(Ally *ptr);
    bool Double_Turn(Ally *ptr);
    bool Ult_Condition(Ally *ptr);
    void Ult_Atk_buff(Ally *ptr);

    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->Sub_Unit_ptr[0]->Base_hp = 1280;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_atk = 640;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_def = 485;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Base_speed = 102;
        Ally_unit[num]->Max_energy = 160;
        Ally_unit[num]->Ult_cost = 160;
        Ally_unit[num]->Eidolon = E;
        Ally_unit[num]->Sub_Unit_ptr[0]->Element_type.push_back("Physical");
        Ally_unit[num]->Path.push_back("Harmony");
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_num = num;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Char_Name = "Robin";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_Name = "Robin";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->ptr_to_unit = Ally_unit[num]->Sub_Unit_ptr[0].get();
        Robin_num = num;
        Ally_unit[num]->Ult_priority +=1;
        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());

        Ally_unit[num]->Sub_Unit_ptr[0]->Turn_func = Turn_func;
        Ally_unit[num]->Ult_func = Ult_func;
        Ally_unit[num]->Char_func.Reset_func = Reset;
        Ally_unit[num]->Char_func.Before_turn_func = Before_turn;
        Ally_unit[num]->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->Char_func.When_attack_func = When_attack;
        Ally_unit[num]->Char_func.Before_attack_func = Before_attack;
        Ally_unit[num]->Char_func.Start_wave_func = Start_wave;
        Ally_unit[num]->Char_func.Start_game_func = Start_game;
        Ally_unit[num]->Char_func.When_Combat_func = When_Combat;


        //countdown
        Ally_unit[num]->Countdown_ptr.resize(1);
        Ally_unit[num]->Countdown_ptr[0] =  make_unique<Unit>();
        Ally_unit[num]->Countdown_ptr[0]->Atv_stats->Base_speed = -1;
        Ally_unit[num]->Countdown_ptr[0]->Atv_stats->Unit_num = num;
        Ally_unit[num]->Countdown_ptr[0]->Atv_stats->Char_Name = "Concerto_state";
        Ally_unit[num]->Countdown_ptr[0]->Atv_stats->Unit_Name = "Concerto_state";
        Ally_unit[num]->Countdown_ptr[0]->Atv_stats->Side = "Countdown";
        Ally_unit[num]->Countdown_ptr[0]->Atv_stats->ptr_to_unit = Ally_unit[num]->Countdown_ptr[0].get();
        Ally_unit[num]->Countdown_ptr[0]->Turn_func = [](Unit *x){

            auto ptr = Ally_unit[x->Atv_stats->Unit_num].get();

            if( ptr->Countdown_ptr[0]->Atv_stats->Base_speed == 90){
                ptr->Countdown_ptr[0]->Atv_stats->Base_speed = -1;
                ptr->Sub_Unit_ptr[0]->Atv_stats->Base_speed = 102;
                Update_Max_atv(ptr->Sub_Unit_ptr[0]->Atv_stats.get());
                Update_Max_atv(ptr->Countdown_ptr[0]->Atv_stats.get());
                atv_reset(ptr->Sub_Unit_ptr[0]->Atv_stats.get());
                atv_reset(ptr->Countdown_ptr[0]->Atv_stats.get());
                Buff_All_Ally("Flat_Atk","None","None",-ptr->Sub_Unit_ptr[0]->Buff_note["Concerto_state"]);
                Buff_All_Ally("Crit_dam","Fua","None",-25);
                if(ptr->Eidolon>=1){
                        Buff_All_Ally("Respen","None","None",-24);
                    }

                if(ptr->Eidolon>=2){
                    Speed_Buff_All_Ally_Exclude_Buffer(-16,0,"Robin");
                }
                }
                Action_forward(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),100);
                if(ptr->Print){
                    cout<<"-----------------------------------------------------------------------Robin Ult End at "<<Current_atv<<endl;
                }
            };
        
        
    }
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=28;
        ptr->Sub_Unit_ptr[0]->Stats_type["Hp%"]["None"]+=18;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=5;
        

        //relic
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Energy_recharge+=19.4;

        //substats
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=54.432; //14
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=13.8; //5

        ptr->Countdown_ptr[0]->Atv_stats->Base_speed = -1;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Base_speed = 102;
        return;
    }
    void When_Combat(Ally *ptr){
        Buff_All_Ally("Crit_dam","None","None",20);
    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        if(!Buff_check(ally_ptr,"Pinion'sAria")){
            Skill(ally_ptr->ptr_to_unit);           
        }else{
            
            Basic_Atk(ally_ptr->ptr_to_unit);
        }
    }
    void Skill(Ally *ptr){
        Skill_point(ptr->Sub_Unit_ptr[0].get(),-1);
        Increase_energy(ptr,35);
        Combat_data data_ = Combat_data();
        data_.Skill_set(ptr->Sub_Unit_ptr[0].get(),"Single_target","Buff");
        data_.Add_Buff_Single_Target(ptr->Sub_Unit_ptr[0].get());
        data_.Turn_reset = 1;
        Buff_All_Ally("Dmg%","None","None",50);
        ptr->Sub_Unit_ptr[0]->Buff_check["Pinion'sAria"] = 1;
        Extend_Buff_single_target(ptr->Sub_Unit_ptr[0].get(),"Pinion'sAria",3);
        Action_bar.push(data_);
    }
    void Basic_Atk(Ally *ptr){
        Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
        Increase_energy(ptr,20);
        Combat_data data_ = Combat_data();
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");
        data_.Add_Target(Choose_Enemy_target(ptr->Sub_Unit_ptr[0].get()));
        data_.Turn_reset = 1;
        data_.Damage_spilt.Main.push_back({100,0,0,10});
        Action_bar.push(data_);
    }
    bool Double_Turn(Ally *ptr){
        Sub_Unit *target =Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr[ptr->Sub_Unit_ptr[0]->Sub_Unit_num].get();

        if((Ally_unit[Driver_num]->Sub_Unit_ptr[0]->Atv_stats->atv<Ally_unit[Driver_num]->Sub_Unit_ptr[0]->Atv_stats->Max_atv*0.2 || target->Atv_stats->atv<target->Atv_stats->Max_atv*0.2))return 1;
        if((Ally_unit[Driver_num]->Sub_Unit_ptr[0]->Atv_stats->atv < target->Atv_stats->atv))return 1;

        return 0;
    }
    bool Ult_Condition(Ally *ptr){
        //if(Current_atv<150&&(Ally_unit[Main_dps_num]->Countdown_ptr[0]->Atv_stats->Base_speed==-1))return true;
            
        for(int i=0;i<Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Summon_ptr.size();i++){
            if(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Summon_ptr[i]->Atv_stats->atv==0)return true;
        }
        for(int i=0;i<Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr.size();i++){
            if(Ally_unit[ptr->Sub_Unit_ptr[0]->Target_num]->Sub_Unit_ptr[i]->Atv_stats->atv==0)return true;
        }
        return false;
    }
    void Ult_func(Ally *ptr){
        //return;
        if(Driver_Type=="Double_turn"){
            if(Double_Turn(ptr))return;
        }else if(Driver_Type=="Swap_pull"){
            //if(Ally_unit[Driver_num]->Atv_stats->atv <= Ally_unit[Main_dps_num]->Atv_stats->atv &&Ally_unit[Main_dps_num]->Sub_Unit_ptr[0]->Summon_ptr==nullptr)return;
            
        }else if(Driver_Type=="Always_pull"){
            // if(Ally_unit[Driver_num]->Atv_stats->Name=="Hanabi"){
            //     if(Ally_unit[Driver_num]->Atv_stats->atv <= Ally_unit[Main_dps_num]->Atv_stats->atv )return;
            // }
            // if(Ally_unit[Driver_num]->Atv_stats->Name=="Sunday"){
            //     if(Ally_unit[Main_dps_num]->Sub_Unit_ptr[0]->Summon_ptr==nullptr){
            //         if(Ally_unit[Driver_num]->Atv_stats->atv <= Ally_unit[Main_dps_num]->Atv_stats->atv )return;
            //     }else{
            //     if(Ally_unit[Main_dps_num]->Atv_stats->turn_cnt <2||Ally_unit[Main_dps_num]->Sub_Unit_ptr[0]->Summon_ptr->Atv_stats->atv==0)return;
            //     if(Ally_unit[Driver_num]->Atv_stats->atv <=Ally_unit[Driver_num]->Atv_stats->Max_atv*0.5 )return;
            //     }
                
            // }
        }else{
            if(Choose_Target_buff(ptr->Sub_Unit_ptr[0].get())->Atv_stats->atv < Choose_Target_buff(ptr->Sub_Unit_ptr[0].get())->Atv_stats->Max_atv*0.5 )return;
        }
        if(Ult_Condition(ptr))return;
        if( ptr->Countdown_ptr[0]->Atv_stats->Base_speed != 90&&ptr->Sub_Unit_ptr[0]->Buff_countdown["Pinion'sAria"]>ptr->Sub_Unit_ptr[0]->Atv_stats->turn_cnt&&Ult_use_check(ptr)){
            ptr->Countdown_ptr[0]->Atv_stats->Base_speed = 90;
            
            ptr->Sub_Unit_ptr[0]->Atv_stats->Base_speed = -1;
            Update_Max_atv(ptr->Sub_Unit_ptr[0]->Atv_stats.get());
            Update_Max_atv(ptr->Countdown_ptr[0]->Atv_stats.get());
            atv_reset(ptr->Sub_Unit_ptr[0]->Atv_stats.get());
            atv_reset(ptr->Countdown_ptr[0]->Atv_stats.get());
            ptr->Sub_Unit_ptr[0]->Buff_note["Concerto_state"] = ((ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]/100*ptr->Sub_Unit_ptr[0]->Base_atk+ptr->Sub_Unit_ptr[0]->Base_atk)+ptr->Sub_Unit_ptr[0]->Stats_type["Flat_Atk"]["None"])*0.228+200;

            Buff_All_Ally("Flat_Atk","None","None",ptr->Sub_Unit_ptr[0]->Buff_note["Concerto_state"]);
            Buff_All_Ally("Crit_dam","Fua","None",25);
            if(ptr->Eidolon>=1){
                    Buff_All_Ally("Respen","None","None",24);
                }

            if(ptr->Eidolon>=2){
                Speed_Buff_All_Ally_Exclude_Buffer(16,0,"Robin");
            }
        
        All_Action_forward(100);
        Combat_data data_ = Combat_data();
        data_.Ultimate_set(ptr->Sub_Unit_ptr[0].get(),"Aoe","Buff");
        data_.Add_Buff_All_Ally();
        Action_bar.push(data_);
        if(ptr->Print){
            cout<<"---------------------------------------------------------Robin Ult at "<<Current_atv<<endl;
            
        }
        
        Deal_damage();
        }
        return;
    }
    void Ult_Atk_buff(Ally *ptr){
        if(ptr->Sub_Unit_ptr[0]->Atv_stats->Base_speed!=-1)return;
        Buff_All_Ally("Flat_Atk","None","None",-ptr->Sub_Unit_ptr[0]->Buff_note["Concerto_state"]);
        ptr->Sub_Unit_ptr[0]->Buff_note["Concerto_state"] = ((ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]/100*ptr->Sub_Unit_ptr[0]->Base_atk+ptr->Sub_Unit_ptr[0]->Base_atk)+ptr->Sub_Unit_ptr[0]->Stats_type["Flat_Atk"]["None"])*0.228+200;
        Buff_All_Ally("Flat_Atk","None","None",ptr->Sub_Unit_ptr[0]->Buff_note["Concerto_state"]);    
    }
    void Before_turn(Ally *ptr){
        if(Buff_end(ptr->Sub_Unit_ptr[0].get(),"Pinion'sAria")){
            Buff_All_Ally("Dmg%","None","None",-50);
            ptr->Sub_Unit_ptr[0]->Buff_check["Pinion'sAria"] = 0;
        }
        Ult_Atk_buff(ptr);
    }
    void After_turn(Ally *ptr){
        Ult_Atk_buff(ptr);

    }
    void Before_attack(Ally *ptr, Combat_data &data_){
        Ult_Atk_buff(ptr);
    }
    void When_attack(Ally *ptr,Combat_data &data_){
        Increase_energy(ptr,2);
        if(ptr->Eidolon>=2){
            Increase_energy(ptr,1);
        }
        if( ptr->Countdown_ptr[0]->Atv_stats->Base_speed == 90){

        Combat_data data_ = Combat_data();
        double x1=0,x2=0;
        data_.Additional_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");

        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=100;
        x1 = ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"];
        x2 = Enemy_unit[Main_Enemy_num]->Stats_type["Crit_dam"]["None"];
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"] = 150;
        Enemy_unit[Main_Enemy_num]->Stats_type["Crit_dam"]["None"]= 0;
        
        Cal_Additional_damage(data_,Enemy_unit[Main_Enemy_num].get(),{120,0,0,0});
        
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]-=100;
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"] = x1;
        Enemy_unit[Main_Enemy_num]->Stats_type["Crit_dam"]["None"] = x2;


        }
    }
    void Start_wave(Ally *ptr){
        if(ptr->Technique==1){
            Increase_energy(ptr,5);
        }
    }
    void Start_game(Ally *ptr){
        Action_forward(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),25);
    }
    
}
    
#endif
