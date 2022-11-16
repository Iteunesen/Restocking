with open("input.txt") as f:
    lines = f.readlines()

locations = lines[0][0]
highways = lines[0][2]
time = lines[0][4]

lines = lines[1:]
print (locations, highways, time)

edges = []

for line in lines:
    edges.append([int(line[0]), int(line[2]), int(line[4]), int(line[6])])
print(edges)
