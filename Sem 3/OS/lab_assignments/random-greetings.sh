#!/bin/bash
echo "Hello from Vatsal's Greeting Generator!"
read -p "What is your name?: " name
greeting[0]="Hola"
greeting[1]="Greetings"
greeting[2]="How do"
greeting[3]="Hey there"
greeting[4]="Howdy"
size=${#greeting[@]} #@ here denotes all elements of the array, # indicates length
index=$(($RANDOM % $size))
echo ${greeting[$index]} $name

