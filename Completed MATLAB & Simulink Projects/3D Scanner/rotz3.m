% Creates a 4x4 matrix that represents the 3D rotation about the z-axis

function [R4, R3] = rotz3(theta)
    R3 = [cos(theta) -sin(theta) 0; sin(theta) cos(theta) 0; 0 0 1];
    zero3x1 = [0; 0; 0];
    zero1x3 = [0 0 0];
    R4 = [R3 zero3x1; zero1x3 1];
end