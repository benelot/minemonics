/*
 -----------------------------------------------------------------------------
 Filename:    MinemonicsApplication.h
 -----------------------------------------------------------------------------

 based on the source file which is part of the
 ___                 __    __ _ _    _
 /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
 / \_// (_| | | |  __/  \  /\  /| |   <| |
 \___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
 |___/
 Tutorial Framework
 http://www.ogre3d.org/tikiwiki/
 -----------------------------------------------------------------------------
 */
#ifndef __MinemonicsApplication_h_
#define __MinemonicsApplication_h_

class HillsO3D;

#include "BaseApplication.h"

class MinemonicsApplication: public BaseApplication {
private:
	OgreBites::Label* mInfoLabel;
	HillsO3D* mTerrain;
public:
	MinemonicsApplication(void);
	virtual ~MinemonicsApplication(void);

protected:
	virtual void createScene(void);
	virtual void createFrameListener(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};

#endif // #ifndef __MinemonicsApplication_h_
