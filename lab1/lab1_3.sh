# Name: Tushar Shrivastav
# Date: 1/12/2024
# Title: Lab1 – circle
# Description: adding calculation of circle area to eadding calculation of circle area to eadding calculation of circle area to eadding calculation of circle area to eadding calculation of circle area to eadding calculation of circle area to eadding calculation of circle area to eadding calculation of circle area to eadding calculation of circle area to example/sh

#!/bin/sh

#PI=3.14159

echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=$(whoami)
numusers=$(who | wc -l)
echo "Hi $user! There are $numusers users logged on."
if [ $user = "tshrivastav" ]
then
    echo "Now you can proceed!"
else
    echo "Check who logged in!"
    exit 1
fi

response="Yes"
echo $response
while [ "$response" != "No" ]
do
    echo "Enter height of rectangle: "
    read height
    echo "Enter width of rectangle: "
    read width
    area=$(expr $height \* $width)
    echo "The area of the rectangle is $area"

    echo "Enter radius of Circle:"
    read radius
    area_circle=$(echo "$radius" | awk '{print 3.14159 * $1 * $1}')
    echo "The area of the Circle is $area_circle"

    echo "Would you like to repeat for another rectangle and circle [Yes/No]?"
    read response
done
