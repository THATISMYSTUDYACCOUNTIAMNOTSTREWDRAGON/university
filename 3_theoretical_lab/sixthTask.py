class Node:
    def __init__(self, symbol, frequency, left=None, right=None) -> None:
        self.symbol = symbol
        self.frequency = frequency
        self.left = left
        self.right = right
        self.code = ""

class Haff:
    def create_nodes(self, frequency: dict) -> list[Node]:
        nodes = []
        for symbol in frequency:
            nodes.append(Node(symbol, frequency[symbol]))
        return nodes

    def calculate_frequency(self, message: str) -> dict:
        frequency = {}
        for i in list(set(message)):
            frequency[i] = message.count(i)
        return frequency

    def calculate_code(self, node: Node, code="", codes={}) -> str:

        code = code + str(node.code)

        if node.left:
            self.calculate_code(node.left, code, codes)
        if node.right:
            self.calculate_code(node.right, code, codes)

        if not node.left and not node.right:
            codes[node.symbol] = code

        return codes

    def replace_encoded(self, message: str, code_map: dict) -> dict:
        for i in code_map:
            message = message.replace(i, code_map[i])
        return message

    def decode(self, message: str, huffman_tree: Node):
        tree_head = huffman_tree
        decoded = ""

        for i in message:
            if i == '1':
                huffman_tree = huffman_tree.right   
            if i == '0':
                huffman_tree = huffman_tree.left
            try:
                if huffman_tree.left.symbol == None and huffman_tree.right.symbol == None:
                    pass
            except AttributeError:
                decoded += huffman_tree.symbol
                huffman_tree = tree_head
            
        return decoded

    def encode(self, message: str) -> str:
        nodes = self.create_nodes(self.calculate_frequency(message))

        while len(nodes) > 1:
            nodes = sorted(nodes, key=lambda x: x.frequency)

            right_node: Node = nodes[0]
            left_node: Node = nodes[1]

            right_node.code = 1
            left_node.code = 0

            new_node = Node(left_node.symbol + right_node.symbol, left_node.frequency + right_node.frequency, left_node, right_node)

            nodes.remove(left_node)
            nodes.remove(right_node)
            nodes.append(new_node)
        
        self.haffman_tree = nodes[0]

        return self.replace_encoded(message, self.calculate_code(self.haffman_tree))

    def get_haffman_tree(self) -> Node:
        return self.haffman_tree

haff = Haff()

with open("sixthMessage.txt", "r", encoding="utf-8") as file:
    variable = file.read()

print(haff.encode(variable))
print(haff.decode(haff.encode(variable), haff.get_haffman_tree()))