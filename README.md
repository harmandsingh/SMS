# ServerMonitoringSystem
Server Monitoring System written in C.

Part 1:
This project contains a simulator that generates log files for each server.
The monitoring system has a total of 1000 servers and each server has 2 CPUs.
Each server generates a log for CPU usage every minute which is of the following format:

Timestamp IP cpu_id usage
1414689783 192.168.1.10 0 87
1414689783 192.168.1.10 1 90
1414689783 192.168.1.11 1 93

A simulator will be used to generate the logs for one day, say 2014-10-31. One file will be generated for each server and stored in a directory.

Part 2:
