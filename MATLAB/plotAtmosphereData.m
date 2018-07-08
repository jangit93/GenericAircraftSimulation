
[Atmosphere] = importdata('../ModuleTest/Output/AtmosphereTestData.txt',' ',1);

Altitude = -Atmosphere.data(:,1);
Rho = Atmosphere.data(:,2);
Temperature =  Atmosphere.data(:,3);
Pressure =  Atmosphere.data(:,4);
SpeedOfSound =  Atmosphere.data(:,5);

figure(1)
subplot(2,2,1)
plot(Altitude,Rho);
xlabel('Altitude [m]')
ylabel('\rho [Kg/m^3]')
grid on
subplot(2,2,2)
plot(Altitude,SpeedOfSound)
xlabel('Altitude [m]')
ylabel('a [m/s]')
grid on
subplot(2,2,3)
plot(Altitude,Temperature)
xlabel('Altitude [m]')
ylabel('T [K]')
grid on
subplot(2,2,4)
plot(Altitude,Pressure)
xlabel('Altitude [m]')
ylabel('P [Pa]')
grid on