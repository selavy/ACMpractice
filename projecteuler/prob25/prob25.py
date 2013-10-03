import math

def get_length(i):
    return int(math.log10(i))+1;

def main():
    prev1 = 0
    prev2 = 1;
    tmp = 0
    for i in range(1, 10000):
        if get_length(prev1 + prev2) == 1000:
            print i
            print prev1 + prev2
            break;
        else:
            tmp = prev1
            prev1 = prev1 + prev2
            prev2 = tmp
        #print i+1, ": ", prev1 + prev2
        
if __name__ == "__main__":
    main()
