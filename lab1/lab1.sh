#!/bin/sh

# Name: Tushar Shrivastav
# Date: 1/12/2024
# Title: Lab1 – task
# Description: example


echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "tshrivastav" ]
then
        echo "Now you can proceed!"
else
        echo "Check who logged in!"
        exit 1
fi

response="Yes"
echo response
while [ $response != "No" ]
do
        echo "Enter height of rectangle: "
        read height
        echo "Enter width of rectangle: "
        read width
        area=`expr $height \* $width`
        echo "The area of the rectangle is $area"

        echo "Would you like to repeat for another rectangle [Yes/No]?"
        read response

done
