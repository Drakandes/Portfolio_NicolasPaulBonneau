#pragma once
#include "BaseSimpleProjectile.h"
#include "PetBase.h"

class TransparentRect :
	public BaseSimpleProjectile
{
private:
	std::shared_ptr<PetBase> parent;
	sf::RectangleShape rect;
public:
	TransparentRect();
	~TransparentRect();

	virtual sf::Vector2f GetCurrentPosition() { return rect.getPosition(); }
	virtual sf::FloatRect GetCollisionRect() { return rect.getGlobalBounds(); }
	void Init(sf::Vector2f &position_initial, std::shared_ptr<PetBase> parent_pet, sf::Vector2f size_received);
	virtual void MovementGestion(float DELTATIME);
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return false; }
};

