%% ////////////////////////////////////////////////////////////////////////
%
% Title       : evaluation.m
%
% Description : evaluation of simulation
%
% Version     : 1.0
%
% Date        : 
%
% Input-Data  :  all structures
%
% Output-Data :  specific plots
%
%%//////////////////////////////////////////////////////////////////////////

function [] = evaluation(t,...
                         Aerodynamic,...
                         Airframe,...
                         Autopilot,...
                         AircraftData,...
                         Guidance)

%//////////////////////////////////////////////////////////////////////////
% trajcetory and velocity
%//////////////////////////////////////////////////////////////////////////
h1 = figure('Name','Trajcetory');
subplot(311)
plot3(Airframe.posNED(1,1:t),Airframe.posNED(2,1:t),-Airframe.posNED(3,1:t),'r',...
       Guidance.s_x(1,1:t),Guidance.s_y(1,1:t),-Guidance.s_z(1,1:t),'k--');
grid on
xlabel('X_{NED}')
ylabel('Y_{NED}')
zlabel('Z_{NED}')
legend('Trajectory','commanded Trajectory')
title('3D Trajectory')

subplot(312)
plot(1:t,Airframe.posNED(3,1:t),'r',...
      1:t,Guidance.s_z(1,1:t),'k--')
grid on
xlabel('Time [s]')
ylabel('Z_{NED}')
axis auto
legend('Trajectory','commanded Trajectory','Location','eastoutside')
title('Trajectory x-z-plane')

subplot(313)
plot(1:t,Airframe.posNED(2,1:t),'r',...
      1:t,Guidance.s_y(1,1:t),'k--')
legend('Trajectory','commanded Trajectory','Location','eastoutside')
grid on
xlabel('X_{NED}')
ylabel('Y_{NED}')
axis auto
title('Trajectory x-y-plane')

%//////////////////////////////////////////////////////////////////////////
% pitch axis parameter over time
%//////////////////////////////////////////////////////////////////////////
h2 = figure('Name','Pitch Axis');
subplot(511)
plot(1:t,Aerodynamic.Alpha(1,1:t),'r')
xlabel('Time [s]')
ylabel('\alpha [°]')
grid on
title('angle of attack')

subplot(512)
plot(1:t,Airframe.EulerAngles(2,1:t)*180/pi,'r')
xlabel('Time [s]')
ylabel('\theta [°]')
grid on
title('pitch angle')

subplot(513)
plot(1:t,Airframe.Gamma(1,1:t)*180/pi,'r')
xlabel('Time [s]')
ylabel('\gamma [°]')
grid on
title('flight path angle')

subplot(514)
plot(1:t,Airframe.rotRateBody(2,1:t),'r')
grid on
xlabel('Time [s]')
ylabel('q [rad/s]')
grid on
title('pitch rate')

subplot(515)
plot(1:t,Airframe.Eta(1,1:t)*180/pi,'r')
xlabel('Time [s]')
ylabel('\eta [°]')
grid on
title('elevator angle')

%//////////////////////////////////////////////////////////////////////////
% roll axis parameter over time
%//////////////////////////////////////////////////////////////////////////
 h3 = figure('Name','Roll Axis');

subplot(311)
plot(1:t,Airframe.EulerAngles(1,1:t)*180/pi,'r')
xlabel('Time [s]')
ylabel('\phi [°]')
grid on
title('roll angle')

subplot(312)
plot(1:t,Airframe.Xi(1,1:t)*180/pi,'r')
grid on
xlabel('Time [s]')
ylabel('\xi [°]')
title('aileron angle')

subplot(313)
plot(1:t,Airframe.rotRateBody(1,1:t),'r')
xlabel('Time [s]')
ylabel('p [rad/s]')
grid on
title('roll rate')

%//////////////////////////////////////////////////////////////////////////
% yaw axis parameter over time
%//////////////////////////////////////////////////////////////////////////
h4 = figure('Name','Yaw axis');
subplot(311)
plot(1:t,Aerodynamic.Beta(1,1:t)*180/pi,'r',...
      1:t,Guidance.Beta_com(1,1:t)*180/pi,'k--')
xlabel('Time [s]')
ylabel('\beta [°]')
grid on
legend('\beta','\beta_{com}','location','best')
title('angle of sideslip')

