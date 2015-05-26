//# corresponding headers
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//# forward declarations
//# system headers
#include <vector>

//## controller headers
//## model headers
#include <GLX/OgreTimerImp.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>

//## view headers
#include <OgreBlendMode.h>
#include <OgreLog.h>
#include <OgreLogManager.h>
#include <OgreManualObject.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>
#include <OgrePass.h>
#include <OgrePrerequisites.h>
#include <OgreRenderOperation.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreSingleton.h>
#include <OgreTechnique.h>
#include <OgreTextureUnitState.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

OgreBtDebugDrawer::OgreBtDebugDrawer(Ogre::SceneManager *scm,
		bool drawTrajectory) :
		mLinesSwap(NULL), mTrianglesSwap(NULL), mDrawTrajectory(drawTrajectory), mClear(
				0), mDebugMode(0), mDrawable(false), mDebugDrawingEnabled(true) {
	mDrawTrajectory = drawTrajectory;
	mContactPoints = &mContactPoints1;
	mLines = new Ogre::ManualObject("BulletPhysicsLines1");
	mLines2 = new Ogre::ManualObject("BulletPhysicsLines2");

	mTriangles = new Ogre::ManualObject("BulletPhysicsTriangles1");
	mTriangles2 = new Ogre::ManualObject("BulletPhysicsTriangles2");

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
	Ogre::MaterialPtr mtl =
			Ogre::MaterialManager::getSingleton().getDefaultSettings()->clone(
					matName);
	mtl->setReceiveShadows(false);
	mtl->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	mtl->setDepthBias(0.1, 0);
	Ogre::TextureUnitState * tu =
			mtl->getTechnique(0)->getPass(0)->createTextureUnitState();

	tu->setColourOperationEx(Ogre::LBX_SOURCE1, Ogre::LBS_DIFFUSE);
	mtl->getTechnique(0)->setLightingEnabled(false);
	//mtl->getTechnique(0)->setSelfIllumination( ColourValue::White );

	Ogre::Root::getSingleton().addFrameListener(this);
}

OgreBtDebugDrawer::~OgreBtDebugDrawer() {
	Ogre::Root::getSingleton().removeFrameListener(this);
	delete mLines;
	delete mTriangles;
}

void OgreBtDebugDrawer::drawLine(const btVector3 &from, const btVector3 &to,
		const btVector3 &color) {
	drawLine(OgreBulletUtils::convert(from), OgreBulletUtils::convert(to),
			Ogre::ColourValue(color.getX(), color.getY(), color.getZ()));
}

void OgreBtDebugDrawer::drawLine(const Ogre::Vector3& from,
		const Ogre::Vector3& to, Ogre::ColourValue color) {
	if (mDebugMode > 0 && mDebugDrawingEnabled) {
		if (mDrawable) {
			color.saturate();
			mLines->position(from);
			mLines->colour(color);
			mLines->position(to);
			mLines->colour(color);
			draw();
		} else {
			Line line;
			color.saturate();
			line.color = color;
			line.from = from;
			line.to = to;
			line.drawn = false;
			mExtLines.push_back(line);
		}
	}
}

void OgreBtDebugDrawer::drawTriangle(const btVector3 &v0, const btVector3 &v1,
		const btVector3 &v2, const btVector3 &color, btScalar alpha) {
	drawTriangle(OgreBulletUtils::convert(v0), OgreBulletUtils::convert(v1),
			OgreBulletUtils::convert(v2),
			Ogre::ColourValue(color.getX(), color.getY(), color.getZ()),
			Ogre::Real(alpha));
}

void OgreBtDebugDrawer::drawTriangle(const Ogre::Vector3& v0,
		const Ogre::Vector3& v1, const Ogre::Vector3& v2,
		Ogre::ColourValue color, Ogre::Real alpha) {
	if (mDebugMode > 0 && mDebugDrawingEnabled) {
		if (mDrawable) {
			mTriangles->position(v0);
			mTriangles->colour(color);
			mTriangles->position(v1);
			mTriangles->colour(color);
			mTriangles->position(v2);
			mTriangles->colour(color);
			draw();
		} else {
			Triangle triangle;

			color.saturate();
			triangle.color = color;
			triangle.v0 = v0;
			triangle.v1 = v1;
			triangle.v2 = v2;
			triangle.drawn = false;
			mExtTriangles.push_back(triangle);
		}
	}
}

