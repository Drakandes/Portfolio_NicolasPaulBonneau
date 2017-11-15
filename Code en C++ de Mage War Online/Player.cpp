#include "stdafx.h"
#include "Player.h"
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"

Player::Player()
{
	language = ListObjectsSingleton::instance()->GetCurrentLanguage();
	/*player_level = 19;
	player_experience = 166000;
	player_experience_needed_next_level = 167780;*/
	achievement_gestion.Init(ListObjectsSingleton::instance()->GetListStringAchiements());
	UpdatePlayerStats();

	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font player" << std::endl;
	}

	if (!skillbase_icone_texture.loadFromFile("SkillBase_icone_player_interface.png"))
	{
		std::cout << "Error while loading skillbase icone in player" << std::endl;
	}
	if (!texture_out_battle.loadFromFile("PeaceIcone.png"))
	{
		std::cout << "Error while loading peace icone in player" << std::endl;
	}
	if (!texture_health_bar_interface.loadFromFile("HealthBarInterface.png"))
	{
		std::cout << "Error while loading health bar icone in player" << std::endl;
	}
	if (!texture_big_player_health.loadFromFile("BigHealthBarInterface.png"))
	{
		std::cout << "Error while loading big health bar icone in player" << std::endl;
	}

	if (!texture_basic_big_player_health.loadFromFile("BasicBigHealthBarInterface.png"))
	{
		std::cout << "Error while loading big health bar icone in player" << std::endl;
	}

	if (!texture_health_potion.loadFromFile("HealthPotion_Icone.png"))
	{
		std::cout << "Error while loading big health bar icone in player" << std::endl;
	}

	if (!texture_player_experience_bar.loadFromFile("BigExperienceBarInterface.png"))
	{
		std::cout << "Error while loading experience bar icone in player" << std::endl;
	}

	if (!basic_skill_icone_texture.loadFromFile("SkillBase_icone.png"))
	{
		std::cout << "Error while loading basic skill icone in player" << std::endl;
	}

	std::vector<int> material;
	int stick = 40;
	int iron = 4;
	int ruby = 2;
	int emerald = 2;
	int topaz = 2;
	int magic_sand = 9;
	material.push_back(stick);
	material.push_back(iron);
	material.push_back(ruby);
	material.push_back(emerald);
	material.push_back(topaz);
	material.push_back(magic_sand);
	std::vector<int> miscallaneous;
	int health_potion = 0;
	miscallaneous.push_back(health_potion);
	inventory.push_back(material);
	inventory.push_back(miscallaneous);
	listAllArmors = ListObjectsSingleton::instance()->GetListArmor();
	listAllSkills = ListObjectsSingleton::instance()->GetListSkill();
	listAllGems = ListObjectsSingleton::instance()->GetListGem();
	listAllTalents = ListObjectsSingleton::instance()->GetListTalent();
	listScrollBonus = ListObjectsSingleton::instance()->GetListAchievementsBonus();

	if (!shadow_texture.loadFromFile("MageShadow.png"))
	{
		std::cout << "Error while loading mage shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), shadow_size, shadow_texture);
	shadow.setOrigin(sf::Vector2f(GetSize().x / 2, 0));

	for (int i = 0; i < NUMBERSKILL; i++)
	{
		std::vector<bool> listruneavailable{ false,false,false };
		listRuneAvailable.push_back(listruneavailable);
	}
}

Player::~Player()
{
	listAllActiveGems.clear();
	listAllArmors.clear();
	listAllGems.clear();
	listAllSkills.clear();
	listEquipment.clear();
	current_weapon.reset();
}

void Player::Init(sf::Vector2f position, sf::Vector2f position_view_player, sf::Vector2f window_dimension_received, int id_received)
{
	if (!player_texture[ClassWater].loadFromFile("Watermage.png"))
	{
		std::cout << "Error: Couldn't load Firemage texture" << std::endl;
	}

	if (!player_texture[ClassFire].loadFromFile("Firemage.png"))
	{
		std::cout << "Error: Couldn't load Firemage texture" << std::endl;
	}

	if (!player_texture[ClassGrass].loadFromFile("Grassmage.png"))
	{
		std::cout << "Error: Couldn't load Firemage texture" << std::endl;
	}
	if (!player_texture[ClassRock].loadFromFile("Rockmage.png"))
	{
		std::cout << "Error: Couldn't load Firemage texture" << std::endl;
	}

	UpdatePlayerStats();
	UpdateStatsWithEquipments();
	player_current_health = player_maximum_health;
	player_id = id_received;
	window_dimension = window_dimension_received;
	player_in_game_stat_interface.Init(position_view_player);
	player_money = player_starting_money;
	player_image.setOrigin(sf::Vector2f(player_image_size_x / 2, player_image_size_y / 2));
	player_image.setTexture(player_texture[current_class]);
	player_image.setPosition(position);
	position_going_to = position;
	player_health_bar.setOrigin(sf::Vector2f(size_health_bar.x / 2, size_health_bar.y /2 ));
	player_health_bar.setFillColor(sf::Color::Red);
	player_maximum_health_bar.setOrigin(sf::Vector2f(size_health_bar.x / 2, size_health_bar.y / 2));
	player_maximum_health_bar.setFillColor(sf::Color::Black);
	rect_sprinting_bar = GlobalFunction::CreateRectangleWithOrigin(size_sprinting_bar, sf::Vector2f(0, 0), sf::Color::Color(41, 47, 162));
	rect_shield_player_bar.setOrigin(sf::Vector2f(size_health_bar.x / 2, size_health_bar.y / 2));
	rect_shield_player_bar.setFillColor(sf::Color::Color(0,0,255,180));
	sprite_health_bar_interface = GlobalFunction::CreateSprite(sf::Vector2f(0, 0), size_health_bar_interface, texture_health_bar_interface);
	stun_bar.setOrigin(0, 2);
	stun_bar.setFillColor(sf::Color::Blue);
	bar_looting = GlobalFunction::CreateRectangleWithOrigin(size_bar_looting, position_bar_looting, sf::Color::Color(34, 139, 34));
	bar_looting_progress = GlobalFunction::CreateRectangleWithOrigin(size_bar_looting, position_bar_looting, sf::Color::Color(50, 205, 50));

	InitAllPlayerStaticInterface(position_view_player);
	GivePlayerChangeStat(Immunity, 5, 1);
}

void Player::DrawToScreen(sf::RenderWindow &window, sf::View &view_player, sf::Vector2f position_view_player)
{
	if (is_looting)
	{
		window.draw(bar_looting);
		window.draw(bar_looting_progress);
	}
	UpdateAllPlayerStaticInterface(position_view_player);
	UpdatePlayerSkillArrayPosition(position_view_player);
	DrawToScreenAllPlayerStaticInterface(window);
	player_in_game_stat_interface.DrawToScreen(window);
}

bool Player::IsStandingStill()
{
	return standing_still;
}

void Player::CheckPlayerStillInMap()
{
	if (player_spawned_after_death)
	{
		sf::Vector2f map_limit_maximum = ListObjectsSingleton::instance()->GetMapLimitSizeMaximum();
		sf::Vector2f map_limit_minimum = ListObjectsSingleton::instance()->GetMapLimitSizeMinimum();

		sf::Vector2f position_player = GetCurrentPosition();
		bool changed = false;

		if (position_player.x < map_limit_minimum.x)
		{
			changed = true;
			position_player.x = map_limit_minimum.x;
		}
		else if (position_player.x > map_limit_maximum.x)
		{
			changed = true;
			position_player.x = map_limit_maximum.x;
		}

		if (position_player.y < map_limit_minimum.y)
		{
			changed = true;
			position_player.y = map_limit_minimum.y;
		}
		else if (position_player.y > map_limit_maximum.y)
		{
			changed = true;
			position_player.y = map_limit_maximum.y;
		}

		player_image.setPosition(position_player);
		if (changed)
		{
			position_going_to = position_player;
		}
	}
}

