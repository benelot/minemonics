/*
 * MathGLObject.h
 *
 *  Created on: Feb 24, 2015
 *      Author: leviathan
 */

#ifndef MATHGLOBJECT_H_
#define MATHGLOBJECT_H_

class SimulationManager;

namespace CEGUI {
class Window;
class TextureTarget;
}

#include <CEGUI/System.h>
#include <CEGUI/Window.h>
#include <CEGUI/Image.h>
#include <OgreTexture.h>

class MathGLObject {
public:
	MathGLObject(SimulationManager* simulationMgr,int textureWidth,
			int textureHeight);
	virtual ~MathGLObject();
	void update(int timeSinceLastFrame);
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
