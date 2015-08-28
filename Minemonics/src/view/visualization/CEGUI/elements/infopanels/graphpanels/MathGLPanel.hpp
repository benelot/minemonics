#ifndef VIEW_VISUALIZATION_PANELS_MATHGLPANEL_H_
#define VIEW_VISUALIZATION_PANELS_MATHGLPANEL_H_
//# corresponding headers
#include <view/visualization/CEGUI/elements/MovablePanel.hpp>

//# forward declarations
class ViewController;
namespace CEGUI {
class TextureTarget;
} /* namespace CEGUI */

//# system headers
//## controller headers
//## model headers
//## view headers

#include <OgrePrerequisites.h>

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
class MathGLPanel: public MovablePanel {
public:
	MathGLPanel(const int left, const int top, const int width,
	const int height, ViewController* const viewController,
	Ogre::Root* const root, const int textureWidth, const int textureHeight);
	virtual ~MathGLPanel();

	void update(const double timeSinceLastFrame);

	void makePrint() {
		mMakePrint = true;
	}

private:
	ViewController* mViewController;

	Ogre::TexturePtr mTexture;

	double mTime;

	CEGUI::GUIContext* mRenderGuiContext;

	CEGUI::TextureTarget* mRenderTextureTarget;

	bool mMakePrint;
};

#endif /* MATHGLPANEL_H_ */