void Player::CalculateMovement(float DELTATIME, sf::Vector2f mouse_position)
{
	if (player_characteristic_created)
	{
		if (!being_pushed)
		{
			bool standStill = true;
			bool up = false;
			bool down = false;
			bool left = false;
			bool right = false;

			sf::Vector2f current_speed_of_player{ speed_of_player,speed_of_player };
			float angle_going = 0;
			bool mouse_button_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
			bool sprinting = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
			bool keyboard_button_pressed = false;
			sf::Vector2f current_position = GetCurrentPosition();

			if (current_opened_interface == NoInterface_E)
			{
				if (!player_is_stunned && !is_looting)
				{
					if (mouse_button_pressed)
					{
						position_going_to = mouse_position;
						angle_going = GlobalFunction::GetRotationBetweenTwoPositions(mouse_position, current_position);
						standing_still = false;
						source_y = GlobalFunction::GetDirectionFromAngle(GlobalFunction::GetRotationBetweenTwoPositions(current_position, position_going_to));
					}
				}
			}

			if (!player_is_stunned && !is_looting)
			{
				is_sprinting = false;
				if (can_sprint && !ListDrawbackMages[2])
				{
					if (sprinting && sprint_points > 0)
					{
						is_sprinting = true;
						sprint_points -= rate_sprint_lost_second*DELTATIME;
						current_speed_of_player.x = current_speed_of_player.x * sprint_percent_bonus / 100;
						current_speed_of_player.y = current_speed_of_player.y * sprint_percent_bonus / 100;

						if (sprint_points <= 0)
						{
							sprint_points = 0;
							can_sprint = false;
							clock_breath_from_sprinting.restart();
							achievement_gestion.ActionInAchievement(A_OutOfSprint, 1);
						}
					}
					else
					{
						sprint_points += rate_sprint_gained_second*DELTATIME;
						if (sprint_points > sprint_max_points)
						{
							sprint_points = sprint_max_points;
						}
					}
				}
				else
				{
					if (clock_breath_from_sprinting.getElapsedTime().asSeconds() >= cooldown_sprinting)
					{
						can_sprint = true;
					}
				}

				if (!player_is_scared)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					{
						current_speed_of_player.x = -current_speed_of_player.x;
						left = true;
						source_y = Left;
						standStill = false;
						keyboard_button_pressed = true;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					{
						right = true;
						source_y = Right;
						standStill = false;
						keyboard_button_pressed = true;
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					{
						down = true;
						source_y = Down;
						standStill = false;
						keyboard_button_pressed = true;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						current_speed_of_player.y = -current_speed_of_player.y;
						up = true;
						source_y = Up;
						standStill = false;
						keyboard_button_pressed = true;
					}
				}
				else
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					{
						current_speed_of_player.x = -current_speed_of_player.x;
						left = true;
						source_y = Left;
						standStill = false;
						keyboard_button_pressed = true;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					{
						right = true;
						source_y = Right;
						standStill = false;
						keyboard_button_pressed = true;
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					{
						down = true;
						source_y = Down;
						standStill = false;
						keyboard_button_pressed = true;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					{
						current_speed_of_player.y = -current_speed_of_player.y;
						up = true;
						source_y = Up;
						standStill = false;
						keyboard_button_pressed = true;
					}
				}
			}

			if (current_opened_interface == MageSelectionInterface_E)
			{
				keyboard_button_pressed = false;
			}

			if (!keyboard_button_pressed)
			{
				angle_going = GlobalFunction::GetRotationBetweenTwoPositions(position_going_to, current_position);

				if (GlobalFunction::GetDistanceBetweenTwoPositions(position_going_to, current_position) <= 7)
				{
					current_speed_of_player.x = 0;
					current_speed_of_player.y = 0;
					source_y = Standing;
				}
				else
				{
					source_y = GlobalFunction::GetDirectionFromAngle(GlobalFunction::GetRotationBetweenTwoPositions(current_position, position_going_to));
					standing_still = false;
				}
			}
			else
			{
				current_opened_interface = NoInterface_E;

				angle_going = 0;

				if ((up && left) || (up && right) || (down && left) || (down && right))
				{
					angle_going = 45;
				}
				else if (right || left)
				{
					angle_going = 0;
				}
				else
				{
					angle_going = 90;
				}

				if (standStill)
				{
					source_y = Standing;
				}

				if (ListDrawbackMages[1])
				{
					if (GlobalFunction::getRandomRange(1, 1000) <= 5)
					{
						GivePlayerChangeStat(Scared, 0.2, 1);
					}
				}
			}

			velocity_player.x = (cos(angle_going * PI / 180))*current_speed_of_player.x;
			velocity_player.y = (sin(angle_going * PI / 180))*current_speed_of_player.y;
			player_image.setPosition(current_position + sf::Vector2f(velocity_player.x*DELTATIME, velocity_player.y*DELTATIME));
			if (keyboard_button_pressed)
			{
				position_going_to = player_image.getPosition();
			}

			if (ListDrawbackMages[7] && GlobalFunction::getRandomRange(1, 4000) <= 2)
			{
				sf::Vector2f player_position_now = player_image.getPosition();
				float random_angle = GlobalFunction::getRandomRange(1, 360);
				float random_distance = GlobalFunction::getRandomRange(200, 500);
				sf::Vector2f position_to_add_now = sf::Vector2f(-(cos(random_angle * PI / 180))*random_distance, -(sin(random_angle * PI / 180))*random_distance);
				player_image.setPosition(player_position_now + position_to_add_now);
				position_going_to = player_position_now + position_to_add_now;
			}

		}

		else
		{
			player_image.move(-(cos(push_rotation * PI / 180))*push_speed*DELTATIME*push_force, -(sin(push_rotation * PI / 180))*push_speed*DELTATIME*push_force);
			position_going_to = player_image.getPosition();
			if (GlobalFunction::GetDistanceBetweenTwoPositions(push_origin, GetCurrentPosition()) >= distance_being_pushed)
			{
				push_force = NoPush;
				distance_being_pushed = 0;
				being_pushed = false;
				push_rotation = 0;
			}
		}
	}

	CheckPlayerStillInMap();
}

sf::Vector2f Player::GetCurrentPosition()
{
	return player_image.getPosition();
}

void Player::CuttingSprite()
{
	if (source_y == Standing)
	{
		if (game_timer.getElapsedTime().asSeconds() >= 3 || !standing_still)
		{
			standing_still = false;
			if (game_timer.getElapsedTime().asSeconds() >= 0.15)
			{
				game_timer.restart();
				player_image.setTextureRect(sf::IntRect(player_image_size_x * source_x_standing, source_y * player_image_size_y, player_image_size_x, player_image_size_y));
				shadow.setTextureRect(sf::IntRect(player_image_size_x * source_x_standing, source_y * player_image_size_y, player_image_size_x, player_image_size_y));
				cutting_source.x = source_x_standing;
				cutting_source.y = source_y;
				source_x_standing++;
				if (source_x_standing >= 10)
				{
					source_x_standing = 0;
				}
			}
		}
		else if (game_timer.getElapsedTime().asSeconds() >= 2)
		{
			player_image.setTextureRect(sf::IntRect(0, source_y * player_image_size_y, player_image_size_x, player_image_size_y));
			shadow.setTextureRect(sf::IntRect(0, source_y * player_image_size_y, player_image_size_x, player_image_size_y));
		}
	}
	else if (game_timer.getElapsedTime().asSeconds() >= 0.1)
	{
		standing_still = true;
		source_x_standing = 0;
		game_timer.restart();
		player_image.setTextureRect(sf::IntRect(player_image_size_x * source_x, source_y * player_image_size_y, player_image_size_x, player_image_size_y));
		shadow.setTextureRect(sf::IntRect(player_image_size_x * source_x, source_y * player_image_size_y, player_image_size_x, player_image_size_y));
		cutting_source.x = source_x;
		cutting_source.y = source_y;
		source_x++;
		if (source_x >= 6)
		{
			source_x = 0;
		}
	}
}

void Player::player_health_maintenance()
{
	player_maximum_health_bar.setSize(sf::Vector2f(size_health_bar.x, size_health_bar.y));
	player_maximum_health_bar.setPosition(sf::Vector2f(player_image.getPosition().x, player_image.getPosition().y - player_image_size_y / 2 - 7));

	//sprite_health_bar_interface.setPosition(std::round(player_maximum_health_bar.getPosition().x), std::round(player_maximum_health_bar.getPosition().y));
	sprite_health_bar_interface.setPosition(player_maximum_health_bar.getPosition());

	float percent_health_bar = player_current_health / player_maximum_health;
	if (percent_health_bar > 100)
	{
		percent_health_bar = 100;
	}
	player_health_bar.setSize(sf::Vector2f(size_health_bar.x * percent_health_bar, size_health_bar.y));
	player_health_bar.setPosition(sf::Vector2f(player_image.getPosition().x, player_image.getPosition().y - player_image_size_y / 2 - 7));

	float percent_shield = player_current_shield / player_maximum_health;
	if (percent_shield > 100)
	{
		percent_shield = 100;
	}
	rect_shield_player_bar.setSize(sf::Vector2f(size_health_bar.x * percent_shield, size_health_bar.y));
	rect_shield_player_bar.setPosition(sf::Vector2f(player_image.getPosition().x, player_image.getPosition().y - player_image_size_y / 2 - 7));
}

void Player::SprintingMaintenance()
{
	rect_sprinting_bar.setPosition(GetCurrentPosition() + sf::Vector2f(0, player_image_size_y / 2 + size_sprinting_bar.y / 2 + 5));
	rect_sprinting_bar.setSize(sf::Vector2f(size_sprinting_bar.x * (sprint_points / sprint_max_points), size_sprinting_bar.y));
	sf::Vector2f current_size = rect_sprinting_bar.getSize();
	rect_sprinting_bar.setOrigin(current_size.x / 2, current_size.y / 2);
}

void Player::LifeGestion()
{
	if (player_current_health <= 0)
	{
		if (CheckIfPlayerHasSkill(ReviveEnum) && clock_skill_revive.getElapsedTime().asSeconds() >= listAllSkills[ReviveEnum]->GetPassiveBonusDuration(GetLevelSpecificSkill(ReviveEnum), current_class, player_skills_rune_array[ReviveEnum]))
		{
			ShieldObject(listAllSkills[ReviveEnum]->GetPassiveBonusValue(GetLevelSpecificSkill(ReviveEnum), current_class, player_skills_rune_array[ReviveEnum])* player_maximum_health / 100);
			HealPlayer(listAllSkills[ReviveEnum]->GetPassiveBonusValue(GetLevelSpecificSkill(ReviveEnum), current_class, player_skills_rune_array[ReviveEnum])* player_maximum_health / 100);
			if (player_skills_rune_array[ReviveEnum] == FirstRune_E)
			{
				HealPlayer(50*player_maximum_health / 100);
			}
			clock_skill_revive.restart();
		}
		else
		{
			achievement_gestion.PlayerDied();
			SaveInformations();
			current_opened_interface = MageSelectionInterface_E;
			player_image.setPosition(sf::Vector2f(-10000, -10000));
			position_going_to = sf::Vector2f(-10000, -10000);
			player_current_health = player_maximum_health;
			player_spawned_after_death = false;
			player_died = true;

			player_level = 0;
			player_experience = 0;
			GetExp(1);

			for (int i = 3; i < number_talent; i++)
			{
				player_array_talent_level[i] = 0;
				player_array_talent_increasement[i] = 0;
			}
			player_array_talent_points_used[0] = 0;
			player_array_talent_points_used[1] = 0;
			player_array_talent_points_used[2] = 0;
			player_array_talent_points_used[3] = 0;

			for (int i = 0; i < 9; i++)
			{
				player_skills_array[i] = -1;
			}

			ResetCurrentHat();
			ResetCurrentRing1();
			ResetCurrentRing2();
			ResetCurrentWeapon();
			ResetCurrentPet();
			listEquipment.clear();
			listPickableMaterial.clear();
			listAllActiveGems.clear();
			player_gem_array.clear();

			for (int i = 0; i < listRuneAvailable.size(); i++)
			{
				for (int ii = 0; ii < listRuneAvailable[i].size(); ii++)
				{
					listRuneAvailable[i][ii] = false;
				}
			}

			for (int i = 0; i < listScrollEquipped.size(); i++)
			{
				listScrollEquipped[i] = false;
			}

			for (int i = 0; i < player_skills_rune_array.size(); i++)
			{
				player_skills_rune_array[i] = NoRune_E;
			}

			for (int i = 0; i < player_skills_level_array.size(); i++)
			{
				player_skills_level_array[i] = 0;
				player_modified_skill_level_list[i] = 0;
				player_skill_increasement[i] = 0;
			}

			for (int i = 0; i < player_number_fragments.size(); i++)
			{
				player_number_fragments[i] = 0;
			}

			for (int i = 0; i < player_armor_array.size(); i++)
			{
				player_armor_array[i] = 0;
			}
			player_armor_array[0];
			number_current_armor = 0;

			TypeChange.clear();
			DurationChange.clear();
			ValueChange.clear();
			ClockChange.clear();
			ChangeEffect.clear();

			FeatGestion::instance()->UpdateUponDeath();
			listFeatBonus = FeatGestion::instance()->GetListFeatBonus();

			SaveInformations();
		}
	}

	if (!player_spawned_after_death && current_opened_interface != MageSelectionInterface_E)
	{
		player_spawned_after_death = true;
	}
}

float Player::GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent)
{
	if (!player_is_immune)
	{
		if (damage_dealt > 0)
		{
			achievement_gestion.PlayerTookDamage();
			StopLooting();
			PlayerDidCombatAction();

			damage_dealt -=  damage_dealt*player_damage_reduction / 100;
	
			float armor_on_shield = player_defense*(player_defense*armor_on_shield_percent / 100)*(1 - armor_penetration_percent / 100);
			float modifier_armor_shield = GlobalFunction::GetArmorReductionModifier(armor_on_shield);

			float damage_on_shield = 0;
			float damage_on_player = damage_dealt;

			if (player_current_shield > 0)
			{
				damage_on_shield = damage_dealt*0.85;
				damage_on_player = damage_dealt*0.15;
			}

			if (player_current_shield > 0)
			{
				damage_on_shield = damage_on_shield*modifier_armor_shield;
				if (damage_on_shield > 0)
				{
					float damage_done_to_shield = 0;
					if (damage_on_shield > player_current_shield)
					{
						damage_done_to_shield = player_current_shield;
						player_current_shield = 0;
						float damage_to_add_to_player = (damage_on_shield - damage_done_to_shield) / modifier_armor_shield;
						damage_on_player += damage_to_add_to_player;
					}
					else
					{
						damage_done_to_shield = damage_on_shield;
						player_current_shield -= damage_on_shield;
					}

					sf::String str = "-";
					str = GlobalFunction::InsertNumberToString(str, damage_done_to_shield, str.getSize());
					TextGenerator::instance()->GenerateOneTextStringAndColor(GetCurrentPosition(), str, GetSize(), sf::Color::Color(128, 128, 128), shared_from_this());
				}
			}

			if (damage_on_player > 0)
			{
				float modifier_armor_player = GlobalFunction::GetArmorReductionModifier(player_defense*(1 - armor_penetration_percent / 100));
				damage_on_player = damage_on_player*modifier_armor_player;
				player_current_health -= damage_on_player;
				damage_received_liquid_body += damage_on_player;
				sf::String str = "-";
				str = GlobalFunction::InsertNumberToString(str, damage_on_player, str.getSize());
				TextGenerator::instance()->GenerateOneTextStringAndColor(GetCurrentPosition(), str, GetSize(), sf::Color::Red, shared_from_this());
				SoundGestion::instance()->AddSound("SoundPlayerHit.wav", 85, false);

				if (cant_die_status)
				{
					if (player_current_health < 1)
					{
						player_current_health == 1;
					}
				}

				return damage_dealt;
			}
		}
	}
	return 0;
}

sf::Vector2f Player::GetSize()
{
	sf::Vector2f size(player_image_size_x, player_image_size_y);
	return size;
}

int Player::GetRayon()
{
	return rayon;
}

float Player::GetDamage()
{
	return player_damage_modified;
}

int Player::GetExp(int exp_received)
{
	if (exp_received > 0)
	{
		player_experience = player_experience + exp_received;
		sf::Vector2f player_level_exp = GlobalFunction::GetPlayerlevel(player_experience, player_level);
		player_level = player_level_exp.x;
		player_experience = player_level_exp.y;
		UpdatePlayerStats();
		return exp_received;
	}
	return exp_received;
}

float Player::GetHealth()
{
	return player_current_health;
}

int Player::GetMaximumHealth()
{
	return player_maximum_health;
}

void Player::UpdatePlayerStats()
{
	if (current_hat != NULL)
	{
		player_maximum_health_initial = 1500 + (player_level - 1) * ((current_hat->GetBonusValue(HealthPerLevel) / 100)* 550 + 550);
		player_damage = 120 + (player_level - 1) * ((current_hat->GetBonusValue(DamagePerLevel) / 100)*35 + 35);
		player_defense_initial = 30 + (player_level - 1) * ((current_hat->GetBonusValue(ArmorPerLevel)/100)*4 + 4);
		speed_of_player_initial = 275 + (player_level - 1) *((current_hat->GetBonusValue(SpeedPerLevel) / 100)*5);
		player_cooldown_reduction_initial = (player_level - 1) *((current_hat->GetBonusValue(CooldownRedutionPerLevel) / 100)*1);
		player_max_attack_speed = 1.5 + (player_level - 1) *((current_hat->GetBonusValue(AttackSpeedPerLevel) / 100)*0.015);
	}
	else
	{
		player_maximum_health_initial = 1500 + ((player_level - 1) * 550);
		player_damage = 120 + ((player_level - 1) * 35);
		player_defense_initial = 30 + ((player_level - 1) * 4);
		player_max_attack_speed = 1.5;
		player_cooldown_reduction_initial = 0;
		speed_of_player_initial = 275 + ((player_level - 1)* 5);
	}
}

void Player::UsingSkill(SkillManagement &skill_management, sf::Vector2f mouse_position)
{
	if (player_characteristic_created)
	{
		for (size_t number = 0; number < 9; number++)
		{
			if (player_skill_clock[number].getElapsedTime().asSeconds() >= player_skill_cooldown[number] && !player_skill_ready[number])
			{
				player_skill_ready[number] = true;
				player_skill_clock[number].restart();
				skill_cooldown_changed[number] = false;
			}
		}

		if (!player_is_stunned && !is_looting)
		{
			sf::Vector2f current_position = GetCurrentPosition();
			float range_modifier = GetProjectileRangeBonus() / 100 + 1;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && player_skill_ready[FirstSkill] && !(player_skills_array[FirstSkill] == -1) && listAllSkills[player_skills_array[FirstSkill]]->GetTypeSkill() != PassiveSkill_E && !skill_is_canceled[FirstSkill])
			{
				can_cast_skill[FirstSkill] = true;
				skill_management.DrawSkillHitBox(mouse_position, GetLevelSpecificSkill(player_skills_array[FirstSkill]), current_position, player_skills_array[FirstSkill], current_class, range_modifier, player_skills_rune_array[player_skills_array[FirstSkill]]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && player_skill_ready[SecondSkill] && !(player_skills_array[SecondSkill] == -1) && listAllSkills[player_skills_array[SecondSkill]]->GetTypeSkill() != PassiveSkill_E && !skill_is_canceled[SecondSkill])
			{
				can_cast_skill[SecondSkill] = true;
				skill_management.DrawSkillHitBox(mouse_position, GetLevelSpecificSkill(player_skills_array[SecondSkill]), current_position, player_skills_array[SecondSkill], current_class, range_modifier, player_skills_rune_array[player_skills_array[SecondSkill]]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && player_skill_ready[ThirdSkill] && !(player_skills_array[ThirdSkill] == -1) && listAllSkills[player_skills_array[ThirdSkill]]->GetTypeSkill() != PassiveSkill_E && !skill_is_canceled[ThirdSkill])
			{
				can_cast_skill[ThirdSkill] = true;
				skill_management.DrawSkillHitBox(mouse_position, GetLevelSpecificSkill(player_skills_array[ThirdSkill]), current_position, player_skills_array[ThirdSkill], current_class, range_modifier, player_skills_rune_array[player_skills_array[ThirdSkill]]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && player_skill_ready[FourthSkill] && !(player_skills_array[FourthSkill] == -1) && listAllSkills[player_skills_array[FourthSkill]]->GetTypeSkill() != PassiveSkill_E && !skill_is_canceled[FourthSkill])
			{
				can_cast_skill[FourthSkill] = true;
				skill_management.DrawSkillHitBox(mouse_position, GetLevelSpecificSkill(player_skills_array[FourthSkill]), current_position, player_skills_array[FourthSkill], current_class, range_modifier, player_skills_rune_array[player_skills_array[FourthSkill]]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && player_skill_ready[FifthSkill] && !(player_skills_array[FifthSkill] == -1) && listAllSkills[player_skills_array[FifthSkill]]->GetTypeSkill() != PassiveSkill_E && !skill_is_canceled[FifthSkill])
			{
				can_cast_skill[FifthSkill] = true;
				skill_management.DrawSkillHitBox(mouse_position, GetLevelSpecificSkill(player_skills_array[FifthSkill]), current_position, player_skills_array[FifthSkill], current_class, range_modifier, player_skills_rune_array[player_skills_array[FifthSkill]]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && player_skill_ready[SixthSkill] && !(player_skills_array[SixthSkill] == -1) && listAllSkills[player_skills_array[SixthSkill]]->GetTypeSkill() != PassiveSkill_E && !skill_is_canceled[SixthSkill])
			{
				can_cast_skill[SixthSkill] = true;
				skill_management.DrawSkillHitBox(mouse_position, GetLevelSpecificSkill(player_skills_array[SixthSkill]), current_position, player_skills_array[SixthSkill], current_class, range_modifier, player_skills_rune_array[player_skills_array[SixthSkill]]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) && player_skill_ready[SeventhSkill] && !(player_skills_array[SeventhSkill] == -1) && listAllSkills[player_skills_array[SeventhSkill]]->GetTypeSkill() != PassiveSkill_E && !skill_is_canceled[SeventhSkill])
			{
				can_cast_skill[SeventhSkill] = true;
				skill_management.DrawSkillHitBox(mouse_position, GetLevelSpecificSkill(player_skills_array[SeventhSkill]), current_position, player_skills_array[SeventhSkill], current_class, range_modifier, player_skills_rune_array[player_skills_array[SeventhSkill]]);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && player_skill_ready[EighthSkill] && !(player_skills_array[EighthSkill] == -1) && listAllSkills[player_skills_array[EighthSkill]]->GetTypeSkill() != PassiveSkill_E && !skill_is_canceled[EighthSkill])
			{
				can_cast_skill[EighthSkill] = true;
				skill_management.DrawSkillHitBox(mouse_position, GetLevelSpecificSkill(player_skills_array[EighthSkill]), current_position, player_skills_array[EighthSkill], current_class, range_modifier, player_skills_rune_array[player_skills_array[EighthSkill]]);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) && player_skill_ready[NinethSkill] && !(player_skills_array[NinethSkill] == -1) && listAllSkills[player_skills_array[NinethSkill]]->GetTypeSkill() != PassiveSkill_E && !skill_is_canceled[NinethSkill])
			{
				can_cast_skill[NinethSkill] = true;
				skill_management.DrawSkillHitBox(mouse_position, GetLevelSpecificSkill(player_skills_array[NinethSkill]), current_position, player_skills_array[NinethSkill], current_class, range_modifier, player_skills_rune_array[player_skills_array[NinethSkill]]);
			}
		}
		else
		{
			for (int i = 0; i < 9; i++)
			{
				can_cast_skill[i] = false;
			}
		}

		for (int i = 0; i < 9; i++)
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				if (can_cast_skill[FirstSkill])
				{
					if (ListDrawbackMages[9])
					{
						if (GlobalFunction::getRandomRange(1, 1000) >= 200)
						{
							player_number_skills_casted++;
							skill_management.InitSkill(player_id, player_skills_array[FirstSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[FirstSkill]), player_skills_rune_array[player_skills_array[FirstSkill]]);
							player_skill_ready[FirstSkill] = false;
							player_skill_clock[FirstSkill].restart();
							SkillUsed(FirstSkill);
							ChangeStunTime(stun_from_normal_casting);
						}
					}
					else
					{
						player_number_skills_casted++;
						skill_management.InitSkill(player_id, player_skills_array[FirstSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[FirstSkill]), player_skills_rune_array[player_skills_array[FirstSkill]]);
						player_skill_ready[FirstSkill] = false;
						player_skill_clock[FirstSkill].restart();
						SkillUsed(FirstSkill);
						ChangeStunTime(stun_from_normal_casting);
					}
					can_cast_skill[FirstSkill] = false;
				}
				if (skill_is_canceled[FirstSkill])
				{
					skill_is_canceled[FirstSkill] = false;
				}
			}

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				if (can_cast_skill[SecondSkill])
				{
					if (ListDrawbackMages[9])
					{
						if (GlobalFunction::getRandomRange(1, 1000) >= 200)
						{
							player_number_skills_casted++;
							skill_management.InitSkill(player_id, player_skills_array[SecondSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[SecondSkill]), player_skills_rune_array[player_skills_array[SecondSkill]]);
							player_skill_ready[SecondSkill] = false;
							player_skill_clock[SecondSkill].restart();
							SkillUsed(SecondSkill);
							ChangeStunTime(stun_from_normal_casting);
						}
					}
					else
					{
						player_number_skills_casted++;
						skill_management.InitSkill(player_id, player_skills_array[SecondSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[SecondSkill]), player_skills_rune_array[player_skills_array[SecondSkill]]);
						player_skill_ready[SecondSkill] = false;
						player_skill_clock[SecondSkill].restart();
						SkillUsed(SecondSkill);
						ChangeStunTime(stun_from_normal_casting);
					}
					can_cast_skill[SecondSkill] = false;
				}
				if (skill_is_canceled[SecondSkill])
				{
					skill_is_canceled[SecondSkill] = false;
				}
			}

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				if (can_cast_skill[ThirdSkill])
				{
					if (ListDrawbackMages[9])
					{
						if (GlobalFunction::getRandomRange(1, 1000) >= 200)
						{
							player_number_skills_casted++;
							skill_management.InitSkill(player_id, player_skills_array[ThirdSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[ThirdSkill]), player_skills_rune_array[player_skills_array[ThirdSkill]]);
							player_skill_ready[ThirdSkill] = false;
							player_skill_clock[ThirdSkill].restart();
							SkillUsed(ThirdSkill);
							ChangeStunTime(stun_from_normal_casting);
						}
					}
					else
					{
						player_number_skills_casted++;
						skill_management.InitSkill(player_id, player_skills_array[ThirdSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[ThirdSkill]), player_skills_rune_array[player_skills_array[ThirdSkill]]);
						player_skill_ready[ThirdSkill] = false;
						player_skill_clock[ThirdSkill].restart();
						SkillUsed(ThirdSkill);
						ChangeStunTime(stun_from_normal_casting);
					}
					can_cast_skill[ThirdSkill] = false;
				}
				if (skill_is_canceled[ThirdSkill])
				{
					skill_is_canceled[ThirdSkill] = false;
				}
			}

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			{
				if (can_cast_skill[FourthSkill])
				{
					if (ListDrawbackMages[9])
					{
						if (GlobalFunction::getRandomRange(1, 1000) >= 200)
						{
							player_number_skills_casted++;
							skill_management.InitSkill(player_id, player_skills_array[FourthSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[FourthSkill]), player_skills_rune_array[player_skills_array[FourthSkill]]);
							player_skill_ready[FourthSkill] = false;
							player_skill_clock[FourthSkill].restart();
							SkillUsed(FourthSkill);
							ChangeStunTime(stun_from_normal_casting);
						}
					}
					else
					{
						player_number_skills_casted++;
						skill_management.InitSkill(player_id, player_skills_array[FourthSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[FourthSkill]), player_skills_rune_array[player_skills_array[FourthSkill]]);
						player_skill_ready[FourthSkill] = false;
						player_skill_clock[FourthSkill].restart();
						SkillUsed(FourthSkill);
						ChangeStunTime(stun_from_normal_casting);
					}
					can_cast_skill[FourthSkill] = false;
				}
				if (skill_is_canceled[FourthSkill])
				{
					skill_is_canceled[FourthSkill] = false;
				}
			}

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			{
				if (can_cast_skill[FifthSkill])
				{
					if (ListDrawbackMages[9])
					{
						if (GlobalFunction::getRandomRange(1, 1000) >= 200)
						{
							player_number_skills_casted++;
							skill_management.InitSkill(player_id, player_skills_array[FifthSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[FifthSkill]), player_skills_rune_array[player_skills_array[FifthSkill]]);
							player_skill_ready[FifthSkill] = false;
							player_skill_clock[FifthSkill].restart();
							SkillUsed(FifthSkill);
							ChangeStunTime(stun_from_normal_casting);
						}
					}
					else
					{
						player_number_skills_casted++;
						skill_management.InitSkill(player_id, player_skills_array[FifthSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[FifthSkill]), player_skills_rune_array[player_skills_array[FifthSkill]]);
						player_skill_ready[FifthSkill] = false;
						player_skill_clock[FifthSkill].restart();
						SkillUsed(FifthSkill);
						ChangeStunTime(stun_from_normal_casting);
					}
					can_cast_skill[FifthSkill] = false;
				}
				if (skill_is_canceled[FifthSkill])
				{
					skill_is_canceled[FifthSkill] = false;
				}
			}

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
			{
				if (can_cast_skill[SixthSkill])
				{
					if (ListDrawbackMages[9])
					{
						if (GlobalFunction::getRandomRange(1, 1000) >= 200)
						{
							player_number_skills_casted++;
							skill_management.InitSkill(player_id, player_skills_array[SixthSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[SixthSkill]), player_skills_rune_array[player_skills_array[SixthSkill]]);
							player_skill_ready[SixthSkill] = false;
							player_skill_clock[SixthSkill].restart();
							SkillUsed(SixthSkill);
							ChangeStunTime(stun_from_normal_casting);
						}
					}
					else
					{
						player_number_skills_casted++;
						skill_management.InitSkill(player_id, player_skills_array[SixthSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[SixthSkill]), player_skills_rune_array[player_skills_array[SixthSkill]]);
						player_skill_ready[SixthSkill] = false;
						player_skill_clock[SixthSkill].restart();
						SkillUsed(SixthSkill);
						ChangeStunTime(stun_from_normal_casting);
					}
					can_cast_skill[SixthSkill] = false;
				}
				if (skill_is_canceled[SixthSkill])
				{
					skill_is_canceled[SixthSkill] = false;
				}
			}

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
			{
				if (can_cast_skill[SeventhSkill])
				{
					if (ListDrawbackMages[9])
					{
						if (GlobalFunction::getRandomRange(1, 1000) >= 200)
						{
							player_number_skills_casted++;
							skill_management.InitSkill(player_id, player_skills_array[SeventhSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[SeventhSkill]), player_skills_rune_array[player_skills_array[SeventhSkill]]);
							player_skill_ready[SeventhSkill] = false;
							player_skill_clock[SeventhSkill].restart();
							SkillUsed(SeventhSkill);
							ChangeStunTime(stun_from_normal_casting);
						}
					}
					else
					{
						player_number_skills_casted++;
						skill_management.InitSkill(player_id, player_skills_array[SeventhSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[SeventhSkill]), player_skills_rune_array[player_skills_array[SeventhSkill]]);
						player_skill_ready[SeventhSkill] = false;
						player_skill_clock[SeventhSkill].restart();
						SkillUsed(SeventhSkill);
						ChangeStunTime(stun_from_normal_casting);
					}
					can_cast_skill[SeventhSkill] = false;
				}
				if (skill_is_canceled[SeventhSkill])
				{
					skill_is_canceled[SeventhSkill] = false;
				}
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
			{
				if (can_cast_skill[EighthSkill])
				{
					if (ListDrawbackMages[9])
					{
						if (GlobalFunction::getRandomRange(1, 1000) >= 200)
						{
							player_number_skills_casted++;
							skill_management.InitSkill(player_id, player_skills_array[EighthSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[EighthSkill]), player_skills_rune_array[player_skills_array[EighthSkill]]);
							player_skill_ready[EighthSkill] = false;
							player_skill_clock[EighthSkill].restart();
							SkillUsed(EighthSkill);
							ChangeStunTime(stun_from_normal_casting);
						}
					}
					else
					{
						player_number_skills_casted++;
						skill_management.InitSkill(player_id, player_skills_array[EighthSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[EighthSkill]), player_skills_rune_array[player_skills_array[EighthSkill]]);
						player_skill_ready[EighthSkill] = false;
						player_skill_clock[EighthSkill].restart();
						SkillUsed(EighthSkill);
						ChangeStunTime(stun_from_normal_casting);
					}
					can_cast_skill[EighthSkill] = false;
				}
				if (skill_is_canceled[EighthSkill])
				{
					skill_is_canceled[EighthSkill] = false;
				}
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
			{
				if (can_cast_skill[NinethSkill])
				{
					if (ListDrawbackMages[9])
					{
						if (GlobalFunction::getRandomRange(1, 1000) >= 200)
						{
							player_number_skills_casted++;
							skill_management.InitSkill(player_id, player_skills_array[NinethSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[NinethSkill]), player_skills_rune_array[player_skills_array[NinethSkill]]);
							player_skill_ready[NinethSkill] = false;
							player_skill_clock[NinethSkill].restart();
							SkillUsed(NinethSkill);
							ChangeStunTime(stun_from_normal_casting);
						}
					}
					else
					{
						player_number_skills_casted++;
						skill_management.InitSkill(player_id, player_skills_array[NinethSkill], GetCurrentPosition(), player_damage_modified, mouse_position, shared_from_this(), GetLevelSpecificSkill(player_skills_array[NinethSkill]), player_skills_rune_array[player_skills_array[NinethSkill]]);
						player_skill_ready[NinethSkill] = false;
						player_skill_clock[NinethSkill].restart();
						SkillUsed(NinethSkill);
						ChangeStunTime(stun_from_normal_casting);
					}
					can_cast_skill[NinethSkill] = false;
				}
				if (skill_is_canceled[NinethSkill])
				{
					skill_is_canceled[NinethSkill] = false;
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			for (int i = 0; i < 9; i++)
			{
				can_cast_skill[i] = false;
				skill_is_canceled[i] = true;
			}
		}
	}
}

void Player::UpdateSkillCooldown()
{
	for (int number = 0; number < maximum_skills; number++)
	{
		if (player_skills_array[number] != -1 && !skill_cooldown_changed[number])
		{
			float skill_cooldown = listAllSkills[player_skills_array[number]]->GetSkillCooldown(GetLevelSpecificSkill( player_skills_array[number]), current_class);
			skill_cooldown = skill_cooldown - skill_cooldown*player_cooldown_reduction_percent / 100 - player_cooldown_reduction;
			if (skill_cooldown <= 0)
			{
				skill_cooldown = 0.5;
			}
			player_skill_cooldown[number] = skill_cooldown;
			array_skill_cooldown[number] = skill_cooldown;
		}
	}
}

int Player::GetId()
{
	return player_id;
}

float Player::GetAttackSpeed()
{
	return player_current_attack_speed;
}

void Player::SkillUsed(int skill_slot)
{
	skill_cooldown_rectangle_created[skill_slot] = true;
	skill_cooldown_clock[skill_slot].restart();
}

#pragma region StaticInterface
void Player::InitAllPlayerStaticInterface(sf::Vector2f position_view_player)
{
	InitPlayerHealthInterface();
	InitPlayerExperienceInterface();

	for (int number = 0; number < maximum_skills; number++)
	{
		array_position_sprite_skill_icone[number] = sf::Vector2f(position_initial_sprite_skill_icone.x + size_rect_skill_slot.x * 2 * holder_position_sprite_skill_icone, position_initial_sprite_skill_icone.y);
		holder_position_sprite_skill_icone++;

		rect_skill_slot[number] = GlobalFunction::CreateSprite(array_position_sprite_skill_icone[number], size_sprite_skillbase_icone, skillbase_icone_texture);

		if (!(player_skills_array[number] == -1))
		{
			texture_player_skill_icone[number] = listAllSkills[player_skills_array[number]]->ReturnSkillIconeTexture();
			sprite_skill_icone[number] = GlobalFunction::CreateSprite(array_position_sprite_skill_icone[number], size_icone, texture_player_skill_icone[number]);
		}
		else
		{
			sprite_skill_icone[number] = GlobalFunction::CreateSprite(array_position_sprite_skill_icone[number], size_icone, basic_skill_icone_texture);
		}
		skill_cooldown_rectangle[number] = GlobalFunction::CreateRectangleWithOrigin(size_skill_cooldown_rectangle_max, array_position_sprite_skill_icone[number], sf::Color::Black);
		skill_cooldown_rectangle[number].setFillColor(sf::Color::Color(0, 0, 0, 100));
	}

	rect_health_potion_cooldown = GlobalFunction::CreateRectangleWithOrigin(size_skill_cooldown_rectangle_max, position_health_potion, sf::Color::Black);
	rect_health_potion_cooldown.setFillColor(sf::Color::Color(0, 0, 0, 100));
	sprite_health_potion = GlobalFunction::CreateSprite(position_health_potion, size_sprite_skillbase_icone, texture_health_potion);
	text_number_health_potion = GlobalFunction::CreateText(position_health_potion, "0", font, 18);
	text_number_health_potion.setFillColor(sf::Color::Color(54, 46, 39));
	rect_blinded = GlobalFunction::CreateRectangleWithOrigin(sf::Vector2f(10, 10), sf::Vector2f(0, 0), sf::Color::Color(0,0,0,150));
}

void Player::InitPlayerHealthInterface()
{
	string_text_player_health = GlobalFunction::InsertNumberToString(string_text_player_health, player_current_health, string_text_player_health.getSize());
	text_player_health = GlobalFunction::CreateText(position_text_player_health, string_text_player_health, font, character_size_text_player_health);
	sf::Vector2f text_position = text_player_health.getPosition();
	basic_big_player_health = GlobalFunction::CreateSpriteWithoutOrigin(text_position, size_rect_player_health, texture_basic_big_player_health);
	basic_big_player_health.setOrigin(0, size_rect_player_health.y / 2);
	big_player_health = GlobalFunction::CreateSpriteWithoutOrigin(text_position,size_rect_player_health, texture_big_player_health);
	big_player_health.setOrigin(0, size_rect_player_health.y / 2);
}

void Player::InitPlayerExperienceInterface()
{
	rect_player_experience = GlobalFunction::CreateSprite(position_player_experience_bar, size_rect_player_experience, texture_player_experience_bar);
	string_text_player_experience = GlobalFunction::InsertNumberToString(string_text_player_experience, player_level, string_text_player_experience.getSize());
	string_text_player_experience.insert(string_text_player_experience.getSize(), ":   ");
	string_text_player_experience = GlobalFunction::InsertNumberToString(string_text_player_experience, player_experience, string_text_player_experience.getSize());
	string_text_player_experience.insert(string_text_player_experience.getSize(), " / ");
	string_text_player_experience = GlobalFunction::InsertNumberToString(string_text_player_experience, GlobalFunction::GetPlayerExperienceNeeded(player_level), string_text_player_experience.getSize());
	text_player_experience = GlobalFunction::CreateText(rect_player_experience.getPosition(), string_text_player_experience, font, character_size_text_player_health);
}

void Player::UpdatePlayerSkillArrayPosition(sf::Vector2f position_view_player)
{
	for (int number = 0; number < maximum_skills; number++)
	{
		if (!(player_skills_array[number] == -1))
		{
			if (!skill_cooldown_changed[number])
			{
				texture_player_skill_icone[number] = listAllSkills[player_skills_array[number]]->ReturnSkillIconeTexture();
				sprite_skill_icone[number].setTexture(texture_player_skill_icone[number]);
			}
			skill_cooldown_rectangle[number].setFillColor(sf::Color::Color(0, 0, 0, 100));
		}
		else
		{
			texture_player_skill_icone[number] = basic_skill_icone_texture;
			sprite_skill_icone[number].setTexture(texture_player_skill_icone[number]);
		}

		if (skill_cooldown_rectangle_created[number])
		{
			if (skill_cooldown_clock[number].getElapsedTime().asSeconds() >= array_skill_cooldown[number])
			{
				skill_cooldown_rectangle_created[number] = false;
				//skill_cooldown_rectangle[number].setSize(size_skill_cooldown_rectangle_max);
				skill_cooldown_clock[number].restart();
			}
			skill_cooldown_rectangle[number].setSize(sf::Vector2f(size_skill_cooldown_rectangle_max.x, (1 - (skill_cooldown_clock[number].getElapsedTime().asSeconds() / array_skill_cooldown[number])) * size_skill_cooldown_rectangle_max.y));
		}

		rect_skill_slot[number].setPosition(position_view_player + array_position_sprite_skill_icone[number]);
		sprite_skill_icone[number].setPosition(position_view_player + array_position_sprite_skill_icone[number] - sf::Vector2f(2, 2));
		skill_cooldown_rectangle[number].setPosition(position_view_player + array_position_sprite_skill_icone[number]);
	}
}

void Player::UpdateAllPlayerStaticInterface(sf::Vector2f position_view_player)
{
	UpdateStaticInterfaceAccordingToResolution();
	UpdatePlayerHealthInterface(position_view_player);
	UpdatePlayerExperienceInterface(position_view_player);

	sprite_health_potion.setPosition(position_view_player + position_health_potion);
	int number_health_potion = inventory[I_Miscellaneous][ IM_HealthPotion];
	string_number_health_potion.clear();
	string_number_health_potion = "";
	string_number_health_potion = GlobalFunction::InsertNumberToString(string_number_health_potion, number_health_potion, string_number_health_potion.getSize());
	text_number_health_potion.setString(string_number_health_potion);
	text_number_health_potion.setPosition(position_view_player + position_number_health_potion);

	rect_health_potion_cooldown.setSize(sf::Vector2f(size_skill_cooldown_rectangle_max.x, (1 - (clock_cooldown_health_potion.getElapsedTime().asSeconds() / health_potion_cooldown)) * size_skill_cooldown_rectangle_max.y));
	rect_health_potion_cooldown.setPosition(position_view_player + position_health_potion);
}

void Player::UpdatePlayerHealthInterface(sf::Vector2f position_view_player)
{
	string_text_player_health = "Hp: ";
	string_text_player_health = GlobalFunction::InsertNumberToString(string_text_player_health, player_current_health, string_text_player_health.getSize());
	text_player_health = GlobalFunction::CreateText(position_text_player_health, string_text_player_health, font, character_size_text_player_health);
	text_player_health.setPosition(sf::Vector2f(position_text_player_health.x + position_view_player.x, position_text_player_health.y + position_view_player.y));
	basic_big_player_health.setPosition(position_big_health_bar + position_view_player - sf::Vector2f(size_rect_player_health.x / 2, 0));
	big_player_health.setPosition(position_big_health_bar + position_view_player - sf::Vector2f(size_rect_player_health.x/2,0));

	if (clock_animation_big_health_bar.getElapsedTime().asSeconds() >= 0.075)
	{
		float percent_health_bar = player_current_health / player_maximum_health;
		if (percent_health_bar > 100)
		{
			percent_health_bar = 100;
		}
		big_player_health.setTextureRect(sf::IntRect(0, size_rect_player_health.y*counter_big_health_bar, size_rect_player_health.x * percent_health_bar, size_rect_player_health.y));
		counter_big_health_bar++;
		if (counter_big_health_bar == number_big_health_bar_animations)
		{
			counter_big_health_bar = 0;
		}
		clock_animation_big_health_bar.restart();
	}
}

void Player::UpdateStaticInterfaceAccordingToResolution()
{
	sf::Vector2f window_size = ListObjectsSingleton::instance()->GetSizeWindow();
	position_bar_looting.x = window_size.x / 2;
	position_bar_looting.y = window_size.y - 200;
	position_health_potion.x = window_size.x - 200;
	position_health_potion.y = window_size.y - 100;
	position_initial_sprite_skill_icone.y = window_size.y - 100;
	position_text_player_experience.x = window_size.x/2;
	position_text_player_experience.y = window_size.y - 35;
	position_player_experience_bar.x = window_size.x/2;
	position_player_experience_bar.y = window_size.y - 30;
	position_number_health_potion.y = window_size.x - 188;
	position_number_health_potion.y = window_size.y - 88;

	rect_blinded.setSize(sf::Vector2f(window_size.x*5,window_size.y * 5));
	rect_blinded.setOrigin(window_size.x*5 / 2, window_size.y*5 / 2);
	rect_blinded.setPosition(GetCurrentPosition());

	holder_position_sprite_skill_icone = 0;
	for (int number = 0; number < maximum_skills; number++)
	{
		array_position_sprite_skill_icone[number] = sf::Vector2f(position_initial_sprite_skill_icone.x + size_rect_skill_slot.x * 2 * holder_position_sprite_skill_icone, position_initial_sprite_skill_icone.y);
		holder_position_sprite_skill_icone++;
	}
}

void Player::UpdatePlayerExperienceInterface(sf::Vector2f position_view_player)
{
	string_text_player_experience = "Level ";
	string_text_player_experience = GlobalFunction::InsertNumberToString(string_text_player_experience, player_level, string_text_player_experience.getSize());
	string_text_player_experience.insert(string_text_player_experience.getSize(), ":   ");
	string_text_player_experience = GlobalFunction::InsertNumberToString(string_text_player_experience, player_experience, string_text_player_experience.getSize());
	string_text_player_experience.insert(string_text_player_experience.getSize(), " / ");
	string_text_player_experience = GlobalFunction::InsertNumberToString(string_text_player_experience, GlobalFunction::GetPlayerExperienceNeeded(player_level), string_text_player_experience.getSize());
	text_player_experience.setString(string_text_player_experience);

	rect_player_experience.setPosition(position_player_experience_bar + position_view_player);
	text_player_experience.setPosition(position_text_player_experience + position_view_player);

	/*if (clock_animation_experience_bar.getElapsedTime().asSeconds() >= 0.075)
	{
		rect_player_experience.setTextureRect(sf::IntRect(0, size_rect_player_experience.y*counter_experience_bar, size_rect_player_experience.x, size_rect_player_experience.y));
		counter_experience_bar++;
		if (counter_experience_bar == number_big_health_bar_animations)
		{
			counter_experience_bar = 0;
		}
		clock_animation_experience_bar.restart();
	}*/
}

void Player::DrawToScreenAllPlayerStaticInterface(sf::RenderWindow &window)
{	
	if (ListDrawbackMages[5])
	{
		window.draw(rect_blinded);
	}
	if (!ListDrawbackMages[8])
	{
		window.draw(basic_big_player_health);
		window.draw(big_player_health);
		window.draw(text_player_health);
		window.draw(rect_player_experience);
		window.draw(text_player_experience);
		if (sprint_points < sprint_max_points)
		{
			window.draw(rect_sprinting_bar);
		}

		for (size_t i = 0; i < listAllArmors[number_current_armor]->ReturnArmorNumberSkills(); i++)
		{
			window.draw(rect_skill_slot[i]);
			if (player_skills_array[i] != -1)
			{
				window.draw(sprite_skill_icone[i]);
			}
			if (skill_cooldown_rectangle_created[i])
			{
				window.draw(skill_cooldown_rectangle[i]);
			}
		}
		window.draw(sprite_health_potion);
		window.draw(text_number_health_potion);
		if (!can_use_health_potion)
		{
			window.draw(rect_health_potion_cooldown);
		}

		player_icone_bonus.Draw(window, GetCurrentPosition());
	}
}
#pragma endregion StaticInterface

#pragma region AllArrayInformation
void Player::NewPlayerSkillArray(std::vector<int> player_skills_array_received)
{
	player_skills_array = player_skills_array_received;
}

void Player::NewPlayerNumberFragments(std::vector<int> player_number_fragments_received)
{
	player_number_fragments = player_number_fragments_received;
}

std::vector<int> Player::GetPlayerSkillArray()
{
	return player_skills_array;
}

void Player::NewPlayerActiveGemArray(std::vector<int> listAllActiveGemsRecevied)
{
	listAllActiveGems = listAllActiveGemsRecevied;
}

void Player::NewPlayerSkillLevel(std::vector<int> player_skill_level_received)
{
	player_skills_level_array = player_skill_level_received;
}

std::vector<int> Player::GetPlayerSkillLevelArray()
{
	return player_skills_level_array;
}

std::vector<int> Player::GetPlayerNumberFragments()
{
	return player_number_fragments;
}

void Player::GivePlayerFragments(int type_fragment, int number_fragments)
{
	if (number_fragments > 0)
	{
		player_number_fragments[type_fragment] = player_number_fragments[type_fragment] + number_fragments;
	}
}

void Player::NewPlayerCurrentArmor(int number_armor)
{
	number_current_armor = number_armor;
}

int Player::GetPlayerCurrentArmor()
{
	return number_current_armor;
}

void Player::NewPlayerArmorArray(std::vector<int> player_armor_array_received)
{
	player_armor_array = player_armor_array_received;
}

void Player::NewPlayerGemArray(std::vector<sf::Vector2f> player_gem_array_received)
{
	player_gem_array = player_gem_array_received;
}

std::vector<int> Player::GetPlayerActiveGemArray()
{
	return listAllActiveGems;
}

std::vector<sf::Vector2f> Player::GetPlayerGemArray()
{
	return player_gem_array;
}

std::vector<int> Player::GetPlayerArmorArray()
{
	return player_armor_array;
}
#pragma endregion AllArrayInformation

float Player::GetMoney()
{
	player_money_sent = player_money;
	return player_money;
}

void Player::GivePlayerMoney(float money_received)
{
	player_money_added += money_received;
}

void Player::NewPlayerMoney(float player_money_received)
{
	if(player_money_received - player_money_sent < 0)
	{
		achievement_gestion.ActionInAchievement(A_GoldSpent, player_money_sent - player_money_received);
	}
	player_money_received_total = player_money_received_total + player_money_received - player_money_sent;
}

void Player::MoneyGestion()
{
	player_money = player_money + player_money_received_total + player_money_added;
	player_money_added = 0;
	player_money_received_total = 0;
}

void Player::UpdateStatsWithEquipments()
{
	player_maximum_health = GlobalFunction::PlayerHealthGestion(player_maximum_health_initial, player_gem_array, listAllGems, listAllArmors, number_current_armor, listAllActiveGems);
	player_damage_modified = GlobalFunction::PlayerDamageGestion(player_damage, player_gem_array, listAllGems, listAllArmors, number_current_armor, listAllActiveGems);
	player_defense = GlobalFunction::PlayerDefenseGestion(player_defense_initial, player_gem_array, listAllGems, listAllArmors, number_current_armor, listAllActiveGems);
	player_bonus_experience_percent = GlobalFunction::PlayerExperienceGestion(player_gem_array, listAllGems, listAllArmors, number_current_armor, listAllActiveGems);
	player_bonus_money_percent = 0;
	player_bonus_fragments_percent = 0;
	speed_of_player = GlobalFunction::PlayerMovementSpeedGestion(speed_of_player_initial, player_gem_array, listAllGems, listAllArmors, number_current_armor, listAllActiveGems);
	player_cooldown_reduction_percent = GlobalFunction::PlayerCooldownReductionGestion(player_gem_array, listAllGems, listAllArmors, number_current_armor, listAllActiveGems);
	player_current_attack_speed = player_max_attack_speed;
	time_before_out_of_battle = time_before_out_of_battle_initial;
	Hp_recovery = 0;
	hp_recovery_increase = 0;
	player_damage_reduction = 0;
	player_cooldown_reduction = player_cooldown_reduction_initial;
	player_lifesteal = 0;
	player_stun_reduction_percent = 0;
	player_stun_reduction = 0;
	armor_on_shield_percent = 0;
	player_max_cooldown_reduction = player_max_cooldown_reduction_initial;
	player_slow_reduction = 0;
	player_shield_recovery = 0;
	player_shieldleech = 0;
	player_maximum_shield_percent = 30;
	sprint_percent_bonus = sprint_percent_bonus_initial;
	player_radar_range_modifier = 1;
	player_bonus_crafting_stat = 0;
	time_to_loot = time_to_loot_initial;
	time_before_out_of_battle = time_before_out_of_battle_initial;
	
	/*player_current_attack_speed += 20;
	player_damage_modified += 2000;
	speed_of_player += 1000;*/
}

float Player::GetBonusExperiencePercent()
{
	return player_bonus_experience_percent;
}

float Player::GetCooldownReduction()
{
	return player_cooldown_reduction_percent;
}

float Player::GetMovementSpeed()
{
	return speed_of_player;
}

int Player::GetNumberTotalGemsUsable()
{
return listAllArmors[number_current_armor]->ReturnAmorNumberGems();
}

#pragma region StunGestion
void Player::StunGestion()
{
	if (player_is_stunned)
	{
		if (clock_check_if_still_stunned.getElapsedTime().asSeconds() >= time_being_stunned)
		{
			time_being_stunned = 0;
			player_is_stunned = false;
			clock_check_if_still_stunned.restart();
		}
		else
		{
			PlayerDidCombatAction();
			position_going_to = GetCurrentPosition();
		}
	}
	StunBarGestion();
}

float Player::GetStunTime()
{
	return time_being_stunned;
}

void Player::StunBarGestion()
{
	if (player_is_stunned)
	{
		float size = (1 - (clock_check_if_still_stunned.getElapsedTime().asSeconds() / time_being_stunned)) * size_health_bar.x;
		stun_bar.setSize(sf::Vector2f(size, 4));
		stun_bar.setPosition(sf::Vector2f(player_image.getPosition().x - player_maximum_health_bar.getSize().x / 2, player_maximum_health_bar.getPosition().y + player_maximum_health_bar.getSize().y / 2 + stun_bar.getSize().y / 2 + 1));
	}
}

void Player::ChangeStunTime(float stun_time_received)
{
	if (!player_is_immune)
	{
		StopLooting();
		player_is_stunned = true;

		if (stun_time_received > 0.15)
		{
			stun_time_received = stun_time_received*(1 - player_stun_reduction_percent / 100);
		}

		if (stun_time_received > 0.3)
		{
			stun_time_received -= player_stun_reduction;
			if (stun_time_received < 0.3)
			{
				stun_time_received = 0.3;
			}
		}

		time_being_stunned = (time_being_stunned > stun_time_received ? time_being_stunned : stun_time_received);
		clock_check_if_still_stunned.restart();
	}
}

bool Player::IsPlayerStunned()
{
	return player_is_stunned;
}

#pragma endregion StunGestion

void Player::Update(TextGenerator &text_generator, sf::RenderWindow &window, float DELTATIME, sf::Vector2f position_view_player, SkillManagement &skill_manager)
{
	if (player_characteristic_created)
	{
		UpdateListPickableMaterial();
		LootOnFloor();
		LootingGestion(position_view_player);
		UpdateStatsWithEquipments();
		CalculateAllStatChanges();
		OutOfBattleGestion();
		UpdateSkillCooldown();
		HealthPotionGestion();
		HealthRecoveryGestion();
		ShieldRecoveryGestion();
		LifeStealGestion();
		StunGestion();
		player_health_maintenance();
		SprintingMaintenance();
		CuttingSprite();

		FeatGestion::instance()->Action(F_MoneyReceived, player_money);
		FeatGestion::instance()->Action(F_LevelReached, player_level-1);
		int counter_succeeded= 0;
		for (int i = 0; i < achievement_gestion.listSucceeded.size(); i++)
		{
			if (achievement_gestion.listSucceeded[i])
			{
				counter_succeeded++;
			}
		}
		FeatGestion::instance()->Action(F_Achievement, counter_succeeded);

		player_in_game_stat_interface.Update(position_view_player, player_damage_modified, is_sprinting ? speed_of_player*sprint_percent_bonus / 100 : speed_of_player, player_cooldown_reduction_percent, player_defense, player_maximum_health, player_current_attack_speed, ListObjectsSingleton::instance()->GetSizeWindow(),player_lifesteal, Hp_recovery);
		float hp_recovery = GetAmountHealingThisTurn();
		float shield_recovery = GetAmountShieldedThisTurn();
		if (hp_recovery > 0)
		{
			if (can_display_hp_recovery)
			{
				sf::String str = "+";
				str = GlobalFunction::InsertNumberToString(str, hp_recovery * 2, str.getSize());
				TextGenerator::instance()->GenerateOneTextStringAndColor(GetCurrentPosition(), str, GetSize(), sf::Color::Green, shared_from_this());
			}
		}
		if (shield_recovery > 0)
		{
			if (can_display_shield_recovery)
			{
				sf::String str = "+";
				str = GlobalFunction::InsertNumberToString(str, shield_recovery * 2, str.getSize());
				TextGenerator::instance()->GenerateOneTextStringAndColor(GetCurrentPosition(), str, GetSize(), sf::Color::Blue, shared_from_this());
			}
		}

		LifeGestion();
	}
	else
	{
		current_opened_interface = MageSelectionInterface_E;
		player_image.setPosition(sf::Vector2f(-10000, -10000));
		position_going_to = sf::Vector2f(-10000, -10000);
		player_current_health = player_maximum_health;
		player_spawned_after_death = false;
	}
}

void Player::GivePlayerChangeStat(int type_change, float duration_change, float value_change)
{
	if (type_change == MovementSpeedPercent && value_change < 0)
	{
		value_change = value_change - value_change*player_slow_reduction / 100;
	}

	TypeChange.push_back(type_change);
	DurationChange.push_back(duration_change);
	ValueChange.push_back(value_change);
	sf::Clock clock_;
	ClockChange.push_back(clock_);
}

void Player::GetSlowed(int type_slow, float duration_slow, float percent_slow)
{
	bool can_be_slowed = true;

	if (type_slow == TranquilizerTalentSlow_E)
	{
		std::list<int>::iterator iterator_type = TypeChange.begin();
		std::list<sf::Clock>::iterator iterator_clock = ClockChange.begin();
		while (iterator_type != TypeChange.end())
		{
			if ((*iterator_type) == TranquilizerTalentSlow_E)
			{

				(*iterator_clock).restart();
				can_be_slowed = false;
				break;
			}
			iterator_type++;
			iterator_clock++;
		}
	}
	if (can_be_slowed)
	{
		GivePlayerChangeStat(MovementSpeedPercent, duration_slow, -percent_slow);
	}
}

void Player::CalculateAllStatChanges()
{
	player_can_be_immune = false;
	player_can_be_scared = false;
	player_can_be_cantdie = false;

	std::list<int>::iterator iterator_type = TypeChange.begin();
	std::list<float>::iterator iterator_duration = DurationChange.begin();
	std::list<float>::iterator iterator_value = ValueChange.begin();
	std::list<sf::Clock>::iterator iterator_clock = ClockChange.begin();
	while (iterator_duration != DurationChange.end())
	{
		if ((*iterator_duration) == -1)
		{
			if ((*iterator_type) == MovementSpeedPercent)
			{
				if ((*iterator_value) > 0)
				{
					bonus_movement_speed_percent_positive += (*iterator_value);
				}
				else
				{
					bonus_movement_speed_percent_negative = bonus_movement_speed_percent_negative < (*iterator_value) ? bonus_movement_speed_percent_negative : (*iterator_value);
				}
			}
			else if ((*iterator_type) == AttackSpeedPercent)
			{
				bonus_attack_speed_percent += (*iterator_value);
			}
			else if ((*iterator_type) == DamagePercent)
			{
				bonus_attack_damage_percent += (*iterator_value);
			}
			else if ((*iterator_type) == Immunity)
			{
				player_can_be_immune = true;
			}
			else if ((*iterator_type) == HpPercentRecovery)
			{
				bonus_hp_percent_recovery += (*iterator_value);
			}
			else if ((*iterator_type) == DefensePercent)
			{
				bonus_defense_addition += (*iterator_value);
			}
			else if ((*iterator_type) == HealthPercent)
			{
				bonus_health_percent += (*iterator_value);
			}
			else if ((*iterator_type) == DamagePercentOverall)
			{
				bonus_attack_damage_percent_overall += (*iterator_value);
			}
			else if ((*iterator_type) == HpRecoveryPercentIncrease)
			{
				bonus_hp_recovery_increase_percent += (*iterator_value);
			}
			else if ((*iterator_type) == LifeSteal)
			{
				bonus_lifesteal += (*iterator_value);
			}
			else if ((*iterator_type) == CantDie)
			{
				player_can_be_cantdie = true;
			}
			else if ((*iterator_type) == StunReductionPercent)
			{
				bonus_stun_reduction_percent += (*iterator_value);
			}
			else if ((*iterator_type) == HpRecovery)
			{
				bonus_hp_recovery += (*iterator_value);
			}
			else if ((*iterator_type) == DamageReduction)
			{
				bonus_damage_reduction += (*iterator_value);
			}
			else if ((*iterator_type) == ShieldCapacity)
			{
				bonus_shield_capacity_addition_percent += (*iterator_value);
			}
			else if ((*iterator_type) == DamageAddition)
			{
				bonus_attack_damage_addition += (*iterator_value);
			}

			DurationChange.erase(iterator_duration++);
			TypeChange.erase(iterator_type++);
			ValueChange.erase(iterator_value++);
			ClockChange.erase(iterator_clock++);
		}
		else
		{
			if ((*iterator_clock).getElapsedTime().asSeconds() <= (*iterator_duration))
			{
				if ((*iterator_type) == MovementSpeedPercent)
				{
					if ((*iterator_value) > 0)
					{
						bonus_movement_speed_percent_positive +=(*iterator_value);
					}
					else
					{
						bonus_movement_speed_percent_negative = bonus_movement_speed_percent_negative < (*iterator_value) ? bonus_movement_speed_percent_negative : (*iterator_value);
					}
				}
				else if ((*iterator_type) == AttackSpeedPercent)
				{
					bonus_attack_speed_percent += (*iterator_value);
				}
				else if ((*iterator_type) == DamagePercent)
				{
					bonus_attack_damage_percent += (*iterator_value);
				}
				else if ((*iterator_type) == Immunity)
				{
					player_can_be_immune = true;
				}
				else if ((*iterator_type) == Scared)
				{
					player_can_be_scared = true;
				}
				else if ((*iterator_type) == HpPercentRecovery)
				{
					bonus_hp_percent_recovery += (*iterator_value);
				}
				else if ((*iterator_type) == DefensePercent)
				{
					bonus_defense_percent += (*iterator_value);
				}
				else if ((*iterator_type) == HealthPercent)
				{
					bonus_health_percent += (*iterator_value);
				}
				else if ((*iterator_type) == DamagePercentOverall)
				{
					bonus_attack_damage_percent_overall += (*iterator_value);
				}
				else if ((*iterator_type) == HpRecoveryPercentIncrease)
				{
					bonus_hp_recovery_increase_percent += (*iterator_value);
				}
				else if ((*iterator_type) == LifeSteal)
				{
					bonus_lifesteal += (*iterator_value);
				}
				else if ((*iterator_type) == ShieldHpPercentRecovery)
				{
					bonus_shield_recovery_percent_health += (*iterator_value);
				}
				else if ((*iterator_type) == CantDie)
				{
					player_can_be_cantdie = true;
				}
				else if ((*iterator_type) == StunReductionPercent)
				{
					bonus_stun_reduction_percent += (*iterator_value);
				}
				else if ((*iterator_type) == HpRecovery)
				{
					bonus_hp_recovery += (*iterator_value);
				}
				else if ((*iterator_type) == DamageReduction)
				{
					bonus_damage_reduction += (*iterator_value);
				}
				else if ((*iterator_type) == ShieldCapacity)
				{
					bonus_shield_capacity_addition_percent += (*iterator_value);
				}
				else if ((*iterator_type) == DamageAddition)
				{
					bonus_attack_damage_addition += (*iterator_value);
				}

				iterator_duration++;
				iterator_type++;
				iterator_value++;
				iterator_clock++;
			}
			else
			{
				DurationChange.erase(iterator_duration++);
				TypeChange.erase(iterator_type++);
				ValueChange.erase(iterator_value++);
				ClockChange.erase(iterator_clock++);
			}
		}
	}

	player_icone_bonus.Update(player_is_out_of_battle, bonus_attack_damage_percent + bonus_attack_damage_percent_overall, bonus_health_percent + bonus_health_percent_overall, bonus_defense_percent + bonus_defense_percent_overall, bonus_movement_speed_percent_positive + bonus_movement_speed_percent_negative, bonus_hp_percent_recovery + bonus_hp_recovery, player_can_be_immune, bonus_attack_speed_percent);

	bonus_attack_damage_percent;

	CheckWeaponBonus();
	CheckTalentBonus();
	PassiveSkillGestion();
	TalentBuffGestion();
	CheckScrollBonus();
	CheckRingBonus();
	CheckCharacteristicBonus();
	CheckArmorBonus();

	player_slow_reduction += bonus_slow_reduction;

	speed_of_player += bonus_movement_speed;
	speed_of_player += bonus_movement_speed_percent_positive*speed_of_player / 100;
	speed_of_player += bonus_movement_speed_percent_after_all*speed_of_player / 100;

	if (bonus_movement_speed_percent_negative < 0)
	{
		bonus_movement_speed_percent_negative -= bonus_movement_speed_percent_negative*player_slow_reduction/100;
		speed_of_player += bonus_movement_speed_percent_negative*speed_of_player / 100;
	}

	if (speed_of_player < 0)
	{
		speed_of_player = 0;
	}

	sprint_percent_bonus = sprint_percent_bonus + bonus_addition_percent_sprint;

	player_current_attack_speed += bonus_attack_speed;
	player_current_attack_speed += bonus_attack_speed_percent*player_current_attack_speed / 100;

	player_maximum_health += bonus_health_addition;
	player_maximum_health += bonus_health_percent*(player_maximum_health/100);
	player_maximum_health += player_maximum_health*bonus_health_percent_overall / 100;

	player_defense += bonus_defense_addition;
	player_defense += bonus_defense_percent*player_defense / 100;
	player_defense += bonus_defense_percent_overall*player_defense / 100;
	armor_on_shield_percent += bonus_armor_on_shield;
	

	hp_recovery_increase += hp_recovery_increase*listFeatBonus[Surviver_E];
	hp_recovery_increase = bonus_hp_recovery_increase_percent;
	Hp_recovery += bonus_hp_recovery*(hp_recovery_increase / 100 + 1);
	Hp_recovery += player_maximum_health*bonus_hp_percent_recovery / 100 * (hp_recovery_increase / 100 + 1);

	player_damage_reduction += bonus_damage_reduction;

	player_damage_modified += bonus_attack_damage_addition;
	player_damage_modified += bonus_attack_damage_percent*player_damage_modified / 100;
	player_damage_modified += player_damage_modified*bonus_attack_damage_percent_overall / 100;

	player_lifesteal += bonus_lifesteal;
	if (player_lifesteal < 0)
	{
		player_lifesteal = 0;
	}

	player_maximum_shield_percent += bonus_shield_capacity_addition_percent;
	player_shieldleech += bonus_shieldleech;
	player_shield_recovery += bonus_shield_recovery_percent_health*player_maximum_health / 100;

	player_stun_reduction += bonus_stun_reduction;
	player_stun_reduction_percent += bonus_stun_reduction_percent;

	player_max_cooldown_reduction += bonus_max_cooldown_reduction;
	player_cooldown_reduction += bonus_cooldown_reduction;
	player_cooldown_reduction_percent += bonus_cooldown_reduction_percent;
	if (player_cooldown_reduction_percent > player_max_cooldown_reduction)
	{
		player_cooldown_reduction_percent = player_max_cooldown_reduction;
	}

	if (player_can_be_immune)
	{
		player_is_immune = true;
		player_image.setColor(sf::Color::Yellow);
		player_is_scared = false;
	}
	else
	{
		if (player_can_be_scared)
		{
			player_is_scared = true;
		}
		else
		{
			player_is_scared = false;
		}
		player_is_immune = false;
		player_image.setColor(sf::Color::Color(255,255,255));
	}
	if (player_can_be_cantdie)
	{
		cant_die_status = true;
	}
	//BonusForTesting
	//player_damage_modified = 50;
	//player_current_attack_speed = 10;
	//speed_of_player = 1500;
	//player_is_immune = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		//player_current_health = -1;
		player_maximum_health = 100000;
		player_current_health = 100000;
		player_current_attack_speed = 10;
		number_monster_hearts = 25;
		player_damage_modified += 10000;
		speed_of_player = 1200;
		player_is_immune = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
	{
		HealPlayer(1000);
		GivePlayerMoney(50000);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		if (clock_testing.getElapsedTime().asSeconds() >= 0.5)
		{
			GetExp(GlobalFunction::GetPlayerExperienceNeeded(player_level) / 4);
			clock_testing.restart();
		}
	}

	time_before_out_of_battle -= bonus_time_out_battle_modifier;

	player_bonus_experience_percent += bonus_to_bonus_experience_percent;
	player_bonus_money_percent += bonus_to_bonus_money_percent;

	player_radar_range_modifier += bonus_radar_range_modifier;

	player_bonus_crafting_stat += bonus_to_bonus_crafting_stat;

	time_to_loot -= bonus_looting_time_modifier;

	bonus_to_bonus_experience_percent = 0;
	bonus_attack_damage_percent_overall = 0;
	bonus_shield_capacity_addition_percent = 0;
	bonus_movement_speed_percent_after_all = 0;
	bonus_movement_speed_percent = 0;
	bonus_attack_speed_percent = 0;
	bonus_attack_damage_addition = 0;
	bonus_cooldown_reduction = 0;
	bonus_attack_damage_percent = 0;
	bonus_hp_percent_recovery = 0;
	bonus_hp_recovery = 0;
	bonus_health_percent = 0;
	bonus_health_addition = 0;
	bonus_defense_percent = 0;
	bonus_defense_addition = 0;
	bonus_armor_on_shield = 0;
	bonus_shield_recovery_percent_health = 0;
	bonus_stun_reduction = 0;
	bonus_max_cooldown_reduction = 0;
	bonus_lifesteal = 0;
	bonus_slow_reduction = 0;
	bonus_time_out_battle_modifier = 0;
	bonus_cooldown_reduction_percent = 0;
	bonus_damage_reduction = 0;
	bonus_hp_recovery_increase_percent = 0;
	bonus_stun_reduction_percent = 0;
	bonus_attack_speed = 0;
	bonus_shieldleech = 0;
	bonus_movement_speed_percent_negative = 0;
	bonus_movement_speed_percent_positive = 0;
	bonus_movement_speed_percent = 0;
	bonus_addition_percent_sprint = 0;
	bonus_health_percent_overall = 0;
	bonus_defense_percent_overall = 0;
	bonus_to_bonus_money_percent = 0;
	bonus_radar_range_modifier = 0;
	bonus_to_bonus_crafting_stat = 0;
	bonus_movement_speed = 0;
	bonus_looting_time_modifier = 0;

	CheckFeatBonus();
}

void Player::CheckTalentBonus()
{
	if (player_array_talent_level[Enraged_E] + player_array_talent_increasement[Enraged_E] >= 1)
	{
		bonus_attack_damage_percent += listAllTalents[Enraged_E]->GetTalentBonus(player_array_talent_level[Enraged_E] + player_array_talent_increasement[Enraged_E]);
	}
	if (player_array_talent_level[Boosted_E] + player_array_talent_increasement[Boosted_E] >= 1)
	{
		bonus_attack_speed_percent += listAllTalents[Boosted_E]->GetTalentBonus(player_array_talent_level[Boosted_E] + player_array_talent_increasement[Boosted_E]);
	}
	if (player_array_talent_level[Beastly_E] + player_array_talent_increasement[Beastly_E] >= 1)
	{
		bonus_health_percent += listAllTalents[Beastly_E]->GetTalentBonus(player_array_talent_level[Beastly_E] + player_array_talent_increasement[Beastly_E]);
	}
	if (player_array_talent_level[StoneMan_E] + player_array_talent_increasement[StoneMan_E] >= 1)
	{
		bonus_defense_percent += listAllTalents[StoneMan_E]->GetTalentBonus(player_array_talent_level[StoneMan_E] + player_array_talent_increasement[StoneMan_E]);
	}
	if (player_array_talent_level[Swifty_E] + player_array_talent_increasement[Swifty_E] >= 1)
	{
		bonus_movement_speed_percent += listAllTalents[Swifty_E]->GetTalentBonus(player_array_talent_level[Swifty_E] + player_array_talent_increasement[Swifty_E]);
	}
	if (player_array_talent_level[HappyMeal_E] + player_array_talent_increasement[HappyMeal_E] >= 1)
	{
		bonus_lifesteal += listAllTalents[HappyMeal_E]->GetTalentBonus(player_array_talent_level[HappyMeal_E] + player_array_talent_increasement[HappyMeal_E]);
	}
	if (player_array_talent_level[NatureBornKiller_E] + player_array_talent_increasement[NatureBornKiller_E] >= 1)
	{
		bonus_attack_speed += listAllTalents[NatureBornKiller_E]->GetTalentBonus(player_array_talent_level[NatureBornKiller_E] + player_array_talent_increasement[NatureBornKiller_E]);
	}
	if (player_array_talent_level[PeaceLoving_E] + player_array_talent_increasement[PeaceLoving_E] >= 1)
	{
		bonus_time_out_battle_modifier += listAllTalents[PeaceLoving_E]->GetTalentBonus(player_array_talent_level[PeaceLoving_E] + player_array_talent_increasement[PeaceLoving_E]);
	}
	if (player_array_talent_level[Enlightened_E] + player_array_talent_increasement[Enlightened_E] >= 1)
	{
		bonus_max_cooldown_reduction += listAllTalents[Enlightened_E]->GetTalentBonus(player_array_talent_level[Enlightened_E] + player_array_talent_increasement[Enlightened_E]);
	}
	if (player_array_talent_level[Unstoppable_E] + player_array_talent_increasement[Unstoppable_E] >= 1)
	{
		bonus_slow_reduction += listAllTalents[Unstoppable_E]->GetTalentBonus(player_array_talent_level[Unstoppable_E] + player_array_talent_increasement[Unstoppable_E]);
	}
	if (player_array_talent_level[HardyMan_E] + player_array_talent_increasement[HardyMan_E] >= 1)
	{
		bonus_stun_reduction += listAllTalents[HardyMan_E]->GetTalentBonus(player_array_talent_level[HardyMan_E] + player_array_talent_increasement[HardyMan_E]);
	}
	if (player_array_talent_level[Restless_E] + player_array_talent_increasement[Restless_E] >= 1)
	{
		bonus_cooldown_reduction += listAllTalents[Restless_E]->GetTalentBonus(player_array_talent_level[Restless_E] + player_array_talent_increasement[Restless_E]);
	}
	if (player_array_talent_level[OvercomeTheBarriers_E] + player_array_talent_increasement[OvercomeTheBarriers_E] >= 1 && player_is_out_of_battle)
	{
		bonus_shield_recovery_percent_health += listAllTalents[OvercomeTheBarriers_E]->GetTalentBonus(player_array_talent_level[OvercomeTheBarriers_E] + player_array_talent_increasement[OvercomeTheBarriers_E]);
	}
	if (player_array_talent_level[AfterEffect_E] + player_array_talent_increasement[AfterEffect_E] >= 1)
	{
		bonus_shieldleech += listAllTalents[AfterEffect_E]->GetTalentBonus(player_array_talent_level[AfterEffect_E] + player_array_talent_increasement[AfterEffect_E]);
	}
	if (player_array_talent_level[ImmuneSystem_E] + player_array_talent_increasement[ImmuneSystem_E] >= 1)
	{
		bonus_hp_percent_recovery += listAllTalents[ImmuneSystem_E]->GetTalentBonus(player_array_talent_level[ImmuneSystem_E] + player_array_talent_increasement[ImmuneSystem_E]);
	}
	if (player_array_talent_level[HealthCare_E] + player_array_talent_increasement[HealthCare_E] >= 1)
	{
		bonus_hp_recovery_increase_percent += listAllTalents[HealthCare_E]->GetTalentBonus(player_array_talent_level[HealthCare_E] + player_array_talent_increasement[HealthCare_E]);
	}
	if (player_array_talent_level[DenseShield_E] + player_array_talent_increasement[DenseShield_E] >= 1)
	{
		bonus_shield_capacity_addition_percent += listAllTalents[DenseShield_E]->GetTalentBonus(player_array_talent_level[DenseShield_E] + player_array_talent_increasement[DenseShield_E]);
	}
	if (player_array_talent_level[Blockade_E] + player_array_talent_increasement[Blockade_E] >= 1)
	{
		bonus_damage_reduction += listAllTalents[Blockade_E]->GetTalentBonus(player_array_talent_level[Blockade_E] + player_array_talent_increasement[Blockade_E]);
	}
	if (player_array_talent_level[ReinforcedShield_E] + player_array_talent_increasement[ReinforcedShield_E] >= 1)
	{
		bonus_armor_on_shield += listAllTalents[ReinforcedShield_E]->GetTalentBonus(player_array_talent_level[ReinforcedShield_E] + player_array_talent_increasement[ReinforcedShield_E]);
	}
}

void Player::CheckWeaponBonus()
{
	if (current_weapon != NULL)
	{
		bonus_lifesteal += current_weapon->GetBonusValue(LifeSteal);
		bonus_movement_speed_percent += current_weapon->GetBonusValue(MovementSpeedPercent);
		bonus_attack_speed_percent += current_weapon->GetBonusValue(AttackSpeedPercent);
		bonus_attack_damage_addition += current_weapon->GetBonusValue(DamageAddition);
		bonus_defense_addition += current_weapon->GetBonusValue(DefenseAddition);
		bonus_health_addition += current_weapon->GetBonusValue(HealthAddition);
		bonus_hp_recovery += current_weapon->GetBonusValue(HpRecovery);
		bonus_cooldown_reduction_percent += current_weapon->GetBonusValue(CooldownReduction);
		bonus_stun_reduction_percent += current_weapon->GetBonusValue(StunReductionPercent);
	}
}

void Player::CheckScrollBonus()
{
	if (listScrollEquipped[OutOfSprintOneRun])
	{
		bonus_addition_percent_sprint += listScrollBonus[OutOfSprintOneRun];
	}
	if (listScrollEquipped[MonsterKilledOneRun])
	{
		bonus_attack_damage_percent_overall += listScrollBonus[MonsterKilledOneRun];
	}
	if(listScrollEquipped[MapFifthReached])
	{
		bonus_health_percent_overall += listScrollBonus[MapFifthReached];
		bonus_defense_percent_overall += listScrollBonus[MapFifthReached];
	}
	if (listScrollEquipped[ReachLevelTen])
	{
		bonus_to_bonus_experience_percent += listScrollBonus[ReachLevelTen];
	}
	if (listScrollEquipped[SpendGoldOneRun])
	{
		bonus_to_bonus_money_percent += listScrollBonus[SpendGoldOneRun];
	}
	if (listScrollEquipped[TotalHealOneRun] && player_is_out_of_battle)
	{
		bonus_hp_percent_recovery += listScrollBonus[TotalHealOneRun];
	}
	if (listScrollEquipped[MonsterOnRadar])
	{
		bonus_radar_range_modifier += 0.5;
	}
	if (listScrollEquipped[NoDamageWhileCombat])
	{
		if (clock_scroll_immunity.getElapsedTime().asSeconds() >= listScrollBonus[NoDamageWhileCombat])
		{
			clock_scroll_immunity.restart();
			GivePlayerChangeStat(Immunity, 3, 0);
		}
	}
}

void Player::CheckCharacteristicBonus()
{
	if (ListCharacteristicMages[0])
	{
		if (ListCharacteristicProsOrCons[0] > 0)
		{
			bonus_attack_damage_percent_overall += ListCharacteristicValue[0];
		}
		else
		{
			bonus_attack_damage_percent_overall -= ListCharacteristicValue[0];
		}
	}
	if (ListCharacteristicMages[1])
	{
		if (ListCharacteristicProsOrCons[1] > 0)
		{
			bonus_damage_reduction += ListCharacteristicValue[1];
		}
		else
		{
			bonus_damage_reduction -= ListCharacteristicValue[1];
		}
	}
	if (ListCharacteristicMages[2])
	{
		if (ListCharacteristicProsOrCons[2] > 0)
		{
			bonus_health_percent_overall += ListCharacteristicValue[2];
		}
		else
		{
			bonus_health_percent_overall -= ListCharacteristicValue[2];
		}
	}
	if (ListCharacteristicMages[3])
	{
		if (ListCharacteristicProsOrCons[3] > 0)
		{
			bonus_addition_percent_sprint += ListCharacteristicValue[3];
		}
		else
		{
			bonus_addition_percent_sprint -= ListCharacteristicValue[3];
		}
	}
	if (ListCharacteristicMages[4])
	{
		if (ListCharacteristicProsOrCons[4] > 0)
		{
			bonus_movement_speed_percent_after_all += ListCharacteristicValue[4];
		}
		else
		{
			bonus_movement_speed_percent_after_all -= ListCharacteristicValue[4];
		}
	}
	if (ListCharacteristicMages[5])
	{
		if (ListCharacteristicProsOrCons[5] > 0)
		{
			bonus_to_bonus_experience_percent += ListCharacteristicValue[5];
		}
		else
		{
			bonus_to_bonus_experience_percent -= ListCharacteristicValue[5];
		}
	}
	if (ListCharacteristicMages[6])
	{
		if (ListCharacteristicProsOrCons[6] > 0)
		{
			bonus_to_bonus_money_percent += ListCharacteristicValue[6];
		}
		else
		{
			bonus_to_bonus_money_percent -= ListCharacteristicValue[6];
		}
	}
	if (ListCharacteristicMages[7])
	{
		if (ListCharacteristicProsOrCons[7] > 0)
		{
			bonus_attack_speed_percent += ListCharacteristicValue[7];
		}
		else
		{
			bonus_attack_speed_percent -= ListCharacteristicValue[7];
		}
	}
	if (ListCharacteristicMages[8])
	{
		if (ListCharacteristicProsOrCons[8] > 0)
		{
			bonus_hp_recovery_increase_percent += ListCharacteristicValue[8];
		}
		else
		{
			bonus_hp_recovery_increase_percent -= ListCharacteristicValue[8];
		}
	}
	if (ListCharacteristicMages[9])
	{
		if (ListCharacteristicProsOrCons[9] > 0)
		{
			bonus_lifesteal += ListCharacteristicValue[9];
		}
		else
		{
			bonus_lifesteal -= ListCharacteristicValue[9];
		}
	}
	if (ListCharacteristicMages[10])
	{
		if (ListCharacteristicProsOrCons[10] > 0)
		{
			bonus_radar_range_modifier += ListCharacteristicValue[10]/100;
		}
		else
		{
			bonus_radar_range_modifier -= ListCharacteristicValue[10]/100;
		}
	}
	if (ListCharacteristicMages[11])
	{
		if (ListCharacteristicProsOrCons[11] > 0)
		{
			bonus_to_bonus_crafting_stat += ListCharacteristicValue[11];
		}
		else
		{
			bonus_to_bonus_crafting_stat -= ListCharacteristicValue[11];
		}
	}
	if (ListCharacteristicMages[12])
	{
		if (ListCharacteristicProsOrCons[12] > 0)
		{
			bonus_stun_reduction_percent += ListCharacteristicValue[12];
		}
		else
		{
			bonus_stun_reduction_percent -= ListCharacteristicValue[12];
		}
	}
	if (ListCharacteristicMages[13])
	{
		if (ListCharacteristicProsOrCons[13] > 0)
		{
			bonus_looting_time_modifier += ListCharacteristicValue[13]* time_to_loot_initial/100;
		}
		else
		{
			bonus_looting_time_modifier -= ListCharacteristicValue[13]* time_to_loot_initial/100;
		}
	}
	if (ListCharacteristicMages[14])
	{
		if (ListCharacteristicProsOrCons[14] > 0)
		{
			bonus_time_out_battle_modifier += ListCharacteristicValue[14];
		}
		else
		{
			bonus_time_out_battle_modifier -= ListCharacteristicValue[14];
		}
	}
}

void Player::CheckRingBonus()
{
	if (current_ring1 != NULL)
	{
		std::vector<bool> listRingIfHaveBonus = current_ring1->GetListIfHaveBonus();
		std::vector<float> listRingBonus = current_ring1->GetListBonus();

		if (listRingIfHaveBonus[RingHpRecovery])
		{
			bonus_hp_recovery += listRingBonus[RingHpRecovery];
		}
		if (listRingIfHaveBonus[RingHpPercentRevoery])
		{
			bonus_hp_percent_recovery += listRingBonus[RingHpPercentRevoery];
		}
		if (listRingIfHaveBonus[RingMovementSpeedAddition])
		{
			bonus_movement_speed += listRingBonus[RingMovementSpeedAddition];
		}
		if (listRingIfHaveBonus[RingDamagePercent])
		{
			bonus_attack_damage_percent += listRingBonus[RingDamagePercent];
		}
		if (listRingIfHaveBonus[RingDamageAddition])
		{
			bonus_attack_damage_addition += listRingBonus[RingDamageAddition];
		}
		if (listRingIfHaveBonus[RingExperiencePercent])
		{
			bonus_to_bonus_experience_percent += listRingBonus[RingExperiencePercent];
		}
		if (listRingIfHaveBonus[RingHealthAddition])
		{
			bonus_health_addition += listRingBonus[RingHealthAddition];
		}
		if (listRingIfHaveBonus[RingHealthPercent])
		{
			bonus_health_percent += listRingBonus[RingHealthPercent];
		}
		if (listRingIfHaveBonus[RingArmorAddition])
		{
			bonus_defense_addition += listRingBonus[RingArmorAddition];
		}
		if (listRingIfHaveBonus[RingArmorPercent])
		{
			bonus_defense_percent += listRingBonus[RingArmorPercent];
		}
		if (listRingIfHaveBonus[RingCooldown])
		{
			bonus_cooldown_reduction_percent += listRingBonus[RingCooldown];
		}
		if (listRingIfHaveBonus[RingAttackSpeedPercent])
		{
			bonus_attack_speed_percent += listRingBonus[RingAttackSpeedPercent];
		}
		if (listRingIfHaveBonus[RingLifeSteal])
		{
			bonus_lifesteal += listRingBonus[RingLifeSteal];
		}
	}

	if (current_ring2 != NULL)
	{
		std::vector<bool> listRingIfHaveBonus = current_ring2->GetListIfHaveBonus();
		std::vector<float> listRingBonus = current_ring2->GetListBonus();

		if (listRingIfHaveBonus[RingHpRecovery])
		{
			bonus_hp_recovery += listRingBonus[RingHpRecovery];
		}
		if (listRingIfHaveBonus[RingHpPercentRevoery])
		{
			bonus_hp_percent_recovery += listRingBonus[RingHpPercentRevoery];
		}
		if (listRingIfHaveBonus[RingMovementSpeedAddition])
		{
			bonus_movement_speed += listRingBonus[RingMovementSpeedAddition];
		}
		if (listRingIfHaveBonus[RingDamagePercent])
		{
			bonus_attack_damage_percent += listRingBonus[RingDamagePercent];
		}
		if (listRingIfHaveBonus[RingDamageAddition])
		{
			bonus_attack_damage_addition += listRingBonus[RingDamageAddition];
		}
		if (listRingIfHaveBonus[RingExperiencePercent])
		{
			bonus_to_bonus_experience_percent += listRingBonus[RingExperiencePercent];
		}
		if (listRingIfHaveBonus[RingHealthAddition])
		{
			bonus_health_addition += listRingBonus[RingHealthAddition];
		}
		if (listRingIfHaveBonus[RingHealthPercent])
		{
			bonus_health_percent += listRingBonus[RingHealthPercent];
		}
		if (listRingIfHaveBonus[RingArmorAddition])
		{
			bonus_defense_addition += listRingBonus[RingArmorAddition];
		}
		if (listRingIfHaveBonus[RingArmorPercent])
		{
			bonus_defense_percent += listRingBonus[RingArmorPercent];
		}
		if (listRingIfHaveBonus[RingCooldown])
		{
			bonus_cooldown_reduction_percent += listRingBonus[RingCooldown];
		}
		if (listRingIfHaveBonus[RingAttackSpeedPercent])
		{
			bonus_attack_speed_percent += listRingBonus[RingAttackSpeedPercent];
		}
		if (listRingIfHaveBonus[RingLifeSteal])
		{
			bonus_lifesteal += listRingBonus[RingLifeSteal];
		}
	}
}

void Player::CheckArmorBonus()
{
	int type_bonus_armor = listAllArmors[number_current_armor]->ReturnArmorBonusType();
	float bonus_armor = listAllArmors[number_current_armor]->ReturnArmorBonusNumber();
	switch (type_bonus_armor)
	{
	case A_HealthPerSecond:
		bonus_hp_recovery += bonus_armor;
		break;
	case A_Damage:
		bonus_attack_damage_percent += bonus_armor;
		break;
	case A_HealthArmor:
		bonus_health_percent += bonus_armor;
		bonus_defense_percent += bonus_armor;
		break;
	case A_AttackSpeed:
		bonus_attack_speed_percent += bonus_armor;
		break;
	case A_HealthArmorDamage:
		bonus_attack_damage_percent += bonus_armor;
		bonus_health_percent += bonus_armor;
		bonus_defense_percent += bonus_armor;
		break;
	case A_Speed:
		bonus_movement_speed_percent += bonus_armor;
		break;
	case A_Cooldown:
		bonus_cooldown_reduction_percent += bonus_armor;
		break;
	}
}

void Player::CheckFeatBonus()
{
	player_damage_modified += player_damage_modified*listFeatBonus[Slaughterer_E] / 100;
	player_lifesteal += player_lifesteal*listFeatBonus[Fighter_E] / 100;
	player_current_attack_speed += player_current_attack_speed*listFeatBonus[Hitman_E] / 100;
	player_maximum_health += player_maximum_health*listFeatBonus[Surviver_E] / 100;
	player_bonus_experience_percent += listFeatBonus[Veteran_E];
	player_bonus_money_percent += listFeatBonus[Greedy_E];
	player_bonus_crafting_stat += listFeatBonus[Lord_E];
	player_bonus_fragments_percent += listFeatBonus[Archmage_E];
	player_defense += player_defense*listFeatBonus[Talented_E]/100;
}

#pragma region Recovery

void Player::HealthRecoveryGestion()
{
	if (clock_health_recovery.getElapsedTime().asSeconds() >= 0.49)
	{
		float health_missing = player_maximum_health - player_current_health;
		if (health_missing >= Hp_recovery / 2)
		{
			player_current_health += Hp_recovery / 2;
			amount_health_recovered_this_turn += Hp_recovery / 2;
		}
		else
		{
			player_current_health += health_missing;
			amount_health_recovered_this_turn += health_missing;
		}
		can_display_hp_recovery = !can_display_hp_recovery;
		clock_health_recovery.restart();
	}
}

void Player::ShieldRecoveryGestion()
{
	if (clock_shield_recovery.getElapsedTime().asSeconds() >= 0.5)
	{
		float shield_missing = player_maximum_health*player_maximum_shield_percent/100 - player_current_shield;
		if (shield_missing >= player_shield_recovery / 2)
		{
			player_current_shield += player_shield_recovery / 2;
			amount_shield_recovered_this_turn += player_shield_recovery / 2;
		}
		else
		{
			player_current_shield += shield_missing;
			amount_shield_recovered_this_turn += shield_missing;
		}
		can_display_shield_recovery = !can_display_hp_recovery;
		clock_shield_recovery.restart();
	}
}

float Player::GetAmountHealingThisTurn()
{
	float amount_healed = amount_health_recovered_this_turn;
	amount_health_recovered_this_turn = 0;
	return amount_healed;
}

float Player::GetAmountShieldedThisTurn()
{
	float amount_shielded = amount_shield_recovered_this_turn;
	amount_shield_recovered_this_turn = 0;
	return amount_shielded;
}

void Player::HealPlayer(float amount_healed)
{
	if (amount_healed > 0)
	{
		float health_missing = player_maximum_health - player_current_health;
		if (health_missing >= amount_healed)
		{
			player_current_health += amount_healed;
			achievement_gestion.ActionInAchievement(A_Heal, amount_healed);
		}
		else
		{
			player_current_health += health_missing;
			achievement_gestion.ActionInAchievement(A_Heal, health_missing);
		}
		TextGenerator::instance()->GenerateOneTextPlayerColorSpecified(GetCurrentPosition(), amount_healed, GetSize(), sf::Color::Green, shared_from_this());
	}
}

void Player::ShieldObject(float amount_shield)
{
	if (!player_is_immune)
	{
		if (amount_shield > 0)
		{
			float shield_missing = player_maximum_health*player_maximum_shield_percent/100 - player_current_shield;
			if (shield_missing >= amount_shield)
			{
				player_current_shield += amount_shield;
			}
			else
			{
				player_current_shield += shield_missing;
			}
			TextGenerator::instance()->GenerateOneTextPlayerColorSpecified(GetCurrentPosition(), amount_shield, GetSize(), sf::Color::Blue, shared_from_this());
		}
	}
}

void Player::HealthPotionGestion()
{
	if (inventory[I_Miscellaneous][IM_HealthPotion] > 0 && can_use_health_potion && player_current_health < player_maximum_health*0.95)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			clock_health_potion_duration.restart();
			clock_cooldown_health_potion.restart();
			clock_health_potion_tick.restart();
			can_use_health_potion = false;
			using_potion = true;
			inventory[I_Miscellaneous][IM_HealthPotion]--;

			FeatGestion::instance()->Action(F_PotionUsed, 1);

			if (ListDrawbackMages[4])
			{
				int number_random = GlobalFunction::getRandomRange(1, 1000);
				if (number_random <= 250)
				{
					GivePlayerChangeStat(Scared, 2, 0);
				}
				else if (number_random <= 500)
				{
					GivePlayerChangeStat(DamagePercent,-50,20);
				}
				else if (number_random <= 750)
				{
					GivePlayerChangeStat(MovementSpeedPercent, -50, 20);
				}
				else
				{
					GivePlayerChangeStat(HpRecovery, -20 - (player_level-1)*9.5, 10);
				}
			}
		}
	}

	if(clock_health_potion_duration.getElapsedTime().asSeconds() <= 10.05)
	{
		if (clock_health_potion_tick.getElapsedTime().asSeconds() >= 0.49)
		{
			float potion_recovery = player_maximum_health*0.4 / 10;
			if (player_is_out_of_battle)
			{
				float health_missing = player_maximum_health - player_current_health;
				if (health_missing >= potion_recovery / 2)
				{
					player_current_health += potion_recovery / 2;
					amount_health_recovered_this_turn += potion_recovery / 2;
				}
				else
				{
					player_current_health += health_missing;
					amount_health_recovered_this_turn += health_missing;
				}
			}
			else
			{
				float health_missing = player_maximum_health - player_current_health;
				if (health_missing >= potion_recovery / 2)
				{
					player_current_health += potion_recovery / 2;
					amount_health_recovered_this_turn += potion_recovery / 2;
				}
				else
				{
					player_current_health += health_missing;
					amount_health_recovered_this_turn += health_missing;
				}
			}
			clock_health_potion_tick.restart();
		}
	}
	else
	{
		using_potion = false;
	}

	if (!can_use_health_potion)
	{
		if (clock_cooldown_health_potion.getElapsedTime().asSeconds() >= health_potion_cooldown)
		{
			can_use_health_potion = true;
		}
	}
}

void Player::LifeStealGestion()
{
	if (clock_lifesteal.getElapsedTime().asSeconds() >= 1)
	{
		HealPlayer(damage_dealt_in_second*GetLifesteal() / 100);
		ShieldObject(damage_dealt_in_second*bonus_shieldleech / 100);

		damage_dealt_in_second = 0;
		clock_lifesteal.restart();
	}
}

#pragma endregion Recovery

void Player::PassiveSkillGestion()
{
	for (int number = 0; number < player_skills_array.size(); number++)
	{
		if (player_skills_array[number] == WoodSkinEnum)
		{
			if (player_skills_level_array[WoodSkinEnum] >= 1)
			{
				if (player_skills_rune_array[WoodSkinEnum] == ThirdRune_E)
				{
					bonus_defense_percent_overall += listAllSkills[WoodSkinEnum]->GetPassiveBonusValue(GetLevelSpecificSkill(WoodSkinEnum), current_class, player_skills_rune_array[WoodSkinEnum]);
				}
				else
				{
					bonus_defense_percent += listAllSkills[WoodSkinEnum]->GetPassiveBonusValue(GetLevelSpecificSkill(WoodSkinEnum), current_class, player_skills_rune_array[WoodSkinEnum]);
				}
				if (player_skills_rune_array[WoodSkinEnum] == SecondRune_E)
				{
					bonus_health_percent += 5;
				}
			}
		}
		else if (player_skills_array[number] == SwiftnessEnum)
		{
			if (player_is_out_of_battle)
			{
				if (player_skills_level_array[SwiftnessEnum] >= 1)
				{
					bonus_movement_speed_percent_after_all += listAllSkills[SwiftnessEnum]->GetPassiveBonusValue(GetLevelSpecificSkill(SwiftnessEnum), current_class, player_skills_rune_array[SwiftnessEnum]);
				}
			}
			else if (player_skills_rune_array[SwiftnessEnum] == SecondRune_E)
			{
				bonus_movement_speed_percent_after_all += listAllSkills[SwiftnessEnum]->GetPassiveBonusValue(GetLevelSpecificSkill(SwiftnessEnum), current_class, player_skills_rune_array[SwiftnessEnum]) / 3;
			}
			if (player_skills_rune_array[SwiftnessEnum] == ThirdRune_E)
			{
				bonus_attack_speed_percent += 8;
			}
		}
		else if (player_skills_array[number] == LiquidBodyEnum)
		{
			if (player_skills_level_array[LiquidBodyEnum] >= 1)
			{
				if (clock_liquid_body.getElapsedTime().asSeconds() >= 0.5)
				{
					int timer = listAllSkills[LiquidBodyEnum]->GetPassiveBonusType();
					GivePlayerChangeStat(HpRecovery, timer,damage_received_liquid_body*listAllSkills[LiquidBodyEnum]->GetPassiveBonusValue(GetLevelSpecificSkill(LiquidBodyEnum), current_class, player_skills_rune_array[LiquidBodyEnum])/100/ timer);
					damage_received_liquid_body = 0;
					clock_liquid_body.restart();
				}
			}
		}
		else if (player_skills_array[number] == ReinforcementEnum)
		{
			if (player_skills_rune_array[SwiftnessEnum] == FirstRune_E)
			{
				bonus_shield_capacity_addition_percent += 25;
			}
			else if(player_skills_rune_array[SwiftnessEnum] == SecondRune_E)
			{
				bonus_armor_on_shield += 15;
			}
		}
		else if (player_skills_array[number] == ReviveEnum)
		{
			if (player_skills_rune_array[ReviveEnum] == SecondRune_E)
			{
				GivePlayerChangeStat(ShieldCapacity, -1, 40);
			}
			else
			{
				GivePlayerChangeStat(ShieldCapacity, -1, 25);
			}
		}
	}
}

void Player::OutOfBattleGestion()
{
	if (clock_out_of_battle.getElapsedTime().asSeconds() >= time_before_out_of_battle)
	{
		float time_passed_in_battle = clock_feat_in_combat.getElapsedTime().asSeconds();
		FeatGestion::instance()->Action(F_TimeBattle, time_passed_in_battle);
		clock_feat_in_combat.restart();
		player_is_out_of_battle = true;
		achievement_gestion.ActionInAchievement(A_InCombat,-1);
	}
	else
	{
		achievement_gestion.ActionInAchievement(A_InCombat,1);
		player_is_out_of_battle = false;
	}
}

void Player::PlayerDidCombatAction()
{
	clock_out_of_battle.restart();
}

void Player::ResetASkill(int skill_reset)
{
	for (int number = 0; number < 9; number++)
	{
		if (player_skills_array[number] == skill_reset)
		{
			player_skill_ready[number] = true;
			player_skill_clock[number].restart();
			skill_cooldown_clock[number];
			skill_cooldown_rectangle_created[number] = false;
		}
	}
}

void Player::ChangeASkillCooldown(int skill_cooldown_changing, float new_cooldown)
{
	if (new_cooldown > 0)
	{
		for (int number = 0; number < 9; number++)
		{
			if (player_skills_array[number] == skill_cooldown_changing)
			{
				player_skill_clock[number].restart();
				skill_cooldown_clock[number].restart();
				skill_cooldown_changed[number] = true;
				player_skill_cooldown[number] = new_cooldown;
				array_skill_cooldown[number] = new_cooldown;
				skill_cooldown_rectangle_created[number] = true;
			}
		}
	}
}

void Player::GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking)
{
	if (push_force < force_of_pushing)
	{
		sf::Vector2f position_monster = GetCurrentPosition();
		if (GlobalFunction::GetDistanceBetweenTwoPositions(origin_of_propulsion_receveid, position_monster) < distance_being_pushed_received)
		{
			StopLooting();
			distance_being_pushed = distance_being_pushed_received;
			being_pushed = true;
			push_force = force_of_pushing;
			push_origin = origin_of_propulsion_receveid;
			push_rotation = GlobalFunction::GetRotationBetweenTwoPositions(origin_object_blocking, position_monster);
		}
	}
}

float Player::GetDefense()
{
	return player_defense;
}

sf::Vector2f Player::GetPositionViewPlayer()
{
	return positition_view_of_player;
}

void Player::CalculateView()
{
	sf::Vector2f position = GetCurrentPosition();

	positition_view_of_player.x = std::round(position.x - (ListObjectsSingleton::instance()->GetSizeWindow().x / 2 / Proportion));
	positition_view_of_player.y = std::round(position.y - (ListObjectsSingleton::instance()->GetSizeWindow().y / 2 / Proportion));

	if (positition_view_of_player.x < 0)
		positition_view_of_player.x = 0;
	if (positition_view_of_player.y < 0)
		positition_view_of_player.y = 0;
}

bool Player::CheckIfPlayerHasSkill(int SkillEnum)
{
	if (player_skills_level_array[SkillEnum] > 0)
	{
		for (size_t i = 0; i < listAllArmors[number_current_armor]->ReturnArmorNumberSkills(); i++)
		{
			if (player_skills_array[i] == SkillEnum)
			{
				return true;
			}
		}
	}
	return false;
}

void Player::PutItBackInQuadtree()
{
	need_to_be_put_in_quadtree = true;
}

bool Player::CheckIfNeedGoBackQuadtree()
{
	bool holder = need_to_be_put_in_quadtree;
	need_to_be_put_in_quadtree = false;
	return holder;
}

void Player::TeleportEntity(sf::Vector2f position, int TypeTeleportation)
{
	if (position.x < 0)
	{
		position.x = 1;
	}
	if (position.y < 0)
	{
		position.y = 1;
	}

	position_going_to = position;
	player_image.setPosition(position);
}

void Player::AddMaterialToList(std::shared_ptr<CollisionalObject> object)
{
	int id_object = object->GetId();
	if (CheckIDMaterial(id_object))
	{
		listPickableMaterial.push_back(object);
		ListPickableMaterialID.push_back(id_object);
	}
}

bool Player::CheckIDMaterial(int id)
{
	std::vector<int>::iterator iterator = ListPickableMaterialID.begin();
	while (iterator != ListPickableMaterialID.end())
	{
		if ((*iterator) == id)
		{
			return false;
		}
		iterator++;
	}
	return true;
}

void Player::UpdateListPickableMaterial()
{
	sf::FloatRect player_bounds = player_image.getGlobalBounds();
	int counter = 0;
	std::list<std::shared_ptr<CollisionalObject>>::iterator iterator = listPickableMaterial.begin();
	while (iterator != listPickableMaterial.end())
	{
		if ((*iterator)->IsNeedToDelete())
		{
			ListPickableMaterialID.erase(ListPickableMaterialID.begin() + counter);
			listPickableMaterial.erase(iterator++);
		}
		else
		{
			if (player_bounds.intersects((*iterator)->GetCollisionRect()))
			{
				counter++;
				iterator++;
			}
			else
			{
				ListPickableMaterialID.erase(ListPickableMaterialID.begin() + counter);
				listPickableMaterial.erase(iterator++);
			}
		}
	}
}

void Player::LootOnFloor()
{
	if (!is_looting && !being_pushed && !player_is_stunned)
	{
		if (listPickableMaterial.size() > 0)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				float distance_material = 1000;
				sf::Vector2f position_player = GetCurrentPosition();

				std::list<std::shared_ptr<CollisionalObject>>::iterator i = listPickableMaterial.begin();
				while (i != listPickableMaterial.end())
				{
					if (GlobalFunction::GetDistanceBetweenTwoPositions(position_player, (*i)->GetCurrentPosition()) < distance_material)
					{
						object_looting.reset();
						object_looting = (*i);
					}
					i++;
				}
				is_looting = true;
				clock_looting.restart();
			}
		}
	}
}

