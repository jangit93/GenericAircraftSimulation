clc
clear 
close all
[Guidance] = importdata('../ModuleTest/Output/GuidanceTestData.txt',' ',1);
time = Guidance.data(:,1);
Acc_x = Guidance.data(:,2);
Acc_y = Guidance.data(:,3);
Acc_z = Guidance.data(:,4);
Vel_x = Guidance.data(:,5);
Vel_y = Guidance.data(:,6);
Vel_z = Guidance.data(:,7);

Pos_x = Guidance.data(:,8);
Pos_y = Guidance.data(:,9);
Pos_z = Guidance.data(:,10);

phi = Guidance.data(:,11);
theta = Guidance.data(:,12);



figure('Name','Position and Velocity')
subplot(311)
plot(time,-Pos_z)
xlabel('time [s]')
ylabel('z_{NED} [m]')
grid on
subplot(312)
plot(Pos_x,Pos_y)
xlabel('x_{NED} [m]')
ylabel('y_{NED} [m]')
grid on
subplot(313)
plot(time,sqrt(Vel_x.^2+Vel_y.^2+Vel_z.^2));
xlabel('time [s]')
ylabel('V_{abs} [m/s]')
grid on

figure('Name','Accelerations')
subplot(311)
plot(time,Acc_x)
ylabel('Accx_{NED} [m]')
xlabel('time [s]')

subplot(312)
plot(time,Acc_y)
ylabel('Accy_{NED} [m]')
xlabel('time [s]')

subplot(313)
plot(time,Acc_z)
ylabel('Aczx_{NED} [m]')
xlabel('time [s]')

figure('Name','Commanded Roll Angle')
subplot(2,1,1)
plot(time,phi*180/pi)
xlabel('Time [s]')
ylabel('\phi_{com}')
grid on
subplot(2,1,2)
plot(time,theta*180/pi)
xlabel('Time [s]')
ylabel('\theta_{com}')
grid on