#ifndef VIEW_UNIVERSE_ENVIRONMENTS_ENVIRONMENTGRAPHICS_H_
#define VIEW_UNIVERSE_ENVIRONMENTS_ENVIRONMENTGRAPHICS_H_

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

	/**
	 * is the environment view in the world?
	 * @return if the environment view is in the world.
	 */
	virtual bool isInWorld() const = 0;

	/**
	 * Add the environment view to the world.
	 */
	virtual void addToWorld() = 0;
	virtual void removeFromWorld() = 0;
};

#endif /* VIEW_UNIVERSE_ENVIRONMENTS_ENVIRONMENTGRAPHICS_H_ */
