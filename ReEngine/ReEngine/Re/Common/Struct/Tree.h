#pragma once
#include <memory>
#include <initializer_list>>

/*
A simple template for tree-like structures

requirements:
this template should be inherited
T should be name of the inheriting class
*/
template<typename T>
class Tree
{
public:
	Tree() {}
	Tree(const std::initializer_list<T*>&  list)
		: parent(nullptr), siblingLeft(nullptr)
	{
		create(list);
	}
	virtual ~Tree() {};

	/// create tree object using a set of T
	void create(const std::initializer_list<T*>&  list);

	void prepareToRemove()
	{
		if(parent)
			parent->child = unique_ptr<T>(sibling.release());

		
	}



public:
	//data 
	T* parent;
	T* siblingLeft;
	std::unique_ptr<T> child, sibling;

public:
	void addChild(T* s)
	{
		if (child)
		{
			child->addSibling(s);
			//s->parent = (T*)this;
		}
		else
		{
			child.swap(std::unique_ptr<T>(s));
			s->parent = (T*)this;
		}
	}

	void addSibling(T* s)
	{
		if (sibling)
			sibling->addSibling(s);
		else
		{
			sibling.swap(std::unique_ptr<T>(s));
			s->parent = parent;
			s->siblingLeft = (T*)this;
		}
	}

	/// removes child, its childs and siblings
	void removeChildAll()
	{
		if (child)
		{
			child.reset();
		}
	}
	/// removes child, its childs and siblings
	void removeSiblingAll()
	{
		if (sibling)
		{
			sibling.reset();
		}
	}

};

template<typename T>
void Tree<T>::create(const std::initializer_list<T*>&  list)
{
	for each(auto it in list)
		if (it != nullptr)
			addChild(it);
}