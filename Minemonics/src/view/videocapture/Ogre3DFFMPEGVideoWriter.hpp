#ifndef VIEW_VIDEOCAPTURE_OGRE3DFFMPEGVIDEOWRITER
#define VIEW_VIDEOCAPTURE_OGRE3DFFMPEGVIDEOWRITER

//# corresponding header
//# forward declarations
class SimulationManager;
//# system headers
#include <iostream>

//## controller headers
//## model headers
//## view headers
#include <OgreRenderTexture.h>
#include <OgreRenderTarget.h>
#include <OgreRenderTargetListener.h>
#include <OgreCamera.h>

#define FF_API_PIX_FMT 0 // fix collision between Ogre::PixelFormat and the Macro PixelFormat AVPixelFormat in pixfmt.h of FFmpeg
#ifdef __cplusplus
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}
#endif

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

#ifdef  __cplusplus

static const std::string av_make_error_string(int errnum) {
	char errorBuffer[AV_ERROR_MAX_STRING_SIZE];
	av_strerror(errnum, errorBuffer, AV_ERROR_MAX_STRING_SIZE);
	return (std::string) errorBuffer;
}

#undef av_err2str
#define av_err2str(errnum) av_make_error_string(errnum).c_str()

#endif // __cplusplus

/**
 * @brief		An adaptive framerate video capturer for OGRE3D.
 * @details		An adaptive framerate video capturer for OGRE3D.
 * Adapted from ofxFFMPEGVideoWriter.cpp created by roy_shilkrot on 4/7/13.
 * taken from ffmpeg's examples code: http://ffmpeg.org/doxygen/trunk/api-example_8c-source.html
 * http://ffmpeg.org/doxygen/trunk/doc_2examples_2decoding_encoding_8c-example.html#a33
 * http://ffmpeg.org/doxygen/trunk/doc_2examples_2muxing_8c-example.html#a75
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class Ogre3DFFMPEGVideoWriter: public Ogre::RenderTargetListener {
public:
	Ogre3DFFMPEGVideoWriter() :
		mAvFormatContext(NULL), mAVCodec(NULL), mWriterInitialized(false), frame_count(
			1), mAVCodecContext(NULL), size(0), mAVOutputFormat(NULL), mSwsContext(
			NULL), mAVFrame(NULL), mPictureRGB24(NULL), mTimebasefactor(0), mAVStream(
			NULL), mRenderTexture(NULL), mPrevious(0), mNow(0), mRuntime(0), mStart(
			0) {
	}

	/**
	 * setup the video writer
	 * @param output filename, the codec and format will be determined by it. (e.g. "xxx.mpg" will create an MPEG1 file)
	 * @param width width of the frame
	 * @param height height of the frame
	 * @param bitrate the bitrate of the video
	 * @param timebasefactor the timebasefactor
	 **/
	void setup(const char* filename, int width, int height,
		int bitrate = 800000, float timebasefactor = 200);
	/**
	 * add a frame to the video file
	 * @param pixels the pixels packed in RGB (24-bit RGBRGBRGB...)
	 * @param timestamp
	 **/
	void addFrame(Ogre::uint8* pDest, long int timestamp);
	/**
	 * close the video file and release all datastructs
	 **/
	void close();
	/**
	 * is the videowriter initialized?
	 **/
	bool isInitialized() const {
		return mWriterInitialized;
	}

	void postRenderTargetUpdate(const Ogre::RenderTargetEvent &evt);

private:
	Ogre::Timer time;
	unsigned long int mStart;
	unsigned long int mPrevious;
	unsigned long int mNow;
	long int mRuntime;
	float mTimebasefactor;

	//instance variables
	AVCodec *mAVCodec;
	int size, frame_count;
	AVFrame *mAVFrame, *mPictureRGB24;
	struct SwsContext *mSwsContext;
	AVOutputFormat *mAVOutputFormat;
	AVFormatContext *mAvFormatContext;
	AVStream *mAVStream;
	AVCodecContext* mAVCodecContext;

	bool mWriterInitialized;

	Ogre::RenderTexture* mRenderTexture;
	Ogre::TexturePtr mVideoTexture;
};

#endif /* VIEW_VIDEOCAPTURE_OGRE3DFFMPEGVIDEOWRITER */
