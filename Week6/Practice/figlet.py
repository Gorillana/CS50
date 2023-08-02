# Applies figlet to user input

import sys
import random
from pyfiglet import Figlet

figlet = Figlet()

# Expect 0 or 2 command line args
# 0 for a random font
if len(sys.argv) == 1:
    RandFont = True

# 2 for specific font, require -f or --font
elif len(sys.argv) == 3 and (sys.argv[1] == "-f" or sys.argv[1] == "--font"):
    RandFont = False
else:
    print("Invalid Usage")
    sys.exit(1)

# the second arg is the name of the font, otherwise program exits
if RandFont == False:
      # searches for sys.argv[2] in figlet font list
    try:
        figlet.setFont(font = sys.argv[2])
      # if font typed isn't in Figlet font list, error
    except:
        print("Invalid Usage")
        sys.exit(1)

# Chooses random font by applying random function
else:
    font = random.choice(figlet.getFonts())

# Prompt user for a string of text
text = input("Input: ")

# To have output be typed in desired font
print(f"Output: ")
print(figlet.renderText(text))
