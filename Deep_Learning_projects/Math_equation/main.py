import os
import random
import timeit
from random import randint

SETS_QUANTITY = 60000

dataset = [None] * 1
input_data = [None] * 5

def Get_random_list(users_list, from_range, to_range):
  for index in range (len(users_list)):
    users_list[index] = random.randint(from_range, to_range)
  print(users_list)
  return users_list

def Get_dataset(users_dataset, sets_quantity, from_range, to_range):
  for i in range (sets_quantity):
    users_dataset.append(Get_random_list(input_data, from_range, to_range))
  if(len(users_dataset) == SETS_QUANTITY):
    return True
  else:
    return False

elapsed_time = timeit.timeit(Get_dataset(dataset, SETS_QUANTITY, 1, 5), number = 100/1)/100
print(elapsed_time)