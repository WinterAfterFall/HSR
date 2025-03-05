#ifndef Cal_damage_H
#define Cal_damage_H
#include<bits/stdc++.h>
#include"Action_value.h"

#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
#define K_const 10000



queue<Combat_data> Action_bar;

class Ratio_data{
    public:
    double Atk_ratio;
    double Hp_ratio;
    double Def_ratio;
    double Toughness_ratio;
};
class Hit_spilt{
    public:
    vector<Ratio_data> Main;
    vector<Ratio_data> Adjacent;
    vector<Ratio_data> Other;
};
class Combat_data{
    public:
    bool Turn_reset = 0;
    double Dont_care_weakness =0;
    Sub_Unit* Attacker = nullptr; //
    vector<Sub_Unit*> Target_Buff;
    vector<Enemy*> Target_Attack;

    Hit_spilt Damage_spilt;
    vector<pair<int,Sub_Unit*>> Joint;
    int Attack_trigger = 1; 
    vector<Sub_Unit*> All_Attacker;//

    pair<string,string> Action_type;//Attack Buff//Skill Basic_Attack Ultimate

    vector<string> Buff_type;//Buff Heal Shield 
    vector<string> Skill_Type;//  None Basic_Attack Skill Ultimate  Dot  Fua  Summon  Break_dmg  Super_break Additional
    string Damage_element = "";//Physical Fire Ice Lightning Wind Quantum Imaginary

    string Target_Type = "";// Aoe Single_target Bounce

