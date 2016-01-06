//# corresponding headers
#include <view/visualization/CEGUI/infopanels/graphpanels/MathGLPanel.hpp>

//## system headers
#include <stddef.h>
#include <cstdio>
#include <string>

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
#include <CEGUI/Size.h>
#include <CEGUI/System.h>
#include <CEGUI/TextureTarget.h>
#include <CEGUI/UDim.h>
#include <CEGUI/widgets/FrameWindow.h>
#include <CEGUI/WindowManager.h>
#include <mgl2/mgl.h>
#include <OgreHardwareBuffer.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgrePixelFormat.h>
#include <OgrePlatform.h>
#include <OgreResourceGroupManager.h>
#include <OgreRoot.h>
#include <OgreSharedPtr.h>
#include <OgreTexture.h>
#include <OgreTextureManager.h>
#include <Renderer.h>
#include <Texture.h>

//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>
#include <configuration/PlotConfiguration.hpp>

//## controller headers
#include <controller/viewcontroller/ViewController.hpp>

//## model headers
//## view headers
//## utils headers

MathGLPanel::MathGLPanel(const std::string name, const int left, const int top,
	const int width, const int height, Ogre::Root* const root,
	const int textureWidth, const int textureHeight) :
	MovablePanel(name, MovablePanel::GRAPHPANEL), mTime(0), mMakePrint(false), mVerticalRotation(
		60), mHorizontalRotation(50), mXLabel("x"), mYLabel("y"), mZLabel("z") {

	std::string uniqueID = boost::lexical_cast<std::string>(this);

	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	CEGUI::Sizef size(static_cast<float>(textureWidth),
		static_cast<float>(textureHeight));

	// We create a CEGUI texture target and create a GUIContext that will use it.
	mRenderTextureTarget =
		SimulationManager::getSingleton()->getViewController().getRenderer()->createTextureTarget();
	mRenderTextureTarget->declareRenderSize(size);
	mRenderGuiContext =
		&SimulationManager::getSingleton()->getViewController().getSystem()->createGUIContext(
			static_cast<CEGUI::RenderTarget&>(*mRenderTextureTarget));

	mTexture = root->getTextureManager()->createManual("RTT",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::TEX_TYPE_2D, textureWidth, textureHeight, 0, Ogre::PF_R8G8B8,
		Ogre::TU_RENDERTARGET);

	Ogre::RenderTexture *rtex = mTexture->getBuffer()->getRenderTarget();

	// We create a CEGUI Texture using the renderer you use:
	CEGUI::Texture& texture =
		SimulationManager::getSingleton()->getViewController().getRenderer()->createTexture(
			"MathGLTexture" + uniqueID, mTexture);

	// Now we need to cast it to the CEGUI::Texture superclass which matches your Renderer. This can be CEGUI::OgreTexture or CEGUI::OpenGLTexture, depending on the renderer you use in your application
	// We will use Ogre here as an example
	CEGUI::OgreTexture& rendererTexture =
		static_cast<CEGUI::OgreTexture&>(texture);

	rendererTexture.setOgreTexture(mTexture, false);

	// We create a BasicImage and set the Texture
	CEGUI::BasicImage* image =
		static_cast<CEGUI::BasicImage*>(&CEGUI::ImageManager::getSingleton().create(
			"BasicImage", "RTTImage" + uniqueID));
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
			CEGUIConfiguration::CEGUI_SCHEME + "/StaticImage");
	staticImage->setSize(
		CEGUI::USize(CEGUI::UDim(0, width - 20), CEGUI::UDim(0, height - 40)));
	staticImage->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0, 10), CEGUI::UDim(0, 20)));
	staticImage->setProperty("Image", "RTTImage" + uniqueID);

	MovablePanel::initialize(left, top, width, height, false);
	mFrameWindow->addChild(staticImage);

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
			*pDest++ = 255; // G
			*pDest++ = 255; // R
			*pDest++ = 127; // A
		}

	// Unlock the pixel buffer
	pixelBuffer->unlock();

	mHorizontalSlider = static_cast<CEGUI::Slider*>(wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/HorizontalSlider"));

	mHorizontalSlider->setSize(
		CEGUI::USize(CEGUI::UDim(0, width), CEGUI::UDim(0, 20)));

	mHorizontalSlider->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0, 0.0f), CEGUI::UDim(0, height - 30)));

	mHorizontalSlider->setMaxValue(360);
	mHorizontalSlider->setClickStep(1.0f);
	mHorizontalSlider->setCurrentValue(mHorizontalRotation);

	mHorizontalSlider->subscribeEvent(CEGUI::Slider::EventValueChanged,
		CEGUI::Event::Subscriber(&MathGLPanel::onHorizontalSliderValueChanged,
			this));

	mFrameWindow->addChild(mHorizontalSlider);

	mVerticalSlider = static_cast<CEGUI::Slider*>(wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/Slider"));

	mVerticalSlider->setSize(
		CEGUI::USize(CEGUI::UDim(0, 20), CEGUI::UDim(0, height - 20)));

	mVerticalSlider->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0, width - 10), CEGUI::UDim(0, 0.0f)));

	mVerticalSlider->setMaxValue(360);
	mVerticalSlider->setClickStep(1.0f);
	mVerticalSlider->setCurrentValue(mVerticalRotation);

	mVerticalSlider->subscribeEvent(CEGUI::Slider::EventValueChanged,
		CEGUI::Event::Subscriber(&MathGLPanel::onVerticalSliderValueChanged,
			this));

	mFrameWindow->addChild(mVerticalSlider);
}

