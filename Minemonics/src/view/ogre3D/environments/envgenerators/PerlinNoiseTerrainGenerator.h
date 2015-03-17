#pragma once

//# corresponding header
//# forward declarations
//# system headers
//## controller headers

//## model headers
//## view headers
#include <OgreTerrainPagedWorldSection.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers

#define PERLIN_B 0x100

///Use PerlinNoise algorithm to generate terrain height map
class PerlinNoiseTerrainGenerator: public Ogre::TerrainPagedWorldSection::TerrainDefiner {
public:
	/** Constructor of PerlinNoiseTerrainGenerator
	 @param alpha The weight when the sum is formed
	 @param beta The harmonic scaling/spacing
	 @param iterationNum The iterations num to produce a point.
	 @param cycle The terrain size maps to one cycle of perlin curve
	 @param heightScale The height maps to curve amplitude
	 */
	PerlinNoiseTerrainGenerator(const Ogre::Real& alpha = 3.3, const Ogre::Real& beta = 2.2,
			int iterationNum = 10, const Ogre::Real& cycle = 128,
			const Ogre::Real& heightScale = 4);

	/// Define terrain
	virtual void define(Ogre::TerrainGroup* terrainGroup, long x, long y);
	/// Random terrain origin point to make it looks different
	void randomize();
private:
	/** Produce a noise according to PerlinNoise algorithm
	 Generate multiple values by calling noise():
	 v0=noise(x,y),
	 v1=noise(x*beta,y*beta),
	 v2=noise(x*beta*beta,y*beta*beta)
	 ...
	 Accumulate them:
	 result = v0/alpha + v1/(alpha*alpha) + v1/(alpha*alpha*alpha) + ...
	 */
	Ogre::Real produceSingleHeight(const Ogre::Vector2& vec2);

	/// Generate a 2D noise
	Ogre::Real noise(const Ogre::Vector2& vec2);

	inline Ogre::Real sCurve(const Ogre::Real& t) const {
		return t * t * (3 - 2 * t);
	}
	inline Ogre::Real lerp(const Ogre::Real& t, const Ogre::Real& a, const Ogre::Real& b) const {
		return a + t * (b - a);
	}
	void setup(const Ogre::Real& target, int& b0, int& b1, Ogre::Real& r0, Ogre::Real& r1);

	Ogre::Real mAlpha;
	Ogre::Real mBeta;
	int mIterationNum;
	Ogre::Real mCycle;
	Ogre::Real mHeightScale;
	Ogre::Vector2 mOriginPoint;

	int p[PERLIN_B + PERLIN_B + 2];
	Ogre::Vector3 g3[PERLIN_B + PERLIN_B + 2];
	Ogre::Vector2 g2[PERLIN_B + PERLIN_B + 2];
	Ogre::Real g1[PERLIN_B + PERLIN_B + 2];
};
