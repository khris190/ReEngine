#pragma once
#include <Re\ReEngine.h>
#include <Re\Game\Efect\efects.h>


class Villager : public Game::Actor
{
public:

	void onInit() override;
	void onUpdate(sf::Time dt) override;

	Graphics::Model model;
};
