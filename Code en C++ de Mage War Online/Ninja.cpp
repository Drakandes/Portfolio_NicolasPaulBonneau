#include "stdafx.h"
#include "Ninja.h"

Ninja::Ninja(int id_received)
{
	if (!texture_pet.loadFromFile("Ninja.png"))
	{
		std::cout << "Error while loading Ninja texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("NinjaShadow.png"))
	{
		std::cout << "Error while loading Ninja shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), size_pet, shadow_texture);
	shadow.setOrigin(sf::Vector2f(size_pet.x / 2, 0));

	sprite_pet = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), size_pet, texture_pet);

	for (int i = 0; i < PetMaxAttributes.size(); i++)
	{
		PetMaxAttributes[i] = GlobalFunction::getRandomRange(10, 20);
	}
	id = id_received;

	rect_first_skill = GlobalFunction::CreateRectangleWithOrigin(sf::Vector2f(size_pet.x, 5), sf::Vector2f(0, 0), sf::Color::Black);
	rect_second_skill = GlobalFunction::CreateRectangleWithOrigin(sf::Vector2f(size_pet.x, 5), sf::Vector2f(0, 0), sf::Color::Black);

	rect_first_skill_cooldown = GlobalFunction::CreateRectangle(sf::Vector2f(size_pet.x, 5), sf::Vector2f(0, 0));
	rect_first_skill_cooldown.setFillColor(sf::Color::Blue);
	rect_first_skill_cooldown.setOrigin(sf::Vector2f(0, 2.5));

	rect_second_skill_cooldown = GlobalFunction::CreateRectangle(sf::Vector2f(size_pet.x, 5), sf::Vector2f(0, 0));
	rect_second_skill_cooldown.setFillColor(sf::Color::Blue);
	rect_second_skill_cooldown.setOrigin(sf::Vector2f(0, 2.5));

	GetRandomSkill();

	if (language == English_E)
	{
		if (true)
		{
			sf::String str0 = "Nothing";
			sf::String str1 = "Shuriken";
			sf::String str2 = "Katana";
			sf::String str3 = "Dagger";
			sf::String str4 = "Frenzied";
			sf::String str5 = "Empower";
			sf::String str6 = "Cruel";
			sf::String str7 = "Self-Esteem";
			sf::String str8 = "Deadly Shuriken";
			sf::String str9 = "Strengh";
			sf::String str10 = "Agility";
			sf::String str11 = "Quickness";
			sf::String str12 = "Cruelty";
			sf::String str13 = "Knowledge";

			listStringNameAbilites.push_back(str0);
			listStringNameAbilites.push_back(str1);
			listStringNameAbilites.push_back(str2);
			listStringNameAbilites.push_back(str3);
			listStringNameAbilites.push_back(str4);
			listStringNameAbilites.push_back(str5);
			listStringNameAbilites.push_back(str6);
			listStringNameAbilites.push_back(str7);
			listStringNameAbilites.push_back(str8);
			listStringNameAbilites.push_back(str9);
			listStringNameAbilites.push_back(str10);
			listStringNameAbilites.push_back(str11);
			listStringNameAbilites.push_back(str12);
			listStringNameAbilites.push_back(str13);
		}
		if (true)
		{
			sf::String str0 = "Nothing";
			sf::String str1 = "Throw 3 shurikens at a rate equal to 75% of the player's attack speed. Each shuriken deals 20% of player's damage. Medium range.";
			sf::String str2 = "Throw a katana at a rate equal to 50% of the player's attack speed. The katana deals 115% of player's damage. Short range.";
			sf::String str3 = "Throw a dagger at a rate equal to 100% of the player's attack speed. The dagger deals 40% of player's damage. Long range.";
			sf::String str4 = "Cast an orb that increases the player's attack speed by 50% for 4 seconds.";
			sf::String str5 = "Cast an orb that increases the player's overall damage by 100% for 2 seconds.";
			sf::String str6 = "Cast an orb that increases the player's lifesteal by +30% for 10 seconds.";
			sf::String str7 = "Increase the pet's attack speed by 300% for 5 seconds.";
			sf::String str8 = "Throw a huge shuriken that deals 350% of player's damage. Can pass through ennemies. Long range.";
			sf::String str9 = "Increase the player's damage by 5%.";
			sf::String str10 = "Increase the player's movement speed by 3%.";
			sf::String str11 = "Increase the player's attack speed by 8%.";
			sf::String str12 = "Increase the player's lifesteal by 4%.";
			sf::String str13 = "Increase the player's cooldown reduction by 7%.";

			listStringDescriptionAbilities.push_back(str0);
			listStringDescriptionAbilities.push_back(str1);
			listStringDescriptionAbilities.push_back(str2);
			listStringDescriptionAbilities.push_back(str3);
			listStringDescriptionAbilities.push_back(str4);
			listStringDescriptionAbilities.push_back(str5);
			listStringDescriptionAbilities.push_back(str6);
			listStringDescriptionAbilities.push_back(str7);
			listStringDescriptionAbilities.push_back(str8);
			listStringDescriptionAbilities.push_back(str9);
			listStringDescriptionAbilities.push_back(str10);
			listStringDescriptionAbilities.push_back(str11);
			listStringDescriptionAbilities.push_back(str12);
			listStringDescriptionAbilities.push_back(str13);
		}
	}
	else
	{
		if (true)
		{
			sf::String str0 = "Nothing";
			sf::String str1 = "Shuriken";
			sf::String str2 = "Katana";
			sf::String str3 = "Dague";
			sf::String str4 = "Frénétique";
			sf::String str5 = "Surpuissant";
			sf::String str6 = "Cruel";
			sf::String str7 = "Amour Propre";
			sf::String str8 = "Shuriken Mortel";
			sf::String str9 = "Force";
			sf::String str10 = "Agileté";
			sf::String str11 = "Rapidité";
			sf::String str12 = "Cruauté";
			sf::String str13 = "Connaisance";

			listStringNameAbilites.push_back(str0);
			listStringNameAbilites.push_back(str1);
			listStringNameAbilites.push_back(str2);
			listStringNameAbilites.push_back(str3);
			listStringNameAbilites.push_back(str4);
			listStringNameAbilites.push_back(str5);
			listStringNameAbilites.push_back(str6);
			listStringNameAbilites.push_back(str7);
			listStringNameAbilites.push_back(str8);
			listStringNameAbilites.push_back(str9);
			listStringNameAbilites.push_back(str10);
			listStringNameAbilites.push_back(str11);
			listStringNameAbilites.push_back(str12);
			listStringNameAbilites.push_back(str13);
		}
		if (true)
		{
			sf::String str0 = "Nothing";
			sf::String str1 = "Lance 3 shurikens avec une fréquence égale à 50% de la vitesse d'attaque du joueur. Chaque shuriken inflige 20% des dégâts du joueur. Moyenne portée.";
			sf::String str2 = "Lance un katana avec une fréquence égale à 30% de la vitesse d'attaque du joueur. Le katana inflige 115% des dégâts du joueur. Courte portée.";
			sf::String str3 = "Lance une dague avec une fréquence égale à 75% de la vitesse d'attaque du joueur. La dague inflige 40% des dégâts du joueur. Longue portée.";
			sf::String str4 = "Jete une orbe qui augmente la vitesse d'attaque totale du joueur de 50% pendant 4 secondes.";
			sf::String str5 = "Jete une orbe qui augmente les dégâts totaux du joueur de 100% pendant 2 secondes.";
			sf::String str6 = "Jete une orbe qui augmente le vol de vie du joueur de +30% pendant 10 secondes.";
			sf::String str7 = "Augmente la vitesse d'attaque du familier de 300% pendant 5 secondes.";
			sf::String str8 = "Lance un énorme shuriken qui inflige 350% des dégâts du joueur. Peut passer au travers des ennemies. Longue portée";
			sf::String str9 = "Augmente les dégâts du joueur de 5%.";
			sf::String str10 = "Augmente la vitesse de déplacement du joueur de 3%.";
			sf::String str11 = "Augmente la vitesse d'attaque du joueur de 8%.";
			sf::String str12 = "Augmente le vol de vie du joueur de 4%.";
			sf::String str13 = "Augmente le temps de latence du joueur de 7%.";

			listStringDescriptionAbilities.push_back(str0);
			listStringDescriptionAbilities.push_back(str1);
			listStringDescriptionAbilities.push_back(str2);
			listStringDescriptionAbilities.push_back(str3);
			listStringDescriptionAbilities.push_back(str4);
			listStringDescriptionAbilities.push_back(str5);
			listStringDescriptionAbilities.push_back(str6);
			listStringDescriptionAbilities.push_back(str7);
			listStringDescriptionAbilities.push_back(str8);
			listStringDescriptionAbilities.push_back(str9);
			listStringDescriptionAbilities.push_back(str10);
			listStringDescriptionAbilities.push_back(str11);
			listStringDescriptionAbilities.push_back(str12);
			listStringDescriptionAbilities.push_back(str13);
		}
	}
}

