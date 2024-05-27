def RC4(key: str, text: str) -> str:
    S = list(range(256))  # Initialize state array with values 0 through 255
    j = 0  # Initialize j
    out = []  # Output list

    # Key-scheduling algorithm (KSA)
    for i in range(256):
        j = (j + S[i] + ord(key[i % len(key)])) % 256
        S[i], S[j] = S[j], S[i]  # Swap values

    # Pseudo-random generation algorithm (PRGA)
    i = j = 0
    for char in text:
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i]  # Swap values
        t = (S[i] + S[j]) % 256
        K = S[t]
        out.append(
            chr(ord(char) ^ K)
        )  # XOR and transform to char

    return ''.join(out)

def to_hex(text: str) -> str:
    out: str = ""

    for c in text:
        out += format(ord(c), '02X')

    return out