#ifndef DEEPSEACONTROLLER_H_
#define DEEPSEACONTROLLER_H_

//# corresponding header
#include <model/universe/environments/physics/MotionController.hpp>

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
class DeepSeaController: public MotionController {
public:
	DeepSeaController();
	virtual ~DeepSeaController();
};

#endif /* DEEPSEACONTROLLER_H_ */
