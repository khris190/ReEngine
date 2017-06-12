#include "WarriorPlayer.h"



void WarriorPlayer::onInit()
{
	Game::Actor::onInit();

	addEfect(new Efect::Rigidbody(25.f, 20.f));
	addEfect(new Efect::ColliderCircle(50.f,0.5f));

	addEfect(new Efect::UpdateTransform());
	addEfect(new Efect::GraphicsCircle(sf::Color(100, 200, 100, 100), 65.f));
	auto efModel = addEfect(new Efect::Model("Warrior\\model_Full.txt"));
	addEfect(new Efect::FollowCamera(Efect::FollowCamera::positionOnlySmooth))->setLerpPosition(0.025);

	addEfect(new Efect::Animation("anim_swingWeaponLeft.txt", efModel->model))
		->eventControllAnimation = [](Graphics::AnimationController& cont) { cont.updateReturn(); };

	//addEfect(new Efect::MouseMovement(50.f, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.03) ) );
	addEfect(new Efect::StaticMovement(50.f, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.025)));

}