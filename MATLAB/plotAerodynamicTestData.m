%% plot Aerodynamic polars
clear
close all
clc
%% read in data
[Aerodynamic] = readIn('AerodynamicTestData.txt',' ',1);


nAoA = Aerodynamic.data(1,9);
AoA = Aerodynamic.data(1:nAoA,6);

nMach = Aerodynamic.data(1,10);
ii = 1;
for i = nAoA:nAoA:nAoA*nMach
    Mach(ii) = Aerodynamic.data(i,7);
    ii = ii+1;
end

nEta  = Aerodynamic.data(1,11);
ii = 1;
for i = nAoA*nMach:nAoA*nMach:nAoA*nMach*nEta
    Eta(ii) = Aerodynamic.data(i,8)*180/pi;
    ii = ii+1;
end

for a = 1:nEta
    tempeta = Eta(a);
    if tempeta == 0
        break;
    end
end

CA  = Aerodynamic.data(:,1);
CM  = Aerodynamic.data(:,2);
CW  = Aerodynamic.data(:,3);
CZ = Aerodynamic.data(:,4);
CX = Aerodynamic.data(:,5);

Ca = reshape(CA,[nAoA,nMach,nEta]);
Cm = reshape(CM,[nAoA,nMach,nEta]);
Cw = reshape(CW,[nAoA,nMach,nEta]);
Cx = reshape(CX,[nAoA,nMach,nEta]);
Cz = reshape(CZ,[nAoA,nMach,nEta]);

%% eta = 0

figure ('Name','Lift and Drag Coefficient')
%C_A
subplot(221)
plot(AoA,Ca(:,:,1))
xlabel('\alpha [°]')
ylabel('C_A')
grid on 
for i=1:nMach
    textleg1(i)={['Ma = ' num2str(Mach(i))]};
end
legend(textleg1,'Location','best');
title('lift-coefficient')

%C_W
subplot(222)
plot(AoA,Cw(:,:,1))
xlabel('\alpha [°]')
ylabel('C_W')
grid on 
for i=1:nMach
    textleg2(i)={['Ma = ' num2str(Mach(i))]};
end
legend(textleg2,'Location','best');
title('drag-coefficient')

%C_W over C_A
subplot(223)
for u = 1:8
plot(squeeze(Cw(:,u,a)),squeeze(Ca(:,u,a)))
grid on 
hold on
xlabel('C_W')
ylabel('C_A')
 textleg3(u)={['Ma = ' num2str(Mach(u))]};
end
title('drag polar')
legend(textleg3,'Location','best');

%C_M @ eta = 0°
figure('Name','Pitching Moment Coefficient')
subplot(221)
plot(AoA,Cm(:,:,1))
xlabel('\alpha [°]')
ylabel('C_M')
grid on 
for i=1:nMach
    textleg4(i)={['Ma = ' num2str(Mach(i))]};
end
legend(textleg4,'Location','best');
etastring={['\eta = ' num2str(Eta(a)) ' [°]']};
title(etastring)

%C_M @ different elevator angles and constant mach number
subplot(222)
plot(AoA,squeeze(Cm(:,3,:)))
grid on 
xlabel('\alpha [°]')
ylabel('C_M')
for i=1:nEta
    textleg5(i)={['Eta = ' num2str(Eta(i))]};
end
legend(textleg5,'Location','best');
cm1string={['Ma = ' num2str(Mach(3))]};
title(cm1string)

%C_M @ different elevator angles and constant mach number
subplot(223)
plot(AoA,squeeze(Cm(:,3,:)))
xlabel('\alpha [°]')
ylabel('C_M')
grid on 
cm2string={['Ma = ' num2str(Mach(a))]};
title(cm2string)
for i=1:nEta
    textleg6(i)={['Eta = ' num2str(Eta(i))]};
end
legend(textleg6,'Location','best');

%C_M @ different elevator angles and constant mach number
subplot(224)
plot(AoA,squeeze(Cm(:,7,:)))
xlabel('\alpha [°]')
ylabel('C_M')
grid on 
for i=1:nEta
    textleg7(i)={['Eta = ' num2str(Eta(i))]};
end
legend(textleg7,'Location','best');
cm3string={['Ma = ' num2str(Mach(7))]};
title(cm3string)

figure('Name','Body fixed Coefficients')
%C_X
subplot(211)
plot(AoA,squeeze(Cx(:,:,a)))
xlabel('\alpha [°]')
ylabel('C_X')
grid on
for i=1:nMach
    textleg8(i)={['Ma = ' num2str(Mach(i))]};
end
legend(textleg8,'Location','best');
title('C_X')

%C_Z
subplot(212)
plot(AoA,squeeze(Cz(:,:,a)))
xlabel('\alpha [°]')
ylabel('C_Z')
grid on
for i=1:nMach
    textleg9(i)={['Ma = ' num2str(Mach(i))]};
end
legend(textleg9,'Location','best');
title('C_Z')