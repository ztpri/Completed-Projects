% Paint the blank image with black to create the map
% Set an index to 0 to make it black
% Account for an empty blankRoomImg and empty pc
% Account for the case in which a point is outside the image
% If it is outside the map return with an error
% blankRoomImg is a YxXx1 matrix for a blank image
% pc is a Kx2 matrix containing the point cloud
% res is the resolution of each pixel (cm/pixel)
% printedRoomImg is a YxXx1 image that represents a map

function [paintedRoomImg] = paintObjects(blankRoomImg, pc, res)
    % check for an empty image or pc
    if(isempty(blankRoomImg))
        paintedRoomImg = [];
        return
    end
    if(isempty(pc))
        paintedRoomImg = blankRoomImg;
        return
    end

    % find center of image in pixels
    % image center might not be geometrically centered
    [height, width] = size(blankRoomImg); % get width of image for later
    a = size(pc);   % get size of point cloud list
    yMax = 0;
    yMin = 0;
    xMax = 0;
    xMin = 0;
    for i = 1:a(1)  % find max and min values
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
    yMaxPix = round(yMax/res);
    xMinPix = round(xMin/res);
    xOrigin = abs(xMinPix) + 1;    % get x center
    yOrigin = yMaxPix + 1;    % get y center

    % paint obejcts
    a = size(pc);
    j = 0;
    k = 0;
    for i = 1:a(1)
        x = pc(i, 1);   % get position in cm
        xPix = x / res; % convert cm to pixels
        y = pc(i, 2);   % get position in cm
        yPix = y / res; % convert cm to pixels

        j = round(xOrigin + xPix, 0);   % convert x position to index
        k = round(yOrigin - yPix, 0);   % convert y position to index

        if((j > width) || (k > height)) % check for object outside image
            paintedRoomImg = blankRoomImg;
            disp([height width]);
            disp([yOrigin xOrigin]);
            disp([k j]);
            disp([y x]);
            error('Detected object lies outside map');
        end

        blankRoomImg(k, j) = 0;
    end

    % output map
    paintedRoomImg = blankRoomImg;
end