%% Main Code
% code calibration variables
file = 'Chris.mat';     % file to use for scan
animationTime = 0.1;    % time between animated points for end effector
animationSkips = 0;     % time line intervals to skip for end effector anim
maxDist = 1;   % max distance of scan
minDist = 0.2; % min distance of scan
pixelStep = 5; % number of pixels to skip when making pc

% load data
load(file);

% get global point cloud and end effector for entire timeline
[joints, intervals] = size(joint_pos);

endEffTimeLine = NaN * ones(3, intervals+1);
j = 1;  % use to count filled time line spaces

n = size(cam_d);
pcSize = n(1)*n(2)*n(3);
pcGlob = ones(pcSize, 3) * NaN;
k = 1;  % count number of valid intervals

for i = 1:intervals
    % get end effector timeline
    q = joint_pos(2:5, i);
    im = cam_d(:, :, i);
    xi = qarmPose(q);
    b = size(xi);
    if(~isnan(xi(1)))   % if invalid joint angles, dont save
        % save end effector position
        endEffTimeLine(1, j) = xi(1, 4, 6);
        endEffTimeLine(2, j) = xi(2, 4, 6);
        endEffTimeLine(3, j) = xi(3, 4, 6);
        j = j + 1;

        % save point cloud
        pc_t = qarmCam2Global(q, im, maxDist, minDist, pixelStep);
        if(~isempty(pc_t))
            a = size(pc_t);
            nextK = k + a(1) - 1;
            pcGlob(k:nextK, :) = pc_t;
            k = k + a(1);
        end
    else
        i
        q
    end
end

endEffTimeLine(:, j:(intervals+1)) = [];  % remove all empty spaces
pcGlob(k:pcSize, :) = [];

% Animate end effector position
figure('Name', 'End Effector Trajectory');
animateTrajectory(endEffTimeLine, animationSkips, animationTime);

% create 3D map
figure('Name', '3D Scan');
pcshow(pcGlob);



