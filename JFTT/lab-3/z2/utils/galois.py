
class Galois:
    def __init__(this, P: int, value: int):
        this.P = P
        this.value = this._normalize(value)

    def _normalize(this, a: int) -> int:
        a %= this.P

        if a < 0:
            a += this.P
        
        return a
    
    def _inverse(this, a: int) -> int:
        b: int = this.P

        x: int = 1
        y: int = 0

        x1: int = 0
        y1: int = 1

        while b != 0:
            q: int = a // b
            
            x, x1 = x1, x - q * x1
            y, y1 = y1, y - q * y1
            a, b  = b,  a - q * b

        return this._normalize(x) 

    def add(this, other: 'Galois') -> 'Galois':
        return Galois(this.P, this.value + other.value)
    
    def sub(this, other: 'Galois') -> 'Galois':
        return Galois(this.P, this.value - other.value)
    
    def mul(this, other: 'Galois') -> 'Galois':
        return Galois(this.P, this.value * other.value)
    
    def div(this, other: 'Galois') -> 'Galois':
        return Galois(this.P, this.value * this._inverse(other.value))
    
    def pow(this, other: 'Galois') -> 'Galois':
        return Galois(this.P, pow(this.value, other.value, this.P))
    
    