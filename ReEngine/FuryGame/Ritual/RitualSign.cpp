#include "RitualSign.h"

void RitualSign::onInit()
{
	Actor::onInit();


	auto efParticle = addEfect(new Efect::Particle)
		->addEmitter( Emitter().setEmissionRate(3000.f).setColor(Color(0,0,0,15))
			.setLifetime(thor::Distributions::uniform(seconds(0.25), seconds(1.)))
			.setVelocity([]() {return Vector2D(0, randRange(1, 20)).getRotated(); })
			.setPosition([]() {return Vector2D(0, randRange(450, 500)).getRotated(); })
		)->setTexture(200);
}

void RitualSign::onUpdate(sf::Time dt)
{
	Actor::onUpdate(dt);
}
