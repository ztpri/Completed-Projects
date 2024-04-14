% Given multiple frames, plot each frame
% Frames should be named global, 1, 2, ..., e
% The first frame is global and the last is the end effector
% all frames inbetween are 1, 2, ..., n
% xis is a 4x4xN matrix, where N is the number of frames
% scale is a value that scales each axis of each frame
% f is a figure of these plotted frames

function [f] = plotPoseSet(xis, scale)
    f = figure;
    hold on;

    [rows, columns, frames] = size(xis);
    for i = 1:frames
        xi = xis(:, :, i);
        
        switch i
            case frames
                textlabel = 'e';
            case 1
                textlabel = 'Global';
            otherwise
                textlabel = int2str(i-1);
        end
        
        plotReferenceFrame(xi, scale, textlabel);
    end
end