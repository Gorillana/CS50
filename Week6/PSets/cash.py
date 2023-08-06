# use get_float to ask for input
from cs50 import get_float

#declare var to start count of coins
coins = 0

#ensure non-neg value
while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

# change to int from float
change = round(int(change * 100))

# Coins calculations
while change > 0:
  # Calc Quarters
  if change >= 25:
      change -= 25
      coins += 1
  # Calc Dimes
  elif change >= 10:
      change -= 10
      coins += 1
  # Calc Nickels
  elif change >= 5:
      change -= 5
      coins += 1
  # Calc Pennies
  elife change >= 1:
      change -= 1
      coins += 1

print(f"Coins: {coins}")
