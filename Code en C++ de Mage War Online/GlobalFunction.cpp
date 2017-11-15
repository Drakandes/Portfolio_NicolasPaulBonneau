#include "stdafx.h"
#include "GlobalFunction.h"

int GlobalFunction::getRandomRange(int min, int max)
{
	if (min > max)
	{
		return min;
	}
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	int number = distr(eng);
	return  number;
}

float GlobalFunction::getRandomRangeIfFloat(float min, float max)
{
	if (min < max)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> distr(min, max); // define the range
		float number = distr(eng);
		return number;
	}
	return  min;
}

int GlobalFunction::getRandomRangeWithException(int min, int max, int exception)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	int number = distr(eng);

	for (number; number == exception; number)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> distr(min, max); // define the range
		number = distr(eng);
	}
	return number;
}

int GlobalFunction::getRandomRangeWithUnknownException(int min, int max, std::vector<int> listException)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	int number = distr(eng);

	while (1)
	{
		bool can_return = true;

		for (int i = 0; i < listException.size(); i++)
		{
			if (number == listException[i])
			{
				can_return = false;
				break;
			}
		}

		if (can_return)
		{
			return number;
		}

		std::random_device rd; 
		std::mt19937 eng(rd()); 
		std::uniform_int_distribution<> distr(min, max); 
		number = distr(eng);
	}

	return number;
}

sf::RectangleShape GlobalFunction::CreateRectangle(sf::Vector2f rectangle_size, sf::Vector2f rectangle_position)
{
	sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(rectangle_size.x, rectangle_size.y));
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setPosition(rectangle_position.x, rectangle_position.y);

	return rectangle;
}

sf::Text GlobalFunction::CreateText(sf::Vector2f text_position, sf::String text_string, sf::Font &font, int character_size)
{
	sf::Text text;
	text.setCharacterSize(character_size);
	text.setFont(font);
	text.setPosition(text_position.x, text_position.y);
	text.setString(text_string);
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2, text.getGlobalBounds().height / 2));
	return text;
}

sf::Text GlobalFunction::CreateTextWithNoOrigin(sf::Vector2f text_position, sf::String text_string, sf::Font &font, int character_size)
{
	sf::Text text;
	text.setCharacterSize(character_size);
	text.setFont(font);
	text.setPosition(text_position.x, text_position.y);
	text.setString(text_string);
	return text;
}

sf::String GlobalFunction::InsertNumberToString(sf::String string, int number_to_add, int position_number_to_add)
{
	sf::String string_to_add = std::to_string(number_to_add);
	string.insert(position_number_to_add, string_to_add);
	return string;
}

sf::String GlobalFunction::InsertNumberToStringIfFloat(sf::String string, float number_to_add, int position_number_to_add)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << number_to_add;
	std::string mystring = ss.str();
	string.insert(position_number_to_add, mystring);
	return string;
}

