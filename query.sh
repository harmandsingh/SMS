#! /bin/bash
# Bash script to query the logs file

# Checks if the DATA_PATH exists and is not empty
if [ -z "$1" ] || [ "$1" == " " ]; then
    printf "Error: Please provide a correct DATA_PATH\nUsage: ./query.sh DATA_PATH\n"
    exit
fi

# Two commands supported by the interactive query tool
query_command="QUERY"
exit_command="EXIT"

# Variable to keep track of when to exit the loop
loop=0
while [ $loop -eq 0 ]; do
    printf ">"
    read LOG_QUERY
    # Separates the command from the arguments
    IFS=" " read -r command ip cpu_id start_date start_time end_date end_time <<<"$LOG_QUERY"

    # Ignore case while matching commands
    shopt -s nocasematch

    # If the command provided is QUERY command
    if [[ $command == $query_command ]]; then
        # Checks if the given Query command syntax is valid
        if [ -z "$command" ] || [ -z "$ip" ] || [ -z "$cpu_id" ] || [ -z "$start_date" ] || [ -z "$start_time" ] || [ -z "$end_date" ] || [ -z "$end_time" ]; then
            printf "Error: Invalid QUERY command syntax\nSyntax: QUERY IP CPU_ID START_DATE START_TIME END_DATE END_TIME\nPlease type help or HELP for more help!\n"
            continue
        fi

        # Converts the given start time to unix time
        start_utime=$(date -j -f "%Y-%m-%d %H:%M:%S" "$start_date $start_time" "+%s")
        # Converts the given start time to unix time
        end_utime=$(date -j -f "%Y-%m-%d %H:%M:%S" "$end_date $end_time" "+%s")

        # variable to ensure cpu usage is printed only once
        print_usage=0
        # variable to ensure that correct date and time is provided
        found_results=0

        for ((i = $start_utime; i < $end_utime; i = i + 60)); do
            # Using * in grep to find zero or more occurences of ip and cpu_id
            query_result=$(grep "$i * $ip * $cpu_id" $1/logs.txt)
            if [ -z "$query_result" ]; then
                # if the query_result is empty
                printf "No results found: Could be a syntax error.\nSyntax: QUERY IP CPU_ID START_DATE START_TIME END_DATE END_TIME\nPlease type help or HELP for more help!\n"
                break
            fi

            found_results=1
            IFS=" " read result_utime result_ip result_cpu_id result_usage <<<"$query_result"

            if [ $print_usage -eq 0 ]; then
                printf "CPU$result_cpu_id usage on $result_ip\n"
                print_usage=1
            fi

            # print the timestamp and cpu usage
            result_readabletime=$(date -j -f "%s" "$result_utime" "+%Y-%m-%d %H:%M:%S")
            printf "($result_readabletime,$result_usage),"
        done

        # if no results are found, could be invalid date and time input
        if [ $found_results -eq 0 ]; then
            printf "No results found: Please check the START_DATE and START_TIME.\nSyntax: QUERY IP CPU_ID START_DATE START_TIME END_DATE END_TIME\nPlease type help or HELP for more help!\n"
        fi
        printf "\n"

    elif
        [[ $command == $exit_command ]]
    then
        # exit the loop on exit_command
        loop=1

    else
        # display help options if the user input is anything else
        printf "Possible commands are:\n1. QUERY IP CPU_ID START_DATE START_TIME END_DATE END_TIME\nIP range: 192.168.1.1 to 192.168.1.255, 192.168.2.1 to 192.168.2.255, 192.168.3.1 to 192.168.3.255, and 192.168.4.1 to 192.168.4.235\nCPU_ID: 0 or 1\nDATE: 2014-10-31\nTIME: 00:00:00 to 23:59:00\n2. EXIT\n"
    fi
done
