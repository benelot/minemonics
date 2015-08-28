#ifndef CONFIGURATION_CEGUICONFIGURATION_H_
#define CONFIGURATION_CEGUICONFIGURATION_H_

//# corresponding headers
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
 * @brief		The configuration of the CEGUI panels. It defines sizes of columns and text etc.
 * @details		The configuration of the CEGUI panels. It defines sizes of columns and text etc.
 * @date		2015-03-02
 * @author		Benjamin Ellenberger
 */
class CEGUIConfiguration {
public:
	/**
	 * Information panel caption height
	 */
	static const float INFOPANEL_CAPTION = 15;

	/**
	 * Information panel text height
	 */
	static const float INFOPANEL_TEXT_HEIGHT = 35;

	/**
	 * Information panel border height
	 */
	static const float INFOPANEL_BORDER = 10;

	/**
	 * Information panel column1 width
	 */
	static const float INFOPANEL_LEFT_COL_WIDTH = 0.3f;

	/**
	 * Information panel column2 width
	 */
	static const float INFOPANEL_RIGHT_COL_WIDTH = 0.7f;
};

#endif /* CONFIGURATION_CEGUICONFIGURATION_H_ */