    void Add_Buff_Single_Target(Sub_Unit* ptr){
        Target_Buff.push_back(ptr);
    }
    void Add_Buff_Single_Target(Ally* ptr){
        for(auto &e:ptr->Sub_Unit_ptr){
            Target_Buff.push_back(e.get());
        }
    }
    void Add_Buff_All_Ally(){
        
        for(int i=1;i<=Total_ally;i++){
            for(auto &e:Ally_unit[i]->Sub_Unit_ptr){
                Target_Buff.push_back(e.get());
            }
        }
    }
    void Add_Target(Enemy* ptr){
        Target_Attack.push_back(ptr);
    }
    void Add_Target_Main(){
        for(int i=1;i<=Total_enemy;i++){
            if(Enemy_unit[i]->Target_type=="Main"){
                Target_Attack.push_back(Enemy_unit[i].get());
                return;
            }
        }
    }
    void Add_Target_Adjacent(){
        for(int i=1;i<=Total_enemy;i++){
            if(Enemy_unit[i]->Target_type!="Other"){
                Target_Attack.push_back(Enemy_unit[i].get());
            }
        }
    }
    void Add_Target_Other(){
        for(int i=1;i<=Total_enemy;i++){
            Target_Attack.push_back(Enemy_unit[i].get());
            
        }
    }
    void Basic_Attack_set(Sub_Unit* ptr,string target_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Action_type.first = "Attack";
        Action_type.second = "Basic_Attack";
        Skill_Type.push_back("Basic_Attack");
        Damage_element = ptr->Element_type[0];
        Target_Type = target_type;
    }
    void Basic_Attack_set(Sub_Unit* ptr,string target_type,string buff_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Action_type.first = "Buff";
        Action_type.second = "Basic_Attack";
        Skill_Type.push_back("Basic_Attack");
        Buff_type.push_back(buff_type);
        Damage_element = ptr->Element_type[0];
        Target_Type = target_type;
    }
    void Skill_set(Sub_Unit* ptr,string target_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Action_type.first = "Attack";
        Action_type.second = "Skill";
        Skill_Type.push_back("Skill");
        Damage_element = ptr->Element_type[0];
        Target_Type = target_type;
    }
    void Skill_set(Sub_Unit* ptr,string target_type,string buff_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Action_type.first = "Buff";
        Action_type.second = "Skill";
        Skill_Type.push_back("Skill");
        Buff_type.push_back(buff_type);
        Damage_element = ptr->Element_type[0];
        Target_Type = target_type;
    }
    void Ultimate_set(Sub_Unit* ptr,string target_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Action_type.first = "Attack";
        Action_type.second = "Ultimate";
        Skill_Type.push_back("Ultimate");
        Damage_element = ptr->Element_type[0];
        Target_Type = target_type;
    }
    void Ultimate_set(Sub_Unit* ptr,string target_type,string buff_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Action_type.first = "Buff";
        Action_type.second = "Ultimate";
        Skill_Type.push_back("Ultimate");
        Buff_type.push_back(buff_type);
        Damage_element = ptr->Element_type[0];
        Target_Type = target_type;
    }
    void Fua_set(Sub_Unit* ptr,string target_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Action_type.first = "Attack";
        Action_type.second = "Fua";
        Skill_Type.push_back("Fua");
        Damage_element = ptr->Element_type[0];
        Target_Type = target_type;
    }
    void Fua_set(Sub_Unit* ptr,string target_type,string buff_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Action_type.first = "Buff";
        Action_type.second = "Fua";
        Skill_Type.push_back("Fua");
        Buff_type.push_back(buff_type);
        Damage_element = ptr->Element_type[0];
        Target_Type = target_type;
    }
    void Additional_set(Sub_Unit* ptr,string target_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Action_type.first = "Attack";
        Action_type.second = "Additional";
        Skill_Type.push_back("Additional");
        Damage_element = ptr->Element_type[0];
        Target_Type = target_type;
    }
    void Dot_set(Sub_Unit* ptr,string target_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        
        Action_type.first = "Attack";
        Action_type.second = "Dot";

        Skill_Type.push_back("Dot");
        Damage_element = ptr->Element_type[0];
        
        Target_Type = target_type;
    }
    void Technique_set(Sub_Unit* ptr,string target_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Action_type.first = "Attack";
        Action_type.second = "Technique";
        Skill_Type.push_back("Technique");
        Damage_element = ptr->Element_type[0];
        Target_Type = target_type;
    }
    void Technique_set(Sub_Unit* ptr,string target_type,string buff_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Action_type.first = "Buff";
        Action_type.second = "Technique";
        Skill_Type.push_back("Technique");
        Buff_type.push_back(buff_type);
        Damage_element = ptr->Element_type[0];
        Target_Type = target_type;
    }
    void Entanglement_set(Sub_Unit* ptr){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Skill_Type.push_back("Entanglement");
        Damage_element = "Quantum";

        Action_type.first = "Attack";
        Action_type.second = "Entanglement";
        Target_Type = "Single_target";
    }
    void Freeze_set(Sub_Unit* ptr){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Skill_Type.push_back("Freeze");
        Damage_element = "Ice";

        Action_type.first = "Attack";
        Action_type.second = "Freeze";
        Target_Type = "Single_target";
    }
    void SuperBreak_set(Sub_Unit* ptr,string target_type){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Skill_Type.push_back("Break_dmg");
        Skill_Type.push_back("Super_break");
        Damage_element = ptr->Element_type[0];
        Action_type.first = "Attack";
        Action_type.second = "Super_break";
        Target_Type =target_type;
    }
    void Break_dmg_set(Sub_Unit* ptr){
        Attacker = ptr;
        All_Attacker.push_back(ptr);
        Skill_Type.push_back("Break_dmg");
        Damage_element = ptr->Element_type[0];
        Action_type.first = "Attack";
        Action_type.second = "Break_dmg";
        Target_Type ="Single_target";
    }
    
    

};
double Cal_Atk_multiplier(Combat_data &data_,Enemy *target){
    double ans = data_.Attacker->Base_atk;
    double Atk_percent_mtpr = 100;
    double Flat_atk_mtpr = 0;
    
    Atk_percent_mtpr += data_.Attacker->Stats_type["Atk%"]["None"] + target->Stats_type["Atk%"]["None"];
    Flat_atk_mtpr += data_.Attacker->Stats_type["Flat_Atk"]["None"] + target->Stats_type["Flat_Atk"]["None"];

    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Atk_percent_mtpr+= data_.Attacker->Stats_type["Atk%"][data_.Skill_Type[i]];
            Atk_percent_mtpr+= target->Stats_type["Atk%"][data_.Skill_Type[i]];

            Flat_atk_mtpr += data_.Attacker->Stats_type["Flat_Atk"][data_.Skill_Type[i]];
            Flat_atk_mtpr += target->Stats_type["Flat_Atk"][data_.Skill_Type[i]];
    }
    

    ans = (ans * Atk_percent_mtpr/100) + Flat_atk_mtpr;
    return ans;
}
double Cal_Hp_multiplier(Combat_data &data_,Enemy *target){
    double ans = data_.Attacker->Base_hp;
    double Hp_percent_mtpr = 100;
    double Flat_hp_mtpr = 0;
    Hp_percent_mtpr += data_.Attacker->Stats_type["Hp%"]["None"] + target->Stats_type["Hp%"]["None"];
    Flat_hp_mtpr += data_.Attacker->Stats_type["Flat_Hp"]["None"] + target->Stats_type["Flat_Hp"]["None"];

    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Hp_percent_mtpr+= data_.Attacker->Stats_type["Hp%"][data_.Skill_Type[i]];
            Hp_percent_mtpr+= target->Stats_type["Hp%"][data_.Skill_Type[i]];

            Flat_hp_mtpr += data_.Attacker->Stats_type["Flat_Hp"][data_.Skill_Type[i]];
            Flat_hp_mtpr += target->Stats_type["Flat_Hp"][data_.Skill_Type[i]];
    }
    

    ans = (ans * Hp_percent_mtpr/100) + Flat_hp_mtpr;
    return ans;
}

