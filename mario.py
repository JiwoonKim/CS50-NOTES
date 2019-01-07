import cs50


def main():
    # prompt user for appropriate input
    while True:
        print("Height: ", end="")
        num = cs50.get_int()
        if num >= 0 and num <= 23:
            break
    # create the pyramid
    for i in range(num):
        k = i + 1
        # create left side
        print(" " * (num - k), end="")
        print("#" * k, end="")
        # create space
        print("  ", end="")
        # create right side
        print("#" * k, end="")
        # new line
        print()


# start main
if __name__ == "__main__":
    main()
