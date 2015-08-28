/*
 * DetailsPanel.hpp
 *
 *  Created on: Aug 28, 2015
 *      Author: leviathan
 */

#ifndef VIEW_VISUALIZATION_CEGUI_ELEMENTS_INFOPANELS_DETAILSPANEL_HPP_
#define VIEW_VISUALIZATION_CEGUI_ELEMENTS_INFOPANELS_DETAILSPANEL_HPP_

#include <view/visualization/CEGUI/elements/infopanels/ParamsPanel.hpp>

/*
 *
 */
class DetailsPanel: public ParamsPanel {
public:
	DetailsPanel(const int left, const int top);
	virtual ~DetailsPanel();
};

#endif /* VIEW_VISUALIZATION_CEGUI_ELEMENTS_INFOPANELS_DETAILSPANEL_HPP_ */