MathGLPanel::~MathGLPanel() {
	delete mRenderGuiContext;
	mRenderGuiContext = NULL;

	delete mRenderTextureTarget;
	mRenderTextureTarget = NULL;
}

void MathGLPanel::onHorizontalSliderValueChanged() {
	mHorizontalRotation = mHorizontalSlider->getCurrentValue();
}

void MathGLPanel::onVerticalSliderValueChanged() {
	mVerticalRotation = mVerticalSlider->getCurrentValue();
}

void MathGLPanel::update(const double timeSinceLastFrame) {

	if (mFrameWindow->isVisible()) {
		mTime += timeSinceLastFrame;

		// Create chart
		mglGraph graph(0, mTexture->getWidth(), mTexture->getHeight());
		graph.Title(mName.c_str());
		graph.Rotate(mVerticalRotation, mHorizontalRotation);

		double minX = 1000000;
		double minY = 1000000;
		double minZ = 1000000;
		double maxX = 0;
		double maxY = 0;
		double maxZ = 0;

		for (std::vector<const MathGLDataset*>::const_iterator mit =
			mDatasets.begin(); mit != mDatasets.end(); mit++) {
			// calculate maxima and minima
			for (int i = 0; i < (*(*mit)->getDatasetX()).nx; i++) {
				minX =
					(minX > (*(*mit)->getDatasetX()).a[i]) ?
						(*(*mit)->getDatasetX()).a[i] : minX;

				maxX =
					(maxX < (*(*mit)->getDatasetX()).a[i]) ?
						(*(*mit)->getDatasetX()).a[i] : maxX;
			}

			for (int i = 0; i < (*(*mit)->getDatasetY()).nx; i++) {
				minY =
					(minY > (*(*mit)->getDatasetY()).a[i]) ?
						(*(*mit)->getDatasetY()).a[i] : minY;

				maxY =
					(maxY < (*(*mit)->getDatasetY()).a[i]) ?
						(*(*mit)->getDatasetY()).a[i] : maxY;
			}

			for (int i = 0; i < (*(*mit)->getDatasetZ()).nx; i++) {
				minZ =
					(minZ > (*(*mit)->getDatasetZ()).a[i]) ?
						(*(*mit)->getDatasetZ()).a[i] : minZ;

				maxZ =
					(maxZ < (*(*mit)->getDatasetZ()).a[i]) ?
						(*(*mit)->getDatasetZ()).a[i] : maxZ;
			}

		}

		// in case there are no data sets
		if (mDatasets.size() == 0) {
			minX = minY = minZ = 0;
			maxX = maxY = maxZ = 1;
		}

		// if max and min are not too far away, move them further apart (this messes with mgl it seems)
		if (maxX - minX < PlotConfiguration::plotMinMaxDistance) {
			maxX += PlotConfiguration::plotMinMaxDistance;
			minX -= PlotConfiguration::plotMinMaxDistance;
		}

		if (maxY - minY < PlotConfiguration::plotMinMaxDistance) {
			maxY += PlotConfiguration::plotMinMaxDistance;
			minY -= PlotConfiguration::plotMinMaxDistance;
		}

		if (maxZ - minZ < PlotConfiguration::plotMinMaxDistance) {
			maxZ += PlotConfiguration::plotMinMaxDistance;
			minZ -= PlotConfiguration::plotMinMaxDistance;
		}

		graph.SetRanges(minX, maxX, minY, maxY, minZ, maxZ);
		for (std::vector<const MathGLDataset*>::const_iterator mit =
			mDatasets.begin(); mit != mDatasets.end(); mit++) {
			graph.SetColor('o', (*mit)->getPlotColor().r,
				(*mit)->getPlotColor().g, (*mit)->getPlotColor().b);
			graph.Plot((*(*mit)->getDatasetX()), (*(*mit)->getDatasetY()),
				(*(*mit)->getDatasetZ()), "VA-");
		}

		graph.Label('x', mXLabel.c_str(), 0);
		graph.Label('y', mYLabel.c_str(), 0);
		graph.Label('z', mZLabel.c_str(), 0);
		graph.Box();
		graph.Axis();

		Ogre::HardwarePixelBufferSharedPtr pixelBuffer = mTexture->getBuffer(); // Get the pixel buffer

		pixelBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
		const Ogre::PixelBox& pixelBox = pixelBuffer->getCurrentLock(); // Lock the pixel buffer and get a pixel box

		Ogre::uint8* pDest = static_cast<Ogre::uint8*>(pixelBox.data);
		graph.GetBGRN((unsigned char*) pDest,
			4 * mTexture->getWidth() * mTexture->getHeight()); // Copy chart image to the pixel buffer

		pixelBuffer->unlock(); // Unlock the pixel buffer

		if (mMakePrint) {
			std::string fileName;
			fileName.append("Graph");
			fileName.append(boost::lexical_cast<std::string>(mTime));
			fileName.append(".png");
			graph.WritePNG(fileName.c_str());
			mMakePrint = false;
		}

		CEGUI::Renderer* guiRenderer(
			SimulationManager::getSingleton()->getViewController().getRenderer());
		guiRenderer->beginRendering();

		mRenderTextureTarget->clear();
		mRenderGuiContext->draw();

		guiRenderer->endRendering();

		mFrameWindow->invalidate(true); //notify window of the texture to update
	}
}
