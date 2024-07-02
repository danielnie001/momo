cmake_minimum_required(VERSION 3.16)

# Only interpret if() arguments as variables or keywords when unquoted.
cmake_policy(SET CMP0054 NEW)
# MSVC runtime library flags are selected by an abstraction.
cmake_policy(SET CMP0091 NEW)

set(MOMO_PACKAGE_NAME "macos_arm64" CACHE STRING "构建设置自动化的软件包名称")
message("CMAKE_CURRENT_SOURCE_DIR : ${MOMO_PACKAGE_NAME}")
set(TARGET_OS "macos" CACHE STRING "构建目标运行的操作系统。\n有效值为 windows, macos, linux")
set(TARGET_OS_LINUX "" CACHE STRING "TARGET_OS 为 linux 时的详细操作系统信息。")
set(TARGET_ARCH "" CACHE STRING "构建目标运行的 CPU。\n有效值为 x86_64, arm")
set(TARGET_ARCH_ARM "" CACHE STRING "TARGET_ARCH 为 arm 时的详细 CPU 信息。\n有效值为 armv6, armv7, armv8")
set(USE_NVCODEC_ENCODER OFF CACHE BOOL "是否使用 NVIDIA VIDEO CODEC SDK 的硬件编码器")
set(USE_MMAL_ENCODER OFF CACHE BOOL "是否使用 MMAL 硬件编码器")
set(USE_JETSON_ENCODER OFF CACHE BOOL "是否使用 Jetson 的硬件编码器")
set(USE_MSDK_ENCODER OFF CACHE BOOL "是否使用 Intel Media SDK 的硬件编码器")
set(USE_H264 OFF CACHE BOOL "是否使用 H264")
set(USE_SDL2 OFF CACHE BOOL "是否使用 SDL2 进行画面输出")
set(USE_LINUX_PULSE_AUDIO OFF CACHE BOOL "在 Linux 上是否使用 PulseAudio 代替 ALSA")
set(USE_SCREEN_CAPTURER OFF CACHE BOOL "是否使用屏幕捕捉器")
set(BOOST_ROOT_DIR "" CACHE PATH "Boost 的安装目录\n如果为空则使用默认搜索路径的 Boost")
set(SDL2_ROOT_DIR "" CACHE PATH "SDL2 的安装目录\n如果为空则使用默认搜索路径的 SDL2")
set(CLI11_ROOT_DIR "" CACHE PATH "CLI11 的安装目录")
set(NVCODEC_ROOT_DIR "" CACHE PATH "NVIDIA VIDEO CODEC SDK 的安装目录")
set(WEBRTC_INCLUDE_DIR /Users/daniel/Code/webrtc-checkout/src CACHE PATH "WebRTC 的包含目录")
message("WEBRTC_INCLUDE_DIR:${WEBRTC_INCLUDE_DIR}")
set(WEBRTC_LIBRARY_DIR /Users/daniel/Code/webrtc-checkout/src/out/Default/obj CACHE PATH "WebRTC 的库目录")
message("WEBRTC_LIBRARY_DIR:${WEBRTC_LIBRARY_DIR}")
set(WEBRTC_LIBRARY_NAME "webrtc" CACHE STRING "WebRTC 的库名称")
set(CLANG_ROOT "" CACHE PATH "用于编译的 clang 编译器位置")
set(USE_LIBCXX OFF CACHE BOOL "是否使用 libc++ 代替 libstdc++")
set(LIBCXX_INCLUDE_DIR "" CACHE PATH "使用 libc++ 时的包含目录\n如果为空则使用默认搜索路径的 libc++")
set(SYSROOT "" CACHE PATH "TARGET_ARCH 为 arm 时的交叉构建用 RootFS 目录")
set(MOMO_VERSION "unspecified" CACHE STRING "Momo 的版本")
set(MOMO_COMMIT "<commit>" CACHE STRING "Momo 的提交哈希")
set(WEBRTC_BUILD_VERSION "unspecified" CACHE STRING "webrtc-build 的版本")
set(WEBRTC_READABLE_VERSION "unspecified" CACHE STRING "WebRTC 的可读版本")
set(WEBRTC_COMMIT "<commit>" CACHE STRING "WebRTC 的提交哈希")

