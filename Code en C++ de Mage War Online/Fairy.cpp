#include "stdafx.h"
#include "Fairy.h"

Fairy::Fairy(int id_received)
{
	if (!texture_pet.loadFromFile("Fairy.png"))
	{
		std::cout << "Error while loading Fairy texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("FairyShadow.png"))
	{
		std::cout << "Error while loading Fairy shadow texture" << std::endl;
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
			sf::String str1 = "Flowering";
			sf::String str2 = "Magic Leaf";
			sf::String str3 = "Drain";
			sf::String str4 = "Heal";
			sf::String str5 = "Recharge";
			sf::String str6 = "Rest";
			sf::String str7 = "Exalt";
			sf::String str8 = "Life Orb";
			sf::String str9 = "Amplified";
			sf::String str10 = "Healthy";
			sf::String str11 = "Robust";
			sf::String str12 = "Lively";
			sf::String str13 = "Strengthened";

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
			sf::String str1 = "Grow a flower each 2 seconds. When the player touches the flower, he is healed for 125% of player's damage. Each 2 seconds, the flower's healing power is increased by 25%.";
			sf::String str2 = "Throw a magic leaf at a rate equal to 75% of the player's attack speed. When it collides with the player, the magic leaf restores the player's shield by 30% of his damage. Long range.";
			sf::String str3 = "Throw a spike at a rate equal to 60% of the player's attack speed. The spike deals 65% of player's damage and heals the player for the same amount. Medium range.";
			sf::String str4 = "Cast an orb that increases the player's health recovery by 5% of his maximum health for 10 seconds.";
			sf::String str5 = "Cast an orb that increases the player's shield recovery by 10% of his maximum health for 10 seconds.";
			sf::String str6 = "Cast an orb that increases the player's heal received by +100% for 3 seconds.";
			sf::String str7 = "Cast an orb that turns the player immune for 2 seconds.";
			sf::String str8 = "Throw a huge orb that heals the player for 600% of his's damage and restores his shield for the same amount. Medium range.";
			sf::String str9 = "Increase the pet's healing and shielding ability power by 25%.";
			sf::String str10 = "Increase the player's maximum health by 10%.";
			sf::String str11 = "Increase the player's armor by 10%.";
			sf::String str12 = "Increase the player's health recovery by 0.5% of his maximum health.";
			sf::String str13 = "Increase the player's shield recovery by 1.5% of his maximum health.";

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
			sf::String str1 = "Floraison";
			sf::String str2 = "Feuille Magique";
			sf::String str3 = "Drainage";
			sf::String str4 = "Soin";
			sf::String str5 = "Recharge";
			sf::String str6 = "Repos";
			sf::String str7 = "Exalter";
			sf::String str8 = "Orbe de vie";
			sf::String str9 = "Amplifié";
			sf::String str10 = "Sain";
			sf::String str11 = "Robuste";
			sf::String str12 = "Vigoureux";
			sf::String str13 = "Renforcé";

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
			sf::String str1 = "Croît une fleur à chaque 2 secondes. Lorsque le joueur touche la fleur, il est soigné de 125% de ses dégâts. À chaque 2 secondes, les soins de la fleur sont augmentés de 25%.";
			sf::String str2 = "Lance une feuille magique avec une fréquence égale à 75% de la vitesse d'attaque du joueur. Lorsqu'elle touche le joueur, la feuille magique restaure le bouclier du joueur de 30% de ses dégâts. Longue portée.";
			sf::String str3 = "Lance une pointe avec une fréquence égale à 60% de la vitesse d'attaque du joueur. La pointe inflige 65% des dégâts du joueur et soigne le joueur pour le même montant. Moyenne portée.";
			sf::String str4 = "Jete une orbe qui augmente la regénération de la vie du joueur de 5% de sa vie totale pendant 10 secondes.";
			sf::String str5 = "Jete une orbe qui augmente la regénération du bouclier du joueur de 10% de sa vie totale pendant 10 secondes.";
			sf::String str6 = "Jete une orbe qui augmente les soins reçus du joueur de +100% pendant 3 secondes.";
			sf::String str7 = "Jete une orbe qui rend le joueur immunisé pendant 2 secondes.";
			sf::String str8 = "Lance une énorme orbe qui soigne le joueur pour 600% de ses dégâts et restaure son bouclier pour le même montant. Moyenne portée";
			sf::String str9 = "Augmente la force des abilités de soins et de restauration du bouclier du familier de 25%.";
			sf::String str10 = "Augmente la vie totale du joueur de 10%.";
			sf::String str11 = "Augmente l'armure du joueur de 10%.";
			sf::String str12 = "Augmente la regénération de la vie du joueur de 0.5% de sa vie totale.";
			sf::String str13 = "Augmente la regénération du bouclier du joueur de 1.5% de sa vie totale.";

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

Fairy::~Fairy()
{
	parent.reset();
}

void Fairy::Init(std::shared_ptr<Player> player)
{
	parent = player;
	sprite_pet.setPosition(parent->GetCurrentPosition());
}

void Fairy::Update(float DELTATIME, sf::Vector2f target_position, sf::Vector2f target_velocity)
{
	MovementGestion(DELTATIME);
	UseAbilities(target_position, target_velocity);
	CooldownGestion();
}

void Fairy::MovementGestion(float DELTATIME)
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

void Fairy::CuttingSprite()
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

void Fairy::CooldownGestion()
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

void Fairy::Draw(sf::RenderWindow &window)
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

void Fairy::GetRandomSkill()
{
	int random_number;

#pragma region BasicAttack
	std::vector<int> PoolBasicAttack{ Flowering_E,MagicLeaf_E,Drain_E };

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
	std::vector<int> PoolSkill{ Heal_E,Recharge_E,Rest_E,Exalt_E,LifeOrb_E };

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
	std::vector<int> PoolPassive{ PassivePetPower,PassiveHealth,PassiveArmor,PassiveHpRecovery,PassiveShieldRecovery };

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

void Fairy::UseAbilities(sf::Vector2f target_position, sf::Vector2f target_velocity)
{
	if (ListPetSkillObtained[P_FirstPassive] == PassivePetPower || ListPetSkillObtained[P_SecondSkill])
	{
		recovering_ability_power_modifier = 1.25;
	}
	else
	{
		recovering_ability_power_modifier = 1;
	}

#pragma region BasicAttack

	if (ListPetSkillObtained[P_BasicAttack] != NoSkill)
	{
		if (ListPetSkillObtained[P_BasicAttack] == Flowering_E)
		{
			if (clock_basic_attack.getElapsedTime().asSeconds() >= 2)
			{
				float range_projectile = 320;
				sf::Vector2f position_shooter = GetCurrentPosition();
				if (GlobalFunction::GetDistanceBetweenTwoPositions(target_position, position_shooter) <= range_projectile)
				{
					float speed_projectile = 650;

					if (!parent->GetIfPlayerOutOfCombat())
					{
						std::shared_ptr<Flowering> projectile = std::shared_ptr<Flowering>(new Flowering());
						projectile->Init(position_shooter, parent->GetDamage() * 1.25 * (1 + 0.05*PetAttributes[Power_E]), 0, id, speed_projectile, true, false, range_projectile);
						ProjectileGestion::instance()->AddObjectToList(projectile);
						projectile.reset();

						clock_basic_attack.restart();
					}
				}
			}
		}
		else if (ListPetSkillObtained[P_BasicAttack] == MagicLeaf_E)
		{
			if (clock_basic_attack.getElapsedTime().asSeconds() >= 1 / (parent->GetAttackSpeed()*0.75))
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				float range_projectile = 600;
				float speed_projectile = 650;

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

				std::shared_ptr<MagicLeaf> projectile = std::shared_ptr<MagicLeaf>(new MagicLeaf());
				projectile->Init(position_shooter, parent->GetDamage() * 0.3 * (1 + 0.05*PetAttributes[Power_E]), angle_aiming, id, speed_projectile, true, false, range_projectile);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();

				clock_basic_attack.restart();
			}
		}
		else if (ListPetSkillObtained[P_BasicAttack] == Drain_E)
		{
			if (clock_basic_attack.getElapsedTime().asSeconds() >= 1 / (parent->GetAttackSpeed()*0.6))
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

					std::shared_ptr<Spike> projectile = std::shared_ptr<Spike>(new Spike());
					projectile->Init(position_shooter, parent->GetDamage() * 0.65* (1 + 0.05*PetAttributes[Power_E]), angle_aiming, id, speed_projectile, false, true, range_projectile,parent);
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
			if (ListPetSkillObtained[P_FirstSkill] == Heal_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Fairy_E);
				std::vector<int> ListChangeType{ HpPercentRecovery };
				std::vector<float> ListChangeDuration{ 10 };
				std::vector<float> ListChangeValue{ static_cast<float>(5 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_first_skill.restart();
				can_use_first_skill = false;
			}
			else if (ListPetSkillObtained[P_FirstSkill] == Recharge_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Fairy_E);
				std::vector<int> ListChangeType{ ShieldHpPercentRecovery };
				std::vector<float> ListChangeDuration{ 10 };
				std::vector<float> ListChangeValue{ static_cast<float>(10 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_first_skill.restart();
				can_use_first_skill = false;
			}
			else if (ListPetSkillObtained[P_FirstSkill] == Rest_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Fairy_E);
				std::vector<int> ListChangeType{ HpRecoveryPercentIncrease };
				std::vector<float> ListChangeDuration{ 3 };
				std::vector<float> ListChangeValue{ static_cast<float>(100 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_first_skill.restart();
				can_use_first_skill = false;
			}
			else if (ListPetSkillObtained[P_FirstSkill] == Exalt_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Fairy_E);
				std::vector<int> ListChangeType{ Immunity };
				std::vector<float> ListChangeDuration{ 2 };
				std::vector<float> ListChangeValue{ static_cast<float>(0 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_first_skill.restart();
				can_use_first_skill = false;
			}
			else if (ListPetSkillObtained[P_FirstSkill] == LifeOrb_E)
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				float range_projectile = 450;
				float speed_projectile = 700;

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

					std::shared_ptr<LifeOrb> projectile = std::shared_ptr<LifeOrb>(new LifeOrb());
					projectile->Init(position_shooter, parent->GetDamage() * 6* (1 + 0.05*PetAttributes[Power_E]), angle_aiming, id, speed_projectile, true, false, range_projectile);
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
			if (ListPetSkillObtained[P_SecondSkill] == Heal_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Fairy_E);
				std::vector<int> ListChangeType{ HpPercentRecovery };
				std::vector<float> ListChangeDuration{ 10 };
				std::vector<float> ListChangeValue{ static_cast<float>(5 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_second_skill.restart();
				can_use_second_skill = false;
			}
			else if (ListPetSkillObtained[P_SecondSkill] == Recharge_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Fairy_E);
				std::vector<int> ListChangeType{ ShieldHpPercentRecovery };
				std::vector<float> ListChangeDuration{ 10 };
				std::vector<float> ListChangeValue{ static_cast<float>(10 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_second_skill.restart();
				can_use_second_skill = false;
			}
			else if (ListPetSkillObtained[P_SecondSkill] == Rest_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Fairy_E);
				std::vector<int> ListChangeType{ HpRecoveryPercentIncrease };
				std::vector<float> ListChangeDuration{ 3 };
				std::vector<float> ListChangeValue{ static_cast<float>(100 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_second_skill.restart();
				can_use_second_skill = false;
			}
			else if (ListPetSkillObtained[P_SecondSkill] == Exalt_E)
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
				projectile->Init(position_shooter, 0, angle_aiming, id, speed_projectile, true, false, range_projectile, Fairy_E);
				std::vector<int> ListChangeType{ Immunity };
				std::vector<float> ListChangeDuration{ 2 };
				std::vector<float> ListChangeValue{ static_cast<float>(0 * (1 + 0.05*PetAttributes[Power_E])) };
				projectile->GiveChangeEffect(ListChangeType, ListChangeDuration, ListChangeValue);
				ProjectileGestion::instance()->AddObjectToList(projectile);
				projectile.reset();
				clock_second_skill.restart();
				can_use_second_skill = false;
			}
			else if (ListPetSkillObtained[P_SecondSkill] == LifeOrb_E)
			{
				sf::Vector2f position_player = parent->GetCurrentPosition();
				sf::Vector2f position_shooter = GetCurrentPosition();
				sf::Vector2f velocity_player = parent->GetVelocityPlayer();
				float distance_between_player = GlobalFunction::GetDistanceBetweenTwoPositions(position_player, position_shooter);

				float range_projectile = 450;
				float speed_projectile = 700;

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

					std::shared_ptr<LifeOrb> projectile = std::shared_ptr<LifeOrb>(new LifeOrb());
					projectile->Init(position_shooter, parent->GetDamage() * 6 * (1 + 0.05*PetAttributes[Power_E]), angle_aiming, id, speed_projectile, true, false, range_projectile);
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
		if (ListPetSkillObtained[P_FirstPassive] == PassiveHealth)
		{
			parent->GivePlayerChangeStat(HealthPercent, -1, 10 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_FirstPassive] == PassiveArmor)
		{
			parent->GivePlayerChangeStat(DefensePercent, -1, 10 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_FirstPassive] == PassiveHpRecovery)
		{
			parent->GivePlayerChangeStat(HpPercentRecovery, -1, 0.5 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_FirstPassive] == PassiveShieldRecovery)
		{
			parent->GivePlayerChangeStat(ShieldHpPercentRecovery, -1, 1.5 * (1 + 0.05*PetAttributes[Power_E]));
		}
	}

	if (ListPetSkillObtained[P_SecondPassive] != NoSkill)
	{
		if (ListPetSkillObtained[P_SecondPassive] == PassiveHealth)
		{
			parent->GivePlayerChangeStat(HealthPercent, -1, 10 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_SecondPassive] == PassiveArmor)
		{
			parent->GivePlayerChangeStat(DefensePercent, -1, 10 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_SecondPassive] == PassiveHpRecovery)
		{
			parent->GivePlayerChangeStat(HpPercentRecovery, -1, 0.5 * (1 + 0.05*PetAttributes[Power_E]));
		}
		else if (ListPetSkillObtained[P_SecondPassive] == PassiveShieldRecovery)
		{
			parent->GivePlayerChangeStat(ShieldHpPercentRecovery, -1, 1.5 * (1 + 0.05*PetAttributes[Power_E]));
		}
	}

#pragma endregion Passive
}

void Fairy::SelectAbility(int type_ability, int ability_chosen)
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

void Fairy::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(sprite_pet.getPosition() + sf::Vector2f(0, size_pet.y / 2));
	window.draw(shadow);
}

sf::Vector2f Fairy::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, -5);
}

void Fairy::SaveInformation(int current_pet_id)
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
		int number = Fairy_E;
		std::string str("" + std::to_string(number));
		myfile << str;
		myfile << " ";
		myfile << " > ";
		myfile << std::endl;
	}

	myfile.close();
}

void Fairy::InitWithInformation(std::vector<int> PetAttributes, std::vector<int> PetMaxAttributes, std::vector<sf::Vector2i> ListPetSkillPossible, std::vector<int> ListPetSkillObtained, std::vector<int> ListPetSkillObtainedForInterface, float exp, int level)
{
	this->PetAttributes = PetAttributes;
	this->PetMaxAttributes = PetMaxAttributes;
	this->ListPetSkillPossible = ListPetSkillPossible;
	this->ListPetSkillObtained = ListPetSkillObtained;
	this->ListPetSkillObtainedForInterface = ListPetSkillObtainedForInterface;
	this->exp = exp;
	this->level = level;
}

