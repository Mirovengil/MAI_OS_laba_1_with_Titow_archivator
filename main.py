from TFileOpener import TFileOpener
from TInputParser import TInputParser
from TDBusCommander import TDBusCommander


if __name__ == "__main__":
    file_opener = TFileOpener()
    input_parser = TInputParser()


    while True:
        print(end='\n')
        input_parser.get_input()
        command = input_parser.get_input_filename()
        print(end='\n')

        if command == TInputParser.EXIT_FLAG:
            print('Благодарим за работу с нашей программой!')
            exit(0)
        
        filename = command
        file_opener.open_file(filename)
