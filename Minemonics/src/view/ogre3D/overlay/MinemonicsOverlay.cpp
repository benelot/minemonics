/*
 * OgreOverlay.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#include "MinemonicsOverlay.h"

MinemonicsOverlay::MinemonicsOverlay() {
	// TODO Auto-generated constructor stub

}

MinemonicsOverlay::~MinemonicsOverlay() {
	// TODO Auto-generated destructor stub
}

void MinemonicsOverlay::initialize() {
	// setup LOD info overlay
	mLodInfoOverlay = OverlayManager::getSingleton().create("InfoOverlay");

	mLodInfoOverlay->setZOrder(10);
	mLodInfoOverlayContainer =
			(OverlayContainer*) OverlayManager::getSingleton().createOverlayElement(
					"Panel", "InfoOverlayPanel");
	mLodInfoOverlayContainer->setDimensions(1.0, 1.0);
	mLodInfoOverlayContainer->setPosition(0.0, 0.0);

	mLodInfoOverlay->add2D(mLodInfoOverlayContainer);
	mLodInfoOverlay->show();
}

void MinemonicsOverlay::addInfo(OgreOverlayInfo info) {

}

void MinemonicsOverlay::update() {
	Vector3 pt = mCamera->getProjectionMatrix()
			* (mCamera->getViewMatrix() * t->getPosition());
	Real x = (pt.x / 2) + 0.5f;
	Real y = 1 - ((pt.y / 2) + 0.5f);

	String lName = StringConverter::toString((unsigned long) (t)) + "/"
			+ "LodInfoLabel";

	OverlayElement *l = OverlayManager::getSingleton().createOverlayElement(
			"TextArea", lName);
	l->setCaption(
			"Target=" + StringConverter::toString(t->getTargetLodLevel())
					+ "\nHighest="
					+ StringConverter::toString(t->getHighestLodLoaded())
					+ "\nPrepared="
					+ StringConverter::toString(t->getHighestLodPrepared()));
	l->setPosition(x, y);
	l->setDimensions(0.1, 0.1); // center text in label and its position
	l->setParameter("font_name", "SdkTrays/Value");
	l->setParameter("char_height", "0.02f");
	l->setColour(ColourValue(1.0, 0.0, 0.0));

	mLodInfoOverlayContainer->addChild(l);
	mLodStatusLabelList.push_back(l);
}

