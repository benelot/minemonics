//# corresponding headers
//# forward declarations
//# system headers
#include <cstdio>
#include <string>
#include <stddef.h>

//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>

//## view headers
#include <CEGUI/BasicImage.h>
#include <CEGUI/Element.h>
#include <CEGUI/GUIContext.h>
#include <CEGUI/Image.h>
#include <CEGUI/ImageManager.h>
#include <CEGUI/Rect.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/System.h>
#include <CEGUI/TextureTarget.h>
#include <CEGUI/UDim.h>
#include <CEGUI/Vector.h>
#include <CEGUI/WindowManager.h>
#include <Renderer.h>
#include <Texture.h>
#include <OgreHardwareBuffer.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgrePixelFormat.h>
#include <OgrePlatform.h>
#include <OgreResourceGroupManager.h>
#include <OgreRoot.h>
#include <OgreSharedPtr.h>
#include <OgreTextureManager.h>
#include <mgl2/mgl.h>

//# custom headers
//## base headers
#include <SimulationManager.hpp>
#include <view/visualization/panels/MathGLPanel.hpp>

//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

MathGLPanel::MathGLPanel(ViewController* const viewController,Ogre::Root* const root, const int textureWidth,
		const int textureHeight, const CEGUI::USize windowSize,const CEGUI::USize windowPosition) :
		mViewController(viewController),mTime(0),mMakePrint(false) {

	CEGUI::Sizef size(static_cast<float>(textureWidth),
			static_cast<float>(textureHeight));

	// We create a CEGUI texture target and create a GUIContext that will use it.
	mRenderTextureTarget = mViewController->getRenderer()->createTextureTarget();
	mRenderTextureTarget->declareRenderSize(size);
	mRenderGuiContext = &mViewController->getSystem()->createGUIContext(
			static_cast<CEGUI::RenderTarget&>(*mRenderTextureTarget));

	mTexture = root->getTextureManager()->createManual(
			"RTT", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Ogre::TEX_TYPE_2D, textureWidth, textureHeight, 0, Ogre::PF_R8G8B8,
			Ogre::TU_RENDERTARGET);

	Ogre::RenderTexture *rtex = mTexture->getBuffer()->getRenderTarget();

	// We create a CEGUI Texture using the renderer you use:
	CEGUI::Texture& texture = mViewController->getRenderer()->createTexture(
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

MathGLPanel::~MathGLPanel() {
	mViewController = NULL;

	delete mMathGLWindow;
	mMathGLWindow = NULL;

	delete mRenderGuiContext;
	mRenderGuiContext = NULL;

	delete mRenderTextureTarget;
	mRenderTextureTarget = NULL;
}

void MathGLPanel::update(const double timeSinceLastFrame) {

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

	CEGUI::Renderer* guiRenderer(mViewController->getRenderer());
	guiRenderer->beginRendering();

	mRenderTextureTarget->clear();
	mRenderGuiContext->draw();

	guiRenderer->endRendering();

	//notify window of the texture to update

	mMathGLWindow->invalidate(true); // CEGUI::Window*
}

CEGUI::Window*& MathGLPanel::getMathGlWindow() {
	return mMathGLWindow;
}
