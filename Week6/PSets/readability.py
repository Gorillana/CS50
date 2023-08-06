# Calculate reading level of text

from cs50 import get_string

# receive text from user
text = get_string("Text: ")

# dec/init variables
letters = 0
words = 1
sentences = 0

# Determine/Calc sentences, words, letter count for index
for i in text:
  if i.isalpha():
      letters += 1
  elif i == " ":
      words += 1
  elif i == "." or i == "!" or i == "?":
      sentences += 1

# Coleman-Liau index used to calc grade
index = round(0.0588 * (letters/words * 100) - 0.296 * (sentences / words * 100) - 15.8)

# Determine index grade level and print result
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
