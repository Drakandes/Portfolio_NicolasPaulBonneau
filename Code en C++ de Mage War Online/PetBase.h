#pragma once
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SpriteBase.h"

class Player;

class PetBase : public SpriteBase
{
private:

public:
	PetBase();
	~PetBase();

	virtual void Init(std::shared_ptr<Player>){}
	virtual void MovementGestion(float DELTATIME){}
	virtual sf::Vector2f GetCurrentPosition() { return sf::Vector2f(0, 0); }
	virtual void Draw(sf::RenderWindow &window){}
	virtual int GetTypePet() { return NoPet_E; }
	virtual std::vector<int> GetPetAttributes() { return std::vector<int>{0}; }
	virtual std::vector<int> GetPetMaxAttributes() { return std::vector<int>{0}; }
	virtual int GetLevelPet() { return 0; }
	virtual  sf::Vector2f GetExpPet() { return sf::Vector2f(0,1); }
	virtual void GetNewPetAttributes(std::vector<int> new_PetAttributes){}
	virtual int GetPetId() { return -1; }
	virtual void Update(float DELTATIME, sf::Vector2f target_position, sf::Vector2f target_velocity){}
	virtual void SelectAbility(int type_ability, int ability_chosen){}
	virtual void DrawShadow(sf::RenderWindow &window){}
	virtual sf::Vector2f GetCurrentPositionShadow() { return sf::Vector2f(0, 0); }
	virtual bool SpriteHasShadow() { return false; }
	virtual std::vector <sf::String> GetStringAbilityName() { std::vector <sf::String> list; return list; }
	virtual std::vector <sf::String> GetStringAbilityDescription(){ std::vector <sf::String> list; return list; }
	virtual std::vector<sf::Vector2i> GetAbitliesPossible() { std::vector <sf::Vector2i> list; return list; }
	virtual std::vector<int> GetAbitliesObtained() { std::vector <int> list; return list; }
	virtual void SaveInformation(int current_pet_id){}
};

