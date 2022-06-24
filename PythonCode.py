# Bryan Pirrone
# CS - 210
# Project 3
# 6/17/2022

import re
import string

FILENAME = "items"


# FIXXXX MEEEEEE

def readFile():
    ticket = open("items.txt")
    products = ticket.read().split()
    unique_Product = sorted(set(products))

    for word in unique_Product:
        print("\n")
        print(products.count(word), " : ", word)
        print("\n")

    ticket.close()

    
def getInventory(v):
    ticket = open("items.txt")
    products = ticket.read().split()
    unique_Product = sorted(set(products))
    ticket.close()

    tot = 0
    tot_inventory = 0
    tot_inventory_count = 0

    for word in unique_Product:
        tot_inventory_count += 1

    for word in unique_Product:
        temp_String = word
        tot_inventory += 1
        if (temp_String == v):
            tot = products.count(word)
            tot_inventory -= 1
        if (temp_String != v and tot_inventory == tot_inventory_count):
            return -1

    return tot

def output():
    ticket = open("items.txt")
    data = open("frequency.dat", "w")
    products = ticket.read().split()
    unique_Product = sorted(set(products))

    for word in unique_Product:
        data.write(word)
        data.write(" ")
        data.write(str(products.count(word)))
        data.write("\n")

    data.close()

    histo_data = open("frequency.dat", "r")
    product_data = histo_data.readlines()

    temp_freq = histo_data
    temp_product = ""

    for line in product_data:
        temp_int = 0
        temp_string = line.split()
        for word in temp_string:
            temp_int += 1
            if (temp_int == 1):
                temp_product = word
                print(temp_product, end = " ")
            if (temp_int == 2):
                temp_freq = int(word)

        for i in range(temp_freq):
            print("*", end = "")
        print("\n")
