from sys import argv, exit
import csv
from time import sleep


# checking for correct usage of program
if len(argv) != 3:
    print("invalid arguments.")
    exit(1)

with open(argv[1], "r") as database_file:  # open the csv file
    database_reader = csv.DictReader(database_file)  # instantiate csv dict reader object
    STRs = database_reader.fieldnames[1:]  # get list of STRs present in database file

    with open(argv[2], "r") as dna_sequence_file:
        dna_sequence = dna_sequence_file.read()  # read the sequence as string

    #  calculating longest runs of each STR
    STR_record = {}  # dictionary to keep record of count of longest run of consecutive repeats of the STR in the DNA sequence
    for STR in STRs:
        STR_record[STR] = 0
        STR_len = len(STR)
        index = dna_sequence.find(STR, 0)  # finding index of start of first repeat of current STR

        while index != -1:  # while not gone past the index of the last occurance of the STR (st.find() returns -1 when not found)

            #  counting length of current run of repeats of the STR
            count = 0
            while dna_sequence[index: index + STR_len] == STR:
                count += 1
                index += STR_len  # jump length-of-STR indexes ahead in the sequence

            #  updating count in dict if current value in dict is less than new calculated count
            if STR_record[STR] < count:
                STR_record[STR] = count

            index = dna_sequence.find(STR, index)  # finding index of start of next repeat of current STR

    # Finding out if STRs match any record in database
    match_found = False
    for row in database_reader:  # for every record
        for STR in STR_record:
            match_found = True
            if int(row[STR]) != STR_record[STR]:
                match_found = False
                break

        if match_found:
            print(row['name'])
            break
    else:
        print("No match")
