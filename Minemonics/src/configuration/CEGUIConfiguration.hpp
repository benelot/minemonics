#ifndef CEGUICONFIGURATION_H_
#define CEGUICONFIGURATION_H_

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
	static const float INFOPANEL_TEXT = 30;

	/**
	 * Information panel border height
	 */
	static const float INFOPANEL_BORDER = 10;

	/**
	 * Information panel column1 height
	 */
	static const float INFOPANEL_COL1 = 0.5f;

	/**
	 * Information panel column2 height
	 */
	static const float INFOPANEL_COL2 = 0.5f;
};

#endif /* CEGUICONFIGURATION_H_ */
