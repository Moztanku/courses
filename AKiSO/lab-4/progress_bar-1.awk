BEGIN{
    ORS=""
    WHITE="\033[38:5:15m"
    GRAY="\033[38:5:8m"
    GREEN="\033[38:5:2m"
    RESET="\033[0m"
}
/[0-9]+/ {
    print($1 ": ")
    print($2 "% " num WHITE "▐");
    for(i=1;i<=$3;i++)
        if(i <= $2/(100/$3))
            print GREEN "█";
        else
            print GRAY "🗆";
    print WHITE "▌" RESET " ";
}
