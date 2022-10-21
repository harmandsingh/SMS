#include "serversystem.h"

int main(int argc, char *argv[]){
    time_t rawtime;
    struct tm *timeinfo;
    
    server_system_t s_system[NO_OF_SERVERS];
    server_system_t* array_ptr = s_system;
    FILE *fptr;

    if(argc < 2){
        printf("Error: Please provide the output DATA_PATH\nUsage: ./generate DATA_PATH\n");
        return 0;
    }

    if(array_ptr == NULL){
        printf("Error: Could not allocate memory");
        return 0;
    }

    fptr = fopen("logs.txt", "w");
    char *title = "Timestamp        IP      cpu_id  usage";
    time(&rawtime);
    fprintf(fptr, "%s\n", title);
    
    for (int i = 0; i < 1440; i++)
    {
        uint16_t ip3 = 1;
        uint16_t ip4 = 1;

        for (int j = 0; j < NO_OF_SERVERS; j++)
        {
            s_system[j].unix_time = rawtime;

            s_system[j].cpu1 = 0;
            s_system[j].cpu2 = 1;

            s_system[j].cpu1_usage = 50;
            s_system[j].cpu2_usage = 75;

            s_system[j].ip[0] = 192;
            s_system[j].ip[1] = 168;

            if (ip4 <= 255)
            {
                s_system[j].ip[2] = ip3;
                s_system[j].ip[3] = ip4;
                ip4++;
            }
            else{
                ip4 = 1;
                ip3++;
                s_system[j].ip[2] = ip3;
                s_system[j].ip[3] = ip4;
                ip4++;
            }

            fprintf(fptr, "%ld    %d.%d.%d.%d    %d     %d\n", rawtime,s_system[j].ip[0],s_system[j].ip[1],s_system[j].ip[2],s_system[j].ip[3],s_system[j].cpu1, s_system[j].cpu1_usage);

            fprintf(fptr, "%ld    %d.%d.%d.%d    %d     %d\n", rawtime,s_system[j].ip[0],s_system[j].ip[1],s_system[j].ip[2],s_system[j].ip[3],s_system[j].cpu2, s_system[j].cpu2_usage);
        }
        
        rawtime+=60;
    }

    fclose(fptr);
    return 0;
}