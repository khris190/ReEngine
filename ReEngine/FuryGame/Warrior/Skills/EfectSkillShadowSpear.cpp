#include "EfectSkillShadowSpear.h"
#include "../../Layers.h"

namespace Efect
{






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
		Game::Actor* bullet = Game::world.addActor(new Game::Actor, Game::Layers::bullet);
		//bullet->
		return bullet;
	}

}