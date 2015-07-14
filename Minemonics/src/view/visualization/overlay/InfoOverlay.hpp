#ifndef VIEW_VISUALIZATION_OVERLAY_INFOOVERLAY_H_
#define VIEW_VISUALIZATION_OVERLAY_INFOOVERLAY_H_

//# corresponding header
//# forward declarations
//# system headers
#include <vector>

//## controller headers
//## model headers
//## view headers
#include <OgreOverlayElement.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
#include <view/visualization/overlay/InfoOverlayData.hpp>

/**
 * @brief		The info overlay adds information to the 3D objects in the scene.
 * @details		Details
 * @date		2015-03-17
 * @author		Benjamin Ellenberger
 */
class InfoOverlay {
public:
	InfoOverlay();
	virtual ~InfoOverlay();

	void initialize(Ogre::Camera* const camera);

	void addInfo(InfoOverlayData* const data);

	void update();

private:

	std::vector<InfoOverlayData*> mOverlayData;

	Ogre::Overlay* mInfoOverlay;
	Ogre::OverlayContainer* mInfoOverlayContainer;
	Ogre::Camera* mCamera;

	std::vector<Ogre::OverlayElement*> mStatusLabelList;

};

#endif /* VIEW_VISUALIZATION_OVERLAY_INFOOVERLAY_H_ */
