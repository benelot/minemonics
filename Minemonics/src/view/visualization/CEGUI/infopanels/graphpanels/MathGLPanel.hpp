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
#include <model/data/MathGLDataset.hpp>

//## utils headers

/**
 * @brief		The MathGL Panel displays mathematical functions in a scalable panel.
 * @details		Details
 * @date		2015-02-24
 * @author		Benjamin Ellenberger
 */
class MathGLPanel: public MovablePanel {
public:
	MathGLPanel(const std::string name, const int left, const int top, const int width,
		const int height, Ogre::Root* const root, const int textureWidth,
		const int textureHeight);
	virtual ~MathGLPanel();

	void onHorizontalSliderValueChanged();
	void onVerticalSliderValueChanged();

	void update(const double timeSinceLastFrame);

	void addDataset(const MathGLDataset* dataset){
		mDatasets.push_back(dataset);
	}

	void clearDatasets(){
		mDatasets.clear();
	}

	void makePrint() {
		mMakePrint = true;
	}

	double getHorizontalRotation() const {
		return mHorizontalRotation;
	}

	void setHorizontalRotation(double horizontalRotation) {
		mHorizontalRotation = horizontalRotation;
	}

	double getVerticalRotation() const {
		return mVerticalRotation;
	}

	void setVerticalRotation(double verticalRotation) {
		mVerticalRotation = verticalRotation;
	}

	const std::string& getXLabel() const {
		return mXLabel;
	}

	void setXLabel(const std::string& xLabel) {
		mXLabel = xLabel;
	}

	const std::string& getYLabel() const {
		return mYLabel;
	}

	void setYLabel(const std::string& yLabel) {
		mYLabel = yLabel;
	}

	const std::string& getZLabel() const {
		return mZLabel;
	}

	void setZLabel(const std::string& zLabel) {
		mZLabel = zLabel;
	}

private:

	CEGUI::Slider* mVerticalSlider; /**!< The slider right to the graph */
	double mHorizontalRotation;
	CEGUI::Slider* mHorizontalSlider; /**!< The slider below the graph */
	double mVerticalRotation;

	std::string mXLabel;
	std::string mYLabel;
	std::string mZLabel;

	std::vector<const MathGLDataset*> mDatasets; /**!< The different data sets to plot*/
	Ogre::TexturePtr mTexture; /**!< The texture to drawn the math gl on*/

	double mTime; /**!< The indication of time math */

	CEGUI::GUIContext* mRenderGuiContext; /**!< The render GUI context */

	CEGUI::TextureTarget* mRenderTextureTarget; /**!< The render texture target */

	bool mMakePrint; /**!< Make a print screen */
};

#endif /* MATHGLPANEL_H_ */
