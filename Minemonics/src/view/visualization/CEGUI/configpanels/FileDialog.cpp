//# corresponding headers
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <iterator>

//## controller headers
//## model headers
#include <boost/iterator/iterator_facade.hpp>

//## view headers
#include <CEGUI/Element.h>
#include <CEGUI/Event.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/Size.h>
#include <CEGUI/String.h>
#include <CEGUI/SubscriberSlot.h>
#include <CEGUI/UDim.h>
#include <CEGUI/Vector.h>
#include <CEGUI/widgets/Combobox.h>
#include <CEGUI/widgets/FrameWindow.h>
#include <CEGUI/widgets/Listbox.h>
#include <CEGUI/widgets/ListboxItem.h>
#include <CEGUI/widgets/ListboxTextItem.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>

//# custom headers
//## base headers
//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>
#include <configuration/GUIConfiguration.hpp>
#include <view/visualization/CEGUI/configpanels/FileDialog.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers

FileDialog::FileDialog(const int left, const int top, const std::string name,
	MovablePanel::MovablePanelType type) :
	MovablePanel(name, type), mDialogShown(false) {

	mType = type;

	int width = 600;
	int height = 600;

	MovablePanel::initialize(left, top, width, height, false);

	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	// Load the window layout, initialize the widget attributes and subscribe to events
	{
		// back button
		mBackButton = static_cast<CEGUI::PushButton*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Button"));
		mBackButton->setText("Back");
		mBackButton->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.7f, 0), CEGUI::UDim(0.07f, 0)));
		mBackButton->setSize(
			CEGUI::USize(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.05f, 0)));
		mBaseWidget->addChild(mBackButton);

	}

	{
		// ok button
		mOkButton = static_cast<CEGUI::PushButton*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Button"));
		mOkButton->setText("Ok");
		mOkButton->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.75f, 0), CEGUI::UDim(0.85f, 0)));
		mOkButton->setSize(
			CEGUI::USize(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.05f, 0)));
		mBaseWidget->addChild(mOkButton);
	}

	{
		// cancel button
		mCancelButton = static_cast<CEGUI::PushButton*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Button"));
		mCancelButton->setText("Cancel");
		mCancelButton->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.75f, 0), CEGUI::UDim(0.9f, 0)));
		mCancelButton->setSize(
			CEGUI::USize(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.05f, 0)));
		mBaseWidget->addChild(mCancelButton);
	}

	{
		//extensions label
		mFileLabel = static_cast<CEGUI::Window*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label"));
		mFileLabel->setText("File: ");
		mFileLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.05f, 0), CEGUI::UDim(0.85f, 0)));
		mFileLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.06f, 0)));
		mBaseWidget->addChild(mFileLabel);
	}

	{
		// file combobox
		mFileCb = static_cast<CEGUI::Combobox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
		mFileCb->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.25f, 0), CEGUI::UDim(0.85f, 0)));
		mFileCb->setSize(
			CEGUI::USize(CEGUI::UDim(0.5f, 0), CEGUI::UDim(0.5f, 0)));
		mBaseWidget->addChild(mFileCb);
	}

	{
		// drives combobox
		mDrivesCb = static_cast<CEGUI::Combobox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
		mDrivesCb->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.05f, 0), CEGUI::UDim(0.07f, 0)));
		mDrivesCb->setSize(
			CEGUI::USize(CEGUI::UDim(0.6f, 0), CEGUI::UDim(0.5f, 0)));
		mBaseWidget->addChild(mDrivesCb);
	}

	{
		//extensions label
		mExtensionsLabel = static_cast<CEGUI::Window*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label"));
		mExtensionsLabel->setText("Extension: ");
		mExtensionsLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.05f, 0), CEGUI::UDim(0.9f, 0)));
		mExtensionsLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.06f, 0)));
		mBaseWidget->addChild(mExtensionsLabel);
	}

	{
		// extensions combobox
		mExtensionsCb = static_cast<CEGUI::Combobox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
		mExtensionsCb->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.25f, 0), CEGUI::UDim(0.9f, 0)));
		mExtensionsCb->setSize(
			CEGUI::USize(CEGUI::UDim(0.5f, 0), CEGUI::UDim(0.5f, 0)));
		mBaseWidget->addChild(mExtensionsCb);
	}

	{
		// files listbox
		mFilesLb = static_cast<CEGUI::Listbox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Listbox"));
		mFilesLb->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.05f, 0), CEGUI::UDim(0.13f, 0)));
		mFilesLb->setSize(
			CEGUI::USize(CEGUI::UDim(0.9f, 0), CEGUI::UDim(0.7f, 0)));
		mBaseWidget->addChild(mFilesLb);
	}

	{
		// window-prompt loading
		mWindowPromptLoad = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/FrameWindow"));
		mWindowPromptLoad->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.3f, 0)));
		mWindowPromptLoad->setSize(
			CEGUI::USize(CEGUI::UDim(0.6f, 0), CEGUI::UDim(0.4f, 0)));
	}

	{
		//static prompt load
		mStPromptLoad = static_cast<CEGUI::Window*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label"));
		mStPromptLoad->setText(GUIConfiguration::OpenFileLoadConfirm);
		mStPromptLoad->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.05f, 0), CEGUI::UDim(0.2f, 0)));
		mStPromptLoad->setSize(
			CEGUI::USize(CEGUI::UDim(0.9f, 0), CEGUI::UDim(0.1f, 0)));
		mWindowPromptLoad->addChild(mStPromptLoad);
	}

	{
		// loading window ok button
		mPromptLoadOkButton = static_cast<CEGUI::PushButton*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Button"));
		mPromptLoadOkButton->setText("Yes");
		mPromptLoadOkButton->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.8f, 0)));
		mPromptLoadOkButton->setSize(
			CEGUI::USize(CEGUI::UDim(0.25f, 0), CEGUI::UDim(0.1f, 0)));
		mWindowPromptLoad->addChild(mPromptLoadOkButton);
	}

	{
		// load window cancel button
		mPromptLoadCancelButton =
			static_cast<CEGUI::PushButton*>(wmgr.createWindow(
				CEGUIConfiguration::CEGUI_SCHEME + "/Button"));
		mPromptLoadCancelButton->setText("No");
		mPromptLoadCancelButton->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.55f, 0), CEGUI::UDim(0.8f, 0)));
		mPromptLoadCancelButton->setSize(
			CEGUI::USize(CEGUI::UDim(0.25f, 0), CEGUI::UDim(0.1f, 0)));
		mWindowPromptLoad->addChild(mPromptLoadCancelButton);
	}

	{
		// window-prompt saving
		mWindowPromptSave = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/FrameWindow"));
		mWindowPromptSave->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.3f, 0)));
		mWindowPromptSave->setSize(
			CEGUI::USize(CEGUI::UDim(0.6f, 0), CEGUI::UDim(0.4f, 0)));
	}

	{
		//static prompt save
		mStPromptSave = static_cast<CEGUI::Window*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label"));
		mStPromptSave->setText(GUIConfiguration::OpenFileSaveConfirm);
		mStPromptSave->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.05f, 0), CEGUI::UDim(0.2f, 0)));
		mStPromptSave->setSize(
			CEGUI::USize(CEGUI::UDim(0.9f, 0), CEGUI::UDim(0.1f, 0)));
		mWindowPromptSave->addChild(mStPromptSave);
	}

	{
		// saving window ok button
		mPromptSaveOkButton = static_cast<CEGUI::PushButton*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Button"));
		mPromptSaveOkButton->setText("Yes");
		mPromptSaveOkButton->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.8f, 0)));
		mPromptSaveOkButton->setSize(
			CEGUI::USize(CEGUI::UDim(0.25f, 0), CEGUI::UDim(0.1f, 0)));
		mWindowPromptSave->addChild(mPromptSaveOkButton);
	}

	{
		// save window cancel button
		mPromptSaveCancelButton =
			static_cast<CEGUI::PushButton*>(wmgr.createWindow(
				CEGUIConfiguration::CEGUI_SCHEME + "/Button"));
		mPromptSaveCancelButton->setText("No");
		mPromptSaveCancelButton->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.55f, 0), CEGUI::UDim(0.8f, 0)));
		mPromptSaveCancelButton->setSize(
			CEGUI::USize(CEGUI::UDim(0.25f, 0), CEGUI::UDim(0.1f, 0)));
		mWindowPromptSave->addChild(mPromptSaveCancelButton);
	}

	if (mBackButton) {
		mBackButton->setText("^"); // Must set it here, otherwise the xml parser gets confused
		mBackButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FileDialog::handleBack, this));
	}

	if (mCancelButton)
		mCancelButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FileDialog::handleCancel, this));

	if (mOkButton)
		mOkButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FileDialog::handleOk, this));

	if (mExtensionsCb) {
		mExtensionsCb->subscribeEvent(
			CEGUI::Combobox::EventListSelectionAccepted,
			CEGUI::Event::Subscriber(&FileDialog::handleFilterSelect, this));
		CEGUI::ListboxTextItem* itemCombobox = new CEGUI::ListboxTextItem(
			" All (*)", 0);
		mExtensionsCb->addItem(itemCombobox);
		mExtensionsCb->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
		mExtensionsCb->setItemSelectState(itemCombobox, true);
	}

	if (mDrivesCb) {
		mDrivesCb->subscribeEvent(CEGUI::Combobox::EventListSelectionAccepted,
			CEGUI::Event::Subscriber(&FileDialog::handleDriveSelect, this));
	}

	if (mFilesLb) {
		mFilesLb->setSortingEnabled(true);
		mFilesLb->subscribeEvent(CEGUI::Listbox::EventMouseClick,
			CEGUI::Event::Subscriber(&FileDialog::handleSingleClickSelect,
				this));
		mFilesLb->subscribeEvent(CEGUI::Listbox::EventMouseDoubleClick,
			CEGUI::Event::Subscriber(&FileDialog::handleDoubleClickSelect,
				this));
		mFilesLb->setSortingEnabled(false);
	}

	if (mWindowPromptLoad) {
		mBaseWidget->getParent()->addChild(mWindowPromptLoad);
		mWindowPromptLoad->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber(&FileDialog::handlePromptLoadCancel,
				this));
		mWindowPromptLoad->disable();
		mWindowPromptLoad->hide();
	}

	if (mPromptLoadOkButton) {
		mPromptLoadOkButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FileDialog::handleOk, this));
	}

	if (mPromptLoadCancelButton) {
		mPromptLoadCancelButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FileDialog::handlePromptLoadCancel,
				this));
	}

	if (mWindowPromptSave) {
		mBaseWidget->getParent()->addChild(mWindowPromptSave);
		mWindowPromptSave->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber(&FileDialog::handlePromptSaveCancel,
				this));
		mWindowPromptSave->disable();
		mWindowPromptSave->hide();
	}

	if (mPromptSaveOkButton) {
		mPromptSaveOkButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FileDialog::handleOk, this));
	}

	if (mPromptSaveCancelButton) {
		mPromptSaveCancelButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FileDialog::handlePromptSaveCancel,
				this));
	}

	// change to this directory
	changeDirectory(".");
	determineDrives();
	fillDrivesbox();
}

