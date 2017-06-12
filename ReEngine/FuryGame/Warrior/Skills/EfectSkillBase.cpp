#include "EfectSkillBase.h"

namespace Efect
{
	void SkillJump::onStart()
	{
		baseMovementSpeed = movement->movementSpeed;
	}
	void SkillJump::onUpdate(sf::Time dt)
	{
		SkillBase::onUpdate(dt);

		if (isReady())
		{
			movement->movementSpeed = movementSpeedSprint;
		}

	}
}