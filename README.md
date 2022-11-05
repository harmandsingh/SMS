# ServerMonitoringSystem

## Server Monitoring System written in C.

### Part 1: Logs Generator

This project contains a simulator that generates a log file for the monitoring system. The system has a total of 1000 servers and each server has 2 CPUs. Each server generates a log for CPU usage every minute which is of the following format:

- Timestamp IP cpu_id usage
- 1414689783 192.168.1.10 0 87
- 1414689783 192.168.1.10 1 90
- 1414689783 192.168.1.11 1 93

### Part 2: Interactive Query Tool

There is also a query tool included, which can be used to query the logs. This interactive tool supports two commands:

1. QUERY IP CPU_ID START_DATE START_TIME END_DATE END_TIME
   IP range: 192.168.1.1 to 192.168.1.255, 192.168.2.1 to 192.168.2.255, 192.168.3.1 to 192.168.3.255, and 192.168.4.1 to 192.168.4.235
   CPU_ID: 0 or 1
   DATE: 2014-10-31
   TIME: 00:00:00 to 23:59:00
2. EXIT

- Any other command will display the help options menu.
