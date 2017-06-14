#include <Re\Graphics\GraphicsModelPolygon.h>
#include <Re\Graphics\GraphicsAnimationPart.h>


namespace Graphics
{

	ModelPolygon::ModelPolygon()
	{
		scale = Vector2D(1, 1);
		color = Color_f(255, 255, 255, 255);
	}

	ModelPolygon::ModelPolygon(size_t _pointsN, size_t _layersN, const ModelDef & def, TsId tsId)
		: Model(tsId, def)
	{
		setLayers(_pointsN, _layersN);
	}

	ModelPolygon::ModelPolygon(const char * path)
	{
		deserialise(path);
	}

	ModelPolygon * ModelPolygon::setLayers(size_t _pointsN, size_t _layersN)
	{
		pointsN = _pointsN;
		layers.resize(_layersN);
		for (auto&it : layers)
		{
			it.setPointCount(_pointsN);
		}
		return this;
	}

	void ModelPolygon::drawDynamic(RenderTarget & wnd, const RenderStates & states)
	{
		for (auto& it : layers)
			wnd.draw(it);

		if (changeClock.getElapsedTime() > cdChange)
		{
			for (auto &itLayer : layers)
				for (int i = 0; i < pointsN; ++i)
					itLayer.setPoint(i, points[i] + Vector2D(changeRadius, 0).getRotated());
			changeClock.restart();
		}
	}
	void ModelPolygon::drawStatic(RenderTarget & wnd, const RenderStates & states) const
	{
		for (auto& it : layers)
			wnd.draw(it);
	}

	void ModelPolygon::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		/// count offset with animations
		ModelDef def;
		def = *this;

		for (auto &it : parts)
			if (it->isWithinRange())
				it->countOffset(def);


		/// Update
		if (changeClock.getElapsedTime() > cdChange)
		{
			for (auto &itLayer : layers)
				for (int i = 0; i < pointsN; ++i)
				{
					itLayer.setPoint(i, points[i] + Vector2D(changeRadius, 0).getRotated());
					itLayer.setTexture(myTexture);
				}
			changeClock.restart();
		}


		if (childDown)
			target.draw(*childDown, states);


		if (parent)
		{
			lastDef = def.countOffset(parent->lastDef);
			for (auto& it : layers)
			{
				lastDef.update(it);
				target.draw(it);
			}
		}
		else
		{
			lastDef = def;

			for (auto& it : layers)
			{
				lastDef.update(it);
				target.draw(it);
			}
		}

		/// draw sibling
		if (sibling)
			target.draw(*sibling, states);

		if (childUp)
			target.draw(*childUp, states);

	}

	void ModelPolygon::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
	}

	void ModelPolygon::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		ModelDef::deserialiseF(file, loader);
		/// set texture
		TsId tsId = loader.load("ts", 0);
		if (tsId != 0)
			setTexture(tsId, true);
		else
			myTexture = nullptr;

		pointsN = loader.load("pointN", 0u);
		size_t layersN = loader.load("layerN", 0u);
		setLayers(pointsN, layersN);

		cdChange = sf::seconds(loader.load("cdChange", 0.05f));
		changeRadius = loader.load("changeRadius", 5.f);

		for (int i = 0; i < pointsN; ++i)
		{
			stringstream s;
			s << i;
			setPoint(i, Vector2D(
				loader.load("posX" + s.str(), 0),
				loader.load("posY" + s.str(), 0)
			));
		}


		DATA_SCRIPT_MULTILINE(file, loader)
		{
			string b = loader.load<string>("ud", "down");
			ModelPolygon *m = new ModelPolygon();

			if (b == "up")
				addUp(m);
			else // if( b == "down")
				addDown(m);

			m->deserialise(file, loader);
		}
	}
}