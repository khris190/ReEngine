#include <Re\Game\Efect\Graphical\EfectModelPolygon.h>
#include <Re\Game\GameActor.h>

namespace Efect
{
	ModelPolygon::ModelPolygon(const char* path, UpdateMode _updateMode)
		:model(path), updateMode(_updateMode)
	{
	}

	void ModelPolygon::onInit()
	{
		updateOwner = getOwner();
	}

	void Efect::ModelPolygon::onUpdate(sf::Time dt)
	{
		if (updateMode == toTransform)
			updateOwner->updateGraphics(model);

		cam.draw(model);
	}

}