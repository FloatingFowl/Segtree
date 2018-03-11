filename = "data_3_100.txt"
content = []
every = 0
summer = [0 for i in range(3)]
limit = 3

with open(filename) as f:
    content = f.readlines()
print len(content)

for i in content:
    summer[every] += float(i)
    every = (every + 1) % limit

print summer
