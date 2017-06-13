#include <Re\ReEngine.h>
#include <Re\Graphics\Gui\Gui.h>
#include <Re\Lambdas.h>
#include <Re\Game\Efect\efects.h>
#include "Layers.h"



#include "Warrior\WarriorPlayer.h"
#include "Warrior\Villager.h"
#include "Ritual\RitualSign.h"

void addBackground(const Vector2D& position = Vector2D())
{
	auto background = Game::world.addActor(new Game::Actor, Game::Layers::background);

	background->setPosition(position);

	auto efModel = background->addEfect(new Efect::Model((TsId)100u))
		->setScale(Vector2D(5.f, 5.f));
}
Villager* addVillager(const Vector2D& position)
{
	auto villager = Game::world.addActor(new Villager, Game::Layers::character);
	villager->getRigidbody().SetTransform(position*toB2Position, randRange(Angle::zero, Angle::full).asRadian());

	return villager;
}

void initKeys()
{
	actionMap["up"] = thor::Action(sf::Keyboard::W);
	actionMap["down"] = thor::Action(sf::Keyboard::S);
	actionMap["left"] = thor::Action(sf::Keyboard::A);
	actionMap["right"] = thor::Action(sf::Keyboard::D);

	actionMap["up2"] = thor::Action(sf::Keyboard::Up);
	actionMap["down2"] = thor::Action(sf::Keyboard::Down);
	actionMap["left2"] = thor::Action(sf::Keyboard::Left);
	actionMap["right2"] = thor::Action(sf::Keyboard::Right);


	actionMap["fire1"] = thor::Action(sf::Mouse::Left) || thor::Action(sf::Mouse::Right);
	actionMap["fire2"] = thor::Action(sf::Keyboard::Q, thor::Action::PressOnce);
	actionMap["fire3"] = thor::Action(sf::Keyboard::E, thor::Action::PressOnce);

	actionMap["debugPhysics"] = thor::Action(sf::Keyboard::Z, thor::Action::Hold);
	actionMap["restart"] = thor::Action(sf::Keyboard::P, thor::Action::PressOnce);
}

Game::State* createState()
{
	return new Game::StateLambda(
		[]() /// init
	{
		Game::Layers::init();
		cam.setScale(2.5f);
		addBackground();
		Game::world.addActor(new WarriorPlayer(), Game::Layers::character);

		for (int i = 0; i < 15; ++i)
			addVillager(Vector2D(0, randRange(100.f, 1500.f)).getRotated(randRange(Angle::zero, Angle::full)));
	},

		[](sf::Time dt)->Game::State*
	{
		Game::world.onUpdate(dt);
		cam.display(wnd);
		if (actionMap.isActive("restart"))
			return createState();
		return nullptr;
	}
	);

}


void init()
{
	srand((unsigned int)time(nullptr));
	wnd.create(VideoMode(1100, 750), "ReEngine");
	//wnd.setVerticalSyncEnabled(true);
	wnd.setFramerateLimit(30);

	cam.create(Vector2D(wnd.getSize().x, wnd.getSize().y));
	cam.setBackgroundColor(Color(0, 0, 0));
	cam.setDarkness(1);
	cam.setBackgroundColor(Color(200, 200, 200));

	res.textures.acquire(0u, thor::ResourceLoader<Texture>(
		[]()->unique_ptr<Texture> {return unique_ptr<Texture>(new Texture()); }, ""));
	res.deserialise("Resources.txt");


	initKeys();



	Game::stateManager.setState( createState() );
}


void update()
{
	static Clock clock, performanceClock;
	performanceClock.restart();
	Game::stateManager.onUpdate(clock.getElapsedTime());


	sf::Text txt;
	{
		static int32 average = performanceClock.getElapsedTime().asMilliseconds();
		average = (average * 7 + performanceClock.getElapsedTime().asMilliseconds()) *0.125;

		txt.setPosition(0, 0);
		txt.setFont(res.fonts[1]);
		txt.setCharacterSize(35);
		txt.setFillColor(Color::White);
		txt.setStyle(sf::Text::Bold);
		std::stringstream ss;
		ss << "ms: " << average;
		txt.setString(ss.str());
	}
	clock.restart();
	wnd.draw(txt);

	Gui::gui.update(wnd, RenderStates::Default);
}
void out()
{

}


int main()
{
	init();

	while (wnd.isOpen())
	{
		actionMap.clearEvents();
		Event ev;
		while (wnd.pollEvent(ev))
		{
			if (ev.type == Event::Closed
				|| (ev.type == Event::KeyPressed && ev.key.code == sf::Keyboard::Escape))
				wnd.close();
			actionMap.pushEvent(ev);
		}
		update();

		wnd.display();
	}
	out();
}