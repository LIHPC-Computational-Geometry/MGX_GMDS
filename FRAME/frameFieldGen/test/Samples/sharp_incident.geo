// Gmsh project created on Fri Apr 10 10:06:29 2015
Point(1) = {0, 0, 0, 3};
Point(2) = {35, 0, 0, 3};
Point(3) = {35, 44, 0, 3};
Point(4) = {0, 44, 0, 3};
Point(5) = {0, 15, 0, 3};
Point(6) = {0, 17, 0, 3};
Point(7) = {11, 16, 0, 3};
Point(8) = {24, 27, 0, 3};
Point(9) = {35, 28, 0, 3};
Point(10) = {35, 26, 0, 3};
Line(1) = {4, 3};
Line(2) = {3, 9};
Line(3) = {9, 8};
Line(4) = {8, 10};
Line(5) = {10, 2};
Line(6) = {2, 1};
Line(7) = {1, 5};
Line(8) = {5, 7};
Line(9) = {7, 6};
Line(10) = {6, 4};
Line Loop(11) = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
Plane Surface(12) = {11};