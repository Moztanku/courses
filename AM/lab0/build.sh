#!/bin/bash

# Requires installed SFML library

$(g++ -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system -o main main.cpp)