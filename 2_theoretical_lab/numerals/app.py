

class Convertor:
	def __init__(self):
		pass

	@staticmethod
	def convert_base(number, to_base=10, from_base=10):
		if isinstance(number, str):
			n = int(number, from_base)
		else:
			n = int(number)

		alphabet = "0123456789ABCDEFGHIJKLMNOP"

		if n < to_base:
			return alphabet[n]

		return Convertor.convert_base(n / to_base, to_base) + alphabet[n % to_base]


class Task:
	@staticmethod
	def do_first_task():
		with open("firstTaskFile.txt", "r") as file:
			text = file.readline()
			numbers_bin = list(map(lambda x: Convertor.convert_base(x, 2), text.split()))
			numbers_hex = list(map(lambda x: Convertor.convert_base(x, 16), text.split()))
			print(numbers_bin)
			print(numbers_hex)


Task.do_first_task()


