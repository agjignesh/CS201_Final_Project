This is the CS201 Final project of group number 42.
We are creating quad trees that are used in computer graphics and image processing.
This project is written in C language.

The Intial code of the project is in quad_trees.c 
I have tried to describe the code as much as possible using comments.

In this code I have created a struct point, a struct region, a struct quad tree.

A point contains the x and y coordinates of a point.
The region contains four points which are the corners of a rectangle.
The quad tree contains a region, a point, four pointers to the children quad trees.

Then we have some fuctions relating to points and regions.

Then we have the functions that create the quad tree, insert a point in the quad tree, search for a point in the quad tree, delete a point from the quad tree, print the quad tree, free the quad tree.

Then we have the main function which is used to test the code.

The code is working fine and I have tested it with some test cases.


IMPORTANT AFTER THIS LINE PLS DO READ


But I am not sure if the code works for edge cases, ie when the element is on the edge of the region or when the region is a square.

I am also not sure if the code works for all the cases when the region is a rectangle.

Basically the testing part of the code is not complete.

also i am ataching a Image of how the quadrents look like.

we are always moving in clockwise direction for the regions.