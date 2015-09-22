#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_COMPONENTMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_COMPONENTMODEL_HPP_

//# corresponding headers
//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <vector>
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

/**
 * @brief		The component model holds all the state information of the component independent of other models.
 * @details		Details
 * @date		2015-05-09
 * @author		Benjamin Ellenberger
 */
class ComponentModel {
public:
	enum ComponentType {
		UnknownComponent, LimbComponent, JointComponent, NUM_COMPONENTS
	};

	ComponentModel();
	virtual ~ComponentModel();

	/**
	 * Initialize the component model.
	 * @param type The type of component.
	 */
	void initialize(const ComponentType type, const std::vector<ComponentModel*>::size_type ownIndex);

	/**
	 * Compare the component model to another component model.
	 * @param componentModel Another component model.
	 * @return If the component model is equal to the other component model.
	 */
	bool equals(const ComponentModel& componentModel) const;

	/**
	 * Clone the component model.
	 * @return The clone of the component model.
	 */
	virtual ComponentModel* clone() = 0;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the component model to a string.
	 * @param os The ostream.
	 * @param creature The component we want to serialize.
	 * @return A string containing all information about the component.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const ComponentModel & componentModel) {
		return os << "ComponentModel: Type=" << componentModel.mComponentType;
	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**The type of the component*/
		& BOOST_SERIALIZATION_NVP(mComponentType);
	}

	ComponentType getComponentType() const {
		return mComponentType;
	}

	std::vector<ComponentModel*>::size_type getIndex() const {
		return mOwnIndex;
	}

protected:
	/**
	 * Component type of the compoment.
	 */
	ComponentType mComponentType;

	/**
	 * The index of the component in the genotype.
	 */
	std::vector<ComponentModel*>::size_type mOwnIndex;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_COMPONENTMODEL_HPP_ */
