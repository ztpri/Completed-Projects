%% creates a 3x3 matrix to represent 2D rotation

function [R3, R2] = rot2(theta)
    %{
    if theta < 0
        thetaAbs = theta + 360;
    else
        thetaAbs = theta;
    end 
    %}
    thetaAbs = theta;

    R2 = [cos(thetaAbs) -sin(theta); sin(thetaAbs) cos(thetaAbs)];
    R3 = [cos(thetaAbs) -sin(thetaAbs) 0; sin(thetaAbs) cos(thetaAbs) 0; 0 0 1];
end