sf::Vector2f GlobalFunction::GetPlayerlevel(float player_experience, int player_level)
{
	/*if (player_level <= 5)
	{
		if (player_experience < 500)
		{
			return 1;
		}
		if (player_experience >= 500 && player_experience < 800)
		{
			return 2;
		}

		if (player_experience >= 800 && player_experience < 1260)
		{
			return 3;
		}

		if (player_experience >= 1260 && player_experience < 1955)
		{
			return 4;
		}

		if (player_experience >= 1955 && player_experience < 2980)
		{
			return 5;
		}

		if (player_experience >= 2980 && player_experience < 4470)
		{
			return 6;
		}
	}
	if (player_level <= 10)
	{
		if (player_experience >= 2980 && player_experience < 4470)
		{
			return 6;
		}

		if (player_experience >= 4470 && player_experience < 6590)
		{
			return 7;
		}

		if (player_experience >= 6590 && player_experience < 9545)
		{
			return 8;
		}

		if (player_experience >= 9545 && player_experience < 13615)
		{
			return 9;
		}

		if (player_experience >= 13615 && player_experience < 19060)
		{
			return 10;
		}

		if (player_experience >= 19060 && player_experience < 26210)
		{
			return 11;
		}
	}
	if (player_level <= 15)
	{
		if (player_experience >= 19060 && player_experience < 26210)
		{
			return 11;
		}

		if (player_experience >= 26210 && player_experience < 35380)
		{
			return 12;
		}

		if (player_experience >= 35380 && player_experience < 46880)
		{
			return 13;
		}

		if (player_experience >= 46880 && player_experience < 60950)
		{
			return 14;
		}

		if (player_experience >= 60950 && player_experience < 77710)
		{
			return 15;
		}

		if (player_experience >= 77710 && player_experience < 97135)
		{
			return 16;
		}
	}
	if (player_level <= 21)
	{
		if (player_experience >= 77710 && player_experience < 97135)
		{
			return 16;
		}

		if (player_experience >= 97135 && player_experience < 118990)
		{
			return 17;
		}

		if (player_experience >= 118990 && player_experience < 142790)
		{
			return 18;
		}

		if (player_experience >= 142790 && player_experience < 167780)
		{
			return 19;
		}

		if (player_experience >= 167780 && player_experience < 192945)
		{
			return 20;
		}

		if (player_experience >= 192945)
		{
			return 21;
		}
	}
	return 0;*/

	sf::Vector2f vector{ static_cast<float>(player_level),player_experience };

	if (player_level <= 7)
	{
		if (player_level < 2)
		{
			if (player_experience >= 500)
			{
				vector.x++;
				vector.y -= 500;
			}
		}
		if (player_level < 3)
		{
			if(player_experience >=  800)
			{
				vector.x++;
				vector.y -= 800;
			}
		}

		if (player_level < 4)
		{
			if(player_experience >=  1260)
			{
				vector.x++;
				vector.y -= 1260;
			}
		}

		if (player_level < 5)
		{
			if(player_experience >=  1955)
			{
				vector.x++;
				vector.y -= 1955;
			}
		}

		if (player_level < 6)
		{
			if(player_experience >=  2980)
			{
				vector.x++;
				vector.y -= 2980;
			}
		}

		if (player_level < 7)
		{
			if(player_experience >=  4470)
			{
				vector.x++;
				vector.y -= 4470;
			}
		}
	}
	else if (player_level <= 12)
	{
		if (player_level < 7)
		{
			if(player_experience >=  4470)
			{
				vector.x++;
				vector.y -= 4470;
			}
		}

		if (player_level < 8)
		{
			if(player_experience >=  6590)
			{
				vector.x++;
				vector.y -= 6590;
			}
		}

		if (player_level < 9)
		{
			if(player_experience >=  9545)
			{
				vector.x++;
				vector.y -= 9545;
			}
		}

		if (player_level < 10)
		{
			if(player_experience >=  13615)
			{
				vector.x++;
				vector.y -= 13615;
			}
		}

		if (player_level < 11)
		{
			if(player_experience >=  19060)
			{
				vector.x++;
				vector.y -= 19060;
			}
		}

		if (player_level < 12)
		{
			if(player_experience >=  26210)
			{
				vector.x++;
				vector.y -= 26210;
			}
		}
	}
	else if (player_level <= 17)
	{
		if (player_level < 12)
		{
			if(player_experience >=  26210)
			{
				vector.x++;
				vector.y -= 26210;
			}
		}

		if (player_level < 13)
		{
			if(player_experience >=  35380)
			{
				vector.x++;
				vector.y -= 35380;
			}
		}

		if (player_level < 14)
		{
			if(player_experience >=  46880)
			{
				vector.x++;
				vector.y -= 46880;
			}
		}

		if (player_level < 15)
		{
			if(player_experience >=  60950)
			{
				vector.x++;
				vector.y -= 60950;
			}
		}

		if (player_level < 16)
		{
			if(player_experience >=  77710)
			{
				vector.x++;
				vector.y -= 77710;
			}
		}

		if (player_level < 17)
		{
			if(player_experience >=  97135)
			{
				vector.x++;
				vector.y -= 97135;
			}
		}
	}
	else if (player_level <= 22)
	{
		if (player_level < 17)
		{
			if(player_experience >=  97135)
			{
				vector.x++;
				vector.y -= 97135;
			}
		}

		if (player_level < 18)
		{
			if(player_experience >=  118990)
			{
				vector.x++;
				vector.y -= 118990;
			}
		}

		if (player_level < 19)
		{
			if(player_experience >=  142790)
			{
				vector.x++;
				vector.y -= 142790;
			}
		}

		if (player_level < 20)
		{
			if(player_experience >=  167780)
			{
				vector.x++;
				vector.y -= 167780;
			}
		}

		if (player_level < 21)
		{
			if (player_experience >= 192945)
			{
				vector.x++;
				vector.y -= 192945;
			}
		}
	}
	return vector;
}

