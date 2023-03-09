% theta3"(t)=k3ei3(t)+k4theta3'(t)+k5cos(theta23(t)) 

load('System_Identification_unity_feedback_observer_team_9.mat','data');

k = rand(1,3); %random guess for k vector
gamma = 3; % learning rate
N = size(data, 2);
Ts = .002; % sampling period
Iterations = 10000;
wc = 10*pi;

%Filter
Theta1F = zeros(1, 229034);
Theta2F = zeros(1, 229034);
PWM2F = zeros(1, 229034);

Theta1Fnm1 = 0;
Theta2Fnm1 = 0;
PWM2Fnm1 = 0;

for n=1:229034
    Theta1F(n) = (1/(1+Ts*wc))*(Theta1Fnm1 + Ts*wc*data(3,n));
    Theta1Fnm1 = Theta1F(n);

    Theta2F(n) = (1/(1+Ts*wc))*(Theta2Fnm1 + Ts*wc*data(4,n));
    Theta2Fnm1 = Theta2F(n);

    PWM2F(n) = (1/(1+Ts*wc))*(PWM2Fnm1 + Ts*wc*data(8,n));
    PWM2Fnm1 = PWM2F(n);
end

%Identification 

K3 = zeros(1, Iterations);
K4 = zeros(1, Iterations);
K5 = zeros(1, Iterations);

for i = 1:Iterations
    dJdk = [0,0,0];
    J = 0;
    for n = 1:(N-2)
        ei3 = PWM2F(n);
        q2 = (Theta2F(n+1)-Theta2F(n))/Ts;
        q2np1 = (Theta2F(n+2)-Theta2F(n+1))/Ts;
        costheta23 = cos(Theta1F(n)+Theta2F(n));

        S = [ei3;q2;costheta23];
        J = J +(1/2)*(q2+Ts*k*S - q2np1)^2;
        dJdk = dJdk + (q2+Ts*k*S - q2np1)*Ts*(S');
    end
    k = k - gamma*dJdk;
    disp([J,k]);
    K3(i) = k(1);
    K4(i) = k(2);
    K5(i) = k(3);
end
