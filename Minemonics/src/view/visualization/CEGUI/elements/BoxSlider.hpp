#ifndef VIEW_VISUALIZATION_CEGUI_ELEMENTS_BOXSLIDER_HPP_
#define VIEW_VISUALIZATION_CEGUI_ELEMENTS_BOXSLIDER_HPP_

//# corresponding header
//# forward declarations
//# system headers
#include <string>

//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>

//## view headers
#include <CEGUI/widgets/Editbox.h>
#include <CEGUI/Window.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The box slider is an element combining a text box and a slider.
 * @details		The box slider is an element combining a text box and a slider to slide through common values and but still being able to set another value via the textbox.
 * @date		2015-08-29
 * @author		Benjamin Ellenberger
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
	CEGUI::Slider* mSlider; /**!< The slider of the box slider */
	CEGUI::Editbox* mEditBox; /**!< The box of the box slider */
};

#endif /* VIEW_VISUALIZATION_CEGUI_ELEMENTS_BOXSLIDER_HPP_ */
