/*
 * OgreOverlayInfo.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#include <view/overlay/InfoOverlayData.hpp>

InfoOverlayData::InfoOverlayData(Ogre::Vector3 position, std::string text) :
		mPosition(position), mText(text) {

}

InfoOverlayData::~InfoOverlayData() {
	// TODO Auto-generated destructor stub
}

