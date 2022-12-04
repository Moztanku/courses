#!/bin/bash

LGREEN_F="\033[38;5;10m"
LYELLOW_F="\033[38:5:11m"

DBLACK_B="\033[48:5:0m"
DGREEN_B="\033[48;5;2m"
DYELLOW_B="\033[48;5;3m"
DBLUE_B="\033[48;5;4m"

RESET="\033[0m"

WIDTH=40;
HEIGHT=15;

function drawBackground(){
    COLOR=$1
    printf $COLOR
    tput clear;
    printf $RESET
}

function drawBorder(){
    COLOR=$1
    printf $COLOR
    x=$(( (COLUMNS-WIDTH)/2 ))
    y=$(( (LINES-HEIGHT)/2 ))
    tput cup $y $x; printf "████████████████████  ████████████████████"; y=$(( y+1 ));
    tput cup $y $x; printf "█                                        █"; y=$(( y+1 ));
    tput cup $y $x; printf "█ ███              ████                  █"; y=$(( y+1 ));
    tput cup $y $x; printf "█                                        █"; y=$(( y+1 ));
    tput cup $y $x; printf "███                ████                  █"; y=$(( y+1 ));
    tput cup $y $x; printf "█                                        █"; y=$(( y+1 ));
    tput cup $y $x; printf "█ ███              ████                  █"; y=$(( y+1 ));
    tput cup $y $x; printf "█                  █  █                  █"; y=$(( y+1 ));
    tput cup $y $x; printf "███                ████                  █"; y=$(( y+1 ));
    tput cup $y $x; printf "█                                        █"; y=$(( y+1 ));
    tput cup $y $x; printf "█ ███              ████                  █"; y=$(( y+1 ));
    tput cup $y $x; printf "█     █                                  █"; y=$(( y+1 ));
    tput cup $y $x; printf "███ ███            ████                  █"; y=$(( y+1 ));
    tput cup $y $x; printf "█                                        █"; y=$(( y+1 ));
    tput cup $y $x; printf "█ ███ █            ████                  █"; y=$(( y+1 ));
    tput cup $y $x; printf "█     █                                  █"; y=$(( y+1 ));
    tput cup $y $x; printf "████████████████████  ████████████████████";
    printf $RESET
}

function drawPacman(){
    x=$(( (COLUMNS-WIDTH)/2+$1  ))
    y=$(( (LINES-HEIGHT)/2+$2 ))
    tput cup $y $x
    printf "${LYELLOW_F}ᗧ${RESET}"
}
function movePacman(){
    dir=$1
    if [ $dir -e 0 ]; then
        $pacman_x=$(( pacman_x+1 ))
    fi;
    if [ $dir -e 1 ]; then
        $pacman_x=$(( pacman_x-1 ))
    fi;
    if [ $dir -e 2 ]; then
        $pacman_y=$(( pacman_y+1 ))
    fi;
    if [ $dir -e 3 ]; then
        $pacman_y=$(( pacman_y-1 ))
    fi;
}

drawBackground $DBLUE_B;
pacman_x=10;
pacman_y=10;
pacman_dir=0; #0 - right, 1 - left, 2 - down, 3 - up. 
while true
do
    timeStart=$(date +%s%N);
    drawBorder $LGREEN_F;
    drawPacman $pacman_x $pacman_y;

    tput cup 0 0;
    timeEnd=$(date +%s%N);
    deltaTime=$(( (timeEnd-timeStart) ))  # Time elapsed since timeStart in nanoseconds
    sleep $(echo $deltaTime | awk '{ print 0.5-$1/1000000000 }');
done;