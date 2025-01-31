# ASTEROIDS – INTERACTIVE 3D GRAPHICS & ANIMATION.
s3728738 – Aren Carter Balgos

## FEATURES THAT HAVE BEEN IMPLEMENTED :

    LEVEL 1 :
        1. ✔ Screen Mode
        2. ✔ The Arena 
        3. ✔ Ready Player 1 
        4. ✔ Starting Location 
        5. ✔ Player Movement 
        6. ✔ Hit The Wall 
        7. ✔ Shooting
        8. ✔ Math Structs/Classes and Functions 
        9. ✔ Code Quality 

    LEVEL 2 :
        1. ✔ Launch Position 
        2. ✔ Asteroid Launch 
        3. ✔ Gun Rendering & Shooting
        4. ✔ Asteroid / Ship / Bullet Collision 
        5. ✔ Multiple Asteroids 
        6. ✔ Particle Puff 

    LEVEL 3 :
        1. ✔ Procedurally Generated Asteroids 
        2. ✔ Rotating Asteroids 
        3. 1/2 Gun Switching 
            - Graphics are switched when Z is pressed, but the Missile doesn't actually activate and the gun is still used.
        4. ✔ Hit Points 
        5. ✔ Time and Score 
        6. ✔ Game Over, Man 

    LEVEL 4 :
        1. ✔ Bouncies 
        2. ✔ Bouncies 2 
        3. ✔ Do The Splits
        4. ✔ Earth Shattering Kaboom 
           
    BONUS FEATURES :
        1. ✔ Better Ship Movement
        2. 𐄂 Spawn Drone

## NOTES FROM DEVELOPER :

- all rendering is done in render.cpp
- the game is all made in main.cpp
- objects & classes are in the entities folder
- keyboard mechanics are in keyboard

 I've been testing and compiling this program completely on macOS so I'm not exactly sure if the compiling requirements are different for windows or linux, but if you run the makefile it should compile just fine on macOS.

## HOW TO COMPILE/BUILD CODE :

1. cd to directory:
     cd 'I3DG A1'
2. run "make" or "bash build.sh" inside folder (they really just do the same thing):
     make
     (or) bash build.sh
3. ./game to run game
     ./game
4. "make clean" to clean
     make clean