import cs50
import math


def main():
    # prompt user input
    while True:
        # continue to prompt input from user if not given apropriate value
        print("Number: ", end="")
        card = cs50.get_float()
        # break from continuous prompt, when given appropriate input
        if card > 0:
            break
    # validate credit card
    # checksum = used to validate card by the sum of calculations
    # count = count the length of the card number for identifying which company is belongs to
    #       -> starts with 1 for the sake of identifying whether given placeholder is odd or even
    #        ; will later decrease for the appropriate length of card number
    # temp = temporary storage for card number; will be trunketing off the lowest place while calculating checksum
    check_sum = 0
    count = 1
    temp = card
    # iterate as long as card number exists (able to parse and trunket values for checksum calculation)
    while temp >= 1:
        # if even number placeholder, multiply twice
        if (count % 2) == 0:
            num = (temp % 10) * 2
            # if the multiplied value is larger than 10, parse it into individual numbers and add them together
            if num >= 10:
                temp1 = num // 10
                temp2 = num % 10
                num = temp1 + temp2
        # if odd number placeholder, just leave the value
        else:
            num = temp % 10
        # add parsed number (value at given placeholder) to the checksum
        check_sum += num
        # increment count
        count += 1
        # truncate the already calculated placeholder; preparation for next placeholder
        temp = temp // 10
    # decrease count by 1 to achieve appropriate length of card number
    count -= 1
    # if check sum's lowest placeholder is not 0, print invalid to identify it is an invalid card number
    if (check_sum % 10) != 0:
        print("INVALID")
        return 0
    # else, valid card number so proceed to print which company it is
    else:
        # if length is 13 and it starts with 4, print VISA
        if count == 13:
            cut = card // math.pow(10, 12)
            if (cut % 10) == 4:
                print("VISA")
        # if length is 15 and it starts with 34 or 37, print AMEX
        elif count == 15:
            cut = card // math.pow(10, 13)
            if cut == 34 or cut == 37:
                print("AMEX")
        # if length is 16,
        elif count == 16:
            cut = card // math.pow(10, 15)
            # and starts with 4, print VISA
            if (cut % 10) == 4:
                print("VISA")
            # or either starts with 51, 52, 53, 54, 55, print MASTERCARD
            elif (cut % 10 == 5):
                cut = card // math.pow(10, 14)
                if cut == 51 or cut == 52 or cut == 53 or cut == 54 or cut == 55:
                    print("MASTERCARD")
        # other cases, though checksum is valid, the number does not belong to valid company so print INVALID
        else:
            print("INVALID")
    return 0


# call main function
if __name__ == "__main__":
    main()
