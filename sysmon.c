#include <glob.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    glob_t result;

    glob("/sys/class/hwmon/hwmon*", 0, NULL, &result);

    while (1) {
        printf("\033[H");
        printf("SYSTEM MONITORING (CTRL+C for Exit)\n");

        for (size_t i = 0; i < result.gl_pathc; i++) {
            char name_path[256];
            char temp_path[256];

            snprintf(name_path, sizeof(name_path), "%s/name", result.gl_pathv[i]);
            snprintf(temp_path, sizeof(temp_path), "%s/temp1_input", result.gl_pathv[i]);

            FILE *f_name = fopen(name_path, "r");
            FILE *f_temp = fopen(temp_path, "r");

            if (f_name && f_temp) {
                char dev_name[64];
                int raw_temp = 0;

                fscanf(f_name, "%63s", dev_name);
                fscanf(f_temp, "%d", &raw_temp);

                float celsius = raw_temp / 1000.0;

                printf("Device: %-5s | Temperature %.1f °C\n", dev_name, celsius);
            }

            if (f_name)
                fclose(f_name);
            if (f_temp)
                fclose(f_temp);
        }
        usleep(100000);
    }

    globfree(&result);

    return 0;
}