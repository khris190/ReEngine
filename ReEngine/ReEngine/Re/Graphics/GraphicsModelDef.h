#pragma once
#include <Re\Common\utility.h>

namespace Graphics
{

	/*
	*	class holding all propertites of model
	*	like color, pos, rotation, scale ect.
	*	updates pransformable
	*/
	class ModelDef : public Res::ISerialisable
	{
	public: /// functions section
		
			/// ctors
		ModelDef(const Vector2D& position = Vector2D(), Angle rot = Angle::zero, 
			Color_f color = Color_f(), 
			const Vector2D& scale = Vector2D(), Angle rotAround = Angle::zero, Vector2D posNoRot = Vector2D());
		ModelDef(std::istream& file, Res::DataScriptLoader& loader) { deserialise(file, loader); }

		/// transforms taken as an argument sprite to fit to this modelDef; 
		/// parametrs of sf::Sprite before has no influence (besides texture&origin data which are not overrided)
		void update(sf::Sprite& toUpdate);
		void update(sf::Sprite& toUpdate, const ModelDef& parent) const;
		ModelDef countOffset(const ModelDef& parent) const;

	public: /// Data section
		Vector2D pos, posNoRot;
		Vector2D scale{Vector2D(1,1)};
		/// rot is rotation of sprite aroumd its origin
		Angle rot, 
		/// rot around is rotation of pos around parent
			rotAround;
		Color_f color;

	public: /// operators section
		ModelDef operator+(const ModelDef& other) const;
		ModelDef operator-(const ModelDef& other) const;
		ModelDef operator*(float32 other) const;
		ModelDef operator/(float32 other) const;

		void operator+=(const ModelDef& other);
		void operator-=(const ModelDef& other);
		void operator*=(float32 other);
		void operator/=(float32 other);

	protected: /// ISerialisable section
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;

	public: /// predefined values section

		/// default ModelDef, not changing sprite at update; to use in Model class
		static const ModelDef default;
		/// ModelDef with all values equal to 0; to use in animation class
		static const ModelDef zero;
	};

}