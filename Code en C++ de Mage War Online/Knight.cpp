#include "stdafx.h"
#include "Knight.h"

Knight::Knight(int id_received)
{
	if (!texture_pet.loadFromFile("Knight.png"))
	{
		std::cout << "Error while loading Knight texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("KnightShadow.png"))
	{
		std::cout << "Error while loading Knight shadow texture" << std::endl;
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
			sf::String str1 = "Shield";
			sf::String str2 = "Spear";
			sf::String str3 = "Broadsword";
			sf::String str4 = "Boost";
			sf::String str5 = "Armouring";
			sf::String str6 = "Indestructible";
			sf::String str7 = "Adrenaline Rush";
			sf::String str8 = "Impenetrable";
			sf::String str9 = "Quickness";
			sf::String str10 = "Healthy";
			sf::String str11 = "Robust";
			sf::String str12 = "Strengh";
			sf::String str13 = "Inalienable";

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
			sf::String str1 = "Throw a shield each second. When it collides with the player, the shield increases the player's armor by +10% of his damage for 1 second. Medium range.";
			sf::String str2 = "Throw a spear at a rate equal to 10% of the player's attack speed. The spike deals 225% of player's damage and stuns the target hit for 1 second. Long range.";
			sf::String str3 = "Throw a broadsword at a rate equal to 25% of the player's attack speed. The broadsword deals 125% of player's damage and slows the target by 5% for 3 seconds. Medium range.";
			sf::String str4 = "Cast an orb that increases the player's maximum health by 50% for 10 seconds. Also heals the player for the half of the amount.";
			sf::String str5 = "Cast an orb that increases the player's armor by 35% for 8 seconds.";
			sf::String str6 = "Cast an orb that turns the player immune for 5 seconds and slows him by 90% for the duration.";
			sf::String str7 = "Cast an orb that prevents the player's health to drop below 1 for 5 seconds.";
			sf::String str8 = "The pet can block any enemy projectile for 4 seconds.";
			sf::String str9 = "Increase the player's damage by 5%.";
			sf::String str10 = "Increase the player's maximum health by 10%.";
			sf::String str11 = "Increase the player's armor by 10%.";
			sf::String str12 = "Increase the player's attack speed by 8%.";
			sf::String str13 = "Decrease the duration of stuns recived by 30%.";

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
			sf::String str1 = "Bouclier";
			sf::String str2 = "Lance";
			sf::String str3 = "Glaive";
			sf::String str4 = "Stimulé";
			sf::String str5 = "Blindage";
			sf::String str6 = "Indestructible";
			sf::String str7 = "Poussée D'Adrénaline";
			sf::String str8 = "Impénétrable";
			sf::String str9 = "Rapidité";
			sf::String str10 = "Sain";
			sf::String str11 = "Robuste";
			sf::String str12 = "Force";
			sf::String str13 = "Inaliénable";

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
			sf::String str1 = "Lance un bouclier à chaque seconde. Lorsqu'il touche le joueur, le bouclier augmente l'armure du joueur de 10% de ses dégâts pendant une seconde. Moyenne portée.";
			sf::String str2 = "Projette une lance avec une fréquence égale à 10% de la vitesse d'attaque du joueur. La pointe inflige 225% des dégâts du joueur et étourtit la cible touchée pendant 1 seconde. Longue portée.";
			sf::String str3 = "Lance un glaive avec une fréquence égale à 25% de la vitesse d'attaque du joueur. Le Glaive inflige 125% des dégâts du joueur et ralentit la cible touchée de 5% pendant 3 secondes. Moyenne portée.";
			sf::String str4 = "Jete une orbe qui augmente la vie totale du joueur de 50% pendant 10 secondes. Soigne aussi le joueur de la moitié du montant.";
			sf::String str5 = "Jete une orbe qui augmente l'armure du joueur de 35% pendant 8 secondes.";
			sf::String str6 = "Jete une orbe qui rend le joueur immunisé pendant 3 secondes et qui le ralentit de 90% pour toute la durée.";
			sf::String str7 = "Jete une orbe qui empêche la vie du joueur de descendre sous 1 pendant 5 secondes.";
			sf::String str8 = "Le familier peut bloqué tous les projectiles ennemies pendant 4 secondes.";
			sf::String str9 = "Augmente les dégâts du joueur de 5%.";
			sf::String str10 = "Augmente la vie totale du joueur de 10%.";
			sf::String str11 = "Augmente l'armure du joueur de 10%.";
			sf::String str12 = "Augmente la vitesse d'attaque du joueur de 8%.";
			sf::String str13 = "Réduit la durée des étourdissements reçus de 30%.";

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

Knight::~Knight()
{
	parent.reset();
}

void Knight::Init(std::shared_ptr<Player> player)
{
	parent = player;
	sprite_pet.setPosition(parent->GetCurrentPosition());
}

void Knight::Update(float DELTATIME, sf::Vector2f target_position, sf::Vector2f target_velocity)
{
	MovementGestion(DELTATIME);
	UseAbilities(target_position, target_velocity);
	CooldownGestion();
}

void Knight::MovementGestion(float DELTATIME)
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

void Knight::CuttingSprite()
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

void Knight::CooldownGestion()
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

void Knight::Draw(sf::RenderWindow &window)
{
	CuttingSprite();
	window.draw(sprite_pet);

	sf::Vector2f position_pet = GetCurrentPosition();
	if (level >= 5 && ListPetSkillObtained[P_FirstSkill] != NoSkill && !can_use_first_skill)
	{
		rect_first_skill.setPosition(position_pet + sf::Vector2f(0, -size_pet.y / 2 - 20));
		window.draw(rect_first_skill);
		rect_first_skill_cooldown.setPosition(position_pet + sf::Vector2f(-size_pet.x / 2, -size_pet.y / 2 - 20));
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

void Knight::GetRandomSkill()
{
	int random_number;

#pragma region BasicAttack
	std::vector<int> PoolBasicAttack{ Spear_E,Broadsword_E,Shield_E };

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
	std::vector<int> PoolSkill{ Boost_E,Armored_E,Indestructible_E,AdrenalineRush_E,Impenetrable_E };

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
	std::vector<int> PoolPassive{ PassiveDmg,PassiveHealth,PassiveArmor,PassiveAts,PassiveStun };

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

void Knight::UseAbilities(sf::Vector2f target_position, sf::Vector2f target_velocity)
{
#pragma region BasicAttack

	if (ListPetSkillObtained[P_BasicAttack] != NoSkill)
	{
		if (ListPetSkillObtained[P_BasicAttack] == Shield_E)
		{
			if (clock_basic_attack.getElapsedTime().asSeconds() >= 1)
			{
				if (!parent->GetIfPlayerOutOfCombat())
				{
					sf::Vector2f position_player = parent->GetCurrentPosition();
					sf::Vector2f position_shooter = GetCurrentPosition();
					sf::Vector2f velocity_player = parent->GetVelocityPlayer();

					float range_projectile = 450;
					float speed_projectile = 550;

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

					std::shared_ptr<Shield> projectile = std::shared_ptr<Shield>(new Shield());
					projectile->Init(position_shooter, 0, 0, id, speed_projectile, true, false, range_projectile);
					std::vector<int> listType{ DefenseAddition };
					std::vector<float> listDuration{ 1 };
					std::vector<float> listValue{ static_cast<float>(parent->GetDamage() * 0.1 * (1 + 0.05*PetAttributes[Power_E])) };
					projectile->GiveChangeEffect(listType, listDuration, listValue);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();

					clock_basic_attack.restart();
				}
			}
		}
		else if (ListPetSkillObtained[P_BasicAttack] == Spear_E)
		{
			if (clock_basic_attack.getElapsedTime().asSeconds() >= 1 / (parent->GetAttackSpeed()*0.1))
			{
				float range_projectile = 700;
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

					std::shared_ptr< Spear> projectile = std::shared_ptr< Spear>(new  Spear());
					projectile->Init(position_shooter, parent->GetDamage() * 2.25 * (1 + 0.05*PetAttributes[Power_E]), angle_aiming, id, speed_projectile, false,true, range_projectile);
					projectile->GiveStunEffect(1);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();

					clock_basic_attack.restart();
				}
			}
		}
		else if (ListPetSkillObtained[P_BasicAttack] == Broadsword_E)
		{
			if (clock_basic_attack.getElapsedTime().asSeconds() >= 1 / (parent->GetAttackSpeed()*0.25))
			{
				float range_projectile = 425;
				sf::Vector2f position_shooter = GetCurrentPosition();
				if (GlobalFunction::GetDistanceBetweenTwoPositions(target_position, position_shooter) <= range_projectile)
				{
					float speed_projectile = 750;

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

					std::shared_ptr< Broadsword> projectile = std::shared_ptr< Broadsword>(new  Broadsword());
					projectile->Init(position_shooter, parent->GetDamage() * 1.25 * (1 + 0.05*PetAttributes[Power_E]), angle_aiming, id, speed_projectile, false, true, range_projectile);
					projectile->GiveSlowEffect(3,5);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();

					clock_basic_attack.restart();
				}
			}
		}
	}

#pragma endregion BasicAttack

#pragma region FirstSkill

	if (ListPetSkillObtained[P_FirstSkill] != NoSkill)
	{
		if (can_use_first_skill)
		{
			if (ListPetSkillObtained[P_FirstSkill] == Boost_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Knight_E);
				std::vector<int> ListChangeType{ HealthPercent,HpPercentRecovery };
				std::vector<float> ListChangeDuration{ 10,-1 };
				std::vector<float> ListChangeValue{ static_cast<float>(50 * (1 + 0.05*PetAttributes[Power_E])),static_cast<float>(50 * (1 + 0.05*PetAttributes[Power_E])/2) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_first_skill.restart();
				can_use_first_skill = false;
			}
			else if (ListPetSkillObtained[P_FirstSkill] == Armored_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Knight_E);
				std::vector<int> ListChangeType{ DefensePercent };
				std::vector<float> ListChangeDuration{ 10 };
				std::vector<float> ListChangeValue{ static_cast<float>(35 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_first_skill.restart();
				can_use_first_skill = false;
			}
			else if (ListPetSkillObtained[P_FirstSkill] == Indestructible_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Knight_E);
				std::vector<int> ListChangeType{ Immunity,MovementSpeedPercent };
				std::vector<float> ListChangeDuration{ 5,5 };
				std::vector<float> ListChangeValue{ 0,90 };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_first_skill.restart();
				can_use_first_skill = false;
			}
			else if (ListPetSkillObtained[P_FirstSkill] == AdrenalineRush_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Knight_E);
				std::vector<int> ListChangeType{ CantDie };
				std::vector<float> ListChangeDuration{ 5 };
				std::vector<float> ListChangeValue{ 0 };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_first_skill.restart();
				can_use_first_skill = false;
			}
			else if (ListPetSkillObtained[P_FirstSkill] == Impenetrable_E)
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				if (!parent->GetIfPlayerOutOfCombat())
				{
					std::shared_ptr<TransparentRect> projectile = std::shared_ptr<TransparentRect>(new TransparentRect());
					projectile->Init(position_shooter, shared_from_this(),size_pet);
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
			if (ListPetSkillObtained[P_SecondSkill] == Boost_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Knight_E);
				std::vector<int> ListChangeType{ HealthPercent,HpPercentRecovery };
				std::vector<float> ListChangeDuration{ 10,-1 };
				std::vector<float> ListChangeValue{ static_cast<float>(50 * (1 + 0.05*PetAttributes[Power_E])),static_cast<float>(50 * (1 + 0.05*PetAttributes[Power_E]) / 2) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_second_skill.restart();
				can_use_second_skill = false;
			}
			else if (ListPetSkillObtained[P_SecondSkill] == Armored_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Knight_E);
				std::vector<int> ListChangeType{ DefensePercent };
				std::vector<float> ListChangeDuration{ 10 };
				std::vector<float> ListChangeValue{ static_cast<float>(35 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_second_skill.restart();
				can_use_second_skill = false;
			}
			else if (ListPetSkillObtained[P_SecondSkill] == Indestructible_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Knight_E);
				std::vector<int> ListChangeType{ Immunity,MovementSpeedPercent };
				std::vector<float> ListChangeDuration{ 5,5 };
				std::vector<float> ListChangeValue{ 0,90 };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_second_skill.restart();
				can_use_second_skill = false;
			}
			else if (ListPetSkillObtained[P_SecondSkill] == AdrenalineRush_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Knight_E);
				std::vector<int> ListChangeType{ CantDie };
				std::vector<float> ListChangeDuration{ 5 };
				std::vector<float> ListChangeValue{ 0 };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_second_skill.restart();
				can_use_second_skill = false;
			}
			else if (ListPetSkillObtained[P_SecondSkill] == Impenetrable_E)
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				if (!parent->GetIfPlayerOutOfCombat())
				{
					std::shared_ptr<TransparentRect> projectile = std::shared_ptr<TransparentRect>(new TransparentRect());
					projectile->Init(position_shooter, shared_from_this(), size_pet);
					ProjectileGestion::instance()->AddObjectToList(projectile);
					projectile.reset();
					clock_second_skill.restart();
					can_use_second_skill = false;
				}
			}
		}
	}

#pragma endregion SecondSkill

#pragma region Passive

	if (ListPetSkillObtained[P_FirstPassive] != NoSkill)
	{
		if (ListPetSkillObtained[P_FirstPassive] == PassiveDmg)
		{
			parent->GivePlayerChangeStat(DamagePercent, -1, 5 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_FirstPassive] == PassiveHealth)
		{
			parent->GivePlayerChangeStat(HealthPercent, -1, 10 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_FirstPassive] == PassiveArmor)
		{
			parent->GivePlayerChangeStat(DefensePercent, -1, 10 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_FirstPassive] == PassiveAts)
		{
			parent->GivePlayerChangeStat(AttackSpeedPercent, -1, 8 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_FirstPassive] == PassiveStun)
		{
			parent->GivePlayerChangeStat(StunReductionPercent, -1, 30 * (1 + 0.05*PetAttributes[Power_E]));
		}
	}

	if (ListPetSkillObtained[P_SecondPassive] != NoSkill)
	{
		if (ListPetSkillObtained[P_SecondPassive] == PassiveDmg)
		{
			parent->GivePlayerChangeStat(DamagePercent, -1, 5 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_SecondPassive] == PassiveHealth)
		{
			parent->GivePlayerChangeStat(HealthPercent, -1, 10 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_SecondPassive] == PassiveArmor)
		{
			parent->GivePlayerChangeStat(DefensePercent, -1, 10 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_SecondPassive] == PassiveAts)
		{
			parent->GivePlayerChangeStat(AttackSpeedPercent, -1, 8 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_SecondPassive] == PassiveStun)
		{
			parent->GivePlayerChangeStat(StunReductionPercent, -1, 30 * (1 + 0.05*PetAttributes[Power_E]));
		}
	}

#pragma endregion Passive
}

void Knight::SelectAbility(int type_ability, int ability_chosen)
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

void Knight::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(sprite_pet.getPosition() + sf::Vector2f(0, size_pet.y / 2 - 6));
	window.draw(shadow);
}

sf::Vector2f Knight::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}

void Knight::SaveInformation(int current_pet_id)
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
		int number = Knight_E;
		std::string str("" + std::to_string(number));
		myfile << str;
		myfile << " ";
		myfile << " > ";
		myfile << std::endl;
	}

	myfile.close();
}

void Knight::InitWithInformation(std::vector<int> PetAttributes, std::vector<int> PetMaxAttributes, std::vector<sf::Vector2i> ListPetSkillPossible, std::vector<int> ListPetSkillObtained, std::vector<int> ListPetSkillObtainedForInterface, float exp, int level)
{
	this->PetAttributes = PetAttributes;
	this->PetMaxAttributes = PetMaxAttributes;
	this->ListPetSkillPossible = ListPetSkillPossible;
	this->ListPetSkillObtained = ListPetSkillObtained;
	this->ListPetSkillObtainedForInterface = ListPetSkillObtainedForInterface;
	this->exp = exp;
	this->level = level;
}
