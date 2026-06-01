# Generate **This sheet** automaticly.
# (The sheet of README.md)

import os

def gen_sheet() -> str:
    files = os.listdir(os.path.dirname(__file__))
    py_files = []
    introductions = []

    for file in files:
        if not file.endswith(".py"):
            continue
        
        try:
            text = open(os.path.dirname(__file__) + "/" + file, "r", encoding="utf-8").read()
            lines = text.splitlines()
            if len(lines) >= 2:
                intro = lines[0].lstrip("# ").strip()
            else:
                intro = "No description"
            
            py_files.append(file)
            introductions.append(intro)
        except:
            continue

    file_max_len = max(len(f) for f in py_files) if py_files else 10
    intro_max_len = max(len(i) for i in introductions) if introductions else 20

    res = ""
    res += f"| {'File'.ljust(file_max_len)} | {'Usage'.ljust(intro_max_len)} |\n"
    res += f"|{'-'*(file_max_len+2)}|{'-'*(intro_max_len+2)}|\n"

    for f, i in zip(py_files, introductions):
        res += f"| {f.ljust(file_max_len)} | {i.ljust(intro_max_len)} |\n"

    return res


def write_to_readme() -> None:
    sheet = gen_sheet()
    text = """
# MISC
Here's some **miscellaneous** things from my **secret & awesome ideas**...

## Navigation

""" + sheet

    with open(f"{os.path.dirname(__file__)}/README.md", "w", encoding="utf-8") as f:
        f.write(text)


if __name__ == '__main__':
    write_to_readme()
