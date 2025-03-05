
#ifndef RMC_H
#define RMC_H

#define F first
#define S second
#include"..\..\Setup.cpp"

namespace RMC{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Mem_turn(Unit *ptr);
    void Start_game(Ally *ptr);
    void When_Combat(Ally *ptr);
    void After_turn(Ally *ptr);
    void Buff(Ally *ptr,Combat_data &data_);
    void Before_turn(Ally *ptr);
    void Before_attack(Ally *ptr,Combat_data &data_);
    void After_attack(Ally *ptr,Combat_data &data_);
    void When_Energy_Increase(Ally *ptr,Ally *target,double Energy);
    

    void Ult_func(Ally *ptr);
    void Tune_stats(Ally *ptr);    
    void Setup_Memo(Ally *ptr);


//temp
    void Basic_Atk(Ally *ptr);
    void Skill(Ally *ptr);
    void Increase_Charge(Ally *ptr,double charge);
    void Memo_Skill(Ally *ptr);
    void Memo_Echance_Skill(Ally *ptr);
    void Mem_Talent_reset(Ally *ptr);


    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();
        SetBaseStats(Ally_unit[num]->Sub_Unit_ptr[0].get(),1048,543,631);
        SetBasicStats(Ally_unit[num].get(),103,160,160,E,"Ice","Remembrance",num,"RMC","Ally",1);

        //substats
        Ally_unit[num]->Total_substats=20;
        Ally_unit[num]->Separate_sub=20;

        Ally_unit[num]->Substats.push_back({"Crit_dam",20});

        Ally_unit[num]->Max_damage_Substats.resize(Ally_unit[num]->Substats.size());


        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        Ally_unit[num]->Sub_Unit_ptr[0]->Turn_func = Turn_func;
        Ally_unit[num]->Ult_func = Ult_func;
        Ally_unit[num]->Char_func.Reset_func = Reset;
        Ally_unit[num]->Char_func.Tune_stats_func = Tune_stats;
        Ally_unit[num]->Char_func.Start_game_func = Start_game;
        Ally_unit[num]->Char_func.When_Combat_func = When_Combat;
        Ally_unit[num]->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->Char_func.Before_turn_func = Before_turn;
        Ally_unit[num]->Char_func.Buff_func = Buff;
        Ally_unit[num]->Char_func.When_Energy_Increase_func = When_Energy_Increase;
        Ally_unit[num]->Char_func.After_attack_func = After_attack;
        Ally_unit[num]->Char_func.Before_attack_func = Before_attack;
        Ally_unit[num]->Char_func.Setup_Memo_func = Setup_Memo;