Ninja::~Ninja()
{
	parent.reset();
}

void Ninja::Init(std::shared_ptr<Player> player)
{
	parent = player;
	sprite_pet.setPosition(parent->GetCurrentPosition());
}

void Ninja::Update(float DELTATIME,sf::Vector2f target_position,sf::Vector2f target_velocity)
{
	MovementGestion(DELTATIME);
	UseAbilities(target_position,target_velocity);
	CooldownGestion();
}

void Ninja::MovementGestion(float DELTATIME)
{
	sf::Vector2f position_player = parent->GetCurrentPosition();
	sf::Vector2f position_pet = GetCurrentPosition();
	float distance_from_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_pet);

	if (distance_from_player >= range_from_player)
	{
		moving_to_player = true;
		if (distance_from_player >= range_from_player + 10)
		{
			clock_standing.restart();
		}

		angle_going = GlobalFunction::GetRotationBetweenTwoPositions(position_pet, position_player);
		direction = GlobalFunction::GetDirectionFromAngle(angle_going);

		sprite_pet.move(-(cos(angle_going * PI / 180))*speed*DELTATIME, -(sin(angle_going * PI / 180))*speed* (1 + 0.1*PetAttributes[Speed_E])*DELTATIME);
	}
	else
	{
		if (direction != Standing)
		{
			angle_going = GlobalFunction::GetRotationBetweenTwoPositions(position_pet, position_player);
			direction = GlobalFunction::GetDirectionFromAngle(angle_going);
		}

		moving_to_player = false;
	}
}