FileDialog::~FileDialog() {

	// According to:
	//http://cegui.org.uk/forum/viewtopic.php?t=1535
	// All chilrden of base widget are deleted as well
//	if (mBackButton) {
//		delete mBackButton;
//	}
//	mBackButton = NULL;
//
//	if (mOkButton) {
//		delete mOkButton;
//	}
//	mOkButton = NULL;
//
//	if (mCancelButton) {
//		delete mCancelButton;
//	}
//	mCancelButton = NULL;
//
//	if (mFileLabel) {
//		delete mFileLabel;
//	}
//	mFileLabel = NULL;
//
//	if (mFileCb) {
//		delete mFileCb;
//	}
//	mFileCb = NULL;
//
//	if (mDrivesCb) {
//		delete mDrivesCb;
//	}
//	mDrivesCb = NULL;
//
//	if (mExtensionsLabel) {
//		delete mExtensionsLabel;
//	}
//	mExtensionsLabel = NULL;
//
//	if (mFilesLb) {
//		delete mFilesLb;
//	}
//	mFilesLb = NULL;
//
//	if (mWindowPromptLoad) {
//		delete mWindowPromptLoad;
//	}
//	mWindowPromptLoad = NULL;
//
//	if (mStPromptLoad) {
//		delete mStPromptLoad;
//	}
//	mStPromptLoad = NULL;
//
//	if (mPromptLoadOkButton) {
//		delete mPromptLoadOkButton;
//	}
//	mPromptLoadOkButton = NULL;
//
//	if (mPromptLoadCancelButton) {
//		delete mPromptLoadCancelButton;
//	}
//	mPromptLoadCancelButton = NULL;
//
//	if (mWindowPromptSave) {
//		delete mWindowPromptSave;
//	}
//	mWindowPromptSave = NULL;
//
//	if (mStPromptSave) {
//		delete mStPromptSave;
//	}
//	mStPromptSave = NULL;
//
//	if (mPromptSaveOkButton) {
//		delete mPromptSaveOkButton;
//	}
//	mPromptSaveOkButton = NULL;
//
//	if (mPromptSaveCancelButton) {
//		delete mPromptSaveCancelButton;
//	}
//	mPromptSaveCancelButton = NULL;
}

