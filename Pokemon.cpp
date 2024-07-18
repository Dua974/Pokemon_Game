/*********
 **File: Pokemon.cpp
 
 **Author: Dua Abdullah
 
 **implements the funcitionalitties of Pokemon class and defnes the attributes of Pokemon object **which will later be used. 
 *********************************/

#include "Pokemon.h"

//Name: Pokemon
//PreCondition: None
//PostCondition: Pokemon is created
Pokemon::Pokemon() {
  m_num = 0;     //number of pokemon 
  m_name = "";   // Name of pokemon
  m_CP = 0;     //Combat power of pokemon 
  m_rarity = 0;   //Rarity of pokemon 
}


//Name: Pokemon
//PreCondition: None
//PostCondition: Pokemon is initialized with num, name, cp, rarity
Pokemon::Pokemon(int num, string name, int cp, int rarity) {

  m_num = num;   //number of pokemon    
  m_name = name;   //name of pokemon 
  m_CP = cp;       //Combat power of pokemon 
  m_rarity = rarity;    //rarity of pokemon 
}


//Name:GetCP
//PreCondition: None
//PostCondition: returns CP
int Pokemon::GetCP() {
  return m_CP;
}


//Name:GetRarity
//PreCondition: None       
//PostCondition: returns rarity    
int Pokemon::GetRarity() {
  return m_rarity;
}

// Name: GetName
// Preconditions - None
// Postconditions - Returns name
string Pokemon::GetName() {
  return m_name;
}


// Name: GetNum
// Preconditions - None                                                                                                                                                                                    // Postconditions - Returns num   
int Pokemon::GetNum() {
  return m_num; 
}

//Name:SetRarity
//PreCondiion: None
//PostCondition: Updates rarity
void Pokemon::SetRarity(int newRarity) {
  m_rarity = newRarity;
}

//Name: SetName
//PreCondition: None
//PostCondition:updates m_name
void Pokemon::SetName(string newName) {
    m_name = newName;
}


//Name: SetCP
//PreCondition: None
//PostCondition: updates m_CP
void Pokemon::SetCP(int newCP) {
    m_CP = newCP;
}


//Name: Train
//PreCondition: maxCP is calculated and passed as an argument
//PostCondition: updates m_CP by TRAIN_POWER to maxCP 
void Pokemon::Train(int maxCP) {
  m_CP = min(m_CP + TRAIN_VALUE, maxCP); 
}

