#pragma once
#include "PetBase.h"
#include "Player.h"
#include <vector>
#include "EffectOrb.h"
#include "MagicLeaf.h"
#include "Flowering.h"
#include "Spike.h"
#include "LifeOrb.h"

class Fairy : public PetBase
{
private:
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();
	enum PetSKill { NoSkill, Flowering_E, MagicLeaf_E, Drain_E, Heal_E, Recharge_E, Rest_E, Exalt_E, LifeOrb_E, PassivePetPower, PassiveHealth, PassiveArmor, PassiveHpRecovery, PassiveShieldRecovery};
	std::shared_ptr<Player> parent;
	std::vector<int> PetAttributes{ 0,0,0,0 };
	std::vector<int> PetMaxAttributes{ 0,0,0,0 };
	std::vector<sf::Vector2i> ListPetSkillPossible{ sf::Vector2i(NoSkill,NoSkill) ,sf::Vector2i(NoSkill,NoSkill) ,sf::Vector2i(NoSkill,NoSkill) ,sf::Vector2i(NoSkill,NoSkill) ,sf::Vector2i(NoSkill,NoSkill) };
	std::vector<int> ListPetSkillObtained{ -1 ,-1 ,-1 ,-1 ,-1 };
	std::vector<int> ListPetSkillObtainedForInterface{ -1 ,-1 ,-1 ,-1 ,-1 };
	std::vector <sf::String> listStringNameAbilites;
	std::vector<sf::String> listStringDescriptionAbilities;

	sf::RectangleShape rect_first_skill_cooldown;
	sf::RectangleShape rect_first_skill;
	sf::RectangleShape rect_second_skill_cooldown;
	sf::RectangleShape rect_second_skill;

	sf::Sprite sprite_pet;
	sf::Texture texture_pet;
	sf::Vector2f size_pet{ 32,32 };

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 11,10 };

	float range_from_player = 350;
	float speed_initial = 215;
	float speed = speed_initial;
	float angle_going = 1;
	float timer_animation = 0.15;
	float timer_standing = 2;
	float exp = 0;
	float cooldown_first_skill = 18;
	float cooldown_second_skill = 22;
	float recovering_ability_power_modifier = 1;

	int direction = Standing;
	int source = 0;
	int level = 10;
	int id;

	bool moving_to_player = false;
	bool can_use_first_skill = true;
	bool can_use_second_skill = true;

	sf::Clock clock_animation;
	sf::Clock clock_standing;
	sf::Clock clock_basic_attack;
	sf::Clock clock_first_skill;
	sf::Clock clock_second_skill;
	sf::Clock clock_attack_speed_bonus;

	void CuttingSprite();
	void GetRandomSkill();
	void UseAbilities(sf::Vector2f target_position, sf::Vector2f target_velocity);
	void CooldownGestion();
public:
	Fairy(int id_received);
	~Fairy();

	virtual void Init(std::shared_ptr<Player> player);
	virtual void MovementGestion(float DELTATIME);
	virtual sf::Vector2f GetCurrentPosition() { return sprite_pet.getPosition(); }
	virtual void Draw(sf::RenderWindow &window);
	virtual int GetTypePet() { return Fairy_E; }
	virtual std::vector<int> GetPetAttributes() { return PetAttributes; }
	virtual std::vector<int> GetPetMaxAttributes() { return PetMaxAttributes; }
	virtual int GetLevelPet() { return level; }
	virtual  sf::Vector2f GetExpPet() { return sf::Vector2f(exp, GlobalFunction::GetPlayerExperienceNeeded(level)); }
	virtual void GetNewPetAttributes(std::vector<int> new_PetAttributes) { PetAttributes = new_PetAttributes; }
	virtual int GetPetId() { return id; }
	virtual void Update(float DELTATIME, sf::Vector2f target_position, sf::Vector2f target_velocity);
	virtual void SelectAbility(int type_ability, int ability_chosen);
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual sf::Vector2f GetCurrentPositionShadow();
	virtual bool SpriteHasShadow() { return true; }
	virtual std::vector <sf::String> GetStringAbilityName() { return listStringNameAbilites; }
	virtual std::vector <sf::String> GetStringAbilityDescription() { return listStringDescriptionAbilities; }
	virtual std::vector<sf::Vector2i> GetAbitliesPossible() { return ListPetSkillPossible; }
	virtual std::vector<int> GetAbitliesObtained() { return ListPetSkillObtainedForInterface; }
	virtual void SaveInformation(int current_pet_id);
	void InitWithInformation(std::vector<int> PetAttributes, std::vector<int> PetMaxAttributes, std::vector<sf::Vector2i> ListPetSkillPossible, std::vector<int> ListPetSkillObtained, std::vector<int> ListPetSkillObtainedForInterface, float exp, int level);
};