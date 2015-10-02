/*
 * BoxSlider.hpp
 *
 *  Created on: Aug 29, 2015
 *      Author: leviathan
 */

#ifndef VIEW_VISUALIZATION_CEGUI_ELEMENTS_BOXSLIDER_HPP_
#define VIEW_VISUALIZATION_CEGUI_ELEMENTS_BOXSLIDER_HPP_

#include <CEGUI/String.h>
#include <CEGUI/widgets/DefaultWindow.h>
#include <CEGUI/widgets/Editbox.h>
#include <CEGUI/Window.h>
#include <CEGUI/widgets/GroupBox.h>
#include <boost/lexical_cast.hpp>

/*
 *
 */
class BoxSlider: public CEGUI::Window {
public:
	BoxSlider(const std::string name, const int width, const int maxValue,
		const int currentValue, const std::string validationString);
	virtual ~BoxSlider();

	void onSliderValueChanged();

	float getCurrentValue() {
		return boost::lexical_cast<int>(mEditBox->getText());
	}
private:
	CEGUI::Slider* mSlider;
	CEGUI::Editbox* mEditBox;
};

#endif /* VIEW_VISUALIZATION_CEGUI_ELEMENTS_BOXSLIDER_HPP_ */
