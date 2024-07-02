#ifndef LIBCAMERA_CAPTURER_H_
#define LIBCAMERA_CAPTURER_H_

#include <memory>
#include <mutex>
#include <queue>

#include <v4l2_video_capturer/v4l2_video_capturer.h>

#include "libcamerac/libcameracpp.h"
#include "rtc/scalable_track_source.h"

struct LibcameraCapturerConfig : V4L2VideoCapturerConfig {
  LibcameraCapturerConfig() {}
  LibcameraCapturerConfig(const V4L2VideoCapturerConfig& config) {
    *static_cast<V4L2VideoCapturerConfig*>(this) = config;
  }
  LibcameraCapturerConfig(const LibcameraCapturerConfig& config) {
    *this = config;
  }
  // native_frame_output == true 的情况下，将捕获的数据作为 kNative 帧传递。
  // native_frame_output == false 的情况下，复制数据并创建 I420Buffer 帧传递。
  // 前者效率更高，但 kNative 帧在进行 Simulcast 时不会自动调整大小，因此应根据情况选择使用哪种方式。
  bool native_frame_output = false;
};

  // 用于从 Raspberry Pi 专用相机获取视频的类
  // 输出格式有两种：直接从 fd 获取和复制到内存中获取
  // 传递的帧缓冲区，如果直接从 fd 获取则为 V4L2NativeBuffer 类，
  // 如果复制到内存中则为 webrtc::I420Buffer 类。
class LibcameraCapturer : public ScalableVideoTrackSource {
 public:
  static rtc::scoped_refptr<LibcameraCapturer> Create(
      LibcameraCapturerConfig config);
  static void LogDeviceList();
  LibcameraCapturer();
  ~LibcameraCapturer();

  int32_t Init(int camera_id);
  void Release();
  int32_t StartCapture(LibcameraCapturerConfig config);

 private:
  static rtc::scoped_refptr<LibcameraCapturer> Create(
      LibcameraCapturerConfig config,
      size_t capture_device_index);
  int32_t StopCapture();
  static void requestCompleteStatic(libcamerac_Request* request,
                                    void* user_data);
  void requestComplete(libcamerac_Request* request);
  void queueRequest(libcamerac_Request* request);

  std::shared_ptr<libcamerac_CameraManager> camera_manager_;
  std::shared_ptr<libcamerac_Camera> camera_;
  bool acquired_;
  std::shared_ptr<libcamerac_CameraConfiguration> configuration_;
  libcamerac_Stream* stream_;
  std::shared_ptr<libcamerac_FrameBufferAllocator> allocator_ = nullptr;
  struct Span {
    uint8_t* buffer;
    int length;
    int fd;
  };
  std::map<const libcamerac_FrameBuffer*, std::vector<Span>> mapped_buffers_;
  std::queue<libcamerac_FrameBuffer*> frame_buffer_;
  std::vector<std::shared_ptr<libcamerac_Request>> requests_;
  std::shared_ptr<libcamerac_ControlList> controls_;
  bool camera_started_;
  std::mutex camera_stop_mutex_;
};

#endif  // LIBCAMERA_CAPTURER_H_