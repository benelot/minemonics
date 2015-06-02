#ifndef MODEL_BULLET_OGREDEBUGDRAWER_H_
#define MODEL_BULLET_OGREDEBUGDRAWER_H_

//# corresponding header
//# forward declarations
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
	void initialize(Ogre::SceneManager *scm, bool drawTrajectory);
	virtual void drawLine(const btVector3 &from, const btVector3 &to,
			const btVector3 &color);
	void drawLine(const Ogre::Vector3& from, const Ogre::Vector3& to,
			Ogre::ColourValue color);
	virtual void drawTriangle(const btVector3 &v0, const btVector3 &v1,
			const btVector3 &v2, const btVector3 &color, btScalar);
	void drawTriangle(const Ogre::Vector3& v0, const Ogre::Vector3& v1,
			const Ogre::Vector3& v2, Ogre::ColourValue color, Ogre::Real alpha);
	virtual void drawContactPoint(const btVector3 &PointOnB,
			const btVector3 &normalOnB, btScalar distance, int lifeTime,
			const btVector3 &color);
	void drawContactPoint(const Ogre::Vector3& PointOnB,
			const Ogre::Vector3& normalOnB, Ogre::Real distance, int lifeTime,
			const Ogre::ColourValue& color);
	virtual void reportErrorWarning(const char *warningString);
	virtual void draw3dText(const btVector3 &location, const char *textString);
	virtual void setDebugMode(int debugMode);
	virtual int getDebugMode() const;
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
	std::vector<ContactPoint> *mContactPoints;
	std::vector<ContactPoint> mContactPoints1;
	std::vector<ContactPoint> mContactPoints2;

	bool mDrawTrajectory;
	int mClear;
	bool mDrawable;

	bool mDebugDrawingEnabled;

	const char* getMatName() {
		return "OgreBulletCollisionsDebugDefault";
	}
};

#endif /* MODEL_BULLET_OGREDEBUGDRAWER_H_ */
