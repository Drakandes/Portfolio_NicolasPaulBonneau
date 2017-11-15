#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include "IncludeAllSkills.h"
#include "IncludeAllArmors.h"
#include "IncludaAllGems.h"
#include "IncludeAllTalents.h"

class ListObjectsSingleton
{
private:
	std::vector<std::shared_ptr<SkillBase>> listAllSkill;
	std::vector<std::shared_ptr<G_GemBase>> ListAllGems;
	std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors;
	std::vector<std::shared_ptr<TalentBase>> listAllTalents;
	std::vector<sf::String> listStringAchievements;
	std::vector<float> listAchievementsBonus{3,12,20,50,20,15,30,25,2,25,8,33};
	static ListObjectsSingleton *s_instance1;
	std::vector<sf::String> listStringTips;
	std::vector<int> listStringTipsAlreadyPassed;
	int counter_id = 1;
	int counter_id_equipment = 1;
	int game_mode = IntermediateMode;
	int language = French_E;
	int futur_language = French_E;
	int style_interface = 0;
	sf::Vector2f size_window{ 1600,800 };
	sf::Vector2f map_limit_maximum;
	sf::Vector2f map_limit_minimum{124,202};
	bool need_to_load_spawn = false;

	int current_save = NoSave_E;
	std::vector<bool> SaveIsUsed{ false,false,false };
	std::vector<int> ListSaveDifficulty{ 2,2,2 };
	std::vector<int> ListMapLevel{ 1,1,1 };

public:
	ListObjectsSingleton();
	~ListObjectsSingleton();

	int number_drawback = 10;
	int number_characteristic = 15;
	std::vector<sf::String> ListCharacteristicPros;
	std::vector<sf::String> ListCharacteristicCons;
	std::vector<float> ListCharacteristicValue{ 15,15,15,30,10,20,20,15,25,5,25,15,20,25,2 };
	std::vector<sf::String> ListDrawback{"Left Handed","Simple-Minded","Broken Leg","Mingled","Allergic To Potion","Eye Disease","Close-Minded","Radioactive","Anonymous","Genetic Anomaly"};

	static void Initialize()
	{
		s_instance1 = new ListObjectsSingleton();
	}
	static ListObjectsSingleton *instance()
	{
		if (!s_instance1)
			s_instance1 = new ListObjectsSingleton;
		return s_instance1;
	}

	void CreateLists();
	std::vector<std::shared_ptr<A_ArmorBase>> GetListArmor();
	std::vector<std::shared_ptr<SkillBase>> GetListSkill();
	std::vector<std::shared_ptr<G_GemBase>> GetListGem();
	std::vector<std::shared_ptr<TalentBase>> GetListTalent() { return listAllTalents; }
	std::vector<float> GetListAchievementsBonus() { return listAchievementsBonus; }
	void ChangeGameMode(int game_mode_received) { game_mode = game_mode_received; }
	int GetGameMode() { return game_mode; }
	sf::Vector2f GetSizeWindow();
	void ChangeSizeWindow(sf::Vector2f new_window_size);
	int GetNewID();
	int GetNewIDEquipment();
	sf::String GetRandomStringTip();
	void CreateListStringTips();
	void CreateListStringAchiements();
	std::vector<sf::String> GetListStringAchiements() {return listStringAchievements;}
	void CreateListStringCharacteristic();
	void SaveParameter();
	void LoadParameter();
	int GetCurrentLanguage() { return language; }
	void ChangeCurrentLanguage(int new_language) { futur_language = new_language; }
	void GiveMapLimitSize(sf::Vector2f(map_limit_received)) { map_limit_maximum = map_limit_received; }
	sf::Vector2f GetMapLimitSizeMaximum() { return map_limit_maximum; }
	sf::Vector2f GetMapLimitSizeMinimum() { return map_limit_minimum; }
	int GetCurrentSave() { return current_save; }
	void SetCurrentSave(int save_number);
	std::vector<bool> GetIfSaveUsed() { return SaveIsUsed; }
	void SetSaveNotUsed(int save_number) { SaveIsUsed[save_number] = false; }
	void ToggleNeedLoadSpawn() { need_to_load_spawn = true; }
	bool GetIfNeedLoadSpawn() { bool holder = need_to_load_spawn; need_to_load_spawn = false; return holder; }
	int GetLevelMap() { return ListMapLevel[current_save]; }
	void ChangeLevelMap(int new_level) { ListMapLevel[current_save] = new_level; }
	int GetStyleInterface() { return style_interface; }
	void IncreaseStyleInterface();
};

