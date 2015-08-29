//# corresponding header
#include <view/visualization/CEGUI/elements/ShowCasePanel.hpp>

//## system headers
#include <stddef.h>
#include <string>
#include <vector>

//## controller headers
//## model headers
//## view headers
#include <CEGUI/Element.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/Size.h>
#include <CEGUI/String.h>
#include <CEGUI/UDim.h>
#include <CEGUI/Vector.h>
#include <CEGUI/widgets/Combobox.h>
#include <CEGUI/widgets/DefaultWindow.h>
#include <CEGUI/widgets/Editbox.h>
#include <CEGUI/widgets/FrameWindow.h>
#include <CEGUI/widgets/Listbox.h>
#include <CEGUI/widgets/ListboxItem.h>
#include <CEGUI/widgets/ListboxTextItem.h>
#include <CEGUI/widgets/MultiColumnList.h>
#include <CEGUI/widgets/MultiLineEditbox.h>
#include <CEGUI/widgets/ProgressBar.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/widgets/RadioButton.h>
#include <CEGUI/widgets/ScrollablePane.h>
#include <CEGUI/widgets/Scrollbar.h>
#include <CEGUI/widgets/Slider.h>
#include <CEGUI/widgets/Spinner.h>
#include <CEGUI/widgets/TabControl.h>
#include <CEGUI/widgets/ToggleButton.h>
#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>

//# custom headers
//## base headers
//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers

ShowCasePanel::ShowCasePanel(const int left, const int top,
	const std::string name, const int width, const int height) :
	MovablePanel(name, MovablePanel::FPSPANEL) {

	MovablePanel::initialize(left, top, width, height, false);

	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

//	/* StaticText */
//	CEGUI::DefaultWindow* staticText =
//		static_cast<CEGUI::DefaultWindow*>(wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/StaticText"));
//	staticText->setText("Red Static Text");
//	// Colours are specified as aarrggbb in Hexadecimal
//	// Where aa is alpha, rr is red, gg is green, and bb is blue
//	// tl: top left,  tr: top right,  bl: bottom left,  br: bottom right
//	staticText->setProperty("TextColours",
//		"tl:FFFF0000 tr:FFFF0000 bl:FFFF0000 br:FFFF0000");
//	staticText->setProperty("VertFormatting", "VertCentred"); // TopAligned, BottomAligned, VertCentred
//	staticText->setProperty("HorzFormatting", "HorzCentred"); // LeftAligned, RightAligned, HorzCentred
//	// HorzJustified, WordWrapLeftAligned, WordWrapRightAligned, WordWrapCentred, WordWrapJustified
//	staticText->setTooltipText("This is a StaticText widget");
//	innerWidget->addChild(staticText);
//
//	/* StaticImage */
//	CEGUI::DefaultWindow* staticImage =
//		static_cast<CEGUI::DefaultWindow*>(wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/StaticImage"));
////	staticImage->setProperty("Image",
////		"set:ImageForStaticImage image:full_image"); // "full_image" is a default name from CEGUIImageset::Imageset()
//	innerWidget->addChild(staticImage);

	/* ProgressBar */
	CEGUI::ProgressBar* progressBar =
		static_cast<CEGUI::ProgressBar*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/ProgressBar"));
	progressBar->setProgress(0.25f); // Initial progress of 25%
	progressBar->setStepSize(0.10f); // Calling step() will increase the progress by 10%
	progressBar->step(); // Advance the progress by the size specified in setStepSize()
	progressBar->adjustProgress(-0.05f); // Adjust the progress by a delta value rather than setting a new value through setProgress
	progressBar->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0.0f, 0.1f), CEGUI::UDim(0.0f, 0.1f)));
	float valueProgressBar = progressBar->getProgress(); // initial 0.25f + step 0.10f - adjustment 0.05f = 0.30f
	mBaseWidget->addChild(progressBar);
