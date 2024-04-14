% Use 2D point cloud to create a blank image just big enough for a map
% It should be a YxXx1 matrix with everything equal to 1 (1 = white pixel)
% Account for a case where the point cloud is empty
% Account for the case in which desired resolution is 0
% If resolution is 0, return a blank variable
% pc is a Kx2 matrix
% res is the resolution of each pixel (cm/pixel)
% room-img is the blank image/matrix

function [room_img] = createBlankRoom(pc, res)
    % check for res of 0 or empty point cloud
    if((res == 0) || isempty(pc))
        room_img = [];
        return
    end

    % create max and min variables
    yMax = 0;
    yMin = 0;
    xMax = 0;
    xMin = 0;

    % find max and minmum values
    a = size(pc);   % get size of point cloud list

    for i = 1:a(1)
        xVal = pc(i, 1);
        yVal = pc(i, 2);

        % check for max or min x
        if(xVal > xMax) 
            xMax = xVal;
        elseif(xVal < xMin) 
            xMin = xVal;
        end

        % check for max or min y
        if(yVal > yMax) 
            yMax = yVal;
        elseif(yVal < yMin) 
            yMin = yVal;
        end
    end

    % create map
    % even vs odd changes indexing, so make odd
    % odd size makes indexing from center easier
    mapY = round((yMax + abs(yMin))/res, 0);
    if(mod(mapY, 2) == 0)  % check if even
        mapY = mapY + 1;    % make odd
    end

    mapX = round((xMax - xMin)/res, 0);
    if(mod(mapX, 2) == 0) % check if even
        mapX = mapX + 1; % make odd
    end

    mapX = mapX + 2; % make room for furthest objects and keep odd
    mapY = mapY + 2; % make room for furthest objects and keep odd

    room_img = ones(mapY, mapX, 1);
end