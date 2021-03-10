while True:
    n = int(input("Height: "))
    if n >= 1 and n <= 8:
        break
for i in range(n):
    print(" " * (n- i - 1), end = "")
    print("#" * (i + 1))
    
#two things not working
#Run your program as python mario.py and wait for a prompt for input. Type in foo and press enter. Your program should reject this input as invalid, as by re-prompting the user to type in another number.
#Run your program as python mario.py and wait for a prompt for input. Do not type anything, and press enter. Your program should reject this input as invalid, as by re-prompting the user to type in another number.