double Cal_Def_multiplier(Combat_data &data_,Enemy *target){
    double ans = data_.Attacker->Base_def;
    double Def_percent_mtpr = 100;
    double Flat_def_mtpr = 0;

    Def_percent_mtpr += data_.Attacker->Stats_type["Def%"]["None"] + target->Stats_type["Def%"]["None"];
    Flat_def_mtpr += data_.Attacker->Stats_type["Flat_Def"]["None"] + target->Stats_type["Flat_Def"]["None"];

    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Def_percent_mtpr+= data_.Attacker->Stats_type["Def%"][data_.Skill_Type[i]];
            Def_percent_mtpr+= target->Stats_type["Def%"][data_.Skill_Type[i]];

            Flat_def_mtpr += data_.Attacker->Stats_type["Flat_Def"][data_.Skill_Type[i]];
            Flat_def_mtpr += target->Stats_type["Flat_Def"][data_.Skill_Type[i]];
    }
    

    ans = (ans * Def_percent_mtpr/100) + Flat_def_mtpr;
    return ans;
}
double Cal_Bonus_dmg_multiplier(Combat_data &data_,Enemy *target){
    double Bonus_dmg_mtpr =100;
    
    Bonus_dmg_mtpr += data_.Attacker->Stats_type["Dmg%"]["None"] + target->Stats_type["Dmg%"]["None"] + data_.Attacker->Stats_each_element["Dmg%"][data_.Damage_element]["None"] +target->Stats_each_element["Dmg%"][data_.Damage_element]["None"] ;

    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Bonus_dmg_mtpr += data_.Attacker->Stats_type["Dmg%"][data_.Skill_Type[i]] + data_.Attacker->Stats_each_element["Dmg%"][data_.Damage_element][data_.Skill_Type[i]] ;
            Bonus_dmg_mtpr += target->Stats_type["Dmg%"][data_.Skill_Type[i]]+target->Stats_each_element["Dmg%"][data_.Damage_element][data_.Skill_Type[i]];
    }
    return Bonus_dmg_mtpr/100;
}
double Cal_Crit_multiplier(Combat_data &data_,Enemy *target){
    double Crit_rate_mtpr;
    double Crit_dam_mtpr;

    Crit_rate_mtpr = data_.Attacker->Stats_type["Crit_rate"]["None"] + target->Stats_type["Crit_rate"]["None"];
    Crit_dam_mtpr = data_.Attacker->Stats_type["Crit_dam"]["None"] + target->Stats_type["Crit_dam"]["None"];
    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Crit_rate_mtpr += data_.Attacker->Stats_type["Crit_rate"][data_.Skill_Type[i]] + target->Stats_type["Crit_rate"][data_.Skill_Type[i]];
            Crit_dam_mtpr += data_.Attacker->Stats_type["Crit_dam"][data_.Skill_Type[i]] + target->Stats_type["Crit_dam"][data_.Skill_Type[i]];
    }
    

    if(Crit_rate_mtpr>=100){
        Crit_rate_mtpr = 100;
    }
    return (1+(Crit_rate_mtpr/100 * Crit_dam_mtpr/100));

}
double Cal_Crit_rate_multiplier(Combat_data &data_,Enemy *target){
    double Crit_rate_mtpr;

    Crit_rate_mtpr = data_.Attacker->Stats_type["Crit_rate"]["None"] + target->Stats_type["Crit_rate"]["None"];
    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Crit_rate_mtpr += data_.Attacker->Stats_type["Crit_rate"][data_.Skill_Type[i]] + target->Stats_type["Crit_rate"][data_.Skill_Type[i]];
    }
    

    return Crit_rate_mtpr;

}
double Cal_Crit_dam_multiplier(Combat_data &data_,Enemy *target){
    double Crit_dam_mtpr;

    Crit_dam_mtpr = data_.Attacker->Stats_type["Crit_dam"]["None"] + target->Stats_type["Crit_dam"]["None"];
    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Crit_dam_mtpr += data_.Attacker->Stats_type["Crit_dam"][data_.Skill_Type[i]] + target->Stats_type["Crit_dam"][data_.Skill_Type[i]];
    }
    

    
    return Crit_dam_mtpr;
}
double Cal_Def_shred_multiplier(Combat_data &data_,Enemy *target){
    double Def_shred_mtpr;
    
    Def_shred_mtpr = data_.Attacker->Stats_type["Def_shred"]["None"] + target->Stats_type["Def_shred"]["None"];
    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Def_shred_mtpr += data_.Attacker->Stats_type["Def_shred"][data_.Skill_Type[i]] + target->Stats_type["Def_shred"][data_.Skill_Type[i]];
    }

    

    if(Def_shred_mtpr>=100){
        Def_shred_mtpr = 100;
    }
    return 100/(100 + 115*(1-1*Def_shred_mtpr/100));
}
double Cal_Respen_multiplier(Combat_data &data_,Enemy *target){
    double Respen_mtpr =100;
    
    Respen_mtpr += data_.Attacker->Stats_type["Respen"]["None"] + target->Stats_type["Respen"]["None"] + data_.Attacker->Stats_each_element["Respem"][data_.Damage_element]["None"] +target->Stats_each_element["Respem"][data_.Damage_element]["None"] ;

    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Respen_mtpr += data_.Attacker->Stats_type["Respen"][data_.Skill_Type[i]] + data_.Attacker->Stats_each_element["Respem"][data_.Damage_element][data_.Skill_Type[i]] ;
            Respen_mtpr += target->Stats_type["Respen"][data_.Skill_Type[i]]+target->Stats_each_element["Respem"][data_.Damage_element][data_.Skill_Type[i]];
    }
    return Respen_mtpr/100;
}
double Cal_Vul_multiplier(Combat_data &data_,Enemy *target){
    double Vul_mtpr = 100;
    
    Vul_mtpr += data_.Attacker->Stats_type["Vul"]["None"] + target->Stats_type["Vul"]["None"];
    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Vul_mtpr += data_.Attacker->Stats_type["Vul"][data_.Skill_Type[i]] + target->Stats_type["Vul"][data_.Skill_Type[i]];

        }
    
    
    return Vul_mtpr/100;
}
double Cal_BreakEffect_multiplier(Combat_data &data_,Enemy *target){
    double BreakEffect_mtpr = 100;
  
    BreakEffect_mtpr += data_.Attacker->Stats_type["Break_effect"]["None"] + target->Stats_type["Break_effect"]["None"];
    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            BreakEffect_mtpr += data_.Attacker->Stats_type["Break_effect"][data_.Skill_Type[i]] + target->Stats_type["Break_effect"][data_.Skill_Type[i]];
        }

    
    return BreakEffect_mtpr/100;
}
double Cal_Toughness_multiplier(Combat_data &data_,Enemy *target){
    if((data_.Action_type.second!="Break_dmg"&&Avg_damage_Mode)||target->Toughness_status==0){
        return 1;
    }else{
        return 0.9;
    }
}
double Cal_Superbreak_DamageIncrease_multiplier(Combat_data &data_,Enemy *target){
    double Spb_dmg_mtpr = 100;
       Spb_dmg_mtpr += data_.Attacker->Stats_type["Superbreak_DamageIncrease"]["None"] + target->Stats_type["Superbreak_DamageIncrease"]["None"];
    
    
    return Spb_dmg_mtpr/100;
}
double Cal_Mitigation_multiplier(Combat_data &data_,Enemy *target){
    double Mitigation_mtpr = 100;

    Mitigation_mtpr += data_.Attacker->Stats_type["Mitigation"]["None"] + target->Stats_type["Mitigation"]["None"];
    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Mitigation_mtpr += data_.Attacker->Stats_type["Mitigation"][data_.Skill_Type[i]] + target->Stats_type["Mitigation"][data_.Skill_Type[i]];
        }
    
    
    return Mitigation_mtpr/100;
}