void FileDialog::disableDialog(void) {
	if (mBackButton)
		mBackButton->disable();
	if (mOkButton)
		mOkButton->disable();
	if (mCancelButton)
		mCancelButton->disable();
	if (mFileCb)
		mFileCb->disable();
	if (mDrivesCb)
		mDrivesCb->disable();
	if (mExtensionsCb)
		mExtensionsCb->disable();
	if (mFilesLb)
		mFilesLb->disable();
}

void FileDialog::enableDialog(void) {
	if (mBackButton)
		mBackButton->enable();
	if (mOkButton)
		mOkButton->enable();
	if (mCancelButton)
		mCancelButton->enable();
	if (mFileCb)
		mFileCb->enable();
	if (mDrivesCb)
		mDrivesCb->enable();
	if (mExtensionsCb)
		mExtensionsCb->enable();
	if (mFilesLb)
		mFilesLb->enable();
}

void FileDialog::closeWindow(void) {
	close();

	closePromptWindowLoad();
	closePromptWindowSave();
}

void FileDialog::closePromptWindowLoad(void) {
	if (mWindowPromptLoad) {
		mWindowPromptLoad->disable();
		mWindowPromptLoad->hide();
	}
	enableDialog();
}

void FileDialog::closePromptWindowSave(void) {
	if (mWindowPromptSave) {
		mWindowPromptSave->disable();
		mWindowPromptSave->hide();
	}
	enableDialog();
}