void Ninja::CuttingSprite()
{
	if (clock_animation.getElapsedTime().asSeconds() >= timer_animation)
	{
		if (moving_to_player)
		{
			sprite_pet.setTextureRect(sf::IntRect(source*size_pet.x, direction*size_pet.y, size_pet.x, size_pet.y));
			shadow.setTextureRect(sf::IntRect(source*size_pet.x, direction*size_pet.y, size_pet.x, size_pet.y));
			source++;
			if (source >= 4)
			{
				source = 0;
			}
		}
		else if (direction == Standing)
		{
			sprite_pet.setTextureRect(sf::IntRect(source*size_pet.x, direction*size_pet.y, size_pet.x, size_pet.y));
			shadow.setTextureRect(sf::IntRect(source*size_pet.x, direction*size_pet.y, size_pet.x, size_pet.y));
			source++;
			if (source == 4)
			{
				source = 3;
			}
		}
		else
		{
			sprite_pet.setTextureRect(sf::IntRect(0, direction*size_pet.y, size_pet.x, size_pet.y));
			shadow.setTextureRect(sf::IntRect(0, direction*size_pet.y, size_pet.x, size_pet.y));
		}

		if (direction != Standing)
		{
			if (clock_standing.getElapsedTime().asSeconds() >= timer_standing)
			{
				direction = Standing;
				source = 0;
			}
		}

		clock_animation.restart();
	}
} 

void Ninja::CooldownGestion()
{
	float percent_cd_first_skill = clock_first_skill.getElapsedTime().asSeconds() / cooldown_first_skill;
	rect_first_skill_cooldown.setSize(sf::Vector2f(size_pet.x*percent_cd_first_skill, 5));

	float percent_cd_second_skill = clock_second_skill.getElapsedTime().asSeconds() / cooldown_second_skill;
	rect_first_skill_cooldown.setSize(sf::Vector2f(size_pet.x*percent_cd_first_skill, 5));

	if (!can_use_first_skill)
	{
		if (clock_first_skill.getElapsedTime().asSeconds() >= cooldown_first_skill - (0.25*PetAttributes[Wisdom_E]))
		{
			can_use_first_skill = true;
		}
	}

	if (!can_use_second_skill)
	{
		if (clock_second_skill.getElapsedTime().asSeconds() >= cooldown_second_skill - (0.25*PetAttributes[Wisdom_E]))
		{
			can_use_second_skill = true;
		}
	}
}

