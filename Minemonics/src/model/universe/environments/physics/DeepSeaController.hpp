#ifndef MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_DEEPSEACONTROLLER_H_
#define MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_DEEPSEACONTROLLER_H_

//# corresponding header
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <configuration/Definitions.hpp>

//# forward declarations
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
 * @brief		The deep sea controller simulates physical motion similar to an underwater world.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class DeepSeaController: public PhysicsController {
public:
	DeepSeaController();
	virtual ~DeepSeaController();
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_DEEPSEACONTROLLER_H_ */
