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

BORDER=("█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" " " " " "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" " " " " " " " " " " " " " " " " " " " " " " " " "█" " " " " " " " " " " " " " " " " " " " " " " " " " " " " "█" " " " " " " " " " " " " " " " " " " " " " " " " "█" "█" " " "█" "█" "█" " " "█" " " "█" "█" "█" "█" " " "█" " " "█" "█" "█" " " "█" "█" "█" "█" " " "█" "█" "█" " " "█" " " "█" "█" "█" "█" " " "█" " " "█" "█" "█" " " "█" "█" " " " " " " " " " " "█" " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " "█" " " " " " " " " " " "█" "█" "█" "█" " " "█" "█" "█" " " "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" " " "█" "█" "█" "█" " " "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" " " "█" "█" "█" " " "█" "█" "█" "█" " " " " " " " " " " "█" " " "█" " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " "█" " " "█" " " " " " " " " " " "█" "█" " " "█" "█" "█" " " " " " " " " " " "█" "█" "█" "█" "█" "█" "█" "█" " " "█" "█" "█" "█" " " "█" "█" "█" "█" "█" "█" "█" "█" " " " " " " " " " " "█" "█" "█" " " "█" "█" " " " " " " " " " " "█" " " "█" " " "█" " " " " " " " " " " " " "█" " " "█" " " " " "█" " " "█" " " " " " " " " " " " " "█" " " "█" " " "█" " " " " " " " " " " "█" "█" "█" "█" " " "█" "█" "█" " " "█" " " " " " " "█" "█" "█" "█" " " " " " " "█" "█" "█" "█" " " " " " " "█" "█" "█" "█" " " " " " " "█" " " "█" "█" "█" " " "█" "█" "█" "█" " " " " " " " " " " "█" " " "█" " " "█" " " " " " " " " " " " " "█" " " " " " " " " " " " " "█" " " " " " " " " " " " " "█" " " "█" " " "█" " " " " " " " " " " "█" "█" " " "█" "█" "█" " " " " " " " " " " "█" "█" "█" "█" "█" "█" "█" "█" " " "█" "█" "█" "█" " " "█" "█" "█" "█" "█" "█" "█" "█" " " " " " " " " " " "█" "█" "█" " " "█" "█" " " " " " " " " " " "█" " " "█" " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " "█" " " "█" " " " " " " " " " " "█" "█" "█" "█" " " "█" "█" "█" " " "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" " " "█" "█" "█" "█" " " "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" " " "█" "█" "█" " " "█" "█" "█" "█" " " " " " " " " " " "█" " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " "█" " " " " " " " " " " "█" "█" " " "█" "█" "█" " " "█" " " "█" "█" "█" "█" " " "█" " " "█" "█" "█" " " "█" "█" "█" "█" " " "█" "█" "█" " " "█" " " "█" "█" "█" "█" " " "█" " " "█" "█" "█" " " "█" "█" " " " " " " " " " " " " " " " " " " " " " " " " "█" " " " " " " " " " " " " " " " " " " " " " " " " " " " " "█" " " " " " " " " " " " " " " " " " " " " " " " " "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" " " " " "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█")
ORBS_X=(1 2 3 4 5 6 7 8 9 10 11 12 14 15 16 17 18 19 20 21 22 23 24 25 26 27 29 30 31 32 33 34 35 36 37 38 39 40)
ORBS_Y=(1 1 1 1 1 1 1 1 1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1)

function drawBackground(){
    COLOR=$1
    printf $COLOR
    tput clear;
    printf $RESET
}

