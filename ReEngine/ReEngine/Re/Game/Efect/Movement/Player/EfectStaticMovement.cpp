#include <Re\Game\Efect\Movement\Player\EfectStaticMovement.h>
#include <Re\Game\Game.h>

namespace Efect
{
	StaticMovement::StaticMovement(float32 _linearSpeed,
		RotateToDirection *_efRotDir,
		string _codeUp, string _codeDown, 
		string _codeLeft, string _codeRight)
		: codeUp(_codeUp), codeDown(_codeDown), codeLeft(_codeLeft), codeRight(_codeRight)
		, linearSpeed(_linearSpeed), efRotDir(_efRotDir)
	{
		
	}
	StaticMovement::StaticMovement(float32 _linearSpeed,
		string _codeUp, string _codeDown,
		string _codeLeft, string _codeRight)
		: codeUp(_codeUp), codeDown(_codeDown), codeLeft(_codeLeft), codeRight(_codeRight)
		, linearSpeed(_linearSpeed), efRotDir(new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.11f))
	{

	}

	void StaticMovement::onInit()
	{
		if (efRotDir)
		{
			getOwner()->addEfect(efRotDir);
		}
	}

	void StaticMovement::onUpdate(sf::Time dt)
	{
		assert(getOwner()->isRigidbodyCreated());
		Vector2D offset;
		bool moved = false;

		if (actionMap.isActive(codeUp))
		{
			--offset.y;
			moved = true;
		}
		if (actionMap.isActive(codeDown))
		{
			++offset.y;
			moved = true;
		}
		if (actionMap.isActive(codeLeft))
		{
			--offset.x;
			moved = true;
		}
		if (actionMap.isActive(codeRight))
		{
			++offset.x;
			moved = true;
		}
		
		if (moved)
		{
			offset.normalise();
			getOwner()->getRigidbody().ApplyForceToCenter(offset*linearSpeed*dt.asSeconds()*1000, true);
			if (efRotDir)
				efRotDir->direction = offset.angle();
		}
	}

	StaticMovementNoRigidbody::StaticMovementNoRigidbody(float32 linearSpeed, RotateToDirection *efRotDir, string codeUp, string codeDown, string codeLeft, string codeRight)
		: StaticMovement(linearSpeed, efRotDir, codeUp, codeDown, codeLeft, codeRight)
	{
	}

	void StaticMovementNoRigidbody::onUpdate(sf::Time dt)
	{
		Vector2D offset;
		bool moved = false;

		if (actionMap.isActive(codeUp))
		{
			--offset.y;
			moved = true;
		}
		if (actionMap.isActive(codeDown))
		{
			++offset.y;
			moved = true;
		}
		if (actionMap.isActive(codeLeft))
		{
			--offset.x;
			moved = true;
		}
		if (actionMap.isActive(codeRight))
		{
			++offset.x;
			moved = true;
		}

		if (moved)
		{
			offset.normalise();
			getOwner()->move(offset*linearSpeed*dt.asSeconds()*1000);
			if (efRotDir)
				efRotDir->direction = offset.angle();
		}
	}

}