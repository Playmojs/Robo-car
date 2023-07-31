#%%

import numpy as np
import matplotlib.pyplot as plt
data = np.loadtxt("d:/Programs/Github Repositories/Robo-car/data/sensor_test_2_400_ms.csv")

# %%
# Finding the means for all the scans:
means = np.round(np.nanmean(data,0),3)
medians = np.round(np.nanmedian(data, 0),3)
print(means)
print(medians)

#%%
# Manually looking at individual histograms:
scan_number = 33
bins = np.linspace(0,350,61)
plt.hist(data[:,scan_number],bins)
print("Mean:", means[scan_number], "Median:", medians[scan_number])

# %%
#Looking at 36 of the 37 values:

fig, axs = plt.subplots(6,6)
fig.set_figwidth(32)
fig.set_figheight(25)
bins = np.linspace(0,350,61)

for ax, scan, mean, median in zip(axs.flatten(), data.transpose(), means, medians):
    ax.hist(scan,bins)
    ax.set_title(f"Mean: {mean}  Median: {median}")
    ax.get_yaxis().set_visible(False)
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.spines['left'].set_visible(False)





# %%
