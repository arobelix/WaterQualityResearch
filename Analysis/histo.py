import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

#x-axis
t = np.linspace(0,10,num=5)
x = 0 
#Histogram stuff
def fullhist(data,num_bins,xlabel,ylabel,title):
    #data analysis
    data_mean = np.mean(data)
    data_std = np.std(data)
    #create histogram
    n, bins, patches = plt.hist(data,num_bins,normed=0,facecolor='blue',alpha=0.8)
    #Plot mean and standard deviations
    plt.axvline(x= data_mean, color='r')
    plt.axvline(x= data_mean + data_std, color='g')
    plt.axvline(x= data_mean - data_std, color='g')
    #Plot labels and titles
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    #slight adjustment
    plt.subplots_adjust(left=0.15)
    plt.show()
    return;
    plt.hist
    

#function for plot with labels and title
def fullplot(xval, yval, xlabel, ylabel, title):
    fig = plt.figure()
    ax = fig.gca()
    ax.set_aspect("equal")
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.set_title(title)
    ax.plot(t,cond)
    return;



#mean_cond = np.mean(cond)