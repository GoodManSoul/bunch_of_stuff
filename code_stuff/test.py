import requests
import os
import urllib.request
import time
from bs4 import BeautifulSoup

os.system('cls')

url = 'https://alpari.com/ru/invest/pamm/446542/#pamm-return'
response = requests.get(url)

soup = BeautifulSoup(response.text, "html.parser")

master_value = soup.find('span', class_ = '-dit-value__value')
fraction_value = soup.find('span', class_ = '-dit-value__fraction')

stuff = master_value.text[2;1]


print(stuff)
print(fraction_value)


time.sleep(1)

