/*
 * OgreDebugDrawer.cpp
 *
 *  Created on: Mar 19, 2015
 *      Author: leviathan
 */

#include "OgreDebugDrawer.h"

#include "OgreBulletUtils.h"

#include <OgreManualObject.h>

#include <OgreSceneManager.h>
#include<OgreRoot.h>

using namespace Ogre;

OgreDebugDrawer::OgreDebugDrawer(SceneManager *scm, bool drawTrajectory) :
		mDrawTrajectory(drawTrajectory) {
	mContactPoints = &mContactPoints1;
	mLines = new ManualObject("physics lines");
	//ASSERT( mLines );
	mTriangles = new ManualObject("physics triangles");
	//ASSERT( mTriangles );
	mLines->setDynamic(true);
	mTriangles->setDynamic(true);
	//mLines->estimateVertexCount( 100000 );
	//mLines->estimateIndexCount( 0 );

	scm->getRootSceneNode()->attachObject(mLines);
	scm->getRootSceneNode()->attachObject(mTriangles);

	MaterialPtr mtl =
			MaterialManager::getSingleton().getDefaultSettings()->clone(
					getMatName());
	mtl->setReceiveShadows(false);
	mtl->setSceneBlending(SBT_TRANSPARENT_ALPHA);
	mtl->setDepthBias(0.1, 0);
	TextureUnitState * tu =
			mtl->getTechnique(0)->getPass(0)->createTextureUnitState();
	//ASSERT( tu );
	tu->setColourOperationEx(LBX_SOURCE1, LBS_DIFFUSE);
	mtl->getTechnique(0)->setLightingEnabled(false);
	//mtl->getTechnique(0)->setSelfIllumination( ColourValue::White );

	mLines->begin(getMatName(), RenderOperation::OT_LINE_LIST);
	mLines->position(Vector3::ZERO);
	mLines->colour(ColourValue::Blue);
	mLines->position(Vector3::ZERO);
	mLines->colour(ColourValue::Blue);
	mLines->end();

	mTriangles->begin(getMatName(), RenderOperation::OT_TRIANGLE_LIST);
	mTriangles->position(Vector3::ZERO);
	mTriangles->colour(ColourValue::Blue);
	mTriangles->position(Vector3::ZERO);
	mTriangles->colour(ColourValue::Blue);
	mTriangles->position(Vector3::ZERO);
	mTriangles->colour(ColourValue::Blue);
	mTriangles->end();

	mDebugModes = (DebugDrawModes) DBG_DrawWireframe;
	Root::getSingleton().addFrameListener(this);
}

OgreDebugDrawer::~OgreDebugDrawer() {
	Root::getSingleton().removeFrameListener(this);
	delete mLines;
	delete mTriangles;
}

void OgreDebugDrawer::drawLine(const btVector3 &from, const btVector3 &to,
		const btVector3 &color) {
	ColourValue c(color.getX(), color.getY(), color.getZ());
	c.saturate();
	mLines->begin(getMatName(), RenderOperation::OT_LINE_LIST);
	mLines->position(cvt(from));
	mLines->colour(c);
	mLines->position(cvt(to));
	mLines->colour(c);
	mLines->end();
}

void OgreDebugDrawer::drawTriangle(const btVector3 &v0, const btVector3 &v1,
		const btVector3 &v2, const btVector3 &color, btScalar alpha) {
	ColourValue c(color.getX(), color.getY(), color.getZ(), alpha);
	c.saturate();
	mTriangles->begin(getMatName(), RenderOperation::OT_LINE_LIST);
	mTriangles->position(cvt(v0));
	mTriangles->colour(c);
	mTriangles->position(cvt(v1));
	mTriangles->colour(c);
	mTriangles->position(cvt(v2));
	mTriangles->colour(c);
	mTriangles->end();
}

void OgreDebugDrawer::drawContactPoint(const btVector3 &PointOnB,
		const btVector3 &normalOnB, btScalar distance, int lifeTime,
		const btVector3 &color) {
	mContactPoints->resize(mContactPoints->size() + 1);
	ContactPoint p = mContactPoints->back();
	p.from = cvt(PointOnB);
	p.to = p.from + cvt(normalOnB) * distance;
	p.dieTime = Root::getSingleton().getTimer()->getMilliseconds() + lifeTime;
	p.color.r = color.x();
	p.color.g = color.y();
	p.color.b = color.z();
}

bool OgreDebugDrawer::frameStarted(const Ogre::FrameEvent& evt) {
	size_t now = Root::getSingleton().getTimer()->getMilliseconds();
	std::vector<ContactPoint> *newCP =
			mContactPoints == &mContactPoints1 ?
					&mContactPoints2 : &mContactPoints1;
	mLines->begin(getMatName(), RenderOperation::OT_POINT_LIST);
	for (std::vector<ContactPoint>::iterator i = mContactPoints->begin();
			i < mContactPoints->end(); i++) {
		ContactPoint &cp = *i;
		mLines->position(cp.from);
		mLines->colour(cp.color);
		mLines->position(cp.to);
		if (now <= cp.dieTime)
			newCP->push_back(cp);
	}
	mContactPoints->clear();
	mContactPoints = newCP;

	mLines->end();
	//mTriangles->end();

	return true;
}

bool OgreDebugDrawer::frameEnded(const Ogre::FrameEvent& evt) {
	//this will not clear the old lines drawing a proper trajectory into the air
	if (!mDrawTrajectory) {
		mLines->clear();
		mTriangles->clear();
	}
	return true;
}

void OgreDebugDrawer::reportErrorWarning(const char *warningString) {
	LogManager::getSingleton().getDefaultLog()->logMessage(warningString);
}

void OgreDebugDrawer::draw3dText(const btVector3 &location,
		const char *textString) {

}

void OgreDebugDrawer::setDebugMode(int debugMode) {
	mDebugModes = (DebugDrawModes) debugMode;
}

int OgreDebugDrawer::getDebugMode() const {
	return mDebugModes;
}
