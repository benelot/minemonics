/*
 * MathGLWindow.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <string>
#include <boost/lexical_cast.hpp>

//## controller headers
//## model headers
//## view headers
#include <Ogre.h>
#include <CEGUI/System.h>
#include <CEGUI/Window.h>
#include <CEGUI/Image.h>
#include <CEGUI/RendererModules/Ogre/Texture.h>

#include <mgl2/mgl.h>
#include <SimulationManager.hpp>
#include <view/visualization/MathGL/MathGLWindow.hpp>

//# custom headers
//## base headers

//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

MathGLWindow::MathGLWindow(SimulationManager* simulationMgr, int textureWidth,
		int textureHeight, CEGUI::USize windowSize,CEGUI::USize windowPosition) :
		mSimulationMgr(simulationMgr),mTime(0),mMakePrint(false) {

	CEGUI::Sizef size(static_cast<float>(textureWidth),
			static_cast<float>(textureHeight));

	// We create a CEGUI texture target and create a GUIContext that will use it.
	mRenderTextureTarget = mSimulationMgr->getRenderer()->createTextureTarget();
	mRenderTextureTarget->declareRenderSize(size);
	mRenderGuiContext = &mSimulationMgr->getCEGUISystem()->createGUIContext(
			static_cast<CEGUI::RenderTarget&>(*mRenderTextureTarget));

	mTexture = mSimulationMgr->getRoot()->getTextureManager()->createManual(
			"RTT", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Ogre::TEX_TYPE_2D, textureWidth, textureHeight, 0, Ogre::PF_R8G8B8,
			Ogre::TU_RENDERTARGET);

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
					"BasicImage", "RTTImage"));
	image->setTexture(static_cast<CEGUI::Texture*>(&rendererTexture));

	CEGUI::Rectf imageArea;

	//Flipping is necessary due to differences between renderers regarding top or bottom being the origin
	if (mRenderTextureTarget->isRenderingInverted())
		imageArea = CEGUI::Rectf(0.0f, textureHeight, textureWidth, 0.0f);
	else
		imageArea = CEGUI::Rectf(0.0f, 0.0f, textureWidth, textureHeight);

	image->setArea(imageArea);
	image->setAutoScaled(CEGUI::ASM_Disabled);

	CEGUI::Window* staticImage =
			CEGUI::WindowManager::getSingleton().createWindow(
					"Ogremonics/StaticImage", "MathGLRTTWindow");
	staticImage->setSize(
			CEGUI::USize(CEGUI::UDim(1.0f, 0), CEGUI::UDim(1.0f, 0)));
	staticImage->setProperty("Image", "RTTImage");

	mMathGLWindow =
			CEGUI::WindowManager::getSingleton().createWindow(
					"Ogremonics/FrameWindow", "MathGLWindow");
	mMathGLWindow->setSize(windowSize);
	mMathGLWindow->setPosition(
			CEGUI::UVector2(
					CEGUI::UDim(windowPosition.d_width.d_scale - windowSize.d_width.d_scale / 2.0f, 0),
					CEGUI::UDim(windowPosition.d_height.d_scale - windowSize.d_height.d_scale / 2.0f,
							0)));
	mMathGLWindow->addChild(staticImage);

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

MathGLWindow::~MathGLWindow() {
	mSimulationMgr = NULL;

	delete mMathGLWindow;
	mMathGLWindow = NULL;

	delete mRenderGuiContext;
	mRenderGuiContext = NULL;

	delete mRenderTextureTarget;
	mRenderTextureTarget = NULL;
}

void MathGLWindow::update(double timeSinceLastFrame) {

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

	if(mMakePrint)
	{
		std::string fileName;
		fileName.append("Graph");
		fileName.append(boost::lexical_cast<std::string>(mTime));
		fileName.append(".png");
		graph.WritePNG(fileName.c_str());
		mMakePrint = false;
	}

	CEGUI::Renderer* gui_renderer(mSimulationMgr->getRenderer());
	gui_renderer->beginRendering();

	mRenderTextureTarget->clear();
	mRenderGuiContext->draw();

	gui_renderer->endRendering();

	//notify window of the texture to update

	mMathGLWindow->invalidate(true); // CEGUI::Window*
}

CEGUI::Window*& MathGLWindow::getMathGlWindow() {
	return mMathGLWindow;
}
