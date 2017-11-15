#include "stdafx.h"
#include "ExplosionGenerator.h"


ExplosionGenerator::ExplosionGenerator()
{
}

ExplosionGenerator::~ExplosionGenerator()
{
}

void ExplosionGenerator::GenerateOneExplosion(sf::Vector2f size_explosion, sf::Vector2f position_explosion, float damage_explosion, float explosion_size_modifer)
{
	std::shared_ptr<Explosion>  explosion = std::shared_ptr<Explosion>(new Explosion());
	explosion->Init(size_explosion, position_explosion, damage_explosion, explosion_size_modifer);
	listExplosionsCreated.push_back(explosion);
	explosion.reset();
}

ExplosionGenerator* ExplosionGenerator::s_instance1 = 0;