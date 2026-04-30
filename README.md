# fbplay
A minimal framebuffer player for raw RGB565 video on Linux (`/dev/fb0`), tested on GL.iNet Mudi 7.

---

## Requirements

* Linux system with framebuffer device (`/dev/fb0`)
* Matching framebuffer parameters (resolution and pixel format)
* Raw video file (RGB565)

---

## Build

### Compile on device

```bash
opkg update
opkg install gcc
gcc fbplay.c -o fbplay
chmod +x fbplay
```

---

## Usage

```bash
./fbplay file.raw [fps]
```

* `file.raw`: raw video file (RGB565, matching framebuffer resolution)
* `fps`: optional, default is 30

### Example

```bash
./fbplay video.raw
./fbplay video.raw 30
```

---

## Convert Video (FFmpeg)

Convert a video into raw framebuffer format using FFmpeg:

```bash
ffmpeg -i badapple.mp4 -vf "transpose=1,scale=240:320:flags=lanczos,fps=30" -pix_fmt rgb565le -f rawvideo badapple.raw
```

Adjust resolution and FPS according to your device.

---

## Notes

* Player uses time-based frame pacing to reduce drift

---

## Demo

[https://www.bilibili.com/video/BV1Gj9iBdEE5/](https://www.bilibili.com/video/BV1Gj9iBdEE5/)

## License

MIT
