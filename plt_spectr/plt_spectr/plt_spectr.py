from typing import Sized
import numpy as np
import matplotlib.pyplot as plt
from math import *
from dataclasses import dataclass, field
from numpy.core.fromnumeric import size


@dataclass
class Segments:
    def __init__(self, beg, end , indx, val):
        self.begin = beg
        self.end = end
        self.index = indx
        self.value = val 

@dataclass
class Borders:
     def __init__(self, beg, end):
        self.begin = beg
        self.end = end

def square(list):
    return [i ** 2 for i in list]

def site_in_mass(arr=[]):
    buf =[]
    for i in range(len(arr)):
        buf.append(arr[i])
    return buf

@dataclass
class Site:

    def koef_find(self):
        x_cord =[]
        for i in range(self.borders.begin , self.borders.end): x_cord.append(i)
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

    def __lt__(self, other):
        return (self.angle_k < other.angle_k)

    def __eq__(self, other):
        return (self.angle_k == other.angle_k)

# для визулизации
def save_grph(arr , begin , end , name):
    x = range(begin , end)
    grph = plt.plot(x, arr[begin:end])
    plt.savefig(name)
    plt.close("all")

def print_grph(arr , begin , end):
    x = range(begin , end)
    grph = plt.plot(x, arr[begin:end])
    plt.show()

def fast_print(arr):
    x = range(len(arr))
    grph = plt.plot(x, arr)
    plt.show()

def print_two(begin_1 , y_1, begin_2, y_2):
    x_1 = list( range(  begin_1, (begin_1 + len(y_1))   ))
    x_2 = list( range(  begin_2, (begin_2 + len(y_2))   ))
    grph = plt.plot(x_1, y_1)
    plt.title(name)
    plt.plot(x_2, y_2)
    plt.show()

# нахождение углового и линейного коэфициента методом наименьших квадратов 
def finde_cof(x_cord=[] , y_cord=[]):
   
    sum_x = sum(x_cord)
    sum_y = sum(y_cord)
    sum_xy = 0
    sum_x2 = 0

    for i in range(len(x_cord)):
         a= x_cord[i] * x_cord[i]
         sum_x2 += a

    for i in range(len(x_cord)): sum_xy += x_cord[i] * y_cord[i]

    d = (len(x_cord) * sum_x2) - (sum_x * sum_x)
    koef =[]
    koef.append(((sum_xy * len(x_cord))-(sum_x*sum_y))/d)
    koef.append( ((sum_x2 * sum_y)-(sum_xy*sum_x))/d)

    return koef

# нахождение индекса локального минимума 
def find_local_min_index(arr , begin , end):
    local_min = [] 
    i = begin
    while i < end:
        if((arr[i] < arr[i+1]) & (arr[i] < arr[i - 1])):
            j = 0
            k = 0
            for j in range((i-1), begin , -1):
                if(arr[i] > arr[j]): break
            for k in range((i+1) , end):

                if(arr[i] > arr[k]): break                 
            local_min.append(Segments((j + 1), k, i ,arr[i]))
            i = k
        else: i = i +1
    
    if (len(local_min) > 1):      
       mini  = local_min[0].value
       indx = 0
       for j in range(1 ,(len(local_min))):
            if(mini > local_min[j].value):
                mini = local_min[j].value
                indx = j
       return local_min[indx]
    else: 
        return local_min[0]

#
def end_plato(arr , beg ,end):

    buf = find_local_min_index(arr, beg ,end)
    i  = buf.end
    while (arr[i] > buf.value):
        i  = i + 1

    return i

# нахождение гранимц плато
def finde_bordres_of_plateu( row =[]):
 
    arr = []
    for i in range(len(row)-2):
        arr.append(Site(row[i: (i+3)], i , (i + 3)))
 
    pborders = Borders(arr[arr.index(min(arr))].borders.end ,0)
    pborders.end = arr[ arr.index(min(arr[pborders.begin: len(arr)]))].borders.begin


    #buffer_arr =  row[pborders.begin:pborders.end ]
    #comporand = int (sum( buffer_arr ) /len( buffer_arr))
    #dispersion = int ( np.std( buffer_arr))
    #tmp = []
    #for i in range(pborders.begin, pborders.end) :
    #    if (abs(row[i] - comporand) < dispersion): 
    #        tmp.append(i)
    #pborders = Borders(tmp[0], tmp[-1])

    return Site(row[pborders.begin : pborders.end], pborders.begin ,pborders.end)

#
def tst_(arr, plato:Site):
    tstl = []
    mass =[]
    x = []
    mass.append(arr[plato.borders.begin])
    mass.append(arr[(plato.borders.begin+1)])
    x.append(plato.borders.begin)
    x.append(plato.borders.begin+1)
    #mass.append(arr[plato.borders.end])
    #x.append(plato.borders.end)

    for i in range(plato.borders.begin , (plato.borders.end)):
        mass.append(arr[i])
        x.append(i)
        tstl.append( finde_cof(x  , mass))

    save_grph(tstl, 0, len(tstl), name)


