#-------------------------------------------------------------------------------
# Name:        module2
# Purpose:
#
# Author:      Choi kwangjin
#
# Created:     02-04-2020
# Copyright:   (c) Choi kwangjin 2020
# Licence:     <your licence>
#-------------------------------------------------------------------------------

def main():
    print("Hello Python! 1")
    pass

if __name__ == '__main__':
    main()

print("Hello Python! 2")
import requests
api_key = "Nk7YR07TVGBurP3UKxPOIscV0YTCA/Fe3S+MtoTh/LMjXQXH8GwVTqKuSKZYDPN1ILrYHKrRjWM7xoNXfImumg=="
api_key_decode = requests.utils.unquote(api_key)
parameters = {"ServiceKey":api_key_decode, "numOfROws":10, "pageNo":1}
req = requests.get(url, params = parameters)
