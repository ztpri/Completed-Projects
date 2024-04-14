% Creates a 4x4 matrix that represents the 3D rotation about the x-axis

function [R4, R3] = rotx3(theta)
    R3 = [1 0 0; 0 cos(theta) -sin(theta); 0 sin(theta) cos(theta)];
    zero3x1 = [0; 0; 0];
    zero1x3 = [0 0 0];
    R4 = [R3 zero3x1; zero1x3 1];
end