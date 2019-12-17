```python
# Basic numpy array
import numpy as np
ar = np.zeros((2,3),dtype=np.float64)
print(ar,'\n')
print('metadata : size={0}, bytes={1}, dim={2}, shape={3}'.format(ar.size,ar.nbytes,ar.ndim,ar.shape))
```

    [[0. 0. 0.]
     [0. 0. 0.]] 
    
    metadata : size=6, bytes=48, dim=2, shape=(2, 3)
    


```python
# reshape (copies data)
x = np.arange(1,13,1)
y = np.reshape(x,(2,2,3))
print(y,'\n')
print('metadata : size={0}, bytes={1}, dim={2}, shape={3}'.format(y.size,y.nbytes,y.ndim,y.shape))
```

    [[[ 1  2  3]
      [ 4  5  6]]
    
     [[ 7  8  9]
      [10 11 12]]] 
    
    metadata : size=12, bytes=48, dim=3, shape=(2, 2, 3)
    


```python
# view (does not copy)
z = y[0,:,:]
z[:] = 0
print(y,'\n')
print('metadata : size={0}, bytes={1}, dim={2}, shape={3}'.format(y.size,y.nbytes,y.ndim,y.shape))
```

    [[[ 0  0  0]
      [ 0  0  0]]
    
     [[ 7  8  9]
      [10 11 12]]] 
    
    metadata : size=12, bytes=48, dim=3, shape=(2, 2, 3)
    
