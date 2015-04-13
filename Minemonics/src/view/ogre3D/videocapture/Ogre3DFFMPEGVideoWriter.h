//
//  ofxFFMPEGVideoWriter.h
//  ShapeDeform
//
//  Created by roy_shilkrot on 4/7/13.
//
//

#ifndef __ofxFFMPEGVideoWriter__
#define __ofxFFMPEGVideoWriter__

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
		char errbuf[AV_ERROR_MAX_STRING_SIZE];
		av_strerror(errnum, errbuf, AV_ERROR_MAX_STRING_SIZE);
		return (std::string) errbuf;
	}

#undef av_err2str
#define av_err2str(errnum) av_make_error_string(errnum).c_str()

#endif // __cplusplus

class Ogre3DFFMPEGVideoWriter : public Ogre::RenderTargetListener {
    //instance variables
    AVCodec *codec;
    int size, frame_count;
    AVFrame *picture, *picture_rgb24;
    struct SwsContext *sws_ctx;
    AVOutputFormat *fmt;
    AVFormatContext *oc;
    AVStream *video_st;
    AVCodecContext* c;

    bool initialized;

    Ogre::RenderTexture* renderTexture;
    Ogre::TexturePtr videoTexture;

public:
    Ogre3DFFMPEGVideoWriter():oc(NULL),codec(NULL),initialized(false),frame_count(1) {}
    
    /**
     * setup the video writer
     * @param output filename, the codec and format will be determined by it. (e.g. "xxx.mpg" will create an MPEG1 file
     * @param width of the frame
     * @param height of the frame
     * @param the bitrate
     * @param the framerate
     **/
    void setup(SimulationManager* simulationManager, const char* filename, int width, int height, int bitrate = 400000, int framerate = 12);
    /**
     * add a frame to the video file
     * @param pixels the pixels packed in RGB (24-bit RGBRGBRGB...)
     * @param timestamp
     **/
    void addFrame(Ogre::uint8* pDest,long int timestamp);
    /**
     * close the video file and release all datastructs
     **/
    void close();
    /**
     * is the videowriter initialized?
     **/
    bool isInitialized() const { return initialized; }

    void postRenderTargetUpdate(
    		const Ogre::RenderTargetEvent &evt);

private:
	boost::posix_time::ptime mStart;
	boost::posix_time::ptime mNow;
	boost::posix_time::time_duration mRuntime;
};

#endif /* defined(__ofxFFMPEGVideoWriter__) */
