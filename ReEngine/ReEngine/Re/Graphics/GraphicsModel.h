#pragma once
#include <Re\Graphics\ResourceManager.h>
#include <Re\Graphics\GraphicsModelDef.h>

// #define RE_EDITOR

namespace Graphics
{
	class AnimationPart;

	class Model : 
		public ModelDef,
		public sf::Drawable
	{
	public:
		Model();
		/// manualy set model
		Model(TsId tsId, const ModelDef& def = ModelDef::default);
		/// load model from path
		Model(const char* path);


		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;



		/// sometimes it is useful to have tre structure placed in vector
		/// so it is possible to reference to them by index ( eg. at skieletal animations )
		/// ORDER: Object => ChildsDown => ChildsUp => Siblings in dfs fashion
		/// TODO change raw pointner to smart version 
		///		 there is problem with placing first element in vector
		///		 It is not owned by any smart pointner
		void rewriteToVector(std::vector<Model* >& v) const;

		/// iterates over elements in dfs fashion
		void dfs(const function<void(Model*)>& action);


		/// set texture to the one with id of res.textures
		/// updates Origin to the middle point of texture if updateOrigin == true
		void setTexture(TsId id, bool updateOrigin = true);


		/// add child above
		/// pass a pointner to model created by "new Model"
		void addUp(Model *s)
		{
			if (childUp == nullptr)
			{
				s->parent = this;
				childUp = unique_ptr<Model>(s);
#			ifdef RE_EDITOR
				ud = up;
#			endif // RE_EDITOR
			}
			else
				childUp->addSibling(s);
		}
		/// add child under
		/// pass a pointner to model created by "new Model"
		void addDown(Model *s)
		{
			if (childDown == nullptr)
			{
				s->parent = this;
				childDown = unique_ptr<Model>(s);
#			ifdef RE_EDITOR
				ud = down;
#			endif // RE_EDITOR
			}
			else
				childDown->addSibling(s);
		}

		void addPart(AnimationPart* s);
		void removePart(AnimationPart* s);

		Model* getChildUp()
		{
			return childUp.get();
		}
		Model* getChildDown()
		{
			return childDown.get();
		}
		Model* getChildSibling()
		{
			return sibling.get();
		}

		Model* parent;
	private:
		/// Texture applied to sprite
		/// Checking for texture in container at runtime can be a little bit slow
		/// so hold adress of texture instead if id;
		sf::Texture* myTexture;

#	ifdef RE_EDITOR
		/// data needed for saving models
		/// it is not used in runtime game
		/// so applied only on editor builds

		/// texture index in resource manager
		TsId tsId;
		
		/// to determine wheter the object is assigned 
		/// as upper or lower in his parent
		enum
		{
			up,
			down
		} ud;
#	endif // RE_EDITOR
		list<AnimationPart*> parts;

		mutable ModelDef lastDef;

	private: /// Double Tree data
		/// DoubleTree is like standard tree but have two separated childrens
		/// Those childrens describes the rendering order which is:
		///		childs down(and their childrens)
		///		calling model
		///		childs up(and their childrens)

		/// adds a sibling to the model
		/// for internal purposes
		/// use addUp or addDown instead
		void addSibling(Model *s)
		{
			if (sibling == nullptr)
			{
				sibling = unique_ptr<Model>(s);
				s->parent = parent;
			}
			else
				sibling->addSibling(s);
		}

		/// child can be placed either above or under
		/// which child ptr is used determine rendering order
		std::unique_ptr<Model> childUp, childDown,
			/// sibling to this model
			/// shows all models on the same layer
			/// Rendering order: first this one then siblings
			sibling;
		

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}