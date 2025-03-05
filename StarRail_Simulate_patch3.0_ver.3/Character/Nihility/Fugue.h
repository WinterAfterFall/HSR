
// #ifndef Fugue_H
// #define Fugue_H

// #define endl '\n'
// #define F first
// #define S second
// #include"..\..\Setup.cpp"

// namespace Fugue{
//     void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
//     void Reset(Ally *ptr);
//     void Turn_func(Unit *ptr);
//     void Enchance_Basic_Atk(Ally *ptr);
//     void Skill_func(Ally *ptr);
//     void Ult_func(Ally *ptr);//*
//     void Before_turn(Ally *ptr);
//     void After_turn(Ally *ptr);
//     void Before_attack(Ally *ptr, Combat_data &data_);
//     void After_attack(Ally *ptr, Combat_data &data_);
//     void Start_game(Ally *ptr);
//     void Tune_stats(Ally *ptr);
//     void Toughness_break_func(Ally *ptr,Enemy *target,Ally *Breaker);
    
//     void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar){
//         Ally_unit[num] = make_unique<Ally>();

//         Ally_unit[num]->stats->Base_hp = 1125;
//         Ally_unit[num]->stats->Base_atk = 582;
//         Ally_unit[num]->stats->Base_def = 558;
//         Ally_unit[num]->Atv_stats->Base_speed = 102;
//         Ally_unit[num]->Max_energy = 130;
//         Ally_unit[num]->Ult_cost = 130;
//         Ally_unit[num]->Eidolon = E;
//         Ally_unit[num]->stats->Element_type[0] = "Fire";
//         Ally_unit[num]->Path[0] = "Nihility";
//         Ally_unit[num]->Atv_stats->Character_num = num;
//         Ally_unit[num]->Atv_stats->Name = "Fugue";
//         Ally_unit[num]->Atv_stats->Side = "Ally";
//         Ally_unit[num]->Atv_stats->ptr_to_unit = Ally_unit[num].get();
//         unit[num] = Ally_unit[num]->Atv_stats->ptr_to_unit;
//         Ally_unit[num]->stats->Ult_priority +=0;

//         //func
//         LC(Ally_unit[num].get());
//         Relic(Ally_unit[num].get());
//         Planar(Ally_unit[num].get());
        
//         Ally_unit[num]->Turn_func = Turn_func;
//         Ally_unit[num]->stats->Ult_func = Ult_func;
//         Ally_unit[num]->stats->Char_func.Reset_func = Reset;
//         Ally_unit[num]->stats->Tune_stats_func = Tune_stats;
//         Ally_unit[num]->stats->Char_func.Before_turn_func = Before_turn;
//         Ally_unit[num]->stats->Char_func.After_turn_func = After_turn;
//         Ally_unit[num]->stats->Char_func.Before_attack_func = Before_attack;
//         Ally_unit[num]->stats->Char_func.After_attack_func = After_attack;
//         Ally_unit[num]->stats->Char_func.Start_game_func = Start_game;
//         Ally_unit[num]->stats->Char_func.Toughness_break_func = Toughness_break_func;

        

//         //substats
//         Ally_unit[num]->stats->Total_substats=20;
//         Ally_unit[num]->stats->Separate_sub=20;

//         Ally_unit[num]->stats->Substats.push_back({"Break_effect",20});

//         Ally_unit[num]->stats->Max_damage_Substats.resize(Ally_unit[num]->stats->Substats.size());


//     }
//     void Reset(Ally *ptr){
//         ptr->Hp_percent["None"]+=10;
//         ptr->Break_effect["None"]+=24;
//         ptr->Atv_stats->Flat_speed+=14;


//         //relic
//         ptr->Effect_hit_rate+=43.2;
//         ptr->Atv_stats->Flat_speed+=25;
//         ptr->Atk_percent["None"]+=43.2;
//         //ptr->Break_effect["None"]+=64.8;
//         ptr->stats->Energy_recharge+=19.4;

//         //substats
//         ptr->Effect_hit_rate+=ptr->stats->Sub_effect_hit_rate_use;
//         ptr->Atv_stats->Flat_speed+=ptr->stats->Sub_Speed_use;

//         //skill
//         ptr->Break_effect["None"]+=30;
//     }
//     void Turn_func(Unit *ptr){
//         auto ally_ptr = dynamic_cast<Ally*>(ptr);
//         if(ally_ptr->stats->Buff_check["Fugue_Skill"]==0){
//             Skill_func(ally_ptr);
//         }else{
//             Enchance_Basic_Atk(ally_ptr);
//         }
//     }
//     void Enchance_Basic_Atk(Ally *ptr){
//         Skill_point(1);
//         Increase_energy(ptr->stats.get(),20);
//         Combat_data data_;
//         data_.num = ptr->Atv_stats->Character_num;
//         data_.Turn_reset = 1;

