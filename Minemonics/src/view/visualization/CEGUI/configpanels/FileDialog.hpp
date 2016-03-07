#ifndef VIEW_VISUALIZATION_CEGUI_CONFIGPANELS_FILEDIALOG_HPP_
#define VIEW_VISUALIZATION_CEGUI_CONFIGPANELS_FILEDIALOG_HPP_

//# corresponding headers
#include <view/visualization/CEGUI/MovablePanel.hpp>

//# forward declarations
//# system headers
#include <map>
#include <string>
#include <vector>

//## controller headers
//## model headers
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		An file dialog to select a file on the file system.
 * @details
 * @date		2015-10-05
 * @author		Benjamin Ellenberger
 */
class FileDialog: public MovablePanel {
public:

	static const int MAX_NUMBER_OF_HISTORY_ITEMS = 10;

	FileDialog(const int left, const int top, const std::string name,
		MovablePanel::MovablePanelType type);
	virtual ~FileDialog();

	// Open/close/enable/disable windows and widgets
	void disableDialog(void);
	void enableDialog(void);
	void closeWindow(void);
	void closePromptWindowLoad(void);
	void closePromptWindowSave(void);
	void openPromptWindowLoad(void);
	void openPromptWindowSave(void);

	// Handlers
	bool handleClose(const CEGUI::EventArgs&);
	bool handleCancel(const CEGUI::EventArgs&);
	void okExecute(void);
	bool handleOk(const CEGUI::EventArgs&);
	bool handleBack(const CEGUI::EventArgs&);
	bool handleDriveSelect(const CEGUI::EventArgs&);
	bool handleFilterSelect(const CEGUI::EventArgs&);
	bool handleSingleClickSelect(const CEGUI::EventArgs&);
	bool handleDoubleClickSelect(const CEGUI::EventArgs&);
	bool handlePromptLoadOk(const CEGUI::EventArgs&);
	bool handlePromptSaveOk(const CEGUI::EventArgs&);
	bool handlePromptLoadCancel(const CEGUI::EventArgs&);
	bool handlePromptSaveCancel(const CEGUI::EventArgs&);

	// Other private functions
	bool isFileExisting(const std::string);
	void prefillOutputAndClearInput(void);

	void determineDrives();

	void changeDirectory(std::string directory);

	std::string getWorkingPath(void);
	std::string getCurrentDrive(void);
	int getCurrentFilterElement(void);
	void setCurrentFile(const std::string);
	std::string getCurrentFile(void);
	void addFileNameToHistory(const std::string);
	void adjustPathOfSelectedDrive(const std::string);
	void fillListbox(void);
	void fillDrivesbox(void);

	virtual void openFile(std::string filePath) = 0;

	//==========================================================================
	// Sort paths alphabetically (folders first, files last)
	//==========================================================================
	static bool sortFunction(std::string p1,
		std::string p2) {
		bool d1 = is_directory(boost::filesystem::path(p1));
		bool d2 = is_directory(boost::filesystem::path(p2));

		if ((d1 && d2) || (!d1 && !d2))
			return (boost::filesystem::path(p1).filename() < boost::filesystem::path(p2).filename());
		else if (d1)
			return true;
		else if (d2)
			return false;

		return false;
	}

	const std::string& getSelectedFile() const {
		return mSelectedFile;
	}

protected:
	// Widgets
	CEGUI::PushButton* mBackButton;        // Back button
	CEGUI::PushButton* mOkButton;        // Ok button
	CEGUI::PushButton* mCancelButton;    // Cancel button
	CEGUI::Window* mFileLabel;
	CEGUI::Combobox* mFileCb; // Combobox, containing the file to be loaded or
	// saved, including the history of the last
	// loaded/saved filenames
	CEGUI::Combobox* mDrivesCb;      // Combobox, containing all active drives

	CEGUI::Window* mExtensionsLabel;
	CEGUI::Combobox* mExtensionsCb; // Combobox, that contains the filter elements (extensions)
	CEGUI::Listbox* mFilesLb; // Listbox, that represents the files and (sub)directories
	// of the current path
	CEGUI::FrameWindow* mWindowPromptLoad; // Prompt window, displayed in case file to load doesn't exists

	CEGUI::Window* mStPromptLoad; // Message in the prompt window

	CEGUI::PushButton* mPromptLoadOkButton;        // Ok button
	CEGUI::PushButton* mPromptLoadCancelButton;    // Cancel button

	CEGUI::FrameWindow* mWindowPromptSave; // Prompt window, displayed in case file to save already exists

	CEGUI::Window* mStPromptSave; // Message in the prompt window

	CEGUI::PushButton* mPromptSaveOkButton;        // Ok button
	CEGUI::PushButton* mPromptSaveCancelButton;    // Cancel button

	std::vector<std::string> mDrives;
	std::vector<std::string> mNames; // Vector containing all names
	std::map<std::string, std::string> mPathMap;
	std::string mCurrentPath; // the current path
	std::string mSelectedFile;

	MovablePanelType mType;

	bool mDialogShown;

private:
	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>(
					"FileDialog"));
		}
	} _initializer;
};

#endif /* VIEW_VISUALIZATION_CEGUI_CONFIGPANELS_FILEDIALOG_HPP_ */
