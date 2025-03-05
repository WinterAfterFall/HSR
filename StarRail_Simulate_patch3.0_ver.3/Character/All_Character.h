#ifndef All_Character_H
#define All_Character_H
#include".\Abundance\All_Abundance_char.h"
#include".\Destruction\All_Destruction_char.h"
#include".\Erudition\All_Erudition_char.h"
#include".\Harmony\All_Harmony_char.h"
#include".\Nihility\All_Nihility_char.h"
#include".\Preservation\All_Preservation_char.h"
#include".\Remembrance\All_Remembrance_char.h"
#include".\The_Hunt\All_The_Hunt_char.h"
namespace Char_Command{

void Set_LightCone(double HPtemp ,double ATKtemp,double DEFtemp){
    HP = HPtemp;
    ATK = ATKtemp;
    DEF = DEFtemp;

}
void Set_Substats(Ally *ptr,int sub){
    ptr->Total_substats=sub;
    ptr->Separate_sub=sub;
    ptr->Substats[0].second=sub;
}
void Set_Substats(Ally *ptr,int index,int sub){
    if(ptr->Substats.size()<=index){
        cout<<" Out of bound";
        exit(0);
    }
    ptr->Substats[index].second = sub;
}
void Switch_Substats(Ally *ptr,string temp1,string temp2){
    int index =-1;
    for(int i=0;i<ptr->Substats.size();i++){
        if(temp1==ptr->Substats[i].first){
            index = i;
            break;
        }
    }
    if(index==-1)return;
    for(int i=0;i<ptr->Substats.size();i++){
        if(temp2==ptr->Substats[i].first){
            ptr->Substats[index].first = temp2;
            ptr->Substats[i].first = temp1;
        }
    }
    return;
}
void Switch_Substats_toFirst(Ally *ptr,string temp){
    for(int i=0;i<ptr->Substats.size();i++){
        if(temp==ptr->Substats[i].first){
            ptr->Substats[i].first = ptr->Substats[0].first;
            ptr->Substats[0].first = temp;
            break;
        }
    }
    return;
}
void Set_Target_Buff(Sub_Unit *ptr,int num,int subnum){
    if(num!=0)ptr->Target_num = num;
    if(num!=0)ptr->Sub_Unit_num = subnum;
}
void Set_Target_Buff(Sub_Unit *ptr,int num){
    if(num!=0)ptr->Target_num = num;
}
void Set_Technique(Ally *ptr,int tech){
    ptr->Technique = tech;
}
void Set_Speed_Boot(Ally *ptr,bool Bool){
    ptr->Speed_Boot = Bool;
}
void Set_Er_Rope(Ally *ptr,bool Bool){
    ptr->Er_Rope = Bool;
}
void Set_Body_Critdam(Ally *ptr,bool Bool){
    ptr->Body_CritDam = Bool;

}

void Set_Tune_Speed(Ally *ptr,double value){
    if(value==0)return;
    ptr->Speed_tune_value = value;
}
void Set_Reroll_check(Ally *ptr,bool Bool){
    ptr->Reroll_check = Bool;
}
void Timing_print(Ally *ptr){
    ptr->Print = 1;
}
bool Using_Skill(Ally *ptr){
    if(Sp_status=="Positive")return true;
    if(sp>Sp_Safety)return true;
    if(Robin_num!=0){
        if(Ally_unit[Robin_num ]->Sub_Unit_ptr[0]->Atv_stats->Base_speed==-1)return true;
        if(!Ally_unit[Robin_num]->Wait_Other_Buff)return false;   
    }
    return false;
}
void Set_Other_buff(Ally *ptr,bool Bool){
    ptr->Wait_Other_Buff=Bool;
}
// bool Enemy_got_hit(Enemy *ptr,Combat_data &data_){
//     if(ptr->Target_type=="Main"){
//         for(int i=0;i<data_.Damage_spilt.Main.size();i++){
//             if(data_.Damage_spilt.Main[i].Atk_ratio!=0||data_.Damage_spilt.Main[i].Hp_ratio!=0||data_.Damage_spilt.Main[i].Def_ratio!=0)return true;
//         }
//     }else if(ptr->Target_type=="Adjacent"){
//         for(int i=0;i<data_.Damage_spilt.Adjacent.size();i++){
//             if(data_.Damage_spilt.Adjacent[i].Atk_ratio!=0||data_.Damage_spilt.Adjacent[i].Hp_ratio!=0||data_.Damage_spilt.Adjacent[i].Def_ratio!=0)return true;
//         }
//     }else if(ptr->Target_type=="Other"){
//         for(int i=0;i<data_.Damage_spilt.Other.size();i++){
//             if(data_.Damage_spilt.Other[i].Atk_ratio!=0||data_.Damage_spilt.Other[i].Hp_ratio!=0||data_.Damage_spilt.Other[i].Def_ratio!=0)return true;
//         }
//     }
//     return false;
// }
}

#endif
/*
    void Setup(int num ,int E,function<void(Ally *ptr)> LC,function<void(Ally *ptr)> Relic,function<void(Ally *ptr)> Planar);
    void Reset(Ally *ptr);
    void Setup_Memo(Ally *ptr);
    void Basic_Atk(Ally *ptr);
    void Enchance_Basic_Atk(Ally *ptr);
    void Skill(Ally *ptr);
    void Enchance_Skill(Ally *ptr);
    void When_Combat(Ally *ptr);
    void Tune_stats(Ally *ptr);
    void Start_game(Ally *ptr);
    void Start_wave(Ally *ptr);
    void Before_turn(Ally *ptr);
    void After_turn(Ally *ptr);
    void Before_attack(Ally *ptr,Combat_data &data_);
    void After_attack(Ally *ptr,Combat_data &data_);
    void When_attack(Ally *ptr,Combat_data &data_);
    void Buff(Ally *ptr,Combat_data &data_);
    void Dot(Enemy* target,Ally *ptr,double Dot_ratio,string Dot_type);
    void Toughness_break(Ally *ptr,Enemy *target,Sub_Unit *Breaker);
    void Enemy_hit(Ally *ptr,Enemy *target);
    void Apply_debuff(Ally *ptr,Enemy* target,Sub_Unit *Applier);
    void Skill_point(Ally *ptr,Sub_Unit *SP_maker,int SP);
    void Hit(Ally *ptr,Combat_data &data_,int Hit_cnt,int Total_Hit_cnt);
    void Enemy_Death(Ally *ptr,Enemy *target,Sub_Unit *Killer);
    void When_Energy_Increase(Ally *ptr,Ally *target,double Energy);
    */
   //ไม่ได้ทำ tech ของ 
   //serval