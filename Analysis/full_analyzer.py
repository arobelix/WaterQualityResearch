import numpy as np
import matplotlib.pyplot as plt
import histo 

#pH = np.genfromtxt('ARC Pool\conductivity.txt')
#pH = pH[10:]
#
#time= np.linspace(0,100,100)
#M_pH = np.mean(pH)
#Std_pH = np.std(pH)
#Med_pH = np.median(pH)
#
#min_pH = min(pH)
#max_pH = max(pH)
#
#
#histo.fullhist(pH, 10,"pH","N","pH Sample 1")
#print("Mean pH: ", M_pH, "STD: ", Std_pH, "Median:", Med_pH)
#print("Min pH: ", min_pH, "Max pH: ", max_pH)
#print(len(pH))
#
#plt.plot(pH)
#plt.xlabel("sample")
#plt.ylabel("pH")
#plt.title("pH at each sample")
#plt.show()

#Function to show Histogram, Time plot and values
def fullanalysis(folder, variable, bins):
    file = "%s\%s.txt" % (folder, variable)
    #put data in variable data
    data = np.genfromtxt(file)
    #truncate string if needed
    #data = data[1:]
    
    #Histogram
    h_title = "%s Histogram" % (variable)
    histo.fullhist(data, bins, variable,"N",h_title)
    
    #Time function
    plt.plot(data)
    plt.xlabel("sample")
    plt.ylabel(variable)
    t_title = "%s at each sample" % (variable)
    plt.title(t_title)
    plt.show()
    
    #print values
    print("Mean: ", np.mean(data), "STD: ", np.std(data), "Median:", np.median(data))
    print("Min: ", min(data), "Max: ", max(data))
    print("Samples: ", len(data))
    
#execute function
fullanalysis("ARC Fountain", "turbidity", 10)
    
    
    