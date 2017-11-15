#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <string>
#include <cstring>
#include "SkillManagement.h"
#include "IncludeAllArmors.h"
#include "IncludaAllGems.h"
#include "IncludeAllSkills.h"
#include "IncludeAllTalents.h"
#include "TextGenerator.h"
#include "PlayerInGameStat.h"
#include "ListObjectsSingleton.h"
#include "CollisionalObject.h"
#include "EquipmentBase.h"
#include "IncludeAllEquipments.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "AchievementGestion.h"
#include "PlayerIconeBonus.h"
#include "PetBase.h"
#include "SoundGestion.h"
#include "FeatGestion.h"

class SkillManagement;

class Player : public CollisionalObject , public std::enable_shared_from_this<Player>
{
private:
#pragma region VariablesForChangeStat
	std::list<int> TypeChange;
	std::list<float> DurationChange;
	std::list<float> ValueChange;
	std::list<sf::Clock> ClockChange;
	std::list<float>ChangeEffect;
#pragma endregion VariablesForBoostStat

	int language;

	enum RingBonus { RingHpRecovery, RingHpPercentRevoery, RingMovementSpeedAddition, RingDamagePercent, RingDamageAddition, RingExperiencePercent, RingHealthAddition, RingHealthPercent, RingArmorAddition, RingArmorPercent, RingCooldown, RingAttackSpeedPercent, RingLifeSteal, };
	AchievementGestion achievement_gestion;
	PlayerInGameStat player_in_game_stat_interface;
	PlayerIconeBonus player_icone_bonus;
	const static int maximum_skills = 9;
	static const int number_classes = 4;
	static const int number_talent = 27;
	static const int maximum_scrolls = 8;
	std::vector<std::vector<bool>> listRuneAvailable;
	std::vector<float> listFeatBonus;
	sf::String name_mage;
	std::vector<bool> ListCharacteristicMages{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false };
	std::vector<int> ListCharacteristicProsOrCons{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::vector<bool> ListDrawbackMages{ false,false,false,false,false,false,false,false,false,false};
	std::vector<float> ListCharacteristicValue{ 15,15,15,30,10,20,20,15,25,5,25,15,20,25,2 };
	std::vector<bool> listScrollEquipped{ false,false,false,false,false,false,false,false,false,false,false,false };
	std::vector<float> listScrollBonus;
	sf::Clock clock_scroll_immunity;
	std::vector<sf::Clock> listClockRampage;
	std::vector<std::shared_ptr<TalentBase>> listAllTalents;
	std::shared_ptr<EquipmentBase> current_weapon;
	int current_weapon_index = -1;
	std::shared_ptr<EquipmentBase> current_hat;
	int current_hat_index = -1;
	std::shared_ptr<EquipmentBase> current_ring1;
	std::shared_ptr<EquipmentBase> current_ring2;
	int current_ring1_index = -1;
	int current_ring2_index = -1;
#pragma region Pet
	std::shared_ptr<PetBase> current_pet;
	std::vector<std::shared_ptr<PetBase>> listPets;
	int current_id_pet = -1;
#pragma endregion Pet
	std::vector<std::shared_ptr<EquipmentBase>> listEquipment;
	std::shared_ptr<CollisionalObject> object_looting;
	std::list<std::shared_ptr<CollisionalObject>> listPickableMaterial;
	std::vector<int> ListPickableMaterialID;
	std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors;
	std::vector<std::shared_ptr<G_GemBase>> listAllGems;
	std::vector<std::shared_ptr<SkillBase>> listAllSkills;
	std::vector<int> listAllActiveGems;
	std::vector < sf::Vector2f> player_gem_array;
	std::vector<int> player_array_talent_points_used{ 0,0,0,0 };
	std::vector<int> player_array_talent_level{ 0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0 ,0,0,0,0,0 ,0,0,0,0,0 ,0,0 };
	std::vector<int> player_array_talent_increasement{ 0,0,0,0,0,0,0,0,0,0 ,0,0,0,0,0 ,0,0,0,0,0 ,0,0,0,0,0 ,0,0 };
	std::vector<int> player_skill_increasement{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	std::vector<int> player_modified_skill_level_list{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	std::vector<int> player_skills_level_array{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	std::vector<int> player_skills_rune_array{ NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E,NoRune_E };

	int player_level = 1;
	int rayon = 31;
	int rampage_bonus = 0;
	int player_experience_needed_next_level = 500;
	int player_current_health_int;
	int current_class = ClassFire;
	int class_cant_use = NoClass;
	int current_opened_interface = NoInterface_E;
	int number_monster_hearts = 0;
	int player_id = 1;

	sf::Sprite player_image;
	sf::Texture player_texture[number_classes];
	sf::Texture skillbase_icone_texture;
	sf::Texture texture_health_bar_interface;
	sf::RectangleShape player_maximum_health_bar;
	sf::RectangleShape player_health_bar;
	sf::RectangleShape stun_bar;
	sf::RectangleShape bar_looting;
	sf::RectangleShape bar_looting_progress;	
	sf::Vector2f text_health_position{ 10, 5 };
	sf::Vector2f text_exp_position{ 10,20 };
	sf::Vector2f positition_view_of_player;
	sf::Vector2f window_dimension;
	sf::Vector2f position_bar_looting{ 800,600 };
	sf::Vector2f size_bar_looting{ 500,30 };
	sf::Vector2f position_going_to{ 0,0 };
	sf::Vector2f velocity_player{ 0,0 };
	
	sf::Vector2i cutting_source;

	float player_image_size_x = 48;
	float player_image_size_y = 64;
	float player_starting_money = 5000;
	float player_money;
	float player_money_sent;
	float player_money_received_total;
	float player_money_added;
	float player_experience = 0;
	float player_bonus_experience_percent;
	float player_bonus_money_percent;
	float player_bonus_fragments_percent;
	float player_cooldown_reduction_initial = 0;
	float player_cooldown_reduction_percent = 0;
	float player_cooldown_reduction = 0;
	float player_max_cooldown_reduction = 35;	
	float player_max_cooldown_reduction_initial = 35;
	float speed_of_player_initial = 300;
	float speed_of_player;
	float time_to_loot = 0.5;
	float time_to_loot_initial = 0.5;
	float player_maximum_shield_percent = 30;
	float player_current_shield = 0;
	float player_shield_recovery = 0;
	float player_damage_modified;
	float player_damage = 64;
	float player_maximum_health_initial = 1000;
	float player_maximum_health = 1000;
	float player_defense_initial = 20;
	float player_defense;
	float player_lifesteal = 0;
	float player_shieldleech = 0;
	float player_stun_reduction_percent = 0;
	float player_stun_reduction = 0;
	float player_damage_reduction = 0;
	float player_slow_reduction = 0;
	float player_current_health = player_maximum_health;
	float time_being_stunned = 0;
	float stun_from_normal_casting = 0.15;
	float Hp_recovery = 0;
	float hp_recovery_increase = 0;
	float amount_health_recovered_this_turn = 0;
	float amount_shield_recovered_this_turn = 0;
	float player_max_attack_speed = 1.15;
	float player_current_attack_speed = player_max_attack_speed;
	float time_before_out_of_battle = 5;
	float time_before_out_of_battle_initial = 5;
	float player_number_skills_casted = 0;
	float health_potion_cooldown = 18;
	float sprint_points = 100;
	float sprint_max_points = 150;
	float rate_sprint_lost_second = 30;
	float rate_sprint_gained_second = 10;
	float sprint_percent_bonus_initial = 140;
	float sprint_percent_bonus = 160;
	float cooldown_sprinting = 3;
	float player_radar_range_modifier = 1;
	float player_bonus_crafting_stat = 0;
	float damage_dealt_in_second = 0;
	float damage_received_liquid_body = 0;
	float armor_on_shield_percent = 0;

	float movement_speed_before_change = 0;
	float attack_speed_before_change = 0;
	float speed_of_player_before_change = 0;
	float bonus_movement_speed_percent_after_all = 0;
	float bonus_defense_percent = 0;
	float bonus_defense_percent_overall = 0;
	float bonus_damage_reduction = 0;
	float bonus_movement_speed;
	float bonus_movement_speed_percent_positive;
	float bonus_movement_speed_percent_negative;
	float bonus_movement_speed_percent = 0;
	float bonus_attack_speed_percent = 0;
	float bonus_attack_damage_addition = 0;
	float bonus_attack_damage_percent = 0;
	float bonus_attack_speed = 0;
	float bonus_hp_percent_recovery = 0;
	float bonus_hp_recovery = 0;
	float bonus_hp_recovery_increase_percent = 0;
	float bonus_health_percent = 0;
	float bonus_health_percent_overall = 0;
	float bonus_max_cooldown_reduction = 0;
	float bonus_health_addition = 0;
	float bonus_defense_addition = 0;
	float bonus_cooldown_reduction = 0;
	float bonus_cooldown_reduction_percent = 0;
	float bonus_attack_damage_percent_overall = 0;
	float bonus_stun_reduction_percent = 0;
	float bonus_stun_reduction = 0;
	float bonus_slow_reduction = 0;
	float bonus_time_out_battle_modifier = 0;
	float bonus_lifesteal = 0;
	float bonus_shieldleech = 0;
	float bonus_shield_recovery_percent_health = 0;
	float bonus_shield_capacity_addition_percent = 0;
	float bonus_addition_percent_sprint = 0;
	float bonus_to_bonus_experience_percent = 0;
	float bonus_to_bonus_money_percent = 0;
	float bonus_radar_range_modifier = 0;
	float bonus_to_bonus_crafting_stat = 0;
	float bonus_looting_time_modifier = 0;
	float bonus_armor_on_shield = 0;
	bool player_can_be_immune = false;
	bool player_can_be_scared = false;
	bool player_can_be_cantdie = false;

	bool player_skill_ready[12]{ true, true, true, true, true, true, true, true, true, true, true, true };
	bool player_is_stunned = false;
	bool player_is_immune = false;
	bool need_to_be_put_in_quadtree = false;
	bool player_is_out_of_battle = true;
	bool is_looting = false;
	bool can_cast_skill[9]{ false,false,false,false,false,false,false,false,false };
	bool skill_is_canceled[9]{ false,false,false,false,false,false,false,false,false };
	bool can_display_shield_recovery = true;
	bool can_display_hp_recovery = true;
	bool can_use_health_potion = true;
	bool using_potion = false;
	bool player_is_scared = false;
	bool can_sprint = true;
	bool player_spawned_after_death = true;
	bool is_sprinting = false;
	bool player_characteristic_created = false;
	bool player_is_at_spawn = true;
	bool ritual_done = false;
	bool standing_still = true;
	bool cant_die_status = true;
	bool player_died = false;

	sf::Clock player_skill_clock[12];
	sf::Clock clock_check_if_still_stunned;
	sf::Clock clock_restraining_fps;
	sf::Clock clock_health_recovery;
	sf::Clock clock_shield_recovery;
	sf::Clock clock_out_of_battle;
	sf::Clock clock_looting;
	sf::Clock clock_talent_hasty;
	sf::Clock clock_health_potion_duration;
	sf::Clock clock_health_potion_tick;
	sf::Clock clock_cooldown_health_potion;
	sf::Clock clock_breath_from_sprinting;
	sf::Clock clock_lifesteal;
	sf::Clock clock_liquid_body;
	sf::Clock game_timer;
	sf::Clock clock_skill_revive;
	sf::Clock clock_feat_in_combat;
	sf::Clock clock_testing;

	float player_skill_cooldown[12];
	int source_x = 0;
	int source_y;
	int source_x_standing = 0;
	//Next region is from PlayerStaticInterface which was not working due to circular dependencies
#pragma region PlayerStaticInterface
	sf::Text text_player_health;
	sf::Text text_player_experience;
	sf::Font font;
	sf::Clock clock_animation_big_health_bar;
	sf::Clock clock_animation_experience_bar;
	int number_big_health_bar_animations = 16;
	int counter_big_health_bar = 0;
	int counter_experience_bar = 0;

	sf::Vector2f size_rect_player_experience{ 512, 44 };
	sf::Vector2f size_rect_player_health{ 164,44 };
	sf::Vector2f size_rect_skill_slot{ 50,50 };
	sf::Vector2f size_sprite_skillbase_icone{ 66,66  };
	sf::Vector2f position_text_player_health{ 95,50 };
	sf::Vector2f position_text_player_experience{ 800,765};
	sf::Vector2f position_player_experience_bar{ 800,770 };
	sf::Vector2f position_initial_sprite_skill_icone{ 400,700 };
	sf::Vector2f size_health_bar_interface{ 58,12 };
	sf::Vector2f size_health_bar{ 50,4 };
	sf::Vector2f size_icone{ 50,50 };
	sf::Vector2f size_skill_cooldown_rectangle_max{ 50,50 };
	sf::Vector2f array_position_sprite_skill_icone[12];
	sf::Vector2f position_big_health_bar{ 95,55 };
	sf::Vector2f size_sprinting_bar{ player_image_size_x,5 };
	int character_size_text_player_health = 24;
	sf::String string_text_player_health = "Hp: ";
	sf::String string_text_player_experience = "Level ";
	sf::Sprite big_player_health;
	sf::Sprite basic_big_player_health;
	sf::RectangleShape rect_shield_player_bar;
	sf::RectangleShape rect_sprinting_bar;
	sf::RectangleShape rect_full_sprinting_bar;
	sf::RectangleShape rect_blinded;
	sf::Texture texture_basic_big_player_health;
	sf::Texture texture_big_player_health;
	sf::Texture texture_player_experience_bar;
	sf::Texture texture_out_battle;
	sf::Sprite rect_player_experience;
	sf::Sprite rect_skill_slot[12];
	sf::Sprite sprite_health_bar_interface;
	sf::Sprite sprite_health_potion;
	sf::Vector2f position_health_potion{ 1400,700 };
	sf::String string_number_health_potion;
	sf::Text text_number_health_potion;
	sf::Vector2f position_number_health_potion{ 1412,712 };
	sf::Texture texture_player_skill_icone[12];
	sf::Texture basic_skill_icone_texture;
	sf::Texture texture_health_potion;
	int array_player_skill_id[12];
	float array_skill_cooldown[12];
	sf::Sprite sprite_skill_icone[12];
	int holder_position_sprite_skill_icone = 0;	
	bool skill_cooldown_rectangle_created[12]{ false, false, false, false, false, false };
	bool skill_cooldown_changed[12]{ false, false, false, false, false, false, false, false, false, false, false, false};
	sf::RectangleShape skill_cooldown_rectangle[12];
	sf::RectangleShape rect_health_potion_cooldown;
	sf::Clock skill_cooldown_clock[12];

	void InitPlayerExperienceInterface();
	void InitPlayerHealthInterface();
	void InitAllPlayerStaticInterface(sf::Vector2f position_view_player);
	void UpdateAllPlayerStaticInterface(sf::Vector2f position_view_player);
	void UpdatePlayerHealthInterface(sf::Vector2f position_view_player);
	void UpdatePlayerExperienceInterface(sf::Vector2f position_view_player);
	void DrawToScreenAllPlayerStaticInterface(sf::RenderWindow &window);
	void LifeGestion();
	void UpdateStaticInterfaceAccordingToResolution();
#pragma endregion PlayerStaticInterface
	std::vector<std::vector<int>> inventory;

	float distance_being_pushed;
	bool being_pushed = false;
	sf::Vector2f push_origin{ 0,0 };
	int push_force = NoPush;
	float push_speed = 35;
	float push_rotation = 0;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 32,18 };
	void HealthPotionGestion();
	void LoadWeaponInformations();
	void LoadHatInformations();
	void SaveInventoryInformation();
	void LoadInventoryInformation();
	void SprintingMaintenance();
	void CheckScrollBonus();
	void CheckRingBonus();
	void CheckCharacteristicBonus();
	void SaveCharacteristicInformation();
	void LoadCharacteristicInformation();
	void CheckPlayerStillInMap();
	void LoadRingInformations();
	void LifeStealGestion();
	void CheckArmorBonus();
	void CheckFeatBonus();
public:
	int last_target_id = -3;
	int same_target_hit_time = 0;
	std::vector<int> player_skills_array{ -1, -1, -1,-1,-1,-1,-1, -1, -1};
	std::vector<int> player_number_fragments { 1500,0,0,0,0};
	int player_skills_array_size = 12;
	int number_current_armor = 0;
	std::vector<int> player_armor_array{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	Player();
	~Player();

	int GetCurrentOpenedInterface() { return current_opened_interface; }
	void GiveNewOpenedInterface(int new_interface);
	float GetLifesteal() { return player_lifesteal; }
	void GivePlayerNewClass(int new_class);
	int GetCurrentClassPlayer() { return current_class; }
	int GetClassPlayerCantUse() { return class_cant_use; }
	void GivePlayerItem(int type_inventory, int specific_type, int amount){ inventory[type_inventory][specific_type] += amount; }
	void PlayerConsumedSomething(int type_inventory, int specific_type, int amount) { inventory[type_inventory][specific_type] -= amount; }
	void GiveWeapon(std::shared_ptr<E_Weapon> weapon);
	int GetNumberSpecficItemInInventory(int type_inventory, int specific_type) { return inventory[type_inventory][specific_type];  }
	std::vector<std::vector<int>> GetInventory() { return inventory; }
	void StopLooting();
	void LootingGestion(sf::Vector2f position_view_player);
	void UpdateListPickableMaterial();
	void LootOnFloor();
	bool CheckIDMaterial(int id);
	virtual void AddMaterialToList(std::shared_ptr<CollisionalObject> object);
	virtual void TeleportEntity(sf::Vector2f position, int TypeTeleportation);
	virtual sf::FloatRect GetCollisionRect() { return player_image.getGlobalBounds(); }
	void Init(sf::Vector2f position, sf::Vector2f position_view_player, sf::Vector2f window_dimension_received,int id_received);
	void DrawToScreen(sf::RenderWindow &window, sf::View &view_player, sf::Vector2f position_view_player);
	void player_health_maintenance();
	void CalculateMovement(float DELTATIME, sf::Vector2f mouse_position);
	virtual sf::Vector2f GetCurrentPosition();
	bool IsStandingStill();
	void CuttingSprite();
	virtual float GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent);
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	float GetDamage();
	int GetExp(int DeadOrNot);
	float GetHealth();
	int GetMaximumHealth();
	void UpdatePlayerStats();
	void UsingSkill(SkillManagement &skill_management, sf::Vector2f mouse_position);
	int GetId();
	float GetAttackSpeed();
	void UpdatePlayerSkillArrayPosition(sf::Vector2f position_view_player);
	void SkillUsed(int skill_slot);
	std::vector<int> GetPlayerSkillArray();
	void NewPlayerSkillArray(std::vector<int> player_skills_array_received);
	std::vector<int> GetPlayerSkillLevelArray();
	std::vector<int> GetPlayerSkillLevelIncreasement() { return player_skill_increasement; }
	std::vector<int> GetPlayerNumberFragments();
	void NewPlayerNumberFragments(std::vector<int> player_number_fragments_received);
	void GivePlayerFragments(int type_fragment, int number_fragments);
	void NewPlayerSkillLevel(std::vector<int> player_skill_level_received);
	void NewPlayerCurrentArmor(int number_armor);
	int GetPlayerCurrentArmor();
	std::vector<int> GetPlayerArmorArray();
	float GetMoney();
	void NewPlayerArmorArray(std::vector<int> player_armor_array_received);
	void NewPlayerMoney(float player_money_received);
	void NewPlayerGemArray(std::vector<sf::Vector2f> player_gem_array_received);
	std::vector<sf::Vector2f> Player::GetPlayerGemArray();
	std::vector<int> GetPlayerActiveGemArray();
	void MoneyGestion();
	void UpdateStatsWithEquipments();
	float GetBonusExperiencePercent();
	float GetBonusMoneyPercent() { return player_bonus_money_percent; }
	float GetBonusFragmentsPercent() { return player_bonus_fragments_percent; }
	float GetCooldownReduction();
	float GetMovementSpeed();
	void NewPlayerActiveGemArray(std::vector<int>);
	int GetNumberTotalGemsUsable();
	void StunGestion();
	float GetStunTime();
	virtual void ChangeStunTime(float stun_time_received);
	bool IsPlayerStunned();
	void StunBarGestion();
	void Update(TextGenerator &text_generator, sf::RenderWindow &window, float DELTATIME, sf::Vector2f position_view_player, SkillManagement &skill_manager);
	virtual void GivePlayerChangeStat(int type_change, float duration_change, float value_change);
	void CalculateAllStatChanges();
	void HealthRecoveryGestion();
	void PassiveSkillGestion();
	void OutOfBattleGestion();
	void PlayerDidCombatAction();
	void ResetASkill(int skill_reset);
	virtual void ChangeASkillCooldown(int skill_cooldown_changing, float new_cooldown);
	void HealPlayer(float amount_healed);
	float GetAmountHealingThisTurn();
	virtual void GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking);
	float GetDefense();
	sf::Vector2f GetPositionViewPlayer();
	void CalculateView();
	bool CheckIfPlayerHasSkill(int SkillEnum);
	virtual int GetTypeCollisionalObject() { return Player_E; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	sf::Vector2f GetVelocityPlayer() { return velocity_player; }
	void CheckWeaponBonus();
	std::vector<int> GetPlayerArrayTalentPointsUsed() { return player_array_talent_points_used; }
	std::vector<int> GetPlayerArrayTalentLevel() { return player_array_talent_level; }
	std::vector<int> GetPlayerArrayTalentIncreasement() { return player_array_talent_increasement; }
	void NewPlayerArrayTalentPointsUsed(std::vector<int> new_array) { player_array_talent_points_used = new_array; }
	void NewPlayerArrayTalentLevel(std::vector<int> new_array) { player_array_talent_level = new_array; }
	std::vector<bool> GetPlayerListEquippedScroll() { return listScrollEquipped; }
	void NewPlayerListEquippedScroll(std::vector<bool> new_list) { listScrollEquipped = new_list; }
	int GetPlayerLevel() { return player_level; }
	void CheckTalentBonus();
	void UpdateSkillCooldown();
	float GetProjectileRangeBonus();
	float GetProjectileSpeedBonus(){return listAllTalents[QuickAttack_E]->GetTalentBonus(player_array_talent_level[QuickAttack_E]);}
	void ShieldRecoveryGestion();
	float GetAmountShieldedThisTurn();
	float GetSkillDamageBonus();
	float GetArmorPenetrationPercent(){return listAllTalents[IronTip_E]->GetTalentBonus(player_array_talent_level[IronTip_E]);}
	void OnHitGestion(int id_object, float damage_dealt, int type_object, int type_projectile);
	virtual void ShieldObject(float amount_shield);
	virtual void HealObject(float heal_value) { HealPlayer(heal_value); };
	void TalentBuffGestion();
	float GetSpecificTalentBonus(int type_talent);
	float GetSlowPercentDebuffOnHit();
	float GetSlowDurationDebuffOnHit();
	float GetStunDurationDebuffOnHit();
	virtual void GetSlowed(int type_slow, float duration_slow, float percent_slow);
	void UpdatePlayerArrayTalentIncreasement();
	void UpdatePlayerArraySkillIncreasement();

#pragma region Equipments
	std::vector<std::shared_ptr<EquipmentBase>> GetListEquipment() { return listEquipment; }
	void ChangeCurrentWeapon(int position_weapon_in_list);
	std::shared_ptr<EquipmentBase> GetCurrentWeapon() { return current_weapon; }
	int GetCurrentWeaponIndex() { return current_weapon_index; }
	void ResetCurrentWeapon() { current_weapon.reset(); UpdatePlayerArrayTalentIncreasement(); }

	void GiveHat(std::shared_ptr<E_WizardHat> hat);
	void ChangeCurrentHat(int position_weapon_in_list);
	std::shared_ptr<EquipmentBase> GetCurrentHat() { return current_hat; }
	int GetCurrentHatIndex() { return current_hat_index; }
	void ResetCurrentHat() { current_hat.reset(); UpdatePlayerArraySkillIncreasement(); }

	void GivePet(std::shared_ptr<PetBase> new_pet);
	std::shared_ptr<PetBase> GetCurrentPet() { return current_pet; }
	std::vector<std::shared_ptr<PetBase>> GetListPets() { return listPets; }
	void ResetCurrentPet() { current_pet.reset(); current_id_pet = -1; }
	void ChangeCurrentPet(int position_pet_in_list);
	void DeleteAPet(int position_pet_in_list);
	int GetCurrentIdPet() { return current_id_pet; }
	sf::Vector2f GetCurrentPetPosition() { return current_pet->GetCurrentPosition(); }
	void PetUpdate(float DELTATIME, sf::Vector2f target_position, sf::Vector2f target_velocity) {if (current_pet != NULL){current_pet->Update(DELTATIME, target_position, target_velocity);}}

	void GiveRing(std::shared_ptr<EquipmentBase> ring);
	void ChangeCurrentRing1(int position_weapon_in_list);
	std::shared_ptr<EquipmentBase> GetCurrentRing1() { return current_ring1; }
	int GetCurrentRing1Index() { return current_ring1_index; }
	void ResetCurrentRing1() { current_ring1.reset();}

	void ChangeCurrentRing2(int position_weapon_in_list);
	std::shared_ptr<EquipmentBase> GetCurrentRing2() { return current_ring2; }
	int GetCurrentRing2Index() { return current_ring2_index; }
	void ResetCurrentRing2() { current_ring2.reset();}
#pragma endregion Equipments

	int GetLevelSpecificSkill(int type_skill);
	void GivePlayerMoney(float money_received);
	void AddToDrawListPet();
	virtual void Draw(sf::RenderWindow &window);
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
	void SaveInformations();
	void LoadInformations();
	void MapPortalGestion();
	void AchievementUpdate(int number_point_on_radar, int map_level);
	void MonsterKilledGestion(bool is_elite);
	std::vector<bool> GetListPossibleAchiemevents() { return achievement_gestion.listPossible; }
	std::vector<bool> GetListSucceededAchiemevents() { return achievement_gestion.listSucceeded; }
	std::vector<float> GetListValueReachedAchievements() { return achievement_gestion.listValueReached; }
	float GetPlayerRadarRangeModifier() { return player_radar_range_modifier; }
	float GetPlayerBonusCraftingStat() { return player_bonus_crafting_stat; }
	void GivePlayerNewCharacteristic(std::vector<bool> ListCharacteristicMages_received, std::vector<int> ListCharacteristicProsOrCons_received, std::vector<bool> ListDrawbackMages_received, sf::String name_mage);
	std::vector<bool> GetPlayerListDrawback() { return ListDrawbackMages; }
	std::vector<bool> GetPlayerListCharacteristic() { return ListCharacteristicMages; }
	std::vector<int> GetPlayerListCharacteristicProsOrCons() { return ListCharacteristicProsOrCons; }
	sf::String GetNameMage() {return name_mage;}
	bool GetIfPlayerAtSpawn() { return player_is_at_spawn; }
	void ChangePlayerIsAtSpawn(bool is_player_at_spawn) { player_is_at_spawn = is_player_at_spawn; }
	void ChangePlayerDoneRitual(bool ritual_done) { this->ritual_done = ritual_done; }
	bool GetIfPlayerRitualDone() { return ritual_done; }
	int GetNumberMonsterHearts() { return number_monster_hearts; }
	void DeleteSave(int save_to_delete);
	int GetCurrentRuneForSpecificSkill(int skill_number) { return player_skills_rune_array[skill_number]; }
	void ChangeRuneSpecificSkill(int skill_number, int new_rune) { player_skills_rune_array[skill_number] = new_rune; }
	void GetRandomRune();
	std::vector<std::vector<bool>> GetListRuneAvaiblable() { return listRuneAvailable; }
	bool GetIfPlayerOutOfCombat() { return player_is_out_of_battle; }
	sf::Vector2i GetSourceCutting() { return cutting_source; }
	bool GetIfPlayerDied() { bool temp = player_died; player_died = false; return temp; }
};
