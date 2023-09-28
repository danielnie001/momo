#include "momo_video_decoder_factory.h"

// WebRTC
#include <absl/strings/match.h>
#include <api/video_codecs/sdp_video_format.h>
#include <media/base/codec.h>
#include <media/base/media_constants.h>
#include <modules/video_coding/codecs/h264/include/h264.h>
#include <modules/video_coding/codecs/vp8/include/vp8.h>
#include <modules/video_coding/codecs/vp9/include/vp9.h>
#include <rtc_base/checks.h>
#include <rtc_base/logging.h>

#if !defined(__arm__) || defined(__aarch64__) || defined(__ARM_NEON__)
#include <modules/video_coding/codecs/av1/av1_svc_config.h>
#include <modules/video_coding/codecs/av1/dav1d_decoder.h>
#endif

#if defined(__APPLE__)
#include "mac_helper/objc_codec_factory_helper.h"
#endif

#if USE_JETSON_ENCODER
#include "hwenc_jetson/jetson_video_decoder.h"
#endif

#if USE_MMAL_ENCODER
#include "hwenc_mmal/mmal_h264_decoder.h"
#endif

#if USE_MSDK_ENCODER
#include "hwenc_msdk/msdk_video_decoder.h"
#endif

#if USE_V4L2_ENCODER
#include "hwenc_v4l2/v4l2_h264_decoder.h"
#endif

namespace {

bool IsFormatSupported(
    const std::vector<webrtc::SdpVideoFormat>& supported_formats,
    const webrtc::SdpVideoFormat& format) {
  for (const webrtc::SdpVideoFormat& supported_format : supported_formats) {
    if (format.IsSameCodec(supported_format)) {
      return true;
    }
  }
  return false;
}

}  // namespace

MomoVideoDecoderFactory::MomoVideoDecoderFactory(
    const MomoVideoDecoderFactoryConfig& config)
    : config_(config) {
#if defined(__APPLE__)
  video_decoder_factory_ = CreateObjCDecoderFactory();
#endif
}

std::vector<webrtc::SdpVideoFormat>
MomoVideoDecoderFactory::GetSupportedFormats() const {
  std::vector<webrtc::SdpVideoFormat> supported_codecs;

  // VP8
  if (config_.vp8_decoder == VideoCodecInfo::Type::Software ||
      config_.vp8_decoder == VideoCodecInfo::Type::Jetson ||
      config_.vp8_decoder == VideoCodecInfo::Type::NVIDIA ||
      config_.vp8_decoder == VideoCodecInfo::Type::Intel) {
    supported_codecs.push_back(webrtc::SdpVideoFormat(cricket::kVp8CodecName));
  }

  // VP9
  if (config_.vp9_decoder == VideoCodecInfo::Type::Software ||
      config_.vp9_decoder == VideoCodecInfo::Type::Jetson ||
      config_.vp9_decoder == VideoCodecInfo::Type::NVIDIA ||
      config_.vp9_decoder == VideoCodecInfo::Type::Intel) {
    for (const webrtc::SdpVideoFormat& format :
         webrtc::SupportedVP9Codecs(true)) {
      supported_codecs.push_back(format);
    }
  }

#if !defined(__arm__) || defined(__aarch64__) || defined(__ARM_NEON__)
  // AV1
  if (config_.av1_decoder == VideoCodecInfo::Type::Software ||
      config_.av1_decoder == VideoCodecInfo::Type::Jetson ||
      config_.av1_decoder == VideoCodecInfo::Type::Intel) {
    supported_codecs.push_back(webrtc::SdpVideoFormat(
        cricket::kAv1CodecName, webrtc::SdpVideoFormat::Parameters(),
        webrtc::LibaomAv1EncoderSupportedScalabilityModes()));
  }
#endif

  // H264
  std::vector<webrtc::SdpVideoFormat> h264_codecs = {
      CreateH264Format(webrtc::H264Profile::kProfileBaseline,
                       webrtc::H264Level::kLevel3_1, "1"),
      CreateH264Format(webrtc::H264Profile::kProfileBaseline,
                       webrtc::H264Level::kLevel3_1, "0"),
      CreateH264Format(webrtc::H264Profile::kProfileConstrainedBaseline,
                       webrtc::H264Level::kLevel3_1, "1"),
      CreateH264Format(webrtc::H264Profile::kProfileConstrainedBaseline,
                       webrtc::H264Level::kLevel3_1, "0")};

  if (config_.h264_decoder == VideoCodecInfo::Type::VideoToolbox) {
    // VideoToolbox の場合は video_decoder_factory_ から H264 を拾ってくる
    for (auto format : video_decoder_factory_->GetSupportedFormats()) {
      if (absl::EqualsIgnoreCase(format.name, cricket::kH264CodecName)) {
        supported_codecs.push_back(format);
      }
    }
  } else if (config_.h264_decoder != VideoCodecInfo::Type::NotSupported) {
    // その他のデコーダの場合は手動で追加
    for (const webrtc::SdpVideoFormat& h264_format : h264_codecs) {
      supported_codecs.push_back(h264_format);
    }
  }

  return supported_codecs;
}

