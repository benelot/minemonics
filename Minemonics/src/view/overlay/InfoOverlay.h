/*
 * MinemonicsOverlay.h
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#ifndef VIEW_OGRE3D_OGREOVERLAY_H_
#define VIEW_OGRE3D_OGREOVERLAY_H_

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
#include <view/overlay/InfoOverlayData.h>

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-03-17
 * @author		Benjamin Ellenberger
 */
class InfoOverlay {
public:
	InfoOverlay();
	virtual ~InfoOverlay();

	void initialize(Ogre::Camera* camera);

	void addInfo(InfoOverlayData* data);
	void update();

	std::vector<InfoOverlayData*> mOverlayData;

	Ogre::Overlay* mInfoOverlay;
	Ogre::OverlayContainer* mInfoOverlayContainer;
	Ogre::Camera* mCamera;

	std::vector<Ogre::OverlayElement*> mStatusLabelList;

};

#endif /* VIEW_OGRE3D_OGREOVERLAY_H_ */
