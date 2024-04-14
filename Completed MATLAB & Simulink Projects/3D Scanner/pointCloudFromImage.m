function [pc] = pointCloudFromImage(im, maxDist, minDist, pixelStep)
    % pixel angle (rad/pix)
    lambda = 0.0017;

    % get size of image
    [rows, columns] = size(im);

    % Create empty pc of size (num points)x3
    cloud = ones(rows * columns, 3) * NaN;

    % index through every element of matrix with one argument
    % here, index runs down a column and wraps to next
    centery = rows/2;
    centerx = columns/2;
    i = 1;
    k = 1;
    while i <= columns
        j = 1;
        while j <= rows
            % calculate 3D position of image if valid measurement
            if((im(j, i) < maxDist) && (im(j, i) > minDist))
                % cloud(k, :) = [x y z]
                cloud(k, 1) = sin(lambda * round(centerx - i, 0)) * im(j, i);
                cloud(k, 2) = sin(lambda * round(centery - j, 0)) * im(j, i);
                cloud(k, 3) = sqrt((im(j, i))^2 - (cloud(k, 2))^2 - (cloud(k, 1))^2);

                k = k + 1;
            end

            j = j + pixelStep;
        end

        i = i + pixelStep;
    end

    % remove empty rows from cloud
    cloud(k:(rows*columns), :) = [];

    % return cloud
    pc = cloud;
end