# Generate **This sheet** automaticly.
# (The sheet of README.md)

import os

def gen_sheet() -> str:
    # Traverse files and read its introduction.
    files = os.listdir()
    introductions = []
    for file in files:
        if not file.endswith(".py"): continue
        text = open(file, "r", encoding="utf-8").read()
        introduction = text.split("\n")[1][2:]
        introductions.append(introduction)
    file_max_len, intro_max_len = 0, 0
    file_max_len = max(len(f) for f in files) if files else 10
    intro_max_len = max(len(i) for i in introductions) if introductions else 20
    res = ""
    res += f"|{"File".center(file_max_len)}|{"Usage".center(intro_max_len)}|\n"
    res += f"|{"-" * file_max_len}|{"-" * intro_max_len}|\n"
    for f in files:
        for i in introductions:
            res += "|" + f + " " * (file_max_len - len(f)) + "|" + i + " " * (intro_max_len - len(i))
    return res
def write_to_readme() -> None:
    sheet = gen_sheet() 
    text = """
# MISC
Here's some **miscellaneous** things from my **secret & awesome ideas**\\.\\.\\.
## Nevigation
""" + sheet + "\n"
    with open("README.md", "w", encoding="utf-8") as f:
        f.write(text)

if __name__ == '__main__':
    write_to_readme()

