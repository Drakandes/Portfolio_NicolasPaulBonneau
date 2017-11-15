#include "stdafx.h"
#include "CollisionGestion.h"

CollisionGestion::CollisionGestion()
{
}

CollisionGestion::~CollisionGestion()
{
}

void CollisionGestion::CollisionUpdate(std::list<std::shared_ptr<MonsterBase>> &listMonsters, std::shared_ptr<CollisionalObject> player,TextGenerator &text_generator, std::list<std::shared_ptr<ProjectileBase>> listNatureObjects)
{
	/*std::list<ProjectileBase*> listProjectiles = ProjectileGestion::instance()->GetListProjectiles();
	std::list<ProjectileBase*> listProjectilesAffectingEverything = ProjectileGestion::instance()->GetListProjectilesAffectingEverything();

	bool iterator3_done = true;

	if (listProjectilesAffectingEverything.size() > 0)
	{
		iterator3_done = false;
	}

	std::list<ProjectileBase*>::iterator iterator3 = listProjectilesAffectingEverything.begin();
	std::list<ProjectileBase*>::iterator iterator2 = listProjectiles.begin();
	while (iterator2 != listProjectiles.end())
	{
		sf::Vector2f position_projectile = (*iterator2)->GetCurrentPosition();
		bool can_push = (*iterator2)->CanPush();
		bool can_slow = (*iterator2)->CanSlow();
		bool can_stun = (*iterator2)->CanStun();
		bool can_create_explosion = (*iterator2)->CanCreateExplosion();
		bool can_change_stat = (*iterator2)->CanChangeObjectStat();
		bool can_reset_cooldown_skill = (*iterator2)->CanChangeSkillCooldown();
		float stun_time = (*iterator2)->GetStunTime();
		bool can_affect_player = (*iterator2)->CanAffectPlayer();
		bool can_affect_monster = (*iterator2)->CanAffectMonster();
		float damage_explosion = (*iterator2)->GetDamageExplosion();
		int rayon_projectile = (*iterator2)->GetRayon();
		sf::Vector2f size_projectile = (*iterator2)->GetSize();
		sf::FloatRect rect_collision_projectile = (*iterator2)->GetCollisionRect();

		bool can_ignite_second_list;
		bool can_push_second_list;
		bool can_slow_second_list;
		bool can_stun_second_list;
		bool can_create_explosion_second_list;
		bool can_change_stat_second_list;
		bool can_reset_cooldown_skill_second_list;
		float stun_time_second_list;
		bool can_affect_player_second_list;
		bool can_affect_monster_second_list;
		float damage_explosion_second_list;
		int rayon_projectile_second_list;
		sf::Vector2f position_projectile_second_list;
		sf::Vector2f size_projectile_second_list;
		sf::FloatRect rect_collision_projectile_second_list;

		if (!iterator3_done)
		{
			can_ignite_second_list = (*iterator3)->CanIgnite();
			can_push_second_list = (*iterator3)->CanPush();
			can_slow_second_list = (*iterator3)->CanSlow();
			can_stun_second_list = (*iterator3)->CanStun();
			can_create_explosion_second_list = (*iterator3)->CanCreateExplosion();
			can_change_stat_second_list = (*iterator3)->CanChangeObjectStat();
			can_reset_cooldown_skill_second_list = (*iterator3)->CanChangeSkillCooldown();
			stun_time_second_list = (*iterator3)->GetStunTime();
			can_affect_player_second_list = (*iterator3)->CanAffectPlayer();
			can_affect_monster_second_list = (*iterator3)->CanAffectMonster();
			damage_explosion_second_list = (*iterator3)->GetDamageExplosion();
			rayon_projectile_second_list = (*iterator3)->GetRayon();
			position_projectile_second_list = (*iterator3)->GetCurrentPosition();
			size_projectile_second_list = (*iterator3)->GetSize();
			rect_collision_projectile_second_list = (*iterator3)->GetCollisionRect();
		}

		std::list<ProjectileBase*>::iterator iteratorNature = listNatureObjects.begin();
		while (iteratorNature != listNatureObjects.end())
			if (!((*iteratorNature)->CheckIfProjectileDisable()))
			{
				if ((*iteratorNature)->CheckCollision(rect_collision_projectile, 1,position_projectile))
				{
					(*iterator2)->DealWithCollision(*iteratorNature);
				}
			}
			iteratorNature++;
		}

		std::list<MonsterBase*>::iterator iterator = listMonsters.begin();
		while (iterator != listMonsters.end())
		{
			sf::Vector2f position_monster = (*iterator)->GetCurrentPosition();
			sf::Vector2f size_monster = (*iterator)->GetSize();
			int id_monster = (*iterator)->GetId();
			int rayon_monster = (*iterator)->GetRayon();
			sf::FloatRect rect_collision_monster = (*iterator)->GetCollisionRect();

			if (can_affect_monster)
			{
				if ((*iterator2)->CheckCollision(rect_collision_monster, id_monster, position_monster))
				{
					(*iterator2)->DealWithCollision(*iterator);
					(*iterator)->DealWithCollision(*iterator2);
				}
			}
			if (!iterator3_done)
			{
				if (can_affect_monster_second_list)
				{
					if ((*iterator3)->CheckCollision(rect_collision_monster, id_monster, position_monster))
					{
						(*iterator3)->DealWithCollision(*iterator);
						(*iterator)->DealWithCollision(*iterator3);
					}
				}
			}
			//NeedToAddExplosionToProjectile
			float damage_dealt1 = (*iterator)->GotDamaged(ExplosionGenerator::instance()->CheckAllExplosionCollision(rayon_monster, position_monster, size_monster, (*iterator)->GetId()));
			text_generator.GenerateOneTextForBlob(position_monster, damage_dealt1, size_monster, (*iterator));

			iterator++;
		}

		std::list<ProjectileBase*>::iterator iterator4 = listProjectilesAffectingEverything.begin();
		while (iterator4 != listProjectilesAffectingEverything.end())
		{
			if ((*iterator2)->CheckCollision((*iterator4)->GetCollisionRect(), -2, (*iterator4)->GetCurrentPosition()))
			{
				(*iterator4)->DealWithCollision(*iterator2);
				(*iterator2)->DealWithCollision(*iterator4);
			}
			iterator4++;
		}

		sf::Vector2f position_player = player->GetCurrentPosition();
		sf::Vector2f size_player = player->GetSize();
		int rayon_player = player->GetRayon();
		sf::FloatRect rect_collision_player = player->GetCollisionRect();

		if (can_affect_player)
		{
			if ((*iterator2)->CheckCollision(rect_collision_player, -1, position_player))
			{
				player->DealWithCollision(*iterator2);
				(*iterator2)->DealWithCollision(player);
			}
		}
		bool is_to_delete = (*iterator2)->IsNeedToDelete();
		if (is_to_delete)
		{
			listProjectiles.erase(iterator2++);
		}
		else
		{
			iterator2++;
		
		}
		if (!iterator3_done)
		{
			bool is_to_delete = (*iterator3)->IsNeedToDelete();
			if (is_to_delete)
			{
				listProjectilesAffectingEverything.erase(iterator3++);
				if (iterator3 == listProjectilesAffectingEverything.end())
				{
					iterator3_done = true;
				}
			}
			else
			{
				iterator3++;
				if (iterator3 == listProjectilesAffectingEverything.end())
				{
					iterator3_done = true;
				}
			}
		}
	}
	std::list<MonsterBase*>::iterator iterator = listMonsters.begin();
	while (iterator != listMonsters.end())
	{
		sf::Vector2f position_player = player->GetCurrentPosition();
		sf::Vector2f size_player = player->GetSize();
		int rayon_player = player->GetRayon();
		sf::Vector2f position_monster = (*iterator)->GetCurrentPosition();
		sf::Vector2f size_monster = (*iterator)->GetSize();
		int id_monster = (*iterator)->GetId();
		int rayon_monster = (*iterator)->GetRayon();

		if (GlobalFunction::Check_collision(rayon_monster, rayon_player, position_monster, position_player, size_monster, size_player))
		{
			(*iterator)->DealWithCollision(player);
			player->DealWithCollision(*iterator);
		}
		iterator++;
	}

	std::list<ProjectileBase*>::iterator iteratorNature = listNatureObjects.begin();
	while (iteratorNature != listNatureObjects.end())
	{
		if (!((*iteratorNature)->CheckIfProjectileDisable()))
		{
			sf::Vector2f position_nature_object = (*iteratorNature)->GetCurrentPosition();

			std::list<MonsterBase*>::iterator iteratorMonster = listMonsters.begin();
			while (iteratorMonster != listMonsters.end())
			{
				sf::Vector2f position_monster = (*iteratorMonster)->GetCurrentPosition();
				sf::Vector2f size_monster = (*iteratorMonster)->GetSize();
				int rayon_monster = (*iteratorMonster)->GetRayon();
				sf::FloatRect rect_collision_monster = (*iteratorMonster)->GetCollisionRect();
				if ((*iteratorNature)->CheckCollision(rect_collision_monster,0, position_monster))
				{
					(*iteratorMonster)->DealWithCollision(*iteratorNature);
					(*iteratorNature)->DealWithCollision(*iteratorMonster);
				}

				iteratorMonster++;
			}

			sf::Vector2f position_player = player->GetCurrentPosition();
			sf::Vector2f size_player = player->GetSize();
			int rayon_player = player->GetRayon();
			sf::FloatRect rect_collision_player = player->GetCollisionRect();
			if ((*iteratorNature)->CheckCollision(rect_collision_player,0, position_player))
			{
				player->DealWithCollision(*iteratorNature);
				(*iteratorNature)->DealWithCollision(player);
			}
		}
		iteratorNature++;
	}*/

	//quadtree->Clear();

	/*for (size_t i = 0; i < 11; i++)
	{
		RectTest* rect = new RectTest(sf::Vector2f(850, 850));
		quadtree->insert(rect->GetCurrentPosition(), rect->GetSize(), rect);
		DrawGestion::instance()->AddObjectToList(rect);
	}*/

	/*std::list<ProjectileBase*> listProjectiles = ProjectileGestion::instance()->GetListProjectiles();
	std::list<ProjectileBase*> listProjectilesAffectingEverything = ProjectileGestion::instance()->GetListProjectilesAffectingEverything();

	std::list<ProjectileBase*>::iterator iterator3 = listProjectilesAffectingEverything.begin();
	std::list<ProjectileBase*>::iterator iterator2 = listProjectiles.begin();
	std::list<MonsterBase*>::iterator iterator1 = listMonsters.begin();
	std::list<ProjectileBase*>::iterator iterator4 = listNatureObjects.begin();

	while (iterator1 != listMonsters.end())
	{
		bool is_to_delete = (*iterator1)->IsNeedToDelete();
		if (is_to_delete)
		{
			listMonsters.erase(iterator1++);
		}
		else
		{
			quadtree->insert((*iterator1)->GetCurrentPosition(),(*iterator1)->GetSize(),(*iterator1));
			iterator1++;
		}
	}
	while (iterator4 != listNatureObjects.end())
	{
		bool is_to_delete = (*iterator4)->IsNeedToDelete();
		if (is_to_delete)
		{
			listNatureObjects.erase(iterator4++);
		}
		else
		{
			quadtree->insert((*iterator4)->GetCurrentPosition(), (*iterator4)->GetSize(), (*iterator4));
			iterator4++;
		}
	}

	while (iterator3 != listProjectilesAffectingEverything.end())
	{
		bool is_to_delete = (*iterator3)->IsNeedToDelete();
		if (is_to_delete)
		{
			listProjectilesAffectingEverything.erase(iterator3++);
		}
		else
		{
			quadtree->insert((*iterator3)->GetCurrentPosition(), (*iterator3)->GetSize(), (*iterator3));
			iterator3++;
		}
	}

	while (iterator2 != listProjectiles.end())
	{
		bool is_to_delete = (*iterator2)->IsNeedToDelete();
		if (is_to_delete)
		{
			listProjectiles.erase(iterator2++);
		}
		else
		{
			quadtree->insert((*iterator2)->GetCurrentPosition(), (*iterator2)->GetSize(), (*iterator2));
			iterator2++;
		}
	}

	quadtree->insert(player->GetCurrentPosition(), player->GetSize(), player);
	quadtree->CheckCollision();*/
}


