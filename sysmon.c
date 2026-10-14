#include <stdio.h>
#include <unistd.h>

float get_temp(const char *path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return -1.0f;
    }

    int read_temp = 0;
    fscanf(file, "%d", &read_temp);
    fclose(file);

    return read_temp / 1000.0f;
}

int main(void)
{
    while (1) {
        float cpu_temp = get_temp("/sys/class/hwmon/hwmon1/temp1_input");
        float gpu_temp = get_temp("/sys/class/hwmon/hwmon0/temp1_input");

        printf("\rCPU: %.1f°C | GPU: %.1f°C  ", cpu_temp, gpu_temp);
        fflush(stdout);

        sleep(1);
    }

    return 0;
}