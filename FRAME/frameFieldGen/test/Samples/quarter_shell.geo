Point(1) = {0, 0, 0, 0.1};
Point(2) = {1, 0, 0, 0.1};
Point(3) = {2, 0, 0, 0.1};
Point(4) = {0, 1, 0, 0.1};
Point(5) = {0, 2, 0, 0.1};
Line(1) = {4, 5};
Line(2) = {2, 3};
Circle(3) = {2, 1, 4};
Circle(4) = {3, 1, 5};
Line Loop(6) = {4, -1, -3, 2};
Plane Surface(6) = {6};
