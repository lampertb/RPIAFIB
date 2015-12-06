import sys
import numpy as np
from scipy import signal

# For testing
import csv

defaultWindowSize=120
defaultMinSNR=2
defaultNoisePercentage=10

defaultSampleRate=250

#The find peaks function takes in an array of data
#It returns an array of the peak locations after running the wavelet transform
def findPeaks(dataArray, windowSize=defaultWindowSize):
   peakIndex=signal.find_peaks_cwt(dataArray, np.arange(1, windowSize), min_snr=defaultMinSNR, noise_perc=defaultNoisePercentage)
   #print peakIndex
   return peakIndex

#Calcuate the time interval between samples
def getRR(peakIndex, sampleRate=defaultSampleRate):
    rr_data = []
    for i in range(0, len(peakIndex)-1):
        diff = peakIndex[i+1]-peakIndex[i]
        #print "peak1 {0} - peak2 {1} Diff {2}".format(peakIndex[i+1], peakIndex[i], diff)
        timeDelay = diff/float(sampleRate) #Get the time difference between samples
        rr_data.append(timeDelay)
        #sum+=timeDelay #create an average
    #print "Sum {0}, len {1}".format(sum, len(peakIndex))
    return rr_data

#AFib Detection Algorithm
from scipy.stats import norm
def Fib_Detection( x , seglen = 128):
    N = len(x)
    tprmean = 0.65625; tprvar = 0.001369222
    # TPR mean and variance from rozinn database
    afstats = {};
    afstats['avg'] = [];
    afstats['rmssd'] = [];
    afstats['tpr'] = [];
    afstats['se'] = [];
    afstats['tprstat'] = [];
    afstats['count'] = [];

    for i in range (0,N-seglen+1):
        perc = i/N*100
        j = 0
        segment = x[i:i+seglen]

        #******************** Remove 16 outlier ******************************** 
        #* In the outlier removal, 8 maximum and 8 minimum values are discarded 
        #***********************************************************************
        segment_outlier = segment[:]
        for j in range (0,8):
            segment_outlier.remove(max(segment_outlier))
            segment_outlier.remove(min(segment_outlier))
        #print segment
        #print segment_outlier

        # Get mean
        afstats['avg'].append(np.mean(segment))

        # RMSSD
        difference = np.subtract(segment_outlier[2:seglen-16], segment_outlier[1:seglen-17])
        afstats['rmssd'].append(np.sqrt(np.sum(np.power(difference, 2))/(seglen-17))/afstats['avg'][i-1])

        # TPR
        j = 0
        for k in range (1,seglen-1):
            if ((segment[k]-segment[k-1])*(segment[k]-segment[k+1])>0):
                j = j+1
        afstats['tpr'].append(j/(seglen-2.0))

        # Shannon Entropy
        seg_max = np.max(segment_outlier)
        seg_min = np.min(segment_outlier)
        step = (seg_max-seg_min)/16.0;
        entropy = 0;
        if (step!=0):
            group1 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
            for j in range(0,112):
                z = int(np.around((segment_outlier[j]-seg_min)/step))
                group1[z] = group1[z]+1
            group1 = np.divide(group1,np.sum(group1)+0.0)
            for j in range (0,16):
                if (group1[j]>0):
                    entropy = entropy+group1[j]*np.log(group1[j])
        afstats['se'].append(entropy/-2.7726)

        # Compute the afstats
        afstats['tprstat'].append(norm.cdf(afstats['tpr'][i-1], tprmean, np.sqrt(tprvar)));
        if(afstats['rmssd'][i-1]>=0.1 and afstats['tprstat'][i-1]>0.0001 and afstats['tprstat'][i-1] <= 0.9999 and afstats['se'][i-1] >=0.7):
            afstats['count'].append(1)
        else:
            afstats['count'].append(0)
    return afstats      

#AFib Detection from ECG file
def afib_dect():
    inputFile="0403_Normal_tiny.csv"
    
    ECG=[]
    with open(inputFile,'rb') as csvfile:
    	reader = csv.DictReader(csvfile)
    	for row in reader:
    		ECG.append(float(row['ECG']))
    
    data=np.asarray(ECG)
    peakIndex=findPeaks(data, 200)
    rr_data = getRR(peakIndex)
    
    afstats = Fib_Detection(rr_data)
    
    # Print result to result.txt file
    outputFile = "result.txt"
    result = "%d"%sum(afstats['count']);
    fp = open(outputFile, 'r+')
    fp.write(result);
    fp.close()
    
    return sum(afstats['count']) > 1

afib_dect();
