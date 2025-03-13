# FDF
## Introduction

This project is to render a 3D wireframe from a 2D digits array using MiniLibX library\

### What is MiniLibX?

MiniLibX is a basic graphic library which contains function to render 2D image to display on window.\
Features:\
Allows drawing pixels, lines, and images.\
Supports keyboard and mouse events.\
Can handle textures and basic image manipulations.\
It abstracts X11 (Linux) making it easier to render graphics.\
X11 (X Window System) is a low-level graphics protocol (GUI) used in UNIX-based operating systems like Linux and BSD.\

### Step by step guide

#### 1. Parsing map
-check the file extension\
-read the map using get next line\
-get the number of rows and column of the map using ft_split\
-store the map in a 2D array which contains information of coordinates\
x : position in horizontal direction (number of columns);\
y : position in vertical direction (number of rows);\
z : altititude of the graphic image (non zero digits);\
color : convert from hex to integer (0xRRGGBB);\

#### 2. Understanding MiniLibX library
-use mlx function to create a window (HEIGHT x WIDTH)\
-how to put pixels to the image\
-how to put the image to the window\
-understanding events hook (in this project i just use keypress and close window with 'X')\
-understanding mlx loop, which keeps the window open and keeps the program running and listening to events\

#### 3. Determine the drawing algorithm
-
