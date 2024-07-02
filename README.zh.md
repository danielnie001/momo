# WebRTC Native Client Momo

[![libwebrtc](https://img.shields.io/badge/libwebrtc-m119.6045-blue.svg)](https://chromium.googlesource.com/external/webrtc/+/branch-heads/6045)
[![GitHub tag (latest SemVer)](https://img.shields.io/github/tag/shiguredo/momo.svg)](https://github.com/shiguredo/momo)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Actions Status](https://github.com/shiguredo/momo/workflows/daily-build-workflow/badge.svg)](https://github.com/shiguredo/momo/actions)

## WebRTC 原生客户端 Momo

我们不会回复未在 Discord 上讨论过的 PR 或问题。此外，Discord 仅提供日语版本。

请在使用前阅读 https://github.com/shiguredo/oss/blob/master/README.en.md。

## 时雨堂开源软件

在使用前请阅读 https://github.com/shiguredo/oss

## WebRTC 原生客户端 Momo

WebRTC Native Client Momo 是利用 libwebrtc 在各种环境中无需浏览器即可运行的 WebRTC 原生客户端。

https://momo.shiguredo.jp/

### 硬件编码器支持

- [Raspberry Pi](https://www.raspberrypi.org/) 利用 Raspberry Pi GPU 搭载的 H.264 硬件编码器功能
- [NVIDIA Jetson](https://www.nvidia.com/ja-jp/autonomous-machines/embedded-systems/) 利用 NVIDIA Jetson 搭载的 VP8、VP9 和 H.264 硬件编码器功能，可以实现 4K@30 的流媒体传输。
- Apple macOS 搭载的 H.264 硬件加速器功能可通过 [VideoToolbox](https://developer.apple.com/documentation/videotoolbox) 使用
- NVIDIA 显卡搭载的硬件加速器功能可通过 [NVIDIA VIDEO CODEC SDK](https://developer.nvidia.com/nvidia-video-codec-sdk) 使用
- [Intel Quick Sync Video](https://www.intel.co.jp/content/www/jp/ja/architecture-and-technology/quick-sync-video/quick-sync-video-general.html) 可通过 [Intel Media SDK](https://www.intel.com/content/www/us/en/developer/tools/media-sdk/overview.html) 在 Windows x86_64 和 Ubuntu x86_64 上使用 VP9/H.264 硬件加速器功能

### 4K 30fps 直播

Momo 利用硬件编码器，可通过 WebRTC 实现 4K 60fps 的传输

### 网络同步直播

Momo 支持在 Sora 模式下使用多画质同传。

### 通过数据通道读写串行数据

Momo 可利用数据通道直接对串口进行读写。适用于优先考虑低延迟而非可靠性的场景。

### 利用 SDL 接收音频和视频

使用 Momo 的 GUI 环境时，可以使用 Simple DirectMedia Layer 接收音频和视频。

### 对AV1的支持

支持 AV1 发送和接收。

### 客户端证书支持

Momo 支持在 Sora 模式下使用客户端证书。


## 直播

[WebRTC Native Client Momo 和 Jetson Nano 4K@30 直播](https://www.youtube.com/watch?v=z05bWtsgDPY)

## OpenMomo 项目

OpenMomo 是一个开源项目，公开 WebRTC Native Client Momo 并持续进行开发。我们希望 WebRTC 不仅限于浏览器或智能手机，还能用于各种用途。

详情请见下文。

[OpenMomo 项目](https://gist.github.com/voluntas/51c67d0d8ce7af9f24655cee4d7dd253)

有关 Momo 的推文已汇总如下。

https://gist.github.com/voluntas/51c67d0d8ce7af9f24655cee4d7dd253#twitter

## 已知问题

[已知问题解决方针](https://github.com/shiguredo/momo/issues/89)

## 二进制提供

可从以下网址下载。

https://github.com/shiguredo/momo/releases

## 动作环境

- Raspberry Pi OS (64bit) ARMv8
    - Raspberry Pi 4 树莓派 4
    - Raspberry Pi 3 树莓派 3
    - Raspberry Pi 2
    - Raspberry Pi Zero 2 W 树莓派 Zero 2 W
- Raspberry Pi OS (32bit) ARMv7
    - Raspberry Pi 4 树莓派 4
    - Raspberry Pi 3 树莓派 3
    - Raspberry Pi 2
    - Raspberry Pi Zero 2 W 树莓派 Zero 2 W
- Raspberry Pi OS (32bit) ARMv6
    - Raspberry Pi Zero 树莓派 Zero
    - Raspberry Pi 1 树莓派 1
- Ubuntu 20.04 x86_64
- Ubuntu 22.04 x86_64
- Ubuntu 20.04 ARMv8 Jetson
    - [NVIDIA Jetson AGX Orin](https://www.nvidia.com/ja-jp/autonomous-machines/embedded-systems/jetson-orin/)
    - [NVIDIA Jetson AGX Xavier](https://www.nvidia.com/ja-jp/autonomous-machines/embedded-systems/jetson-agx-xavier/)
    - [NVIDIA Jetson Xavier NX](https://www.nvidia.com/ja-jp/autonomous-machines/embedded-systems/jetson-xavier-nx/)
- macOS 12 arm64 及更高版本
- Windows 10.1809 x86_64 及更高版本

### 不支持

- macOS x86_64
- Ubuntu 20.04 ARMv8 Jetson
    - [NVIDIA Jetson Orin Nano](https://www.nvidia.com/ja-jp/autonomous-machines/embedded-systems/jetson-orin/)
        - Jetson Orin Nano 没有搭载 HWA，所以不支持
- Ubuntu 18.04 ARMv8 Jetson
    - [NVIDIA Jetson Nano](https://www.nvidia.com/ja-jp/autonomous-machines/embedded-systems/jetson-nano/)
    - [NVIDIA Jetson Xavier NX](https://www.nvidia.com/ja-jp/autonomous-machines/embedded-systems/jetson-xavier-nx/)
    - [NVIDIA Jetson AGX Xavier](https://www.nvidia.com/ja-jp/autonomous-machines/embedded-systems/jetson-agx-xavier/)

## 使用说明

想要使用 Momo 的人请阅读 [USE.md](doc/USE.md)。

## 构建

- 想要构建 Linux 版 Momo 的人请阅读 [BUILD_LINUX.md](doc/BUILD_LINUX.md)
- 想要构建 macOS 版 Momo 的人请阅读 [BUILD_MACOS.md](doc/BUILD_MACOS.md)
- 想要构建 Windows 版 Momo 的人请阅读 [BUILD_WINDOWS.md](doc/BUILD_WINDOWS.md)

## 打包

想要创建包的人请阅读 [PACKAGE.md](doc/PACKAGE.md)。

## FAQ

常见问题请阅读[FAQ.md](doc/FAQ.md)。

## 许可证

Apache License 2.0

```
Copyright 2015-2024, tnoho (Original Author)
Copyright 2018-2024, Shiguredo Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```

## 优先实施

优先实施是指，对于已签约 Sora 许可证的客户，可付费提前实施 Momo 预计实施的功能。

- Windows 版 OSS 化
    - [様斯洛斯网络株式会社](http://www.sloth-networks.co.jp) 
- WebRTC 的统计信息支持
    - 目前公司名称保密
- Momo NVIDIA VIDEO CODEC SDK 适用于 Windows
    - [様斯洛斯网络株式会社](http://www.sloth-networks.co.jp) 
- Momo NVIDIA VIDEO CODEC SDK 适用于 Linux
    - [株式会社オプティム](https://www.optim.co.jp/) 
- Windows/Linux 版屏幕截图支持
    - [スロースネットワークス株式会社](http://www.sloth-networks.co.jp) 

### 优先实现的功能列表

**详情请通过 Discord 或邮件联系我们**

- リリース
- Raspberry Pi カメラの Raspberry Pi OS (32bit) 対応
- H.265 (HEVC) HWA 支持
    - macOS Video Toolbox
    - NVIDIA Jetson
        - Ubuntu 20.04
        - Ubuntu 22.04
    - NVIDIA Video Codec SDK
        - Windows
        - Ubuntu
- OpenH264 支持
    - Windows
    - Ubuntu
- oneVPL 支持
- AV1 支持
    - Windows
- Windows / macOS 署名対応

## Momo についての電子書籍

Momo の原作者である @tnoho が書いた Momo のノウハウが沢山詰まった本が販売されています。

[WebRTC をブラウザ外で使ってブラウザでできることを増やしてみませんか?\(電子版\) \- でんでんらぼ \- BOOTH](https://tnoho.booth.pm/items/1572872)

## 支持

### Discord

- **不支持**
- 建议
- 欢迎反馈

最新情况等在 Discord 上共享。问题和咨询也仅在 Discord 上接受。

https://discord.gg/shiguredo

### 错误报告

请到 Discord 上联系我。

### 付费技术支持

WebRTC Native Client 的付费技术支持合同适用于已签订 WebRTC SFU Sora 许可合同的客户。

- Momo 的技术支持
- OSS 公開前提での Momo への機能追加

## H.264 许可费用

仅使用 H.264 硬件编码器的 Momo 单独发行无需支付许可费用，但与硬件捆绑发行时需要支付许可费用。

但是，Raspberry Pi 中的 H.264 许可证已包含在硬件费用中，因此在分发时无需支付许可证费用。

详情请咨询 [MPEG LA](https://www.mpegla.com/)。

- RRaspberry Pi 硬件编码器的许可费用已包含在 Raspberry Pi 的价格中
      - https://www.raspberrypi.org/forums/viewtopic.php?t=200855
- Apple 的许可费用仅限于个人使用和非商业用途，因此在分发时需要与团体另行签订合同
      - https://store.apple.com/Catalog/Japan/Images/EA0270_QTMPEG2.html
- AMD 显卡硬件编码器的授权费用需另行与团体签订合同
      - https://github.com/GPUOpen-LibrariesAndSDKs/AMF/blob/master/amf/doc/AMF_API_Reference.pdf
- NVIDIA 显卡硬件编码器需另行与团体签约付费
    - https://developer.download.nvidia.com/designworks/DesignWorks_SDKs_Samples_Tools_License_distrib_use_rights_2017_06_13.pdf
- NVIDIA Jetson Nano 的硬件编码器需要额外付费，并需要与相关组织签订合同
    - [NVIDIA Jetson Nano 搭載の H\.264/H\.265 ハードウェアエンコーダーのライセンスについて](https://medium.com/@voluntas/nvidia-jetson-nano-%E6%90%AD%E8%BC%89%E3%81%AE-h-264-h-265-%E3%83%8F%E3%83%BC%E3%83%89%E3%82%A6%E3%82%A7%E3%82%A2%E3%82%A8%E3%83%B3%E3%82%B3%E3%83%BC%E3%83%80%E3%81%AE%E3%83%A9%E3%82%A4%E3%82%BB%E3%83%B3%E3%82%B9%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6-ca207af302ee)
- 英特尔快速同步视频硬件编码器许可费用另计，需要与组织签订合同
    - [QuickSync \- H\.264 patent licensing fees \- Intel Community](https://community.intel.com/t5/Media-Intel-oneAPI-Video/QuickSync-H-264-patent-licensing-fees/td-p/921396)