void Ninja::Draw(sf::RenderWindow &window)
{
	CuttingSprite();
	window.draw(sprite_pet);

	sf::Vector2f position_pet = GetCurrentPosition();
	if (level >= 5 && ListPetSkillObtained[P_FirstSkill] != NoSkill && !can_use_first_skill)
	{
		rect_first_skill.setPosition(position_pet + sf::Vector2f(0, -size_pet.y / 2 - 20));
		window.draw(rect_first_skill);
		rect_first_skill_cooldown.setPosition(position_pet + sf::Vector2f(-size_pet.x/2, -size_pet.y / 2 - 20));
		window.draw(rect_first_skill_cooldown);
	}
	if (level >= 15 && ListPetSkillObtained[P_SecondSkill] != NoSkill && !can_use_second_skill)
	{
		rect_second_skill.setPosition(position_pet + sf::Vector2f(0, -size_pet.y / 2 - 10));
		window.draw(rect_second_skill);
		rect_second_skill_cooldown.setPosition(position_pet + sf::Vector2f(-size_pet.x / 2, -size_pet.y / 2 - 10));
		window.draw(rect_second_skill_cooldown);
	}
}

void Ninja::GetRandomSkill()
{
	int random_number;

#pragma region BasicAttack
	std::vector<int> PoolBasicAttack{ Shuriken_E,Katana_E,Dagger_E };

	int first_basic_attack;
	random_number = GlobalFunction::getRandomRange(1, PoolBasicAttack.size()) - 1;
	first_basic_attack = PoolBasicAttack[random_number];
	PoolBasicAttack.erase(PoolBasicAttack.begin() + random_number);

	int second_basic_attack;
	random_number = GlobalFunction::getRandomRange(1, PoolBasicAttack.size()) - 1;
	second_basic_attack = PoolBasicAttack[random_number];

	ListPetSkillPossible[P_BasicAttack] = sf::Vector2i(first_basic_attack, second_basic_attack);
#pragma endregion BasicAttack

#pragma region Skills
	std::vector<int> PoolSkill{ Empower,Frenzy,Cruel,SelfEsteem,HugeShuriken };

	int first_skill;
	random_number = GlobalFunction::getRandomRange(1, PoolSkill.size()) - 1;
	first_skill = PoolSkill[random_number];
	PoolSkill.erase(PoolSkill.begin() + random_number);

	int second_skill;
	random_number = GlobalFunction::getRandomRange(1, PoolSkill.size()) - 1;
	second_skill = PoolSkill[random_number];
	PoolSkill.erase(PoolSkill.begin() + random_number);

	int third_skill;
	random_number = GlobalFunction::getRandomRange(1, PoolSkill.size()) - 1;
	third_skill = PoolSkill[random_number];
	PoolSkill.erase(PoolSkill.begin() + random_number);

	int fourth_skill;
	random_number = GlobalFunction::getRandomRange(1, PoolSkill.size()) - 1;
	fourth_skill = PoolSkill[random_number];
	PoolSkill.erase(PoolSkill.begin() + random_number);

	ListPetSkillPossible[P_FirstSkill] = sf::Vector2i(first_skill, second_skill);
	ListPetSkillPossible[P_SecondSkill] = sf::Vector2i(third_skill, fourth_skill);
#pragma endregion Skills

#pragma region Passive
	std::vector<int> PoolPassive{ PassiveDmg,PassiveAts,PassiveCooldown,PassiveLifesteal,PassiveSpeed };

	int first_passive;
	random_number = GlobalFunction::getRandomRange(1, PoolPassive.size()) - 1;
	first_passive = PoolPassive[random_number];
	PoolPassive.erase(PoolPassive.begin() + random_number);

	int second_passive;
	random_number = GlobalFunction::getRandomRange(1, PoolPassive.size()) - 1;
	second_passive = PoolPassive[random_number];
	PoolPassive.erase(PoolPassive.begin() + random_number);

	int third_passive;
	random_number = GlobalFunction::getRandomRange(1, PoolPassive.size()) - 1;
	third_passive = PoolPassive[random_number];
	PoolPassive.erase(PoolPassive.begin() + random_number);

	int fourth_passive;
	random_number = GlobalFunction::getRandomRange(1, PoolPassive.size()) - 1;
	fourth_passive = PoolPassive[random_number];
	PoolPassive.erase(PoolPassive.begin() + random_number);

	ListPetSkillPossible[P_FirstPassive] = sf::Vector2i(first_passive, second_passive);
	ListPetSkillPossible[P_SecondPassive] = sf::Vector2i(third_passive, fourth_passive);
#pragma endregion Passive
}

