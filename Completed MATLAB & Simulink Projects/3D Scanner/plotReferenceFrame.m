% Plot a frame
% xi is the transformation matrix
% scale scales the size of the axes from 1
% textlabel is the label of the frame

function plotReferenceFrame(xi, scale, textlabel)
    % get position data
    x = xi(1, 4);
    y = xi(2, 4);
    z = xi(3, 4);
    
    % get orientation data
    x_dir = xi(1:3, 1);
    y_dir = xi(1:3, 2);
    z_dir = xi(1:3, 3);
    
    % plot
    quiver3(x, y, z, x_dir(1), x_dir(2), x_dir(3), scale, 'r'); % x-axis
    hold on
    quiver3(x, y, z, y_dir(1), y_dir(2), y_dir(3), scale, 'g'); % y-axis
    hold on
    quiver3(x, y, z, z_dir(1), z_dir(2), z_dir(3), scale, 'b'); % x-axis
    hold on
    text(x, y, z, textlabel);
end