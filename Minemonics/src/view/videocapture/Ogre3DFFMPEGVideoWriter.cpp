//# corresponding header
#include <view/videocapture/Ogre3DFFMPEGVideoWriter.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
#include <Ogre.h>
#include <OgreHardwarePixelBuffer.h>

#define FF_API_PIX_FMT 0 // fix collision between Ogre::PixelFormat and the Macro PixelFormat AVPixelFormat in pixfmt.h of FFmpeg
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
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

void Ogre3DFFMPEGVideoWriter::setup(const char* filename, int width, int height,
	int bitrate, float timebasefactor) {

	mTimebasefactor = timebasefactor;
	// main frame timer initialization
	mStart = time.getMilliseconds();
	mNow = mStart;
	mRuntime = mNow - mStart;

	mVideoTexture =
		SimulationManager::getSingleton()->getRoot()->getTextureManager()->createManual(
			"VideoTex", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Ogre::TEX_TYPE_2D, width, height, 0, Ogre::PF_R8G8B8_UINT,
			Ogre::TU_RENDERTARGET);

	mRenderTexture = mVideoTexture->getBuffer()->getRenderTarget();
	mRenderTexture->addViewport(
		SimulationManager::getSingleton()->getViewController().getCameraHandler().getCamera());
	mRenderTexture->getViewport(0)->setClearEveryFrame(true);
	mRenderTexture->getViewport(0)->setBackgroundColour(
		Ogre::ColourValue::Black);
	//TODO:: The overlays are not shown here, should they be there and how to achieve this?
	mRenderTexture->getViewport(0)->setOverlaysEnabled(true);
	mRenderTexture->addListener(this);
	mRenderTexture->setAutoUpdated(true);

	printf("Video encoding: %s\n", filename);
	/* register all the formats and codecs */
	av_register_all();

	/* allocate the output media context */
	avformat_alloc_output_context2(&mAvFormatContext, NULL, NULL, filename);
	if (!mAvFormatContext) {
		printf(
			"Could not deduce output format from file extension: using MPEG.\n");
		avformat_alloc_output_context2(&mAvFormatContext, NULL, "mp4",
			filename);
	}
	if (!mAvFormatContext) {
		fprintf(stderr, "could not create AVFormat context\n");
		exit(1);
	}
	mAVOutputFormat = mAvFormatContext->oformat;

	AVPixelFormat supported_pix_fmt = AV_PIX_FMT_NONE;

	/* Add the audio and video streams using the default format codecs
	 * and initialize the codecs. */
	mAVStream = NULL;
	if (mAVOutputFormat->video_codec != AV_CODEC_ID_NONE) {
		/* find the video encoder */
		AVCodecID avcid = mAVOutputFormat->video_codec;
		mAVCodec = avcodec_find_encoder(avcid);
		if (!mAVCodec) {
			fprintf(stderr, "codec not found: %s\n", avcodec_get_name(avcid));
			exit(1);
		} else {
			const AVPixelFormat* p = mAVCodec->pix_fmts;
			while (p != NULL && *p != AV_PIX_FMT_NONE) {
				printf("supported pix fmt: %s\n", av_get_pix_fmt_name(*p));
				supported_pix_fmt = *p;
				++p;
			}
			if (p == NULL || *p == AV_PIX_FMT_NONE) {
				if (mAVOutputFormat->video_codec == AV_CODEC_ID_RAWVIDEO) {
					supported_pix_fmt = AV_PIX_FMT_RGB24;
				} else {
					supported_pix_fmt = AV_PIX_FMT_YUV420P; /* default pix_fmt */
				}
			}
		}

		mAVStream = avformat_new_stream(mAvFormatContext, mAVCodec);
		if (!mAVStream) {
			fprintf(stderr, "Could not allocate stream\n");
			exit(1);
		}
		mAVStream->id = mAvFormatContext->nb_streams - 1;
		mAVCodecContext = mAVStream->codec;

		/* Some formats want stream headers to be separate. */
		if (mAvFormatContext->oformat->flags & AVFMT_GLOBALHEADER)
			mAVCodecContext->flags |= CODEC_FLAG_GLOBAL_HEADER;
	}

	/* Now that all the parameters are set, we can open the audio and
	 * video codecs and allocate the necessary encode buffers. */
	{

		mAVFrame = av_frame_alloc();
		mAVFrame->pts = 0;

		/* put sample parameters */
		mAVCodecContext->codec_id = mAVOutputFormat->video_codec;
		mAVCodecContext->bit_rate = bitrate;
		// resolution must be a multiple of two
		mAVCodecContext->width = width;
		mAVCodecContext->height = height;
		// frames per second
		mAVStream->time_base = (AVRational ) { 1, timebasefactor };
		mAVCodecContext->time_base = mAVStream->time_base;
		mAVCodecContext->pix_fmt = supported_pix_fmt;
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
		if ((ret = avcodec_open2(mAVCodecContext, mAVCodec, &options)) < 0) {
			fprintf(stderr, "Could not open codec: %s\n", av_err2str(ret));
			exit(1);
		} else {
			printf("opened %s\n",
				avcodec_get_name(mAVOutputFormat->video_codec));
		}
//        } else
//            printf("raw video, no codec\n");

		/* alloc image and output buffer */
		mAVFrame->data[0] = NULL;
		mAVFrame->linesize[0] = -1;
		mAVFrame->format = mAVCodecContext->pix_fmt;

		ret = av_image_alloc(mAVFrame->data, mAVFrame->linesize,
			mAVCodecContext->width, mAVCodecContext->height,
			(AVPixelFormat) mAVFrame->format, 32);
		if (ret < 0) {
			fprintf(stderr, "Could not allocate raw picture buffer: %s\n",
				av_err2str(ret));
			exit(1);
		} else {
			printf(
				"allocated picture of size %d (ptr %p), linesize %d %d %d %d\n",
				ret, mAVFrame->data[0], mAVFrame->linesize[0],
				mAVFrame->linesize[1], mAVFrame->linesize[2],
				mAVFrame->linesize[3]);
		}

		mPictureRGB24 = av_frame_alloc();
		mPictureRGB24->format = AV_PIX_FMT_0RGB32;

		if ((ret = av_image_alloc(mPictureRGB24->data, mPictureRGB24->linesize,
			mAVCodecContext->width, mAVCodecContext->height,
			(AVPixelFormat) mPictureRGB24->format, 24)) < 0) {
			fprintf(stderr, "cannot allocate RGB temp image\n");
			exit(1);
		} else
			printf(
				"allocated picture of size %d (ptr %p), linesize %d %d %d %d\n",
				ret, mPictureRGB24->data[0], mPictureRGB24->linesize[0],
				mPictureRGB24->linesize[1], mPictureRGB24->linesize[2],
				mPictureRGB24->linesize[3]);

		size = ret;
	}

	av_dump_format(mAvFormatContext, 0, filename, 1);
	/* open the output file, if needed */
	if (!(mAVOutputFormat->flags & AVFMT_NOFILE)) {
		int ret;
		if ((ret = avio_open(&mAvFormatContext->pb, filename, AVIO_FLAG_WRITE))
			< 0) {
			fprintf(stderr, "Could not open '%s': %s\n", filename,
				av_err2str(ret));
			exit(1);
		}
	}
	/* Write the stream header, if any. */
	int ret = avformat_write_header(mAvFormatContext, NULL);
	if (ret < 0) {
		fprintf(stderr, "Error occurred when opening output file: %s\n",
			av_err2str(ret));
		exit(1);
	}

	/* get sws context for RGB24 -> YUV420 conversion */
	mSwsContext = sws_getContext(mAVCodecContext->width,
		mAVCodecContext->height, (AVPixelFormat) mPictureRGB24->format,
		mAVCodecContext->width, mAVCodecContext->height,
		(AVPixelFormat) mAVFrame->format, SWS_BICUBIC, NULL, NULL, NULL);
	if (!mSwsContext) {
		fprintf(stderr, "Could not initialize the conversion context\n");
		exit(1);
	}

	mWriterInitialized = true;
}