int  GlobalFunction::GetPlayerExperienceNeeded(int player_level)
{
	if (player_level <= 7)
	{
		if (player_level < 2)
		{
			return 500;
		}
		if (player_level < 3)
		{
			return 800;
		}

		if (player_level < 4)
		{
			return 1260;
		}

		if (player_level < 5)
		{
			return 1955;
		}

		if (player_level < 6)
		{
			return 2980;
		}

		if (player_level < 7)
		{
			return 4470;
		}
	}
	if (player_level <= 12)
	{
		if (player_level < 7)
		{
			return 4470;
		}

		if (   player_level < 8)
		{
			return 6590;
		}

		if (   player_level < 9)
		{
			return 9545;
		}

		if (   player_level < 10)
		{
			return 13615;
		}

		if (   player_level < 11)
		{
			return 19060;
		}

		if (   player_level < 12)
		{
			return 26210;
		}
	}
	if (player_level <= 17)
	{
		if (   player_level < 12)
		{
			return 26210;
		}

		if (   player_level < 13)
		{
			return 35380;
		}

		if (   player_level < 14)
		{
			return 46880;
		}

		if (   player_level < 15)
		{
			return 60950;
		}

		if (   player_level < 16)
		{
			return 77710;
		}

		if (   player_level < 17)
		{
			return 97135;
		}
	}
	if (player_level <= 22)
	{
		if (   player_level < 17)
		{
			return 97135;
		}

		if (   player_level < 18)
		{
			return 118990;
		}

		if (   player_level < 19)
		{
			return 142790;
		}

		if (   player_level < 20)
		{
			return 167780;
		}

		if (   player_level < 21)
		{
			return 192945;
		}

		if (player_level < 22)
		{
			return 1;
		}
	}
	return 0;
} 

sf::RectangleShape GlobalFunction::CreateRectangleWithOrigin(sf::Vector2f rectangle_size, sf::Vector2f rectangle_position, sf::Color color)
{
	sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(rectangle_size.x, rectangle_size.y));
	rectangle.setFillColor(color);
	rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);
	rectangle.setPosition(rectangle_position.x, rectangle_position.y);
	return rectangle;
}

float GlobalFunction::GetDistanceBetweenTwoPositions(sf::Vector2f position_1, sf::Vector2f position_2)
{
	float distance = sqrt(((position_1.x - position_2.x)*(position_1.x - position_2.x)) + ((position_1.y - position_2.y)*(position_1.y - position_2.y)));
	return distance;
}

sf::Vector2f GlobalFunction::GetMousePosition(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
	sf::Vector2f mouse_position;
	mouse_position.x = sf::Mouse::getPosition(window).x / Proportion + position_view_player.x;
	mouse_position.y = sf::Mouse::getPosition(window).y / Proportion + position_view_player.y;
	return mouse_position;
}

sf::Sprite GlobalFunction::CreateSprite(sf::Vector2f position_sprite, sf::Vector2f size_sprite, sf::Texture &texture_sprite)
{
	sf::Sprite sprite;
	sprite.setPosition(position_sprite);
	sprite.setTexture(texture_sprite);
	sprite.setTextureRect(sf::IntRect(0, 0, size_sprite.x, size_sprite.y));
	sprite.setOrigin(sf::Vector2f(size_sprite.x/2, size_sprite.y/2));
	return sprite;
}

