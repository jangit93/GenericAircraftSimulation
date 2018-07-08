clc
clear 
close all
[Guidance] = importdata('../ModuleTest/Output/GuidanceTestData.txt',' ',1);

figure('Name','Commanded Roll Angle')
plot(Guidance.data(:,1),Guidance.data(:,2)*180/pi)
xlabel('Time [s]')
ylabel('\phi_{com}')

figure('Name','Commanded Pitch Angle')
plot(Guidance.data(:,1),Guidance.data(:,3)*180/pi)
xlabel('Time [s]')
ylabel('\theta_{com}')