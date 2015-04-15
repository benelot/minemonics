//
//  ofxFFMPEGVideoWriter.cpp
//  ShapeDeform
//
//  Created by roy_shilkrot on 4/7/13.
//
//
// taken from ffmpeg's examples code: http://ffmpeg.org/doxygen/trunk/api-example_8c-source.html
// http://ffmpeg.org/doxygen/trunk/doc_2examples_2decoding_encoding_8c-example.html#a33
// http://ffmpeg.org/doxygen/trunk/doc_2examples_2muxing_8c-example.html#a75
//

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
#include <Ogre.h>
#include <OgreHardwarePixelBuffer.h>
#ifdef __cplusplus
extern "C" {
#include <libavutil/mathematics.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavutil/pixdesc.h>
#include <libavformat/avformat.h>
}
#endif

//# custom headers
//## base headers
#include "SimulationManager.h"

//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

#include "Ogre3DFFMPEGVideoWriter.h"

void Ogre3DFFMPEGVideoWriter::setup(SimulationManager* simulationManager,
		const char* filename, int width, int height, int bitrate,float timebasefactor) {

	mTimebasefactor = timebasefactor;
	// main frame timer initialization
	mStart = boost::posix_time::microsec_clock::local_time();
	mNow = boost::posix_time::microsec_clock::local_time();
	mRuntime = mNow - mStart;

	videoTexture =
			simulationManager->getRoot()->getTextureManager()->createManual(
					"VideoTex",
					Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
					Ogre::TEX_TYPE_2D, width, height, 0, Ogre::PF_R8G8B8_UINT,
					Ogre::TU_RENDERTARGET);

	renderTexture = videoTexture->getBuffer()->getRenderTarget();
	renderTexture->addViewport(simulationManager->getCamera());
	renderTexture->getViewport(0)->setClearEveryFrame(true);
	renderTexture->getViewport(0)->setBackgroundColour(
			Ogre::ColourValue::Black);
	//TODO:: The overlays are not shown here, should they be there and how to achieve this?
	renderTexture->getViewport(0)->setOverlaysEnabled(true);
	renderTexture->addListener(this);
	renderTexture->setAutoUpdated(true);

	printf("Video encoding: %s\n", filename);
	/* register all the formats and codecs */
	av_register_all();

	/* allocate the output media context */
	avformat_alloc_output_context2(&oc, NULL, NULL, filename);
	if (!oc) {
		printf(
				"Could not deduce output format from file extension: using MPEG.\n");
		avformat_alloc_output_context2(&oc, NULL, "mp4", filename);
	}
	if (!oc) {
		fprintf(stderr, "could not create AVFormat context\n");
		exit(1);
	}
	fmt = oc->oformat;

	AVPixelFormat supported_pix_fmt = AV_PIX_FMT_NONE;

	/* Add the audio and video streams using the default format codecs
	 * and initialize the codecs. */
	video_st = NULL;
	if (fmt->video_codec != AV_CODEC_ID_NONE) {
		/* find the video encoder */
		AVCodecID avcid = fmt->video_codec;
		codec = avcodec_find_encoder(avcid);
		if (!codec) {
			fprintf(stderr, "codec not found: %s\n", avcodec_get_name(avcid));
			exit(1);
		} else {
			const AVPixelFormat* p = codec->pix_fmts;
			while (p != NULL && *p != AV_PIX_FMT_NONE) {
				printf("supported pix fmt: %s\n", av_get_pix_fmt_name(*p));
				supported_pix_fmt = *p;
				++p;
			}
			if (p == NULL || *p == AV_PIX_FMT_NONE) {
				if (fmt->video_codec == AV_CODEC_ID_RAWVIDEO) {
					supported_pix_fmt = AV_PIX_FMT_RGB24;
				} else {
					supported_pix_fmt = AV_PIX_FMT_YUV420P; /* default pix_fmt */
				}
			}
		}

		video_st = avformat_new_stream(oc, codec);
		if (!video_st) {
			fprintf(stderr, "Could not allocate stream\n");
			exit(1);
		}
		video_st->id = oc->nb_streams - 1;
		c = video_st->codec;

		/* Some formats want stream headers to be separate. */
		if (oc->oformat->flags & AVFMT_GLOBALHEADER)
			c->flags |= CODEC_FLAG_GLOBAL_HEADER;
	}

	/* Now that all the parameters are set, we can open the audio and
	 * video codecs and allocate the necessary encode buffers. */
	{

		picture = avcodec_alloc_frame();
		picture->pts = 0;

		/* put sample parameters */
		c->codec_id = fmt->video_codec;
		c->bit_rate = bitrate;
		// resolution must be a multiple of two
		c->width = width;
		c->height = height;
		// frames per second
		video_st->time_base = (AVRational ) { 1, timebasefactor };
		c->time_base = video_st->time_base;
		c->pix_fmt = supported_pix_fmt;
//        c->gop_size = 10; // emit one intra frame every ten frames
//        c->max_b_frames=1;
//
//        { //try to get the default pix format
//            AVCodecContext tmpcc;
//            avcodec_get_context_defaults3(&tmpcc, c->codec);
//            c->pix_fmt = (tmpcc.pix_fmt != AV_PIX_FMT_NONE) ? tmpcc.pix_fmt : AV_PIX_FMT_YUV420P;
//        }
		int ret = 0;

		/* open it */
//        if(c->codec_id != AV_CODEC_ID_RAWVIDEO) {
		AVDictionary* options = NULL;
		if ((ret = avcodec_open2(c, codec, &options)) < 0) {
			fprintf(stderr, "Could not open codec: %s\n", av_err2str(ret));
			exit(1);
		} else {
			printf("opened %s\n", avcodec_get_name(fmt->video_codec));
		}
//        } else
//            printf("raw video, no codec\n");

		/* alloc image and output buffer */
		picture->data[0] = NULL;
		picture->linesize[0] = -1;
		picture->format = c->pix_fmt;

		ret = av_image_alloc(picture->data, picture->linesize, c->width,
				c->height, (AVPixelFormat) picture->format, 32);
		if (ret < 0) {
			fprintf(stderr, "Could not allocate raw picture buffer: %s\n",
					av_err2str(ret));
			exit(1);
		} else {
			printf(
					"allocated picture of size %d (ptr %x), linesize %d %d %d %d\n",
					ret, picture->data[0], picture->linesize[0],
					picture->linesize[1], picture->linesize[2],
					(unsigned int) picture->linesize[3]);
		}

		picture_rgb24 = avcodec_alloc_frame();
		picture_rgb24->format = AV_PIX_FMT_0RGB32;

		if ((ret = av_image_alloc(picture_rgb24->data, picture_rgb24->linesize,
				c->width, c->height, (AVPixelFormat) picture_rgb24->format, 24))
				< 0) {
			fprintf(stderr, "cannot allocate RGB temp image\n");
			exit(1);
		} else
			printf(
					"allocated picture of size %d (ptr %x), linesize %d %d %d %d\n",
					ret, picture_rgb24->data[0], picture_rgb24->linesize[0],
					picture_rgb24->linesize[1], picture_rgb24->linesize[2],
					(unsigned int) picture_rgb24->linesize[3]);

		size = ret;
	}

	av_dump_format(oc, 0, filename, 1);
	/* open the output file, if needed */
	if (!(fmt->flags & AVFMT_NOFILE)) {
		int ret;
		if ((ret = avio_open(&oc->pb, filename, AVIO_FLAG_WRITE)) < 0) {
			fprintf(stderr, "Could not open '%s': %s\n", filename,
					av_err2str(ret));
			exit(1);
		}
	}
	/* Write the stream header, if any. */
	int ret = avformat_write_header(oc, NULL);
	if (ret < 0) {
		fprintf(stderr, "Error occurred when opening output file: %s\n",
				av_err2str(ret));
		exit(1);
	}

	/* get sws context for RGB24 -> YUV420 conversion */
	sws_ctx = sws_getContext(c->width, c->height,
			(AVPixelFormat) picture_rgb24->format, c->width, c->height,
			(AVPixelFormat) picture->format,
			SWS_BICUBIC, NULL, NULL, NULL);
	if (!sws_ctx) {
		fprintf(stderr, "Could not initialize the conversion context\n");
		exit(1);
	}

	initialized = true;
}

