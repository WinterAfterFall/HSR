
#ifndef Aglaea_H
#define Aglaea_H

#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Aglaea{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
     
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void Before_attack(Ally *ptr,Combat_data &data_);
    void After_attack(Ally *ptr,Combat_data &data_);
    void When_attack(Ally *ptr,Combat_data &data_);
    void Buff(Ally *ptr,Combat_data &data_);
    void Ult_func(Ally *ptr);
    void Tune_stats(Ally *ptr);    
    void Setup_Memo(Ally *ptr);
    void Start_game(Ally *ptr);


    void Mem_turn(Unit *ptr);
    void CountDown_turn(Unit *ptr);  

//temp
    void Basic_Atk(Ally *ptr);
    void Skill(Ally *ptr);
    void Memo_Skill(Ally *ptr);
    void Enchance_Basic_Atk(Ally *ptr);
    void A2(Ally *ptr);


    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();
        SetBaseStats(Ally_unit[num]->Sub_Unit_ptr[0].get(),1242,699,485);
        SetBasicStats(Ally_unit[num].get(),102,350,350,E,"Lightning","Remembrance",num,"Aglaea","Ally",1);

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
        Ally_unit[num]->Char_func.Setup_Memo_func = Setup_Memo;
        Ally_unit[num]->Char_func.When_attack_func = When_attack;
        Ally_unit[num]->Char_func.Before_attack_func = Before_attack;
        Ally_unit[num]->Char_func.After_attack_func = After_attack;
        Ally_unit[num]->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->Char_func.Before_turn_func = Before_turn;
        Ally_unit[num]->Char_func.Buff_func = Buff;
        Ally_unit[num]->Char_func.Start_game_func = Start_game;


        Ally_unit[num]->Element_Orb = 1;
        Ally_unit[num]->Er_Rope = 1;
        Ally_unit[num]->Speed_Boot = 1;
        Ally_unit[num]->Speed_tune_value = 135;
        Aglaea_num = num;



        SetMemoStats(Ally_unit[num].get(),66,35,"Lightning","Garmentmaker","Memosprite");
        SetCountdownStats(Ally_unit[num].get(),"Supreme_Stance");
        Ally_unit[num]->Sub_Unit_ptr[1]->Turn_func = Mem_turn;
        Ally_unit[num]->Countdown_ptr[0]->Turn_func = CountDown_turn;

    }
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Def%"]["None"]+=12.5;
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=12;
        ptr->Sub_Unit_ptr[0]->Stats_each_element["Dmg%"]["Lightning"]["None"]+=22.4;



        //relic
        if(ptr->Body_CritDam){
            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"]+=64.8;
        }else{
            ptr->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"]+=32.4;
        }
        if(ptr->Speed_Boot){
            ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        }else{
            ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        }
        if(ptr->Element_Orb){
            ptr->Sub_Unit_ptr[0]->Stats_each_element["Dmg%"]["Lightning"]["None"]+=38.8;
        }else{
            ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        }
        if(ptr->Er_Rope){
            ptr->Energy_recharge += 19.4;
        }else{
            ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        }


        //substats
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=ptr->Sub_Speed_use;

        //countdown 

        
    }
    void Tune_stats(Ally *ptr){
        Cal_Speed_Needed(ptr,ptr->Speed_tune_value);
    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        if(ally_ptr->ptr_to_unit->Sub_Unit_ptr[1]->Atv_stats->Base_speed==-1){
            Skill(ally_ptr->ptr_to_unit);
        }

        if(ally_ptr->ptr_to_unit->Countdown_ptr[0]->Atv_stats->Base_speed!=-1){
            Enchance_Basic_Atk(ally_ptr->ptr_to_unit);
        }else{
            Basic_Atk(ally_ptr->ptr_to_unit);
        }
            
        
    }
    void Mem_turn(Unit *ptr){
        
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        Memo_Skill(ally_ptr->ptr_to_unit);
        
    }
    void Enchance_Basic_Atk(Ally *ptr){
        Increase_energy(ptr,20);
        Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
        Combat_data data_ = Combat_data();
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Blast");
        data_.Add_Target_Adjacent();
        data_.Turn_reset=true;
        data_.Damage_spilt.Main.push_back({200,0,0,10});
        data_.Damage_spilt.Main.push_back({200,0,0,10});

        data_.Damage_spilt.Adjacent.push_back({90,0,0,5});
        data_.Damage_spilt.Adjacent.push_back({90,0,0,5});
        data_.All_Attacker.push_back(ptr->Sub_Unit_ptr[1].get());
        data_.Attack_trigger++;
        data_.Joint.push_back({1,ptr->Sub_Unit_ptr[1].get()});

        Action_bar.push(data_);
    }
    void Basic_Atk(Ally *ptr){
        Increase_energy(ptr,20);
        Skill_point(ptr->Sub_Unit_ptr[0].get(),1);
        Combat_data data_ = Combat_data();
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Single_target");
        data_.Add_Target(Choose_Enemy_target(ptr->Sub_Unit_ptr[0].get()));
        data_.Turn_reset=true;
        data_.Damage_spilt.Main.push_back({100,0,0,10});
        Action_bar.push(data_);
    }
    void Skill(Ally *ptr){
        Increase_energy(ptr,30);
        Skill_point(ptr->Sub_Unit_ptr[0].get(),-1);
        Combat_data data_ = Combat_data();
        data_.Skill_set(ptr->Sub_Unit_ptr[0].get(),"Single_target","Buff");
        data_.Add_Buff_Single_Target(ptr->Sub_Unit_ptr[0].get());
        data_.Turn_reset=true;
        data_.Buff_type.push_back("Summon");
        
        if(ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed==-1){
            ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed = ptr->Sub_Unit_ptr[0]->Atv_stats->Base_speed*0.35;
            Update_Max_atv(ptr->Sub_Unit_ptr[1]->Atv_stats.get());
            atv_reset(ptr->Sub_Unit_ptr[1]->Atv_stats.get());
            Action_forward(ptr->Sub_Unit_ptr[1]->Atv_stats.get(),100);
            data_.Turn_reset=false;
        }
        Action_bar.push(data_);
    }

    void Ult_func(Ally *ptr){
        if(ptr->Countdown_ptr[0]->Atv_stats->Base_speed!=-1&&(ptr->Countdown_ptr[0]->Atv_stats->atv>ptr->Sub_Unit_ptr[0]->Atv_stats->atv&&(ptr->Sub_Unit_ptr[0]->Atv_stats->atv!=ptr->Sub_Unit_ptr[0]->Atv_stats->Max_atv)))return;
        if(ptr->Sub_Unit_ptr[1]->Atv_stats->atv==0||ptr->Sub_Unit_ptr[0]->Atv_stats->atv==0)return;
        if(!Ult_use_check(ptr))return;
        if(ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed==-1){
            ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed = ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed*0.35;
            Update_Max_atv(ptr->Sub_Unit_ptr[1]->Atv_stats.get());
            atv_reset(ptr->Sub_Unit_ptr[1]->Atv_stats.get());
            Action_forward(ptr->Sub_Unit_ptr[1]->Atv_stats.get(),100);
        }
            Combat_data data_ = Combat_data();
            data_.Ultimate_set(ptr->Sub_Unit_ptr[0].get(),"Single_target","Buff");
            data_.Add_Buff_Single_Target(ptr->Sub_Unit_ptr[0].get());
            if(ptr->Countdown_ptr[0]->Atv_stats->Base_speed==-1)Speed_Buff(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),15*ptr->Sub_Unit_ptr[1]->Stack["Brewed_by_Tears"],0);
            Action_forward(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),100);
            ptr->Countdown_ptr[0]->Atv_stats->Base_speed=100;
            Update_Max_atv(ptr->Countdown_ptr[0]->Atv_stats.get());
            atv_reset(ptr->Countdown_ptr[0]->Atv_stats.get());
            
            A2(ptr);
            Action_bar.push(data_);
            if(ptr->Print)cout<<"---------------------------------------------------- Aglaea Ult START at "<<Current_atv<<endl;

            Deal_damage();        
    }
    void Setup_Memo(Ally *ptr){
        
        
        ptr->Sub_Unit_ptr[1]->Stats_type["Flat_Hp"]["None"]+=720;
        ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed = -1;
    }
    
    void Memo_Skill(Ally *ptr){

        Increase_energy(ptr,10);
        Combat_data data_ = Combat_data();

        data_.Skill_set(ptr->Sub_Unit_ptr[1].get(),"Blast");
        data_.Add_Target_Adjacent();
        data_.Skill_Type.push_back("Summon");
        data_.Turn_reset=true;
        data_.Damage_spilt.Main.push_back({110,0,0,10});
        data_.Damage_spilt.Adjacent.push_back({66,0,0,5});
        if(ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed==-1){
            ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed = ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed*0.35;
            Update_Max_atv(ptr->Sub_Unit_ptr[1]->Atv_stats.get());
            atv_reset(ptr->Sub_Unit_ptr[1]->Atv_stats.get());
            Action_forward(ptr->Sub_Unit_ptr[1]->Atv_stats.get(),100);
            data_.Turn_reset=false;
        }
        Action_bar.push(data_);
    }
    void CountDown_turn(Unit *ptr){
        auto Allyptr = Ally_unit[ptr->Atv_stats->Unit_num].get();
        Speed_Buff(Allyptr->Sub_Unit_ptr[0]->Atv_stats.get(),-15*Allyptr->Sub_Unit_ptr[1]->Stack["Brewed_by_Tears"],0);
        
        Allyptr->Countdown_ptr[0]->Atv_stats->Base_speed=-1;
        Update_Max_atv(Allyptr->Countdown_ptr[0]->Atv_stats.get());
        atv_reset(Allyptr->Countdown_ptr[0]->Atv_stats.get());
        Buff_single_with_all_memo(Allyptr,"Flat_Atk","None","None",-Allyptr->Sub_Unit_ptr[0]->Buff_note["Aglaea_A2"]);
        Allyptr->Sub_Unit_ptr[0]->Buff_note["Aglaea_A2"] = 0;

        Allyptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed = -1;
        Update_Max_atv(Allyptr->Sub_Unit_ptr[1]->Atv_stats.get());
        atv_reset(Allyptr->Sub_Unit_ptr[1]->Atv_stats.get());
        double temp =0;
        if(Allyptr->Sub_Unit_ptr[1]->Stack["Brewed_by_Tears"]>1){
            temp = Allyptr->Sub_Unit_ptr[1]->Stack["Brewed_by_Tears"]-1;
        }
        Speed_Buff(Allyptr->Sub_Unit_ptr[1]->Atv_stats.get(),0,(-55*temp));
        Allyptr->Sub_Unit_ptr[1]->Stack["Brewed_by_Tears"] = 1;
        Increase_energy(Allyptr,20);

        if(Allyptr->Print)cout<<"---------------------------------------------------- Aglaea Ult END at "<<Current_atv<<endl;
    }
    void When_attack(Ally *ptr,Combat_data &data_){
        A2(ptr);
        if(data_.Attacker->Atv_stats->Unit_Name=="Garmentmaker"){
            if(data_.Attacker->Stack["Brewed_by_Tears"]<6){
                Speed_Buff(data_.Attacker->Atv_stats.get(),0,55);
                data_.Attacker->Stack["Brewed_by_Tears"]++;
                if(ptr->Countdown_ptr[0]->Atv_stats->Base_speed!=-1){
                Speed_Buff(data_.Attacker->ptr_to_unit->Sub_Unit_ptr[0]->Atv_stats.get(),15,0);
                }
            }
            
        }
        if(data_.Action_type.second!="Technique"&&data_.Attacker->Atv_stats->Unit_num==ptr->Sub_Unit_ptr[0]->Atv_stats->Unit_num){
            if(Enemy_unit[Main_Enemy_num]->Debuff["Seam_Stitch"]==0){
                Enemy_unit[Main_Enemy_num]->Debuff["Seam_Stitch"]=1;
                if(ptr->Eidolon>=1){
                    Debuff_single_target(Enemy_unit[Main_Enemy_num].get(),"Vul","None","None",15);
                }
            }
            Combat_data data_Additional = Combat_data();
            data_Additional.Additional_set(data_.Attacker,"Single_target");
            Cal_Additional_damage(data_Additional,Enemy_unit[Main_Enemy_num].get(),{30,0,0,0});
            if(ptr->Eidolon>=1){
                Increase_energy(ptr,20);
            }
        }
        
    }
    void A2(Ally *ptr){
        if(ptr->Countdown_ptr[0]->Atv_stats->Base_speed==-1)return;
        Buff_single_with_all_memo(ptr,"Flat_Atk","None","None",-ptr->Sub_Unit_ptr[0]->Buff_note["Aglaea_A2"]);
        ptr->Sub_Unit_ptr[0]->Buff_note["Aglaea_A2"] = ((ptr->Sub_Unit_ptr[0]->Atv_stats->Base_speed+ptr->Sub_Unit_ptr[0]->Atv_stats->Base_speed*ptr->Sub_Unit_ptr[0]->Atv_stats->Speed_percent/100)+ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed)*7.2
        + ((ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed+ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed*ptr->Sub_Unit_ptr[1]->Atv_stats->Speed_percent/100)+ptr->Sub_Unit_ptr[1]->Atv_stats->Flat_speed)*3.6;
        Buff_single_with_all_memo(ptr,"Flat_Atk","None","None",ptr->Sub_Unit_ptr[0]->Buff_note["Aglaea_A2"]);
    }
    void Buff(Ally *ptr,Combat_data &data_){
        if(ptr->Eidolon>=2&&(data_.Attacker->Atv_stats->Unit_Name=="Aglaea"||data_.Attacker->Atv_stats->Unit_Name=="Garmentmaker")){
            Stack_Buff_single_with_all_memo(ptr,"Def_shred","None","None",14,1,3,"Aglaea_E2");
        }
        A2(ptr);
    }    
    void Before_turn(Ally *ptr){
        A2(ptr);
    }
    void After_turn(Ally *ptr){
        A2(ptr);
    }
    void Before_attack(Ally *ptr,Combat_data &data_){
        if(ptr->Eidolon>=2){
            if(data_.Attacker->Atv_stats->Unit_Name=="Aglaea"||data_.Attacker->Atv_stats->Unit_Name=="Garmentmaker"){
                Stack_Buff_single_with_all_memo(ptr,"Def_shred","None","None",14,1,3,"Aglaea_E2");
            }else{
                for(int i=0;i<ptr->Sub_Unit_ptr.size();i++){
                    Buff_single_target(ptr->Sub_Unit_ptr[i].get(),"Def_shred","None","None",ptr->Sub_Unit_ptr[i]->Stack["Aglaea_E2"]*(-14));
                    ptr->Sub_Unit_ptr[i]->Stack["Aglaea_E2"]=0;
                }
            }
        }
        
        A2(ptr);
    }
    void After_attack(Ally *ptr,Combat_data &data_){
        A2(ptr);
    }
    void Start_game(Ally *ptr){
        if(ptr->Technique==1){
        
        Combat_data data_ = Combat_data();
        data_.Technique_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
        data_.Add_Target_Other();
        data_.Damage_spilt.Main.push_back({100,0,0,20});
        data_.Damage_spilt.Adjacent.push_back({100,0,0,20});
        data_.Damage_spilt.Other.push_back({100,0,0,20});
        Increase_energy(ptr,30);
        ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed = ptr->Sub_Unit_ptr[0]->Atv_stats->Base_speed*0.35;
        Update_Max_atv(ptr->Sub_Unit_ptr[1]->Atv_stats.get());
        atv_reset(ptr->Sub_Unit_ptr[1]->Atv_stats.get());
        Action_forward(ptr->Sub_Unit_ptr[1]->Atv_stats.get(),100);
        Action_bar.push(data_);
        Deal_damage();
        }
        
    }
}
#endif