void FileDialog::openPromptWindowLoad(void) {
	if (mWindowPromptLoad) {
		disableDialog();
		mWindowPromptLoad->show();
		mWindowPromptLoad->enable();
	}
}

void FileDialog::openPromptWindowSave(void) {
	if (mWindowPromptSave) {
		disableDialog();
		mWindowPromptSave->show();
		mWindowPromptSave->enable();
	}
}

bool FileDialog::handleClose(const CEGUI::EventArgs&) {
	prefillOutputAndClearInput();
	closeWindow();
	return true;
}

bool FileDialog::handleCancel(const CEGUI::EventArgs&) {
	prefillOutputAndClearInput();
	closeWindow();
}

void FileDialog::okExecute(void) {
	prefillOutputAndClearInput();

	// Add the filename to the combobox (= history)
	addFileNameToHistory(getCurrentFile());

	closeWindow();
	openFile(mSelectedFile);
}

bool FileDialog::handleOk(const CEGUI::EventArgs&) {

	switch (mType) {
	case MovablePanel::LOAD_PANEL:
		if (!mDialogShown && isFileExisting(getCurrentFile())) {
			openPromptWindowLoad();
			mDialogShown = true;
			return true;
		}
		break;
	case MovablePanel::SAVE_PANEL:
		if (!mDialogShown && isFileExisting(getCurrentFile())) {
			openPromptWindowSave();
			mDialogShown = true;
			return true;
		}
		break;
	}

	okExecute();
	return true;
}

