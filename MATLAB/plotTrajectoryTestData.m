%% plot Aerodynamic polars
clear
close all
clc
%% read in data
[Trajectory] = readIn('TrajectoryTestData.txt',' ',1);

plot(Trajectory.data(:,1),Trajectory.data(:,3))
plot(Trajectory.data(:,1),Trajectory.data(:,4))

