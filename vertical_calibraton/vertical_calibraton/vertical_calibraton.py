import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import math

from dataclasses import dataclass, field
from math import *
from numpy.core.fromnumeric import size


@dataclass
class Segments:
    def __init__(self, beg, end , indx, val):
        self.begin = beg
        self.end = end
        self.index = indx
        self.value = val 

@dataclass
# границы участка
class Borders:
     def __init__(self, beg, end):
        self.begin = beg
        self.end = end

@dataclass
class Site:

    def koef_find(self):
        x_cord = list(range(self.borders.begin, self.borders.end))
        sum_x = sum(x_cord)
        sum_y = sum(self.data)
        sum_x2 = sum( square(x_cord))
        sum_xy = 0
        for i in range(len(self.data)): sum_xy += x_cord[i] * self.data[i]
        d = (len(self.data) * sum_x2) - (sum_x * sum_x)

        self.angle_k  = ((sum_xy * len(self.data))-(sum_x*sum_y))/d
        self.line_k = ((sum_x2 * sum_y)-(sum_xy*sum_x))/d



    def __init__(self, arr=[] , beg = 0 , end = 0):
        self.angle_k = 0
        self.line_k = 0
        self.data  = []
        self.borders = Borders(beg, end) 
        if(arr is None):
            a = 5
        else:
            for i in range(len(arr)):
                self.data.append(arr[i])
            if(len(arr) > 1):
                self.koef_find()

    def __init__(self, arr=[] , bord = Borders(0,3)):
        self.angle_k = 0
        self.line_k = 0
        self.borders = bord
        self.data = []
        if(arr is None):
            a = 5
        else:
            for i in range(self.borders.begin, self.borders.end):
                self.data.append(arr[i])
            if(len(arr) > 1):
                self.koef_find()

    def __lt__(self, other):
        return (self.angle_k < other.angle_k)

    def __eq__(self, other):
        return (self.angle_k == other.angle_k)

# возведение всего списка в квадрат 
def square(list):
    return [i ** 2 for i in list]



# быстрый вывод графика на экран 
def fast_print(arr):
    x = range(len(arr))
    grph = plt.plot(x, arr)
    plt.show()

# вывод двыух графикоф на экран 
def print_two(begin_1 , y_1, begin_2, y_2):
    x_1 = list( range(  begin_1, (begin_1 + len(y_1))   ))
    x_2 = list( range(  begin_2, (begin_2 + len(y_2))   ))
    plt.plot(x_1, y_1)
    plt.title(name)
    plt.plot(x_2, y_2)
    plt.show()

# гнаходит испорченный пиксель и заполн€ет его с помощью линейной интерпол€ции , а так же выводит его на экрарн 
def broken_pixel_data_rstr(mass):
   # пиксель считаетс€ разбитым если его значение равно 0 а соседние не равно нулю  
   for i in range(len(mass)):
       for j in range(len(mass[i])):
           if(mass[i][j] == 0):
              if((mass[i-1][j] != 0) and (mass[i+1][j] != 0)):
                  # линейна€ интерпол€ци€ сломанного пиксел€ сосе€дми по столбцу
                  x1 = i -1
                  x2 = i+1
                  x = i
                  y1 = mass[x1][j]
                  y2 = mass[x2][j]
                  mass[i][j] = y1 + ((y2 - y1) * (x - x1))/(x2 - x1)
                  
                  print("pixel x =",i,"y =" ,j ,"is broken",sep =" ")

# линейное сглаживание
def SMA(window, iterations, arr = [] ):
    anser = arr
    buf =[]
    sma = lambda b , arr: sum( arr[b.begin:b.end])/(b.end - b.begin)

    for i in range(iterations):    
        for j in range(window, len(anser)):
            brd = Borders((j - window) , j)
            buf.append(sma(brd, anser))
        anser = list(buf)
        buf.clear()
    return(anser)


#path =  'D:/work(DLNP)/Calibration_prj/teast_dir/'
path = 'D:/work(DLNP)/Calibration_prj/spectrs_named_Test/'
for itr in range(31):
    name = itr
    name =  '{}_Event.txt'.format(name)
    file = open(path + name);
    mass = np.loadtxt(file);
    file.close()
    name = name + ".png"

    sector =[]

    for i in range(len(mass)):
        sector.append(list(mass[i][102:130]))

    broken_pixel_data_rstr(sector)

    lines = []
    for i in range(len(sector[0])):
        line = []
        for j in range(len(sector)):
            line.append(sector[j][i])
        lines.append(list(line))


    window = 10
    sma_sector =[]
    sites =[]
    index = []
    for i in range(len(lines)):
        sma_line = SMA(window, 3, lines[i])
        sites.append( Site(sma_line, Borders(0,len(sma_line))) )
        sma_sector.append(sma_line)

        print (i, sites[-1].angle_k ,sep =" : ")   
        
    #for i in range(1,len(sites)):
    #    if((index[i] - index[i-1]) != 1): 
    #        sites = list(sites[0:i])

    #a = list(map(list, zip(*sma_sector)))

       


    sns.heatmap(sector)
    plt.show()



