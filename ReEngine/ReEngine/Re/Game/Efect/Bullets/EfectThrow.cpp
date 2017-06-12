#include <Re\Game\Efect\Bullets\EfectThrow.h>
#include <Re\Game\Game.h>
extern RenderWindow wnd;

namespace Efect
{
	Throw::Throw(function<Game::Actor*()> _createBullet, 
		function<bool()> _conditionToFire)
		: createBullet(_createBullet), conditionToFire(_conditionToFire)
	{
	}

	void Throw::onUpdate(sf::Time dt)
	{
		if (conditionToFire())
		{
			auto bullet = createBullet();
			if (bullet == nullptr)
				return;
			Game::world.addActor(bullet, getLayer() );

			if (bullet->isRigidbodyCreated())
				bullet->getRigidbody().SetTransform(
		
					bullet->getRigidbody().GetPosition() 
					+ offset.getRotated(rotation + getOwner()->getRotation())*toB2Position
					+ (Vector2D)getOwner()->getPosition()*toB2Position
					,
					bullet->getRigidbody().GetAngle()
					+ getOwner()->getRotation().asRadian()
				);
			else
			{
				bullet->move(offset.getRotated(rotation + getOwner()->getRotation())
					+ getOwner()->getPosition());
				bullet->rotate(getOwner()->getRotation().asDegree());
			}
		}
	}
	bool Throw::conditionToFire_default()
	{
		return actionMap.isActive("fire2") && wnd.hasFocus();
	}
}