%% plot Aerodynamic polars
clear
close all
clc

[Aerodynamic] = readIn('AerodynamicTestData.txt',' ',1);

AoA = Aerodynamic.data(1:20,1);

CA  = Aerodynamic.data(:,4);

Ca = reshape(CA,[20,8,7]);

%% eta = 0
for i = 1:8
plot(AoA,Ca(:,i))
hold on
end