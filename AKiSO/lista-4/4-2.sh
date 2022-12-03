#!/bin/bash

function appendString(){
    echo "123";
}

utemp=$(mktemp);
dtemp=$(mktemp);
echo "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0" > $utemp;
echo "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0" > $dtemp;


function cleanup(){
    printf "\nDeleting temp files\n";
    rm $utemp $dtemp;
}

trap cleanup EXIT;
while :
do
    {
        rbStart=`awk 'BEGIN {sum=0} /:/ {sum=sum=$2} END {print sum}' /proc/net/dev`;   #Bytes received at start of the loop
        sbStart=`awk 'BEGIN {sum=0} /:/ {sum=sum=$10} END {print sum}' /proc/net/dev`;   #sent

        cpuStart=`awk '/cpu[0-9]+/ {print($0)}' /proc/stat`;

        sleep 0.8;
        tput clear;
        #tput cup 0,0;  #Altarnative to clear that puts cursor to position 0,0

        rbEnd=`awk 'BEGIN {sum=0} /:/ {sum=sum=$2} END {print sum}' /proc/net/dev`;     #Bytes received at end of the loop
        sbEnd=`awk 'BEGIN {sum=0} /:/ {sum=sum=$10} END {print sum}' /proc/net/dev`;     #sent

        battery=`grep POWER_SUPPLY_CAPACITY= < /sys/class/power_supply/BAT0/uevent | cut -d "=" -f 2`;
        printf "Battery ${battery} 50" | awk -f "/home/most/Dokumenty/bash/akiso-4-2/script-1.awk";   # Prints battery
        printf "\n\n"

        cpuEnd=`awk '/cpu[0-9]+/ {print($0)}' /proc/stat`;
        readarray -t cpuStartArr <<< "$cpuStart";
        readarray -t cpuEndArr <<< "$cpuEnd";
        coreCount=${#cpuStartArr[@]};
        for (( i=0; i<coreCount; i++)); do
            start=(${cpuStartArr[i]});
            end=(${cpuEndArr[i]});
            usage=$(( 100 - (end[4]-start[4])*100/(end[1]-start[1]+end[2]-start[2]+end[3]-start[3]+end[4]-start[4]+end[5]-start[5]+end[6]-start[6]+end[7]-start[7]+end[8]-start[8]+end[9]-start[9]) ));
            mhz=$(( `cat /sys/devices/system/cpu/cpu$i/cpufreq/scaling_cur_freq` / 1000000))
            printf "${start[0]} $usage 20" | awk -f "/home/most/Dokumenty/bash/akiso-4-2/script-1.awk";   # Printing cpu info in rows of 2
            if [ $((i%2)) -eq 1 ]; then
                printf "\n";
            fi;
        done | column -t;   # if makes it split cores into 2 columns

        printf "\n";
        echo "$(awk 'BEGIN{ORS=" "}/MemTotal*|MemFree*|MemAvailable*/ {print $2}' < /proc/meminfo)50" | awk -f "/home/most/Dokumenty/bash/akiso-4-2/script-2.awk";  # Printing memory info

        printf "\n\n";
        bytesReceived=$(numfmt --to iec --format "%8.0f" $(( rbEnd - rbStart )));    #Bytes received in a second
        bytesSent=$(numfmt --to iec --format "%8.0f" $(( sbEnd - sbStart )));    #sent
        appendString $uploadRecords $bytesSent
        printf "${uploadRecords}\n"
        # {
        #     printf "Bytes sent:,${bytesSent}B\n"
        #     printf "${uploadRecords}\n"
        #     printf "Bytes received:,${bytesReceived}B\n"
        #     printf "${downloadRecords}\n"
        # } | column -t -s,;
        printf "\nUptime: ";
        echo $(cat /proc/uptime | awk '// {print ($1-$1%3600)/3600 "h " ($1%3600)/60-($1/60%1) "m " ($1%60)-($1%1) "s"}');   # Printing Uptime
        printf "Load Average: %s %s %s\n" $(awk '// {print $1 " " $2 " " $3}' < /proc/loadavg); # Printing average load
    } | column --table-empty-lines -s,  # column makes text after its processed all at once
done