void Player::LootingGestion(sf::Vector2f position_view_player)
{
	if (is_looting)
	{
		if(object_looting->IsNeedToDelete())
		{
			is_looting = false;
			object_looting.reset();
		}
		if (clock_looting.getElapsedTime().asSeconds() >= time_to_loot)
		{
			is_looting = false;
			if (object_looting->GetTypeCollisionalObject() == Material_E)
			{
				if (listScrollEquipped[CollectMaterialOneRun])
				{
					if (GlobalFunction::getRandomRange(1, 1000) > listScrollBonus[CollectMaterialOneRun] * 10)
					{
						inventory[I_Material][object_looting->GetTypeMaterial()]++;
					}
					else
					{
						inventory[I_Material][object_looting->GetTypeMaterial()] += 2;
					}
				}
				else
				{
					inventory[I_Material][object_looting->GetTypeMaterial()]++;
				}
				achievement_gestion.ActionInAchievement(A_MaterialCollected, 1);
			}
			else if (object_looting->GetTypeCollisionalObject() == LootBag_E)
			{
				std::vector<std::shared_ptr<EquipmentBase>> ListLoot = object_looting->GetListEquipmentLoot();
				for (int i = 0; i < ListLoot.size(); i++)
				{
					if (ListLoot[i]->GetCategoryEquipment() == RingEquipment_E)
					{
						GiveRing(ListLoot[i]);
					}
				}
				ListLoot.clear();
			}

			SoundGestion::instance()->AddSound("SoundLooting.wav", 100, false);

			object_looting->SetToDelete();
			object_looting.reset();
		}

		bar_looting_progress.setSize(sf::Vector2f(size_bar_looting.x * (clock_looting.getElapsedTime().asSeconds() / time_to_loot), size_bar_looting.y));
		bar_looting_progress.setPosition(sf::Vector2f(position_bar_looting.x, position_bar_looting.y) + position_view_player);
		bar_looting.setPosition(position_bar_looting + position_view_player);
	}
}

