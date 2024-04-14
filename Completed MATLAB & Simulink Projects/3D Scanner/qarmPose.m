function [xi] = qarmPose(q)
    % check for invalid data
    if((q(1) < -2.9671) || (q(1) > 2.9671))
        xi = NaN;
        return
    end
    if((q(2) < -1.4835) || (q(2) > 1.6))
        xi = NaN;
        return
    end
    if((q(3) < -1.6581) || (q(3) > 1.309))
        xi = NaN;
        return
    end
    if((q(4) < -2.7925) || (q(4) > 2.7925))
        xi = NaN;
        return
    end

    % get joint positions relative to previous joint
    xig = poseDH(0, 0, 0, 0);
    xi1 = poseDH(0, 0, 0, 0);
    xi2 = poseDH(q(1), 0.14, 0, -pi/2);
    xi3 = poseDH(-1.4289+q(2), 0, sqrt((0.35^2)+(0.05^2)), 0);
    xi4 = poseDH(-0.142+q(3), 0, 0, -pi/2);
    xie = poseDH(q(4), 0.315, 0, 0);

    % convert to global points
    gxi2 = xi1 * xi2;
    gxi3 = gxi2 * xi3;
    gxi4 = gxi3 * xi4;
    gxie = gxi4 * xie;

    % create output matrix
    xi(:, :, 1) = xig;
    xi(:, :, 2) = xi1;
    xi(:, :, 3) = gxi2;
    xi(:, :, 4) = gxi3;
    xi(:, :, 5) = gxi4;
    xi(:, :, 6) = gxie;
    
    % plot joint frames
    %{
    plotReferenceFrame(xi(:, :, 1), 1, 'global');
    hold on
    plotReferenceFrame(xi(:, :, 2), 1, 'j1');
    hold on
    plotReferenceFrame(xi(:, :, 3), 1, 'j2');
    hold on
    plotReferenceFrame(xi(:, :, 4), 1, 'j3');
    hold on
    plotReferenceFrame(xi(:, :, 5), 1, 'j4');
    hold on
    plotReferenceFrame(xi(:, :, 6), 1, 'end effector');
    %}
end