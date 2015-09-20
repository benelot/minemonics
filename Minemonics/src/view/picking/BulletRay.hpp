#ifndef VIEW_PICKING_BULLETRAY_HPP_
#define VIEW_PICKING_BULLETRAY_HPP_

//# corresponding headers
#include <configuration/Definitions.hpp>

//# forward declarations
class btVector3;
class btDynamicsWorld;

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
 * @brief		The object picker implemented in bullet physics.
 * @details		Details
 * @date		2015-05-20
 * @author		Benjamin Ellenberger
 */
class BulletRay {
public:
	static btVector3 castRay(btDynamicsWorld* world, btVector3 origin,
		btVector3 direction);
};

#endif /* VIEW_PICKING_BULLETRAY_HPP_ */