std::unique_ptr<webrtc::VideoDecoder>
MomoVideoDecoderFactory::CreateVideoDecoder(
    const webrtc::SdpVideoFormat& format) {
  if (!IsFormatSupported(GetSupportedFormats(), format)) {
    RTC_LOG(LS_ERROR) << "Trying to create decoder for unsupported format";
    return nullptr;
  }

  if (absl::EqualsIgnoreCase(format.name, cricket::kVp8CodecName)) {
#if USE_NVCODEC_ENCODER
    if (config_.vp8_decoder == VideoCodecInfo::Type::NVIDIA) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<NvCodecVideoDecoder>(config_.cuda_context,
                                                 CudaVideoCodec::VP8));
    }
#endif
#if USE_MSDK_ENCODER
    if (config_.vp8_decoder == VideoCodecInfo::Type::Intel) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<MsdkVideoDecoder>(MsdkSession::Create(),
                                              MFX_CODEC_VP8));
    }
#endif
#if USE_JETSON_ENCODER
    if (config_.vp8_decoder == VideoCodecInfo::Type::Jetson &&
        JetsonVideoDecoder::IsSupportedVP8()) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<JetsonVideoDecoder>(webrtc::kVideoCodecVP8));
    }
#endif

    if (config_.vp8_decoder == VideoCodecInfo::Type::Software) {
      return webrtc::VP8Decoder::Create();
    }
  }

  if (absl::EqualsIgnoreCase(format.name, cricket::kVp9CodecName)) {
#if USE_NVCODEC_ENCODER
    if (config_.vp9_decoder == VideoCodecInfo::Type::NVIDIA) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<NvCodecVideoDecoder>(config_.cuda_context,
                                                 CudaVideoCodec::VP9));
    }
#endif
#if USE_MSDK_ENCODER
    if (config_.vp9_decoder == VideoCodecInfo::Type::Intel) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<MsdkVideoDecoder>(MsdkSession::Create(),
                                              MFX_CODEC_VP9));
    }
#endif
#if USE_JETSON_ENCODER
    if (config_.vp9_decoder == VideoCodecInfo::Type::Jetson) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<JetsonVideoDecoder>(webrtc::kVideoCodecVP9));
    }
#endif

    if (config_.vp9_decoder == VideoCodecInfo::Type::Software) {
      return webrtc::VP9Decoder::Create();
    }
  }

  if (absl::EqualsIgnoreCase(format.name, cricket::kAv1CodecName)) {
#if USE_MSDK_ENCODER
    if (config_.av1_decoder == VideoCodecInfo::Type::Intel) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<MsdkVideoDecoder>(MsdkSession::Create(),
                                              MFX_CODEC_AV1));
    }
#endif
#if USE_JETSON_ENCODER
    if (config_.av1_decoder == VideoCodecInfo::Type::Jetson &&
        JetsonVideoDecoder::IsSupportedAV1()) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<JetsonVideoDecoder>(webrtc::kVideoCodecAV1));
    }
#endif
#if !defined(__arm__) || defined(__aarch64__) || defined(__ARM_NEON__)
    if (config_.av1_decoder == VideoCodecInfo::Type::Software) {
      return webrtc::CreateDav1dDecoder();
    }
#endif
  }

  if (absl::EqualsIgnoreCase(format.name, cricket::kH264CodecName)) {
#if defined(__APPLE__)
    if (config_.h264_decoder == VideoCodecInfo::Type::VideoToolbox) {
      return video_decoder_factory_->CreateVideoDecoder(format);
    }
#endif

#if USE_NVCODEC_ENCODER
    if (config_.h264_decoder == VideoCodecInfo::Type::NVIDIA) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<NvCodecVideoDecoder>(config_.cuda_context,
                                                 CudaVideoCodec::H264));
    }
#endif
#if USE_MSDK_ENCODER
    if (config_.h264_decoder == VideoCodecInfo::Type::Intel) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<MsdkVideoDecoder>(MsdkSession::Create(),
                                              MFX_CODEC_AVC));
    }
#endif
#if USE_JETSON_ENCODER
    if (config_.h264_decoder == VideoCodecInfo::Type::Jetson) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<JetsonVideoDecoder>(webrtc::kVideoCodecH264));
    }
#endif

#if USE_MMAL_ENCODER
    if (config_.h264_decoder == VideoCodecInfo::Type::MMAL) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<MMALH264Decoder>());
    }
#endif

#if USE_V4L2_ENCODER
    if (config_.h264_decoder == VideoCodecInfo::Type::V4L2) {
      return std::unique_ptr<webrtc::VideoDecoder>(
          absl::make_unique<V4L2H264Decoder>(webrtc::kVideoCodecH264));
    }
#endif
  }

  RTC_DCHECK_NOTREACHED();
  return nullptr;
}
