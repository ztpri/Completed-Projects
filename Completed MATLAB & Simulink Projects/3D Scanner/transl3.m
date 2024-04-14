% creates a 4x4 matrix to represent the translation of a 3D object/frame

function [T] = transl3(dx, dy, dz)
    T = [1 0 0 dx; 0 1 0 dy; 0 0 1 dz; 0 0 0 1];
end