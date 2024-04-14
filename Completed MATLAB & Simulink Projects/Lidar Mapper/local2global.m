% Use pose data of robot and lidar data to create a point cloud
% Ensure pose and lidar data have some amount of time stamps
% If they have different amount of points return an empty matrix
% Use lidar2location
% poseTimeLine is a 3xT matrix that contains robot pose data
% lid_data is a 361xT matrix that contains lidar data
% pc is a Kx2 matrix that contains the x and y values wrt global

function [pc] = local2global(poseTimeLine, lid_data)
    % make sure data sets have same amount of time stamps
    a = size(poseTimeLine); % get size of pose data
    b = size(lid_data);     % get size of lidar data
    T = b(2);   % save number of timestamps

    if a(2) ~= b(2) % check number of time stamps
        pc = [];    % if not equal, return empty matrix
        return
    end
    
    % get pose and relative points, then calculate global points
    % aP = aSr * rP
    lidarSnap = lid_data;   % setup sample/snap
    lidarSnap(1, :) = [];   % remove time stamp row -> 360xT

    globPoints = ones((360 * T), 2);   % create list of global points
    globPoints = NaN .* globPoints; % fill with NaN and replace or remove
    k = 1;  % set global list index

    for i = 1:T     % go through all time stamps
        rx = poseTimeLine(1, i);    % get x position of R
        ry = poseTimeLine(2, i);    % get y position of R
        theta = poseTimeLine(3, i); % get orientation of R
        aSr = pose2(rx, ry, theta); % get pose of R with respect to A

        [x, y] = lidar2location(lidarSnap(:, i));   % get points wrt robot
        a = size(x);     % get number of found points
        
        for j = 1:a(1)   % go though all relative points at that stamp
            if isnan(x(j))   %if NaN is found then go to next point
                continue
            end

            rP = [x(j); y(j); 1]; % get P respect to R
            aP = aSr * rP;  % calculate P respect to A
            globPoints(k, :) = [aP(1) aP(2)];  % save to list
            k = k + 1;  % go to next global list index
        end
    end

    % return point cloud
    a = size(globPoints);   % find end of global points list
    globPoints(k:a(1), :) = []; % empty all indexes left with NaN
    pc = globPoints;
end