/* add a frame to the video file, RGB 24bpp format */
void Ogre3DFFMPEGVideoWriter::addFrame(Ogre::uint8* pDest, long int timestamp) {

	if (initialized) {
		/* copy the buffer */
		memcpy(picture_rgb24->data[0], pDest, size);
		picture_rgb24->width = c->width;
		picture_rgb24->height = c->height;

		/* convert RGB24 to YUV420 */
		sws_scale(sws_ctx, picture_rgb24->data, picture_rgb24->linesize, 0,
				c->height, picture->data, picture->linesize);

		picture->width = c->width;
		picture->height = c->height;

		int ret = -1;
		if (oc->oformat->flags & AVFMT_RAWPICTURE) {
			/* Raw video case - directly store the picture in the packet */
			AVPacket pkt;
			av_init_packet(&pkt);
			pkt.flags |= AV_PKT_FLAG_KEY;
			pkt.stream_index = video_st->index;
			pkt.data = picture->data[0];
			pkt.size = sizeof(AVPicture);
			//pkt.dts = c->time_base;
			//pkt.pts = timestamp;
			ret = av_interleaved_write_frame(oc, &pkt);
		} else {
			AVPacket pkt = { 0 };
			int got_packet;
			av_init_packet(&pkt);
			/* encode the image */
			ret = avcodec_encode_video2(c, &pkt, picture, &got_packet);
			if (ret < 0) {
				fprintf(stderr, "Error encoding video frame: %s\n",
						av_err2str(ret));
				exit(1);
			}
			/* If size is zero, it means the image was buffered. */
			if (!ret && got_packet && pkt.size) {
				pkt.stream_index = video_st->index;
				/* Write the compressed frame to the media file. */
				ret = av_interleaved_write_frame(oc, &pkt);
			} else {
				ret = 0;
			}
		}
		if (timestamp == 0) {
			picture->pts += av_rescale_q(1, video_st->codec->time_base,
					video_st->time_base);
		} else {
			//std::cout << "pts::" << picture->pts << "/avrescale::" << av_rescale_q(timestamp, video_st->codec->time_base,
			//		video_st->time_base) << std::endl;
			picture->pts += av_rescale_q(timestamp, video_st->codec->time_base,
					video_st->time_base);
		}
		frame_count++;
	}
}

