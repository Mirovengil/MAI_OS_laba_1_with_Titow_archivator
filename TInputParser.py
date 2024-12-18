

class TInputParser(object):
    EXIT_FLAG = 0

    def __init__(self):
        self.__input = ''
        pass
    
    def get_input(self):
        print('Для выхода из программы введите \'exit\'')
        print('Введите имя файла, который необходимо открыть', end=': ')
        self.__input = input()
    
    def get_input_filename(self):
        if self.__input != 'exit':
            return self.__input
        return TInputParser.EXIT_FLAG