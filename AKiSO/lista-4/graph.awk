BEGIN{
    ORS = "";
    GRAY="\033[38:5:8m"
    GREEN="\033[38:5:2m"
    RESET="\033[0m"
}
{
    max=$1;
    for(i=1;i<=20;i++)
        if($i > max)
            max=$i;
    for(y=1;y<=10;y++){
        for(x=1;x<=20;x++){
            if($x > (10-y)/10*max)
                print GREEN "█";
            else
                print GRAY "█";
        }
        number=int(max*(11-y)/10);
        if(number > 1000){
            number/=1000;
            if(number > 1000){
                number/=1000;
                print RESET " " number " MB\n"; 
            }else{
                print RESET " " number " kB\n"; 
            }
        }else{
            print RESET " " number " B\n"; 
        }
    }
}