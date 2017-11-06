#For experiment A
import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('spikes_A.txt')

select= np.array([d for d in data if d[1] < 30])
data1= select.transpose()
pl.scatter(0.1*data1[0],data1[1],alpha=0.8, edgecolors='none');
pl.show();

n, bins, patches = pl.hist(0.1*data1[0], 50, normed=0, alpha=0.75)
pl.show();

#------------------------------------------------------------------------------------------
#For experiment B
import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('spikes_B.txt')

select= np.array([d for d in data if d[1] < 30])
data1= select.transpose()
pl.scatter(0.1*data1[0],data1[1],alpha=0.8, edgecolors='none');
pl.show();

n, bins, patches = pl.hist(0.1*data1[0], 50, normed=0, alpha=0.75)
pl.show();

#------------------------------------------------------------------------------------------
#For experiment C
import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('spikes_C.txt')

select= np.array([d for d in data if d[1] < 30])
data1= select.transpose()
pl.scatter(0.1*data1[0],data1[1],alpha=0.8, edgecolors='none');
pl.show();

n, bins, patches = pl.hist(0.1*data1[0], 50, normed=0, alpha=0.75)
pl.show();

#------------------------------------------------------------------------------------------
#For experiment D
import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('spikes_D.txt')

select= np.array([d for d in data if d[1] < 30])
data1= select.transpose()
pl.scatter(0.1*data1[0],data1[1],alpha=0.8, edgecolors='none');
pl.show();

n, bins, patches = pl.hist(0.1*data1[0], 50, normed=0, alpha=0.75)
pl.show();
