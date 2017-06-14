#pragma once

/// general
#include <Re\Graphics\Camera.h>
#include <Re\Graphics\ResourceManager.h>

/// models and parts
#include <Re\Graphics\GraphicsModel.h>
#include <Re\Graphics\GraphicsModelPolygon.h>
#include <Re\Graphics\GraphicsAnimationController.h>
#include <Re\Graphics\GraphicsAnimationPart.h>

/// global acces to main window
extern RenderWindow wnd;

/// Gui
/// to increase performance include only most important files of gui module
/// in case you will create gui by .res files it would be enough
/// otherwise include file below
//#include <Re\Graphics\Gui\Gui.h>

#include <Re\Graphics\Gui\GuiMenu.h>
namespace Gui
{
	extern Menu gui;
}
