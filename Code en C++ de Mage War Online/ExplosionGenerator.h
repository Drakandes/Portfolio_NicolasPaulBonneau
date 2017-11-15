#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Explosion.h"
#include <iostream>
#include <list>

class ExplosionGenerator
{
private:
	std::list<std::shared_ptr<Explosion>> listExplosionsCreated;
	static ExplosionGenerator *s_instance1;
public:
	ExplosionGenerator();
	~ExplosionGenerator();

	static void Initialize()
	{
		s_instance1 = new ExplosionGenerator();
	}
	static ExplosionGenerator *instance()
	{
		if (!s_instance1)
			s_instance1 = new ExplosionGenerator;
		return s_instance1;
	}

	void GenerateOneExplosion(sf::Vector2f size_explosion, sf::Vector2f position_explosion, float damage_explosion, float explosion_size_modifer);
	std::list<std::shared_ptr<Explosion>> GetListExplosions() { return listExplosionsCreated; }
	void EmptyListExplosion() { listExplosionsCreated.clear(); }
};

