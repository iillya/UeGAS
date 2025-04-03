// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefailtInfo UCharacterClassInfo::GetCharacterClassInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInformation.FindAndRemoveChecked(CharacterClass);
}
