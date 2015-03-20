/*
 * MinemonicsOverlay.h
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#ifndef VIEW_OGRE3D_OGREOVERLAY_H_
#define VIEW_OGRE3D_OGREOVERLAY_H_

#include "InfoOverlayData.h"
#include <vector>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreCamera.h>


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