bool FileDialog::handleBack(const CEGUI::EventArgs&) {
	changeDirectory(mCurrentPath + "/..");
}

bool FileDialog::handleDriveSelect(const CEGUI::EventArgs&) {
	changeDirectory(getCurrentDrive());
}

bool FileDialog::handleFilterSelect(const CEGUI::EventArgs&) {
	changeDirectory(mCurrentPath);
	return true;
}

bool FileDialog::handleSingleClickSelect(const CEGUI::EventArgs&) {
	if (mFilesLb) {
		CEGUI::ListboxTextItem* item =
			static_cast<CEGUI::ListboxTextItem*>(mFilesLb->getFirstSelectedItem());
		if (item) {
			// Return if a directory is selected
			if (item->getText().length() > 0) {
				if (mPathMap.find(item->getText().c_str()) != mPathMap.end()
					&& boost::filesystem::is_regular_file(
						boost::filesystem::path(
							(*mPathMap.find(item->getText().c_str())).second))) {
					if (mFileCb) {
						mFileCb->setText(item->getText());
						mSelectedFile =
							(*mPathMap.find(item->getText().c_str())).second;
					}
				}

			}
		}
	}
	return true;
}

bool FileDialog::handleDoubleClickSelect(const CEGUI::EventArgs&) {
	if (mFilesLb) {
		CEGUI::ListboxTextItem* item =
			static_cast<CEGUI::ListboxTextItem*>(mFilesLb->getFirstSelectedItem());
		if (item) {
			// Return if no directory is selected
			if (item->getText().length() > 0) {
				if (mPathMap.find(item->getText().c_str()) != mPathMap.end()) {
					if (boost::filesystem::is_directory(
						boost::filesystem::path(
							mPathMap.find(item->getText().c_str())->second))) {
						// Determine new directory
						changeDirectory(
							mPathMap.find(item->getText().c_str())->second);
						fillListbox();
					} else if (boost::filesystem::is_regular_file(
						boost::filesystem::path(
							mPathMap.find(item->getText().c_str())->second))) {
						if (mFileCb) {
							mFileCb->setText(item->getText());
							mSelectedFile = (*mPathMap.find(
								item->getText().c_str())).second;
						}
						handleOk(CEGUI::EventArgs());
					}
				}

			}
		}
	}
	return true;
}

bool FileDialog::handlePromptLoadOk(const CEGUI::EventArgs&) {
	closePromptWindowLoad();
	return true;
}

bool FileDialog::handlePromptSaveOk(const CEGUI::EventArgs&) {
	closePromptWindowLoad();
	return true;
}

bool FileDialog::handlePromptLoadCancel(const CEGUI::EventArgs&) {
	closePromptWindowLoad();
	mDialogShown = false;
	return true;
}

bool FileDialog::handlePromptSaveCancel(const CEGUI::EventArgs&) {
	closePromptWindowSave();
	mDialogShown = false;
	return true;
}

bool FileDialog::isFileExisting(const std::string file) {
	return boost::filesystem::exists(boost::filesystem::path(file));
}

void FileDialog::prefillOutputAndClearInput(void) {
	mFileCb->setText("");
}

