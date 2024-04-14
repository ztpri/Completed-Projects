function animateTrajectory(locationTL, n, pauseTime)
    [row, col] = size(locationTL);

    xMax = max(locationTL(1, :));
    xMin = min(locationTL(1, :));

    yMax = max(locationTL(2, :));
    yMin = min(locationTL(2, :));

    zMax = max(locationTL(3, :));
    zMin = min(locationTL(3, :));
    

    i = 1;
    while i < col
        x = locationTL(1, i);
        y = locationTL(2, i);
        z = locationTL(3, i);

        scatter3(x, y, z, 'red', '.');
        xlim([xMin xMax]);
        ylim([yMin yMax]);
        zlim([zMin zMax]);
        hold on

        pause(pauseTime);

        i = i + 1 + n;
    end
end