void Player::StopLooting()
{
	is_looting = false;
	object_looting.reset();
}

#pragma region Equipments
void Player::GiveWeapon(std::shared_ptr<E_Weapon> weapon)
{ 
	if (weapon->GetRarityItem() == Legendary_E)
	{
		FeatGestion::instance()->Action(F_LegendaryGotten, 1);
	}
	if (language == English_E)
	{
		NotificationSystem::instance()->AddNoticeToList("You received a weapon.");
	}
	else
	{
		NotificationSystem::instance()->AddNoticeToList("Vous avez reçu une arme.");
	}
	listEquipment.push_back(weapon);
	UpdatePlayerArrayTalentIncreasement();
}

void Player::GiveHat(std::shared_ptr<E_WizardHat> hat)
{
	if (hat->GetRarityItem() == Legendary_E)
	{
		FeatGestion::instance()->Action(F_LegendaryGotten, 1);
	}
	if (language == English_E)
	{
		NotificationSystem::instance()->AddNoticeToList("You received a wizard hat.");
	}
	else
	{
		NotificationSystem::instance()->AddNoticeToList("Vous avez reçu un chapeau de magicien.");
	}
	UpdatePlayerArraySkillIncreasement();
	listEquipment.push_back(hat);
}

void Player::GiveRing(std::shared_ptr<EquipmentBase> ring)
{
	if (ring->GetRarityItem() == Legendary_E)
	{
		FeatGestion::instance()->Action(F_LegendaryGotten, 1);
	}
	if (language == English_E)
	{
		NotificationSystem::instance()->AddNoticeToList("You received a ring.");
	}
	else
	{
		NotificationSystem::instance()->AddNoticeToList("Vous avez reçu un anneau.");
	}
	listEquipment.push_back(ring);
}

