# Testing for handling of missing bits and correct resulting key (using Python since ESP32 not available)

keyLength = 5
aliceBasisSelection = [0, 1, 1, 0, 0, 0, 1, 0, 1, 0]
bobBasisSelection = [0, 1, 0, 1, 1, 0, 1, 0, 0, 0]
aliceTimestamps = [0, 5, 10, 15, 20, 25, 30, 35, 40, 45]
bobTimestamps = [0, 6, 15, 20, 23, 30, 40, 45, 50, 60]

i = 0
# iterate through all instances when Alice sends a bit
while i < len(aliceTimestamps):
    j = 0
    # iterate through all instances when Bob recieves a bit
    while j < len(bobTimestamps):
        # if there is more than 1 second difference between when Alice sends and Bob recieves the bit, the bit is considered lost
        if abs(aliceTimestamps[i] - bobTimestamps[j]) <= 1:
            if aliceBasisSelection[i] == bobBasisSelection[j]:
                print("Bit", i, "is valid and can be used for the key.")
            else:
                print("Bit", i, "has different basis selections and will be discarded.")
        j += 1
    i += 1


    