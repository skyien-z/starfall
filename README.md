###Starfall App
####Description
This program is a cinder application that displays a simulation of shooting stars,
based on Sarah J. Maas' description of a fictional "Starfall" in her book *A Court 
of Mist and Fury*. Using keyboard commands, a user can generate stars of different
colors and trajectories. There is also a preloaded timer-run Starfall simulation 
corresponding Maas' Starfall paragraph description (also displayed on the screen)
that an user can choose to play. In order to make this simulation somewhat realistic,
an user can also draw boundaries, that, when touched by a star, make the star disappear
from the screen. 

####Installation
* Download Cinder (v0.9.2) for your platform from https://libcinder.org/download
* Download this project's folders from this github repository
* This application was made with macOS Big Sur

####Controls
#####User Controls
Key | Action
----|------
Spacebar | Generate random trajectory and color for next star released
r | Generate random color for next star released
Return | Start Starfall automated simulation
Delete | Stop Starfall automated simulation
Right | Generate random trajectory going right for the next star released
Left | Generate random trajectory going left for the next star released
Down | Save drawn boundaries to import in later
Up | Upload boundaries if saved
Tab | Remove current map boundaries
Left Click | Release star with generated specifications
Shift+Right Click Drag | Draw Boundary Line

