clc 
clear
close all
[IMU] = readIn('IMUData.txt',' ',1);
[Guidance]  = readIn('GuidanceData.txt',' ',1);
FlightTime          = Guidance.data(:,1);
Acc_body_xcom = Guidance.data(:,2);
Acc_body_ycom = Guidance.data(:,3);
Acc_body_zcom = Guidance.data(:,4);

Acc_body_x = IMU.data(:,4);
Acc_body_y = IMU.data(:,5);
Acc_body_z = IMU.data(:,6);

figure('Name','Acceleration Body [m/s^2]')

subplot(311)
plot(FlightTime,Acc_body_x,'r--',FlightTime,Acc_body_xcom,'k')
xlabel('Time [s]')
ylabel('Acc_{x} [m/s^2]')
grid on
subplot(312)
plot(FlightTime,Acc_body_y,'r--',FlightTime,Acc_body_ycom,'k')
xlabel('Time [s]')
ylabel('Acc_{y} [m/s^2]')
grid on
subplot(313)
plot(FlightTime,Acc_body_z,'r--',FlightTime,Acc_body_zcom,'k')
xlabel('Time [s]')
ylabel('Acc_{z} [m/s^2]')
grid on
legend('Acc_{sim}','Acc_{com}','Location','best')

function [relError] = error(Value_ist,Value_ref)

relError = abs((Value_ist-Value_ref)'/Value_ref)*100;
end