import sys
import crypt


def main():
    # get hashed password
    while True:
        if len(sys.argv) != 2:
            print("Usage: crack.py hash")
        else:
            hashed = sys.argv[1]
            break

    # iterate over all guesses until find match with hased password
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxy"
    # iterate over one character
    for i in alphabet:
        if check(hashed, i) == True:
            print(i)
            return 0
    # iterate over two characters
    for a in alphabet:
        for b in alphabet:
            guess = a + b
            if check(hashed, guess) == True:
                print(guess)
                return 0
    # iterate over three characters
    for c in alphabet:
        for d in alphabet:
            for e in alphabet:
                guess = c + d + e
                if check(hashed, guess) == True:
                    print(guess)
                    return 0
    # iterate over four characters
    for f in alphabet:
        for g in alphabet:
            for h in alphabet:
                for j in alphabet:
                    guess = f + g + h + j
                    if check(hashed, guess) == True:
                        print(guess)
                        return 0
    # iterate over five characters
    for k in alphabet:
        for m in alphabet:
            for n in alphabet:
                for p in alphabet:
                    for q in alphabet:
                        guess = k + m + n + p + q
                        if check(hashed, guess) == True:
                            print(guess)
                            return 0


def check(hashed, guess):
    if hashed == crypt.crypt(guess, "50"):
        return True
    return False


if __name__ == "__main__":
    main()
