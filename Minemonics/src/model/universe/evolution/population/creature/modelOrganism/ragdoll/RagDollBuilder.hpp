#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_MODELORGANISM_MODELLEG_RagDollBuilder_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_MODELORGANISM_MODELLEG_RagDollBuilder_HPP_

//# corresponding headers
//# forward declarations
class MixedGenome;

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/controller/ControllerGene.hpp>

//## view headers
//## utils headers

/**
 * @brief		The model leg builder creates a simple model leg in the genome.
 * @details		Details
 * @date		2015-11-05
 * @author		Benjamin Ellenberger
 */
class RagDollBuilder {
public:
	enum {
		BODYPART_ABDOMENPELVIS = 0, BODYPART_THORAX, BODYPART_HEAD,

		BODYPART_LEFT_THIGH, BODYPART_LEFT_LEG,

		BODYPART_RIGHT_THIGH, BODYPART_RIGHT_LEG,

		BODYPART_LEFT_UPPER_ARM, BODYPART_LEFT_FOREARM,

		BODYPART_RIGHT_UPPER_ARM, BODYPART_RIGHT_FOREARM,

		BODYPART_COUNT
	};

	enum {
		JOINT_PELVIS_THORAX = 0, JOINT_THORAX_HEAD,

		JOINT_LEFT_HIP, JOINT_LEFT_KNEE,

		JOINT_RIGHT_HIP, JOINT_RIGHT_KNEE,

		JOINT_LEFT_SHOULDER, JOINT_LEFT_ELBOW,

		JOINT_RIGHT_SHOULDER, JOINT_RIGHT_ELBOW,

		JOINT_COUNT
	};

	//From: http://www.exrx.net/Kinesiology/Segments.html
	static const double RAGDOLL_HEAD = 8.26;
	static const double RAGDOLL_THORAX = 20.1;
	static const double RAGDOLL_ABDOMENPELVIS = 26.72;
	static const double RAGDOLL_THIGH = 10.5;
	static const double RAGDOLL_LEG = 6.18;
	static const double RAGDOLL_UPPER_ARM = 3.25;
	static const double RAGDOLL_FOREARM = 2.52;

	static void build(MixedGenome* genome,
		ControllerGene::ControllerType controllerType);
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_MODELORGANISM_MODELLEG_RagDollBuilder_HPP_ */
