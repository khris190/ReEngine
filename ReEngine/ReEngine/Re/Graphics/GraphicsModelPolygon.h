#pragma once
#include <Re\Graphics\GraphicsModelDef.h>
#include <Re\Graphics\GraphicsModel.h>

namespace Graphics
{
	class ModelPolygon : public Model
	{
	public:
		ModelPolygon();
		/// manualy set model
		ModelPolygon(size_t _pointsN, size_t _layersN, const ModelDef& def = ModelDef::default, TsId tsId = 0);
		/// load model from path
		ModelPolygon(const char* path);

		/// setters
		ModelPolygon* addDown(ModelPolygon *s) { Model::addDown(s); return this; }
		ModelPolygon* addUp(ModelPolygon *s) { Model::addUp(s); return this; }
		ModelPolygon* addPoint(const Vector2D& point)
		{
			assert(pointsN < points.size());
			points[++pointsN] = point;
			return this;
		}
		ModelPolygon* setPoint(size_t i, const Vector2D& point)
		{
			assert(i < pointsN);
			points[i] = point;
			return this;
		}
		ModelPolygon* setChange(sf::Time cd, float32 radius)
		{
			cdChange = cd;
			changeRadius = radius;
			return this;
		}
		ModelPolygon* setLayers(size_t _pointsN, size_t _layersN);

		/// getters
		ModelPolygon* getChildUp()
		{
			return (ModelPolygon*)Model::getChildUp();
		}
		ModelPolygon* getChildDown()
		{
			return (ModelPolygon*)Model::getChildDown();
		}
		ModelPolygon* getChildSibling()
		{
			return (ModelPolygon*)Model::getChildSibling();
		}
		ModelPolygon* getParent()
		{
			return (ModelPolygon*)Model::parent;
		}

		Vector2D getPoint(size_t i)
		{
			return points[i];
		}
		size_t getLayersN() { return layers.size(); }
		size_t getPointsN() { return pointsN; }
		sf::Time getCdChange() { return cdChange; }
		float32 getChangeRadius() { return changeRadius; }

	public: /// drawing
		void drawDynamic(RenderTarget& wnd, const RenderStates& states);
		void drawStatic(RenderTarget& wnd, const RenderStates& states) const;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		/// default positions of all points
		array<Vector2D, 8> points;
		/// points used
		size_t pointsN{ 0 };

		mutable vector<ConvexShape> layers;

		/// how far positions on layers can be changed;
		float32 changeRadius{ 0 };
		/// how often positions on layers change
		Time cdChange{ seconds(0.15f) };
		mutable Clock changeClock;

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};
}