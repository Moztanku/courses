#!/bin/bash
pat='^/proc/[0-9]+'
{
echo "PPID?PID?COMM?STATE?TTY?RSS?PGID?SID?PROC";
for f in /proc/*; do
    if [[ $f =~ $pat  ]]; then
        str=`cat $f/stat`;
        comm=`echo $str | cut -d "(" -f2 | cut -d ")" -f1`;

        strArr=(${str//$comm/""});
        ppid=${strArr[3]};
        pid=${strArr[0]};
        state=${strArr[2]};
        tty=${strArr[6]};
        rss=${strArr[23]};
        pgid=${strArr[7]};
        sid=${strArr[6]};
        fileCount=`sudo ls $f/fd/ | wc -l`;
        echo "$ppid?$pid?$comm?$state?$tty?$rss?$pgid?$sid?$fileCount";
    fi
done
} | column -t -s "?"