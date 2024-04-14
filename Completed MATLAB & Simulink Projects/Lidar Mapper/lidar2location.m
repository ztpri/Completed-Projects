% Transform data into 2D points relative to robot frame
% Ensure input data is correct size, else return blank vectors: []
% Ignore all data points with NaN data
% Do not leave blank or NaN data in output vector
% lidarSnap is 360x1
% x and y are Nx1, where N is amount of valid stamps

function [x, y] = lidar2location(lidarSnap)
    % check lidarSnap size
    if ~isequal(size(lidarSnap), [360 1])   % check size
        x = [];
        y = [];

        return; % return with empty matrices
    end
    
    % create temp matrices
    xTemp = zeros(1, 2);
    yTemp = zeros(1, 2);

    % expand and fill matrices when valid data is found
    i = 1;  % to index through snap
    j = 1;  % to index through x and y matrices
    while i < 361
        if ~isnan(lidarSnap(i)) % make sure there is no NaN
            xTemp(j, 1) = 100*lidarSnap(i)*cosd(i-1);   % calculate x
            yTemp(j, 1) = 100*lidarSnap(i)*sind(i-1);   % calculate y
            j = j + 1;  % increase position index
        end

        i = i + 1;  % increase snap index
    end

    % assign return matrices
    x = xTemp;
    y = yTemp;
end