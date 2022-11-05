#include "serversystem.h"

/* main method of the server system
   argv[1] contains the DATA_PATH along with the filename, logs will be stored in directory DATA_PATH/logs.txt */
int main(int argc, char *argv[])
{
    // rawtime will hold the unix time for the date: 2014-10-31
    time_t rawtime;
    struct tm timeinfo;

    // setting the date and time to 2014-10-31 00:00:00
    int year = 2014;
    int month = 10;
    int day = 31;
    int hour = 0;
    int min = 0;
    int sec = 0;

    // initialize an array of 1000 server systems objects
    server_system_t s_system[NO_OF_SERVERS];
    server_system_t *array_ptr = s_system;
    FILE *fptr;

    if (argc < 2)
    {
        printf("Error: Please provide the output DATA_PATH\nUsage: ./generate DATA_PATH\n");
        return 0;
    }

    if (array_ptr == NULL)
    // if the array pointer points to null, enough memory could not be allocated for the array
    {
        printf("Error: Could not allocate memory");
        return 0;
    }

    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = min;
    timeinfo.tm_sec = sec;
    // since the daylight savings time is in effect
    timeinfo.tm_isdst = 1;

    // gets the date and time 2014-10-31 00:00:00 in epoch time
    rawtime = mktime(&timeinfo);
    // converts rawtime to type long
    int unix_timestamp = (long)rawtime;

    // initializing the srand function
    srand(time(0));

    /* file pointer opens the file with write privileges if it already exists, otherwise creates the file */
    fptr = fopen(argv[1], "w");
    // prints the first title line to the file
    char *title = "Timestamp        IP      cpu_id  usage";
    fprintf(fptr, "%s\n", title);

    for (int i = 0; i < MINUTES_IN_DAY; i++)
    {
        /* only the third and fourth numbers of the ip address are incremented, first and second numbers are set to 192 and 168 respectively */
        uint16_t ip3 = 1;
        uint16_t ip4 = 1;

        for (int j = 0; j < NO_OF_SERVERS; j++)
        {
            s_system[j].unix_time = unix_timestamp;

            s_system[j].cpu1 = 0;
            s_system[j].cpu2 = 1;

            s_system[j].cpu1_usage = rand() % (MAX_CPU_USAGE + 1);
            s_system[j].cpu2_usage = rand() % (MAX_CPU_USAGE + 1);

            s_system[j].ip[0] = 192;
            s_system[j].ip[1] = 168;

            if (ip4 <= 255)
            {
                s_system[j].ip[2] = ip3;
                s_system[j].ip[3] = ip4;
                ip4++;
            }
            else
            {
                // increment ip3 and set ip4=1 when ip4>255
                ip4 = 1;
                ip3++;
                s_system[j].ip[2] = ip3;
                s_system[j].ip[3] = ip4;
                ip4++;
            }

            // print the cpu usage to the opened file

            fprintf(fptr, "%d    %d.%d.%d.%d    %d     %d\n", s_system[j].unix_time, s_system[j].ip[0], s_system[j].ip[1], s_system[j].ip[2], s_system[j].ip[3], s_system[j].cpu1, s_system[j].cpu1_usage);

            fprintf(fptr, "%d    %d.%d.%d.%d    %d     %d\n", s_system[j].unix_time, s_system[j].ip[0], s_system[j].ip[1], s_system[j].ip[2], s_system[j].ip[3], s_system[j].cpu2, s_system[j].cpu2_usage);
        }
        // increment timestamp by 1 minute or 60 seconds
        unix_timestamp = unix_timestamp + 60;
    }

    fclose(fptr);
    return 0;
}