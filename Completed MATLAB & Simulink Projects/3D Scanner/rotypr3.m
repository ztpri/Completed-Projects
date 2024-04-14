% Creates a 4x4 matrix to represent an entire 3D orientation
% Follows zyx (yaw, pitch, roll) convention for Euler's Rotation Theorem

function [R4, R3] = rotypr3(yaw, pitch, roll)
    [R Rz] = rotz3(yaw);
    [R Ry] = roty3(pitch);
    [R Rx] = rotx3(roll);
    R3 = Rz * Ry * Rx;
    zero3x1 = [0; 0; 0];
    zero1x3 = [0 0 0];
    R4 = [R3 zero3x1; zero1x3 1];
end