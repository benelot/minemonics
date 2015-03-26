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
#include <OgreRoot.h>

using namespace Ogre;

OgreDebugDrawer::OgreDebugDrawer(SceneManager *scm, bool drawTrajectory) :
		mLinesSwap(NULL), mTrianglesSwap(NULL), mDrawTrajectory(drawTrajectory), mClear(
				0) {
	mDrawTrajectory = drawTrajectory;
	mContactPoints = &mContactPoints1;
	mLines = new ManualObject("BulletPhysicsLines1");
	mLines2 = new ManualObject("BulletPhysicsLines2");
	//ASSERT( mLines );
	mTriangles = new ManualObject("BulletPhysicsTriangles1");
	mTriangles2 = new ManualObject("BulletPhysicsTriangles2");
	//ASSERT( mTriangles );
	mLines->setDynamic(true);
	mLines2->setDynamic(true);
	mTriangles->setDynamic(true);
	mTriangles2->setDynamic(true);
	//mLines->estimateVertexCount( 100000 );
	//mLines->estimateIndexCount( 0 );

	scm->getRootSceneNode()->attachObject(mLines);
	scm->getRootSceneNode()->attachObject(mLines2);
	scm->getRootSceneNode()->attachObject(mTriangles);
	scm->getRootSceneNode()->attachObject(mTriangles2);

	static const char * matName = "OgreBulletCollisionsDebugDefault";
	MaterialPtr mtl =
			MaterialManager::getSingleton().getDefaultSettings()->clone(
					matName);
	mtl->setReceiveShadows(false);
	mtl->setSceneBlending(SBT_TRANSPARENT_ALPHA);
	mtl->setDepthBias(0.1, 0);
	TextureUnitState * tu =
			mtl->getTechnique(0)->getPass(0)->createTextureUnitState();
	//ASSERT( tu );
	tu->setColourOperationEx(LBX_SOURCE1, LBS_DIFFUSE);
	mtl->getTechnique(0)->setLightingEnabled(false);
	//mtl->getTechnique(0)->setSelfIllumination( ColourValue::White );

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
	mLines->position(cvt(from));
	mLines->colour(c);
	mLines->position(cvt(to));
	mLines->colour(c);
}

void OgreDebugDrawer::drawTriangle(const btVector3 &v0, const btVector3 &v1,
		const btVector3 &v2, const btVector3 &color, btScalar alpha) {
	ColourValue c(color.getX(), color.getY(), color.getZ(), alpha);
	c.saturate();
	mTriangles->position(cvt(v0));
	mTriangles->colour(c);
	mTriangles->position(cvt(v1));
	mTriangles->colour(c);
	mTriangles->position(cvt(v2));
	mTriangles->colour(c);
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

	mLinesSwap = mLines;
	mLines = mLines2;
	mLines2 = mLinesSwap;

	mTrianglesSwap = mTriangles;
	mTriangles = mTriangles2;
	mTriangles2 = mTrianglesSwap;

	static const char * matName = "OgreBulletCollisionsDebugDefault";

	mLines->begin(matName, RenderOperation::OT_LINE_LIST);
	mLines->position(Vector3::ZERO);
	mLines->colour(ColourValue::Blue);
	mLines->position(Vector3::ZERO);
	mLines->colour(ColourValue::Blue);

	mTriangles->begin(matName, RenderOperation::OT_TRIANGLE_LIST);
	mTriangles->position(Vector3::ZERO);
	mTriangles->colour(ColourValue::Blue);
	mTriangles->position(Vector3::ZERO);
	mTriangles->colour(ColourValue::Blue);
	mTriangles->position(Vector3::ZERO);
	mTriangles->colour(ColourValue::Blue);

	size_t now = Root::getSingleton().getTimer()->getMilliseconds();
	std::vector<ContactPoint> *newCP =
			mContactPoints == &mContactPoints1 ?
					&mContactPoints2 : &mContactPoints1;
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

	return true;
}

bool OgreDebugDrawer::frameEnded(const Ogre::FrameEvent& evt) {

	mLines->end();
	mTriangles->end();

	if (!mDrawTrajectory) {
		mLines2->clear();
		mTriangles2->clear();
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
