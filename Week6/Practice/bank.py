# calculates payout depending on greeting

# Prompt user for greeting
greeting = input("Greeting: ")

bank_greeting = greeting.lower().strip()

# If greeting starts with hello output $0
if 'hello' in bank_greeting:
  print("$0")

# If greeting starts with H, output $20
elif 'h' == greeting[0]:
  print("$20")

# Otherwise, return $100
else:
  printf("$100")