void OgreBtDebugDrawer::drawContactPoint(const btVector3 &PointOnB,
		const btVector3 &normalOnB, btScalar distance, int lifeTime,
		const btVector3 &color) {
	drawContactPoint(OgreBulletUtils::convert(PointOnB),
			OgreBulletUtils::convert(normalOnB), distance, lifeTime,
			Ogre::ColourValue(color.getX(), color.getY(), color.getZ()));
}

void OgreBtDebugDrawer::drawContactPoint(const Ogre::Vector3& PointOnB,
		const Ogre::Vector3& normalOnB, Ogre::Real distance, int lifeTime,
		const Ogre::ColourValue& color) {
	if ((mDebugMode & btIDebugDraw::DBG_DrawContactPoints)
			&& mDebugDrawingEnabled) {
		ContactPoint p;
		p.from = PointOnB;
		p.to = p.from + normalOnB * distance;
		p.dieTime = Ogre::Root::getSingleton().getTimer()->getMilliseconds()
				+ lifeTime;
		p.color = color;
		mContactPoints->push_back(p);
	}
}

void OgreBtDebugDrawer::draw() {
	if (mDebugDrawingEnabled) {
		for (std::vector<Line>::iterator i = mExtLines.begin();
				i < mExtLines.end(); i++) {
			Line &l = *i;
			if (l.drawn == true && !mDrawTrajectory) {
				//mLines.erase(i--);
			} else {
				mLines->position(l.from);
				mLines->colour(l.color);
				mLines->position(l.to);
				mLines->colour(l.color);
				l.drawn = true;
			}
		}

		for (std::vector<Triangle>::iterator i = mExtTriangles.begin();
				i < mExtTriangles.end(); i++) {
			Triangle &t = *i;
			if (t.drawn == true && !mDrawTrajectory) {
				//mTriangles.erase(i--);
			} else {
				mLines->position(t.v0);
				mLines->colour(t.color);
				mLines->position(t.v1);
				mLines->colour(t.color);
				mLines->position(t.v2);
				mLines->colour(t.color);
				t.drawn = true;
			}
		}
	}

	mExtLines.clear();
	mExtTriangles.clear();
}

bool OgreBtDebugDrawer::frameStarted(const Ogre::FrameEvent& evt) {

	mLinesSwap = mLines;
	mLines = mLines2;
	mLines2 = mLinesSwap;

	mTrianglesSwap = mTriangles;
	mTriangles = mTriangles2;
	mTriangles2 = mTrianglesSwap;

	static const char * matName = "OgreBulletCollisionsDebugDefault";

	mLines->begin(matName, Ogre::RenderOperation::OT_LINE_LIST);
	mLines->position(Ogre::Vector3::ZERO);
	mLines->colour(Ogre::ColourValue::Blue);
	mLines->position(Ogre::Vector3::ZERO);
	mLines->colour(Ogre::ColourValue::Blue);

	mTriangles->begin(matName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
	mTriangles->position(Ogre::Vector3::ZERO);
	mTriangles->colour(Ogre::ColourValue::Blue);
	mTriangles->position(Ogre::Vector3::ZERO);
	mTriangles->colour(Ogre::ColourValue::Blue);
	mTriangles->position(Ogre::Vector3::ZERO);
	mTriangles->colour(Ogre::ColourValue::Blue);

	size_t now = Ogre::Root::getSingleton().getTimer()->getMilliseconds();
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

	//draw remaining objects from last frame
	draw();

	mDrawable = true;

	return true;
}

bool OgreBtDebugDrawer::frameEnded(const Ogre::FrameEvent& evt) {

	mLines->end();
	mTriangles->end();

	mDrawable = false;

	if (!mDrawTrajectory) {
		mLines2->clear();
		mTriangles2->clear();
	}

	return true;
}

void OgreBtDebugDrawer::reportErrorWarning(const char *warningString) {
	Ogre::LogManager::getSingleton().getDefaultLog()->logMessage(warningString);
}

void OgreBtDebugDrawer::draw3dText(const btVector3 &location,
		const char *textString) {

}

void OgreBtDebugDrawer::setDebugMode(int debugMode) {
	mDebugMode = debugMode;
}

int OgreBtDebugDrawer::getDebugMode() const {
	return mDebugMode;
}

//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setDrawAabb(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_DrawAabb;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawAabb;
}
//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesDrawAabb() const {
	return (mDebugMode & btIDebugDraw::DBG_DrawAabb) != 0;
}
;
//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesDrawWireframe() const {
	return (mDebugMode & btIDebugDraw::DBG_DrawWireframe) != 0;
}
;

