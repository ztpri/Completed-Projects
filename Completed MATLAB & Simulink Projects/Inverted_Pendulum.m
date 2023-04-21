% Clean Console
clc;

% Constants
k = 1;

% Parts of Plant
S = tf(1, [0.01 1]);
angleTF = 0.08448;
R = tf(7.007, [1 0 0]);

% Feedback System
C = k;
P = series(series(S, angleTF), R)
H = tf(15, [1 15]);
CLCE = C*P*H
O = zero(CLCE)
X = pole(CLCE)

% Create root locus and start moving loci
rltool(CLCE);

%% Standardize controller for Simulink [if needed]
clc;
syms s;
expand((0.0083*s + 1) * (0.01*s + 1))