//
	/* Button */
	CEGUI::PushButton* btnClose =
		static_cast<CEGUI::PushButton*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Button"));
	btnClose->setText("Exit");
	btnClose->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0.3f, 0.0f), CEGUI::UDim(0.2f, 0.0f)));
	mBaseWidget->addChild(btnClose);

//	/* ScrollablePane */
//	CEGUI::ScrollablePane* scrollablePane =
//		static_cast<CEGUI::ScrollablePane*>(wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/ScrollablePane"));
//	CEGUI::DefaultWindow* staticImageInScrollablePane =
//		static_cast<CEGUI::DefaultWindow*>(wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/StaticImage",
//			"StaticImageInScrollablePane"));
////	staticImageInScrollablePane->setProperty("Image",
////		"set:ImageForScrollablePane image:full_image"); // "full_image" is a default name from CEGUIImageset::Imageset()
//	staticImageInScrollablePane->setPosition(
//		CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(0.0f, 0.0f))); // Start in the upper left corner
//	staticImageInScrollablePane->setWidth(CEGUI::UDim(2.0f, 0.0f)); // Twice the width of the parent, the ScrollablePane
//	staticImageInScrollablePane->setHeight(CEGUI::UDim(2.0f, 0.0f)); // Twice the height of the parent, the ScrollablePane
//	scrollablePane->addChild(staticImageInScrollablePane); // Add the image to the // Twice the width of the parent, the ScrollablePane
//	CEGUI::Editbox* editboxInScrollablePane =
//		static_cast<CEGUI::Editbox*>(wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/Editbox",
//			"EditboxInScrollablePane"));
//	editboxInScrollablePane->setPosition(
//		CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(2.1f, 0.0f))); // Start below the image
//	editboxInScrollablePane->setWidth(CEGUI::UDim(2.0f, 0.0f));
//	editboxInScrollablePane->setHeight(CEGUI::UDim(0.3f, 0.0f));
//	scrollablePane->addChild(editboxInScrollablePane);
//	innerWidget->addChild(scrollablePane);
//
	/* ToggleButton */
	CEGUI::ToggleButton* toggleButton =
		static_cast<CEGUI::ToggleButton*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Checkbox"));
	toggleButton->setSelected(true);
	bool valueCheckbox = toggleButton->isSelected(); // Retrieve whether it is checked
	toggleButton->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0.3f, 0.0f), CEGUI::UDim(0.3f, 0.0f)));
	mBaseWidget->addChild(toggleButton);
//
	/* Spinner */
//	CEGUI::Spinner* spinner = static_cast<CEGUI::Spinner*>(wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/Spinner"));
////	spinner->setTextInputMode(CEGUI::Spinner::FloatingPoint); // FloatingPoint, Integer, Hexadecimal, Octal
////	spinner->setMinimumValue(-10.0f);
////	spinner->setMaximumValue(10.0f);
////	spinner->setStepSize(0.2f);
////	spinner->setCurrentValue(5.2f);
//	float valueSpinner = spinner->getCurrentValue(); // Retrieve the value
//	spinner->setPosition(
//		CEGUI::UVector2(CEGUI::UDim(0.8f, 0.0f), CEGUI::UDim(0.8f, 0.0f)));
//	innerWidget->addChild(spinner);
//	/* Editbox */
//	CEGUI::Editbox* editbox = static_cast<CEGUI::Editbox*>(wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/Editbox"));
//	editbox->setText("Editbox values");
////	editbox->setValidator(CEGUI::RegexMatcher());
////	editbox->setMaxTextLength(13); // The trailing 's' will not be displayed
////	editbox->setReadOnly(false);
////	editbox->setTextMasked(false);
////	editbox->setMaskCodePoint(0x002A); // *
//	CEGUI::String valueEditbox = editbox->getText(); // Retrieve the text
//	editbox->setPosition(
//		CEGUI::UVector2(CEGUI::UDim(0.8f, 0.0f), CEGUI::UDim(0.35f, 0.0f)));
//	innerWidget->addChild(editbox);
//
	/* Slider */
	CEGUI::Slider* slider = static_cast<CEGUI::Slider*>(wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/Slider"));
	slider->setMaxValue(100.0f);
	slider->setClickStep(10.0f);
	slider->setCurrentValue(20.0f);
	float valueSlider = slider->getCurrentValue(); // Retrieve the value
	slider->setSize(CEGUI::USize(CEGUI::UDim(0, 100), CEGUI::UDim(0, 20)));
	slider->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0.6f, 0.0f), CEGUI::UDim(0.7f, 0.0f)));
	mBaseWidget->addChild(slider);
