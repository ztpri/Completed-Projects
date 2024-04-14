% creates a 3x3 matrix to represent a 2D pose

function xi = pose2(dx, dy, theta)
    T = transl2(dx, dy);
    [R3, R2] = rot2(theta);
    
    xi = T * R3;
    % pose is simply the translation compounded with rotation
end