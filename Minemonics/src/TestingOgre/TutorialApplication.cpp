/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
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
#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	    Ogre::Entity* entNinja = mSceneMgr->createEntity("Ninja", "ninja.mesh");
	    entNinja->setCastShadows(true);
	    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);

	    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	        plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

	    entGround->setMaterialName("Examples/Rockwall");
	    entGround->setCastShadows(false);

	    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
	    pointLight->setType(Ogre::Light::LT_POINT);
	    pointLight->setPosition(Ogre::Vector3(0, 150, 250));

	    pointLight->setDiffuseColour(1.0, 0.0, 0.0);
	    pointLight->setSpecularColour(1.0, 0.0, 0.0);

	    Ogre::Light* directionalLight = mSceneMgr->createLight("directionalLight");
	    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	    directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, 0));
	    directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));

	    directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 ));

	    Ogre::Light* spotLight = mSceneMgr->createLight("spotLight");
	    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
	    spotLight->setDiffuseColour(0, 0, 1.0);
	    spotLight->setSpecularColour(0, 0, 1.0);

	    spotLight->setDirection(-1, -1, 0);
	    spotLight->setPosition(Ogre::Vector3(300, 300, 0));

	    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
