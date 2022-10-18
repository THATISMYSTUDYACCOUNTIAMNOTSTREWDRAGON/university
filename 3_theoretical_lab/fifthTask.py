from fourthTask import Caesar

class CaesarOffset(Caesar):
    const = 14

    def __init__(self) -> None:
        super().__init__()

    def encode_offset(self, message):
        return self.encode("".join([chr(ord(i) + self.const) for i in message]))

    def decode_offset(self, message):
        return "".join([chr(ord(i) - self.const) for i in self.decode(message) ])

with open("fourthMessage.txt", "r", encoding="utf-8") as file:
    message = file.read()

caesar = CaesarOffset()
message = caesar.encode_offset(message)
print(message)
message = caesar.decode_offset(message)
print(message)