if(MOMO_PACKAGE_NAME STREQUAL "windows_x86_64")
  set(_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/windows_x86_64/_install)

  set(TARGET_OS "windows")
  set(TARGET_ARCH "x86_64")
  set(USE_NVCODEC_ENCODER ON)
  set(USE_MSDK_ENCODER ON)
  set(USE_H264 ON)
  set(USE_SDL2 ON)
  set(USE_SCREEN_CAPTURER ON)
  set(BOOST_ROOT_DIR ${_INSTALL_DIR}/boost)
  set(SDL2_ROOT_DIR ${_INSTALL_DIR}/SDL2)
  set(CLI11_ROOT_DIR ${_INSTALL_DIR}/CLI11)
  set(WEBRTC_INCLUDE_DIR ${_INSTALL_DIR}/webrtc/include)
  set(WEBRTC_LIBRARY_DIR ${_INSTALL_DIR}/webrtc/lib)

  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${SDL2_ROOT_DIR}/cmake)
  list(APPEND CMAKE_PREFIX_PATH ${BOOST_ROOT_DIR} ${SDL2_ROOT_DIR})

elseif(MOMO_PACKAGE_NAME STREQUAL "macos_arm64")

  set(_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build/macos_arm64/_install)

  set(TARGET_OS "macos")
  set(TARGET_ARCH "arm64")
  set(USE_H264 ON)
  set(USE_SDL2 ON)
  set(USE_SCREEN_CAPTURER ON)
  set(BOOST_ROOT_DIR /opt/homebrew/Cellar/boost/1.84.0_1)
  set(SDL2_ROOT_DIR /opt/homebrew/Cellar/sdl2/2.30.2)
  set(CLI11_ROOT_DIR /opt/homebrew/Cellar/cli11/2.4.2)
  set(WEBRTC_INCLUDE_DIR /Users/daniel/Code/webrtc-checkout/src)
  set(WEBRTC_LIBRARY_DIR /Users/daniel/Code/webrtc-checkout/src/out/Default/obj)

elseif(MOMO_PACKAGE_NAME STREQUAL "raspberry-pi-os_armv6")

  set(TARGET_OS "linux")
  set(TARGET_OS_LINUX "raspberry-pi-os")
  set(TARGET_ARCH "arm")
  set(TARGET_ARCH_ARM "armv6")
  set(USE_MMAL_ENCODER ON)
  set(USE_H264 ON)
  set(BOOST_ROOT_DIR /root/boost)
  set(CLI11_ROOT_DIR /root/CLI11)
  set(WEBRTC_INCLUDE_DIR /root/webrtc/include)
  set(WEBRTC_LIBRARY_DIR /root/webrtc/lib)
  set(CLANG_ROOT /root/llvm/clang)
  set(SYSROOT /root/rootfs)

  set(USE_LIBCXX ON)
  set(LIBCXX_INCLUDE_DIR /root/llvm/libcxx/include)

  set(Boost_ARCHITECTURE 32)

elseif(MOMO_PACKAGE_NAME STREQUAL "raspberry-pi-os_armv7")

  set(TARGET_OS "linux")
  set(TARGET_OS_LINUX "raspberry-pi-os")
  set(TARGET_ARCH "arm")
  set(TARGET_ARCH_ARM "armv7")
  set(USE_MMAL_ENCODER ON)
  set(USE_H264 ON)
  set(USE_SDL2 ON)
  set(BOOST_ROOT_DIR /root/boost)
  set(SDL2_ROOT_DIR /root/SDL2)
  set(CLI11_ROOT_DIR /root/CLI11)
  set(WEBRTC_INCLUDE_DIR /root/webrtc/include)
  set(WEBRTC_LIBRARY_DIR /root/webrtc/lib)
  set(CLANG_ROOT /root/llvm/clang)
  set(SYSROOT /root/rootfs)

  set(USE_LIBCXX ON)
  set(LIBCXX_INCLUDE_DIR /root/llvm/libcxx/include)

  set(Boost_ARCHITECTURE 32)

elseif(MOMO_PACKAGE_NAME STREQUAL "raspberry-pi-os_armv8")

  set(TARGET_OS "linux")
  set(TARGET_OS_LINUX "raspberry-pi-os")
  set(TARGET_ARCH "arm")
  set(TARGET_ARCH_ARM "armv8")
  set(USE_V4L2_ENCODER ON)
  set(USE_H264 ON)
  set(USE_SDL2 ON)
  set(USE_LINUX_PULSE_AUDIO ON)
  set(BOOST_ROOT_DIR /root/boost)
  set(SDL2_ROOT_DIR /root/SDL2)
  set(CLI11_ROOT_DIR /root/CLI11)
  set(WEBRTC_INCLUDE_DIR /root/webrtc/include)
  set(WEBRTC_LIBRARY_DIR /root/webrtc/lib)
  set(CLANG_ROOT /root/llvm/clang)
  set(SYSROOT /root/rootfs)

  set(USE_LIBCXX ON)
  set(LIBCXX_INCLUDE_DIR /root/llvm/libcxx/include)

