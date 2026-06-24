/*
Copyright (c) 2004-2021, Lode Vandevenne

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

#define mapWidth 25;
#define mapHeight 24;

int map[mapWidth][mapHeight] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int main(int /*argc*/, char * /*argv*/[])
{
    double posX = 22, posY = 12; // player position (x,y)
    double dirX = -1, dirY = 0;  // direction of player (x,y)

    // camera plane of the player
    // controls how wide a player can see
    // determines fov, in this case it is 66°
    double planeX = 0, planeY = 0.66;

    // FOV influenced by directional vector
    // if directional vector is smaller = narrower FOV
    // if directional vector is higher = wider FOV
    // tan(angle) = ratio (opp/adj)
    // atan(ratio (opp/adj)) = angle
    // Multiply this FOV results by 2 since there are two separate rays to account for, or 2 right angled triangles.
    // int FOV = 2 * std::atan((dirX / dirY) / (planeX/ planeY));
    double time = 0.0;
    double oldTime = 0.0;

    const int screenWidth = 1280;
    const int screenHeight = 1024;

    // Resolution, 0 = no fullscreen, 1 = fullscreen, title of application
    screen(screenWidth, screenHeight, 0, "Raycaster");

    while (!done())
    {
        // Create ray direction
        for (int i = 0; i < w; i++)
        {
            // Camera's X position based on plane
            // Left = -1, Centre = 0, Right = 1
            double cameraX = 2 * i / double(w) - 1;

            // apply camera's position to the plane, then add player's direction to the vector
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;

            // cameraX * plane chooses how far left, centre, or right this ray is on the screen.
            // Adding direction makes the ray point forward in the player's facing direction.
            // plane * cameraX chooses where on the screen/FOV the ray aims.
            // dir makes that ray go forward in the player's facing direction.

            // Position of sqaure we are in
            int mapX = int(posX);
            int mapY = int(posY);

            // Initial distance that passes a boundary e.g. horizontal or vertical
            double sideDistX; // initial vertical boundary
            double sideDistY; // initial horizontal boundary

            // deltaDistX and deltaDistY tell us the repeated distance between grid boundaries along the ray (diagonal).
            // rayDirX and rayDirY tell us how strongly the ray moves in each direction.
            // If rayDirX or rayDirY is 0, the ray will not cross that type of boundary, so we store a huge number instead.
            double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
            double prepWallDist;

            // Direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            int hit = 0; // Was there a wall to hit?
            int side;    // was a NS or a EW wall hit?

            // Calculate step and initial sideDist

            // Determine which boundary to choose
            // e.g. For vertical boundary, if ray direction is left, then choose cloest left boundary
            // else, choose right boundary.
            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            }

            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            // Same logic as above, for top or bottom horizontal boundary
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            }
            else
            {
                stepY = +1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }

            while (hit == 0) {
                
                // if next vertical border is closer
                if (sideDistX < sideDistX) {
                    sideDistX += deltaDistX;
                    // StepX = 1: move right
                    // StepX = -1: move left
                    mapX += stepX;
                    side = 0;
                }
                // if next horizontal border is closer
                else {
                    sideDistY += deltaDistY;
                    // StepY = 1: move up
                    // StepY = -1: move down
                    mapY += stepY;
                    side = 1;
                }

                // Check if ray has hit a wall
                if (worldMap[mapX][mapY] > 0) hit = 1;
            }
            
            // distance from player's view to wall 
            double prepWallDist;
            
            // subtract delta dist because within last iteration of DDA loop we added an extra delta dist
            if (side == 0) {
                prepWallDist = sideDistX - deltaDistX;
            }
            else {
                prepWallDist = sideDistY - deltaDistY;
            }


            // walls slice height (walls height depending on distance) 
            int lineHeight = (int)(h / prepWallDist);
        }
    }
}