//# corresponding headers
#include <model/data/MathGLDataset.hpp>

//# system headers
#include <stddef.h>
#include <cstring>

//## controller headers
//## model headers
#include <mgl2/data.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

//#include <mgl2/mgl.h>

MathGLDataset::MathGLDataset() :
	mLength(0), mDimensions(0), mDatasetID(""), mPlotColor(
		Randomness::getSingleton()->nextUnifDouble(0, 1),
		Randomness::getSingleton()->nextUnifDouble(0, 1),
		Randomness::getSingleton()->nextUnifDouble(0, 1)), mDatasetX(NULL), mDatasetY(
	NULL), mDatasetZ(NULL) {
}

MathGLDataset::~MathGLDataset() {
	delete mDatasetX;
	mDatasetX = NULL;

}

void MathGLDataset::initialize(std::string datasetID, int dimensions,
	int length) {
	mDatasetID = datasetID;
	mDimensions = dimensions;
	mLength = length;

	switch (dimensions) {
	case 3: {
		mDatasetZ = new mglData(length);
		mDatasetY = new mglData(length);
		mDatasetX = new mglData(length);
		break;
	}
	case 2: {
		mDatasetY = new mglData(length);
		mDatasetX = new mglData(length);
		break;
	}
	case 1: {
		mDatasetX = new mglData(length);
		break;
	}
	}

}

void MathGLDataset::addData(double* newDataX, double* newDataY,
	double* newDataZ, int dimensions, int length) {
	if (mDatasetX && dimensions >= 1) {

		//TODO: Make this more safe, if mLength < length etc.
		std::memmove(mDatasetX->a + length, mDatasetX->a,
			(mDatasetX->nx - length) * sizeof(mreal));

		for (int i = 0; i < length; i++) {
			mDatasetX->a[i] = newDataX[i];
		}
	}

	if (mDatasetY && dimensions >= 2) {
		std::memmove(mDatasetY->a + length, mDatasetY->a,
			(mDatasetY->nx - length) * sizeof(mreal));
		for (int i = 0; i < length; i++) {
			mDatasetY->a[i] = newDataY[i];
		}
	}

	if (mDatasetZ && dimensions == 3) {
		std::memmove(mDatasetZ->a + length, mDatasetZ->a,
			(mDatasetZ->nx - length) * sizeof(mreal));
		for (int i = 0; i < length; i++) {
			mDatasetZ->a[i] = newDataZ[i];
		}
	}
}

