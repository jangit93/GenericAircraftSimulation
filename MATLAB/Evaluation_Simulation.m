%%plot airframe data
clear 
close all 
clc

%% read in data
[Airframe]      = readIn('AirframeData.txt',' ',1);
[Guidance]      = readIn('GuidanceData.txt',' ',1);
[Thrust]        = readIn('EngineData.txt',' ',1);
[Aerodynamic]   = readIn('AerodynamicData.txt',' ',1);
[Navigation]    = readIn('NavigationData.txt',' ',1);
[Actuator]      = readIn('ActuatorData.txt',' ',1);
[IMU]           = readIn('IMUData.txt',' ',1);

%% Plot Trajectory
FlightTime = Navigation.data(:,1);
Posx_NED =  Navigation.data(:,3);
Posy_NED =  Navigation.data(:,4);
Posz_NED = -Navigation.data(:,5);
Posx_NED_com =  Guidance.data(:,8);
Posy_NED_com =  Guidance.data(:,9);
Posz_NED_com = -Guidance.data(:,10);

figure('Name','Trajectory NED')
subplot(3,1,1)
plot3(Posx_NED,Posy_NED,Posz_NED)
grid on 
xlabel('X_{NED}')
ylabel('Y_{NED}')
zlabel('Z_{NED}')


subplot(3,1,2)
plot(FlightTime,Posz_NED)
grid on 
xlabel('Flighttime in [s]')
ylabel('Z_{NED}')

subplot(3,1,3)
plot(Posx_NED,Posy_NED,'',Posx_NED_com,Posy_NED_com,'k--')
grid on 
xlabel('X_{NED}')
ylabel('Y_{NED}')
legend('Simulation','target','Location','best')

%% Plot Longitudinal
AoA = Aerodynamic.data(:,2);
Gamma = Airframe.data(:,2);
Theta = Navigation.data(:,7);
q  = IMU.data(:,2);
eta = Actuator.data(:,1);

figure('Name','Longitudinal')
subplot(5,1,1)
plot(FlightTime,AoA*180/pi);
xlabel('Flighttime in [s]')
ylabel('\alpha in [°]')
grid on


subplot(5,1,2)
plot(FlightTime,Theta*180/pi);
xlabel('Flighttime in [s]')
ylabel('\theta in [°]')
grid on

subplot(5,1,3)
plot(FlightTime,Gamma*180/pi);
xlabel('Flighttime in [s]')
ylabel('\gamma in [°]')
grid on

subplot(5,1,4)
plot(FlightTime,q*180/pi);
xlabel('Flighttime in [s]')
ylabel('q in [°/s]')
grid on

subplot(5,1,5)
plot(FlightTime,eta*180/pi);
xlabel('Flighttime in [s]')
ylabel('\eta in [°]')

grid on

%% lateral-roll
xi  = Actuator.data(:,3);
phi = Navigation.data(:,6);
p   = IMU.data(:,1);
figure('Name','lateral-roll')
subplot(3,1,1)
plot(FlightTime,phi*180/pi);
xlabel('Flighttime in [s]')
ylabel('\phi in [°]')
grid on

subplot(3,1,2)
plot(FlightTime,p*180/pi);
xlabel('Flighttime in [s]')
ylabel('p in [°/s]')
grid on

subplot(3,1,3)
plot(FlightTime,xi*180/pi);
xlabel('Flighttime in [s]')
ylabel('\xi in [°]')
grid on

%% lateral-roll
zeta  = Actuator.data(:,2);
psi = Navigation.data(:,8);
r   = IMU.data(:,3);
beta = Aerodynamic.data(:,3);
chi = Airframe.data(:,3);

figure('Name','lateral-roll')
subplot(4,1,1)
plot(FlightTime,beta*180/pi);
xlabel('Flighttime in [s]')
ylabel('\beta in [°]')
grid on

subplot(5,1,2)
plot(FlightTime,psi*180/pi);
xlabel('Flighttime in [s]')
ylabel('\psi in [°]')
grid on

subplot(5,1,3)
plot(FlightTime,chi*180/pi);
xlabel('Flighttime in [s]')
ylabel('\chi in [°]')
grid on

subplot(5,1,4)
plot(FlightTime,r*180/pi);
xlabel('Flighttime in [s]')
ylabel('r in [°/s]')
grid on

subplot(5,1,5)
plot(FlightTime,zeta*180/pi);
xlabel('Flighttime in [s]')
ylabel('\zeta in [°]')
grid on

%%acceleration
Acc_body_xcom = Guidance.data(:,2);
Acc_body_ycom = Guidance.data(:,3);
Acc_body_zcom = Guidance.data(:,4);

Acc_body_x = IMU.data(:,4);
Acc_body_y = IMU.data(:,5);
Acc_body_z = IMU.data(:,6);

figure('Name','Acceleration Body [m/s^2]')
subplot(311)
plot(FlightTime,Acc_body_x,FlightTime,Acc_body_xcom,'k--')
xlabel('Time [s]')
ylabel('Acc_{x} [m/s^2]')
grid on
subplot(312)
plot(FlightTime,Acc_body_y,FlightTime,Acc_body_ycom,'k--')
xlabel('Time [s]')
ylabel('Acc_{y} [m/s^2]')
grid on
subplot(313)
plot(FlightTime,Acc_body_z,FlightTime,Acc_body_zcom,'k--')
xlabel('Time [s]')
ylabel('Acc_{z} [m/s^2]')
grid on
legend('Acc_{sim}','Acc_{com}','Location','best')

%% Velocity
Vel = Navigation.data(:,2);
Vel_Com = sqrt(Guidance.data(:,4).^2+Guidance.data(:,5).^2+Guidance.data(:,6).^2);
Delta = Actuator.data(:,4);
figure('Name','Velocity')
subplot(2,1,1)
plot(FlightTime,Vel,FlightTime,Vel_Com,'k--')
xlabel('Flighttime in [s]')
ylabel('Velocity [m/s]')
legend('Vel_{sim}','Vel_{com}','Location','best')
grid on

subplot(2,1,2)
plot(FlightTime,Delta*100)
grid on
xlabel('Flighttime in [s]')
ylabel('\delta_F [%]')

clear