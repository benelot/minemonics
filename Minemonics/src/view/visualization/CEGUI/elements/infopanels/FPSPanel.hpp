/*
 * FPSPanel.hpp
 *
 *  Created on: Aug 28, 2015
 *      Author: leviathan
 */

#ifndef VIEW_VISUALIZATION_CEGUI_ELEMENTS_INFOPANELS_FPSPANEL_HPP_
#define VIEW_VISUALIZATION_CEGUI_ELEMENTS_INFOPANELS_FPSPANEL_HPP_

#include <view/visualization/CEGUI/elements/infopanels/ParamsPanel.hpp>

/*
 *
 */
class FPSPanel: public ParamsPanel {
public:
	FPSPanel(const int left, const int top);
	virtual ~FPSPanel();
};

#endif /* VIEW_VISUALIZATION_CEGUI_ELEMENTS_INFOPANELS_FPSPANEL_HPP_ */