void Player::GivePet(std::shared_ptr<PetBase> new_pet)
{
	if (listPets.size() <= 10)
	{
		if (current_pet == NULL)
		{
			new_pet->Init(shared_from_this());
			current_id_pet = new_pet->GetPetId();
			current_pet = new_pet;
		}

		if (language == English_E)
		{
			NotificationSystem::instance()->AddNoticeToList("You received a pet.");
		}
		else
		{
			NotificationSystem::instance()->AddNoticeToList("Vous avez reçu un familier.");
		}
		listPets.push_back(new_pet);
	}

	else
	{
		if (language == English_E)
		{
			NotificationSystem::instance()->AddNoticeToList("You received a pet, but you didn't have any spot for him.");
		}
		else
		{
			NotificationSystem::instance()->AddNoticeToList("Vous avez reçu un familier, mais vous n'avez pu de place pour lui.");
		}
	}

	if (listPets.size() == 8)
	{
		if (language == English_E)
		{
			NotificationSystem::instance()->AddNoticeToList("You have one spot left for a pet. You might want to release one.");
		}
		else
		{
			NotificationSystem::instance()->AddNoticeToList("Vous avez une place restante un familier. Vous devriez peut-être en relâcher un.");
		}
	}
}

void Player::DeleteAPet(int position_pet_in_list)
{
	if (position_pet_in_list < listPets.size())
	{
		listPets.erase(listPets.begin() + position_pet_in_list);
	}
}