void Ninja::UseAbilities(sf::Vector2f target_position, sf::Vector2f target_velocity)
{
	if (clock_attack_speed_bonus.getElapsedTime().asSeconds() >= 5)
	{
		attack_speed_modifier = 1;
	}

#pragma region BasicAttack

	if (ListPetSkillObtained[P_BasicAttack] != NoSkill)
	{
		if (ListPetSkillObtained[P_BasicAttack] == Shuriken_E)
		{
			if (clock_basic_attack.getElapsedTime().asSeconds() >= 1 / (parent->GetAttackSpeed()*0.75)*attack_speed_modifier)
			{
				float range_projectile = 320;
				sf::Vector2f position_shooter = GetCurrentPosition();
				if (GlobalFunction::GetDistanceBetweenTwoPositions(target_position, position_shooter) <= range_projectile)
				{
					float speed_projectile = 650;

					sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, target_position, target_velocity, speed_projectile);
					float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

					if (GlobalFunction::getRandomRange(1, 1000) <= 500)
					{
						angle_aiming += GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
					}
					else
					{
						angle_aiming -= GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
					}

					for (int i = 0; i < 3; i++)
					{
						std::shared_ptr<Shuriken> projectile = std::shared_ptr<Shuriken>(new Shuriken());
						projectile->Init(position_shooter, parent->GetDamage() * 0.20 * (1+ 0.05*PetAttributes[Power_E]), angle_aiming - 10 + i * 10, id, speed_projectile, false, true, range_projectile);
						ProjectileGestion::instance()->AddObjectToList(projectile);
						projectile.reset();
					}

					clock_basic_attack.restart();
				}
			}
		}
		else if (ListPetSkillObtained[P_BasicAttack] == Katana_E)
		{
			if (clock_basic_attack.getElapsedTime().asSeconds() >= 1 / (parent->GetAttackSpeed()*0.5)*attack_speed_modifier)
			{
				float range_projectile = 250;
				sf::Vector2f position_shooter = GetCurrentPosition();
				if (GlobalFunction::GetDistanceBetweenTwoPositions(target_position, position_shooter) <= range_projectile)
				{
					float speed_projectile = 550;

					sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, target_position, target_velocity, speed_projectile);
					float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

					if (GlobalFunction::getRandomRange(1, 1000) <= 500)
					{
						angle_aiming += GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
					}
					else
					{
						angle_aiming -= GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
					}

					std::shared_ptr<Katana> projectile = std::shared_ptr<Katana>(new Katana());
					projectile->Init(position_shooter, parent->GetDamage() * 1.15 * (1 + 0.05*PetAttributes[Power_E]), angle_aiming, id, speed_projectile, false, true, range_projectile);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();

					clock_basic_attack.restart();
				}
			}
		}
		else if (ListPetSkillObtained[P_BasicAttack] == Dagger_E)
		{
			if (clock_basic_attack.getElapsedTime().asSeconds() >= 1 / (parent->GetAttackSpeed())*attack_speed_modifier)
			{
				float range_projectile = 450;
				sf::Vector2f position_shooter = GetCurrentPosition();
				if (GlobalFunction::GetDistanceBetweenTwoPositions(target_position, position_shooter) <= range_projectile)
				{
					float speed_projectile = 700;

					sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, target_position, target_velocity, speed_projectile);
					float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

					if (GlobalFunction::getRandomRange(1, 1000) <= 500)
					{
						angle_aiming += GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
					}
					else
					{
						angle_aiming -= GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
					}

					std::shared_ptr<Dagger> projectile = std::shared_ptr<Dagger>(new Dagger());
					projectile->Init(position_shooter, parent->GetDamage() * 0.4* (1 + 0.05*PetAttributes[Power_E]), angle_aiming, id, speed_projectile, false, true, range_projectile);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();

					clock_basic_attack.restart();
				}
			}
		}
	}

#pragma endregion BasicAttack

#pragma region Skill

