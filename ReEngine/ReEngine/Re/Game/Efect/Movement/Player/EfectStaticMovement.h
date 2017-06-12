#pragma once
#include <Re\Game\Efect\Movement\EfectRotateToDirection.h>

namespace Efect
{
	/// efect that allows to move player in x and y axes without any rotation
	/// @Warring:  Rigidbody must be created before a first update of the component!
	class StaticMovement : public Base
	{
	public:
		StaticMovement(float32 linearSpeed,
			string codeUp = "up",
			string codeDown = "down",
			string codeLeft = "left",
			string codeRight = "right"
		);
		StaticMovement(float32 linearSpeed,
			RotateToDirection *efRotDir,
			string codeUp = "up", 
			string codeDown = "down",
			string codeLeft = "left",
			string codeRight = "right"
		);

		virtual void onInit() override;
		virtual void onUpdate(sf::Time st) override;

		float32 linearSpeed;
		string codeUp, codeDown, codeLeft, codeRight;

		/// pointner to efect which will change direction of owner
		/// nullptr disables the this feature
		RotateToDirection *efRotDir{nullptr};
	};

	/// version of StaticMovement which does not require rigidbody
	class StaticMovementNoRigidbody : public StaticMovement
	{
	public:
		StaticMovementNoRigidbody(float32 linearSpeed,
			RotateToDirection *efRotDir = nullptr,
			string codeUp = "up",
			string codeDown = "down",
			string codeLeft = "left",
			string codeRight = "right"
		);

		virtual void onUpdate(sf::Time st) override;
	};
}