elseif(MOMO_PACKAGE_NAME STREQUAL "ubuntu-20.04_x86_64")

  set(TARGET_OS "linux")
  set(TARGET_OS_LINUX "ubuntu-20.04")
  set(TARGET_ARCH "x86_64")
  set(USE_H264 ON)
  set(USE_SDL2 ON)
  set(USE_NVCODEC_ENCODER ON)
  set(USE_MSDK_ENCODER ON)
  set(USE_SCREEN_CAPTURER ON)
  set(BOOST_ROOT_DIR /root/boost)
  set(CLI11_ROOT_DIR /root/CLI11)
  set(SDL2_ROOT_DIR /root/SDL2)
  set(LIBVA_ROOT_DIR /root/libva)
  set(MSDK_ROOT_DIR /root/msdk)
  set(WEBRTC_INCLUDE_DIR /root/webrtc/include)
  set(WEBRTC_LIBRARY_DIR /root/webrtc/lib)

  # /root/llvm/clang 不要使用附带的编译器，而是使用通过 apt 安装的 clang-10。
  set(CMAKE_C_COMPILER clang-15)
  set(CMAKE_CXX_COMPILER clang++-15)

  set(USE_LIBCXX ON)
  set(LIBCXX_INCLUDE_DIR /root/llvm/libcxx/include)

elseif(MOMO_PACKAGE_NAME STREQUAL "ubuntu-20.04_armv8_jetson_xavier")

  set(TARGET_OS "linux")
  set(TARGET_OS_LINUX "ubuntu-20.04")
  set(TARGET_ARCH "arm")
  set(TARGET_ARCH_ARM "armv8")
  set(USE_JETSON_ENCODER ON)
  set(USE_H264 ON)
  set(USE_SDL2 ON)
  set(USE_LINUX_PULSE_AUDIO ON)
  set(BOOST_ROOT_DIR /root/boost)
  set(CLI11_ROOT_DIR /root/CLI11)
  set(SDL2_ROOT_DIR /root/SDL2)
  set(WEBRTC_INCLUDE_DIR /root/webrtc/include)
  set(WEBRTC_LIBRARY_DIR /root/webrtc/lib)
  set(CLANG_ROOT /root/llvm/clang)
  set(SYSROOT /root/rootfs)

  set(USE_LIBCXX ON)
  set(LIBCXX_INCLUDE_DIR /root/llvm/libcxx/include)

elseif(MOMO_PACKAGE_NAME STREQUAL "ubuntu-22.04_x86_64")

  set(TARGET_OS "linux")
  set(TARGET_OS_LINUX "ubuntu-22.04")
  set(TARGET_ARCH "x86_64")
  set(USE_H264 ON)
  set(USE_SDL2 ON)
  set(USE_NVCODEC_ENCODER ON)
  set(USE_MSDK_ENCODER ON)
  set(USE_SCREEN_CAPTURER ON)
  set(BOOST_ROOT_DIR /root/boost)
  set(CLI11_ROOT_DIR /root/CLI11)
  set(SDL2_ROOT_DIR /root/SDL2)
  set(LIBVA_ROOT_DIR /root/libva)
  set(MSDK_ROOT_DIR /root/msdk)
  set(WEBRTC_INCLUDE_DIR /root/webrtc/include)
  set(WEBRTC_LIBRARY_DIR /root/webrtc/lib)

  # /root/llvm/clang 不要使用附带的编译器，而是使用通过 apt 安装的 clang-15。
  set(CMAKE_C_COMPILER clang-15)
  set(CMAKE_CXX_COMPILER clang++-15)

  set(USE_LIBCXX ON)
  set(LIBCXX_INCLUDE_DIR /root/llvm/libcxx/include)

else()
endif()

if (NOT "${CLANG_ROOT}" STREQUAL "")
  set(CMAKE_C_COMPILER ${CLANG_ROOT}/bin/clang)
  set(CMAKE_CXX_COMPILER ${CLANG_ROOT}/bin/clang++)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if (NOT "${BOOST_ROOT_DIR}" STREQUAL "")
  list(APPEND CMAKE_PREFIX_PATH ${BOOST_ROOT_DIR})
endif()

if (USE_SDL2 AND (NOT "${SDL2_ROOT_DIR}" STREQUAL ""))
  list(APPEND CMAKE_MODULE_PATH ${SDL2_ROOT_DIR}/cmake)
  list(APPEND CMAKE_PREFIX_PATH ${SDL2_ROOT_DIR})
endif()

