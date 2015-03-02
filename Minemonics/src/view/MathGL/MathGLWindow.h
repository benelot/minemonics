/*
 * MathGLWindow.h
 *
 *  Created on: Feb 24, 2015
 *      Author: leviathan
 */

#ifndef MATHGLOBJECT_H_
#define MATHGLOBJECT_H_

//# corresponding header

//# forward declarations
class SimulationManager;

namespace CEGUI {
class Window;
class TextureTarget;
}

//# system headers
//## controller headers

//## model headers

//## view headers
#include <CEGUI/Window.h>
#include <OgreTexture.h>

//# custom headers
//## base headers

//## configuration headers

//## controller headers

//## model headers

//## view headers

//## utils headers

class MathGLWindow {
public:
	MathGLWindow(SimulationManager* simulationMgr,int textureWidth,
			int textureHeight,CEGUI::USize windowSize);
	virtual ~MathGLWindow();
	void update(double timeSinceLastFrame);
	CEGUI::Window*& getMathGlWindow();

private:
	SimulationManager* mSimulationMgr;
	Ogre::TexturePtr mTexture;
	CEGUI::Window* mMathGLWindow;
	double mTime;
	CEGUI::GUIContext* renderGuiContext;
	CEGUI::TextureTarget* renderTextureTarget;
};

#endif /* MATHGLOBJECT_H_ */
