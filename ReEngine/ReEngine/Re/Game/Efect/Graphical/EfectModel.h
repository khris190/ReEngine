#pragma once
#include <Re\Game\Efect\EfectBase.h>
#include <Re\Graphics\Graphics.h>


namespace Efect
{
	/// Efect which will simplyfy maintaining
	/// Models within game objects
	class Model : public Base
	{
	public:

		enum UpdateMode
		{
			none,
			toTransform
		}updateMode{ toTransform };

		Model() {}
		Model(const char* path, UpdateMode _updateMode = toTransform);
		Model(TsId ts, UpdateMode _updateMode = toTransform);

		virtual void onInit() override;
		virtual void onUpdate(sf::Time dt) override;

		Model* setPosition(const Vector2D& position)
		{
			model.pos = position;
			return this;
		}
		Model* setRotation(Angle angle)
		{
			model.rot = angle;
			return this;
		}
		Model* setScale(const Vector2D& scale)
		{
			model.scale = scale;
			return this;
		}
		Model* setColor(Color_f cl)
		{
			model.color = cl;
			return this;
		}
		Model* setRotationAround(Angle angle)
		{
			model.rotAround = angle;
			return this;
		}
		Model* setParent(Graphics::Model* parent)
		{
			model.parent = parent;
			return this;
		}
		Model* setUpdateOwner(Game::Actor* actor)
		{
			updateOwner = actor;
			return this;
		}

		Model* setTexture(TsId id, bool updateOrigin = true)
		{
			model.setTexture(id, updateOrigin);
		}
		Model* setUpdateMode(UpdateMode _updateMode)
		{
			updateMode = _updateMode;
		}

		/// graphics data 
		Graphics::Model model;
		Game::Actor*updateOwner{nullptr};
	};
}