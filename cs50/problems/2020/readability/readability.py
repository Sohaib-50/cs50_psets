from cs50 import get_string

text = get_string("Text: ")

# count number of letters, words and sentences in text
letters, words, sentences = 0, 0, 0
for char in text:
    if char.isalpha():
        letters += 1
    elif char == " ":
        words += 1
    elif char in {"!", "?", "."}:
        sentences += 1
words += 1  # this is needed because after last word, there won't be a space

coleman_liau_index = round(0.0588 * ((100 * letters) / words) - 0.296 * ((100 * sentences) / words) -
                           15.8)  # round() rounds to nearest int if no 2nd parameter

if coleman_liau_index > 16:
    print("Grade: 16+")
elif coleman_liau_index < 1:
    print("Before Grade 1")
else:
    print(f"Grade: {coleman_liau_index}")
