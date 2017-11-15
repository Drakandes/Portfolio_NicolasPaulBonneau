#include "stdafx.h"
#include "Pillar.h"

Pillar::Pillar()
{
	if (!texture.loadFromFile("Pillar.png"))
	{
		std::cout << "Error while laoding Pillar texture" << std::endl;
	}

	if (!shadow_texture.loadFromFile("PillarShadow.png"))
	{
		std::cout << "Error while loading pillar shadow texture" << std::endl;
	}
	shadow = GlobalFunction::CreateSpriteWithoutOrigin(sf::Vector2f(0, 0), shadow_size, shadow_texture);
	shadow.setOrigin(shadow_size.x / 2, 0);
}

Pillar::~Pillar()
{
}

void Pillar::Init(sf::Vector2f position, int type_pillar)
{
	sprite = GlobalFunction::CreateSprite(position, size_sprite, texture);
	this->type_pillar = type_pillar;
}

void Pillar::Update(float DELTATIME, sf::Vector2f player_position)
{

	if (clock_animation.getElapsedTime().asSeconds() >= 0.1)
	{
		sprite.setTextureRect(sf::IntRect(counter*size_sprite.x, type_pillar*size_sprite.y, size_sprite.x, size_sprite.y));
		shadow.setTextureRect(sf::IntRect(counter*size_sprite.x, type_pillar*size_sprite.y, size_sprite.x, size_sprite.y));
		counter++;
		if (counter == 4)
		{
			counter = 0;
		}
		clock_animation.restart();
	}

	if (used)
	{
		sprite.setTextureRect(sf::IntRect(4 * size_sprite.x, type_pillar*size_sprite.y, size_sprite.x, size_sprite.y));
		shadow.setTextureRect(sf::IntRect(4 * size_sprite.x, type_pillar*size_sprite.y, size_sprite.x, size_sprite.y));
	}

	if (clock_used.getElapsedTime().asSeconds() >= 300)
	{
		used = false;
	}
}

void Pillar::Draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

sf::Vector2i Pillar::DealWithCollision(std::shared_ptr<CollisionalObject> object_collided)
{
	if (!used)
	{
		int language = ListObjectsSingleton::instance()->GetCurrentLanguage();
		used = true;
		clock_used.restart();
		if (type_pillar == Self_Damage)
		{
			if (GlobalFunction::getRandomRange(1, 10000) <= 8000)
			{
				if (language == English_E)
				{
					NotificationSystem::instance()->AddNoticeToList("Lucky! Your damage is increased by 25% for 1 minute.");
				}
				else
				{
					NotificationSystem::instance()->AddNoticeToList("Chanceux! Vos dégâts sont augmentés de 25% pendant 1 minute.");
				}
				object_collided->GivePlayerChangeStat(DamagePercentOverall, 60, 25);
			}
			else
			{
				if (language == English_E)
				{
					NotificationSystem::instance()->AddNoticeToList("Sorry! 3 monsters arise.");
				}
				else
				{
					NotificationSystem::instance()->AddNoticeToList("Désolé! 3 monstres apparaissent.");
				}
				return sf::Vector2i(SpawnRandomNumberMonsters, 3);
			}
		}
		else if (type_pillar == Self_Speed)
		{
			if (GlobalFunction::getRandomRange(1, 10000) <= 7500)
			{
				if (language == English_E)
				{
					NotificationSystem::instance()->AddNoticeToList("Lucky! Your attack speed and movement speed are increased by 25% for 2 minutes.");
				}
				else
				{
					NotificationSystem::instance()->AddNoticeToList("Chanceux! Votre vitesse d'attaque et de déplacement sont augmentées de 25% pendant 2 minutes.");
				}
				object_collided->GivePlayerChangeStat(MovementSpeedPercent, 120, 25);
				object_collided->GivePlayerChangeStat(AttackSpeedPercent, 120, 25);
			}
			else
			{
				if (language == English_E)
				{
					NotificationSystem::instance()->AddNoticeToList("Sorry! Your attack speed and movement speed are decreased by 15% for 2 minutes.");
				}
				else
				{
					NotificationSystem::instance()->AddNoticeToList("Désolé! Votre vitesse d'attaque et de déplacement sont réduites de 15% pendant 2 minutes.");
				}
				object_collided->GivePlayerChangeStat(MovementSpeedPercent, 120, -15);
				object_collided->GivePlayerChangeStat(AttackSpeedPercent, 120, -15);
			}
		}
		else if (type_pillar == Self_Exp)
		{
			if (GlobalFunction::getRandomRange(1, 10000) <= 7500)
			{
				if (language == English_E)
				{
					NotificationSystem::instance()->AddNoticeToList("Lucky! You receive 30% more experience for 10 minutes.");
				}
				else
				{
					NotificationSystem::instance()->AddNoticeToList("Chanceux! Vous recevez 30% d'expérience en plus pendant 10 minutes.");
				}
				object_collided->GivePlayerChangeStat(ExperiencePercent, 600, 30);
			}
			else
			{
				if (language == English_E)
				{
					NotificationSystem::instance()->AddNoticeToList("Sorry! One monster is added in each spawn.");
				}
				else
				{
					NotificationSystem::instance()->AddNoticeToList("Désolé! Un monstre apparaît dans tous les générateurs de montres.");
				}
				return sf::Vector2i(FillSpawnsWithXMonsters,1);
			}
		}
		else
		{
			if (GlobalFunction::getRandomRange(1, 10000) <= 7500)
			{
				if (language == English_E)
				{
					NotificationSystem::instance()->AddNoticeToList("Lucky! You recover 2% of your maximum health for 30 seconds and you are fully healed.");
				}
				else
				{
					NotificationSystem::instance()->AddNoticeToList("Chanceux! Vous récupérez 2% de votre vie totale pendant 30 secondes et vous êtes complètement soigné.");
				}
				object_collided->HealObject(1000000);
				object_collided->GivePlayerChangeStat(HpPercentRecovery, 30, 2);
			}
			else
			{
				if (language == English_E)
				{
					NotificationSystem::instance()->AddNoticeToList("Sorry! You have 50% less health for 1 minute.");
				}
				else
				{
					NotificationSystem::instance()->AddNoticeToList("Désolé! Vous avez 50% moins de vie pendant 1 minute.");
				}
				object_collided->GivePlayerChangeStat(HealthPercent, 60, -50);
			}
		}
	}

	return sf::Vector2i(MonsterGeneratorNothing,0);
}

void Pillar::DrawShadow(sf::RenderWindow &window)
{
	shadow.setPosition(sprite.getPosition() + sf::Vector2f(0,shadow_size.y/2));
	window.draw(shadow);
}

sf::Vector2f Pillar::GetCurrentPositionShadow()
{
	return shadow.getPosition() + sf::Vector2f(0, 0);
}