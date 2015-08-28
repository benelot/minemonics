#ifndef VIEW_VISUALIZATION_CEGUI_ELEMENTS_MENUBAR_HPP_
#define VIEW_VISUALIZATION_CEGUI_ELEMENTS_MENUBAR_HPP_

//# corresponding headers
//# forward declarations
namespace CEGUI {
class Window;
} /* namespace CEGUI */

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
 * @brief		The menu bar of the simulator.
 * @details		Details
 * @date		2015-08-28
 * @author		Benjamin Ellenberger
 */
class MenuBar {
public:
	MenuBar();
	virtual ~MenuBar();

	//Accessor methods
	CEGUI::Window*& getWindow() {
		return mMenuBar;
	}

private:
	CEGUI::Window* mMenuBar;
};

#endif /* VIEW_VISUALIZATION_CEGUI_ELEMENTS_MENUBAR_HPP_ */