//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesDrawConstraints() const {
	return (mDebugMode & btIDebugDraw::DBG_DrawConstraints) != 0;
}
;

//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesDrawConstraintLimits() const {
	return (mDebugMode & btIDebugDraw::DBG_DrawConstraintLimits) != 0;
}
;
//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesDrawNormals() const {
	return (mDebugMode & btIDebugDraw::DBG_DrawNormals) != 0;
}
;
//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesDrawFeaturesText() const {
	return (mDebugMode & btIDebugDraw::DBG_DrawFeaturesText) != 0;
}
;
//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesDrawContactPoints() const {
	return (mDebugMode & btIDebugDraw::DBG_DrawContactPoints) != 0;
}
;
//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesNoDeactivation() const {
	return (mDebugMode & btIDebugDraw::DBG_NoDeactivation) != 0;
}
;
//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesNoHelpText() const {
	return (mDebugMode & btIDebugDraw::DBG_NoHelpText) != 0;
}
;
//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesDrawText() const {
	return (mDebugMode & btIDebugDraw::DBG_DrawText) != 0;
}
;
//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesProfileTimings() const {
	return (mDebugMode & btIDebugDraw::DBG_ProfileTimings) != 0;
}
;
//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesEnableSatComparison() const {
	return (mDebugMode & btIDebugDraw::DBG_EnableSatComparison) != 0;
}
;
//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesDisableBulletLCP() const {
	return (mDebugMode & btIDebugDraw::DBG_DisableBulletLCP) != 0;
}
;
//------------------------------------------------------------------------------------------------
bool OgreBtDebugDrawer::doesEnableCCD() const {
	return (mDebugMode & btIDebugDraw::DBG_EnableCCD) != 0;
}
;
//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setDrawWireframe(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_DrawWireframe;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawWireframe;
}

//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setDrawConstraints(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_DrawConstraints;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawConstraints;
}

//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setDrawConstraintLimits(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_DrawConstraintLimits;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawConstraintLimits;
}
//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setDrawNormals(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_DrawNormals;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawNormals;
}
//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setDrawFeaturesText(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_DrawFeaturesText;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawFeaturesText;
}
//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setDrawContactPoints(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_DrawContactPoints;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawContactPoints;
}
//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setNoDeactivation(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_NoDeactivation;
	else
		mDebugMode &= ~btIDebugDraw::DBG_NoDeactivation;
}
//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setNoHelpText(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_NoHelpText;
	else
		mDebugMode &= ~btIDebugDraw::DBG_NoHelpText;
}
//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setDrawText(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_DrawText;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DrawText;
}
//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setProfileTimings(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_ProfileTimings;
	else
		mDebugMode &= ~btIDebugDraw::DBG_ProfileTimings;
}
//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setEnableSatComparison(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_EnableSatComparison;
	else
		mDebugMode &= ~btIDebugDraw::DBG_EnableSatComparison;
}
//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setDisableBulletLCP(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_DisableBulletLCP;
	else
		mDebugMode &= ~btIDebugDraw::DBG_DisableBulletLCP;
}
//------------------------------------------------------------------------------------------------
void OgreBtDebugDrawer::setEnableCCD(bool enable) {
	if (enable)
		mDebugMode |= btIDebugDraw::DBG_EnableCCD;
	else
		mDebugMode &= ~btIDebugDraw::DBG_EnableCCD;
}
