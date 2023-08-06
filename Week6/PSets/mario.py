# mario pyramid

# import get_int from cs50 lib

from cs50 import get_int

# Prompt user for int between 1,8
while True:
  g = get_int("Height: ")

  # should reprompt until input is 1-8
  if g > 0 and g < 9:
      break

# Nested loops to create a grid of rows/cols
# range function increments up until input, g
for i in range(0, g, 1):
  for j in range(0, g, 1):
      # print correct amt of spaces before #
      # by making this condition, it allowed to
      # print # for i+j >= g-1
      if (i + j < g - 1):
          # include end to remove extra space
          print(" ", end="")
      else:
          print("#", end="")
      # include print to move to next line
      print()
