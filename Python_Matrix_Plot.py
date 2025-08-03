import matplotlib.pyplot as plt

sizes = [250, 500, 750, 1000, 2000]
threads = [1, 2, 4, 8]
times = [
    [0.000601 ,0.000475 ,0.000359 ,0.000472 ],
    [0.002182 ,0.001003 ,0.000949 ,0.000701 ],
    [0.002054 ,0.001012 ,0.001144 ,0.001140 ],
    [0.003318 ,0.002979 ,0.002015 ,0.001892 ],
    [0.016763 ,0.008028 ,0.006162 ,0.004694]
]

plt.figure(figsize=(10, 6))
for idx, N in enumerate(sizes):
    speedup = [times[idx][0]/t for t in times[idx]]
    plt.plot(threads, speedup, marker='o', label=f'{N}x{N}')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup')
plt.title('Speedup vs Number of Threads for Matrix Addition')
plt.xticks(threads)
plt.legend(title='Matrix Size')
plt.grid(True)
plt.show()
