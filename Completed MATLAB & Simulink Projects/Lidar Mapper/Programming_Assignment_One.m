%% Programming Assignment One

% Load in the data collected by the robot and convert to matrices
lidarData = struct2array(load("Run_02.mat", "lid_data"));
poseData = struct2array(load("Run_02.mat", "poseTimeLine"));

% Create global points from robot pose and lidar data
[pc] = local2global(poseData, lidarData);

% Overlay the global point locations on an image to construct a room map
% use imshow function to display map
res = 1;
[room_img] = createBlankRoom(pc, res);

[paintedRoomImg] = paintObjects(room_img, pc, res);
imshow(paintedRoomImg);