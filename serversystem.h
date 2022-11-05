/* header file for the server monitoring system, contains the definition of the server system struct along with other needed constants */
#ifndef SERVER_SYSTEM_H
#define SERVER_SYSTEM_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define NO_OF_SERVERS 1000
#define MINUTES_IN_DAY 1440
#define MAX_CPU_USAGE 100

typedef struct server_system_t
{
    int unix_time;
    uint16_t ip[4];
    uint16_t cpu1;
    uint16_t cpu2;
    uint16_t cpu1_usage;
    uint16_t cpu2_usage;
} server_system_t;

#endif