#pragma region FirstSkill

	if (ListPetSkillObtained[P_FirstSkill] != NoSkill)
	{
		if (can_use_first_skill)
		{
			if (ListPetSkillObtained[P_FirstSkill] == Frenzy)
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				float range_projectile = 600;
				float speed_projectile = 450;

				sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, position_player, velocity_player, speed_projectile);
				float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

				if (GlobalFunction::getRandomRange(1, 1000) <= 500)
				{
					angle_aiming += GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
				}
				else
				{
					angle_aiming -= GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
				}

				std::shared_ptr<EffectOrb> projectile = std::shared_ptr<EffectOrb>(new EffectOrb());
				projectile->Init(position_shooter, 0, angle_aiming , id, speed_projectile, true, false, range_projectile, Ninja_E);
				std::vector<int> ListChangeType{AttackSpeedPercent};
				std::vector<float> ListChangeDuration{4};
				std::vector<float> ListChangeValue{static_cast<float>(50*(1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_first_skill.restart();
				can_use_first_skill = false;
			}
			else if (ListPetSkillObtained[P_FirstSkill] == Empower)
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				float range_projectile = 600;
				float speed_projectile = 450;

				sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, position_player, velocity_player, speed_projectile);
				float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

				if (GlobalFunction::getRandomRange(1, 1000) <= 500)
				{
					angle_aiming += GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
				}
				else
				{
					angle_aiming -= GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
				}

				std::shared_ptr<EffectOrb> projectile = std::shared_ptr<EffectOrb>(new EffectOrb());
				projectile->Init(position_shooter,0, angle_aiming, id, speed_projectile, true, false, range_projectile, Ninja_E);
				std::vector<int> ListChangeType{ DamagePercentOverall };
				std::vector<float> ListChangeDuration{ 2 };
				std::vector<float> ListChangeValue{ static_cast<float>(100 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_first_skill.restart();
				can_use_first_skill = false;
			}
			else if (ListPetSkillObtained[P_FirstSkill] == Cruel)
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				float range_projectile = 600;
				float speed_projectile = 450;

				sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, position_player, velocity_player, speed_projectile);
				float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

				if (GlobalFunction::getRandomRange(1, 1000) <= 500)
				{
					angle_aiming += GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
				}
				else
				{
					angle_aiming -= GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
				}

				std::shared_ptr<EffectOrb> projectile = std::shared_ptr<EffectOrb>(new EffectOrb());
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Ninja_E);
				std::vector<int> ListChangeType{ LifeSteal };
				std::vector<float> ListChangeDuration{ 10 };
				std::vector<float> ListChangeValue{ static_cast<float>(30 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_first_skill.restart();
				can_use_first_skill = false;
			}
			else if (ListPetSkillObtained[P_FirstSkill] == SelfEsteem)
			{
				attack_speed_modifier = 3 * (1 + 0.05*PetAttributes[Power_E]);
				clock_attack_speed_bonus.restart();
				clock_first_skill.restart();
				can_use_first_skill = false;
			}
			else if (ListPetSkillObtained[P_FirstSkill] == HugeShuriken)
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				float range_projectile = 700;
				float speed_projectile = 650;

				if (GlobalFunction::GetDistanceBetweenTwoPositions(position_shooter, target_position) <= range_projectile)
				{
					sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, target_position, target_velocity, speed_projectile);
					float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

					if (GlobalFunction::getRandomRange(1, 1000) <= 500)
					{
						angle_aiming += GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
					}
					else
					{
						angle_aiming -= GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
					}

					std::shared_ptr<DeadlyShuriken> projectile = std::shared_ptr<DeadlyShuriken>(new DeadlyShuriken());
					projectile->Init(position_shooter, parent->GetDamage() * 3.5* (1 + 0.05*PetAttributes[Power_E]), angle_aiming, id, speed_projectile, false, true, range_projectile);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();
					clock_first_skill.restart();
					can_use_first_skill = false;
				}
			}
		}
	}

#pragma endregion FirstSkill

