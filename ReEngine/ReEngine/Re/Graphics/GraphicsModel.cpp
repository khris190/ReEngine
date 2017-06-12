#include <Re\Graphics\GraphicsModel.h>
#include <Re\Graphics\GraphicsAnimationPart.h>

namespace Graphics
{
	Model::Model()
		: myTexture(nullptr), parent(nullptr), lastDef(ModelDef::default)
	{
	}

	Model::Model(TsId tsId, const ModelDef& def)
		: ModelDef(def), parent(nullptr), lastDef(ModelDef::default)
	{
		setTexture(tsId, true);
	}

	Model::Model(const char * path)
		: parent(nullptr), lastDef(ModelDef::default)
	{
		deserialise(path);
	}

	

	void Model::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		/// count offset with animations
		ModelDef def;
		def = *this;

		for (auto &it : parts)
			if (it->isWithinRange())
				it->countOffset(def);


		sf::Sprite sp;
		if (myTexture)
		{
			sp.setTexture(*myTexture);
			sp.setOrigin((Vector2D)myTexture->getSize() * 0.5f);
		}
		
		if (parent)
		{
			lastDef = def.countOffset(parent->lastDef);
			lastDef.update(sp);
		}
		else
		{
			lastDef = def;
			def.update(sp);
		}
		

		if (childDown)
			target.draw(*childDown, states);

		target.draw(sp, states);

		/// draw sibling
		if (sibling)
			target.draw(*sibling,states);

		if (childUp)
			target.draw(*childUp, states);
	}

	void Model::rewriteToVector(std::vector<Model* >& v) const
	{
		v.push_back((Model*)this);

		if (childDown)
			childDown->rewriteToVector(v);

		if (childUp)
			childUp->rewriteToVector(v);

		if (sibling)
			sibling->rewriteToVector(v);
	}

	void Model::dfs(const function<void(Model*)>& action)
	{
		action(this);

		if (childDown)
			childDown->dfs(action);
		if (childUp)
			childUp->dfs(action);

		if (sibling)
			sibling->dfs(action);
	}


	void Model::setTexture(TsId id, bool updateOrigin)
	{
		myTexture = &res.textures[id];
#ifdef RE_EDITOR
		tsId = id;
#endif // RE_EDITOR
	}

	void Model::addPart(AnimationPart * s)
	{
		parts.push_back(s);
	}

	void Model::removePart(AnimationPart * s)
	{
		for(auto it = parts.begin(); it != parts.end(); ++it)
			if ( *it == s)
			{
				parts.erase(it);
				return;
			}
	}

	void Model::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		ModelDef::serialiseF(file, saver);
#ifdef RE_EDITOR
		/// Only in editor
		/// TODO
#endif // RE_EDITOR
	}

	void Model::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		ModelDef::deserialiseF(file, loader);
		/// set texture
		TsId tsId = loader.load("ts", 0);
		if (tsId != 0)
			setTexture(tsId, true);
		else
			myTexture = nullptr;

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			string b = loader.load<string>("ud", "down");
			Model *m = new Model();

			if (b == "up")
				addUp(m);
			else // if( b == "down")
				addDown(m);

			m->deserialise(file, loader);
		}
	}
}