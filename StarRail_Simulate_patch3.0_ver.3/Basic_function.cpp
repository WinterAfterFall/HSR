#ifndef Basic_Function_H
#define Basic_Function_H
#include<bits/stdc++.h>
#include"Combat.cpp"

#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
#define K_const 10000
using std::cout ;
using std::vector;
void Basic_reset();
void Setup_enemy(int num,double speed,double energy,double Toughness,string type);
void Enemy_func(Unit *ptr);
void Summon_reset();
void Countdown_reset();
void Memosprite_reset();
void Basic_reset(){
    
    for(int i=1;i<=Total_ally;i++){
        //flat atk
        for(auto &e1:Ally_unit[i]->Sub_Unit_ptr[0]->Stats_type){
            for(auto &e2:e1.second){
                e2.second = 0;
            }

        }
        for(auto &e1:Ally_unit[i]->Sub_Unit_ptr[0]->Stats_each_element){
            for(auto &e2:e1.second){
                for(auto &e3:e2.second){
                    e3.second = 0;
                }
                
            }

        }
        
        
        //ally edit
            Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Flat_speed = 0;
            Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Speed_percent = 0;
            Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->turn_cnt = 0;
            Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->priority = 0;
            Ally_unit[i]->Energy_recharge = 100;
            Ally_unit[i]->Current_energy = Ally_unit[i]->Max_energy/2;
            for(auto &e:Ally_unit[i]->Sub_Unit_ptr[0]->Stack){
                e.second = 0;
            }
            for(auto &e:Ally_unit[i]->Sub_Unit_ptr[0]->Buff_countdown){
                e.second = 0;
            }
            for(auto &e:Ally_unit[i]->Sub_Unit_ptr[0]->Buff_note){
                e.second = 0;
            }
            for(auto &e:Ally_unit[i]->Sub_Unit_ptr[0]->Buff_check){
                e.second = 0;
            }
            Ally_unit[i]->Sub_Unit_ptr[0]->Stats_type["Atk%"]["None"] += 3.888*2;
            Ally_unit[i]->Sub_Unit_ptr[0]->Stats_type["Flat_Atk"]["None"] += 352.8+38;
            Ally_unit[i]->Sub_Unit_ptr[0]->Stats_type["Hp%"]["None"] += 3.888*2;
            Ally_unit[i]->Sub_Unit_ptr[0]->Stats_type["Flat_Hp"]["None"] += 76+705.6;
            Ally_unit[i]->Sub_Unit_ptr[0]->Stats_type["Def%"]["None"] += 4.86*2;
            Ally_unit[i]->Sub_Unit_ptr[0]->Stats_type["Crit_rate"]["None"] += 5+2.9*2;
            Ally_unit[i]->Sub_Unit_ptr[0]->Stats_type["Crit_dam"]["None"] += 50+5.8*2;
            Ally_unit[i]->Sub_Unit_ptr[0]->Stats_type["Break_effect"]["None"] += 5.8*2;
            Ally_unit[i]->Sub_Unit_ptr[0]->Stats_type["Effect_hit_rate"]["None"] += 3.888*2;
            Ally_unit[i]->Sub_Unit_ptr[0]->Stats_type["True_Damage"]["None"] += 100;
            Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Flat_speed += 2.3*2;
    }



        //enemy edit
        for(int i=1;i<=Total_enemy;i++){
            for(auto &e1:Enemy_unit[i]->Stats_type){
                for(auto &e2:e1.second){
                    e2.second = 0;
                }

            }
            for(auto &e1:Enemy_unit[i]->Stats_each_element){
                for(auto &e2:e1.second){
                    for(auto &e3:e2.second){
                        e3.second = 0;
                    }
                
                }

        }
            Enemy_unit[i]->Atv_stats->Flat_speed = 0;
            Enemy_unit[i]->Atv_stats->Speed_percent = 0;
            Enemy_unit[i]->Atv_stats->turn_cnt = 0;
            Enemy_unit[i]->Atv_stats->priority = 0;
            Enemy_unit[i]->Toughness_status=1;
            Enemy_unit[i]->Current_toughness=Enemy_unit[i]->Max_toughness;
            Enemy_unit[i]->Total_debuff=0;
            for(auto &e: Enemy_unit[i]->Debuff){
                e.second = 0;
            }
            for(auto &e: Enemy_unit[i]->Debuff_time_count){
                e.second = 0;
            }
            Enemy_unit[i]->Bleed=0;
            Enemy_unit[i]->Bleeder=0;
            Enemy_unit[i]->Burn=0;
            Enemy_unit[i]->Burner=0;
            Enemy_unit[i]->Shock=0;
            Enemy_unit[i]->Shocker=0;
            Enemy_unit[i]->Wind_shear=0;
            Enemy_unit[i]->Wind_shear_stack=0;
            Enemy_unit[i]->Wind_shearer=0;
            Enemy_unit[i]->Freeze=0;
            Enemy_unit[i]->Entanglement=0;
            Enemy_unit[i]->Entanglement_stack=0;
            Enemy_unit[i]->Imprisonment=0;
            Enemy_unit[i]->Total_toughness_broken_time =0;
            Enemy_unit[i]->when_toughness_broken = 0;
            
            Enemy_unit[i]->Stats_each_element["Respen"]["Fire"]["None"] = -Enemy_res["Fire"];
            Enemy_unit[i]->Stats_each_element["Respen"]["Ice"]["None"] = -Enemy_res["Ice"];
            Enemy_unit[i]->Stats_each_element["Respen"]["Quantum"]["None"] = -Enemy_res["Quantum"];
            Enemy_unit[i]->Stats_each_element["Respen"]["Wind"]["None"] = -Enemy_res["Wind"];
            Enemy_unit[i]->Stats_each_element["Respen"]["Lightning"]["None"] = -Enemy_res["Lightning"];
            Enemy_unit[i]->Stats_each_element["Respen"]["Physical"]["None"] = -Enemy_res["Physical"];
            Enemy_unit[i]->Stats_each_element["Respen"]["Imaginary"]["None"] = -Enemy_res["Imaginary"];
        }

    

}
void Memosprite_reset(){
    for(int i=1;i<=Total_ally;i++){
        for(int j=1,sz = Ally_unit[i]->Sub_Unit_ptr.size();j<sz;j++){
            for(auto &e1:Ally_unit[i]->Sub_Unit_ptr[j]->Stats_type){
                for(auto &e2:e1.second){
                    e2.second = 0;
                }

            }
            for(auto &e1:Ally_unit[i]->Sub_Unit_ptr[j]->Stats_each_element){
                for(auto &e2:e1.second){
                    for(auto &e3:e2.second){
                        e3.second = 0;
                    }

                }

            }
            for(auto &e1:Ally_unit[i]->Sub_Unit_ptr[0]->Stats_type){
                for(auto &e2:e1.second){
                    Ally_unit[i]->Sub_Unit_ptr[j]->Stats_type[e1.first][e2.first] = e2.second;
                }

            }
            for(auto &e1:Ally_unit[i]->Sub_Unit_ptr[0]->Stats_each_element){
                for(auto &e2:e1.second){
                    for(auto &e3:e2.second){
                        Ally_unit[i]->Sub_Unit_ptr[j]->Stats_each_element[e1.first][e2.first][e3.first] = e3.second;
                    }

                }

            }
            for(auto &e :Ally_unit[i]->Sub_Unit_ptr[j]->Stats_type["Flat_Hp"]){    
                e.second *=(Ally_unit[i]->Sub_Unit_ptr[j]->Unit_Hp_Ratio/100);
            }
        //speed
        
            for(auto &e:Ally_unit[i]->Sub_Unit_ptr[j]->Stack){
                e.second = 0;
            }
            for(auto &e:Ally_unit[i]->Sub_Unit_ptr[j]->Buff_countdown){
                e.second = 0;
            }
            for(auto &e:Ally_unit[i]->Sub_Unit_ptr[j]->Buff_note){
                e.second = 0;
            }
            for(auto &e:Ally_unit[i]->Sub_Unit_ptr[j]->Buff_check){
                e.second = 0;
            }
            
        Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->turn_cnt = 0;
        Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->priority = 0;
        Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->Flat_speed = Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Flat_speed*(Ally_unit[i]->Sub_Unit_ptr[j]->Unit_Speed_Ratio/100);
        if(Ally_unit[i]->Sub_Unit_ptr[j]->Unit_Speed_Ratio!=0)Ally_unit[i]->Sub_Unit_ptr[j]->Atv_stats->Speed_percent = Ally_unit[i]->Sub_Unit_ptr[0]->Atv_stats->Speed_percent;


        }
        
    }
}
void Summon_reset(){
    for(int i=1;i<=Total_ally;i++){
        for(int j=0,sz = Ally_unit[i]->Summon_ptr.size();j<sz;j++){  
        
        //speed
        Ally_unit[i]->Summon_ptr[j]->Atv_stats->Speed_percent=0;
        Ally_unit[i]->Summon_ptr[j]->Atv_stats->Flat_speed=0;
        Ally_unit[i]->Summon_ptr[j]->Atv_stats->turn_cnt = 0;
        Ally_unit[i]->Summon_ptr[j]->Atv_stats->priority = 0;

        
        
        
        }
    }
}
void Countdown_reset(){
    for(int i=1;i<=Total_ally;i++){
        for(int j=0,sz = Ally_unit[i]->Countdown_ptr.size();j<sz;j++){  
        
        //speed
        Ally_unit[i]->Countdown_ptr[j]->Atv_stats->Speed_percent=0;
        Ally_unit[i]->Countdown_ptr[j]->Atv_stats->Flat_speed=0;
        Ally_unit[i]->Countdown_ptr[j]->Atv_stats->turn_cnt = 0;
        Ally_unit[i]->Countdown_ptr[j]->Atv_stats->priority = 0;
        Ally_unit[i]->Countdown_ptr[j]->Atv_stats->Base_speed = -1;
        }
    }
}
void Enemy_func(Unit *ptr){
    auto target = dynamic_cast<Enemy*>(ptr);
    if(target){
    if(target->Toughness_status==0){
        target->Toughness_status = 1;
        target->Current_toughness =  target->Max_toughness;
        target->Total_toughness_broken_time+=(Current_atv - target->when_toughness_broken);
    }
    }
    ++target->Debuff["Attack_cnt"];
    if(target->Debuff["Attack_cnt"]%3==2){

        
        if(target){
        Enemy_hit(target->Energy_gen,target);
        }else{
            cout<<"error from Enemy_func";
            exit(0);
        }
    }
}
void Setup_enemy(int num,double speed,double energy,double Toughness,string type){
    if(num ==0){
        cout<<"setup enemy error";
        exit(0);
    }
    Enemy_unit[num] = make_unique<Enemy>();

        Enemy_unit[num]->Atv_stats->Base_speed = speed;
        Enemy_unit[num]->Energy_gen = energy;
        Enemy_unit[num]->Max_toughness = Toughness;
        Enemy_unit[num]->Target_type = type;
        if(type == "Main"){
            Main_Enemy_num = num;
        }

        Enemy_unit[num]->Turn_func = Enemy_func;



        for(auto &e:Enemy_weak){
                Enemy_unit[num]->Weakness_type[e.first] = e.second;
        }
        
        Enemy_unit[num]->Atv_stats->Unit_num = num;
        Enemy_unit[num]->Atv_stats->Char_Name = "Enemy_";
        Enemy_unit[num]->Atv_stats->Char_Name += type;
        Enemy_unit[num]->Atv_stats->Unit_Name = Enemy_unit[num]->Atv_stats->Char_Name;
        Enemy_unit[num]->Atv_stats->Side = "Enemy";
        Enemy_unit[num]->Atv_stats->ptr_to_unit = Enemy_unit[num].get();
}

#endif