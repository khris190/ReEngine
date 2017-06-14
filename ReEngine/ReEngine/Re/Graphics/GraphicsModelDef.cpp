#include <Re\Graphics\GraphicsModelDef.h>

namespace Graphics
{
	const ModelDef ModelDef::default(Vector2D(), Angle::zero, Color_f(255.f, 255.f, 255.f, 255.f),  Vector2D(1,1), Angle::zero );
	const ModelDef ModelDef::zero(Vector2D(), Angle::zero, Color_f(), Vector2D(), Angle::zero);

	ModelDef::ModelDef(const Vector2D & _position, Angle _rot, Color_f _color, const Vector2D & _scale, Angle _rotAround, Vector2D _posNoRot)
		: pos(_position), rot(_rot), color(_color), scale(_scale), rotAround(_rotAround), posNoRot(_posNoRot)
	{
	}
	void ModelDef::update(sf::Sprite & toUpdate)
	{
		toUpdate.setPosition(posNoRot);
		toUpdate.setRotation(rot.asDegree());
		toUpdate.setScale(scale);

		/// color is non depended on parent
		toUpdate.setColor( sf::Color( 
			clamp(color.r, 0.f, 255.f), 
			clamp(color.g, 0.f, 255.f), 
			clamp(color.b, 0.f, 255.f), 
			clamp(color.a, 0.f, 255.f)
		));
	}
	void ModelDef::update(ConvexShape & toUpdate)
	{
		toUpdate.setPosition(posNoRot);
		toUpdate.setRotation(rot.asDegree());
		toUpdate.setScale(scale);

		/// color is non depended on parent
		toUpdate.setFillColor(sf::Color(
			clamp(color.r, 0.f, 255.f),
			clamp(color.g, 0.f, 255.f),
			clamp(color.b, 0.f, 255.f),
			clamp(color.a, 0.f, 255.f)
		));
	}
	void ModelDef::update(sf::Sprite & toUpdate, const ModelDef& parent) const
	{
		countOffset(parent).update(toUpdate);
	}

	ModelDef ModelDef::countOffset(const ModelDef & parent) const
	{
		ModelDef def = *this;

		def.posNoRot += (pos*parent.scale).getRotated(rotAround + parent.rot) + parent.posNoRot;
		def.rot += parent.rot;
		def.scale *= parent.scale;

		return def;
	}

	ModelDef ModelDef::operator+(const ModelDef & other)  const
	{
		ModelDef def;
		def.pos = pos + other.pos;
		def.posNoRot= posNoRot+ other.posNoRot;
		def.rot = rot+ other.rot;
		def.rotAround = rotAround+ other.rotAround;
		def.scale = scale + other.scale;
		def.color = color + other.color;
		return def;
	}
	ModelDef ModelDef::operator-(const ModelDef & other) const
	{
		ModelDef def;
		def.pos = pos - other.pos;
		def.posNoRot = posNoRot - other.posNoRot;
		def.rot = rot - other.rot;
		def.rotAround = rotAround - other.rotAround;
		def.scale = scale - other.scale;
		def.color = color - other.color;
		return def;
	}
	ModelDef ModelDef::operator*(float32 other) const
	{
		ModelDef def;
		def.pos = pos * other;
		def.posNoRot = posNoRot * other;
		def.rot = rot * other;
		def.rotAround = rotAround * other;
		def.scale = scale * other;
		def.color = color * other;
		return def;
	}
	ModelDef ModelDef::operator/(float32 other) const
	{
		assert(other != 0);
		ModelDef def;
		def.pos = pos / other;
		def.posNoRot = posNoRot / other;
		def.rot = rot / other;
		def.rotAround = rotAround / other;
		def.scale = scale / other;
		def.color = color / other;
		return def;
	}
	void ModelDef::operator+=(const ModelDef & other)
	{
		pos += other.pos;
		posNoRot += other.posNoRot;
		rot += other.rot;
		rotAround += other.rotAround;
		scale += other.scale;
		color += other.color;
	}
	void ModelDef::operator-=(const ModelDef & other)
	{
		pos -= other.pos;
		posNoRot -= other.posNoRot;
		rot -= other.rot;
		rotAround -= other.rotAround;
		scale -= other.scale;
		color -= other.color;
	}
	void ModelDef::operator*=(float32 other)
	{
		pos *= other;
		posNoRot *= other;
		rot *= other;
		rotAround *= other;
		scale *= other;
		color *= other;
	}
	void ModelDef::operator/=(float32 other)
	{
		assert(other != 0);
		pos /= other;
		posNoRot /= other;
		rot /= other;
		rotAround /= other;
		scale /= other;
		color /= other;
	}
	void ModelDef::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save("posX", pos.x);
		saver.save("posY", pos.y);

		saver.save("posNoRotX", posNoRot.x);
		saver.save("posNoRotY", posNoRot.y);

		saver.save("scaleX", scale.x);
		saver.save("scaleY", scale.y);

		saver.save("rot", rot.asDegree());
		saver.save("rotAround", rotAround.asDegree());

		saver.save("clR", color.r);
		saver.save("clG", color.g);
		saver.save("clB", color.b);
		saver.save("clA", color.a);
	}
	void ModelDef::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		pos.x = loader.load("posX", ModelDef::default.pos.x);
		pos.y = loader.load("posY", ModelDef::default.pos.y);

		posNoRot.x = loader.load("posNoRotX", ModelDef::default.posNoRot.x);
		posNoRot.y = loader.load("posNoRotY", ModelDef::default.posNoRot.y);

		scale.x = loader.load("scaleX", ModelDef::default.scale.x);
		scale.y = loader.load("scaleY", ModelDef::default.scale.y);

		rot = Degree(loader.load("rot", ModelDef::default.rot.asDegree()) );
		rotAround = Degree(loader.load("rotAround", ModelDef::default.rotAround.asDegree()) );

		color.r = loader.load("clR", ModelDef::default.color.r);
		color.g = loader.load("clG", ModelDef::default.color.g);
		color.b = loader.load("clB", ModelDef::default.color.b);
		color.a = loader.load("clA", ModelDef::default.color.a);
	}
}