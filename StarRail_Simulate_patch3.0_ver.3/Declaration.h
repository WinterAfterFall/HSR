#ifndef Define_H
#define Define_H
#include <bits/stdc++.h>

#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
using std::cout ;
using std::vector;
using std::string;
using std::unordered_map;
using std::queue;
using std::pair;
using std::function;
using std::unique_ptr;
using std::make_unique;
// Stats
class Unit;
class Sub_Unit;
class Enemy_stats;
class Action_value_stats;
class Func;
class Ally;
class Enemy;
class Combat_data;
class Ratio_data;
class Hit_spilt;
typedef unordered_map<string,double> Common_stats; 
typedef unordered_map<string,Common_stats> Common_stats_type; 
typedef unordered_map<string,Common_stats_type> Common_stats_each_element;
/*  None 
    Basic_Attack
    Skill
    Ultimate 
    Dot 
    Fua 
    Summon 
    Break_dmg 
    Super_break 
*/


//cal
double Cal_Atk_multiplier(Combat_data &data_,Enemy *target);
double Cal_Hp_multiplier(Combat_data &data_,Enemy *target);
double Cal_Def_multiplier(Combat_data &data_,Enemy *target);
double Cal_Bonus_dmg_multiplier(Combat_data &data_,Enemy *target);
double Cal_Crit_multiplier(Combat_data &data_,Enemy *target);
double Cal_Crit_rate_multiplier(Combat_data &data_,Enemy *target);
double Cal_Crit_dam_multiplier(Combat_data &data_,Enemy *target);

double Cal_Def_shred_multiplier(Combat_data &data_,Enemy *target);
double Cal_Respen_multiplier(Combat_data &data_,Enemy *target);
double Cal_Vul_multiplier(Combat_data &data_,Enemy *target);
double Cal_BreakEffect_multiplier(Combat_data &data_,Enemy *target);
double Cal_Toughness_multiplier(Combat_data &data_,Enemy *target);
double Cal_Superbreak_DamageIncrease_multiplier(Combat_data &data_,Enemy *target);
double Cal_Mitigation_multiplier(Combat_data &data_,Enemy *target);


void Cal_Toughness_reduction(Combat_data &data_,Enemy* target,double Toughness_reduce);
void Cal_Damage(Combat_data &data_,Enemy *target,Ratio_data Skill_mtpr);
void Cal_Additional_damage(Combat_data &data_,Enemy *target,Ratio_data Skill_mtpr);
void Cal_Break_damage(Combat_data &data_,Enemy *target,double &Constant);
void Cal_Freeze_damage(Combat_data &data_,Enemy *target);
void Cal_Superbreak_damage(Combat_data &data_,Enemy *target,double Superbreak_ratio);
void Cal_Dot_damage(Combat_data &data_,Enemy *target,double Dot_ratio);
void Cal_Dot_Toughness_break_damage(Combat_data &data_,Enemy *target,double Dot_ratio);
double Cal_Average(Enemy *target,double Total_atv);
double Cal_Total_Toughness_Reduce(Combat_data &data_,Enemy *target,double Base_Toughness_reduce);
void Cal_Average();
//atv
void Update_Max_atv(Action_value_stats *ptr);
void atv_reset(Action_value_stats *ptr);
void Action_forward(Action_value_stats *ptr,double fwd);
void All_Action_forward(double fwd);
void All_atv_reset();

void Speed_Buff(Action_value_stats *ptr,double spd_percent ,double flat_spd );
void Speed_Buff_All_Ally(double spd_percent ,double flat_spd);
void Speed_Buff_All_Ally(double spd_percent ,double flat_spd,string Buff_name);
void Speed_Buff_All_Ally_Exclude_Buffer(double spd_percent ,double flat_spd,string Buffer);
void Speed_Buff_All_Ally_Exclude_Buffer(double spd_percent ,double flat_spd,string Buffer,string Buff_name);
void Increase_energy(Ally *ptr,double Energy);
void Increase_energy(Ally *ptr,double Energy_percent,double Flat_energy);
void Find_turn();
void Atv_fix(double Atv_reduce);
//combat
void Toughness_break(Combat_data &data_,Enemy* target);
void Deal_damage();
void All_ult_check();
void Take_action();
void Buff(Combat_data &data_);
void Before_turn();
void After_turn();
void Before_attack(Combat_data &data_);
void After_attack(Combat_data &data_);
void When_attack(Combat_data &data_);
void When_Toughness_break(Combat_data &data_,Enemy *target);
void Attack(Combat_data &data_);
bool Ult_use_check(Ally *ptr);
void Dot_trigger(double Dot_ratio,Enemy *target,string Dot_type);
void Attack_hit(Combat_data &data_,int Hit_cnt,int Total_Hit_cnt);
void Enemy_hit(double energy,Enemy *target);
void Superbreak_trigger(Combat_data &data_, double Superbreak_ratio);
void Apply_debuff(Sub_Unit *ptr,Enemy* target);
void Skill_point(Sub_Unit *ptr,int p);
void When_Enemy_Death(Sub_Unit *Killer,Enemy *target);
void When_Energy_Increase(Ally *target,double Energy);

//void Hp_drop(Ally *ptr,vector<int> chr);

//char func
namespace Char_Command{
    void Set_Technique(Ally *ptr,int tech);
void Timing_print(Ally *ptr);
bool Using_Skill(Ally *ptr);
//bool Enemy_got_hit(Enemy *ptr,Combat_data &data_);
void Set_Substats(Ally *ptr,int sub);
void Set_Substats(Ally *ptr,int index,int sub);
void Switch_Substats(Ally *ptr,string temp1,string temp2);
void Switch_Substats_toFirst(Ally *ptr,string temp);
void Set_Target_Buff(Sub_Unit *ptr,int num,int subnum);
void Set_Target_Buff(Sub_Unit *ptr,int num);
void Set_Speed_Boot(Ally *ptr,bool Bool);
void Set_Er_Rope(Ally *ptr,bool Bool);
void Set_Body_Critdam(Ally *ptr,bool Bool);

void Set_Tune_Speed(Ally *ptr,double value);
void Set_Reroll_check(Ally *ptr,bool Bool);
void Set_Other_buff(Ally *ptr,bool Bool);
}

#endif
