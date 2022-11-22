
def series_sum(start1, start2, end1, end2, step):
    mul1 = start1
    mul2 = start2
    num = []
    for idx in range(int((end1 - start1) / step) + 1):
        print("num:{} * {}".format(mul1, mul2))
        num.append(mul1 * mul2)
        mul1 += step
        mul2 += step

    print(num) 
    print("sum:", sum(num))

if __name__ == "__main__":
    series_sum(17, 21, 101, 105, 4)

    
