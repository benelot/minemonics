#ifndef VIEW_VISUALIZATION_OVERLAY_OGREOVERLAYINFO_H_
#define VIEW_VISUALIZATION_OVERLAY_OGREOVERLAYINFO_H_

//# corresponding header
//# forward declarations
//# system headers
#include <string>

//## controller headers
//## model headers
//## view headers
#include <OgreVector3.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers

/**
 * @brief		A data structure to holds a string of information overlay data together with a position on the screen.
 * @details		Details
 * @date		2015-03-17
 * @author		Benjamin Ellenberger
 */
class InfoOverlayData {
public:
	InfoOverlayData(Ogre::Vector3 position, std::string text);
	virtual ~InfoOverlayData();

	const Ogre::Vector3& getPosition() const {
		return mPosition;
	}

	const std::string& getText() const {
		return mText;
	}

private:
	Ogre::Vector3 mPosition;
	std::string mText;
};

#endif /* VIEW_VISUALIZATION_OVERLAY_OGREOVERLAYINFO_H_ */
