#include <Re\Game\Efect\Graphical\EfectAnimation.h>

namespace Efect
{
	Animation::Animation(const char * path)
		:controller(path)
	{
	}

	Animation::Animation(const char * path, Graphics::Model & model)
		: controller(path)
	{
		controller.attachToModel(model);
	}

	void Animation::onUpdate(sf::Time dt)
	{
		eventControllAnimation(controller);
	}

}