# SYSROOT 或其他设置。
# 这些设置需要在 project 之前进行。
if (TARGET_OS STREQUAL "linux")
  if (TARGET_ARCH STREQUAL "arm")
    if (TARGET_ARCH_ARM STREQUAL "armv8")
      set(ARCH_NAME aarch64-linux-gnu)
    else()
      set(ARCH_NAME arm-linux-gnueabihf)
    endif()

    set(CMAKE_SYSTEM_NAME Linux)
    if (TARGET_ARCH_ARM STREQUAL "armv8")
      set(CMAKE_SYSTEM_PROCESSOR aarch64)
    else()
      set(CMAKE_SYSTEM_PROCESSOR arm)
    endif()
    set(CMAKE_SYSROOT ${SYSROOT})
    set(CMAKE_C_COMPILER_TARGET ${ARCH_NAME})
    set(CMAKE_CXX_COMPILER_TARGET ${ARCH_NAME})

    set(CMAKE_FIND_ROOT_PATH ${SYSROOT})
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
  endif()
endif()

if (TARGET_OS STREQUAL "macos")
  set(ARCH_NAME aarch64-apple-darwin)
  set(CMAKE_SYSTEM_PROCESSOR arm64)

  set(CMAKE_C_COMPILER_TARGET ${ARCH_NAME})
  set(CMAKE_CXX_COMPILER_TARGET ${ARCH_NAME})
endif()

project(momo C CXX)

