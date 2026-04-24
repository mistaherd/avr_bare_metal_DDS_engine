import numpy as np 
import matplotlib.pylab as plt
fc =62725
freq_points=np.linspace(0,fc*2,255)
ideal_response=np.array([ 1 if freq_points[i] <fc else 0 for i in range(len(freq_points)) ])
plt.plot(freq_points,ideal_response)
plt.xlabel("Frequencz (hz)")
plt.ylabel("mock amplitdue (volts)")

plt.show()