//
//	/* Scrollbar (Horizontal) */
//	CEGUI::Scrollbar* scrollbarHorizontal =
//		static_cast<CEGUI::Scrollbar*>(wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/HorizontalScrollbar"));
//	scrollbarHorizontal->setDocumentSize(100.0f);
//	scrollbarHorizontal->setPageSize(10.0f);
//	scrollbarHorizontal->setStepSize(1.0f);
//	scrollbarHorizontal->setScrollPosition(75.0f);
//	float valueScrollbarHorizontal = scrollbarHorizontal->getScrollPosition(); // Retrieve the scroll position
//	innerWidget->addChild(scrollbarHorizontal);
//
//	/* Scrollbar (Vertical) */
//	CEGUI::Scrollbar* scrollbarVertical =
//		static_cast<CEGUI::Scrollbar*>(wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/VerticalScrollbar"));
//	scrollbarVertical->setDocumentSize(100.0f);
//	scrollbarVertical->setPageSize(10.0f);
//	scrollbarVertical->setStepSize(1.0f);
//	scrollbarVertical->setScrollPosition(25.0f);
//	float valueScrollbarVertical = scrollbarVertical->getScrollPosition(); // Retrieve the scroll position
//	innerWidget->addChild(scrollbarVertical);
//
	/* MultiLineEditbox */
	CEGUI::MultiLineEditbox* multiLineEditbox =
		static_cast<CEGUI::MultiLineEditbox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MultiLineEditbox"));
	multiLineEditbox->setText("MultiLineEditbox value");
	multiLineEditbox->setReadOnly(false);
	multiLineEditbox->setWordWrapping(true);
	CEGUI::String valueMultiLineEditbox = multiLineEditbox->getText(); // Retrieve the text
	multiLineEditbox->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0.9f, 0.0f), CEGUI::UDim(0.3f, 0.0f)));
	mBaseWidget->addChild(multiLineEditbox);

	/* RadioButton */
	CEGUI::RadioButton* radioButton =
		static_cast<CEGUI::RadioButton*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/RadioButton"));
	radioButton->setGroupID(1);
	radioButton->setID(101);
	radioButton->setSelected(true);
//	radioButton = static_cast<CEGUI::RadioButton*>(wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/RadioButton", "RadioButton"));
//	radioButton->setGroupID(1);
//	radioButton->setID(102);
//	radioButton = static_cast<CEGUI::RadioButton*>(wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/RadioButton", "RadioButton_C"));
//	radioButton->setGroupID(1);
//	radioButton->setID(103);
//	radioButton = static_cast<CEGUI::RadioButton*>(wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/RadioButton", "RadioButton_1"));
//	radioButton->setGroupID(2);
//	radioButton->setID(201);
//	radioButton->setSelected(true);
//	radioButton = static_cast<CEGUI::RadioButton*>(wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/RadioButton", "RadioButton_2"));
//	radioButton->setGroupID(2);
//	radioButton->setID(202);
//	radioButton = static_cast<CEGUI::RadioButton*>(wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/RadioButton", "RadioButton_3"));
//	radioButton->setGroupID(2);
//	radioButton->setID(203);
//	radioButton = static_cast<CEGUI::RadioButton*>(wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/RadioButton", "RadioButton_A")); // Get handle of one radio button from the group
////	uint valueRadioButtonLetters =
////		radioButton->getSelectedButtonInGroup()->getID(); // Get selected ID
//	radioButton = static_cast<CEGUI::RadioButton*>(wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/RadioButton", "RadioButton_3")); // Can obtain the handle of any radio button in the group
////	uint valueRadioButtonNumbers =
////		radioButton->getSelectedButtonInGroup()->getID();
//	radioButton->setSelected(true); // Specify which button should appear selected by default
	radioButton->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0.7f, 0.0f), CEGUI::UDim(0.2f, 0.0f)));
	mBaseWidget->addChild(radioButton);

