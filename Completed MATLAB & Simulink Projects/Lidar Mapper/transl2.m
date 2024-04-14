%% creates a 3x3 matrix to represent 2D translation

function T = transl2(dx, dy)
    T = [1 0 dx; 0 1 dy; 0 0 1];
end