sf::Sprite GlobalFunction::CreateSpriteWithoutOrigin(sf::Vector2f position_sprite, sf::Vector2f size_sprite, sf::Texture &texture_sprite)
{
	sf::Sprite sprite;
	sprite.setPosition(position_sprite);
	sprite.setTexture(texture_sprite);
	sprite.setTextureRect(sf::IntRect(0, 0, size_sprite.x, size_sprite.y));
	return sprite;
}

bool GlobalFunction::CheckMouseOnSomethingWithOrigin(sf::Vector2f mouse_position, sf::Vector2f object_position, sf::Vector2f object_size)
{
	if (object_position.x - object_size.x / 2 <= mouse_position.x && object_position.x + object_size.x / 2 >= mouse_position.x && object_position.y - object_size.y / 2 <= mouse_position.y && object_position.y + object_size.y / 2 >= mouse_position.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

sf::String GlobalFunction::GetFragmentNeededForSkillUpgrade(int skill_level)
{
	sf::String string_holder;
	if (skill_level == 0)
	{
		string_holder = "Need 500 strong fragments to upgrade this skill";
	}
	else if (skill_level == 1)
	{
		string_holder = "Need 500 enchanted fragments to upgrade this skill";
	}
	else if (skill_level == 2)
	{
		string_holder = "Need 750 runic fragments to upgrade this skil";
	}
	else if (skill_level == 3)
	{
		string_holder = "Need 1000 ancient fragments to upgrade this skill";
	}
	else if (skill_level == 4)
	{
		string_holder = "Need 50 lost legendary fragments to upgrade this skill";
	}
	else if (skill_level == 5)
	{
		string_holder = "You can't upgrade this skill anymore";
	}
	else
	{
		string_holder = "Unknown";
	}
	return string_holder;
}

sf::String GlobalFunction::GetTypeFragment(int number_type_fragment)
{
	sf::String string_holder;
	if (number_type_fragment == StrongFragment)
	{
		string_holder = "Strong fragments: ";
	}
	else if (number_type_fragment == EnchantedFragment)
	{
		string_holder = "Enchanted fragments: ";
	}
	else if (number_type_fragment == RunicFragment)
	{
		string_holder = "Runic fragments: ";
	}
	else if (number_type_fragment == AncientFragment)
	{
		string_holder = "Ancient fragments: ";
	}
	else if (number_type_fragment == LostLegendaryFragment)
	{
		string_holder = "Legendary fragments: ";
	}
	else
	{
		string_holder = "Unknown fragments: ";
	}
	return string_holder;
}

int GlobalFunction::GetNumberFragmentsNeeded(int skill_level)
{
	if (skill_level == 0)
	{
		return 500;
	}
	else if (skill_level == 1)
	{
		return 500;
	}
	else if (skill_level == 2)
	{
		return 750;
	}
	else if (skill_level == 3)
	{
		return 1000;
	}
	else if (skill_level == 4)
	{
		return 50;
	}
	
	return 10000;
}

int GlobalFunction::GetTypeFragmentNeeded(int skill_level)
{
	{
		if (skill_level == 0)
		{
			return StrongFragment;
		}
		else if (skill_level == 1)
		{
			return EnchantedFragment;
		}
		else if (skill_level == 2)
		{
			return RunicFragment;
		}
		else if (skill_level == 3)
		{
			return AncientFragment;
		}
		else if (skill_level == 4)
		{
			return LostLegendaryFragment;
		}

		return -1;
	}
}

bool GlobalFunction::CheckIfPlayerAlreadyHasSkill(int skill, std::vector<int> player_skill_array)
{
	for (int number = 0; number < player_skill_array.size(); number++)
	{
		if (skill == player_skill_array[number])
		{
			return true;
		}
	}
	return false;
}

sf::Sprite GlobalFunction::CreateSpriteWithoutTexture(sf::Vector2f position_sprite, sf::Vector2f size_sprite)
{
	sf::Sprite sprite;
	sprite.setPosition(position_sprite);
	sprite.setTextureRect(sf::IntRect(0, 0, size_sprite.x, size_sprite.y));
	sprite.setOrigin(sf::Vector2f(size_sprite.x / 2, size_sprite.y / 2));
	return sprite;
}

float GlobalFunction::PlayerDamageGestion(float player_damage_initial, std::vector < sf::Vector2f> player_gem_array, std::vector<std::shared_ptr<G_GemBase>> listAllGems, std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors, int number_current_armor, std::vector<int> listAllActiveGems)
{
	float player_damage_bonus = 0;
	for (int number = 0; number < player_gem_array.size(); number++)
	{
		if (player_gem_array[number].x == GemAttack && listAllActiveGems[number] == 1)
		{
			player_damage_bonus += listAllGems[player_gem_array[number].x]->GetGemBonusForTier(player_gem_array[number].y-1);
		}
	}
	if (listAllArmors[number_current_armor]->ReturnArmorBonusType() == DamagePercent)
	{
		player_damage_bonus += player_damage_initial*listAllArmors[number_current_armor]->ReturnArmorBonusNumber() / 100;
	}
	return player_damage_bonus + player_damage_initial;
}

float GlobalFunction::PlayerHealthGestion(float player_max_health_initial, std::vector < sf::Vector2f> player_gem_array, std::vector<std::shared_ptr<G_GemBase>>listAllGems, std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors, int number_current_armor, std::vector<int> listAllActiveGems)
{
	float player_max_health = 0;
	for (int number = 0; number < player_gem_array.size(); number++)
	{
		if (player_gem_array[number].x == GemLife && listAllActiveGems[number] == 1)
		{
			player_max_health += listAllGems[player_gem_array[number].x]->GetGemBonusForTier(player_gem_array[number].y - 1);
		}
	}
	if (listAllArmors[number_current_armor]->ReturnArmorBonusType() == HealthPercent)
	{
		player_max_health += player_max_health_initial*listAllArmors[number_current_armor]->ReturnArmorBonusNumber() / 100;
	}
	return player_max_health + player_max_health_initial;
}

float GlobalFunction::PlayerDefenseGestion(float player_defense_initial, std::vector < sf::Vector2f> player_gem_array, std::vector<std::shared_ptr<G_GemBase>> listAllGems, std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors, int number_current_armor, std::vector<int> listAllActiveGems)
{
	float player_defense = 0;
	for (int number = 0; number < player_gem_array.size(); number++)
	{
		if (player_gem_array[number].x == GemDefense && listAllActiveGems[number] == 1)
		{
			player_defense += listAllGems[player_gem_array[number].x]->GetGemBonusForTier(player_gem_array[number].y - 1);
		}
	}
	return player_defense + player_defense_initial;
}

float GlobalFunction::PlayerExperienceGestion(std::vector < sf::Vector2f> player_gem_array, std::vector<std::shared_ptr<G_GemBase>>listAllGems, std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors, int number_current_armor, std::vector<int> listAllActiveGems)
{
	float player_bonus_experience_percent = 0;
	for (int number = 0; number < player_gem_array.size(); number++)
	{
		if (player_gem_array[number].x == GemExperience && listAllActiveGems[number] == 1)
		{
			player_bonus_experience_percent += listAllGems[player_gem_array[number].x]->GetGemBonusForTier(player_gem_array[number].y - 1);
		}
	}
	if (listAllArmors[number_current_armor]->ReturnArmorBonusType() == ExperiencePercent)
	{
		player_bonus_experience_percent += listAllArmors[number_current_armor]->ReturnArmorBonusNumber();
	}
	return player_bonus_experience_percent;
}

float GlobalFunction::PlayerMovementSpeedGestion(float player_movement_speed_initial,std::vector < sf::Vector2f> player_gem_array, std::vector<std::shared_ptr<G_GemBase>> listAllGems, std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors, int number_current_armor, std::vector<int> listAllActiveGems)
{
	float player_speed_bonus = 0;
	for (int number = 0; number < player_gem_array.size(); number++)
	{
		if (player_gem_array[number].x == GemSwiftness && listAllActiveGems[number] == 1)
		{
			player_speed_bonus += player_movement_speed_initial*listAllGems[player_gem_array[number].x]->GetGemBonusForTier(player_gem_array[number].y - 1)/100;
		}
	}
	if (listAllArmors[number_current_armor]->ReturnArmorBonusType() == MovementSpeedPercent)
	{
		player_speed_bonus += player_movement_speed_initial*listAllArmors[number_current_armor]->ReturnArmorBonusNumber()/100;
	}
	return player_speed_bonus + player_movement_speed_initial;
}

float GlobalFunction::PlayerCooldownReductionGestion(std::vector < sf::Vector2f> player_gem_array, std::vector<std::shared_ptr<G_GemBase>> listAllGems, std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors, int number_current_armor, std::vector<int> listAllActiveGems)
{
	float player_cooldown_reduction_percent = 0;
	for (int number = 0; number < player_gem_array.size(); number++)
	{
		if (player_gem_array[number].x == GemTime && listAllActiveGems[number] == 1)
		{
			player_cooldown_reduction_percent += listAllGems[player_gem_array[number].x]->GetGemBonusForTier(player_gem_array[number].y - 1);
		}
	}
	if (listAllArmors[number_current_armor]->ReturnArmorBonusType() == CooldownReduction)
	{
		player_cooldown_reduction_percent += listAllArmors[number_current_armor]->ReturnArmorBonusNumber();
	}
	return player_cooldown_reduction_percent;
}

int GlobalFunction::GetDirectionFromAngle(int angle)
{
	if (angle <= 315 && angle >= 225)
	{
		return Down;
	}
	if (angle <= 135 && angle >= 45)
	{
		return Up;
	}
	if ((angle <= 45 && angle >= 0) || (angle >= 315 && angle <= 360))
	{
		return Left;
	}
	if (angle <= 225 && angle >= 135)
	{
		return Right;
	}
}

sf::CircleShape GlobalFunction::CreateCircleForCollision(sf::Vector2f position_circle, int rayon_circle, sf::Color color_circle)
{
	sf::CircleShape circle;
	circle.setRadius(rayon_circle);
	circle.setPosition(position_circle);
	circle.setOutlineThickness(2);
	circle.setOutlineColor(color_circle);
	circle.setFillColor(sf::Color::Color(0, 0, 0, 0));
	circle.setOrigin(rayon_circle, rayon_circle);
	return circle;
}

sf::CircleShape GlobalFunction::CreateCircleWithOrigin(sf::Vector2f position_circle, int rayon_circle)
{
	sf::CircleShape circle;
	circle.setRadius(rayon_circle);
	circle.setPosition(position_circle);
	circle.setFillColor(sf::Color::Blue);
	circle.setOrigin(rayon_circle, rayon_circle);
	return circle;
}

bool GlobalFunction::CheckCollisionWithCircleIfBothWithOrigin(int rayon_circle, sf::Vector2f position_circle, sf::Vector2f position_entity, sf::Vector2f size_entity, int rayon_entity)
{
	float distance = sqrt(((position_circle.x - position_entity.x  )*(position_circle.x - position_entity.x)) + ((position_circle.y - position_entity.y)*(position_circle.y - position_entity.y)));
	if (distance <= rayon_circle + rayon_entity)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float GlobalFunction::GetInclineForLineFromTwoPoints(sf::Vector2f point_1, sf::Vector2f point_2)
{
	float incline;
	if (point_1.x > point_2.x)
	{
		incline = -1*((point_1.y - point_2.y) / (point_1.x - point_2.x));
		return incline;
	}
	else if (point_1.x < point_2.x)
	{
		incline = -1*((point_2.y - point_1.y) / (point_2.x - point_1.x));
		return incline;
	}
	else
	{
		return 0;
	}
}

float GlobalFunction::GetRotationBetweenTwoPositions(sf::Vector2f position, sf::Vector2f position_center)
{
	float rotation = 0;

	if (position.x == position_center.x)
	{
		if (position.y <= position_center.y)
		{
			rotation = 270;
		}
		else if (position.y >= position_center.y)
		{
			rotation = 90;
		}
	}
	else if (position.y == position_center.y)
	{
		if (position.x >= position_center.x)
		{
			rotation = 0;
		}
		else if (position.x <= position_center.x)
		{
			rotation = 180;
		}
	}
	else if (position.x > position_center.x)
	{
		if (position.y < position_center.y)
		{
			rotation = 270 + ((((atan((position.x - position_center.x) / (position_center.y - position.y))) * 180 / PI)));
		}
		else if (position.y > position_center.y)
		{
			rotation = (90 - ((atan((position.x - position_center.x) / (position.y - position_center.y)) * 180 / PI)));
		}
	}
	else if (position.x < position_center.x)
	{
		if(position.y < position_center.y)
		{
			rotation = 270 + ((atan((position.x - position_center.x) / (position_center.y - position.y))) * 180 / PI);
		}
		else if (position.y > position_center.y)
		{
			rotation = (180 - (((atan((position_center.y - position.y) / (position.x - position_center.x))) * 180 / PI)));
		}
	}
	return rotation;
}

bool GlobalFunction::Check_collision(float rayon_1, float rayon_2, sf::Vector2f position_1, sf::Vector2f position_2, sf::Vector2f size_1, sf::Vector2f size_2)
{
	float distance = sqrt(((position_1.x - position_2.x)*(position_1.x - position_2.x)) + ((position_1.y - position_2.y)*(position_1.y - position_2.y)));
	if (distance > rayon_1 + rayon_2)
	{
		return false;
	}
	else if (position_1.x - size_1.x / 2 <= position_2.x + size_2.x / 2 && position_1.x + size_1.x / 2 >= position_2.x - size_2.x / 2 && position_1.y - size_1.y / 2 <= position_2.y + size_2.y / 2 && position_1.y + size_1.y / 2 >= position_2.y - size_2.y / 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GlobalFunction::CheckCollisionV2(sf::FloatRect CollisionRect1, sf::FloatRect CollisionRect2, int rayon1, int rayon2)
{
	if (CollisionRect1.intersects(CollisionRect2))
	{
		return true;
	}
	return false;
}

sf::Vector2f GlobalFunction::quad(float a, float b, float c)
{
	sf::Vector2f sol{ 0,0 };

	if (abs(a) < pow(1, -6))
	{
		if (abs(b) < pow(1, -6))
		{
		}
		else
		{
			sol.x = -c / b;
			sol.y = -c / b;
		}
	}
	else
	{
		float disc = b*b - 4 * a * c;
		if (disc >= 0)
		{
			disc = sqrt(disc);
			a = 2 * a;
			sol.x = (-b - disc) / a;
			sol.y = (-b + disc) / a;
		}
	}

	return sol;
}

sf::Vector2f GlobalFunction::PositionPrediction(sf::Vector2f position_shooter, sf::Vector2f position_target, sf::Vector2f velocity_target, float velocity_bullet)
{
	float position_shooter_x = position_shooter.x;
	float position_shooter_y = position_shooter.y;
	float position_target_x = position_target.x;
	float position_target_y = position_target.y;
	float velocity_target_x = velocity_target.x;
	float velocity_target_y = velocity_target.y;

	float tx = position_target_x - position_shooter_x;
	float ty = position_target_y - position_shooter_y;
	float tvx = velocity_target_x;
	float tvy = velocity_target_y;
	float v = velocity_bullet;

	float a = tvx*tvx + tvy*tvy - v*v;
	float b = 2 * (tvx * tx + tvy * ty);
	float c = tx*tx + ty*ty;

	sf::Vector2f ts = quad(a, b, c);
	float sol_x = 0;
	float sol_y = 0;

	float t0 = ts.x;
	float t = 0;
	if (ts.x > ts.y)
	{
		t = ts.y;
	}
	else
	{
		t = ts.x;
	}

	if (t < 0)
	{
		if (ts.x < ts.y)
		{
			t = ts.y;
		}
		else
		{
			t = ts.x;
		}
	}

	if (t > 0)
	{
		sol_x = position_target_x + velocity_target_x*t;
		sol_y = position_target_y + velocity_target_y*t;
	}
	return sf::Vector2f (sol_x, sol_y);
}

int GlobalFunction::GetNumberFromFile(std::vector<char> listUnity)
{
	if (listUnity[0] != 45)
	{
		int size_list = listUnity.size();
		int counter = 0;
		int number = 0;

		while (size_list != 0)
		{
			number += (listUnity[counter] - 48)*pow(10, size_list - 1);
			counter++;
			size_list--;
		}
		return number;
	}
	else
	{
		int size_list = listUnity.size()-1;
		int counter = 1;
		int number = 0;

		while (size_list != 0)
		{
			number += (listUnity[counter] - 48)*pow(10, size_list - 1);
			counter++;
			size_list--;
		}
		return number*-1;
	}
}

sf::Vector2f GlobalFunction::GetVectorFromFile(std::vector<char> listUnity)
{
	sf::Vector2f number;

	int position_line = 0;
	while (listUnity[position_line] != 124)
	{
		position_line++;
	}

	if (true)
	{
		int size_list = position_line;
		int counter = 0;

		while (size_list != 0)
		{
			number.x += (listUnity[counter] - 48)*pow(10, size_list - 1);
			counter++;
			size_list--;
		}
	}

	if (true)
	{
		int size_list = listUnity.size() - (position_line + 1);
		int counter = position_line + 1;

		while (size_list != 0)
		{
			number.y += (listUnity[counter] - 48)*pow(10, size_list - 1);
			counter++;
			size_list--;
		}
	}

	return number;
}

float GlobalFunction::ConvertStringToFloat(std::string str)
{
	return std::stof(str);
}

int GlobalFunction::ConvertStringToInt(std::string str)
{
	return std::stoi(str);
}

sf::Vector2f GlobalFunction::AddDistanceWithAngleToVector(sf::Vector2f main_vector, float distance, float angle)
{
	main_vector = main_vector + sf::Vector2f(-(cos(angle * PI / 180))*distance, -(sin(angle * PI / 180))*distance);
	return  main_vector;
}

sf::String GlobalFunction::GetRarityString(int rarity, int language)
{
	if (language == English_E)
	{
		if (rarity == Common_E)
		{
			return "Common";
		}
		else if (rarity == Uncommon_E)
		{
			return "Uncommon";
		}
		else if (rarity == Rare_E)
		{
			return "Rare";
		}
		else if (rarity == Epic_E)
		{
			return "Epic";
		}
		else if (rarity == Legendary_E)
		{
			return "Legendary";
		}
	}
	else
	{
		if (rarity == Common_E)
		{
			return "Commun";
		}
		else if (rarity == Uncommon_E)
		{
			return "Peu Commun";
		}
		else if (rarity == Rare_E)
		{
			return "Rare";
		}
		else if (rarity == Epic_E)
		{
			return "Épique";
		}
		else if (rarity == Legendary_E)
		{
			return "Légendaire";
		}
	}
}

float GlobalFunction::AddAngleToAngle(float angle, float angle_to_add)
{
	if (angle + angle_to_add > 360)
	{
		angle = angle + angle_to_add - 360;
	}
	else if (angle + angle_to_add < 0)
	{
		angle = 360 - angle + angle_to_add;
	}

	return angle;
}

float GlobalFunction::GetArmorReductionModifier(float armor)
{
	return 125 / (125 + armor);
}

sf::Vector2f GlobalFunction::GetRandomVectorBetweenRange(float range)
{
	sf::Vector2f vector;

	if (getRandomRange(1, 1000) <= 500)
	{
		vector.x = getRandomRange(1, range);
	}
	else
	{
		vector.x = -getRandomRange(1, range);
	}

	if (getRandomRange(1, 1000) <= 500)
	{
		vector.y = getRandomRange(1, range);
	}
	else
	{
		vector.y = -getRandomRange(1, range);
	}

	return vector;
}