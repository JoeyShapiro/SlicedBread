# using a png sounds easier than making a ui
# Import the necessary libraries
from PIL import Image
from numpy import asarray
  
  
# load the image and convert into 
# numpy array
img = Image.open('cells/left.jpg')
numpydata = asarray(img)
matrix = []
cell = ['{']
  
# data
print(numpydata.shape)
for e in numpydata:
    row = []
    for c in e:
        color = list(c)
        if color == [0, 0, 0]:
            row.append('O')
        elif color == [255, 255, 255]:
            row.append(' ')
        else:
            row.append('?')
    matrix.append(row)

for i in matrix:
    cellRow = []
    cellRow.append('{')
    for j in i:
        print(j, end="")
        cellRow.append('\''+j+'\'')
        cellRow.append(',')
    print()
    del cellRow[-1] # remove last comma of row
    cellRow.append('}')
    cellRow.append(',')
    cell.append(cellRow)
cell.append('}')

for i in cell:
    for j in i:
        print(j, end="")
    print()

# TPI
# change chacter based on connections
# kinda hard in python
# for i in range(len(matrix)):
#     cellRow = []
#     cellRow.append('{')
#     for j in range(len(matrix[0])):
#         print(matrix[i][j], end="")
#         if matrix[i][j+1] == 'O':
#             cellRow.append('\'|\'')
#         else:
#             cellRow.append('\''+matrix[i][j]+'\'')
#         cellRow.append(',')
#     print()
#     del cellRow[-1] # remove last comma of row
#     cellRow.append('}')
#     cellRow.append(',')
#     cell.append(cellRow)
# cell.append('}')