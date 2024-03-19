BEGIN{
    ORS=""
    WHITE="\033[38:5:15m"
    GRAY="\033[38:5:8m"
    GREEN="\033[38:5:2m"
    YELLOW="\033[38:5:3m"
    RESET="\033[0m"
}
END{
    #$1 - mem total, $2 - mem free., $3 - mem avail, $4 - length
    printf("Free memory:%3.0f%",$2/$1*100)
    print WHITE " ▐";
    for(i=1;i<=$4;i++)
        if(i <= ($2/$1)*$4)
            print GREEN "█";
        else if(i <= ($3/$1)*$4)
            print YELLOW "█"
        else
            print GRAY "🗆";
    print WHITE "▌" RESET " ";
}
