#pragma once
#include "DeathAnimationBase.h"
#include "DrawGestion.h"

class DeathAnimationGestion
{
private:
	static DeathAnimationGestion *s_instance1;
	std::list<std::shared_ptr<DeathAnimationBase>> listAnimations;
public:
	DeathAnimationGestion();
	~DeathAnimationGestion();

	static void Initialize()
	{
		s_instance1 = new DeathAnimationGestion();
	}
	static DeathAnimationGestion *instance()
	{
		if (!s_instance1)
			s_instance1 = new DeathAnimationGestion;
		return s_instance1;
	}

	void Init(sf::Vector2f size_sprite, int number_animation, float frame_per_second, int position_y, sf::Vector2f position, sf::String string_texture);
	void Update();
};