        SetMemoStats(Ally_unit[num].get(),68,0,"Ice","Mem","Memosprite");
        Ally_unit[num]->Sub_Unit_ptr[1]->Turn_func = Mem_turn;

    }
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=14;
        ptr->Sub_Unit_ptr[0]->Stats_type["Hp%"]["None"]+=14;
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"]+=37.3;

        ptr->Sub_Unit_ptr[0]->Stats_each_element["Dmg%"]["Quantum"]["None"]+=22.4;



        //relic
        ptr->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"]+=64.8;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        ptr->Sub_Unit_ptr[0]->Stats_each_element["Dmg%"]["Ice"]["None"]+=38.8;
        ptr->Energy_recharge += 19.4;


        //substats
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=ptr->Sub_Speed_use;


        
    }
    void Tune_stats(Ally *ptr){
        Cal_Speed_Needed(ptr,150);

    }
    void Increase_Charge(Ally *ptr,double charge){
        if(ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed==-1)return;
        ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Charge"]+=charge;
        if(ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Charge"]>=100){
            ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Charge"]= 0;
            ptr->Sub_Unit_ptr[1]->Buff_check["Mem_Charge"]=1;
            Action_forward(ptr->Sub_Unit_ptr[1]->Atv_stats.get(),100);
        }
    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        if(ally_ptr->Atv_stats->turn_cnt%3!=1){
            Basic_Atk(ally_ptr->ptr_to_unit);
        }else{
            Skill(ally_ptr->ptr_to_unit);
        }
    }
    void Mem_turn(Unit *ptr){
        
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        if(ally_ptr->Buff_check["Mem_Charge"]==1){
            Memo_Echance_Skill(ally_ptr->ptr_to_unit);
        }else{
            Memo_Skill(ally_ptr->ptr_to_unit);
        }
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
        Action_bar.push(data_);
        if(ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed==-1){
            ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed = 130;
            Update_Max_atv(ptr->Sub_Unit_ptr[1]->Atv_stats.get());
            atv_reset(ptr->Sub_Unit_ptr[1]->Atv_stats.get());
            Increase_Charge(ptr,90);
        }
    }

    void Ult_func(Ally *ptr){
        if(ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Charge"]>=60&&Choose_Target_buff(ptr->Sub_Unit_ptr[1].get())->Atv_stats->atv<=20)return;
        if(!Ult_use_check(ptr))return;
            Combat_data data_ = Combat_data();
            data_.Ultimate_set(ptr->Sub_Unit_ptr[1].get(),"Aoe");
            data_.Add_Target_Other();
            data_.Damage_spilt.Main.push_back({264,0,0,20});
            data_.Damage_spilt.Adjacent.push_back({264,0,0,20});
            data_.Damage_spilt.Other.push_back({264,0,0,20});
            Action_bar.push(data_);
            Increase_Charge(ptr,40);
            Buff_single_target(ptr->Sub_Unit_ptr[1].get(),"Crit_rate","None","None",100);
            Deal_damage();
            Buff_single_target(ptr->Sub_Unit_ptr[1].get(),"Crit_rate","None","None",-100);
            if(ptr->Print)cout<<"-------------------------------------------------------- RMC Ult at "<<Current_atv<<endl;
            


    }
    void Setup_Memo(Ally *ptr){
        ptr->Sub_Unit_ptr[1]->Stats_type["Flat_Hp"]["None"]+=688;
        ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed = -1;
    }
    void Memo_Skill(Ally *ptr){

        Increase_energy(ptr,10);
        Combat_data data_ = Combat_data();

        data_.Skill_set(ptr->Sub_Unit_ptr[1].get(),"Aoe");
        data_.Add_Target_Adjacent();
        data_.Skill_Type.push_back("Summon");
        data_.Turn_reset=true;
        if(Total_enemy==1){
            data_.Damage_spilt.Main.push_back({39.6,0,0,5});
            data_.Damage_spilt.Main.push_back({39.6,0,0,5});
            data_.Damage_spilt.Main.push_back({39.6,0,0,5});
            data_.Damage_spilt.Main.push_back({39.6,0,0,5});
        }else if(Total_enemy==2){
            data_.Damage_spilt.Main.push_back({39.6,0,0,5});
            data_.Damage_spilt.Main.push_back({39.6,0,0,5});
            data_.Damage_spilt.Adjacent.push_back({39.6,0,0,5});
            data_.Damage_spilt.Adjacent.push_back({39.6,0,0,5});

        }else{
            data_.Damage_spilt.Main.push_back({39.6,0,0,5});
            data_.Damage_spilt.Main.push_back({39.6,0,0,5});
            data_.Damage_spilt.Adjacent.push_back({39.6,0,0,5});
        }
        data_.Damage_spilt.Main.push_back({99,0,0,10});
        data_.Damage_spilt.Adjacent.push_back({99,0,0,10});
        data_.Damage_spilt.Other.push_back({99,0,0,10});
        Action_bar.push(data_);
        
        Increase_Charge(ptr,5);

    }
    void Memo_Echance_Skill(Ally *ptr){
        Increase_energy(ptr,10);
        ptr->Sub_Unit_ptr[1]->Buff_check["Mem_Charge"]=0;
        Combat_data data_ = Combat_data();
        data_.Skill_set(ptr->Sub_Unit_ptr[1].get(),"Single","Buff");
        data_.Add_Buff_Single_Target(Choose_Target_buff(ptr->Sub_Unit_ptr[1].get()));
        data_.Turn_reset=true;
        data_.Skill_Type.push_back("Summon");
        if(!Buff_check(Choose_Target_buff(ptr->Sub_Unit_ptr[1].get()),"Mem_Support")){
            if(Ally_unit[ptr->Sub_Unit_ptr[1]->Target_num]->Max_energy>=200){
                Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[1]->Target_num].get(),"True_Damage","None","None",30+20);
            }else{
                Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[1]->Target_num].get(),"True_Damage","None","None",30+2*floor((Ally_unit[ptr->Sub_Unit_ptr[1]->Target_num]->Max_energy-100)/10));
            }
            Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[1]->Target_num].get(),"Crit_rate","None","None",10);
            Choose_Target_buff(ptr->Sub_Unit_ptr[1].get())->Buff_check["Mem_Support"]=1;
        }
        Action_forward(Choose_Target_buff(ptr->Sub_Unit_ptr[1].get())->Atv_stats.get(),100);
        
        Extend_Buff_single_target(Choose_Target_buff(ptr->Sub_Unit_ptr[1].get()),"Mem_Support",3);
        if(ptr->Print)cout<<"-------------------------------------------------------- Mem enchance skill at "<<Current_atv<<endl;
        Action_bar.push(data_);
    }
    void After_turn(Ally *ptr){
        Mem_Talent_reset(ptr);
        if(Buff_end(Choose_Target_buff(ptr->Sub_Unit_ptr[1].get()),"Mem_Support")){
             if(Ally_unit[ptr->Sub_Unit_ptr[1]->Target_num]->Max_energy>=200){
            Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[1]->Target_num].get(),"True_Damage","None","None",-50);
        }else{
            Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[1]->Target_num].get(),"True_Damage","None","None",-30-2*floor((Ally_unit[ptr->Sub_Unit_ptr[1]->Target_num]->Max_energy-100)/10));

        }
        Buff_single_with_all_memo(Ally_unit[ptr->Sub_Unit_ptr[1]->Target_num].get(),"Crit_rate","None","None",-10);
        Choose_Target_buff(ptr->Sub_Unit_ptr[1].get())->Buff_check["Mem_Support"]=0;
        }
    }
    void Buff(Ally *ptr,Combat_data &data_){
        Mem_Talent_reset(ptr);
    }
    void Before_turn(Ally *ptr){
        Mem_Talent_reset(ptr);
        ptr->Sub_Unit_ptr[1]->Buff_check["RMC_E2"]=1;
    }
    void Before_attack(Ally *ptr,Combat_data &data_){
        Mem_Talent_reset(ptr);
    }
    void After_attack(Ally *ptr,Combat_data &data_){
        Mem_Talent_reset(ptr);
        if(data_.Attacker->Atv_stats->Unit_Name!="Mem"&&data_.Attacker->Atv_stats->Side=="Memosprite"&&ptr->Sub_Unit_ptr[1]->Buff_check["RMC_E2"]==1){
            Increase_energy(ptr,8);
            ptr->Sub_Unit_ptr[1]->Buff_check["RMC_E2"]=0;
        }
    }
    void When_Combat(Ally *ptr){
        ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Talent_Buff"]=ptr->Sub_Unit_ptr[1]->Stats_type["Crit_dam"]["None"]*0.132+26.4;
        Buff_All_Ally("Crit_dam","None","None",ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Talent_Buff"]);
    }
    void Mem_Talent_reset(Ally *ptr){
        Buff_All_Ally("Crit_dam","None","None",-ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Talent_Buff"]);
        ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Talent_Buff"]=ptr->Sub_Unit_ptr[1]->Stats_type["Crit_dam"]["None"]*0.132+26.4;
        Buff_All_Ally("Crit_dam","None","None",ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Talent_Buff"]);

    }
    void Start_game(Ally *ptr){
        if(ptr->Technique==1){
            for(int i=1;i<=Total_enemy;i++){
                Action_forward(Enemy_unit[i]->Atv_stats.get(),-50);
            }
            Combat_data data_ =Combat_data();
            data_.Technique_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
            data_.Add_Target_Other();
            data_.Damage_spilt.Main.push_back({50,0,0,0});
            data_.Damage_spilt.Adjacent.push_back({50,0,0,0});
            data_.Damage_spilt.Other.push_back({50,0,0,0});

            Action_bar.push(data_);
            
            Deal_damage();
        }
        Action_forward(ptr->Sub_Unit_ptr[0]->Atv_stats.get(),30);

    }
    void When_Energy_Increase(Ally *ptr,Ally *target,double Energy){
        if(ptr->Sub_Unit_ptr[1]->Atv_stats->Base_speed==-1)return;
        if(Energy+target->Current_energy>target->Max_energy){
            Energy = target->Max_energy - target->Current_energy;
        }
        ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Energy_cnt"]+=Energy;
        Increase_Charge(ptr,floor(ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Energy_cnt"]/10));
        ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Energy_cnt"]-=floor(ptr->Sub_Unit_ptr[1]->Buff_note["Mem_Energy_cnt"]/10)*10;
    }
        
    
}
#endif