//	/* Listbox */
//	CEGUI::Listbox* listbox = static_cast<CEGUI::Listbox*>(wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/Listbox"));
//	listbox->setMultiselectEnabled(false);
//	CEGUI::ListboxTextItem* itemListbox = new CEGUI::ListboxTextItem("Value A",
//		1);
////	itemListbox->setSelectionBrushImage("MultiListSelectionBrush");
//	listbox->addItem(itemListbox);
//	itemListbox = new CEGUI::ListboxTextItem("Value B", 2);
////	itemListbox->setSelectionBrushImage("MultiListSelectionBrush");
//	listbox->addItem(itemListbox);
//	itemListbox = new CEGUI::ListboxTextItem("Value C", 3);
////	itemListbox->setSelectionBrushImage("MultiListSelectionBrush");
//	listbox->addItem(itemListbox);
//	itemListbox = new CEGUI::ListboxTextItem("Value D", 4);
////	itemListbox->setSelectionBrushImage("MultiListSelectionBrush");
//	listbox->addItem(itemListbox);
//	listbox->setItemSelectState(itemListbox, true);
//	listbox->ensureItemIsVisible(itemListbox);
//	uint valueListbox = listbox->getFirstSelectedItem()->getID(); // Retrieve the ID of the selected listbox item
//	listbox->setPosition(
//		CEGUI::UVector2(CEGUI::UDim(0.5f, 0.0f), CEGUI::UDim(0.5f, 0.0f)));
//	innerWidget->addChild(listbox);
//
//	/* Combobox */
//	CEGUI::Combobox* combobox = static_cast<CEGUI::Combobox*>(wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
//	combobox->setReadOnly(true);
//	CEGUI::ListboxTextItem* itemCombobox = new CEGUI::ListboxTextItem("Value 1",
//		1);
////	itemCombobox->setSelectionBrushImage("MultiListSelectionBrush");
//	combobox->addItem(itemCombobox);
//	itemCombobox = new CEGUI::ListboxTextItem("Value 2", 2);
////	itemCombobox->setSelectionBrushImage("MultiListSelectionBrush");
//	combobox->addItem(itemCombobox);
//	itemCombobox->setSelected(true); // Select this item
//	combobox->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
//	itemCombobox = new CEGUI::ListboxTextItem("Value 3", 3);
////	itemCombobox->setSelectionBrushImage("MultiListSelectionBrush");
//	combobox->addItem(itemCombobox);
//	itemCombobox = new CEGUI::ListboxTextItem("Value 4", 4);
////	itemCombobox->setSelectionBrushImage("MultiListSelectionBrush");
//	combobox->addItem(itemCombobox);
//	CEGUI::String valueCombobox = combobox->getText(); // Retrieve the displayed text
//	uint idCombobox = combobox->getSelectedItem()->getID(); // Retrieve the ID of the selected combobox item
//	combobox->setPosition(
//		CEGUI::UVector2(CEGUI::UDim(0.3f, 0.0f), CEGUI::UDim(0.7f, 0.0f)));
//	innerWidget->addChild(combobox);
//
//	/* MultiColumnList */
//	CEGUI::MultiColumnList* multiColumnList =
//		static_cast<CEGUI::MultiColumnList*>(wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MultiColumnList"));\
//	multiColumnList->addColumn("Col A", 0, CEGUI::UDim(0.32f, 0));
//	multiColumnList->addColumn("Col B", 1, CEGUI::UDim(0.32f, 0));
//	multiColumnList->addColumn("Col C", 2, CEGUI::UDim(0.32f, 0));
//	multiColumnList->setSelectionMode(CEGUI::MultiColumnList::RowSingle); // MultiColumnList::RowMultiple
//	CEGUI::ListboxTextItem* itemMultiColumnList;
//	multiColumnList->addRow();
//	itemMultiColumnList = new CEGUI::ListboxTextItem("A1", 101);
////	itemMultiColumnList->setSelectionBrushImage("MultiListSelectionBrush");
//	multiColumnList->setItem(itemMultiColumnList, 0, 0); // ColumnID, RowID
//	itemMultiColumnList = new CEGUI::ListboxTextItem("B1", 102);
//	//itemMultiColumnList->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
//	// By commenting the line above a cell does not specify a selection indicator
//	//  selecting that line will show a "gap" in the selection.
//	multiColumnList->setItem(itemMultiColumnList, 1, 0); // ColumnID, RowID
//	itemMultiColumnList = new CEGUI::ListboxTextItem("C1", 103);
////	itemMultiColumnList->setSelectionBrushImage("MultiListSelectionBrush");
//	multiColumnList->setItem(itemMultiColumnList, 2, 0); // ColumnID, RowID
//	multiColumnList->addRow();
//	itemMultiColumnList = new CEGUI::ListboxTextItem("A2", 201);
////	itemMultiColumnList->setSelectionBrushImage("MultiListSelectionBrush");
//	multiColumnList->setItem(itemMultiColumnList, 0, 1); // ColumnID, RowID
//	itemMultiColumnList = new CEGUI::ListboxTextItem("B2", 202);
////	itemMultiColumnList->setSelectionBrushImage("MultiListSelectionBrush");
//	multiColumnList->setItem(itemMultiColumnList, 1, 1); // ColumnID, RowID
//	itemMultiColumnList = new CEGUI::ListboxTextItem("C2", 203);
////	itemMultiColumnList->setSelectionBrushImage("MultiListSelectionBrush");
//	multiColumnList->setItem(itemMultiColumnList, 2, 1); // ColumnID, RowID
//	CEGUI::MCLGridRef grid_ref(1, 0); // Select according to a grid reference; second row
//	multiColumnList->setItemSelectState(grid_ref, true);
//	CEGUI::ListboxItem* listboxItem = multiColumnList->getFirstSelectedItem();
//	uint valueColumnA = listboxItem->getID(); // Retrieve the value of the selected item from column A
//	listboxItem = multiColumnList->getNextSelected(listboxItem);
//	uint valueColumnB = listboxItem->getID(); // Retrieve the value of the selected item from column B
//	listboxItem = multiColumnList->getNextSelected(listboxItem);
//	uint valueColumnC = listboxItem->getID(); // Retrieve the value of the selected item from column C
//	innerWidget->addChild(multiColumnList);
//
//	/* TabControl */
//	CEGUI::TabControl* winTabControl =
//		static_cast<CEGUI::TabControl*>(wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/TabControl"));
//	winTabControl->setTabHeight(CEGUI::UDim(0.15f, 0.0f)); // Make the tab buttons a little bigger
//	CEGUI::Window* tabPage = wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/Group", "TabPane1");
//	tabPage->setText("Page 1");
//	tabPage->setSize(
//		CEGUI::USize(CEGUI::UDim(1.0f, 0.0f), CEGUI::UDim(1.0f, 0.0f))); // Size to 100% of its parent, the TabControl
//	tabPage->setPosition(
//		CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(0.0f, 0.0f))); // Move to the upper left corner of its parent
//	winTabControl->addTab(tabPage);
//	tabPage = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/Group",
//		"TabPane2");
//	tabPage->setText("Page 2");
//	tabPage->setSize(
//		CEGUI::USize(CEGUI::UDim(1.0f, 0.0f), CEGUI::UDim(1.0f, 0.0f)));
//	tabPage->setPosition(
//		CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(0.0f, 0.0f)));
//	winTabControl->addTab(tabPage);
//	innerWidget->addChild(winTabControl);
}

ShowCasePanel::~ShowCasePanel(void) {
}