/* add a frame to the video file, RGB 24bpp format */
void Ogre3DFFMPEGVideoWriter::addFrame(Ogre::uint8* pDest, long int timestamp) {

	if (mWriterInitialized) {
		/* copy the buffer */
		memcpy(mPictureRGB24->data[0], pDest, size);
		mPictureRGB24->width = mAVCodecContext->width;
		mPictureRGB24->height = mAVCodecContext->height;

		/* convert RGB24 to YUV420 */
		sws_scale(mSwsContext, mPictureRGB24->data, mPictureRGB24->linesize, 0,
			mAVCodecContext->height, mAVFrame->data, mAVFrame->linesize);

		mAVFrame->width = mAVCodecContext->width;
		mAVFrame->height = mAVCodecContext->height;

		int ret = -1;
		if (mAvFormatContext->oformat->flags & AVFMT_RAWPICTURE) {
			/* Raw video case - directly store the picture in the packet */
			AVPacket pkt;
			av_init_packet(&pkt);
			pkt.flags |= AV_PKT_FLAG_KEY;
			pkt.stream_index = mAVStream->index;
			pkt.data = mAVFrame->data[0];
			pkt.size = sizeof(AVPicture);
			//pkt.dts = c->time_base;
			//pkt.pts = timestamp;
			ret = av_interleaved_write_frame(mAvFormatContext, &pkt);
		} else {
			AVPacket pkt = { 0 };
			int got_packet;
			av_init_packet(&pkt);
			/* encode the image */
			ret = avcodec_encode_video2(mAVCodecContext, &pkt, mAVFrame,
				&got_packet);
			if (ret < 0) {
				fprintf(stderr, "Error encoding video frame: %s\n",
					av_err2str(ret));
				exit(1);
			}
			/* If size is zero, it means the image was buffered. */
			if (!ret && got_packet && pkt.size) {
				pkt.stream_index = mAVStream->index;
				/* Write the compressed frame to the media file. */
				ret = av_interleaved_write_frame(mAvFormatContext, &pkt);
			} else {
				ret = 0;
			}
		}
		if (timestamp == 0) {
			mAVFrame->pts += av_rescale_q(1, mAVStream->codec->time_base,
				mAVStream->time_base);
		} else {
			//std::cout << "pts::" << picture->pts << "/avrescale::" << av_rescale_q(timestamp, video_st->codec->time_base,
			//		video_st->time_base) << std::endl;
			mAVFrame->pts += av_rescale_q(timestamp,
				mAVStream->codec->time_base, mAVStream->time_base);
		}
		frame_count++;
	}
}