void Cal_Damage(Combat_data &data_,Enemy *target,Ratio_data Skill_mtpr){
    double Total_dmg = 0;
    bool Memo_check=1;
    if(data_.Attacker->Atv_stats->Side=="Memosprite"){
        for(auto e:data_.Skill_Type){
        if(e=="Summon")Memo_check=0;
    }
    }
    if(Memo_check){
        data_.Skill_Type.push_back("Summon");
    }
    if(Normal_Damage_Formula_check_mode&&data_.Attacker->Atv_stats->Unit_num==Normal_Damage_Formula_check_mode){
        cout<<data_.Attacker->Atv_stats->Char_Name<<" :"<<endl;
        cout<<data_.Attacker->Base_atk<<" ";
        cout<<Cal_Atk_multiplier(data_,target)<<" * ";
        cout<<Skill_mtpr.Atk_ratio<<" ";
        cout<<data_.Attacker->Base_hp<<" ";
        cout<<Cal_Hp_multiplier(data_,target)<<" * ";
        cout<<Skill_mtpr.Hp_ratio<<" ";
        cout<<data_.Attacker->Base_def<<" ";
        cout<<Cal_Def_multiplier(data_,target)<<" * ";
        cout<<Skill_mtpr.Def_ratio<<" ";
        cout<<Cal_Bonus_dmg_multiplier(data_,target)<<" ";
        cout<<Cal_Crit_rate_multiplier(data_,target)<<" ";
        cout<<Cal_Crit_dam_multiplier(data_,target)<<" ";
        cout<<Cal_Def_shred_multiplier(data_,target)<<" ";
        cout<<Cal_Respen_multiplier(data_,target)<<" ";
        cout<<Cal_Vul_multiplier(data_,target)<<" ";
        cout<<Cal_Mitigation_multiplier(data_,target)<<" ";
        cout<<Cal_Toughness_multiplier(data_,target)<<" ";
        cout<<endl;
    }
    Total_dmg += Cal_Atk_multiplier(data_,target)*Skill_mtpr.Atk_ratio/100;
    Total_dmg += Cal_Hp_multiplier(data_,target)*Skill_mtpr.Hp_ratio/100;
    Total_dmg += Cal_Def_multiplier(data_,target)*Skill_mtpr.Def_ratio/100;
    Total_dmg = Total_dmg*Cal_Bonus_dmg_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Crit_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Mitigation_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Toughness_multiplier(data_,target);
    
    
    Ally_unit[data_.Attacker->Atv_stats->Unit_num]->Normal_Damage[target->Atv_stats->Unit_num] +=Total_dmg*data_.Attacker->Stats_type["True_Damage"]["None"]/100;
    if(Normal_Damage_check_mode==data_.Attacker->Atv_stats->Unit_num){
        cout<<data_.Attacker->Atv_stats->Char_Name<<" "<<data_.Action_type.second<<" "<<(long long)Total_dmg*data_.Attacker->Stats_type["True_Damage"]["None"]/100<<" to Enemy"<<target->Atv_stats->Unit_num<<endl;
    }
    if(Memo_check){
        data_.Skill_Type.pop_back();
    }

}
void Cal_Toughness_reduction(Combat_data &data_,Enemy* target,double Toughness_reduce){
    if(target->Weakness_type[data_.Damage_element]==0&& 0 == data_.Dont_care_weakness&&target->Current_toughness>0)return ;
    if(target->Weakness_type[data_.Damage_element]==0&& 0 != data_.Dont_care_weakness&&target->Current_toughness>0){
        Toughness_reduce*=(data_.Dont_care_weakness/100);
        target->Current_toughness-=Cal_Total_Toughness_Reduce(data_,target,Toughness_reduce);
        if(target->Current_toughness<=0){
            target->Current_toughness*=(100/data_.Dont_care_weakness);
        }
    }else{
        target->Current_toughness-=Cal_Total_Toughness_Reduce(data_,target,Toughness_reduce);
    }
    
    if(target->Current_toughness<=0&&target->Toughness_status==1){
        
        Toughness_break(data_,target);
        target->when_toughness_broken = Current_atv;
    }
}

