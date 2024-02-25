with open("data.txt", "r+") as file:
    list = file.read()
    list = [int(x) for x in list.split()]
    print(list)
    for i in range(len(list)):
        j = i-1
        key = list[i]
        while(j >= 0 and list[j] > key):
            list[j+1] = list[j]
            j -= 1
        list[j+1] = key
    print(list)
    file.write(str(list))