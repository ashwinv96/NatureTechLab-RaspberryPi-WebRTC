#ifndef CUSTOM_VIDEO_ENCODER_FACTORY_H_
#define CUSTOM_VIDEO_ENCODER_FACTORY_H_

#include <api/video_codecs/video_encoder_factory.h>

#include "args.h"

std::unique_ptr<webrtc::VideoEncoderFactory> CreateCustomVideoEncoderFactory(const Args &args);

class CustomVideoEncoderFactory : public webrtc::VideoEncoderFactory {
  public:
    CustomVideoEncoderFactory(const Args &args)
        : args_(args){};
    ~CustomVideoEncoderFactory() = default;

    std::vector<webrtc::SdpVideoFormat> GetSupportedFormats() const override;

#if __has_include(<api/environment/environment.h>)
    std::unique_ptr<webrtc::VideoEncoder> Create(const webrtc::Environment &env,
                                                 const webrtc::SdpVideoFormat &format) override;
#else
    std::unique_ptr<webrtc::VideoEncoder>
    CreateVideoEncoder(const webrtc::SdpVideoFormat &format) override;
#endif

  private:
    Args args_;
};

#endif // CUSTOM_VIDEO_ENCODER_FACTORY_H_
