#include <Re\Game\Efect\Graphical\EfectModel.h>
#include <Re\Game\GameActor.h>
namespace Efect
{
	Model::Model(const char* path, UpdateMode _updateMode)
		:model(path), updateMode(_updateMode)
	{
	}

	Model::Model(TsId ts, UpdateMode _updateMode)
		:model(ts), updateMode(_updateMode)
	{
	}

	void Model::onInit()
	{
		updateOwner = getOwner();
	}

	void Efect::Model::onUpdate(sf::Time dt)
	{
		if (updateMode == toTransform)
			updateOwner->updateGraphics(model);

		cam.draw(model);
	}

}