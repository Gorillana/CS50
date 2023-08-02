# Cookie Jar storage

class Jar:
  def __init__(self, capacity=12):
      # Initialize a cookie jar
      self._capacity = capacity
      self._size = 0
      # If capacity is non-neg raise ValueError
      if capacity < 0:
          raise ValueError('Insufficient space')

def __str__(self):
    # Return a string with 🍪, n number of cookies
    return self._size * '🍪'

def deposit(self, n):
    # If adding beyond capacity raise ValueError
    if n > self._capacity:
        raise ValueError('Exceeded capacity')
    if self.size + n > self.capacity:
        raise ValueError('Exceeded capacity')

    # Add n cookies to the jar
    self._size += n

def withdraw(self, n):
    # If removing more than available cookies, raise ValueError
    if self._size < n:
        raise ValueError('Not enough cookies!')

    # Remove cookies from the jar
    self._size -= n

@property
def capacity(self):
    # Return cookie jar's capacity
    return self._capacity

@property
def size(self):
    # Return the number of cookies actually in the jar
    return self._size

jar = Jar()
jar.deposit(12)
jar.withdraw(1)
print(jar)
