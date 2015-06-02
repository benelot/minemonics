#ifndef VIEW_OGRE3D_ENVIRONMENTS_ENVIRONMENTGRAPHICS_H_
#define VIEW_OGRE3D_ENVIRONMENTS_ENVIRONMENTGRAPHICS_H_

/**
 * @brief		The environment graphics is the base class for all environment views.
 * @details		Details
 * @date		2015-05-17
 * @author		Benjamin Ellenberger
 */
class EnvironmentGraphics {
public:
	EnvironmentGraphics();
	virtual ~EnvironmentGraphics();

	virtual bool isInWorld() = 0;
	virtual void addToWorld() = 0;
	virtual void removeFromWorld() = 0;

	//virtual void initialize() = 0;
};

#endif /* VIEW_OGRE3D_ENVIRONMENTS_ENVIRONMENTGRAPHICS_H_ */
