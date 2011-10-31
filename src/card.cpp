#include "include/card.h"

Card::Card(QString id)

{
    this->Damage_enemy=0;
    this->Damage_self=0;
    this->Description="";
    this->EnemyChanges_beasts=0;
    this->EnemyChanges_bricks=0;
    this->EnemyChanges_gems=0;
    this->EnemyChanges_tower=0;
    this->EnemyChanges_wall=0;
    this->EnemyMod_beasts=0;
    this->EnemyMod_bricks=0;
    this->EnemyMod_gems=0;
    this->id=id;
    this->Name="None";
    this->Picture_path="none";
    this->PlayerChanges_beasts=0;
    this->PlayerChanges_bricks=0;
    this->PlayerChanges_gems=0;
    this->PlayerChanges_tower=0;
    this->PlayerChanges_wall=0;
    this->PlayerMod_beasts=0;
    this->PlayerMod_bricks=0;
    this->PlayerMod_gems=0;
    this->Requirements=0;
    this->Type="0";
    this->AdditionalTurn=0;
    this->DiscardCard=0;


}


Card::~Card(){

}
