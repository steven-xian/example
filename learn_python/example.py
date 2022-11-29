# %%
import numpy as np

x = np.array([[1,2], [3,4],[5,6]])
y = x[[0,1,2], [0,1,0]]

print(x)
print(y)

print(x[[0,1,2,2,1,1]])

# %%
x1 = np.array([[0,1,2],[3,4,5],[6,7,8],[9,10,11]])
print(x1)

rows = np.array([[0,0],[3,3]])
cols = np.array([[0,2],[0,2]])
print(rows)
print(cols)
print(x1[rows, cols])

# %%
a = np.array([[1,2,3],[4,5,6],[7,8,9]])

b = a[1:3, 1:3]
print(b)

c = a[1:3,[1,2]]
print(c)

d = a[...,1:]
print(d)

# %%
x = np.array([[0,1,2],[3,4,5],[6,7,8],[9,10,11]])
print(x)

print(x[x <= 5])

# %%
a = np.array([np.nan, 1, 2, np.nan, 3, 4,5])
print(a[~np.isnan(a)])
print(a[np.isnan(a)])

# %%
x = np.arange(9)
print(x)

x2 = x[[0,6]]
print(x2)

# %%
x = np.arange(32).reshape(8,4)
print(x)
print("\n")
print(x[[1,5,7,2]])
print("\n")
print(x[[0,3,1,2]])
print("\n")
print("x array")
print(x[[1,5,7,2],[0,3,1,2]])
print("\n")
print(x[np.ix_([1,5,7,2],[0,3,1,2])])

# %%
b = np.array([1,2,3])
print(np.tile(b, (2,1)))

# %%
a = np.arange(8).reshape(2,2,2)
print(a)
# print(np.where(a==6))
# print(a[np.where(a==6)])
b = np.rollaxis(a, 2, 1)
print(b)

# %%
a = [i for i in range(100) if i % 2 != 0 and i >= 11]
print(a)
b = [i for i in range(102) if i %2 != 0 and i >= 13]
print(b)

print(np.sum(np.multiply(a, b)))

# %%
x = [i for i in range(100) if i % 2 == 0 and i >= 10]
print(x)
print(sum(x))
print(450+2*22*45)

# %%
def createnum(a, b, l):
    n = [a,b]
    while True:
        if len(n) == l:
            break
        s = str(n[-1]+n[-2])
        for j in range(len(s)):
            n.append(int(s[j]))

    return n
num = createnum(9,6,2019)

print(len(num))    
print(sum(num))
print(num)


