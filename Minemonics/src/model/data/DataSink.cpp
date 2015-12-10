//# corresponding header
#include <model/data/DataSink.hpp>

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

DataSink::DataSink() {

}

DataSink::~DataSink() {
	// TODO Auto-generated destructor stub
}

void DataSink::addData(double* newDataX,double* newDataY,double* newDataZ, int dimensions, int rows) {
	mDataset.addData(newDataX,newDataY,newDataZ, dimensions, rows);
}

void DataSink::initialize(std::string dataSinkID, int dimensions, int length) {
	mDataset.initialize(dataSinkID, dimensions, length);
}

