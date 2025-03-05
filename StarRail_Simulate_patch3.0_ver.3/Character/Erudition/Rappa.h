
#ifndef Rappa_H
#define Rappa_H

#define endl '\n'
#define F first
#define S second
#include"..\..\Setup.cpp"

namespace Rappa{
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Turn_func(Unit *ptr);
    void Enchance_Basic_Atk(Ally *ptr);
    void Skill_func(Ally *ptr);
    void Ult_func(Ally *ptr);//*
    void After_turn(Ally *ptr);
    void After_attack(Ally *ptr, Combat_data &data_);
    void Start_game(Ally *ptr);
    void Tune_stats(Ally *ptr);
    void Toughness_break_func(Ally *ptr,Enemy *target,Sub_Unit *Breaker);
    
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
        Ally_unit[num] = make_unique<Ally>();

        Ally_unit[num]->Sub_Unit_ptr[0]->Base_hp = 1087;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_atk = 718;
        Ally_unit[num]->Sub_Unit_ptr[0]->Base_def = 461;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Base_speed = 96;
        Ally_unit[num]->Max_energy = 140;
        Ally_unit[num]->Ult_cost = 140;
        Ally_unit[num]->Eidolon = E;
        Ally_unit[num]->Sub_Unit_ptr[0]->Element_type.push_back("Imaginary");
        Ally_unit[num]->Path.push_back("Erudition");
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_num = num;
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Char_Name = "Rappa";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Unit_Name = "Rappa";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->Side = "Ally";
        Ally_unit[num]->Sub_Unit_ptr[0]->Atv_stats->ptr_to_unit = Ally_unit[num]->Sub_Unit_ptr[0].get();
        Ally_unit[num]->Ult_priority -=2;

        //func
        LC(Ally_unit[num].get());
        Relic(Ally_unit[num].get());
        Planar(Ally_unit[num].get());
        
        Ally_unit[num]->Sub_Unit_ptr[0]->Turn_func = Turn_func;
        Ally_unit[num]->Ult_func = Ult_func;
        Ally_unit[num]->Char_func.Reset_func = Reset;
        Ally_unit[num]->Char_func.Tune_stats_func = Tune_stats;
        Ally_unit[num]->Char_func.After_turn_func = After_turn;
        Ally_unit[num]->Char_func.After_attack_func = After_attack;
        Ally_unit[num]->Char_func.Start_game_func = Start_game;
        Ally_unit[num]->Char_func.Toughness_break_func = Toughness_break_func;

        

        //substats
        Ally_unit[num]->Total_substats=20;
        Ally_unit[num]->Separate_sub=20;

        Ally_unit[num]->Substats.push_back({"Break_effect",20});

