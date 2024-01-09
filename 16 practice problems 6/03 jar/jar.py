class Jar:
    def __init__(self, capacity=12):
        self.capacity = capacity
        self.size = 0

    def __str__(self):
        return "🍪" * self.size

    def deposit(self, n):
        if self.size + n > self.capacity:
            raise ValueError("Deposit error")
        self.size = self.size + n

    def withdraw(self, n):
        if n > self.size:
            raise ValueError("Withdraw error")
        self.size = self.size - n

    @property
    def capacity(self):
        return self.capacity

    @property
    def size(self):
        return self.size

def main():
    jar = Jar()
    print(str(jar.capacity))
    print(str(jar))
    jar.deposit(2)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))

main()
