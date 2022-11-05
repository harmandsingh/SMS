#! /bin/bash
# Bash script to generate the logs file

# Checks that the input DATA_PATH is not empty and not a " "
if [ ! -z "$1" ] && [ "$1" != " " ]; then

    # Creates the specified DATA_PATH if it doesn't already exist
    if [ ! -d "$1" ]; then
        mkdir -p $1
        printf "Creating the directory\n"
    fi

    # Compiles the source code
    gcc serversystem.c
    printf "Compiling the source code\n"

    # Runs the executable file
    printf "Generating the logs\n"
    ./a.out $1/logs.txt
    printf "Successfully generated the logs\n"

# Prints an error if the DATA_PATH is wrong or missing
else
    printf "Error: Please provide the output DATA_PATH\nUsage: ./generate DATA_PATH\n"
fi
