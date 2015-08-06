#ifndef VIEW_VISUALIZATION_BULLETPHYSICS_OGREDEBUGDRAWER_H_
#define VIEW_VISUALIZATION_BULLETPHYSICS_OGREDEBUGDRAWER_H_

//# corresponding header
//# forward declarations
class btDynamicsWorld;
namespace Ogre {
class Overlay;
class OverlayContainer;
class OverlayManager;
class TextAreaOverlayElement;
} /* namespace Ogre */

//# system headers
#include <stddef.h>
#include <vector>

//## controller headers
//## model headers
#include <LinearMath/btIDebugDraw.h>
#include <LinearMath/btScalar.h>

//## view headers
#include <bullet/LinearMath/btIDebugDraw.h>
#include <OgreColourValue.h>
#include <OgreFrameListener.h>
#include <OgrePrerequisites.h>
#include <OgreVector3.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The Ogre Bullet debug drawer draws the bullet physics object visualizations with Ogre means.
 * @details		Details
 * @date		2015-03-19
 * @author		Benjamin Ellenberger
 */
class OgreBtDebugDrawer: public btIDebugDraw, public Ogre::FrameListener {
public:
	OgreBtDebugDrawer();
	~OgreBtDebugDrawer();

	/**
	 * Initialize the Ogre Bullet Debug Drawer.
	 * @param sceneManager A handle to the scene manager.
	 * @param drawTrajectory A possibility to draw a trajectory by not deleting lines.
	 */
	void initialize(Ogre::SceneManager* const sceneManager, const bool drawTrajectory);

	/**
	 * Draw a line.
	 * @param from Starting point of the line.
	 * @param to Ending point of the line.
	 * @param color The color of the line.
	 */
	virtual void drawLine(const btVector3 &from, const btVector3 &to,
			const btVector3 &color);

	/**
	 * Draw a line.
	 * @param from Starting point of the line.
	 * @param to Ending point of the line.
	 * @param color The color of the line.
	 */
	void drawLine(const Ogre::Vector3& from, const Ogre::Vector3& to,
			const Ogre::ColourValue color);

	/**
	 * Draw a triangle.
	 * @param v0 First vertex of the triangle.
	 * @param v1 Second vertex of the triangle.
	 * @param v2 Third vertex of the triangle.
	 * @param color The color of the triangle.
	 * @param alpha The alpha value of the triangle.
	 */
	virtual void drawTriangle(const btVector3 &v0, const btVector3 &v1,
			const btVector3 &v2, const btVector3 &color, const btScalar alpha);

	/**
	 * Draw a triangle.
	 * @param v0 First vertex of the triangle.
	 * @param v1 Second vertex of the triangle.
	 * @param v2 Third vertex of the triangle.
	 * @param color The color of the triangle.
	 * @param alpha The alpha value of the triangle.
	 */
	void drawTriangle(const Ogre::Vector3& v0, const Ogre::Vector3& v1,
			const Ogre::Vector3& v2, Ogre::ColourValue color, const Ogre::Real alpha);

	void drawSphere(const Ogre::Vector3& p,const double size, const Ogre::ColourValue& colour);

	void drawSphere(const btVector3, const btScalar size, const btVector3 colour);
	/**
	 * Draw contact point.
	 * @param PointOnB Point on surface.
	 * @param normalOnB Normal on surface.
	 * @param distance Lenght of normal.
	 * @param lifeTime The lifetime of the contact point until it gets removed.
	 * @param color The color of the contact point.
	 */
	virtual void drawContactPoint(const btVector3 &PointOnB,
			const btVector3 &normalOnB, btScalar distance, int lifeTime,
			const btVector3 &color);

	/**
	 * Draw contact point.
	 * @param PointOnB Point on surface.
	 * @param normalOnB Normal on surface.
	 * @param distance Lenght of normal.
	 * @param lifeTime The lifetime of the contact point until it gets removed.
	 * @param color The color of the contact point.
	 */
	void drawContactPoint(const Ogre::Vector3& PointOnB,
			const Ogre::Vector3& normalOnB, Ogre::Real distance, const int lifeTime,
			const Ogre::ColourValue& color);