void Cal_Break_damage(Combat_data &data_,Enemy *target,double &Constant){
    double Total_dmg = Constant *Level_multiplier;
    if(Break_Formula_check_mode&&Break_Formula_check_mode==data_.Attacker->Atv_stats->Unit_num){
        cout<<data_.Attacker->Atv_stats->Char_Name<<" ";
        cout<<(0.5+target->Max_toughness/40)<<" ";
        cout<<Cal_BreakEffect_multiplier(data_,target)<<" ";
        cout<<Cal_Def_shred_multiplier(data_,target)<<" ";
        cout<<Cal_Respen_multiplier(data_,target)<<" ";
        cout<<Cal_Vul_multiplier(data_,target)<<" ";
        cout<<Cal_Mitigation_multiplier(data_,target)<<" ";
        cout<<Cal_Toughness_multiplier(data_,target)<<" ";
        cout<<endl;
    }
    Total_dmg = Total_dmg*(0.5+target->Max_toughness/40);    
    Total_dmg = Total_dmg*Cal_BreakEffect_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Mitigation_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Toughness_multiplier(data_,target);
    Ally_unit[data_.Attacker->Atv_stats->Unit_num]->Break_damage[target->Atv_stats->Unit_num] +=Total_dmg*data_.Attacker->Stats_type["True_Damage"]["None"]/100;
    
}
void Cal_Freeze_damage(Combat_data &data_,Enemy *target){
    double Total_dmg = Level_multiplier;
    
    Total_dmg = Total_dmg*Cal_BreakEffect_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Mitigation_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Toughness_multiplier(data_,target);
    Ally_unit[data_.Attacker->Atv_stats->Unit_num]->Break_damage[target->Atv_stats->Unit_num] +=Total_dmg*data_.Attacker->Stats_type["True_Damage"]["None"]/100;
    
}

