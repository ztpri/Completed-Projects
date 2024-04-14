% Creates a 4x4 matrix that represents the 3D rotation about the y-axis

function [R4, R3] = roty3(theta)
    R3 = [cos(theta) 0 sin(theta); 0 1 0; -sin(theta) 0 cos(theta)];
    zero3x1 = [0; 0; 0];
    zero1x3 = [0 0 0];
    R4 = [R3 zero3x1; zero1x3 1];
end