//# corresponding header
#include <iterator>
#include <string>
//## controller headers
//## model headers
//## view headers
#include <OgreCamera.h>
#include <OgreColourValue.h>
#include <OgreMatrix4.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgrePrerequisites.h>
#include <OgreSingleton.h>
#include <OgreVector3.h>
#include <boost/lexical_cast.hpp>
#include <view/visualization/overlay/InfoOverlay.hpp>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers

InfoOverlay::InfoOverlay() :
		mCamera(NULL), mInfoOverlay(NULL), mInfoOverlayContainer(NULL) {
}

InfoOverlay::~InfoOverlay() {
	if (mInfoOverlay)
		Ogre::OverlayManager::getSingleton().destroy(mInfoOverlay);

	if (mInfoOverlayContainer) {
		for (std::vector<Ogre::OverlayElement*>::iterator li =
				mStatusLabelList.begin(); li != mStatusLabelList.end(); li++) {
			mInfoOverlayContainer->_removeChild(*li);
			Ogre::OverlayManager::getSingleton().destroyOverlayElement(*li);
		}
		mStatusLabelList.clear();

		Ogre::OverlayManager::getSingleton().destroyOverlayElement(
				mInfoOverlayContainer);
	}
}

void InfoOverlay::initialize(Ogre::Camera* camera) {
	// setup LOD info overlay
	mCamera = camera;
	mInfoOverlay = Ogre::OverlayManager::getSingleton().create("InfoOverlay");

	mInfoOverlay->setZOrder(10);
	mInfoOverlayContainer =
			(Ogre::OverlayContainer*) Ogre::OverlayManager::getSingleton().createOverlayElement(
					"Panel", "InfoOverlayPanel");
	mInfoOverlayContainer->setDimensions(1.0, 1.0);
	mInfoOverlayContainer->setPosition(0.0, 0.0);

	mInfoOverlay->add2D(mInfoOverlayContainer);
	mInfoOverlay->show();
}

void InfoOverlay::addInfo(InfoOverlayData* data) {
	mOverlayData.push_back(data);
}

void InfoOverlay::update() {
	for (std::vector<Ogre::OverlayElement*>::iterator li =
			mStatusLabelList.begin(); li != mStatusLabelList.end(); li++) {
		mInfoOverlayContainer->_removeChild(*li);
		Ogre::OverlayManager::getSingleton().destroyOverlayElement(*li);
	}
	mStatusLabelList.clear();

	std::vector<InfoOverlayData*>::iterator it = mOverlayData.begin();
	for (; it != mOverlayData.end(); it++) {

		Ogre::Vector3 pt = mCamera->getProjectionMatrix()
				* (mCamera->getViewMatrix() * (*it)->getPosition());
		Ogre::Real x = (pt.x / 2) + 0.5f;
		Ogre::Real y = 1 - ((pt.y / 2) + 0.5f);

		Ogre::String lName = boost::lexical_cast<std::string>(it.base()) + "/"
				+ "InfoLabel";

		Ogre::OverlayElement *l =
				Ogre::OverlayManager::getSingleton().createOverlayElement(
						"TextArea", lName);
		l->setCaption((*it)->getText());
		l->setPosition(x, y);
		l->setDimensions(0.1, 0.1); // center text in label and its position
		l->setParameter("font_name", "SdkTrays/Value");
		l->setParameter("char_height", "0.02f");
		l->setColour(Ogre::ColourValue(1.0, 0.0, 0.0));

		mInfoOverlayContainer->addChild(l);
		mStatusLabelList.push_back(l);
		delete *it;
	}

	mOverlayData.clear();
}

