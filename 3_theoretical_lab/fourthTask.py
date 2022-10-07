class Caesar:
    def encode(self, message):
        return " ".join([str(ord(i)) for i in message])

    def decode(self, message):
        return "".join([chr(int(i)) for i in message.split()])

with open("fourthMessage.txt", "r", encoding="utf-8") as file:
    message = file.read()

caesar = Caesar()
message = caesar.encode(message)
print(message)
message = caesar.decode(message)
print(message)
