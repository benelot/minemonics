//# corresponding headers
//# forward declarations
//# system headers
#include <string>

//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>

//## view headers
#include <CEGUI/Element.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/Size.h>
#include <CEGUI/UDim.h>
#include <CEGUI/Vector.h>
#include <CEGUI/widgets/Slider.h>
#include <CEGUI/WindowManager.h>

//# custom headers
//## base headers
//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
#include <view/visualization/CEGUI/elements/BoxSlider.hpp>

//## utils headers

BoxSlider::BoxSlider(const std::string name, const int width,
	const int maxValue, const int currentValue,
	const std::string validationString) :
	CEGUI::Window(CEGUIConfiguration::CEGUI_SCHEME + "/Slider", name) {
	setSize(CEGUI::USize(CEGUI::UDim(0, width), CEGUI::UDim(0, 20)));
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	double editBoxWidth = 50;
	mSlider = static_cast<CEGUI::Slider*>(wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/HorizontalSlider"));

	double sliderLength = 0.6f;

	mSlider->setSize(
		CEGUI::USize(CEGUI::UDim(0, sliderLength * width), CEGUI::UDim(0, 20)));

	mSlider->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0, 0.0f), CEGUI::UDim(0, 0.0f)));

	mSlider->setMaxValue(maxValue);
	mSlider->setClickStep(1.0f);
	mSlider->setCurrentValue(currentValue);

	mSlider->subscribeEvent(CEGUI::Slider::EventValueChanged,
		CEGUI::Event::Subscriber(&BoxSlider::onSliderValueChanged, this));

	addChild (mSlider);

	mEditBox = static_cast<CEGUI::Editbox*>(wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/Editbox"));
	mEditBox->setText(
		boost::lexical_cast < std::string
			> (floor(mSlider->getCurrentValue())));
//	CEGUI::String valueEditbox = mEditBox->getText(); // Retrieve the text
	mEditBox->setValidationString(validationString);
	mEditBox->setSize(
		CEGUI::USize(CEGUI::UDim(0, editBoxWidth), CEGUI::UDim(0, 20)));
	mEditBox->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0.6f, 0.0f), CEGUI::UDim(0.0, 0.0f)));
	addChild (mEditBox);

}

BoxSlider::~BoxSlider() {

}

void BoxSlider::onSliderValueChanged() {
	mEditBox->setText(
		boost::lexical_cast < std::string
			> (floor(mSlider->getCurrentValue())));
}