list(APPEND MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(Boost_USE_STATIC_LIBS ON)
if ("${TARGET_OS}" STREQUAL "windows")
  set(Boost_USE_STATIC_RUNTIME ON)
else()
  set(Boost_USE_STATIC_RUNTIME OFF)
endif()

find_package(WebRTC REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem json)
find_package(CLI11 REQUIRED)
if (USE_SDL2)
  find_package(SDL2 REQUIRED)
endif()

add_executable(momo)

string(SUBSTRING "${MOMO_COMMIT}" 0 8 MOMO_COMMIT_SHORT)
string(SUBSTRING "${WEBRTC_COMMIT}" 0 8 WEBRTC_COMMIT_SHORT)
configure_file(src/momo_version.gen.h.template ${CMAKE_CURRENT_BINARY_DIR}/momo_version.gen.h)
target_include_directories(momo PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_sources(momo
  PRIVATE
    src/main.cpp
    src/momo_version.cpp
    src/util.cpp
    src/watchdog.cpp
    src/ssl_verifier.cpp
    src/ayame/ayame_client.cpp
    src/p2p/p2p_server.cpp
    src/p2p/p2p_session.cpp
    src/p2p/p2p_websocket_session.cpp
    src/rtc/aligned_encoder_adapter.cpp
    src/rtc/device_video_capturer.cpp
    src/rtc/momo_video_decoder_factory.cpp
    src/rtc/momo_video_encoder_factory.cpp
    src/rtc/native_buffer.cpp
    src/rtc/peer_connection_observer.cpp
    src/rtc/rtc_connection.cpp
    src/rtc/rtc_manager.cpp
    src/rtc/rtc_ssl_verifier.cpp
    src/rtc/scalable_track_source.cpp
    src/serial_data_channel/serial_data_channel.cpp
    src/serial_data_channel/serial_data_manager.cpp
    src/sora/sora_server.cpp
    src/sora/sora_session.cpp
    src/sora/sora_client.cpp
    src/websocket.cpp
    src/metrics/metrics_server.cpp
    src/metrics/metrics_session.cpp
)

target_include_directories(momo PRIVATE src)

set_target_properties(momo PROPERTIES CXX_STANDARD 20 C_STANDARD 99)

target_link_libraries(momo
  PRIVATE
    WebRTC::WebRTC
    Boost::filesystem
    Boost::json
    CLI11::CLI11
)

target_compile_definitions(momo
  PRIVATE
    # CLI11 在使用 C++17 进行构建时会使用 std::filesystem，但要在 clang 中解决此问题，需要链接 c++fs。
    # 然而，libwebrtc 的 libc++ 并不提供 std::filesystem，因此需要添加以下选项以不使用它。
    CLI11_HAS_FILESYSTEM=0
    OPENSSL_IS_BORINGSSL
    USE_NVCODEC_ENCODER=$<BOOL:${USE_NVCODEC_ENCODER}>
    USE_MMAL_ENCODER=$<BOOL:${USE_MMAL_ENCODER}>
    USE_V4L2_ENCODER=$<BOOL:${USE_V4L2_ENCODER}>
    USE_JETSON_ENCODER=$<BOOL:${USE_JETSON_ENCODER}>
    USE_MSDK_ENCODER=$<BOOL:${USE_MSDK_ENCODER}>
    USE_H264=$<BOOL:${USE_H264}>
    USE_SDL2=$<BOOL:${USE_SDL2}>
    USE_LINUX_PULSE_AUDIO=$<BOOL:${USE_LINUX_PULSE_AUDIO}>
    USE_SCREEN_CAPTURER=$<BOOL:${USE_SCREEN_CAPTURER}>
    # https://github.com/boostorg/container_hash/issues/22 同样的问题也会在 clang-15 上出现，因此需要手动定义以规避该问题。
    BOOST_NO_CXX98_FUNCTION_BASE
)

if (USE_SDL2)
  target_sources(momo
    PRIVATE
      src/sdl_renderer/sdl_renderer.cpp
  )
  target_compile_definitions(momo
    PRIVATE
      _THREAD_SAFE
  )


  if ("${TARGET_OS}" STREQUAL "windows" OR "${TARGET_OS}" STREQUAL "macos")
    target_link_libraries(momo
      PRIVATE
        SDL2::SDL2-static
        SDL2::SDL2main
    )
  else()
    if (TARGET SDL2::SDL2Config)
      target_link_libraries(momo
        PRIVATE
          SDL2::SDL2Config
      )
    else()
      target_link_directories(momo PRIVATE ${SDL2_LIBDIR})
      target_link_libraries(momo PRIVATE SDL2)
      target_include_directories(momo PRIVATE "${SYSROOT}${SDL2_INCLUDE_DIRS}")
    endif()
  endif()

  if ("${TARGET_OS}" STREQUAL "macos")
    target_link_libraries(momo
      PRIVATE
        iconv
        "-framework Carbon"
        "-framework IOKit"
        "-framework ForceFeedback"
    )
  endif()
endif()

if (USE_LIBCXX)
  target_compile_options(momo
    PRIVATE
      "$<$<COMPILE_LANGUAGE:CXX>:-nostdinc++>"
      "$<$<AND:$<COMPILE_LANGUAGE:CXX>,$<BOOL:LIBCXX_INCLUDE_DIR>>:-isystem${LIBCXX_INCLUDE_DIR}>"
  )
endif()

if (USE_SCREEN_CAPTURER)
  target_sources(momo
    PRIVATE
      src/rtc/screen_video_capturer.cpp
  )
  if (TARGET_OS STREQUAL "linux")
    target_link_libraries(momo
      PRIVATE
        # gio-2.0
        # gobject-2.0
        # glib-2.0
        # Xext
        Xdamage
        Xfixes
        Xcomposite
        Xrandr
    )
  endif()
  if (TARGET_OS STREQUAL "macos")
    target_link_libraries(momo
      PRIVATE
        "-framework IOSurface"
    )
  endif()
endif()

if ("${TARGET_OS}" STREQUAL "windows")
  # 将字符编码设为 utf-8，并增加符号表的数量。
  target_compile_options(momo PRIVATE /utf-8 /bigobj)
  set_target_properties(momo
    PROPERTIES
      # 将 CRT 库静态链接，如果是 CMake 3.15 以上版本，可以使用 MSVC_RUNTIME_LIBRARY。
      MSVC_RUNTIME_LIBRARY "MultiThreaded"
  )

  target_link_libraries(momo
    PRIVATE
      dbghelp.lib
      delayimp.lib
      dnsapi.lib
      msimg32.lib
      oleaut32.lib
      psapi.lib
      shell32.lib
      shlwapi.lib
      usp10.lib
      version.lib
      wininet.lib
      winmm.lib
      ws2_32.lib
      amstrmid.lib
      Strmiids.lib
      crypt32.lib
      dmoguids.lib
      iphlpapi.lib
      msdmo.lib
      Secur32.lib
      Shcore.lib
      wmcodecdspuuid.lib
      Dwmapi.lib
  )

  target_compile_definitions(momo
    PRIVATE
      _CONSOLE
      _WIN32_WINNT=0x0A00
      WEBRTC_WIN
      NOMINMAX
      WIN32_LEAN_AND_MEAN
      UNICODE
      _UNICODE
  )

  # NVIDIA Video Codec SDK
  if (USE_NVCODEC_ENCODER)
    target_sources(momo
      PRIVATE
        src/hwenc_nvcodec/nvcodec_h264_encoder.cpp
        NvCodec/NvCodec/NvEncoder/NvEncoder.cpp
        NvCodec/NvCodec/NvEncoder/NvEncoderD3D11.cpp
        src/hwenc_nvcodec/nvcodec_video_decoder.cpp)
    target_include_directories(momo
      PRIVATE
        NvCodec/include
        NvCodec/NvCodec)
    target_link_libraries(momo
      PRIVATE
        DXGI.lib
        D3D11.lib
    )

    # enable_language(CUDA) 使用 CUDA 的 Visual Studio Integration 来检测 CUDA，
    # 但在无法安装 CUDA 驱动的地方无法安装 VS Integration，
    # 因此不能使用 enable_language(CUDA)。
    # 因此（尽管已弃用）使用 FindCUDA 来进行编译。

    set(CUDA_TOOLKIT_ROOT_DIR ${_INSTALL_DIR}/cuda/nvcc)
    find_package(CUDA REQUIRED)

    set_source_files_properties(
        src/cuda/cuda_context_cuda.cpp
        NvCodec/NvCodec/NvDecoder/NvDecoder.cpp
        src/hwenc_nvcodec/nvcodec_decoder_cuda.cpp
      PROPERTIES
        CUDA_SOURCE_PROPERTY_FORMAT OBJ
    )
    cuda_compile(CUDA_FILES
        src/cuda/cuda_context_cuda.cpp
        NvCodec/NvCodec/NvDecoder/NvDecoder.cpp
        src/hwenc_nvcodec/nvcodec_decoder_cuda.cpp
      OPTIONS
        -Xcompiler /utf-8
        -Xcompiler /I${CMAKE_CURRENT_SOURCE_DIR}/NvCodec/include
        -Xcompiler /I${CMAKE_CURRENT_SOURCE_DIR}/NvCodec/NvCodec
        -Xcompiler /I${CMAKE_CURRENT_SOURCE_DIR}/src
    )
    target_sources(momo PRIVATE ${CUDA_FILES})
    target_include_directories(momo PRIVATE ${CUDA_INCLUDE_DIRS})
    target_link_libraries(momo
      PRIVATE
        ${CUDA_TOOLKIT_ROOT_DIR}/lib/x64/cudart_static.lib 
        #${CUDA_LIBRARIES}
    )
  endif()

  # Intel Media SDK
  if (USE_MSDK_ENCODER)
    target_sources(momo
      PRIVATE
        src/hwenc_msdk/msdk_session.cpp
        src/hwenc_msdk/msdk_video_decoder.cpp
        src/hwenc_msdk/msdk_video_encoder.cpp
    )
    target_include_directories(momo PRIVATE ${_INSTALL_DIR}/msdk/include)
    target_link_libraries(momo
      PRIVATE
        ${_INSTALL_DIR}/msdk/lib/libmfx.lib 
    )
  endif()
elseif (TARGET_OS STREQUAL "macos")
  target_sources(momo
    PRIVATE
      src/mac_helper/mac_capturer.mm
      src/mac_helper/macos_version.mm
      src/mac_helper/objc_codec_factory_helper.mm
  )

  target_compile_options(momo PRIVATE -fconstant-string-class=NSConstantString -mmacosx-version-min=11.0)
  target_link_options(momo PRIVATE -ObjC)
  set_target_properties(momo PROPERTIES CXX_VISIBILITY_PRESET hidden)

  target_link_libraries(momo
    PRIVATE
      "-framework Foundation"
      "-framework AVFoundation"
      "-framework CoreServices"
      "-framework CoreFoundation"
      "-framework AudioUnit"
      "-framework AudioToolbox"
      "-framework CoreAudio"
      "-framework CoreGraphics"
      "-framework CoreMedia"
      "-framework CoreVideo"
      "-framework VideoToolbox"
      "-framework AppKit"
      "-framework Metal"
      "-framework MetalKit"
      "-framework OpenGL"
  )

  target_compile_definitions(momo
    PRIVATE
      WEBRTC_POSIX
      WEBRTC_MAC
  )

elseif (TARGET_OS STREQUAL "linux")
  find_package(Threads REQUIRED)

  target_sources(momo
    PRIVATE
      src/v4l2_video_capturer/v4l2_video_capturer.cpp
  )
  target_compile_definitions(momo
    PRIVATE
      WEBRTC_POSIX
      WEBRTC_LINUX
  )
  # 对于 Linux 系统，由于使用了定制的 libc++，需要添加额外的选项。
  target_compile_definitions(momo PRIVATE _LIBCPP_ABI_NAMESPACE=Cr _LIBCPP_ABI_VERSION=2 _LIBCPP_DISABLE_AVAILABILITY)

  set_target_properties(momo PROPERTIES POSITION_INDEPENDENT_CODE ON)
  target_link_libraries(momo
    PRIVATE
      X11
      # Xau
      # Xdmcp
      Xtst
      # xcb
      # plds4
      Xext
      # expat
      dl
      # nss3
      # nssutil3
      # plc4
      # nspr4
      # rt
      Threads::Threads
  )

  # NVIDIA Video Codec SDK
  if (USE_NVCODEC_ENCODER)
    target_sources(momo
      PRIVATE
        src/cuda/cuda_context_cuda.cpp
        src/hwenc_nvcodec/nvcodec_h264_encoder.cpp
        src/hwenc_nvcodec/nvcodec_v4l2_capturer.cpp
        src/hwenc_nvcodec/nvcodec_h264_encoder_cuda.cpp
        src/hwenc_nvcodec/nvcodec_decoder_cuda.cpp
        src/hwenc_nvcodec/nvcodec_video_decoder.cpp
        NvCodec/NvCodec/NvDecoder/NvDecoder.cpp
        NvCodec/NvCodec/NvEncoder/NvEncoder.cpp
        NvCodec/NvCodec/NvEncoder/NvEncoderCuda.cpp)
    target_include_directories(momo
      PRIVATE
        NvCodec/include
        NvCodec/NvCodec
        /usr/local/cuda/include)

    if (WIN32)
      set(_CUDA_COMPILE_OPTIONS "-xcuda;--cuda-gpu-arch=sm_35;-std=gnu++20")
    else()
      set(_CUDA_COMPILE_OPTIONS "-xcuda;--cuda-gpu-arch=sm_35;-std=gnu++17")
    endif()

    # 这些源代码要作为 CUDA 编译。
    set_source_files_properties(
        src/cuda/cuda_context_cuda.cpp
        src/hwenc_nvcodec/nvcodec_h264_encoder_cuda.cpp
        src/hwenc_nvcodec/nvcodec_decoder_cuda.cpp
        NvCodec/NvCodec/NvDecoder/NvDecoder.cpp
        NvCodec/NvCodec/NvEncoder/NvEncoderCuda.cpp
      PROPERTIES
        COMPILE_OPTIONS "${_CUDA_COMPILE_OPTIONS}"
    )

    target_link_directories(momo PRIVATE /usr/local/cuda/lib64)
    target_link_libraries(momo PRIVATE cudart_static dl rt)
  endif()

  # Intel Media SDK
  if (USE_MSDK_ENCODER)
    find_package(MSDK REQUIRED)
    target_sources(momo
      PRIVATE
        src/hwenc_msdk/msdk_session.cpp
        src/hwenc_msdk/msdk_video_decoder.cpp
        src/hwenc_msdk/msdk_video_encoder.cpp
        src/hwenc_msdk/vaapi_utils_drm.cpp
        src/hwenc_msdk/vaapi_utils.cpp
    )
    target_link_libraries(momo
      PRIVATE
        MSDK::MSDK)
  endif()

  if (TARGET_ARCH STREQUAL "arm")
    if (USE_LIBCXX)
      target_include_directories(momo PRIVATE ${SYSROOT}/usr/include/${ARCH_NAME})
      target_link_directories(momo PRIVATE ${SYSROOT}/usr/lib/${ARCH_NAME})
    endif()

    if (TARGET_ARCH_ARM STREQUAL "armv8")
      # Jetson 的设置
      if (USE_JETSON_ENCODER)

        target_sources(momo
          PRIVATE
            src/hwenc_jetson/jetson_buffer.cpp
            src/hwenc_jetson/jetson_jpeg_decoder.cpp
            src/hwenc_jetson/jetson_jpeg_decoder_pool.cpp
            src/hwenc_jetson/jetson_v4l2_capturer.cpp
            src/hwenc_jetson/jetson_video_encoder.cpp
            src/hwenc_jetson/jetson_video_decoder.cpp
            ${SYSROOT}/usr/src/jetson_multimedia_api/samples/common/classes/NvBufSurface.cpp
            ${SYSROOT}/usr/src/jetson_multimedia_api/samples/common/classes/NvBuffer.cpp
            ${SYSROOT}/usr/src/jetson_multimedia_api/samples/common/classes/NvElement.cpp
            ${SYSROOT}/usr/src/jetson_multimedia_api/samples/common/classes/NvElementProfiler.cpp
            ${SYSROOT}/usr/src/jetson_multimedia_api/samples/common/classes/NvJpegDecoder.cpp
            ${SYSROOT}/usr/src/jetson_multimedia_api/samples/common/classes/NvJpegEncoder.cpp
            ${SYSROOT}/usr/src/jetson_multimedia_api/samples/common/classes/NvLogging.cpp
            ${SYSROOT}/usr/src/jetson_multimedia_api/samples/common/classes/NvV4l2Element.cpp
            ${SYSROOT}/usr/src/jetson_multimedia_api/samples/common/classes/NvV4l2ElementPlane.cpp
            ${SYSROOT}/usr/src/jetson_multimedia_api/samples/common/classes/NvVideoEncoder.cpp
            ${SYSROOT}/usr/src/jetson_multimedia_api/samples/common/classes/NvVideoDecoder.cpp
        )

        target_include_directories(momo PRIVATE ${SYSROOT}/usr/src/jetson_multimedia_api/include)
        target_include_directories(momo PRIVATE ${SYSROOT}/usr/src/jetson_multimedia_api/include/libjpeg-8b)
        target_link_directories(momo PRIVATE ${SYSROOT}/usr/lib/aarch64-linux-gnu/tegra)
        target_link_options(momo
          PRIVATE
            "-Wl,-rpath-link=${SYSROOT}/lib/aarch64-linux-gnu"
            "-Wl,-rpath-link=${SYSROOT}/usr/lib/aarch64-linux-gnu"
            "-Wl,-rpath-link=${SYSROOT}/usr/lib/aarch64-linux-gnu/tegra"
        )
        target_link_libraries(momo
          PRIVATE
            nvv4l2
            nvv4lconvert
            #nvbuf_utils
            nvbuf_fdmap
            #nvddk_vic
            #nvddk_2d_v2
            nvjpeg
            nvbufsurface
            nvbufsurftransform
            #nvrm
            #nvrm_graphics
            #nvos
        )
      endif(USE_JETSON_ENCODER)

      if (USE_V4L2_ENCODER)
        add_library(camerac SHARED)
        target_include_directories(camerac PRIVATE ${SYSROOT}/usr/include/libcamera)
        set_target_properties(camerac PROPERTIES CXX_STANDARD 17 C_STANDARD 99)
        target_sources(camerac
          PRIVATE
            src/libcamerac/libcamerac.cpp
        )
        target_link_libraries(camerac
          PRIVATE
            camera
            camera-base
        )

        target_sources(momo
          PRIVATE
            src/hwenc_v4l2/libcamera_capturer.cpp
            src/hwenc_v4l2/v4l2_buffers.cpp
            src/hwenc_v4l2/v4l2_capturer.cpp
            src/hwenc_v4l2/v4l2_converter.cpp
            src/hwenc_v4l2/v4l2_h264_decoder.cpp
            src/hwenc_v4l2/v4l2_h264_encoder.cpp
            src/hwenc_v4l2/v4l2_native_buffer.cpp
            src/hwenc_v4l2/v4l2_runner.cpp
        )
        target_link_libraries(momo PRIVATE camerac)
        set_target_properties(momo PROPERTIES BUILD_RPATH_USE_ORIGIN ON)
      endif(USE_V4L2_ENCODER)
    else()
      # armv6, armv7 用
      if (TARGET_ARCH_ARM STREQUAL "armv6")
        target_compile_options(momo PRIVATE -mfloat-abi=hard -mcpu=arm1176jzf-s -mfpu=vfp)
      else()
        target_compile_options(momo PRIVATE -mfloat-abi=hard -march=armv7-a -mtune=generic-armv7-a -mfpu=neon -mthumb)
      endif()

      if (USE_MMAL_ENCODER)
        target_sources(momo
          PRIVATE
            src/hwenc_mmal/mmal_h264_decoder.cpp
            src/hwenc_mmal/mmal_buffer.cpp
            src/hwenc_mmal/mmal_h264_encoder.cpp
            src/hwenc_mmal/mmal_v4l2_capturer.cpp
        )

        if (TARGET_OS_LINUX STREQUAL "raspberry-pi-os")
          set(_VC_PATH ${SYSROOT}/opt/vc)
        else()
          set(_VC_PATH ${SYSROOT}/usr)
        endif()

        target_include_directories(momo PRIVATE ${_VC_PATH}/include)
        target_compile_options(momo PRIVATE -ftree-vectorize -pipe)
        target_compile_definitions(momo
          PRIVATE
            STANDALONE
            __STDC_CONSTANT_MACROS
            __STDC_LIMIT_MACROS
            TARGET_POSIX
            _LINUX
            PIC
            _REENTRANT
            _LARGEFILE64_SOURCE
            _FILE_OFFSET_BITS=64
            _FORTIFY_SOURCE
            HAVE_LIBOPENMAX=2
            OMX
            OMX_SKIP64BIT
            USE_EXTERNAL_OMX
            HAVE_LIBBCM_HOST
            USE_EXTERNAL_LIBBCM_HOST
            USE_VCHIQ_ARM
        )
        target_link_directories(momo PRIVATE ${_VC_PATH}/lib)
        target_link_libraries(momo
          PRIVATE
            GLESv2
            EGL
            bcm_host
            containers
            vcos
            vcsm
            vchiq_arm
            mmal
            mmal_core
            mmal_components
            mmal_util
            mmal_vc_client
            m
        )

      endif(USE_MMAL_ENCODER)
    endif(TARGET_ARCH_ARM STREQUAL "armv8")
  endif(TARGET_ARCH STREQUAL "arm")
endif()
