#ifndef MATHGLPANEL_H_
#define MATHGLPANEL_H_

//# corresponding headers
#include <view/visualization/panels/InfoPanel.hpp>

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
#include <CEGUI/Size.h>
#include <CEGUI/Window.h>
#include <OgrePrerequisites.h>
#include <OgreTexture.h>
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The MathGL Panel displays functions in a scalable panel.
 * @details		Details
 * @date		2015-02-24
 * @author		Benjamin Ellenberger
 */
class MathGLPanel: public InfoPanel {
public:
	MathGLPanel(SimulationManager* simulationMgr,int textureWidth,
			int textureHeight,CEGUI::USize windowSize,CEGUI::USize windowPosition);
	virtual ~MathGLPanel();
	void update(double timeSinceLastFrame);
	CEGUI::Window*& getMathGlWindow();

	void makePrint()
	{
		mMakePrint = true;
	}

private:
	SimulationManager* mSimulationMgr;
	Ogre::TexturePtr mTexture;
	CEGUI::Window* mMathGLWindow;
	double mTime;
	CEGUI::GUIContext* mRenderGuiContext;
	CEGUI::TextureTarget* mRenderTextureTarget;
	bool mMakePrint;
};

#endif /* MATHGLPANEL_H_ */
