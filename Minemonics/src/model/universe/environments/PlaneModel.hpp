#ifndef MODEL_UNIVERSE_ENVIRONMENTS_PLANEMODEL_HPP_
#define MODEL_UNIVERSE_ENVIRONMENTS_PLANEMODEL_HPP_

//# corresponding headers
#include <model/universe/environments/EnvironmentModel.hpp>

//# forward declarations
class PlaneBt;

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The plane model holds all the information about a plane.
 * @details		Details
 * @date		2015-05-30
 * @author		Benjamin Ellenberger
 */
class PlaneModel: public EnvironmentModel {
public:
	PlaneModel();
	virtual ~PlaneModel();

	/**
	 * Initialize the plane model.
	 */
	virtual void initialize();

	/**
	 * Update the plane model.
	 * @param timeSinceLastTick The time that has passed since the last update.
	 */
	virtual void update(double timeSinceLastTick);

	//Accessor methods

	PlaneBt* const getPlaneBt() const
	{
		return (PlaneBt*) mEnvironmentPhysics;
	}

	//Serialization
	//TODO: Add serialization to plane model
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_PLANEMODEL_HPP_ */
