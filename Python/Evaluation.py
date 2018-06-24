from matplotlib import pyplot as plt
import math
def readData(Filename):
    try:
        with open(Filename, "r") as myFile:
            # read in all lines ignoring Header
            File = myFile.readlines()[2::]

            rows = len(File)

            Data = [[] for i in range(len(File[0].split()))]

            # split data to columns
            for i in range(0, rows):
                temp = File[i].split()
                for ii in range(0, len(File[0].split())):
                    Data[ii].append(float(temp[ii]))
        return Data
    except:
        print("Kann"+Filename+"nicht öffnen")
        return None




if __name__ == "__main__":

    #read in tables
    Airframe = readData("../Output/AirframeData.txt")
    Guidance = readData("../Output/GuidanceData.txt")
    Thrust = readData("../Output/EngineData.txt")
    Aerodynamic = readData("../Output/AerodynamicData.txt")
    Navigation = readData("../Output/NavigationData.txt")
    Actuator = readData("../Output/ActuatorData.txt")
    IMU = readData("../Output/IMUData.txt")

    # show trajectory
    if Navigation != None:
        plt.figure("Trajectory")
        plt.subplot(211)
        plt.plot(Navigation[0], Navigation[4])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("Position y-NED [m")
        plt.grid()
        plt.subplot(212)
        plt.plot(Navigation[2], Navigation[3])
        plt.xlabel("Position x-NED [m]")
        plt.ylabel("Position y-NED [m")
        plt.grid()
    else:
        print("Could not plot Trajectory")

    # plot longitudinal movement
    if Airframe and Aerodynamic and IMU and Navigation and Actuator != None:
        plt.figure("Longitudinal")
        plt.subplot(511)
        plt.plot(Airframe[0], Aerodynamic[1])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("Angle of Attack")
        plt.grid()
        plt.subplot(512)
        plt.plot(Airframe[0], Navigation[6])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("theta")
        plt.grid()
        plt.subplot(513)
        plt.plot(Airframe[0], IMU[1])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("pitch rate")
        plt.grid()
        plt.subplot(514)
        plt.plot(Airframe[0], Airframe[1])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("Gamma")
        plt.grid()
        plt.subplot(515)
        plt.plot(Airframe[0], Actuator[0])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("Elevator")
        plt.grid()
    else:
        print("Could not plot longitudinal")

    #lateral movement
    if Airframe and Aerodynamic and IMU and Navigation and Actuator != None:
        plt.figure("lateral-roll")
        plt.subplot(311)
        plt.plot(Airframe[0], Navigation[5])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("phi")
        plt.grid()
        plt.subplot(312)
        plt.plot(Airframe[0], IMU[0])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("roll rate")
        plt.grid()
        plt.subplot(313)
        plt.plot(Airframe[0], Actuator[1])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("Ailerons")
        plt.grid()

        #lateral movement
        plt.figure("lateral-yaw")
        plt.subplot(511)
        plt.plot(Airframe[0], Aerodynamic[2])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("Angle of Sideslip")
        plt.grid()
        plt.subplot(512)
        plt.plot(Airframe[0], Navigation[7])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("psi")
        plt.grid()
        plt.subplot(513)
        plt.plot(Airframe[0], IMU[2])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("yaw rate")
        plt.grid()
        plt.subplot(514)
        plt.plot(Airframe[0], Airframe[2])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("Chi")
        plt.grid()
        plt.subplot(515)
        plt.plot(Airframe[0], Actuator[2])
        plt.xlabel("Flighttime [s]")
        plt.ylabel("Rudder")
        plt.grid()
    else:
        print("Could not plot lateral")



    plt.show()