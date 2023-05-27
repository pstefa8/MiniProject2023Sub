import matplotlib.pyplot as plt

def appendToPAT(fileLine):
    if(fileLine==''):
        return
    global Pressure, Altitude, Temperature
    measurmentArray=fileLine.split(", ")
    Pressure.append(float(measurmentArray[0]))
    Altitude.append(float(measurmentArray[1]))
    Temperature.append(float(measurmentArray[2]))

Pressure=[]
Altitude=[]
Temperature=[]

file = open("OUTPUT.TXT", "r")
fileContents=file.read()
file.close()

fileLineArray = fileContents.split("\n")

for fileLine in fileLineArray:
    appendToPAT(fileLine)
print(Pressure)

plt.figure(1)
plt.plot(range(0,len(Pressure)), Pressure, '.')
plt.ylabel('Pressure (hPa)')
plt.xlabel('Time')

plt.figure(2)
plt.plot(range(0,len(Altitude)), Altitude, '.')
plt.ylabel('Altitude (m)')
plt.xlabel('Time')

plt.figure(3)
plt.plot(range(0,len(Temperature)), Temperature, '.')
plt.ylabel('Temperature (C)')
plt.xlabel('Time')
plt.show()