function drawBorder(){
    COLOR=$1
    printf $COLOR
    start_x=$(( (COLUMNS-WIDTH)/2 ))
    start_y=$(( (LINES-HEIGHT)/2 ))
    for((y=0;y<HEIGHT+2;y++)); do
        tput cup $(( start_y+y )) $(( start_x ))
        for((x=0;x<WIDTH+2;x++)); do
            #tput cup $(( start_y+y )) $(( start_x+x ))
            printf "${BORDER[(WIDTH+2)*y+x]}";
        done;
    done;
    # tput cup $y $x; printf "████████████████████  ████████████████████"; y=$(( y+1 ));
    # tput cup $y $x; printf "█            █              █            █"; y=$(( y+1 ));
    # tput cup $y $x; printf "█ ███ █ ████ █ ███ ████ ███ █ ████ █ ███ █"; y=$(( y+1 ));
    # tput cup $y $x; printf "█     █                            █     █"; y=$(( y+1 ));
    # tput cup $y $x; printf "███ ███ ██████████ ████ ██████████ ███ ███"; y=$(( y+1 ));
    # tput cup $y $x; printf "█     █ █                        █ █     █"; y=$(( y+1 ));
    # tput cup $y $x; printf "█ ███     ████████ ████ ████████     ███ █"; y=$(( y+1 ));
    # tput cup $y $x; printf "█     █ █ █      █ █  █ █      █ █ █     █"; y=$(( y+1 ));
    # tput cup $y $x; printf "███ ███ █   ████   ████   ████   █ ███ ███"; y=$(( y+1 ));
    # tput cup $y $x; printf "█     █ █ █      █      █      █ █ █     █"; y=$(( y+1 ));
    # tput cup $y $x; printf "█ ███     ████████ ████ ████████     ███ █"; y=$(( y+1 ));
    # tput cup $y $x; printf "█     █ █                        █ █     █"; y=$(( y+1 ));
    # tput cup $y $x; printf "███ ███ ██████████ ████ ██████████ ███ ███"; y=$(( y+1 ));
    # tput cup $y $x; printf "█     █                            █     █"; y=$(( y+1 ));
    # tput cup $y $x; printf "█ ███ █ ████ █ ███ ████ ███ █ ████ █ ███ █"; y=$(( y+1 ));
    # tput cup $y $x; printf "█            █              █            █"; y=$(( y+1 ));
    # tput cup $y $x; printf "████████████████████  ████████████████████";
    printf $RESET
}
function drawPacman(){
    x=$(( (COLUMNS-WIDTH)/2+pacman_x  ))
    y=$(( (LINES-HEIGHT)/2+pacman_y ))
    tput cup $y $x
    if [ $pacman_dir -eq 0 ]; then
        pacman_sprite="ᗧ"
    elif [ $pacman_dir -eq 1 ]; then
        pacman_sprite="ᗤ"
    elif [ $pacman_dir -eq 2 ]; then
        pacman_sprite="ᗣ"
    elif [ $pacman_dir -eq 3 ]; then
        pacman_sprite="ᗢ"
    fi;
    printf "${LYELLOW_F}${pacman_sprite}${RESET}"
}
function drawOrbs(){
    x=$(( (COLUMNS-WIDTH)/2 ))
    y=$(( (LINES-HEIGHT)/2 ))
    size=${#ORBS_X[@]};
    for ((i=0; i<size; i++))
    do
        if [ ${ORBS_X[i]} -ne 0 ]; then
            tput cup $((y+ORBS_Y[i])) $((x+ORBS_X[i]))
            printf "${LYELLOW_F}•${RESET}"
        fi;
    done
}
function drawScore(){
    tput cup $2 $1
    printf "${LYELLOW_F}${DBLUE_B}Score - $score${RESET}"
    tput cup 1 0
}
function moveEntity(){
    if [ $3 -eq 0 ]; then
        (( $2_x=$2_x+($1) ));
    elif [ $3 -eq 1 ]; then
        (( $2_x=$2_x-($1) ));
    elif [ $3 -eq 2 ]; then
        (( $2_y=$2_y+($1) ));
    elif [ $3 -eq 3 ]; then
        (( $2_y=$2_y-($1) ));
    fi;
}
function pacmanTurn(){
    read -rsn1 input;
    if [ "$input"  = "a" ]; then
        pacman_dir=1;
    fi;
}
function checkCollision(){
    if [ "${BORDER[(WIDTH+2)*$3+$2]}" = "█" ]; then
        moveEntity -1 $4 $1;
    fi;

    if [ $3 -eq -1 ]; then
        (( $4_y=16 ));
    elif [ $3 -eq 17 ]; then
        (( $4_y=0 ));
    fi;
}
function checkOrbs(){
    size=${#ORBS_X[@]};
    for((i=0; i<size; i++)); do
        if [ $pacman_x -eq ${ORBS_X[i]} ] && [ $pacman_y -eq ${ORBS_Y[i]} ]; then
            (( score=score+1 ))
            (( ORBS_X[i]=0 ))
        fi;
    done;
}

drawBackground $DBLUE_B;
score=0;
pacman_x=1;
pacman_y=1;
pacman_dir=0; #0 - right, 1 - left, 2 - down, 3 - up.

windowWidth=$COLUMNS
windowHeight=$LINES

stty -icanon time 0 min 0;

while true
do
    timeStart=$(date +%s%N);
    
    if [ $windowWidth -ne $COLUMNS ] || [ $windowHeight -ne $LINES ]; then
        windowWidth=$COLUMNS
        windowHeight=$LINES
        drawBackground $DBLUE_B;
    fi;
    drawBorder $LGREEN_F;

    read input
    if [ "$input" != " " ]; then
        if [ "$input" = "d" ]; then 
            pacman_dir=0;
        elif [ "$input" = "a" ]; then
            pacman_dir=1;
        elif [ "$input" = "s" ]; then
            pacman_dir=2;
        elif [ "$input" = "w" ]; then
            pacman_dir=3;
        fi;
    fi;

    moveEntity 1 pacman $pacman_dir;
    checkCollision $pacman_dir $pacman_x $pacman_y pacman;
    checkOrbs;
    #drawOrbs;
    drawPacman $pacman_x $pacman_y;

    drawScore 0 0;
    timeEnd=$(date +%s%N);
    deltaTime=$(( (timeEnd-timeStart) ))  # Time elapsed since timeStart in nanoseconds
    sleep $(echo $deltaTime | awk '{ print 0.5-$1/1000000000 }');
done;