# тестируем идеии
def mama_idea(beg , end , arr):

    buf = []

    y_data_a = list(arr[beg: (beg + 3)])
    x_data_a = list(range(beg, beg + 3))

    y_data_b = list(arr[(beg+1):end])
    x_data_b = list(range((beg+1) , end))
 
    for i  in range((beg+3) , (end)):

        y_data_b.pop(0)
        x_data_b.pop(0)

        y_data_a.append(arr[i])
        x_data_a.append(i)
        angle_a = finde_cof(x_data_a, y_data_a)
        #print(angle_a)
        angle_a = atan(angle_a[0])* 57.296
        angle_b = abs(atan((finde_cof(x_data_b ,y_data_b)[0]) * 57.296))

        if (angle_b > 89): angle_b = 90

        if(angle_a > 0):
            angle_a = abs(angle_a) 
            if (angle_a > 89): angle_a = 90          
            buf.append(180 - angle_a - angle_b)
        else:
            angle_a = abs(angle_a) 
            if (angle_a > 89): angle_a = 90           
            buf.append(180 +angle_a - angle_b)
 
    return(buf)

def tst(arr):
    
    angles=[]

    #exel_data =[4078, 2409,2294,2277,2307,2245,2279,2231,2220,2108,2222,2149,2149,1922,1550,1019,591,205]
    exel_data= arr
    
    begin = 0
    end = len(exel_data)
    site_end = 4
    a_line =list( exel_data[begin:(begin + site_end)])
    b_line = list(exel_data[(begin + site_end - 1 ):len(exel_data)])

    x = list(range(begin ,end ))

    for i in range( (begin + site_end) ,(end-2) ):
        a_line.append(exel_data[i])
        b_line.pop(0)

        angle_a = atan( (foo(x[begin: (i + 1)], a_line))[0])
        angle_b = atan(( foo(x[i: end], b_line ) )[0]) 
        angles.append((abs(angle_b) - angle_a) * 900)
    x_angles = list(range((begin+site_end), (end - 2)))
    x_ = list(range(0, end))
    grph = plt.plot(x_ , arr)
    plt.plot(x_angles ,angles)
    plt.savefig(name)
    plt.close("all")
    #save_grph(angles, 0,len(angles), name)
    #fast_print(angles)

# поиск среднего отклонения на участке (относительно первой точки)
def id_1(arr , comporand):
    anser = 0   
    for i in arr:
        anser += abs(comporand  - i) 
    return anser / len(arr)

def id_1_main (arr):
    anser = []
    segment_size = 3 + 1
    for i in range(len(arr) - segment_size + 1):
        anser.append(id_1(list(arr[(i+1) : (i +segment_size)]) , arr[i]))
    return anser


def idea_4 (arr = []):

    start_size = 5
    anser =[]
    x = list(range(start_size))
    y = list(arr[0: start_size])
    for i in range( start_size ,len(arr) ):
        x.append(i)
        y.append(arr[i])
        anser.append( finde_cof(x, y)[0])

    return(anser)

def idea_4_invert(arr=[]):
    start_size = 4
    anser =[]
   
    x = list(range( (len(arr)-1), (len(arr) - start_size -1), -1))
    y = list(arr[-start_size:])
    y.reverse()
    for i in range( (len(arr) -start_size-1) , 0, -1):
        x.append(i)
        y.append(arr[i])
        anser.append( finde_cof(x, y)[0])

    return(anser)

# тело прграммы  нужно переписать на мейн

#path = 'D:/teast_dir/'

path =  'D:/work(DLNP)/Calibration_prj/teast_dir/'

if(0):
    for i in range(0,30):
   
        name = i
        name =  '{}_Event.txt'.format(name)
        file = open(path + name);
        mass = np.loadtxt(file);
        file.close()
        name= name +".png"

        #pixel_row = [int(sum(a)/10) for a in zip (*mass[120:131])]
        pixel_row = list(mass[125][0:256])
        pixel_row = [int(a) for a in pixel_row]
        plato:Site =  finde_bordres_of_plateu(pixel_row)
        begin = plato.borders.begin
        end =  plato.borders.end

        arr =  idea_4(plato.data)
        arr_2 = idea_4_invert(plato.data)
        arr_2.reverse()
        print_two(0, arr, 0,arr_2)



        #if(arr.index(min(arr)) == (len(arr)-1)):
        #    arr =  [(arr+2150) for arr in arr]
        #    print_two(0, plato.data, 4, arr)
        #    print(name)
else:
    stop = 'o'
    while(stop != 'y'):
        print("chose graph")
        name = input()
        name =  '{}_Event.txt'.format(name)
        file = open(path + name);
        mass = np.loadtxt(file);
        file.close()
        name= name +".png"

        #pixel_row = [int(sum(a)/10) for a in zip (*mass[120:131])]
        pixel_row = list(mass[125][0:256])
        pixel_row = [int(a) for a in pixel_row]
        plato:Site =  finde_bordres_of_plateu(pixel_row)
        begin = plato.borders.begin
        end =  plato.borders.end

        arr =  idea_4(plato.data)
        arr_2 = idea_4_invert(plato.data)
        arr_2.reverse()
        #print_two(0, arr, 0,arr_2)
        fast_print(pixel_row)

        print("whant to stop [y/n]?")
        stop = input()
    
    