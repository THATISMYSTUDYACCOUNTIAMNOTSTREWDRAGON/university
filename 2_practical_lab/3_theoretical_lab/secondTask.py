with open("secondMessage.txt", "r", encoding="utf-8") as file:
    text = file.readline()
    symbols = text.split()
    print("".join(chr(int(i, 0)) for i in symbols))