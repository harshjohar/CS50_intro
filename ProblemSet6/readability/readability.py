from cs50 import get_string
import math
#inspired from try0read

#Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
#L = number of letters per 100 words
#S = number of sentences per 100 words
while True:
    p = get_string("Text: ")

    l = 0 #letters
    s = 0 #sentences
    w = 1 #words
    h = 0 #dummy

    if(str):
        for i in range(len(p)):
            if (p[i].isalpha()):
                l += 1
            elif (p[i].isnumeric()):
                l += 1
            elif (p[i] == ' ' and p[i + 1] != ' '):
                w += 1
            elif (p[i] == '.' or p[i] == '?' or p[i] == '!'):
                s += 1
            else:
                h += 1

        L = float ((l / w) * 100)
        S = float ((s / w) * 100)

#readability
        R = round((float)(0.0588 * L - 0.296 * S - 15.8))

        if (R >= 16):
            print('Grade 16+')
        elif (R < 1):
            print('Before Grade 1')
        else:
            print('Grade ', R)

        break