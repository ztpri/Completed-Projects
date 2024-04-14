function [pc_t] = qarmCam2Global(q, im, maxDist, minDist, pixelStep)
    % get pose of arm and camera
    [xi] = qarmPose(q);
    xi_cam = xi(:, :, 6) * pose3(0.05, 0, -0.095, -pi/2, 0, 0);

    % get relative point cloud
    pc = pointCloudFromImage(im, maxDist, minDist, pixelStep);

    % turn relative pc into global pc
    a = size(pc);
    pc_t = zeros(a(1), 3);

    for i = 1:a(1)
        dx = pc(i, 1);
        dy = pc(i, 2);
        dz = pc(i, 3);
        gPoint = transpose(xi_cam * [dx; dy; dz; 1]);
        pc_t(i, :) = gPoint(1, 1:3);
    end
end