void Ogre3DFFMPEGVideoWriter::close() {
	/* Write the trailer, if any. The trailer must be written before you
	 * close the CodecContexts open when you wrote the header; otherwise
	 * av_write_trailer() may try to use memory that was freed on
	 * av_codec_close(). */
	av_write_trailer(oc);
	/* Close each codec. */

	avcodec_close(video_st->codec);
	av_freep(&(picture->data[0]));
	av_free(picture);

	if (!(fmt->flags & AVFMT_NOFILE))
		/* Close the output file. */
		avio_close(oc->pb);

	/* free the stream */
	avformat_free_context(oc);

	printf("closed video file\n");

	initialized = false;
	frame_count = 0;
}

void Ogre3DFFMPEGVideoWriter::postRenderTargetUpdate(
		const Ogre::RenderTargetEvent &evt) {

	if (initialized) {
		// main frame timer update
		mNow = boost::posix_time::microsec_clock::local_time();
		mRuntime = mNow - mStart;

		Ogre::RenderTexture *pRenderTex =
				videoTexture->getBuffer()->getRenderTarget();
		Ogre::HardwarePixelBufferSharedPtr buffer = videoTexture->getBuffer();

		buffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);

		const Ogre::PixelBox &pb = buffer->getCurrentLock();
		Ogre::uint8* pDest = static_cast<Ogre::uint8*>(pb.data);

		//TODO: If video colors are wrong in the video, check the value of
		// pb.format in OgrePixelFormat.h and set picture_rgb24->format in setup accordingly
		//std::cout << "diff::" << mRuntime.total_milliseconds()/(0.5f*1000.0f/mTimebasefactor) << std::endl;
		addFrame(pDest, mRuntime.total_milliseconds()/(0.5f*1000.0f/mTimebasefactor));
		mStart = boost::posix_time::microsec_clock::local_time();

		buffer->unlock();
	}
}