void Player::ChangeCurrentPet(int position_pet_in_list)
{
	if (position_pet_in_list < listPets.size())
	{
		current_pet = listPets[position_pet_in_list];
		current_id_pet = current_pet->GetPetId();
		current_pet->Init(shared_from_this());
	}
}

void Player::ChangeCurrentRing1(int position_weapon_in_list)
{
	if (listEquipment[position_weapon_in_list]->GetCategoryEquipment() == RingEquipment_E)
	{
		current_ring1_index = listEquipment[position_weapon_in_list]->GetIdEquipment();
		current_ring1 = listEquipment[position_weapon_in_list];
	}
}

void Player::ChangeCurrentRing2(int position_weapon_in_list)
{
	if (listEquipment[position_weapon_in_list]->GetCategoryEquipment() == RingEquipment_E)
	{
		current_ring2_index = listEquipment[position_weapon_in_list]->GetIdEquipment();
		current_ring2 = listEquipment[position_weapon_in_list];
	}
}

void Player::ChangeCurrentWeapon(int position_weapon_in_list)
{
	if (listEquipment[position_weapon_in_list]->GetCategoryEquipment() == WeaponEquipment_E)
	{
		current_weapon_index = listEquipment[position_weapon_in_list]->GetIdEquipment();
		current_weapon = listEquipment[position_weapon_in_list];
	}
	UpdatePlayerStats();
	UpdatePlayerArrayTalentIncreasement();
}

void Player::ChangeCurrentHat(int position_weapon_in_list)
{
	if (listEquipment[position_weapon_in_list]->GetCategoryEquipment() == WizardHatEquipment_E)
	{
		current_hat_index = listEquipment[position_weapon_in_list]->GetIdEquipment();
		current_hat = listEquipment[position_weapon_in_list];
	}
	UpdatePlayerStats();
	UpdatePlayerArraySkillIncreasement();
}

#pragma endregion Equipments

void Player::GivePlayerNewClass(int new_class)
{
	current_class = new_class;
	player_image.setTexture(player_texture[current_class]);
}

void Player::GiveNewOpenedInterface(int new_interface) 
{ 
	if (current_opened_interface != new_interface)
	{
		current_opened_interface = new_interface;
	}
	else
	{
		current_opened_interface = NoInterface_E;
	}
}

float Player::GetProjectileRangeBonus()
{
	float bonus_range = 0;
	if (player_array_talent_level[SharpShooter_E] > 0)
	{
		bonus_range += listAllTalents[SharpShooter_E]->GetTalentBonus(player_array_talent_level[SharpShooter_E] + player_array_talent_increasement[SharpShooter_E]);
	}
	if (listScrollEquipped[MonsterHitOneRun])
	{
		bonus_range += listScrollBonus[MonsterHitOneRun];
	}
	if (listAllArmors[number_current_armor]->ReturnArmorBonusType() == A_Range)
	{
		bonus_range += listAllArmors[number_current_armor]->ReturnArmorBonusNumber();
	}
	return bonus_range;
}

float Player::GetSkillDamageBonus()
{
	if (player_number_skills_casted == 4)
	{
		player_number_skills_casted = 0;
		return listAllTalents[UnleashedPower_E]->GetTalentBonus(player_array_talent_level[UnleashedPower_E] + player_array_talent_increasement[UnleashedPower_E]);
	}
	return 0;
}

void Player::OnHitGestion(int id_object, float damage_dealt,int type_object,int type_projectile)
{
	SoundGestion::instance()->AddSound("SoundMonsterHit.wav", 100, false);
	PlayerDidCombatAction();
	damage_dealt_in_second += damage_dealt;

	achievement_gestion.ActionInAchievement(A_MonsterHit, 1);

	if (type_projectile == BasicAttackProjectile_E)
	{
		if (player_array_talent_level[Hasty_E] + player_array_talent_increasement[Hasty_E] > 0)
		{
			clock_talent_hasty.restart();
		}
		if (CheckIfPlayerHasSkill(ReinforcementEnum))
		{
			ShieldObject(player_maximum_health*listAllSkills[ReinforcementEnum]->GetPassiveBonusValue(GetLevelSpecificSkill(ReinforcementEnum), current_class, player_skills_rune_array[ReinforcementEnum])/100);
			if (player_skills_rune_array[ReinforcementEnum] == ThirdRune_E)
			{
				GivePlayerChangeStat(DefenseAddition, 3, 2 + 1 * (GetLevelSpecificSkill(ReinforcementEnum) - 1));
			}
		}
	}

	if (player_array_talent_level[Rampage_E] + player_array_talent_increasement[Rampage_E] > 0)
	{
		if (rampage_bonus < 3)
		{
			rampage_bonus++;
			sf::Clock clock;
			listClockRampage.push_back(clock);
		}
		else
		{
			listClockRampage.erase(listClockRampage.begin());
			sf::Clock clock;
			listClockRampage.push_back(clock);
		}
	}
}