void FileDialog::determineDrives() {
	mDrives.clear();

//Linux
// root directory
	std::string linuxRoot = "/";
	if (boost::filesystem::exists(boost::filesystem::path(linuxRoot))) {
		mDrives.push_back(linuxRoot);
	}

	// home directory
	std::string linuxHome = "/home";
	if (boost::filesystem::exists(boost::filesystem::path(linuxHome))) {
		mDrives.push_back(linuxHome);
	}

// media directory
	std::string linuxMedia = "/media";
	if (boost::filesystem::exists(boost::filesystem::path(linuxMedia))) {
		mDrives.push_back(linuxMedia);
	}

//Windows
	for (char letter = 'A'; letter != 'Z'; letter++) {
		std::string path = std::string("" + letter) + ':';
		if (boost::filesystem::exists(boost::filesystem::path(path))) {
			mDrives.push_back(linuxMedia);
		}
	}
}
void FileDialog::changeDirectory(std::string path) {

	mCurrentPath =
		boost::filesystem::absolute(boost::filesystem::path(path)).c_str();

	mNames.clear();

//	mNames.push_back("\[..]");

	std::vector<std::string> tempPaths;

	try {
		for (boost::filesystem::directory_iterator it(mCurrentPath);
			it != boost::filesystem::directory_iterator(); ++it) {
			tempPaths.push_back(it->path().c_str());
		}
	} catch (const boost::filesystem::filesystem_error& ex) {
		// the user probably backed up too far. Jackass.
		mCurrentPath =
			boost::filesystem::path(mCurrentPath).parent_path().c_str();
		for (boost::filesystem::directory_iterator it(mCurrentPath);
			it != boost::filesystem::directory_iterator(); ++it) {
			tempPaths.push_back(it->path().c_str());
		}
	}

	// some shitty OSs don't sort paths..
	std::sort(tempPaths.begin(), tempPaths.end(), sortFunction);

	for (size_t i = 0; i < tempPaths.size(); i++) {
		// folder
		if (boost::filesystem::is_directory(tempPaths[i])) {
			std::string folderName = std::string("\\[")
				+ std::string(
					boost::filesystem::path(tempPaths[i]).filename().c_str())
				+ "\\]";
			mPathMap.insert(std::make_pair(folderName, tempPaths[i]));
			mNames.push_back(folderName);
		}

		// file
		else {
			// filter to extension (if any)
			if (mExtensionsCb->getSelectedItem()->getID() != 0) {
				// extension
				std::string ext =
					mExtensionsCb->getSelectedItem()->getText().c_str();
				if (boost::filesystem::path(tempPaths[i]).extension() == ext) {
					std::string fileName =
						boost::filesystem::path(tempPaths[i]).filename().c_str();
					mNames.push_back(fileName);
					mPathMap.insert(std::make_pair(fileName, tempPaths[i]));
				}
			} else {
				std::string fileName =
					boost::filesystem::path(tempPaths[i]).filename().c_str();
				mNames.push_back(fileName);
				mPathMap.insert(std::make_pair(fileName, tempPaths[i]));
			}
		}
	}

	//Update drives combobox
	mDrivesCb->setText(getWorkingPath());

	fillListbox();

}

std::string FileDialog::getWorkingPath(void) {
	return mCurrentPath;
}

std::string FileDialog::getCurrentDrive(void) {
	return mDrivesCb->getSelectedItem()->getText().c_str();
}

int FileDialog::getCurrentFilterElement(void) {
	return mExtensionsCb->getSelectedItem()->getID();
}

void FileDialog::setCurrentFile(const std::string allocator) {
}

std::string FileDialog::getCurrentFile(void) {
	return mSelectedFile;
}

void FileDialog::addFileNameToHistory(const std::string szFileName) {
	mFileCb->insertItem(new CEGUI::ListboxTextItem(szFileName.c_str()), NULL);
	uint uNumberOfItems = mFileCb->getItemCount();
	if (uNumberOfItems > MAX_NUMBER_OF_HISTORY_ITEMS)
		mFileCb->removeItem(mFileCb->getListboxItemFromIndex(--uNumberOfItems));
}

void FileDialog::fillListbox(void) {
	for (int i = mFilesLb->getItemCount() - 1; i >= 0; --i) {
		CEGUI::ListboxItem* lti = mFilesLb->getListboxItemFromIndex(i);
		mFilesLb->removeItem(lti);
	}

	for (std::vector<std::string>::iterator pos = mNames.begin();
		pos != mNames.end(); pos++) {
		mFilesLb->addItem(new CEGUI::ListboxTextItem(*pos));
	}
}

void FileDialog::fillDrivesbox(void) {
	for (int i = mDrivesCb->getItemCount() - 1; i >= 0; --i) {
		CEGUI::ListboxItem* lti = mDrivesCb->getListboxItemFromIndex(i);
		mFilesLb->removeItem(lti);
	}

	for (std::vector<std::string>::iterator pos = mDrives.begin();
		pos != mDrives.end(); pos++) {
		mDrivesCb->addItem(new CEGUI::ListboxTextItem(*pos));
	}
}