	/**
	 * Report a warning.
	 * @param warningString The warning string.
	 */
	virtual void reportErrorWarning(const char *warningString);
	virtual void draw3dText(const btVector3 &location, const char *textString);
	virtual void setDebugMode(int debugMode);
	virtual int getDebugMode() const;
	void drawRigidBodyInformation(btDynamicsWorld* btDWorld);
	void draw();

	//accessor methods
	void setDrawAabb(bool enable);
	void setDrawWireframe(bool enable);
	void setDrawConstraints(bool enable);
	void setDrawConstraintLimits(bool enable);
	void setDrawNormals(bool enable);
	void setDrawFeaturesText(bool enable);
	void setDrawContactPoints(bool enable);
	void setNoDeactivation(bool enable);
	void setNoHelpText(bool enable);
	void setDrawText(bool enable);
	void setProfileTimings(bool enable);
	void setEnableSatComparison(bool enable);
	void setDisableBulletLCP(bool enable);
	void setEnableCCD(bool enable);

	bool doesDrawAabb() const;
	bool doesDrawWireframe() const;
	bool doesDrawConstraints() const;
	bool doesDrawConstraintLimits() const;
	bool doesDrawNormals() const;
	bool doesDrawFeaturesText() const;
	bool doesDrawContactPoints() const;
	bool doesNoDeactivation() const;
	bool doesNoHelpText() const;
	bool doesDrawText() const;
	bool doesProfileTimings() const;
	bool doesEnableSatComparison() const;
	bool doesDisableBulletLCP() const;
	bool doesEnableCCD() const;

	bool isDrawTrajectory() const {
		return mDrawTrajectory;
	}

	void setDrawTrajectory(bool drawTrajectory) {
		mDrawTrajectory = drawTrajectory;
	}

	bool isDebugDrawingEnabled() const {
		return mDebugDrawingEnabled;
	}

	void setDebugDrawingEnabled(bool debugDrawingEnabled) {
		mDebugDrawingEnabled = debugDrawingEnabled;
	}
protected:
	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
private:
	struct ContactPoint {
		Ogre::Vector3 from;
		Ogre::Vector3 to;
		Ogre::ColourValue color;
		size_t dieTime;
	};

	struct Line {
		Ogre::Vector3 from;
		Ogre::Vector3 to;
		Ogre::ColourValue color;
		bool drawn;
	};

	struct Triangle {
		Ogre::Vector3 v0;
		Ogre::Vector3 v1;
		Ogre::Vector3 v2;
		Ogre::ColourValue color;
		bool drawn;
	};

	std::vector<Line> mExtLines;
	std::vector<Triangle> mExtTriangles;
	std::vector<ContactPoint> mExtContactPoints;

	int mDebugMode;
	Ogre::ManualObject *mLines;
	Ogre::ManualObject *mLines2;
	Ogre::ManualObject *mLinesSwap;
	Ogre::ManualObject *mTriangles;
	Ogre::ManualObject *mTriangles2;
	Ogre::ManualObject *mTrianglesSwap;
	std::vector<ContactPoint>* mContactPoints;
	std::vector<ContactPoint> mContactPoints1;
	std::vector<ContactPoint> mContactPoints2;

	bool mDrawTrajectory;
	int mClear;
	bool mDrawable;

	bool mDebugDrawingEnabled;

	//TODO: Add 3D text writing capability to ogreBtdebugdrawer #133.
//    Ogre::OverlayManager *olm;
//    Ogre::OverlayContainer *panel;
//    Ogre::Overlay *overlay;
//    Ogre::TextAreaOverlayElement *textArea;
//    Ogre::String szElement;

	const char* getMatName() {
		return "OgreBulletCollisionsDebugDefault";
	}
};

#endif /* VIEW_VISUALIZATION_BULLETPHYSICS_OGREDEBUGDRAWER_H_ */