        Ally_unit[num]->Max_damage_Substats.resize(Ally_unit[num]->Substats.size());


    }
    void Reset(Ally *ptr){
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=28;
        ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]+=13.3;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=9;


        //relic
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=25;
        ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]+=43.2;
        ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]+=64.8;
        //ptr->stats->Energy_recharge+=19.4;

        //substats
        ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed+=ptr->Sub_Speed_use;

        //skill
    }
    void Turn_func(Unit *ptr){
        auto ally_ptr = dynamic_cast<Sub_Unit*>(ptr);
        if(ally_ptr->Buff_check["Rappa_Ult"]==0){
            Skill_func(ally_ptr->ptr_to_unit);
        }else{
            Enchance_Basic_Atk(ally_ptr->ptr_to_unit);
        }
    }
    void Enchance_Basic_Atk(Ally *ptr){
        Increase_energy(ptr,20);
        Combat_data data_ = Combat_data();
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Blast");
        data_.Add_Target_Other();
        data_.Turn_reset = 1;
        data_.Dont_care_weakness = 50;
        data_.Damage_spilt.Main.push_back({100,0,0,10});
        data_.Damage_spilt.Main.push_back({100,0,0,10});
        data_.Damage_spilt.Main.push_back({100,0,0,5});
        data_.Damage_spilt.Adjacent.push_back({50,0,0,5});
        data_.Damage_spilt.Adjacent.push_back({50,0,0,5});
        data_.Damage_spilt.Adjacent.push_back({100,0,0,5});
        data_.Damage_spilt.Other.push_back({100,0,0,5});

        double temp = ptr->Sub_Unit_ptr[0]->Stack["Rappa_Talent"]+2;
        ptr->Sub_Unit_ptr[0]->Buff_note["Rappa_Talent"] = ptr->Sub_Unit_ptr[0]->Stack["Rappa_Talent"]*0.5+0.6;
        ptr->Sub_Unit_ptr[0]->Stack["Rappa_Talent"] = 0;

        data_.Damage_spilt.Main.push_back({0,0,0,temp});
        data_.Damage_spilt.Adjacent.push_back({0,0,0,temp});
        data_.Damage_spilt.Other.push_back({0,0,0,temp});

        Action_bar.push(data_);
        ptr->Sub_Unit_ptr[0]->Stack["Rappa_Ult"]--;
        
        
    }
    void Skill_func(Ally *ptr){
        Skill_point(ptr->Sub_Unit_ptr[0].get(),-1);
        Increase_energy(ptr,30);
        Combat_data data_ = Combat_data();
        data_.Skill_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
        data_.Add_Target_Other();
        data_.Turn_reset = 1;
        data_.Damage_spilt.Main.push_back({60,0,0,5});
        data_.Damage_spilt.Main.push_back({60,0,0,5});
        data_.Damage_spilt.Adjacent.push_back({60,0,0,5});
        data_.Damage_spilt.Adjacent.push_back({60,0,0,5});
        data_.Damage_spilt.Other.push_back({60,0,0,5});
        data_.Damage_spilt.Other.push_back({60,0,0,5});

        Action_bar.push(data_);
    }
    void Ult_func(Ally *ptr){
        if(ptr->Sub_Unit_ptr[0]->Buff_check["Rappa_Ult"]==1)return;
        if(!Ult_use_check(ptr))return;
        if(ptr->Print)cout<<"------------------------------------- Rappa Ult Start at "<<Current_atv<<endl;
        ptr->Sub_Unit_ptr[0]->Buff_check["Rappa_Ult"]=1;
        ptr->Sub_Unit_ptr[0]->Stack["Rappa_Ult"]=2;
        ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]+=30;
        ptr->Sub_Unit_ptr[0]->Stats_type["Weakness_Break_Efficiency"]["None"]+=50;
        if(ptr->Eidolon>=1){
            ptr->Sub_Unit_ptr[0]->Stats_type["Def_shred"]["None"]+=15;
        }

        Combat_data data_ = Combat_data();
        data_.Ultimate_set(ptr->Sub_Unit_ptr[0].get(),"Single_target","Buff");
        data_.Add_Buff_Single_Target(ptr->Sub_Unit_ptr[0].get());
        Action_bar.push(data_);
        Deal_damage();
        
        //extra turn
        Increase_energy(ptr,20);
        data_ = Combat_data();
        data_.Basic_Attack_set(ptr->Sub_Unit_ptr[0].get(),"Blast");
        data_.Add_Target_Other();
        data_.Damage_spilt.Main.push_back({100,0,0,10});
        data_.Damage_spilt.Main.push_back({100,0,0,10});
        data_.Damage_spilt.Main.push_back({100,0,0,5});
        data_.Damage_spilt.Adjacent.push_back({50,0,0,5});
        data_.Damage_spilt.Adjacent.push_back({50,0,0,5});
        data_.Damage_spilt.Adjacent.push_back({100,0,0,5});
        data_.Damage_spilt.Other.push_back({100,0,0,5});

        double temp = ptr->Sub_Unit_ptr[0]->Stack["Rappa_Talent"]+2;
        ptr->Sub_Unit_ptr[0]->Buff_note["Rappa_Talent"] = ptr->Sub_Unit_ptr[0]->Stack["Rappa_Talent"]*0.5+0.6;
        ptr->Sub_Unit_ptr[0]->Stack["Rappa_Talent"] = 0;
        data_.Damage_spilt.Main.push_back({0,0,0,temp});
        data_.Damage_spilt.Adjacent.push_back({0,0,0,temp});
        data_.Damage_spilt.Other.push_back({0,0,0,temp});
        Action_bar.push(data_);
        
        Deal_damage();
        
    }
    void Tune_stats(Ally *ptr){
        Cal_Speed_Needed(ptr,145);
    }
    void After_turn(Ally *ptr){
        if(turn->Side=="Enemy"){
            if(Debuff_end(Enemy_unit[turn->Unit_num].get(),"Withered_Leaf")){
                Debuff_single_target(Enemy_unit[turn->Unit_num].get(),"Vul","Break_dmg","None",-Enemy_unit[turn->Unit_num]->Debuff["Withered_Leaf"]);
                Enemy_unit[turn->Unit_num]->Debuff["Withered_Leaf"]=0;
                Enemy_unit[turn->Unit_num]->Total_debuff--;
            }
        }
        if(turn->Char_Name=="Rappa"){
            if(ptr->Sub_Unit_ptr[0]->Stack["Rappa_Ult"]==0&&ptr->Sub_Unit_ptr[0]->Buff_check["Rappa_Ult"]==1){
            ptr->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"]-=30;
            ptr->Sub_Unit_ptr[0]->Stats_type["Weakness_Break_Efficiency"]["None"]-=50;
            
            ptr->Sub_Unit_ptr[0]->Buff_check["Rappa_Ult"]=0;
            if(ptr->Eidolon>=1){
            ptr->Sub_Unit_ptr[0]->Stats_type["Def_shred"]["None"]-=15;
            Increase_energy(ptr,20);
            }
            if(ptr->Print==1){
                cout<<" --------------Rappa Ult End at     "<<Current_atv<<endl;
            }
        }
        }
    }
    void After_attack(Ally *ptr, Combat_data &data_){
        if(data_.Attacker->Atv_stats->Char_Name=="Rappa"){
            if(ptr->Sub_Unit_ptr[0]->Buff_check["Rappa_Ult"]==1){
                Superbreak_trigger(data_,60);

                Combat_data data_ = Combat_data();
                data_.Break_dmg_set(ptr->Sub_Unit_ptr[0].get());
                double temp = ptr->Sub_Unit_ptr[0]->Buff_note["Rappa_Talent"];

                for(int i=1;i<=Total_enemy;i++){
                    Cal_Break_damage( data_,Enemy_unit[i].get(),temp);
                }
                ptr->Sub_Unit_ptr[0]->Buff_note["Rappa_Talent"] = 0;
            }
        }
    }
    void Start_game(Ally *ptr){
        if(ptr->Technique==1){
            Increase_energy(ptr,10);
            for(int i=1;i<=Total_enemy;i++){
                Combat_data data_ = Combat_data();
                double temp;
                data_.Break_dmg_set(ptr->Sub_Unit_ptr[0].get());
                
                
                if(Enemy_unit[i]->Target_type=="Main"){
                    temp = 2;
                    Cal_Break_damage( data_,Enemy_unit[i].get(),temp);
                }else{
                    temp = 1.8;
                    Cal_Break_damage( data_,Enemy_unit[i].get(),temp);
                }
                data_ = Combat_data();
                data_.Technique_set(ptr->Sub_Unit_ptr[0].get(),"Aoe");
                data_.Add_Target_Other();
                Cal_Toughness_reduction(data_,Enemy_unit[i].get(),30);
            }
        }
    }
    void Toughness_break_func(Ally *ptr,Enemy *target,Sub_Unit *Breaker){

        ptr->Sub_Unit_ptr[0]->Stack["Rappa_Talent"]++;
        if(target->Max_toughness>90){
            ptr->Sub_Unit_ptr[0]->Stack["Rappa_Talent"]++;
            Increase_energy(ptr,10);
        }
        if(target->Debuff["Withered_Leaf"]<=0){
            target->Total_debuff++;
        }
        Debuff_single_target(target,"Vul","Break_dmg","None",-target->Debuff["Withered_Leaf"]);
        target->Debuff["Withered_Leaf"] = floor((((ptr->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"]/100*ptr->Sub_Unit_ptr[0]->Base_atk+ptr->Sub_Unit_ptr[0]->Base_atk)+ptr->Sub_Unit_ptr[0]->Stats_type["Flat_Atk"]["None"])-2400)/100)+2;
        if(target->Debuff["Withered_Leaf"]>10){
            target->Debuff["Withered_Leaf"] = 10;   
        }
        if(target->Debuff["Withered_Leaf"]<0){
           target->Debuff["Withered_Leaf"] = 0;  
        }
        Apply_debuff(ptr->Sub_Unit_ptr[0].get(),target);
        Debuff_single_target(target,"Vul","Break_dmg","None",target->Debuff["Withered_Leaf"]);
        Extend_Debuff_single_target(target,"Withered_Leaf",2);

    }
}
#endif
