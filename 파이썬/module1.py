#-------------------------------------------------------------------------------
# Name:        module1
# Purpose:
#
# Author:      Choi kwangjin
#
# Created:     21-05-2022
# Copyright:   (c) Choi kwangjin 2022
# Licence:     <your licence>
#-------------------------------------------------------------------------------

def main():
    express = input().split('-')
    result = 0
    values = express[0].split('+')
    for value in values :
        result += int(value)
    result *= 2
    for partExpress in express :
        values = partExpress.split('+')
        for value in values :
            result -= int(value)
    print(result)
    pass

if __name__ == '__main__':
    main()
