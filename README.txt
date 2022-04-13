How to play
Captain! Your goal is to bring the number at the top (# of enemies) to 0 by killing the aliens and saucers with your primary and heavy fire, gathering power ups to boost your abilities.
Press space to fire your basic weapon, a small bullet that deals chip damage.
Press ‘z’ to fire your heavy weapon, a missile that deals heavy damage
The blue powerup will give you a green shield which takes 3 hits to deplete. It has a timer of 10 seconds
The satellite powerup grants you 2 extra missiles.
Destroying asteroids will not bring down the “# of enemies” counter

Controls:
WS - Movement
AD - Change orientation 
Space - Primary Weapon
Z - Heavy weapon
Quit - alt-f4 / close tab

Fulfilled Requirements:
Design:
View is top down featuring aircraft.
Gameplay is meaningful with enemies and finishing conditions for winning and losing.
Three different enemy types
Asteroid - spawns and flies randomly across the screen
Saucer - flies around in circles with a fireball orbiting it. Fireball deals continuous damage to the player, so it’s recommended you shoot it from afar
Alien - Grounded aliens will fire bullets that follow the player if the player is far enough. If the player is within a certain range, the alien will stop firing and start chasing the player
Two different weapons
Primary (bullet)
Heavy (missile)
Power Ups that bring advantages
Shield power up - grants green shield that blocks 3 hits. Has timer for expiry
Satellite powerup - gives 2 extra missiles

Technical
Written in C++ using OpenGL library math, is documented and runs without crashing
All movement is handled by transformations
Used physical and parametric type movement
Collision detection between all interactive objects with modularized Collision class
Hierarchical transformation with laser class moving relative to saucer class
A gameworld that's bigger than the screen, moves in all directions with WASD movement, keeps the player in the center.
Particle Systems are not visible in the game, BUT the code is implemented, a particle system is added to the game, and the program compiles fine with it.
HUD is on left side, showing health, missiles and shield level, as well as number of enemies left to kill

Extra
Custom background sprite
Victory and defeat screen

IMPORTANT: PLEASE READ
(Screenshots are located in the “Evidence” folder)
The three group members of this project were: Laura Jin, Riley Lutz, and Ransford Bendu
PomperFickle - Riley’s GitHub
dxlce - Laura’s GitHub
RansfordB-CKING - Ransford’s GitHub
(Proof of this can be found under the screenshot “ProofOfGitHubUsernames”
This project was worked on and completed by Laura and Riley. Ransford did not contribute to the project on GitHub (see images labeled “ProofOfCommits” and “ProofOfBranches”). 
We have contacted Ransford multiple times on Discord, but have not received any sort of communication from him to this date.


Instructions on how to run:
1. Download ZIP of code
2. Extract into directory of choice and create "bin" folder in same level
3. Run cmake and point to source folder and new bin folder in project
4. click "configure" and then "generate"
5. Change the library paths to point to your installation locations
6. Click "open project"

ISSUES & FIXES:
- "Project not recognized when running"
Fix: Right click on source folder in solution explorer and click "set as startup project"
