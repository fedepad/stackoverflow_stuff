import pylab
import random
import numpy as np

sampleSize = 100


## Let's simulate the repeated throwing of a single six-sided die
singleDie = []
for i in range(sampleSize):
    newValue = random.randint(1,6)
    singleDie.append(newValue)

print "Results for throwing a single die", sampleSize, "times."
print "Mean of the sample =", pylab.mean(singleDie)
print "Median of the sample =", pylab.median(singleDie)
            #print "Standard deviation of the sample =", pylab.std(singleDie)
            #print
            #print

pylab.hist(singleDie, bins=[0.5,1.5,2.5,3.5,4.5,5.5,6.5] )
pylab.xlabel('Value')
pylab.ylabel('Count')
#pylab.savefig('singleDie.png')
pylab.show()




## What about repeatedly throwing two dice and summing them?
twoDice = []
for i in range(sampleSize):
    newValue = random.randint(1,6) + random.randint(1,6)
    twoDice.append(newValue)

print "Results for throwing two dices", sampleSize, "times."
print "Mean of the sample =", pylab.mean(twoDice)
print "Median of the sample =", pylab.median(twoDice)
#print "Standard deviation of the sample =", pylab.std(twoDice)

pylab.hist(twoDice, bins= pylab.arange(1.5,12.6,1.0))
pylab.xlabel('Value')
pylab.ylabel('Count')
#pylab.savefig('twoDice.png')
pylab.show()

#pylab.hist(twoDice, bins=pylab.arange(1.5,12.6,1.0), normed=1, histtype='step', cumulative=True)
#pylab.hist(twoDice, bins=pylab.arange(1.5,12.6,1.0), histtype='step', cumulative=True)
pylab.hist(twoDice, bins=pylab.arange(1.5,12.6,1.0), normed=1, histtype='step', cumulative=True)
pylab.xlabel('Value')
pylab.ylabel('Fraction')
pylab.show()

twod_cdf = np.array(twoDice)
norm = twod_cdf/12.


X_values = np.sort(twod_cdf)
F_values = np.array(range(sampleSize))/float(sampleSize)
pylab.plot(X_values, F_values)
pylab.show()



print twod_cdf
print norm
