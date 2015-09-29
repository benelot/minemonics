#ifndef MODEL_SERIALIZABLE_HPP_
#define MODEL_SERIALIZABLE_HPP_

//# corresponding headers
//# forward declarations
//# system headers
#include <string>

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
 * @brief		The Serializable class is a base class for all classes that are serializable.
 * @details		Details
 * @date		2015-08-29
 * @author		Benjamin Ellenberger
 */
class Serializable {
public:
	Serializable();
	virtual ~Serializable();

	const std::string& getSerializationPath() const {
		return mSerializationPath;
	}

	void setSerializationPath(const std::string& serializationPath) {
		mSerializationPath = serializationPath;
	}

protected:
	std::string mSerializationPath; /**!< The serialization path. */
};

#endif /* MODEL_SERIALIZABLE_HPP_ */