//         data_.Action_type.first="Attack";
//         data_.Action_type.second = "Basic_Attack";

//         data_.Damage_element="Fire";
//         data_.Damage_type.push_back("Basic_Attack");

//         data_.Target_type="Blast";
//         data_.Damage_spilt.Main.push_back({100,0,0,10});
//         data_.Damage_spilt.Adjacent.push_back({50,0,0,5});
//         Action_bar.push(data_);
        
        
//     }
//     void Skill_func(Ally *ptr){
//         Skill_point(-1);
//         if(ptr->Atv_stats->turn_cnt==1)Skill_point(1);
//         Increase_energy(ptr->stats.get(),30);

//         ptr->stats->Buff_check["Fugue_Skill"]=1;
//         ptr->stats->Buff_check["Fugue_Skill"]=ptr->Atv_stats->turn_cnt+3;
//         Ally_unit[Main_dps_num]->Break_effect["None"]+=30;
//         if(ptr->stats->Eidolon>=1)Ally_unit[Main_dps_num]->Weakness_Break_Efficiency["None"]+=50;


//         Combat_data data_;
//         data_.num = ptr->Atv_stats->Character_num;
//         data_.Turn_reset = 1;

//         data_.Action_type.first="Buff";
//         data_.Action_type.second = "Skill";

//         data_.Buff_type.push_back("Buff");

//         data_.Target_type="Single_target";
//         Action_bar.push(data_);
//     }
//     void Ult_func(Ally *ptr){
//         if(!Ult_use_check(ptr))return;
//         if(ptr->stats->Eidolon>=2){
//         All_Action_forward(24,1,Total_ally);
//         if(ptr->Print)cout<<" ------------------------------------- Fugue ult at "<<Current_atv<<endl;
//         }
//         Combat_data data_;
//         data_.num = ptr->Atv_stats->Character_num;

//         data_.Action_type.first="Attack";
//         data_.Action_type.second = "Ultimate";

//         data_.Damage_element="Fire";
//         data_.Damage_type.push_back("Ultimate");

//         data_.Target_type="Aoe";
//         data_.Damage_spilt.Main.push_back({200,0,0,20});
//         data_.Damage_spilt.Adjacent.push_back({200,0,0,20});
//         data_.Damage_spilt.Other.push_back({200,0,0,20});
//         Action_bar.push(data_);
//         Deal_damage();
        
//     }
//     void Tune_stats(Ally *ptr){
//         Cal_effect_hit_rate(ptr,100);
//         Cal_Speed_Needed(ptr,145);
//     }
//     void Before_turn(Ally *ptr){
//         if(turn->Name=="Fugue"){
//             if(ptr->stats->Buff_check["Fugue_Skill"]==ptr->Atv_stats->turn_cnt){
//                 ptr->stats->Buff_check["Fugue_Skill"]=0;
//                 Ally_unit[Main_dps_num]->Break_effect["None"]-=30;
//                 if(ptr->stats->Eidolon>=1)Ally_unit[Main_dps_num]->Weakness_Break_Efficiency["None"]-=50;

//             }
//         }
//     }
//     void After_turn(Ally *ptr){
//         if(turn->Side=="Enemy"){
//             if(Enemy_unit[turn->Character_num]->stats->Debuff_time_count["Torrid_Scorch"]==Enemy_unit[turn->Character_num]->Atv_stats->turn_cnt){
//                 Enemy_unit[turn->Character_num]->Def_shred["None"]-=18;
//                 Enemy_unit[turn->Character_num]->stats->Total_debuff--;
//                 Enemy_unit[turn->Character_num]->stats->Debuff["Torrid_Scorch"]=0;
//             }
//             if(Enemy_unit[turn->Character_num]->stats->Debuff["Cloudflame_Luster"]==1){
//                 Enemy_unit[turn->Character_num]->stats->Debuff["Cloudflame_Luster"]=0;
//             }

//         }
//         if(turn->Side=="Ally"&&Ally_unit[turn->Character_num]->Atv_stats->Name!="Fugue"){
//             if(Ally_unit[turn->Character_num]->stats->Buff_countdown["Phecda Primordia"] == Ally_unit[turn->Character_num]->Atv_stats->turn_cnt){
//                 Ally_unit[turn->Character_num]->Break_effect["None"]-=18*Ally_unit[turn->Character_num]->stats->Stack["Phecda Primordia"];
//                 Ally_unit[turn->Character_num]->stats->Stack["Phecda Primordia"] = 0;
//             }
//         }
//     }
//     void Before_attack(Ally *ptr, Combat_data &data_){
//         if(Main_dps_num==data_.num){
            
//             if(ptr->stats->Buff_check["Fugue_Skill"]==1){
//             if(data_.Dont_care_weakness<50){
//                 data_.Dont_care_weakness=50;
//             }
            
