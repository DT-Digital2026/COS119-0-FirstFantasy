#include "Item.h"

//Building default constructor. 
Item::Item() {
	//Item Information. 
	mName = ""; 
	mDescription = ""; 
	mType = ItemType::Consumable; 

	//Consumable values. 
	mHPRestore = 0; 
	mAseRestore = 0; 

	//Equipment values. 
	mAtkBonus = 0; 
	mDefBonus = 0; 
}
//Overloaded constructor.
Item::Item(const std::string& Name,const std::string& Description, ItemType Type, int HPRestore, int AseRestore, int AtkBonus, int DefBonus) {
	//Item Information. 
	mName = Name; 
	mDescription = Description; 
	mType = Type; 

	//Consumable Values. 
	mHPRestore = HPRestore; 
	mAseRestore = AseRestore; 

	//Equipment values. 
	mAtkBonus = AtkBonus; 
	mDefBonus = DefBonus; 
}
//Item Getters. 
std::string Item::GetName() const {
	return mName; 
}

std::string Item::GetDescription() const {
	return mDescription; 
}

ItemType Item::GetType() const {
	return mType; 
}

int Item::GetHPRest() const {
	return mHPRestore; 
}

int Item::GetAseRest() const {
	return mAseRestore; 
}

int Item::GetAtkBonus() const {
	return mAtkBonus; 
}

int Item::GetDefBonus() const {
	return mDefBonus; 
}