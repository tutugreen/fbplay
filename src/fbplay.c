#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 240
#define HEIGHT 320
#define BPP 2

// Get current time in microseconds
long get_time_us() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000L + ts.tv_nsec / 1000;
}

int main(int argc, char *argv[]) {
    printf("tutugreen @ 2026-05-01\n");

    if (argc < 2) {
        printf("Usage: %s file.raw [fps]\n", argv[0]);
        return 1;
    }

    // Default FPS = 30
    int fps = 30;

    // Parse optional FPS argument
    if (argc >= 3) {
        fps = atoi(argv[2]);
        if (fps <= 0) fps = 30;
    }

    printf("FPS: %d\n", fps);

    int fb = open("/dev/fb0", O_RDWR);
    int vid = open(argv[1], O_RDONLY);

    size_t framesize = WIDTH * HEIGHT * BPP;

    char *fbp = mmap(0, framesize, PROT_WRITE, MAP_SHARED, fb, 0);
    char buffer[framesize];

    long frame_interval = 1000000L / fps;

    long start_time = get_time_us();
    int frame_count = 0;

    while (read(vid, buffer, framesize) == framesize) {
        memcpy(fbp, buffer, framesize);

        frame_count++;

        long target_time = start_time + frame_count * frame_interval;
        long now = get_time_us();

        if (target_time > now) {
            usleep(target_time - now);
        }
        // If late, skip sleep (auto compensation)
    }

    munmap(fbp, framesize);
    close(fb);
    close(vid);
}
