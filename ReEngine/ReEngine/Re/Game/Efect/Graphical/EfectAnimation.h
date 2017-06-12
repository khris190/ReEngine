#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Graphics\GraphicsAnimationController.h>

namespace Efect
{
	class Animation : public Base
	{
	public:
		Animation() {};
		Animation(const char* path);
		Animation(const char* path, Graphics::Model & model);

		void onUpdate(sf::Time dt) override;

		/// event used for controlling animation while gameplay
		function<void(Graphics::AnimationController&)> eventControllAnimation{ [] (Graphics::AnimationController&){} };

		Graphics::AnimationController controller;
	};


}