void Player::TalentBuffGestion()
{
	for (int i = 0; i < rampage_bonus; i)
	{
		if (listClockRampage[i].getElapsedTime().asSeconds() > 2)
		{
			rampage_bonus--;
			listClockRampage.erase(listClockRampage.begin() + i);
			continue;
		}
		bonus_attack_damage_percent_overall += listAllTalents[Rampage_E]->GetTalentBonus(player_array_talent_level[Rampage_E] + player_array_talent_increasement[Rampage_E]);
		i++;
	}

	if (player_array_talent_level[Hasty_E] + player_array_talent_increasement[Hasty_E] > 0 && clock_talent_hasty.getElapsedTime().asSeconds() <= 2)
	{
		bonus_movement_speed_percent += listAllTalents[Hasty_E]->GetTalentBonus(player_array_talent_level[Hasty_E] + player_array_talent_increasement[Hasty_E]);
	}
}

float Player::GetSpecificTalentBonus(int type_talent)
{
	return listAllTalents[type_talent]->GetTalentBonus(player_array_talent_level[type_talent]+ player_array_talent_increasement[type_talent]);
}

float Player::GetSlowPercentDebuffOnHit()
{
	return GetSpecificTalentBonus(TranquilizerAttack_E);
}

float Player::GetSlowDurationDebuffOnHit()
{
	return 1.5;
}

float Player::GetStunDurationDebuffOnHit()
{
	return GetSpecificTalentBonus(DisablingAttack_E);
}

void Player::UpdatePlayerArrayTalentIncreasement()
{
	for (int i = 0; i < player_array_talent_increasement.size(); i++)
	{
		player_array_talent_increasement[i] = 0;
	}

	if (current_weapon != NULL)
	{
		std::vector<int> listTalentIncreased = current_weapon->GetListTalentIncreasement();
		for (int i = 0; i < listTalentIncreased.size(); i++)
		{
			player_array_talent_increasement[listTalentIncreased[i]]++;
		}
	}
}

void Player::UpdatePlayerArraySkillIncreasement()
{
	for (int i = 0; i < player_skill_increasement.size(); i++)
	{
		player_skill_increasement[i] = 0;
	}

	if (current_hat != NULL)
	{
		std::vector<int> listSkillIncreasement = current_hat->GetListSkillIncreasement();
		std::vector<int> listSkillIncreasementLevel = current_hat->GetListSkillIncreasementLevel();
		for (int i = 0; i < listSkillIncreasement.size(); i++)
		{
			player_skill_increasement[listSkillIncreasement[i]] += listSkillIncreasementLevel[i];
		}
	}
	else
	{
	}
	UpdatePlayerStats();
}

int Player::GetLevelSpecificSkill(int type_skill)
{
	return player_skills_level_array[type_skill] + player_skill_increasement[type_skill];
}

void Player::AddToDrawListPet()
{
	if (current_pet != NULL)
	{
		DrawGestion::instance()->AddObjectToList(current_pet);
	}
}

void Player::Draw(sf::RenderWindow &window)
{
	if (player_is_stunned)
	{
		window.draw(stun_bar);
	}
	window.draw(player_image);
	window.draw(player_maximum_health_bar);
	window.draw(player_health_bar);
	window.draw(rect_shield_player_bar);
	window.draw(sprite_health_bar_interface);
}

void Player::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(player_image.getPosition() + sf::Vector2f(0, GetSize().y / 2 - 1));
	window.draw(shadow);
}

sf::Vector2f Player::GetCurrentPositionShadow() 
{ 
	return shadow.getPosition() + sf::Vector2f(0,0); 
}

#pragma region Save
void Player::SaveInformations()
{
	int current_save = ListObjectsSingleton::instance()->GetCurrentSave();
	std::ofstream ofs;
	std::cout << "saved on save " << current_save+1 << std::endl;
	if (current_save == FirstSave_E)
	{
		ofs.open("Ressource1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Weapons1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("WizardHats1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Rings1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();		
		ofs.open("Pet1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}
	else if (current_save == SecondSave_E)
	{
		ofs.open("Ressource2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Weapons2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("WizardHats2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Rings2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Pet2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}
	else
	{
		ofs.open("Ressource3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Weapons3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("WizardHats3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Rings3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Pet3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}

	ofs.close();


	std::ofstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Ressource1.txt", std::fstream::app);
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Ressource2.txt", std::fstream::app);
	}
	else
	{
		myfile.open("Ressource3.txt", std::fstream::app);
	}

	myfile.seekp(std::ios::end);
	myfile << "ModifyAtYourOwnRisk";
	myfile << std::endl;
	myfile << std::endl;

	if (true)
	{
		myfile << "CurrentArmor";
		myfile << std::endl;
		myfile << "<";
		std::string str("" + std::to_string(number_current_armor));
		myfile << str;
		myfile << ">";
		myfile << std::endl;
	}

	if (true)
	{
		myfile << "CurrentWeaponIndex";
		myfile << std::endl;
		myfile << "<";
		std::string str("" + std::to_string(current_weapon_index));
		myfile << str;
		myfile << ">";
		myfile << std::endl;
	}

	if (true)
	{
		myfile << "CurrentHatIndex";
		myfile << std::endl;
		myfile << "<";
		std::string str("" + std::to_string(current_hat_index));
		myfile << str;
		myfile << ">";
		myfile << std::endl;
	}

	if (true)
	{
		myfile << "PlayerExperience";
		myfile << std::endl;
		myfile << "<";
		int experience = player_experience;
		std::string str("" + std::to_string(experience));
		myfile << str;
		myfile << ">";
		myfile << std::endl;
	}

	if (true)
	{
		myfile << "PlayerLevel";
		myfile << std::endl;
		myfile << "<";
		int experience = player_level;
		std::string str("" + std::to_string(experience));
		myfile << str;
		myfile << ">";
		myfile << std::endl;
	}

	if (true)
	{
		myfile << "PlayerHealth";
		myfile << std::endl;
		myfile << "<";
		int health = player_current_health;
		std::string str("" + std::to_string(health));
		myfile << str;
		myfile << ">";
		myfile << std::endl;
	}

	if (true)
	{
		myfile << "PlayerMoney";
		myfile << std::endl;
		myfile << "<";
		int money = player_money;
		std::string str("" + std::to_string(money));
		myfile << str;
		myfile << ">";
		myfile << std::endl;
	}

	myfile << "ScrollEquipped";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < listScrollEquipped.size(); i++)
	{
		if (listScrollEquipped[i])
		{
			myfile << "true";
			myfile << std::string(" ");
		}
		else
		{
			myfile << "false";
			myfile << std::string(" ");
		}

	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "SkillArray";
	myfile << std::endl;
	myfile << "<";
	for (int i = 0; i < player_skills_array.size(); i++)
	{
		std::string str("" +std::to_string(player_skills_array[i]));
		myfile << str;
		if (i + 1 != player_skills_array.size())
		{
			myfile << ".";
		}
	}
	myfile << ">";
	myfile << std::endl;

	myfile << "SkillLevelArray";
	myfile << std::endl;
	myfile << "<";
	for (int i = 0; i < player_skills_level_array.size(); i++)
	{
		std::string str("" + std::to_string(player_skills_level_array[i]));
		myfile << str;
		if (i + 1 != player_skills_level_array.size())
		{
			myfile << ".";
		}
	}
	myfile << ">";
	myfile << std::endl;

	myfile << "SkillIncreasementArray";
	myfile << std::endl;
	myfile << "<";
	for (int i = 0; i < player_skill_increasement.size(); i++)
	{
		std::string str("" + std::to_string(player_skill_increasement[i]));
		myfile << str;
		if (i + 1 != player_skill_increasement.size())
		{
			myfile << ".";
		}
	}
	myfile << ">";
	myfile << std::endl;

	myfile << "SkillLevelIncreasementArray";
	myfile << std::endl;
	myfile << "<";
	for (int i = 0; i < player_modified_skill_level_list.size(); i++)
	{
		std::string str("" + std::to_string(player_modified_skill_level_list[i]));
		myfile << str;
		if (i + 1 != player_modified_skill_level_list.size())
		{
			myfile << ".";
		}
	}
	myfile << ">";
	myfile << std::endl;

	myfile << "FragmentsArray";
	myfile << std::endl;
	myfile << "<";
	for (int i = 0; i < player_number_fragments.size(); i++)
	{
		std::string str("" + std::to_string(player_number_fragments[i]));
		myfile << str;
		if (i + 1 != player_number_fragments.size())
		{
			myfile << ".";
		}
	}
	myfile << ">";
	myfile << std::endl;
	
	myfile << "ArmorArray";
	myfile << std::endl;
	myfile << "<";
	for (int i = 0; i < player_armor_array.size(); i++)
	{
		std::string str("" + std::to_string(player_armor_array[i]));
		myfile << str;
		if (i + 1 != player_armor_array.size())
		{
			myfile << ".";
		}
	}
	myfile << ">";
	myfile << std::endl;

	myfile << "TalentArray";
	myfile << std::endl;
	myfile << "<";
	for (int i = 0; i < player_array_talent_level.size(); i++)
	{
		std::string str("" + std::to_string(player_array_talent_level[i]));
		myfile << str;
		if (i + 1 != player_array_talent_level.size())
		{
			myfile << ".";
		}
	}
	myfile << ">";
	myfile << std::endl;

	myfile << "TalentPointArray";
	myfile << std::endl;
	myfile << "<";
	for (int i = 0; i < player_array_talent_points_used.size(); i++)
	{
		std::string str("" + std::to_string(player_array_talent_points_used[i]));
		myfile << str;
		if (i + 1 != player_array_talent_points_used.size())
		{
			myfile << ".";
		}
	}
	myfile << ">";
	myfile << std::endl;

	myfile << "TalentIncreasementArray";
	myfile << std::endl;
	myfile << "<";
	for (int i = 0; i < player_array_talent_increasement.size(); i++)
	{
		std::string str("" + std::to_string(player_array_talent_increasement[i]));
		myfile << str;
		if (i + 1 != player_array_talent_increasement.size())
		{
			myfile << ".";
		}
	}
	myfile << ">";
	myfile << std::endl;

	myfile << "GemArray";
	myfile << std::endl;
	myfile << "<";
	for (int i = 0; i < player_gem_array.size(); i++)
	{
		int x = player_gem_array[i].x;
		std::string str("" + std::to_string(x));
		myfile << str;
		myfile << "|";
		int y = player_gem_array[i].y;
		std::string str1("" + std::to_string(y));
		myfile << str1;
		if (i + 1 != player_gem_array.size())
		{
			myfile << ".";
		}
	}
	myfile << ">";
	myfile << std::endl;

	myfile << "ActiveGemArray";
	myfile << std::endl;
	myfile << "<";
	for (int i = 0; i < listAllActiveGems.size(); i++)
	{
		std::string str("" + std::to_string(listAllActiveGems[i]));
		myfile << str;
		if (i + 1 != listAllActiveGems.size())
		{
			myfile << ".";
		}
	}
	myfile << ">";
	myfile << std::endl;

	myfile << "ListRuneAvailable";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < NUMBERSKILL; i++)
	{
		for (int ii = 0; ii < listRuneAvailable[i].size(); ii++)
		{
			if(listRuneAvailable[i][ii])
			{
				myfile << "true";
				myfile << std::string(" ");
			}
			else
			{
				myfile << "false";
				myfile << std::string(" ");
			}
		}
		myfile << " Next ";
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "ListRuneUsing";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < NUMBERSKILL; i++)
	{
		std::string str("" + std::to_string(player_skills_rune_array[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile.close();

	for (int i = 0; i < listEquipment.size(); i++)
	{
		listEquipment[i]->SaveInformation(current_ring1_index,current_ring2_index,current_weapon_index,current_hat_index);
	}

	for (int i = 0; i < listPets.size(); i++)
	{
		listPets[i]->SaveInformation(current_id_pet);
	}

	SaveInventoryInformation();
	achievement_gestion.SaveInformation(current_save);
	SaveCharacteristicInformation();
	FeatGestion::instance()->Save(current_save);
	ListObjectsSingleton::instance()->SaveParameter();
}

void Player::LoadInformations()
{
	int current_save = ListObjectsSingleton::instance()->GetCurrentSave();
	std::ifstream myfile;

	std::cout << "loaded on save " << current_save + 1 << std::endl;
	if (current_save == FirstSave_E)
	{
		myfile.open("Ressource1.txt");
	}
	else if(current_save == SecondSave_E)
	{
		myfile.open("Ressource2.txt");
	}
	else
	{
		myfile.open("Ressource3.txt");
	}

	if (myfile.is_open())
	{
			std::string first_str;
			myfile >> first_str;
		if (first_str == "ModifyAtYourOwnRisk")
		{
			std::string str;
			myfile >> str;
			if (str == "CurrentArmor")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					std::vector<char> listUnity;
					while (str[i] != 46 && str[i] != 62)
					{
						listUnity.push_back(str[i]);
						i++;
					}
					number_current_armor = GlobalFunction::GetNumberFromFile(listUnity);
				}
			}

			myfile >> str;
			if (str == "CurrentWeaponIndex")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					std::vector<char> listUnity;
					while (str[i] != 46 && str[i] != 62)
					{
						listUnity.push_back(str[i]);
						i++;
					}
					current_weapon_index = GlobalFunction::GetNumberFromFile(listUnity);
				}
			}

			myfile >> str;
			if (str == "CurrentHatIndex")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					std::vector<char> listUnity;
					while (str[i] != 46 && str[i] != 62)
					{
						listUnity.push_back(str[i]);
						i++;
					}
					current_hat_index = GlobalFunction::GetNumberFromFile(listUnity);
				}
			}

			str.clear();
			myfile >> str;
			if (str == "PlayerExperience")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					std::vector<char> listUnity;
					while (str[i] != 46 && str[i] != 62)
					{
						listUnity.push_back(str[i]);
						i++;
					}
					GetExp(GlobalFunction::GetNumberFromFile(listUnity));
				}
			}

			str.clear();
			myfile >> str;
			if (str == "PlayerLevel")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					std::vector<char> listUnity;
					while (str[i] != 46 && str[i] != 62)
					{
						listUnity.push_back(str[i]);
						i++;
					}
					player_level = GlobalFunction::GetNumberFromFile(listUnity);
				}
			}

			str.clear();
			myfile >> str;
			if (str == "PlayerHealth")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					std::vector<char> listUnity;
					while (str[i] != 46 && str[i] != 62)
					{
						listUnity.push_back(str[i]);
						i++;
					}
					player_current_health = GlobalFunction::GetNumberFromFile(listUnity);
				}
			}

			str.clear();
			myfile >> str;
			if (str == "PlayerMoney")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					std::vector<char> listUnity;
					while (str[i] != 46 && str[i] != 62)
					{
						listUnity.push_back(str[i]);
						i++;
					}
					player_money = GlobalFunction::GetNumberFromFile(listUnity);
				}
			}

			myfile >> str;
			if (str == "ScrollEquipped")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						if (str == "true")
						{
							listScrollEquipped[counter] = true;
							counter++;
							myfile >> str;
						}
						else
						{
							listScrollEquipped[counter] = false;
							counter++;
							myfile >> str;
						}
					}
				}
			}

			str.clear();
			myfile >> str;
			if (str == "SkillArray")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					int counter_array = 0;
					while (str[i] != 62)
					{
						std::vector<char> listUnity;
						while (str[i] != 46 && str[i] != 62)
						{
							listUnity.push_back(str[i]);
							i++;
						}
						player_skills_array[counter_array] = GlobalFunction::GetNumberFromFile(listUnity);
						counter_array++;
						if (str[i] == 46)
						{
							i++;
						}
					}
				}
			}

			str.clear();
			myfile >> str;
			if (str == "SkillLevelArray")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					int counter_array = 0;
					while (str[i] != 62)
					{
						std::vector<char> listUnity;
						while (str[i] != 46 && str[i] != 62)
						{
							listUnity.push_back(str[i]);
							i++;
						}

						int number = GlobalFunction::GetNumberFromFile(listUnity);
						if (number > 0)
						{
							FeatGestion::instance()->Action(F_SkillLeveled, 1);
						}
						player_skills_level_array[counter_array] = number;
						counter_array++;
						if (str[i] == 46)
						{
							i++;
						}
					}
				}
			}

			str.clear();
			myfile >> str;
			if (str == "SkillIncreasementArray")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					int counter_array = 0;
					while (str[i] != 62)
					{
						std::vector<char> listUnity;
						while (str[i] != 46 && str[i] != 62)
						{
							listUnity.push_back(str[i]);
							i++;
						}
						player_skill_increasement[counter_array] = GlobalFunction::GetNumberFromFile(listUnity);
						counter_array++;
						if (str[i] == 46)
						{
							i++;
						}
					}
				}
			}

			str.clear();
			myfile >> str;
			if (str == "SkillLevelIncreasementArray")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					int counter_array = 0;
					while (str[i] != 62)
					{
						std::vector<char> listUnity;
						while (str[i] != 46 && str[i] != 62)
						{
							listUnity.push_back(str[i]);
							i++;
						}
						player_modified_skill_level_list[counter_array] = GlobalFunction::GetNumberFromFile(listUnity);
						counter_array++;
						if (str[i] == 46)
						{
							i++;
						}
					}
				}
			}
			
			str.clear();
			myfile >> str;
			if (str == "FragmentsArray")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					int counter_array = 0;
					while (str[i] != 62)
					{
						std::vector<char> listUnity;
						while (str[i] != 46 && str[i] != 62)
						{
							listUnity.push_back(str[i]);
							i++;
						}
						player_number_fragments[counter_array] = GlobalFunction::GetNumberFromFile(listUnity);
						counter_array++;
						if (str[i] == 46)
						{
							i++;
						}
					}
				}
			}

			str.clear();
			myfile >> str;
			if (str == "ArmorArray")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					int counter_array = 0;
					while (str[i] != 62)
					{
						std::vector<char> listUnity;
						while (str[i] != 46 && str[i] != 62)
						{
							listUnity.push_back(str[i]);
							i++;
						}
						player_armor_array[counter_array] = GlobalFunction::GetNumberFromFile(listUnity);
						counter_array++;
						if (str[i] == 46)
						{
							i++;
						}
					}
				}
			}

			str.clear();
			myfile >> str;
			if (str == "TalentArray")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					int counter_array = 0;
					while (str[i] != 62)
					{
						std::vector<char> listUnity;
						while (str[i] != 46 && str[i] != 62)
						{
							listUnity.push_back(str[i]);
							i++;
						}
						player_array_talent_level[counter_array] = GlobalFunction::GetNumberFromFile(listUnity);
						counter_array++;
						if (str[i] == 46)
						{
							i++;
						}
					}
				}
			}

			str.clear();
			myfile >> str;
			if (str == "TalentPointArray")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					int counter_array = 0;
					while (str[i] != 62)
					{
						std::vector<char> listUnity;
						while (str[i] != 46 && str[i] != 62)
						{
							listUnity.push_back(str[i]);
							i++;
						}
						player_array_talent_points_used[counter_array] = GlobalFunction::GetNumberFromFile(listUnity);
						counter_array++;
						if (str[i] == 46)
						{
							i++;
						}
					}
				}
			}

			str.clear();
			myfile >> str;
			if (str == "TalentIncreasementArray")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					int counter_array = 0;
					while (str[i] != 62)
					{
						std::vector<char> listUnity;
						while (str[i] != 46 && str[i] != 62)
						{
							listUnity.push_back(str[i]);
							i++;
						}
						player_array_talent_increasement[counter_array] = GlobalFunction::GetNumberFromFile(listUnity);
						counter_array++;
						if (str[i] == 46)
						{
							i++;
						}
					}
				}
			}

			str.clear();
			myfile >> str;
			if (str == "GemArray")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					int counter_array = 0;
					while (str[i] != 62)
					{
						std::vector<char> listUnity;
						while (str[i] != 46 && str[i] != 62)
						{
							listUnity.push_back(str[i]);
							i++;
						}
						player_gem_array.push_back(GlobalFunction::GetVectorFromFile(listUnity));
						counter_array++;
						if (str[i] == 46)
						{
							i++;
						}
					}
				}
			}

			str.clear();
			myfile >> str;
			if (str == "ActiveGemArray")
			{
				str.clear();
				myfile >> str;

				int i = 0;

				if (str[i] == 60)
				{
					i++;
					int counter_array = 0;
					while (str[i] != 62)
					{
						std::vector<char> listUnity;
						while (str[i] != 46 && str[i] != 62)
						{
							listUnity.push_back(str[i]);
							i++;
						}
						listAllActiveGems.push_back(GlobalFunction::GetNumberFromFile(listUnity));
						counter_array++;
						if (str[i] == 46)
						{
							i++;
						}
					}
				}
			}

			myfile >> str;
			if (str == "ListRuneAvailable")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					int counter2 = 0;
					myfile >> str;
					while (str != ">")
					{
						while (str != ">" && str != "Next")
						{
							if (str == "true")
							{
								listRuneAvailable[counter][counter2] = true;
							}
							else
							{
								listRuneAvailable[counter][counter2] = false;
							}
							counter2++;
							myfile >> str;
						}
						counter2 = 0;
						counter++;
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "ListRuneUsing")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						player_skills_rune_array[counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}
		}
	}

	myfile.close();

	LoadWeaponInformations();
	LoadHatInformations();
	LoadInventoryInformation();
	achievement_gestion.LoadInformation(current_save);
	LoadCharacteristicInformation();
	LoadRingInformations();
	FeatGestion::instance()->Load(current_save);
	listFeatBonus = FeatGestion::instance()->GetListFeatBonus();

	listRuneAvailable[IceWallEnum][SecondRune_E] = true;
}

