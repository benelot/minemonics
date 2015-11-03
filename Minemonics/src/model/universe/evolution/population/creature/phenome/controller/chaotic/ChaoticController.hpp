#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CHAOTIC_CHAOTICCONTROLLER_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CHAOTIC_CHAOTICCONTROLLER_HPP_

//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/controller/Controller.hpp>

//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>

//## controller headers
//## model headers
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The chaotic controller is based on a chaotic dynamical system and generates a chaotic output signal.
 * @details		Details
 * @date		2015-10-30
 * @author		Benjamin Ellenberger
 */
class ChaoticController: public Controller {
public:
	ChaoticController();
	ChaoticController(const ChaoticController& chaoticController);
	virtual ~ChaoticController();

	/**
	 * Initialize the chaotic controller with some initial values
	 * TODO: Find initial values.
	 */
	void initialize();

	void calcChuaCircuit();

	/**
	 * Clone the sine controller.
	 * @return The clone of the sine controller.
	 */
	ChaoticController* clone();

	void perform(const double timeSinceLastFrame);

	void collectInputs();

	//Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization*/

	/**
	 * Serializes the chaotic controller model to a string.
	 * @param os The ostream.
	 * @param chaosController The chaotic controller we want to serialize.
	 * @return A string containing all information about the chaotic controller.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const ChaoticController &chaoticController) {
		os << "ChaoticController: Type=" << chaoticController.mType /**!< The type of controller*/
		<< "/Time=" << chaoticController.mTime; /**!< The timer of the controller */
		return os;
	}

	/**
	 * Serializes the sine controller to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Controller) /**!< Serialize the base object */
		& BOOST_SERIALIZATION_NVP(mTime); /**The time of the chaotic controller*/
	}

private:

	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>(
					"ChaoticController"));
		}
	} _initializer;

	/**
	 * The timer of of sine wave.
	 */
	double mTime;

	double u[3];
};

BOOST_CLASS_VERSION(ChaoticController, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_CONTROLLER_CHAOTIC_CHAOTICCONTROLLER_HPP_ */
