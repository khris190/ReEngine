#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Graphics\Graphics.h>

namespace Efect
{
	/// Efect which will simplyfy maintaining
	/// Models within game objects
	class ModelPolygon : public Base
	{
	public:

		enum UpdateMode
		{
			none,
			toTransform
		}updateMode{ toTransform };

		ModelPolygon() {}
		ModelPolygon(const char* path, UpdateMode _updateMode = toTransform);
		
		virtual void onInit() override;
		virtual void onUpdate(sf::Time dt) override;

		/// setters
		ModelPolygon* setPosition(const Vector2D& position)
		{
			model.pos = position;
			return this;
		}
		ModelPolygon* setRotation(Angle angle)
		{
			model.rot = angle;
			return this;
		}
		ModelPolygon* setScale(const Vector2D& scale)
		{
			model.scale = scale;
			return this;
		}
		ModelPolygon* setColor(Color_f cl)
		{
			model.color = cl;
			return this;
		}
		ModelPolygon* setRotationAround(Angle angle)
		{
			model.rotAround = angle;
			return this;
		}
		ModelPolygon* setParent(Graphics::Model* parent)
		{
			model.parent = parent;
			return this;
		}
		ModelPolygon* setUpdateOwner(Game::Actor* actor)
		{
			updateOwner = actor;
			return this;
		}

		ModelPolygon* setTexture(TsId id, bool updateOrigin = true)
		{
			model.setTexture(id, updateOrigin);
		}
		ModelPolygon* setUpdateMode(UpdateMode _updateMode)
		{
			updateMode = _updateMode;
		}

		ModelPolygon* addPoint(const Vector2D& point)
		{
			model.addPoint(point);
			return this;
		}
		ModelPolygon* setPoint(size_t i, const Vector2D& point)
		{
			model.setPoint(i, point);
			return this;
		}
		ModelPolygon* setChange(sf::Time cd, float32 radius)
		{
			model.setChange(cd, radius);
			return this;
		}
		ModelPolygon* setLayers(size_t _pointsN, size_t _layersN)
		{
			model.setLayers(_pointsN, _layersN);
			return this;
		}


		/// graphics data 
		Graphics::ModelPolygon model;
		Game::Actor*updateOwner{ nullptr };
	};
}