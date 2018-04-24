clc
clear 
close all
[Guidance] = readIn('GuidanceTestData.txt',' ',1);

figure('Name','Commanded Roll Angle')
plot(Guidance.data(:,1),Guidance.data(:,2))
xlabel('Time [s]')
ylabel('\phi_{com}')

figure('Name','Commanded Pitch Angle')
plot(Guidance.data(:,1),Guidance.data(:,3))
xlabel('Time [s]')
ylabel('\theta_{com}')