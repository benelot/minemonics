#ifndef VIEW_VISUALIZATION_CEGUI_ELEMENTS_INFOPANELS_FPSPANEL_HPP_
#define VIEW_VISUALIZATION_CEGUI_ELEMENTS_INFOPANELS_FPSPANEL_HPP_

//# corresponding headers
#include <view/visualization/CEGUI/elements/infopanels/ParamsPanel.hpp>

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
 * @brief		The panel that shows the current fps.
 * @details		Details
 * @date		2015-08-28
 * @author		Benjamin Ellenberger
 */
class FPSPanel: public ParamsPanel {
public:
	FPSPanel(const int left, const int top);
	virtual ~FPSPanel();
};

#endif /* VIEW_VISUALIZATION_CEGUI_ELEMENTS_INFOPANELS_FPSPANEL_HPP_ */
