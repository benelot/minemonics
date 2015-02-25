/*
 * MathGLObject.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: leviathan
 */

#include "MathGLObject.h"

#include <CEGUI/System.h>
#include <CEGUI/Window.h>
#include <CEGUI/Image.h>
#include <CEGUI/RendererModules/Ogre/Texture.h>
#include <stdio.h>

#include "SimulationManager.h"

//This include seems to be problematic, as it carries over errors to other external libraries
//At this position it somehow does not.
#include <mgl2/mgl.h>

MathGLObject::MathGLObject(SimulationManager* simulationMgr, int textureWidth,
		int textureHeight):mTime(0) {

	mSimulationMgr = simulationMgr;

	CEGUI::Sizef size(static_cast<float>(textureWidth), static_cast<float>(textureHeight));

	// We create a CEGUI texture target and create a GUIContext that will use it.
	renderTextureTarget =
			mSimulationMgr->getRenderer()->createTextureTarget();
	renderTextureTarget->declareRenderSize(size);
	renderGuiContext = &mSimulationMgr->getCEGUISystem()->createGUIContext(static_cast<CEGUI::RenderTarget&>(*renderTextureTarget) );

	mTexture = mSimulationMgr->getRoot()->getTextureManager()->createManual(
			"RTT", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Ogre::TEX_TYPE_2D, 512, 512, 0, Ogre::PF_R8G8B8,
			Ogre::TU_RENDERTARGET);

//TODO: Delete if mathgl rendering works
//	  // Create the texture
//	   mTexture = Ogre::TextureManager::getSingleton().createManual("DynamicTexture",
//	      Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
//	      Ogre::TEX_TYPE_2D,
//	      256, 256,
//	      0,
//	      Ogre::PF_BYTE_BGRA,
//	      Ogre::TU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

	Ogre::RenderTexture *rtex = mTexture->getBuffer()->getRenderTarget();

	// We create a CEGUI Texture using the renderer you use:
	CEGUI::Texture& texture = simulationMgr->getRenderer()->createTexture(
			"MathGLTexture", mTexture);

	// Now we need to cast it to the CEGUI::Texture superclass which matches your Renderer. This can be CEGUI::OgreTexture or CEGUI::OpenGLTexture, depending on the renderer you use in your application
	// We will use Ogre here as an example
	CEGUI::OgreTexture& rendererTexture =
			static_cast<CEGUI::OgreTexture&>(texture);

	rendererTexture.setOgreTexture(mTexture, false);

	// We create a BasicImage and set the Texture
	CEGUI::BasicImage* image =
			static_cast<CEGUI::BasicImage*>(&CEGUI::ImageManager::getSingleton().create(
					"BasicImage","RTTImage"));
	image->setTexture(static_cast<CEGUI::Texture*>(&rendererTexture));

	CEGUI::Rectf imageArea;

	//Flipping is necessary due to differences between renderers regarding top or bottom being the origin
	if (renderTextureTarget->isRenderingInverted())
		imageArea = CEGUI::Rectf(0.0f, textureHeight, textureWidth, 0.0f);
	else
		imageArea = CEGUI::Rectf(0.0f, 0.0f, textureWidth, textureHeight);

	image->setArea(imageArea);
	image->setAutoScaled(CEGUI::ASM_Disabled);

//	// add the image to the image manager
//	CEGUI::ImageManager::getSingleton().addImageType<CEGUI::BasicImage>(
//			"RTTImageset");
//	CEGUI::ImageManager::getSingleton().create("RTTImageset", "RTTImage");

	mMathGLWindow = CEGUI::WindowManager::getSingleton().createWindow(
			"Ogremonics/StaticImage", "RTTWindow");
	mMathGLWindow->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0), CEGUI::UDim(0.4f, 0)));
	mMathGLWindow->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.5f, 0), CEGUI::UDim(0.0f, 0)));

	mMathGLWindow->setProperty("Image", "RTTImage");

	// Get the pixel buffer
	Ogre::HardwarePixelBufferSharedPtr pixelBuffer = mTexture->getBuffer();

	// Lock the pixel buffer and get a pixel box
	pixelBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
	const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();

	Ogre::uint8* pDest = static_cast<Ogre::uint8*>(pixelBox.data);

	// Fill in some pixel data. This will give a semi-transparent blue,
	// but this is of course dependent on the chosen pixel format.
	for (size_t j = 0; j < mTexture->getWidth(); j++)
		for (size_t i = 0; i < mTexture->getHeight(); i++) {
			*pDest++ = 255; // B
			*pDest++ = 0; // G
			*pDest++ = 0; // R
			*pDest++ = 127; // A
		}

	// Unlock the pixel buffer
	pixelBuffer->unlock();
}

MathGLObject::~MathGLObject() {
	// TODO Auto-generated destructor stub
}

void MathGLObject::update(int timeSinceLastFrame) {

	mTime += timeSinceLastFrame;

	// Create chart
	mglGraph graph(0, mTexture->getWidth(), mTexture->getHeight());
	graph.Box();
	char buffer[128];
	int r = sprintf(buffer, "sin(pi*x+%.2f)", mTime);
	buffer[r] = 0;
	graph.FPlot(buffer);

	// Get the pixel buffer
	Ogre::HardwarePixelBufferSharedPtr pixelBuffer = mTexture->getBuffer();

	// Lock the pixel buffer and get a pixel box
	pixelBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
	const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock();

	// Copy chart image to the pixel buffer
	Ogre::uint8* pDest = static_cast<Ogre::uint8*>(pixelBox.data);
	graph.GetBGRN((unsigned char*) pDest,
			4 * mTexture->getWidth() * mTexture->getHeight());

	// Unlock the pixel buffer
	pixelBuffer->unlock();

    CEGUI::Renderer* gui_renderer(mSimulationMgr->getRenderer());
    gui_renderer->beginRendering();

    renderTextureTarget->clear();
    renderGuiContext->draw();

    gui_renderer->endRendering();

	//notify window of the texture to update
	mMathGLWindow->invalidate(); // CEGUI::Window*
}

CEGUI::Window*& MathGLObject::getMathGlWindow() {
	return mMathGLWindow;
}