#pragma region SecondSkill

	if (ListPetSkillObtained[P_SecondSkill] != NoSkill)
	{
		if (can_use_second_skill)
		{
			if (ListPetSkillObtained[P_SecondSkill] == Frenzy)
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				float range_projectile = distance_between_player + 100;
				float speed_projectile = 450;

				sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, position_player, velocity_player, speed_projectile);
				float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

				if (GlobalFunction::getRandomRange(1, 1000) <= 500)
				{
					angle_aiming += GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
				}
				else
				{
					angle_aiming -= GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
				}

				std::shared_ptr<EffectOrb> projectile = std::shared_ptr<EffectOrb>(new EffectOrb());
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Ninja_E);
				std::vector<int> ListChangeType{ AttackSpeedPercent };
				std::vector<float> ListChangeDuration{ 4 };
				std::vector<float> ListChangeValue{ static_cast<float>(50 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_second_skill.restart();
				can_use_second_skill = false;
			}
			else if (ListPetSkillObtained[P_SecondSkill] == Empower)
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				float range_projectile = distance_between_player + 100;
				float speed_projectile = 450;

				sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, position_player, velocity_player, speed_projectile);
				float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

				if (GlobalFunction::getRandomRange(1, 1000) <= 500)
				{
					angle_aiming += GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
				}
				else
				{
					angle_aiming -= GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
				}

				std::shared_ptr<EffectOrb> projectile = std::shared_ptr<EffectOrb>(new EffectOrb());
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Ninja_E);
				std::vector<int> ListChangeType{ DamagePercentOverall };
				std::vector<float> ListChangeDuration{ 2 };
				std::vector<float> ListChangeValue{ static_cast<float>(100 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_second_skill.restart();
				can_use_second_skill = false;
			}
			else if (ListPetSkillObtained[P_SecondSkill] == Cruel)
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				float range_projectile = distance_between_player + 100;
				float speed_projectile = 450;

				sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, position_player, velocity_player, speed_projectile);
				float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

				if (GlobalFunction::getRandomRange(1, 1000) <= 500)
				{
					angle_aiming += GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
				}
				else
				{
					angle_aiming -= GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
				}

				std::shared_ptr<EffectOrb> projectile = std::shared_ptr<EffectOrb>(new EffectOrb());
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Ninja_E);
				std::vector<int> ListChangeType{ LifeSteal };
				std::vector<float> ListChangeDuration{ 10 };
				std::vector<float> ListChangeValue{ static_cast<float>(30 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_second_skill.restart();
				can_use_second_skill = false;
			}
			else if (ListPetSkillObtained[P_SecondSkill] == SelfEsteem)
			{
				attack_speed_modifier = 3 * (1 + 0.05*PetAttributes[Power_E]);
				clock_attack_speed_bonus.restart();
				clock_second_skill.restart();
				can_use_second_skill = false;
			}
			else if (ListPetSkillObtained[P_SecondSkill] == HugeShuriken)
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				float range_projectile = 600;
				float speed_projectile = 650;

				if (GlobalFunction::GetDistanceBetweenTwoPositions(target_position, position_shooter) <= range_projectile)
				{
					sf::Vector2f position_aiming = GlobalFunction::PositionPrediction(position_shooter, target_position, target_velocity, speed_projectile);
					float angle_aiming = GlobalFunction::GetRotationBetweenTwoPositions(position_shooter, position_aiming);

					if (GlobalFunction::getRandomRange(1, 1000) <= 500)
					{
						angle_aiming += GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
					}
					else
					{
						angle_aiming -= GlobalFunction::getRandomRange(1, 22 - PetAttributes[Intelligence_E]) - 1;
					}

					std::shared_ptr<DeadlyShuriken> projectile = std::shared_ptr<DeadlyShuriken>(new DeadlyShuriken());
					projectile->Init(position_shooter, parent->GetDamage() * 3.5* (1 + 0.05*PetAttributes[Power_E]), angle_aiming, id, speed_projectile, false, true, range_projectile);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();
					clock_second_skill.restart();
					can_use_second_skill = false;
				}
			}
		}
	}

#pragma endregion SecondSkill

#pragma endregion Skill

#pragma region Passive

	if (ListPetSkillObtained[P_FirstPassive] != NoSkill)
	{
		if (ListPetSkillObtained[P_FirstPassive] == PassiveDmg)
		{
			parent->GivePlayerChangeStat(DamagePercent, -1, 5 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_FirstPassive] == PassiveSpeed)
		{
			parent->GivePlayerChangeStat(MovementSpeedPercent, -1, 3 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_FirstPassive] == PassiveAts)
		{
			parent->GivePlayerChangeStat(AttackSpeedPercent, -1, 8 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_FirstPassive] == PassiveLifesteal)
		{
			parent->GivePlayerChangeStat(LifeSteal, -1, 4 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_FirstPassive] == PassiveCooldown)
		{
			parent->GivePlayerChangeStat(CooldownReduction, -1, 7 * (1 + 0.05*PetAttributes[Power_E]));
		}
	}

	if (ListPetSkillObtained[P_SecondPassive] != NoSkill)
	{
		if (ListPetSkillObtained[P_SecondPassive] == PassiveDmg)
		{
			parent->GivePlayerChangeStat(DamagePercent, -1, 5 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_SecondPassive] == PassiveSpeed)
		{
			parent->GivePlayerChangeStat(MovementSpeedPercent, -1, 3 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_SecondPassive] == PassiveAts)
		{
			parent->GivePlayerChangeStat(AttackSpeedPercent, -1, 8 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_SecondPassive] == PassiveLifesteal)
		{
			parent->GivePlayerChangeStat(LifeSteal, -1, 4 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_SecondPassive] == PassiveCooldown)
		{
			parent->GivePlayerChangeStat(CooldownReduction, -1, 7 * (1 + 0.05*PetAttributes[Power_E]));
		}
	}