void Player::LoadWeaponInformations()
{
	int current_save = ListObjectsSingleton::instance()->GetCurrentSave();
	std::ifstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Weapons1.txt");
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Weapons2.txt");
	}
	else
	{
		myfile.open("Weapons3.txt");
	}

	if (myfile.is_open())
	{
		std::string str;
		myfile >> str;

		while (str == "NewWeapon")
		{
			std::vector<int> ListTalentBonuses;
			std::vector<int> ListTalentLevelBonuses;
			std::vector<int> listTypeBonus;
			std::vector<float> listBonus;
			std::vector<sf::Vector2f> listRangeBonus;
			std::vector<sf::String> listTalentString;
			int level_item;
			int type_weapon;
			int id_item;
			int rarity_item;
			bool is_current_weapon = false;

			myfile >> str;
			if (str == "IdItem")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						if(str == "true")
						{
							is_current_weapon = true;
						}
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "ListTalentBonuses")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						ListTalentBonuses.push_back(number);
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "ListTalentLevelBonuses")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						ListTalentLevelBonuses.push_back(number);
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "listTypeBonus")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						listTypeBonus.push_back(number);
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "listBonus")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						float number = GlobalFunction::ConvertStringToFloat(str);
						listBonus.push_back(number);
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "listRangeBonus")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						sf::Vector2f number;

						number.x= GlobalFunction::ConvertStringToFloat(str);
						myfile >> str;

						number.y = GlobalFunction::ConvertStringToFloat(str);
						myfile >> str;

						listRangeBonus.push_back(number);
					}
				}
			}

			myfile >> str;
			if (str == "listTalentString")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						listTalentString.push_back(str);
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "item_level")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					level_item = GlobalFunction::ConvertStringToInt(str);
					myfile >> str;
				}
			}

			myfile >> str;
			if (str == "type_weapon")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					type_weapon = GlobalFunction::ConvertStringToInt(str);
					myfile >> str;
				}
			}

			myfile >> str;
			if (str == "RarityItem")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					rarity_item = GlobalFunction::ConvertStringToInt(str);
					myfile >> str;
				}
			}

			std::shared_ptr<E_Weapon> weapon = std::shared_ptr<E_Weapon>(new E_Weapon(language, current_save));
			weapon->Init(level_item, listTypeBonus, listBonus, listRangeBonus, ListTalentBonuses, ListTalentLevelBonuses, type_weapon, listTalentString,ListObjectsSingleton::instance()->GetNewIDEquipment(), rarity_item);
			GiveWeapon(weapon);
			if (is_current_weapon)
			{
				current_weapon = weapon;
			}
			weapon.reset();
		}
	}
}

void Player::LoadHatInformations()
{
	int current_save = ListObjectsSingleton::instance()->GetCurrentSave();
	std::ifstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("WizardHats1.txt");
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("WizardHats2.txt");
	}
	else
	{
		myfile.open("WizardHats3.txt");
	}


	if (myfile.is_open())
	{
		std::string str;
		myfile >> str;

		while (str == "NewWeapon")
		{
			std::vector<int> ListTalentBonuses;
			std::vector<int> ListTalentLevelBonuses;
			std::vector<int> listTypeBonus;
			std::vector<float> listBonus;
			std::vector<sf::Vector2f> listRangeBonus;
			std::vector<sf::String> listTalentString;
			int level_item;
			int type_weapon;
			int id_item;
			int rarity_item;
			bool is_current_hat = false;

			myfile >> str;
			if (str == "IdItem")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						if(str == "true")
						{ 
							is_current_hat = true;
						}
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "ListTalentBonuses")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						ListTalentBonuses.push_back(number);
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "ListTalentLevelBonuses")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						ListTalentLevelBonuses.push_back(number);
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "listTypeBonus")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						listTypeBonus.push_back(number);
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "listBonus")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						float number = GlobalFunction::ConvertStringToFloat(str);
						listBonus.push_back(number);
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "listRangeBonus")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						sf::Vector2f number;

						number.x = GlobalFunction::ConvertStringToFloat(str);
						myfile >> str;

						number.y = GlobalFunction::ConvertStringToFloat(str);
						myfile >> str;

						listRangeBonus.push_back(number);
					}
				}
			}

			myfile >> str;
			if (str == "listTalentString")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						std::string reconstructed_string("");
						while (str[0] != 46 && str != ">")
						{
							reconstructed_string.insert(reconstructed_string.size(), std::string(" "));
							reconstructed_string.insert(reconstructed_string.size(), str);
							myfile >> str;
						}
						listTalentString.push_back(reconstructed_string);
						if (str != ">")
						{
							myfile >> str;
						}
					}
				}
			}

			myfile >> str;
			if (str == "item_level")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					level_item = GlobalFunction::ConvertStringToInt(str);
					myfile >> str;
				}
			}

			myfile >> str;
			if (str == "type_weapon")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					type_weapon = GlobalFunction::ConvertStringToInt(str);
					myfile >> str;
				}
			}
			myfile >> str;

			if (str == "RarityItem")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					rarity_item = GlobalFunction::ConvertStringToInt(str);
					myfile >> str;
				}
			}
			myfile >> str;

			std::shared_ptr<E_WizardHat> hat = std::shared_ptr<E_WizardHat>(new E_WizardHat(language, current_save));
			hat->Init(level_item, listTypeBonus, listBonus, listRangeBonus, ListTalentBonuses, ListTalentLevelBonuses, listTalentString,type_weapon,ListObjectsSingleton::instance()->GetNewIDEquipment(), rarity_item);
			GiveHat(hat);
			if (is_current_hat)
			{
				current_hat = hat;
			}
			hat.reset();
		}
	}
}

void Player::LoadRingInformations()
{
	int current_save = ListObjectsSingleton::instance()->GetCurrentSave();
	std::ifstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Rings1.txt");
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Rings2.txt");
	}
	else
	{
		myfile.open("Rings3.txt");
	}

	bool ring1_found = false;

	if (myfile.is_open())
	{
		std::string str;
		myfile >> str;

		while (str == "NewWeapon")
		{
			std::vector<bool> listIfHaveBonus{ false,false,false,false,false,false,false,false,false,false,false,false,false };
			std::vector<float> listBonus{ 0,0,0,0,0,0,0,0,0,0,0,0,0 };
			std::vector<sf::Vector2f> listRangeBonus{ sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0),sf::Vector2f(0,0) };
			int level_item = 1;
			int type_weapon = 0;
			int id_item = -1;
			int rarity_item = 0;
			bool is_current_hat = false;

			myfile >> str;
			if (str == "IdItem")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						if (str == "true")
						{
							is_current_hat = true;
						}
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "listTypeBonus")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					int counter = 0;
					while (str != ">")
					{
						if (str == "true")
						{
							listIfHaveBonus[counter] = true;
						}
						else
						{
							listIfHaveBonus[counter] = false;
						}
						counter++;
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "listBonus")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					int counter = 0;
					while (str != ">")
					{
						float number = GlobalFunction::ConvertStringToFloat(str);
						listBonus[counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "listRangeBonus")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					int counter = 0;
					while (str != ">")
					{
						sf::Vector2f number;

						number.x = GlobalFunction::ConvertStringToFloat(str);
						myfile >> str;

						number.y = GlobalFunction::ConvertStringToFloat(str);
						myfile >> str;
						listRangeBonus[counter] = number;
						counter++;
					}
				}
			}

			myfile >> str;
			if (str == "item_level")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					level_item = GlobalFunction::ConvertStringToInt(str);
					myfile >> str;
				}
			}

			myfile >> str;
			if (str == "type_weapon")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					type_weapon = GlobalFunction::ConvertStringToInt(str);
					myfile >> str;
				}
			}
			myfile >> str;

			if (str == "RarityItem")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					rarity_item = GlobalFunction::ConvertStringToInt(str);
					myfile >> str;
				}
			}
			myfile >> str;

			std::shared_ptr<E_Ring> ring = std::shared_ptr<E_Ring>(new E_Ring(language, current_save));
			ring->Init(level_item, listIfHaveBonus, listBonus, listRangeBonus, ListObjectsSingleton::instance()->GetNewIDEquipment(), rarity_item,13);
			GiveRing(ring);
			if (is_current_hat)
			{
				if (!ring1_found)
				{
					current_ring1 = ring;
					ring1_found = true;
				}
				else
				{
					current_ring2 = ring;
				}
			}
			ring.reset();
		}
	}
}

void Player::SaveInventoryInformation()
{
	int current_save = ListObjectsSingleton::instance()->GetCurrentSave();
	std::ofstream ofs;

	if (current_save == FirstSave_E)
	{
		ofs.open("Inventory1.txt", std::ofstream::out | std::ofstream::trunc);
	}
	else if (current_save == SecondSave_E)
	{
		ofs.open("Inventory2.txt", std::ofstream::out | std::ofstream::trunc);
	}
	else
	{
		ofs.open("Inventory3.txt", std::ofstream::out | std::ofstream::trunc);
	}

	ofs.close();


	std::ofstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Inventory1.txt", std::fstream::app);
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Inventory2.txt", std::fstream::app);
	}
	else
	{
		myfile.open("Inventory3.txt", std::fstream::app);
	}

	myfile.seekp(std::ios::end);
	myfile << "ModifyAtYourOwnRisk";
	myfile << std::endl;
	myfile << std::endl;

	myfile << "Material";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < inventory[I_Material].size(); i++)
	{
		std::string str("" + std::to_string(inventory[I_Material][i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "Miscellaneous";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < inventory[I_Miscellaneous].size(); i++)
	{
		std::string str("" + std::to_string(inventory[I_Miscellaneous][i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile.close();
}

void Player::LoadInventoryInformation()
{
	int current_save = ListObjectsSingleton::instance()->GetCurrentSave();
	std::ifstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Inventory1.txt");
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Inventory2.txt");
	}
	else
	{
		myfile.open("Inventory3.txt");
	}

	if (myfile.is_open())
	{
		std::string str;
		myfile >> str;

		if (str == "ModifyAtYourOwnRisk")
		{

			myfile >> str;
			if (str == "Material")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						inventory[I_Material][counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "Miscellaneous")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						inventory[I_Miscellaneous][counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}
		}
	}

	myfile.close();
}

void Player::SaveCharacteristicInformation()
{
	int current_save = ListObjectsSingleton::instance()->GetCurrentSave();
	std::ofstream ofs;

	if (current_save == FirstSave_E)
	{
		ofs.open("Characteristic1.txt", std::ofstream::out | std::ofstream::trunc);
	}
	else if (current_save == SecondSave_E)
	{
		ofs.open("Characteristic2.txt", std::ofstream::out | std::ofstream::trunc);
	}
	else
	{
		ofs.open("Characteristic3.txt", std::ofstream::out | std::ofstream::trunc);
	}

	ofs.close();


	std::ofstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Characteristic1.txt", std::fstream::app);
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Characteristic2.txt", std::fstream::app);
	}
	else
	{
		myfile.open("Characteristic3.txt", std::fstream::app);
	}
	myfile.seekp(std::ios::end);
	myfile << "ModifyAtYourOwnRisk";
	myfile << std::endl;
	myfile << std::endl;

	myfile << "ListCharacteristic";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < ListCharacteristicMages.size(); i++)
	{
		if (ListCharacteristicMages[i])
		{
			myfile << "true";
			myfile << std::string(" ");
		}
		else
		{
			myfile << "false";
			myfile << std::string(" ");
		}
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "ListCharacteristicProsOrCons";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < ListCharacteristicProsOrCons.size(); i++)
	{
		if (ListCharacteristicProsOrCons[i] > 0)
		{
			myfile << "true";
			myfile << std::string(" ");
		}
		else
		{
			myfile << "false";
			myfile << std::string(" ");
		}
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "ListDrawback";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < ListDrawbackMages.size(); i++)
	{
		if (ListDrawbackMages[i])
		{
			myfile << "true";
			myfile << std::string(" ");
		}
		else
		{
			myfile << "false";
			myfile << std::string(" ");
		}
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "ClassCantUse";
	myfile << std::endl;
	myfile << " < ";
	
	std::string str("" + std::to_string(class_cant_use));
	myfile << str;
	myfile << std::string(" ");

	myfile << " > ";
	myfile << std::endl;

	myfile.close();
}

void Player::LoadCharacteristicInformation()
{
	int current_save = ListObjectsSingleton::instance()->GetCurrentSave();
	std::ifstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Characteristic1.txt");
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Characteristic2.txt");
	}
	else
	{
		myfile.open("Characteristic3.txt");
	}

	if (myfile.is_open())
	{
		std::string str;
		myfile >> str;

		if (str == "ModifyAtYourOwnRisk")
		{
			player_characteristic_created = true;
			myfile >> str;
			if (str == "ListCharacteristic")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						if (str == "true")
						{
							ListCharacteristicMages[counter] = true;
							counter++;
							myfile >> str;
						}
						else
						{
							ListCharacteristicMages[counter] = false;
							counter++;
							myfile >> str;
						}
					}
				}
			}

			myfile >> str;
			if (str == "ListCharacteristicProsOrCons")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						if (str == "true")
						{
							ListCharacteristicProsOrCons[counter] = 1;
							counter++;
							myfile >> str;
						}
						else
						{
							ListCharacteristicProsOrCons[counter] = -1;
							counter++;
							myfile >> str;
						}
					}
				}
			}

			myfile >> str;
			if (str == "ListDrawback")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						if (str == "true")
						{
							ListDrawbackMages[counter] = true;
							counter++;
							myfile >> str;
						}
						else
						{
							ListDrawbackMages[counter] = false;
							counter++;
							myfile >> str;
						}
					}
				}
			}


			myfile >> str;
			if (str == "ClassCantUse")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						class_cant_use = number;
						counter++;
						myfile >> str;
					}
				}
			}
		}
	}

	myfile.close();
}

void Player::DeleteSave(int save_to_delete)
{
	std::cout << "deleted on save " << save_to_delete + 1 << std::endl;
	std::ofstream ofs;
	if (save_to_delete == FirstSave_E)
	{
		ofs.open("Characteristic1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Inventory1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Ressource1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Achievements1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Weapons1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("WizardHats1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Achievements1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Rings1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Pet1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Feat1.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}
	else if (save_to_delete == SecondSave_E)
	{
		ofs.open("Characteristic2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Inventory2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Ressource2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Achievements2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Weapons2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("WizardHats2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Achievements2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Rings2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Pet2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Feat2.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}
	else if (save_to_delete == ThirdSave_E)
	{
		ofs.open("Characteristic3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Inventory3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Ressource3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Achievements3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Weapons3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("WizardHats3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Achievements3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Rings3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Pet3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		ofs.open("Feat3.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}
}
#pragma endregion Save

void Player::MapPortalGestion()
{
	player_image.setPosition(sf::Vector2f(100, 100));
	position_going_to = sf::Vector2f(100, 100);
	GivePlayerChangeStat(Immunity, 5, 1);
	number_monster_hearts = 0;
	ritual_done = false;
}

void Player::AchievementUpdate(int number_point_on_radar,int map_level)
{
	int holder = 0;
	for (int i = 0; i < player_skills_level_array.size(); i++)
	{
		if (player_skills_level_array[i] >= 2)
		{
			holder++;
		}
	}
	achievement_gestion.ActionInAchievement(A_NumberSkillLevelTwo, holder);
	achievement_gestion.ActionInAchievement(A_PlayerLevel, player_level);
	achievement_gestion.ActionInAchievement(A_NumberMonsterRadar, number_point_on_radar);
	achievement_gestion.ActionInAchievement(A_MapReachedLevel, map_level);
	achievement_gestion.Update();
}

void Player::MonsterKilledGestion(bool is_elite)
{
	achievement_gestion.ActionInAchievement(A_MonsterKilled, 1);
	number_monster_hearts++;

	if (language == English_E)
	{
		sf::String str = "You received a monster's heart. You now have ";
		str = GlobalFunction::InsertNumberToString(str, number_monster_hearts, str.getSize());
		str.insert(str.getSize(), " of them.");

		NotificationSystem::instance()->AddNoticeToList(str);
	}
	else
	{
		sf::String str = "Vous avez reçu un coeur de monstre. Vous en avez maintenant ";
		str = GlobalFunction::InsertNumberToString(str, number_monster_hearts, str.getSize());
		str.insert(str.getSize(), ".");

		NotificationSystem::instance()->AddNoticeToList(str);
	}

	if (number_monster_hearts == 25 || number_monster_hearts >= 40)
	{
		if (language == English_E)
		{
			NotificationSystem::instance()->AddNoticeToList("You have enough monster's hearts for the ritual.");
		}
		else
		{
			NotificationSystem::instance()->AddNoticeToList("Vous avez suffisant de coeurs de montres pour débuter le rituel.");
		}
	}

	FeatGestion::instance()->Action(F_Kill,1);
	if (is_elite)
	{
		if (GlobalFunction::getRandomRange(1, 1000) <= 250)
		{
			GetRandomRune();
		}
		FeatGestion::instance()->Action(F_KillElite,1);
	}
}

void Player::GivePlayerNewCharacteristic(std::vector<bool> ListCharacteristicMages_received, std::vector<int> ListCharacteristicProsOrCons_received, std::vector<bool> ListDrawbackMages_received, sf::String name_mage_received)
{
	ListCharacteristicMages = ListCharacteristicMages_received;
	ListCharacteristicProsOrCons = ListCharacteristicProsOrCons_received;
	ListDrawbackMages = ListDrawbackMages_received;

	player_characteristic_created = true;
	current_opened_interface = NoInterface_E;

	if (ListDrawbackMages[6])
	{
		class_cant_use = GlobalFunction::getRandomRange(1, 3) - 1;
		if (current_class == class_cant_use)
		{
			if (current_class == ClassGrass)
			{
				current_class = ClassFire;
			}
			else
			{
				current_class = ClassGrass;
			}
		}

	}

	name_mage = name_mage_received;
}

void Player::GetRandomRune()
{
	int random_rune = GlobalFunction::getRandomRange(1, 3) - 1;
	int random_skill = GlobalFunction::getRandomRange(1, NUMBERSKILL) - 1;
	while (listRuneAvailable[random_skill][random_rune])
	{
		random_rune = GlobalFunction::getRandomRange(1, 3) - 1;
		random_skill = GlobalFunction::getRandomRange(1, NUMBERSKILL) - 1;
	}
	listRuneAvailable[random_skill][random_rune] = true;

	if (language == English_E)
	{
		sf::String str_rune_gotten = "You got a rune for the skill ";
		str_rune_gotten.insert(str_rune_gotten.getSize(),listAllSkills[random_skill]->GetStringSkillInformation(0));
		str_rune_gotten.insert(str_rune_gotten.getSize(), ".");
		NotificationSystem::instance()->AddNoticeToList(str_rune_gotten);
	}
	else
	{
		sf::String str_rune_gotten = "Vous avez reçu une rune pour le sort ";
		str_rune_gotten.insert(str_rune_gotten.getSize(), listAllSkills[random_skill]->GetStringSkillInformation(0));
		str_rune_gotten.insert(str_rune_gotten.getSize(), ".");
		NotificationSystem::instance()->AddNoticeToList(str_rune_gotten);
	}
}