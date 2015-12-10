#ifndef MODEL_DATA_DATASINK_HPP_
#define MODEL_DATA_DATASINK_HPP_

//# corresponding header
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
#include <model/data/MathGLDataset.hpp>

//## view headers
//## utils headers

/**
 * @brief	The datasink defines an interface to the plotting system
 * @details
 * @date		2015-12-08
 * @author		Benjamin Ellenberger
 */
class DataSink {
public:
	DataSink();
	DataSink(std::string dataSinkID);
	virtual ~DataSink();

	void initialize(std::string dataSinkID, int dimensions, int length);

	void addData(double* newDataX,double* newDataY,double* newDataZ, int dimensions, int length);

	const MathGLDataset& getDataset() const {
		return mDataset;
	}

private:
	MathGLDataset mDataset;
};

#endif /* MODEL_DATA_DATASINK_HPP_ */
