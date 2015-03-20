/*
 * OgreOverlayInfo.h
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#ifndef VIEW_OGRE3D_OGREOVERLAYINFO_H_
#define VIEW_OGRE3D_OGREOVERLAYINFO_H_

#include <OgreVector3.h>

class InfoOverlayData {
public:
	InfoOverlayData(Ogre::Vector3 position, std::string text);
	virtual ~InfoOverlayData();

	const Ogre::Vector3& getPosition() const {
		return mPosition;
	}

	const std::string& getText() const {
		return mText;
	}

private:
	Ogre::Vector3 mPosition;
	std::string mText;
};

#endif /* VIEW_OGRE3D_OGREOVERLAYINFO_H_ */
