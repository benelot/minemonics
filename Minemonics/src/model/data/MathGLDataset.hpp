#ifndef VIEW_VISUALIZATION_CEGUI_INFOPANELS_GRAPHPANELS_MATHGLDATASET_HPP_
#define VIEW_VISUALIZATION_CEGUI_INFOPANELS_GRAPHPANELS_MATHGLDATASET_HPP_

//# corresponding headers
//# forward declarations
class mglData;

//# system headers
#include <string>

//## controller headers
//## model headers
#include <OgreColourValue.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The MathGL Dataset holds the original dataset and additionally a dataset ID.
 * @details		Details
 * @date		2015-12-08
 * @author		Benjamin Ellenberger
 */
class MathGLDataset {
public:
	MathGLDataset();
	virtual ~MathGLDataset();

	void initialize(std::string datasetID, int dimensions, int length);

	void addData(const double const* newDataX, const double const* newDataY,
		const double const* newDataZ, const int dimensions, const int length);

	std::string getDatasetId() const {
		return mDatasetID;
	}

	void setDatasetId(std::string datasetId) {
		mDatasetID = datasetId;
	}

	int getDimensions() const {
		return mDimensions;
	}

	void setDimensions(int dimensions) {
		mDimensions = dimensions;
	}

	int getLength() const {
		return mLength;
	}

	void setLength(int length) {
		mLength = length;
	}

	const Ogre::ColourValue& getPlotColor() const {
		return mPlotColor;
	}

	void setPlotColor(const Ogre::ColourValue& plotColor) {
		mPlotColor = plotColor;
	}

	const mglData* getDatasetX() const {
		return mDatasetX;
	}

	const mglData* getDatasetY() const {
		return mDatasetY;
	}

	const mglData* getDatasetZ() const {
		return mDatasetZ;
	}

private:
	Ogre::ColourValue mPlotColor;
	int mLength;
	int mDimensions;
	mglData* mDatasetX;
	mglData* mDatasetY;
	mglData* mDatasetZ;
	std::string mDatasetID;
};

#endif /* VIEW_VISUALIZATION_CEGUI_INFOPANELS_GRAPHPANELS_MATHGLDATASET_HPP_ */
