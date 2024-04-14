% Creates a 3D homogenous transformation matrix according to DH parameters
% theta, d, r, and alpha are the four DH parameters
% xi is the 3D pose of a joint


function [xi] = poseDH(theta, d, r, alpha)
    xi = [ cos(theta) -sin(theta)*cos(alpha) sin(theta)*sin(alpha) r*cos(theta); ...
           sin(theta) cos(theta)*cos(alpha)  -cos(theta)*sin(alpha) r*sin(theta);...
                0           sin(alpha)             cos(alpha)           d;       ...
                0               0                       0               1        ];
end