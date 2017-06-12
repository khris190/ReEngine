#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Game\Actor\GameLayer.h>


namespace Efect
{
	class Throw : public Base
	{
	public:
		Throw(function<Game::Actor*()> createBullet,
			function<bool()> conditionToFire = &conditionToFire_default
		);

		void onUpdate(sf::Time dt) override;

		Throw* setOffset(Vector2D _offset, Angle _rotation)
		{
			offset = _offset;
			rotation = _rotation;
			return this;
		}

		Throw* setLayer(function<Game::Layer*()> layerF)
		{
			getLayer = layerF;
			return this;
		}
		Throw* setLayer(Game::Layer* layer)
		{
			getLayer = [=]() {return layer;  };
			return this;
		}

		/// condition to spawn (eg. pressing button)
		/// default one is pressing Action ["fire1"]
		function<bool()> conditionToFire;
		static bool conditionToFire_default();
		function<Game::Actor*()> createBullet;
		
		/// data which defines spawning pos
		/// relative to owner
		Vector2D offset;
		Angle rotation;
		function<Game::Layer*()> getLayer;
	};
}