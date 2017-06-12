#include <Re\Graphics\Gui\GuiButton.h>
#include <Re\Graphics\ResourceManager.h>

extern RenderWindow wnd;

namespace Gui
{
	State::State(sf::Texture* _ts, const sf::Color& _cl)
		:ts(_ts), cl(_cl)
	{

	}
	State::State(const sf::Color& _cl, sf::Texture* _ts)
		: ts(_ts), cl(_cl)
	{

	}

	State::State(TsId tsId, const sf::Color & _cl)
		: ts(&tsInst[tsId]), cl(_cl)
	{
	}


	Button::Button(const Vector2f & _pos, const Vector2f & _halfWh, 
		function<void()> _eventOnPress, 
		State _stateMouseOn,
		State _statePressed,
		State _stateMouseOut)
		:Base(_pos),
		eventOnPress(_eventOnPress),
		stateMouseOn(_stateMouseOn),
		statePressed(_statePressed),
		stateMouseOut(_stateMouseOut)
	{
		halfWh = _halfWh;
	}

	Button::Button(
		State _constantState,
		const Vector2f & _pos, const Vector2f & _halfWh, 
		function<void()> _eventOnPress)
		:Base(_pos),
		eventOnPress(_eventOnPress),
		stateMouseOn(_constantState),
		statePressed(_constantState),
		stateMouseOut(_constantState)
	{
	}

	void Button::update(sf::RenderTarget & target, sf::RenderStates states)
	{
		sf::ConvexShape sh(4);
		sh.setPosition(getPosActual());

		sh.setPoint(0, Vector2D(-halfWh.x, -halfWh.y));
		sh.setPoint(1, Vector2D(halfWh.x, -halfWh.y));
		sh.setPoint(2, Vector2D(halfWh.x, halfWh.y));
		sh.setPoint(3, Vector2D(-halfWh.x, halfWh.y));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOnWindow() == false)
			canBeActivatedAgain = false;
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
			canBeActivatedAgain = true;

		if (isMouseOnWindow())
		{
			sh.setFillColor(stateMouseOn.cl);
			if (stateMouseOn.ts)
				sh.setTexture(stateMouseOn.ts);
			if (canBeActivatedAgain && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if(eventOnPress)
					eventOnPress();
				sh.setFillColor(statePressed.cl);
				if (statePressed.ts)
					sh.setTexture(statePressed.ts);
			}
		}
		else
		{
			sh.setFillColor(stateMouseOut.cl);
			if (stateMouseOut.ts)
				sh.setTexture(stateMouseOut.ts);
		}

		target.draw(sh, states);
	}

	bool Button::isMouseOnWindow() const
	{
		Vector2D mousePos = sf::Mouse::getPosition(wnd);
		return mousePos.x > getPosActual().x - halfWh.x &&
			mousePos.x < getPosActual().x + halfWh.x	&&
			mousePos.y > getPosActual().y - halfWh.y	&&
			mousePos.y < getPosActual().y + halfWh.y;	
	}

	void Button::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
	}

	void Button::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file, loader);

		int ts = loader.load("onTs", (size_t)-1);
		if(ts != -1) stateMouseOn.ts = &tsInst[ts];
		
		ts = loader.load("pressTs", (size_t)-1);
		if (ts != -1) statePressed.ts = &tsInst[ts];

		ts = loader.load("outTs", (size_t)-1);
		if (ts != -1) stateMouseOut.ts = &tsInst[ts];

		stateMouseOn.cl.r = loader.load("onClR", 255);
		stateMouseOn.cl.g = loader.load("onClG", 255);
		stateMouseOn.cl.b = loader.load("onClB", 255);
		stateMouseOn.cl.a = loader.load("onClA", 255);
		

		statePressed.cl.r = loader.load("pressClR", 255);
		statePressed.cl.g = loader.load("pressClG", 255);
		statePressed.cl.b = loader.load("pressClB", 255);
		statePressed.cl.a = loader.load("pressClA", 255);

		stateMouseOut.cl.r = loader.load("outClR", 255);
		stateMouseOut.cl.g = loader.load("outClG", 255);
		stateMouseOut.cl.b = loader.load("outClB", 255);
		stateMouseOut.cl.a = loader.load("outClA", 255);

	}
}