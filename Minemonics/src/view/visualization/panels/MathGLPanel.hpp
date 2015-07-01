#ifndef VIEW_VISUALIZATION_PANELS_MATHGLPANEL_H_
#define VIEW_VISUALIZATION_PANELS_MATHGLPANEL_H_

//# corresponding headers
#include <view/visualization/panels/InfoPanel.hpp>

//# forward declarations
class ViewController;

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
#include <OgreRoot.h>
#include <Renderer.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The MathGL Panel displays mathematical functions in a scalable panel.
 * @details		Details
 * @date		2015-02-24
 * @author		Benjamin Ellenberger
 */
class MathGLPanel: public InfoPanel {
public:
	MathGLPanel(ViewController* viewController,Ogre::Root* root, int textureWidth,
			int textureHeight,CEGUI::USize windowSize,CEGUI::USize windowPosition);
	virtual ~MathGLPanel();

	void update(double timeSinceLastFrame);

	CEGUI::Window*& getMathGlWindow();

	void makePrint()
	{
		mMakePrint = true;
	}

private:
	ViewController* mViewController;

	Ogre::TexturePtr mTexture;

	CEGUI::Window* mMathGLWindow;

	double mTime;

	CEGUI::GUIContext* mRenderGuiContext;

	CEGUI::TextureTarget* mRenderTextureTarget;

	bool mMakePrint;
};

#endif /* MATHGLPANEL_H_ */
