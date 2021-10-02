import numpy as np
import matplotlib.pyplot as plt
import histo 


cond = np.genfromtxt('conductivity.txt')
pH = np.genfromtxt('ph.txt')
temp = np.genfromtxt('temperature.txt')
TDS = np.genfromtxt('tds.txt')
#turb = np.genfromtxt('turbidity.txt')

time= np.linspace(0,100,100)

#Mean and standard deviation for data
M_cond = np.mean(cond)
M_pH = np.mean(pH)
M_TDS = np.mean(TDS)
M_temp = np.mean(temp)
#M_turb = np.mean(turb)

Std_cond = np.std(cond)
Std_pH = np.std(pH)
Std_TDS = np.std(TDS)
Std_temp = np.std(temp)
#Std_turb = np.std(turb)

histo.fullhist(pH, 2,"pH","N","pH Sample 1")
print("Mean pH: ", M_pH, "STD: ", Std_pH)

histo.fullhist(temp, 2,"Temperature (*C)","N","Temp Sample 1")
print("Mean Temp: ", M_temp, "STD: ", Std_temp)

plt.ylim(0,14)
plt.plot(time, pH, 'r')
plt.show()

plt.ylim(15,30)
plt.plot(time, temp)








"""
histo1 = hb.histo("temperatures", 20, 20.5, 22.5)
histo1.hsetlabels("temperature", "N")
for i in temp:    
    histo1.hfill(i)
    
histo1.hprint()

histo2 = hb.histo("ph", 60, 0., 12.)
histo2.hsetlabels("ph","N")
for i in ph:
    histo2.hfill(i)
    
histo2.hprint()

histo3 = hb.histo("conductivity", 10, 0., 1)
histo3.hsetlabels("EC","N")
for i in cond:
    histo3.hfill(i)
    
histo3.hprint()

histo4 = hb.histo("tds", 10, 390., 430)
histo4.hsetlabels("tds","N")
for i in tds:
    histo4.hfill(i)
histo4.hprint()

histo5 = hb.histo("turbidity", 10, 390., 430)
histo5.hsetlabels("turbidity","N")
for i in turb:
    histo4.hfill(i)
histo5.hprint()
"""



"""
# temperature for number sample
temp1 = np.zeros(freq)
temp2 = np.zeros(freq)

# condcutivity for number sample
cond1 = np.zeros(freq)
cond2 = np.zeros(freq)

# tds for number sample
tds1 = np.zeros(freq)
tds2 = np.zeros(freq)

# turbidity for number sample
turb1 = np.zeros(freq)
turb2 = np.zeros(freq)

# ph for number sample
ph1 = np.zeros(freq)
ph2 = np.zeros(freq)

index = np.zeros(100)    

for i in range(data[:,0].size):
    # temp arrays
    if (data[i,0] == 1.0):
        if (data[i,1] == 1.0):
            temp1[math.floor(index[0])] = data[i,2]
            index[0] += 1
        if (data[i,1] == 2.0):
            temp2[math.floor(index[1])] = data[i,2]
            index[1] += 1
    
    # cond arrays
    if (data[i,0] == 2.0):
        if (data[i,1] == 1.0):
            cond1[math.floor(index[2])] = data[i,2]
            index[2] += 1
        if (data[i,1] == 2.0):
            cond2[math.floor(index[3])] = data[i,2]
            index[3] += 1
    
    # tds arrays      
    if (data[i,0] == 2.0):
        if (data[i,1] == 1.0):
            tds1[math.floor(index[4])] = data[i,2]
            index[4] += 1
        if (data[i,1] == 2.0):
            tds2[math.floor(index[5])] = data[i,2]
            index[5] += 1
    
    # turb arrays
    if (data[i,0] == 3.0):
        if (data[i,1] == 1.0):
            turb1[math.floor(index[6])] = data[i,2]
            index[6] += 1
        if (data[i,1] == 2.0):
            turb2[math.floor(index[7])] = data[i,2]
            index[7] += 1
    
    # ph arrays      
    if (data[i,0] == 4.0):
        if (data[i,1] == 1.0):
            ph1[math.floor(index[8])] = data[i,2]
            index[8] += 1
        if (data[i,1] == 2.0):
            ph2[math.floor(index[9])] = data[i,2]
            index[9] += 1
            
            
print(temp1)
print(temp2)
print(cond1)
print(cond2)
print(tds1)
print(tds2)
print(turb1)
print(turb2)
print(ph1)
print(ph2)
"""