subplot(312)
plot(1:t,Airframe.Zeta(1,1:t)*180/pi,'r')
grid on
xlabel('Time [s]')
ylabel('\zeta [°]')
title('rudder angle')

subplot(313)
plot(1:t,Airframe.rotRateBody(3,1:t),'r')
grid on
xlabel('Time [s]')
ylabel('r [rad/s]')
title('yaw rate ')

%//////////////////////////////////////////////////////////////////////////
% velocity and thrust stick position over time
%//////////////////////////////////////////////////////////////////////////

h5 = figure('Name' , 'Velocity');
subplot(211)
plot(1:t,Airframe.StickPos(1,1:t)*100,'r')
grid on
title('Thrust Stick Position \delta ')
xlabel('Time [s]')
ylabel('\delta [%]')
title('Thrust Stick Position')


subplot(212)
plot(1:t,Airframe.V_absolut(1,1:t),'r',...
     1:t,Guidance.Velocity_com(1,1:t),'k--')
xlabel('Time [s]')
ylabel('V [m/s]')
title('absolut Velocity')
grid on
title('Velocity')
legend('V','V_{com}','Location','best')

h6 = figure('Name','G-Force');
subplot(311)
plot(1:t,Aerodynamic.A(1,1:t)/(AircraftData.mass*9.80665),'r')
grid on
title('G-Force')
xlabel('Time [s]')
ylabel('N')

subplot(312)
plot(1:t,Airframe.EulerAngles(1,1:t)*180/pi,'r',...
    1:t,Guidance.Phi_com(1,1:t)*180/pi,'k--')
grid on
xlabel('Time [s]')
ylabel('\phi [°]')
title('Roll Angle')
legend('\phi','\phi_{com}','Location','best')


subplot(313)
plot(1:t,Airframe.EulerAngles(2,1:t)*180/pi,'r',...
    1:t,Guidance.Theta_com(1,1:t)*180/pi,'k--')
grid on
xlabel('Time [s]')
ylabel('\theta')
title('Pitch Angle')
legend('\theta','\theta_{com}','Location','best')


figure('Name','Body Accelerations [m/s^2]')
subplot(311)
plot(1:t-1,Airframe.accBody(1,1:t-1),'r',...
     1:t-1,Guidance.accBody(1,1:t-1),'k--');
grid on
xlabel('Time [s]')
ylabel('a_x')
title('Acceleration x_{body}')
legend('real','BodyCom')

subplot(312)
plot(1:t-1,Airframe.accBody(2,1:t-1),'r',...
     1:t-1,Guidance.accBody(2,1:t-1),'k--');
grid on
xlabel('Time [s]')
ylabel('a_y')
title('Acceleration y_{body}')
legend('real','BodyCom')

subplot(313)
plot(1:t-1,Airframe.accBody(3,1:t-1),'r',...
     1:t-1,Guidance.accBody(3,1:t-1),'k--');
grid on
xlabel('Time [s]')
ylabel('a_z')
title('Acceleration z_{body}')
legend('real','BodyCom')

h15 = figure(251);
plot(1:t-1,Airframe.accBody(2,1:t-1)/9.80665,'r',...
     1:t-1,Guidance.accBody(2,1:t-1)/9.80665,'k--');
grid on
xlabel('Time [s]')
ylabel('n_y')
legend('real','BodyCom')
set(gca,'Fontsize',18)


h16 = figure(251);
plot(1:t-1,Airframe.accBody(3,1:t-1)/9.80665,'r',...
     1:t-1,Guidance.accBody(3,1:t-1)/9.80665,'k--');
grid on
xlabel('Time [s]')
ylabel('n_z')
legend('real','BodyCom')
set(gca,'Fontsize',18)

h17 = figure(250);
plot(1:t,Aerodynamic.Alpha(1,1:t),'r',...
     1:t,Guidance.alpha_com(1,1:t)*180/pi,'k--')
xlabel('Time [s]')
ylabel('\alpha [°]')
grid on
axis([0 t 3 7])
set(gca,'Fontsize',18)

print(h17,'-dpdf','-r1200','AlphaCOm.pdf'); 
print(h15,'-dpdf','-r1200','Ny.pdf'); 
print(h16,'-dpdf','-r1200','Nz.pdf'); 

end
