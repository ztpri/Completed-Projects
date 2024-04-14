% Creates a 4x4 matrix to represent a 3D pose
% This follows the zyx convetion for Euler's Rotation Theorem

function xi = pose3(dx, dy, dz, yaw, pitch, roll)
    T = transl3(dx, dy, dz);
    [R4, R3] = rotypr3(yaw, pitch, roll);
    xi = T * R4;
end