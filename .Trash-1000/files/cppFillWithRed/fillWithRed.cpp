#include <fcntl.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

#define WIDTH 320
#define HEIGHT 240
#define BPP 2 // bytes per pixel (RGB565)

int main()
{
    int fb = open("/dev/fb0", O_RDWR);
    if (fb < 0)
        return 1;

    size_t fb_size = WIDTH * HEIGHT * BPP;

    uint16_t *buf = (uint16_t *)mmap(NULL, fb_size,
                                     PROT_READ | PROT_WRITE,
                                     MAP_SHARED, fb, 0);

    if (buf == MAP_FAILED)
    {
        close(fb);
        return 1;
    }

    // Choose color in RGB565
    // Example: solid red (R=31,G=0,B=0)
    uint16_t color = (0 << 11) | (31 << 5) | 0;

    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        buf[i] = color;
    }

    munmap(buf, fb_size);
    close(fb);
    return 0;
}
