# AP-Game-Project
A simple implementation of Fieldrunners Game using RSDL library

to execute simply extract "Icons.rar" and run "./FieldRunners.out < waves.txt" command

# What you can do:
Select a square and push the following buttons to place a tower
* -G for gatling tower
-M for missile tower
-T for tesla tower
-L for glue

Use U to upgrade a selected tower

Use S to sell a tower (at a lower rate)

Note that placing/upgrading towers will cost money and you can't do so if you lack the sufficient amount.
The goal of the game is to prevent the enemy from reaching the end of the track by placing towers near the path.

The Enemy will appear in forms of waves. A default "waves.txt" file has been included in the repository.
The first line indicates the squares of the path and the following lines show the number of different types of enemies respectively. (the troopers will appear in random order)
* 0 1 1 1 2 1 2 2 2 5 3 5 4 5 5 5 6 5 7 5 8 5 9 5 10 5 11 5 12 5
* 3 4 4 5
* 4 2 6 7