//             int sz2 = data_.Damage_spilt.Adjacent.size();
//             int sz3 = data_.Damage_spilt.Other.size();
//             for(int i=1;i<=Total_enemy;i++){

//             if(Enemy_unit[i]->stats->Target_type=="Main"){
//                 Apply_debuff(Ally_unit[Main_dps_num].get(),Enemy_unit[i].get());
//                 Enemy_unit[i]->stats->Debuff_time_count["Torrid_Scorch"]=Enemy_unit[i]->Atv_stats->turn_cnt+2;
//                 if(Enemy_unit[i]->stats->Debuff["Torrid_Scorch"]==1)continue;
//                 Enemy_unit[i]->stats->Total_debuff++;
//                 Enemy_unit[i]->stats->Debuff["Torrid_Scorch"]=1;
//                 Enemy_unit[i]->Def_shred["None"]+=18;
//             }
            
//             if(0<sz2 && Enemy_unit[i]->stats->Target_type=="Adjacent"){
//                 Apply_debuff(Ally_unit[Main_dps_num].get(),Enemy_unit[i].get());
//                 Enemy_unit[i]->stats->Debuff_time_count["Torrid_Scorch"]=Enemy_unit[i]->Atv_stats->turn_cnt+2;
//                 if(Enemy_unit[i]->stats->Debuff["Torrid_Scorch"]==1)continue;
//                 Enemy_unit[i]->stats->Total_debuff++;
//                 Enemy_unit[i]->stats->Debuff["Torrid_Scorch"]=1;
//                 Enemy_unit[i]->Def_shred["None"]+=18;
//             }
            
//             if(0<sz3 && Enemy_unit[i]->stats->Target_type=="Other"){
//                 Apply_debuff(Ally_unit[Main_dps_num].get(),Enemy_unit[i].get());
//                 Enemy_unit[i]->stats->Debuff_time_count["Torrid_Scorch"]=Enemy_unit[i]->Atv_stats->turn_cnt+2;
//                 if(Enemy_unit[i]->stats->Debuff["Torrid_Scorch"]==1)continue;
//                 Enemy_unit[i]->stats->Total_debuff++;
//                 Enemy_unit[i]->stats->Debuff["Torrid_Scorch"]=1;
//                 Enemy_unit[i]->Def_shred["None"]+=18;
//             }
            
            
//         }
//         }
//         }
//     }
//     void After_attack(Ally *ptr, Combat_data &data_){
//         Superbreak_trigger(data_,100);
//         for(int i=1;i<=Total_enemy;i++){
//             if(Enemy_unit[i]->stats->Debuff["Cloudflame_Luster"]==1&&Enemy_unit[i]->stats->Current_toughness*(-1)>=Enemy_unit[i]->stats->Max_toughness*0.4){

//                 Toughness_break(data_,Enemy_unit[i].get());
//                 Enemy_unit[i]->stats->Debuff["Cloudflame_Luster"]=0;
//             }
//         }
        
//     }
//     void Start_game(Ally *ptr){
//         if(ptr->stats->Technique==1){
//             Action_forward(ptr->Atv_stats.get(),40);
//             for(int i=1;i<=Total_enemy;i++){
//                 Apply_debuff(ptr,Enemy_unit[i].get());
//                 Enemy_unit[i]->stats->Debuff_time_count["Torrid_Scorch"]=Enemy_unit[i]->Atv_stats->turn_cnt+2;
//                 if(Enemy_unit[i]->stats->Debuff["Torrid_Scorch"]==1)continue;
//                 Enemy_unit[i]->stats->Total_debuff++;
//                 Enemy_unit[i]->stats->Debuff["Torrid_Scorch"]=1;
//                 Enemy_unit[i]->Def_shred["None"]+=18;
//             }
//         }
//     }
//     void Toughness_break_func(Ally *ptr,Enemy *target,Ally *Breaker){
//         Action_forward(target->Atv_stats.get(),15);
//         target->stats->Debuff["Cloudflame_Luster"]=1;
//         if(ptr->stats->Eidolon>=2){
//             Increase_energy(ptr->stats.get(),3);
//         }
//         for(int i=1;i<=Total_ally;i++){
//             if(Ally_unit[i]->Atv_stats->Name=="Fugue")continue;
//             if(Ally_unit[i]->stats->Stack["Phecda Primordia"]<2){
//                 Ally_unit[i]->stats->Stack["Phecda Primordia"]++;
                
//                 Ally_unit[i]->Break_effect["None"]+=18;
//             }
//             Ally_unit[i]->stats->Buff_countdown["Phecda Primordia"] = Ally_unit[i]->Atv_stats->turn_cnt+2;
//         }
//     }
    
// }
// #endif
