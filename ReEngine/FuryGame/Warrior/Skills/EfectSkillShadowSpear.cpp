#include "EfectSkillShadowSpear.h"
#include "../../Layers.h"

namespace Efect
{






	void SkillShadowSpear::onInit()
	{
		auto efThrow = getOwner()->getEfect<Efect::Throw>();
		if (!efThrow)
			efThrow = getOwner()->addEfect(new Efect::Throw);

		efThrow->addData(createBullet, [=]() { return isExecuting();  })
			->setDataTransform(Vector2D(0, -175), Angle::zero)
			->setDataLayer(Game::Layers::bullet);

		//getOwner()->addEfect(new Efect::Sound(1))->setWhenPlaying([=]() {return isExecuting(); });

		/*getOwner()->addEfect(new Efect::Throw([=]() {return createBullet();  }))
			->setLayer(Game::Layers::bullet)
			->setOffset(Vector2D(0, -175), Angle::zero)
			->conditionToFire = [=]() { return isExecuting();  };*/
	}

	bool SkillShadowSpear::execute()
	{
		return true;
	}

	bool SkillShadowSpear::condition()
	{
		return true;
	}

	Game::Actor * SkillShadowSpear::createBullet()
	{
		Game::Actor* bullet = new Game::Actor;
		bullet->addEfect(new Efect::Rigidbody(10.f, 10.f));
		bullet->addEfect(new Efect::ColliderCircle(40, 1.f))->fixtureDef.isSensor = true;

		bullet->addEfect(new Efect::RemoveOnCollision());
		bullet->addEfect(new Efect::DamageOnCollision(100));
		bullet->addEfect(new Efect::UpdateTransform());
		bullet->addEfect(new Efect::Model("Warrior\\model_body.txt"));
		bullet->addEfect(new Efect::RemoveAfterDelay(sf::seconds(1.f)));
		bullet->addEfect(new Efect::Motor(50));
		return bullet;
	}

}