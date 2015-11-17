#ifndef VIEW_VISUALIZATION_PANELS_MATHGLPANEL_H_
#define VIEW_VISUALIZATION_PANELS_MATHGLPANEL_H_
//# corresponding headers
#include <view/visualization/CEGUI/MovablePanel.hpp>

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
#include <OgreTexture.h>

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
		const int height, Ogre::Root* const root, const int textureWidth,
		const int textureHeight);
	virtual ~MathGLPanel();

	void update(const double timeSinceLastFrame);

	void makePrint() {
		mMakePrint = true;
	}

private:
	Ogre::TexturePtr mTexture; /**!< The texture to drawn the math gl on*/

	double mTime; /**!< The indication of time math */

	CEGUI::GUIContext* mRenderGuiContext; /**!< The render GUI context */

	CEGUI::TextureTarget* mRenderTextureTarget; /**!< The render texture target */

	bool mMakePrint; /**!< Make a print screen */
};

#endif /* MATHGLPANEL_H_ */
