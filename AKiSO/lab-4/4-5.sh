#!/bin/bash

LGREEN_F="\033[38;5;10m"
LYELLOW_F="\033[38:5:11m"
LBLUE_F="\033[38;5;12m"
LRED_F="\033[38;5;9m"

DBLACK_B="\033[48:5:0m"
DGREEN_B="\033[48;5;2m"
DYELLOW_B="\033[48;5;3m"
DBLUE_B="\033[48;5;4m"

RESET="\033[0m"

WIDTH=40;
HEIGHT=15;

BORDER=(
 "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" " " " " "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█"
 "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█"
 "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█"
 "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█"
 "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█"
 "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█"
 "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█"
 "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" " " " " "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█"
 "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█"
 "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█"
 "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█"
 "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█"
 "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█"
 "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" " " "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█"
 "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "█" "█" "█" "\033[38;5;11m•\033[38;5;10m" "█"
 "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "\033[38;5;11m•\033[38;5;10m" "█"
 "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" " " " " "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█" "█"
 )

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
    elif [ $pacman_dir -eq 3 ]; then
        pacman_sprite="ᗣ"
    elif [ $pacman_dir -eq 2 ]; then
        pacman_sprite="ᗢ"
    fi;
    printf "${LYELLOW_F}${pacman_sprite}${RESET}"
}
function drawGhost(){
    x=$(( (COLUMNS-WIDTH)/2+$1  ))
    y=$(( (LINES-HEIGHT)/2+$2 ))
    tput cup $y $x
    printf "$3ᙁ${RESET}"

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
        (( $2_y=$2_y-($1) ));
    elif [ $3 -eq 3 ]; then
        (( $2_y=$2_y+($1) ));
    fi;
}
function pacmanTurn(){
    read -rsn1 input;
    if [ "$input"  = "a" ]; then
        pacman_dir=1;
    fi;
}
function ghostAAI(){
    index=$(( (WIDTH+2)*ghostA_y+ghostA_x ))
    if [ "${BORDER[index]}" = "█" ]; then
        moveEntity -1 ghostA $ghostA_dir
        ghostA_dir=$(( (ghostA_dir+1)%4 ))
    fi;

    if [ "${BORDER[index-WIDTH-2]}" != "█" ] && [ $ghostA_dir -ne 3 ]; then
        if [ $(($RANDOM%4)) -eq 1 ]; then
            ghostA_dir=2
        fi;
    elif [ "${BORDER[index+WIDTH+2]}" != "█" ] && [ $ghostA_dir -ne 2 ]; then
        if [ $(($RANDOM%4)) -eq 1 ]; then
            ghostA_dir=3
        fi;
    elif [ "${BORDER[index-1]}" != "█" ] && [ $ghostA_dir -ne 0 ]; then
        if [ $(($RANDOM%4)) -eq 1 ]; then
            ghostA_dir=1
        fi;
    elif [ "${BORDER[index+1]}" != "█" ] && [ $ghostA_dir -ne 1 ]; then
        if [ $(($RANDOM%4)) -eq 1 ]; then
            ghostA_dir=0
        fi;
    fi;

    if [ $ghostA_y -eq -1 ]; then
        ghostA_y=16;
    elif [ $ghostA_y -eq 17 ]; then
        ghostA_y=0
    fi;
}
function ghostBAI(){
    index=$(( (WIDTH+2)*ghostB_y+ghostB_x ))
    if [ "${BORDER[index]}" = "█" ]; then
        moveEntity -1 ghostB $ghostB_dir
        ghostB_dir=$(( (ghostB_dir+3)%4 ))
    fi;

    if [ "${BORDER[index-WIDTH-2]}" != "█" ] && [ $ghostB_dir -ne 3 ]; then
        if [ $(($RANDOM%3)) -eq 1 ]; then
            ghostb_dir=2
        fi;
    elif [ "${BORDER[index+WIDTH+2]}" != "█" ] && [ $ghostB_dir -ne 2 ]; then
        if [ $(($RANDOM%3)) -eq 1 ]; then
            ghostB_dir=3
        fi;
    elif [ "${BORDER[index-1]}" != "█" ] && [ $ghostB_dir -ne 0 ]; then
        if [ $(($RANDOM%3)) -eq 1 ]; then
            ghostB_dir=1
        fi;
    elif [ "${BORDER[index+1]}" != "█" ] && [ $ghostB_dir -ne 1 ]; then
        if [ $(($RANDOM%3)) -eq 1 ]; then
            ghostB_dir=0
        fi;
    fi;

    if [ $ghostB_y -eq -1 ]; then
        ghostB_y=16;
    elif [ $ghostB_y -eq 17 ]; then
        ghostB_y=0
    fi;
}
function checkCollision(){
    if [ "${BORDER[(WIDTH+2)*$3+$2]}" = "█" ]; then
        moveEntity -1 $4 $1;
    fi;
    if [[ $2 -eq $ghostA_x && $3 -eq $ghostA_y ]] || [[ $2 -eq $ghostB_x && $3 -eq $ghostB_y ]]; then
        gameover=1;
    fi;

    if [ $3 -eq -1 ]; then
        (( $4_y=16 ));
    elif [ $3 -eq 17 ]; then
        (( $4_y=0 ));
    fi;
}
function checkOrbs(){
    index=$(( (WIDTH+2)*pacman_y+pacman_x ))
    if [ "${BORDER[index]}" = "\033[38;5;11m•\033[38;5;10m" ]; then
        (( score=score+1 ))
        BORDER[$index]=" "
    fi; #   Number of orbs = 363
}

drawBackground $DBLUE_B;
score=0;
pacman_x=20;
pacman_y=3;
pacman_dir=0; #0 - right, 1 - left, 2 - up, 3 - down.

ghostA_x=20;
ghostA_y=5;
ghostA_dir=0;

ghostB_x=21;
ghostB_y=5;
ghostB_dir=1;

windowWidth=$COLUMNS
windowHeight=$LINES
gameover=0

stty -icanon time 0 min 0;

while (( score < 363 )) && (( gameover != 1 ))
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
            pacman_dir=3;
        elif [ "$input" = "w" ]; then
            pacman_dir=2;
        fi;
    fi;

    moveEntity 1 pacman $pacman_dir;
    checkCollision $pacman_dir $pacman_x $pacman_y pacman;
    moveEntity 1 ghostA $ghostA_dir;
    moveEntity 1 ghostB $ghostB_dir;
    ghostAAI;
    ghostBAI;
    checkOrbs;
    drawPacman $pacman_x $pacman_y;
    drawGhost $ghostA_x $ghostA_y $LRED_F;
    drawGhost $ghostB_x $ghostB_y $LBLUE_F;

    drawScore 0 0;
    timeEnd=$(date +%s%N);
    deltaTime=$(( (timeEnd-timeStart) ))  # Time elapsed since timeStart in nanoseconds
    sleep $(echo $deltaTime | awk '{ print 0.5-$1/1000000000 }');
done;


drawBackground $DBLUE_B;
drawBorder;
x=$(( (COLUMNS-WIDTH)/2 ));
y=$(( (LINES-HEIGHT)/2-1 ));
tput cup $y $x;
if [ $gameover -eq 1 ]; then
    printf "${DBLUE_B}${LYELLOW_F}GAME OVER, YOUR SCORE: ${score}${RESET}"
else
   printf "${DBLUE_B}${LYELLOW_F}YOU WON, YOUR SCORE: $score${RESET}"
fi
tput cup $((LINES-1)) 0