#pragma endregion Passive
}

void Ninja::SelectAbility(int type_ability, int ability_chosen)
{
	ListPetSkillObtainedForInterface[type_ability] = ability_chosen;
	if (ability_chosen == 0)
	{
		ListPetSkillObtained[type_ability] = ListPetSkillPossible[type_ability].x;
	}
	else
	{
		ListPetSkillObtained[type_ability] = ListPetSkillPossible[type_ability].y;
	}
}

void Ninja::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(sprite_pet.getPosition() + sf::Vector2f(0, size_pet.y / 2 - 6));
	window.draw(shadow);
}

sf::Vector2f Ninja::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, -5);
}

void Ninja::SaveInformation(int current_pet_id)
{
	int current_save = ListObjectsSingleton::instance()->GetCurrentSave();
	std::ofstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Pet1.txt", std::fstream::app);
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Pet2.txt", std::fstream::app);
	}
	else
	{
		myfile.open("Pet3.txt", std::fstream::app);
	}
	myfile.seekp(std::ios::end);
	myfile << "NewPet";
	myfile << std::endl;

	if (true)
	{
		myfile << "IdItem";
		myfile << std::endl;
		myfile << " < ";
		if (current_pet_id == id)
		{
			myfile << "true";
			myfile << std::string(" ");
		}
		else
		{
			myfile << "false";
			myfile << std::string(" ");
		}
		myfile << " > ";
		myfile << std::endl;
	}

	myfile << "PetAttributes";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < PetAttributes.size(); i++)
	{
		std::string str("" + std::to_string(PetAttributes[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "PetMaxAttributes";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < PetMaxAttributes.size(); i++)
	{
		std::string str("" + std::to_string(PetMaxAttributes[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "ListPetSkillPossible";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < ListPetSkillPossible.size(); i++)
	{
		std::string str("" + std::to_string(ListPetSkillPossible[i].x));
		myfile << str;
		myfile << std::string(" ");

		std::string str1("" + std::to_string(ListPetSkillPossible[i].y));
		myfile << str1;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "ListPetSkillObtained";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < ListPetSkillObtained.size(); i++)
	{
		std::string str("" + std::to_string(ListPetSkillObtained[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "ListPetSkillObtainedForInterface";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < ListPetSkillObtainedForInterface.size(); i++)
	{
		std::string str("" + std::to_string(ListPetSkillObtainedForInterface[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	if (true)
	{
		myfile << "exp";
		myfile << std::endl;
		myfile << " < ";
		float number = exp;
		std::string str("" + std::to_string(number));
		myfile << str;
		myfile << " ";
		myfile << " > ";
		myfile << std::endl;
	}

	if (true)
	{
		myfile << "level";
		myfile << std::endl;
		myfile << " < ";
		int number = level;
		std::string str("" + std::to_string(number));
		myfile << str;
		myfile << " ";
		myfile << " > ";
		myfile << std::endl;
	}

	if (true)
	{
		myfile << "TypePet";
		myfile << std::endl;
		myfile << " < ";
		int number = Ninja_E;
		std::string str("" + std::to_string(number));
		myfile << str;
		myfile << " ";
		myfile << " > ";
		myfile << std::endl;
	}

	myfile.close();
}

void Ninja::InitWithInformation(std::vector<int> PetAttributes, std::vector<int> PetMaxAttributes, std::vector<sf::Vector2i> ListPetSkillPossible, std::vector<int> ListPetSkillObtained, std::vector<int> ListPetSkillObtainedForInterface, float exp, int level)
{
	this->PetAttributes = PetAttributes;
	this->PetMaxAttributes = PetMaxAttributes;
	this->ListPetSkillPossible = ListPetSkillPossible;
	this->ListPetSkillObtained = ListPetSkillObtained;
	this->ListPetSkillObtainedForInterface = ListPetSkillObtainedForInterface;
	this->exp = exp;
	this->level = level;
}
