#include "Zenon.h"
#include "../Layers.h"


void Zenon::onInit()
{
	Game::Actor::onInit();

	addEfect(new Efect::Rigidbody(7.5f, 5.f));
	addEfect(new Efect::ColliderCircle(50.f));

	addEfect(new Efect::UpdateTransform());
	addEfect(new Efect::GraphicsCircle(sf::Color(200, 100, 100, 100), 65.f));
	addEfect(new Efect::Model("Warrior\\model_Full.txt"));
	addEfect(new Efect::Health());
	addEfect(new Efect::SpawnOnDeath([]()
	{
		auto blood = new Game::Actor;

		blood->addEfect(new Efect::Model("model_blood.txt"));
		//blood->addEfect(new Efect::RemoveAfterDelay(sf::seconds(50)));

		return blood;
	}
	))->setLayer(Game::Layers::blood);

	auto movement = addEfect(new Efect::MovementAim(10.f, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.015)));
	addEfect(new Efect::RandomMovement(movement))->setRadius(100.f)->setOffset(Vector2D(0, 100.f));


}

void Zenon::onUpdate(sf::Time dt)
{
	Game::Actor::onUpdate(dt);

}
