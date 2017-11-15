#include "stdafx.h"
#include "EquipmentBase.h"

EquipmentBase::EquipmentBase()
{
}

EquipmentBase::~EquipmentBase()
{
}

std::vector<int> EquipmentBase::GetListSkillIncreasement()
{
	std::cout << "Error, receving from base" << std::endl; 
	std::vector<int> holder{ 0,1 };
	return holder;
}