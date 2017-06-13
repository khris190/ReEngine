#include "WarriorPlayer.h"
#include "Skills/EfectSkillManager.h"
#include "Skills\EfectSkillShadowSpear.h"

void WarriorPlayer::onInit()
{
	Game::Actor::onInit();

	addEfect(new Efect::Rigidbody(25.f, 20.f));
	addEfect(new Efect::ColliderCircle(50.f,0.5f));

	addEfect(new Efect::UpdateTransform());
	addEfect(new Efect::GraphicsCircle(sf::Color(100, 200, 100, 100), 65.f));
	auto efModel = addEfect(new Efect::Model("Warrior\\model_Full.txt"));
	addEfect(new Efect::FollowCamera(Efect::FollowCamera::positionOnlySmooth))->setLerpPosition(0.125);

	addEfect(new Efect::Animation("anim_swingWeaponLeft.txt", efModel->model))
		->eventControllAnimation = [](Graphics::AnimationController& cont) { cont.updateReturn(); };

	addEfect(new Efect::SkillManager)->setRadius({ 175,250,450 })
		->addSkill(new Efect::SkillShadowSpear(":) 1 "), 
			{
				make_pair(1,5), make_pair(1,9) ,make_pair(1,13) ,
				make_pair(5,9), make_pair(5,13),
				make_pair(9,13)
			})
		;

	//addEfect(new Efect::MouseMovement(50.f, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.03) ) );
	addEfect(new Efect::StaticMovement(30.f, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.025)));

}