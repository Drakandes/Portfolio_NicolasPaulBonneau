#include "stdafx.h"
#include "DeathAnimationGestion.h"

DeathAnimationGestion::DeathAnimationGestion()
{
}

DeathAnimationGestion::~DeathAnimationGestion()
{
}

void DeathAnimationGestion::Init(sf::Vector2f size_sprite, int number_animation, float frame_per_second, int position_y, sf::Vector2f position, sf::String string_texture)
{
	std::shared_ptr<DeathAnimationBase> animation = std::shared_ptr<DeathAnimationBase>(new DeathAnimationBase());
	animation->Init(size_sprite, number_animation, frame_per_second, position_y, position, string_texture);
	listAnimations.push_back(animation);
	animation.reset();
}

void DeathAnimationGestion::Update()
{
	std::list<std::shared_ptr<DeathAnimationBase>>::iterator i = listAnimations.begin();
	while (i != listAnimations.end())
	{
		(*i)->Update();

		if ((*i)->CheckIfToDelete())
		{
			listAnimations.erase(i++);
		}
		else
		{
			DrawGestion::instance()->AddObjectToList((*i));
			i++;
		}
	}
}

DeathAnimationGestion* DeathAnimationGestion::s_instance1 = 0;