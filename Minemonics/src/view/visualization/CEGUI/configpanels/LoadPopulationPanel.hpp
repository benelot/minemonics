#ifndef VIEW_VISUALIZATION_CEGUI_ELEMENTS_CONFIGPANELS_LOADPOPULATIONPANEL_HPP_
#define VIEW_VISUALIZATION_CEGUI_ELEMENTS_CONFIGPANELS_LOADPOPULATIONPANEL_HPP_

//# corresponding header
#include <view/visualization/CEGUI/configpanels/FileDialog.hpp>

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
 * @brief		A panel to load a population with.
 * @details		Details
 * @date		2015-08-28
 * @author		Benjamin Ellenberger
 */
class LoadPopulationPanel: public FileDialog {
public:
	LoadPopulationPanel(const int left, const int top, const std::string name);
	~LoadPopulationPanel(void);

	virtual void openFile(std::string filePath);
};

#endif /* VIEW_VISUALIZATION_CEGUI_ELEMENTS_CONFIGPANELS_LOADPOPULATIONPANEL_HPP_ */
