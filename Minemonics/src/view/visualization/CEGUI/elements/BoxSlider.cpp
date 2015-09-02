/*
 * BoxSlider.cpp
 *
 *  Created on: Aug 29, 2015
 *      Author: leviathan
 */

#include <boost/lexical_cast.hpp>
#include <configuration/CEGUIConfiguration.hpp>
#include <CEGUI/Element.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/Size.h>
#include <CEGUI/UDim.h>
#include <CEGUI/Vector.h>
#include <CEGUI/widgets/Slider.h>
#include <CEGUI/WindowManager.h>
#include <view/visualization/CEGUI/elements/BoxSlider.hpp>
#include <string>

BoxSlider::BoxSlider(const std::string name, const int width,
	const std::string validationString) :
	CEGUI::Window(CEGUIConfiguration::CEGUI_SCHEME + "/Slider", name) {
	setSize(CEGUI::USize(CEGUI::UDim(0, width), CEGUI::UDim(0, 30)));
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	mSlider = static_cast<CEGUI::Slider*>(wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/Slider"));
	mSlider->setMaxValue(100.0f);
	mSlider->setClickStep(1.0f);
	mSlider->setCurrentValue(10.0f);
	mSlider->subscribeEvent(CEGUI::Slider::EventValueChanged,
		CEGUI::Event::Subscriber(&BoxSlider::onSliderValueChanged, this));
//	float valueSlider = slider->getCurrentValue(); // Retrieve the value
	mSlider->setSize(CEGUI::USize(CEGUI::UDim(0, 120), CEGUI::UDim(0, 20)));
	mSlider->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0.0, 0.0f), CEGUI::UDim(0.0, 0.0f)));
	addChild (mSlider);

	mEditBox = static_cast<CEGUI::Editbox*>(wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/Editbox"));
	mEditBox->setText(
		boost::lexical_cast < std::string > (mSlider->getCurrentValue()));
//	CEGUI::String valueEditbox = mEditBox->getText(); // Retrieve the text
	mEditBox->setValidationString(validationString);
	mEditBox->setSize(CEGUI::USize(CEGUI::UDim(0, 50), CEGUI::UDim(0, 20)));
	mEditBox->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0.6f, 0.0f), CEGUI::UDim(0.0, 0.0f)));
	addChild (mEditBox);

}

BoxSlider::~BoxSlider() {
	
}

void BoxSlider::onSliderValueChanged() {
	mEditBox->setText(
		boost::lexical_cast < std::string > (mSlider->getCurrentValue()));
}

