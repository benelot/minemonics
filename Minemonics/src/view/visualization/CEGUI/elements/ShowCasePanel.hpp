#ifndef VIEW_VISUALIZATION_CEGUI_ELEMENTS_CONFIGPANELS_ShowCasePanel_HPP_
#define VIEW_VISUALIZATION_CEGUI_ELEMENTS_CONFIGPANELS_ShowCasePanel_HPP_
//# corresponding header
#include <view/visualization/CEGUI/elements/MovablePanel.hpp>

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
 * @brief		A showcase panel to show all possible elements.
 * @details		Details
 * @date		2015-08-28
 * @author		Benjamin Ellenberger
 */
class ShowCasePanel: public MovablePanel {
public:
	ShowCasePanel(const int left, const int top, const std::string name,
		const int width, const int height);
	~ShowCasePanel(void);
};

#endif /* VIEW_VISUALIZATION_CEGUI_ELEMENTS_CONFIGPANELS_ShowCasePanel_HPP_ */
