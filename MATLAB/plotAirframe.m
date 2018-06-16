%%plot airframe data
clear 
close all 
clc

%% read in data
[Airframe] = readIn('AirframeData.txt',' ',1);
[Guidance]  = readIn('GuidanceData.txt',' ',1);
[Thrust]  = readIn('EngineData.txt',' ',1);
[Aerodynamic] = readIn('AerodynamicData.txt',' ',1);
[Navigation] = readIn('NavigationData.txt',' ',1);
FlightTime = Airframe.data(:,1);

Acc_body_x = Airframe.data(:,2);
Acc_body_y = Airframe.data(:,3);
Acc_body_z = Airframe.data(:,4);

Acc_NED_x = Airframe.data(:,5);
Acc_NED_y = Airframe.data(:,6);
Acc_NED_z = Airframe.data(:,7);

Vel_NED_x = Airframe.data(:,8);
Vel_NED_y = Airframe.data(:,9);
Vel_NED_z = Airframe.data(:,10);

Pos_NED_x = Navigation.data(:,3);
Pos_NED_y = Navigation.data(:,4);
Pos_NED_z = Navigation.data(:,5);

Phi   = Airframe.data(:,14)*180/pi;
Theta = Airframe.data(:,15)*180/pi;
Psi   = Airframe.data(:,16)*180/pi;

Eta = Airframe.data(:,17);
Zeta = Airframe.data(:,18);
Xi = Airframe.data(:,19);
delta = Airframe.data(:,20);

p = Airframe.data(:,23);
q = Airframe.data(:,24);
r = Airframe.data(:,25);

Gamma = Airframe.data(:,21)*180/pi;
Chi   = Airframe.data(:,22)*180/pi;

AoA   = Aerodynamic.data(:,2)*180/pi;
AoS   = Aerodynamic.data(:,3)*180/pi;

Acc_body_xcom = Guidance.data(:,2);
Acc_body_ycom = Guidance.data(:,3);
Acc_body_zcom = Guidance.data(:,4);

Vel_xcom = Guidance.data(:,5);
Vel_ycom = Guidance.data(:,6);
Vel_zcom = Guidance.data(:,7);

Pos_xcom = Guidance.data(:,8);
Pos_ycom = Guidance.data(:,9);
Pos_zcom = Guidance.data(:,10);

Phi_com = Guidance.data(:,11)*180/pi;
Theta_com = Guidance.data(:,12)*180/pi;

%% plotting
figure('Name','Trajectory')
subplot(311)
plot3(Pos_NED_x,Pos_NED_y,Pos_NED_z,Pos_xcom,Pos_ycom,Pos_zcom,'--k')
xlabel('x_{NED}')
ylabel('y_{NED}')
zlabel('z_{NED}')
grid on

subplot(312)
plot(Pos_NED_x,Pos_NED_y,Pos_xcom,Pos_ycom,'k--')
xlabel('x_{NED}')
ylabel('y_{NED}')
grid on 

subplot(313)
plot(FlightTime,Pos_NED_z,FlightTime,Pos_zcom,'--k')
xlabel('Time [s]')
ylabel('z_{NED}')
grid on 

%//////////////////////////////////////////////////////////////////////////
% pitch axis parameter over time
%//////////////////////////////////////////////////////////////////////////
figure('Name','Pitch Axis')
subplot(511)
plot(FlightTime,AoA)
subplot(512)
plot(FlightTime,Theta,'k--',FlightTime,Theta_com)
subplot(513)
plot(FlightTime,q)
subplot(514)
plot(FlightTime,Gamma)
subplot(515)
plot(FlightTime,Eta)
grid on
figure('Name','Acceleration Body [m/s^2]')
subplot(311)
plot(FlightTime,Acc_NED_x,'--',FlightTime,Acc_body_xcom)
xlabel('Time [s]')
ylabel('Acc_{x} [m/s^2]')
grid on
subplot(312)
plot(FlightTime,Acc_NED_y,'--',FlightTime,Acc_body_ycom)
xlabel('Time [s]')
ylabel('Acc_{y} [m/s^2]')
grid on
subplot(313)
plot(FlightTime,Acc_body_z,'--',FlightTime,Acc_body_zcom)
xlabel('Time [s]')
ylabel('Acc_{z} [m/s^2]')
grid on