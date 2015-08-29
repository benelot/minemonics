#ifndef VIEW_VISUALIZATION_CEGUI_INFOPANELS_DETAILSPANEL_HPP_
#define VIEW_VISUALIZATION_CEGUI_INFOPANELS_DETAILSPANEL_HPP_

//# corresponding headers
#include <view/visualization/CEGUI/infopanels/ParamsPanel.hpp>

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
 * @brief		The panel that shows additional details about the simulation.
 * @details		Details
 * @date		2015-08-28
 * @author		Benjamin Ellenberger
 */
class DetailsPanel: public ParamsPanel {
public:
	DetailsPanel(const int left, const int top);
	virtual ~DetailsPanel();
};

#endif /* VIEW_VISUALIZATION_CEGUI_INFOPANELS_DETAILSPANEL_HPP_ */