void Cal_Dot_damage(Combat_data &data_,Enemy *target,double Dot_ratio){
    double Total_dmg = 0;
    Total_dmg += Cal_Atk_multiplier(data_,target)*data_.Damage_spilt.Main[0].Atk_ratio/100;
    Total_dmg += Cal_Hp_multiplier(data_,target)*data_.Damage_spilt.Main[0].Hp_ratio/100;
    Total_dmg += Cal_Def_multiplier(data_,target)*data_.Damage_spilt.Main[0].Def_ratio/100;
    Total_dmg = Total_dmg*Cal_Bonus_dmg_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Toughness_multiplier(data_,target);
    
    Ally_unit[data_.Attacker->Atv_stats->Unit_num]->Dot_damage[target->Atv_stats->Unit_num] +=Total_dmg*Dot_ratio/100*data_.Attacker->Stats_type["True_Damage"]["None"]/100;
}
void Cal_Dot_Toughness_break_damage(Combat_data &data_,Enemy *target,double Dot_ratio){
    double Total_dmg = Level_multiplier*Dot_ratio/100;
        
    Total_dmg = Total_dmg*Cal_BreakEffect_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Mitigation_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Toughness_multiplier(data_,target);
    Ally_unit[data_.Attacker->Atv_stats->Unit_num]->Break_damage[target->Atv_stats->Unit_num] +=Total_dmg*data_.Attacker->Stats_type["True_Damage"]["None"]/100;
}
void Cal_Superbreak_damage(Combat_data &data_,Enemy *target,double Superbreak_ratio){
    double Total_dmg = Level_multiplier*Superbreak_ratio/100;
    if(SuperBreak_Formula_check_mode&&SuperBreak_Formula_check_mode==data_.Attacker->Atv_stats->Unit_num){
        cout<<data_.Attacker->Atv_stats->Char_Name<<" ";
        cout<<Superbreak_ratio<<" ";
        cout<<Cal_BreakEffect_multiplier(data_,target)<<" ";
        cout<<Cal_Superbreak_DamageIncrease_multiplier(data_,target)<<" ";
        cout<<Cal_Def_shred_multiplier(data_,target)<<" ";
        cout<<Cal_Respen_multiplier(data_,target)<<" ";
        cout<<Cal_Vul_multiplier(data_,target)<<" ";
        cout<<Cal_Mitigation_multiplier(data_,target)<<endl;
    }
    Total_dmg = Total_dmg*Cal_BreakEffect_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Superbreak_DamageIncrease_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Mitigation_multiplier(data_,target);
    Ally_unit[data_.Attacker->Atv_stats->Unit_num]->Superbreak_damage[target->Atv_stats->Unit_num] +=Total_dmg*data_.Attacker->Stats_type["True_Damage"]["None"]/100;
}
void Cal_Additional_damage(Combat_data &data_,Enemy *target,Ratio_data Skill_mtpr){
    double Total_dmg = 0;
    if(Additional_Damage_Formula_check_mode&&data_.Attacker->Atv_stats->Unit_num==Additional_Damage_Formula_check_mode){
        cout<<data_.Attacker->Atv_stats->Char_Name<<" :"<<endl;
        cout<<data_.Attacker->Base_atk<<" ";
        cout<<Cal_Atk_multiplier(data_,target)<<" * ";
        cout<<Skill_mtpr.Atk_ratio<<" ";
        cout<<data_.Attacker->Base_hp<<" ";
        cout<<Cal_Hp_multiplier(data_,target)<<" * ";
        cout<<Skill_mtpr.Hp_ratio<<" ";
        cout<<data_.Attacker->Base_def<<" ";
        cout<<Cal_Def_multiplier(data_,target)<<" * ";
        cout<<Skill_mtpr.Def_ratio<<" ";
        cout<<Cal_Bonus_dmg_multiplier(data_,target)<<" ";
        cout<<Cal_Crit_rate_multiplier(data_,target)<<" ";
        cout<<Cal_Crit_dam_multiplier(data_,target)<<" ";
        cout<<Cal_Def_shred_multiplier(data_,target)<<" ";
        cout<<Cal_Respen_multiplier(data_,target)<<" ";
        cout<<Cal_Vul_multiplier(data_,target)<<" ";
        cout<<Cal_Mitigation_multiplier(data_,target)<<" ";
        cout<<Cal_Toughness_multiplier(data_,target)<<" ";
        cout<<endl;
    }
    Total_dmg += Cal_Atk_multiplier(data_,target)*Skill_mtpr.Atk_ratio/100;
    Total_dmg += Cal_Hp_multiplier(data_,target)*Skill_mtpr.Hp_ratio/100;
    Total_dmg += Cal_Def_multiplier(data_,target)*Skill_mtpr.Def_ratio/100;
    Total_dmg = Total_dmg*Cal_Bonus_dmg_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Crit_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Def_shred_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Respen_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Vul_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Mitigation_multiplier(data_,target);
    Total_dmg = Total_dmg*Cal_Toughness_multiplier(data_,target);
    
    Ally_unit[data_.Attacker->Atv_stats->Unit_num]->Normal_Damage[target->Atv_stats->Unit_num] +=Total_dmg*data_.Attacker->Stats_type["True_Damage"]["None"]/100;
    if(Additional_Damage_check_mode==data_.Attacker->Atv_stats->Unit_num){
        cout<<data_.Attacker->Atv_stats->Char_Name<<" "<<data_.Action_type.second<<" "<<(long long)Total_dmg*data_.Attacker->Stats_type["True_Damage"]["None"]/100<<" to Enemy"<<target->Atv_stats->Unit_num<<endl;
    }
}
double Cal_Average(Enemy *target,double Total_atv){
    double temp=0;
    if(target->Toughness_status==0){
        temp = (1*(target->Total_toughness_broken_time+(Total_atv - target->when_toughness_broken)) + 0.9*(Total_atv-(target->Total_toughness_broken_time+(Total_atv - target->when_toughness_broken))))/Total_atv; 
    }else{
        temp = (1*(target->Total_toughness_broken_time) + 0.9*(Total_atv-target->Total_toughness_broken_time))/Total_atv; 
    }
    return temp;
}
void Cal_effect_hit_rate(Ally *ptr,double Base_chance){
    double temp=100/(Base_chance/100)/((100 - Enemy_effect_res)/100);
    temp = temp-100;
    double x =0;
    temp-=ptr->Sub_Unit_ptr[0]->Stats_type["Ehr"]["None"];
    if(temp<=0)return ;
    x = ceil(temp/3.888);
    ptr->Total_substats-=x;
    ptr->Separate_sub-=x;
    ptr->Substats[0].second -=x;
    x = x * 3.888;
    ptr->Sub_effect_hit_rate_use += x;
    ptr->Sub_Unit_ptr[0]->Stats_type["Ehr"]["None"] += ptr->Sub_effect_hit_rate_use;
    for(int i=1,sz = ptr->Sub_Unit_ptr.size();i<sz;i++){
        ptr->Sub_Unit_ptr[i]->Stats_type["Ehr"]["None"]+=x;
    }
    return ;
}
void Cal_Speed_Needed(Ally *ptr,double Speed_Need){
    double temp = ptr->Sub_Unit_ptr[0]->Atv_stats->Base_speed+ptr->Sub_Unit_ptr[0]->Atv_stats->Base_speed*ptr->Sub_Unit_ptr[0]->Atv_stats->Speed_percent/100 + ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed;
    temp = Speed_Need - temp;
    double x =0;
    if(temp<=0)return;
    x = ceil(temp/2.3);
    ptr->Total_substats-=x;
    ptr->Separate_sub-=x;
    ptr->Substats[0].second -=x;
    x = x * 2.3;
    ptr->Sub_Speed_use += x;
    ptr->Sub_Unit_ptr[0]->Atv_stats->Flat_speed += x;
    for(int i=1,sz = ptr->Sub_Unit_ptr.size();i<sz;i++){
        ptr->Sub_Unit_ptr[i]->Atv_stats->Flat_speed+=x*(ptr->Sub_Unit_ptr[i]->Unit_Speed_Ratio/100);
    }
    return;
}
double Cal_Total_Toughness_Reduce(Combat_data &data_,Enemy *target,double Base_Toughness_reduce){
    double ans = Base_Toughness_reduce;
    double Toughness_reduction_mtpr =100;
    double Weakness_Break_Efficiency_mtpr =100;
    Toughness_reduction_mtpr += data_.Attacker->Stats_type["Toughness_reduction"]["None"] + target->Stats_type["Toughness_reduction"]["None"];
    Weakness_Break_Efficiency_mtpr += data_.Attacker->Stats_type["Weakness_Break_Efficiency"]["None"] + target->Stats_type["Weakness_Break_Efficiency"]["None"];
    
    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Toughness_reduction_mtpr += data_.Attacker->Stats_type["Toughness_reduction"][data_.Skill_Type[i]] + target->Stats_type["Toughness_reduction"][data_.Skill_Type[i]];

        }
    for(int i=0,sz=data_.Skill_Type.size();i<sz;i++){
            Weakness_Break_Efficiency_mtpr += data_.Attacker->Stats_type["Weakness_Break_Efficiency"][data_.Skill_Type[i]] + target->Stats_type["Weakness_Break_Efficiency"][data_.Skill_Type[i]];

        }
     
    ans *= (Toughness_reduction_mtpr/100);
    ans *= ((Weakness_Break_Efficiency_mtpr)/100);
    return ans;
}
void Cal_Average(){
    double temp[5] = {0,0,0,0,0};
    if(turn->turn_cnt<2)return;
    if(turn->Unit_num!=Main_dps_num)return;
    for(int i=1;i<=Total_enemy;i++){ 
        for(int j=1;j<=Total_ally;j++){
            temp[j]+=((Ally_unit[j]->Dot_damage[i]* Cal_Average(Enemy_unit[i].get(),Current_atv)+Ally_unit[j]->Normal_Damage[i] * Cal_Average(Enemy_unit[i].get(),Current_atv)+Ally_unit[j]->Superbreak_damage[i] +Ally_unit[j]->Break_damage[i]))/Current_atv;            
        }
    }

    for(int i=1;i<=Total_ally;i++){
        if(Current_atv<Ally_unit[i]->Last_note+20){
            Ally_unit[i]->Average_damage_instance[Ally_unit[i]->Average_damage_instance.size()-1] = temp[i];
        }else{
            Ally_unit[i]->Last_note = Current_atv;
            Ally_unit[i]->Average_damage_instance.push_back(temp[i]);
        }
       
        
    }
    //cout<<"Size = "<<Ally_unit[1]->Average_damage_instance.size()<<" "<<Ally_unit[1]->Average_damage_instance[Ally_unit[1]->Average_damage_instance.size()-1]<<endl;
}

#endif