class Data:

    def __init__(self, data):
        data.sort()
        self.__data = data
        self.low = 0
        self.high = len(self.__data) - 1
    
    def binsearch(self, item):
        location = 0
        while (self.low <= self.high) and (location == 0):
            mid = (self.low + self.high) // 2
            if item == data[mid]:
                location = mid
            elif item < data[mid]:
                self.high = mid - 1
            else:
                self.low = mid + 1
        return location 

data=[1,3,5,6,7,9,10,14,17,19]

D = Data(data)
n = int(input("Input : "))
location = D.binsearch(n)
print("Index : ",location)