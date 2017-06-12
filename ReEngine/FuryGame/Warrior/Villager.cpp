#include "Villager.h"

void Villager::onInit()
{
	Game::Actor::onInit();

	addEfect(new Efect::Rigidbody(7.5f, 5.f));
	addEfect(new Efect::ColliderCircle(50.f));

	addEfect(new Efect::UpdateTransform());
	addEfect(new Efect::GraphicsCircle(sf::Color(200, 100, 100, 100), 65.f));
	addEfect(new Efect::Model("Warrior\\model_Full.txt"));

	//model.deserialise("Warrior\\model_Full.txt");

	auto movement = addEfect(new Efect::MovementAim(10.f, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.015)));
	addEfect(new Efect::RandomMovement( movement))->setRadius(100.f)->setOffset(Vector2D(0,100.f));

}

void Villager::onUpdate(sf::Time dt)
{
	Game::Actor::onUpdate(dt);

	/*setPosition((Vector2D)getRigidbody().GetPosition() * toSfPosition);
	setRotation(Radian(getRigidbody().GetAngle()).asDegree());
	
	updateGraphics(model);
	cam.draw(model);*/
}