void Ogre3DFFMPEGVideoWriter::close() {
	/* Write the trailer, if any. The trailer must be written before you
	 * close the CodecContexts open when you wrote the header; otherwise
	 * av_write_trailer() may try to use memory that was freed on
	 * av_codec_close(). */
	av_write_trailer (mAvFormatContext);
	/* Close each codec. */

	avcodec_close(mAVStream->codec);
	av_freep(&(mAVFrame->data[0]));
	av_free (mAVFrame);

	if (!(mAVOutputFormat->flags & AVFMT_NOFILE))
		/* Close the output file. */
		avio_close(mAvFormatContext->pb);

	/* free the stream */
	avformat_free_context(mAvFormatContext);

	printf("closed video file\n");

	mWriterInitialized = false;
	frame_count = 0;
}

void Ogre3DFFMPEGVideoWriter::postRenderTargetUpdate(
	const Ogre::RenderTargetEvent &evt) {

	if (mWriterInitialized) {
		// main frame timer update
		mPrevious = mNow;
		mNow = time.getMilliseconds();
		mRuntime = mNow - mStart;

		Ogre::RenderTexture *pRenderTex =
			mVideoTexture->getBuffer()->getRenderTarget();
		Ogre::HardwarePixelBufferSharedPtr buffer = mVideoTexture->getBuffer();

		buffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY);

		const Ogre::PixelBox &pb = buffer->getCurrentLock();
		Ogre::uint8* pDest = static_cast<Ogre::uint8*>(pb.data);

		//If video colors are wrong in the video, check the value of
		// pb.format in OgrePixelFormat.h and set picture_rgb24->format in setup accordingly
//		std::cout << "diff::" << mRuntime / (1000.0f / mTimebasefactor)
//			<< std::endl;
		addFrame(pDest, mRuntime / (1000.0f / mTimebasefactor));
		mStart = time.getMilliseconds();

		buffer->unlock();
	}
}
