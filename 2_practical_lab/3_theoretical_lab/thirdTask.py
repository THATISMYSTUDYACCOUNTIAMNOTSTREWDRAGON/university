with open("thirdMessage.txt", "r", encoding="utf-8") as file:
    text = file.readline()
    print(" ".join([str(hex(ord(i))) for i in text.strip()]))