import subprocess
import os

from TDBusCommander import TDBusCommander

class TFileOpener(object):

    def __init__(self):
        self.__accordance = dict()

        # сопоставление типов данных с программой для открытия
        self.__accordance['.txt'] = 'gedit'
        self.__accordance['.c'] = 'gedit'
        self.__accordance['.cpp'] = 'code'
        self.__accordance['.mp3'] = 'audacity'
        self.__accordance['.wav'] = 'audacity'
        self.__accordance['.mp4'] = 'vlc'
        self.__accordance['.avi'] = 'vlc'
        self.__accordance['.jpg'] = 'kolourpaint'
        self.__accordance['.png'] = 'kolourpaint'
        self.__accordance['.odt'] = 'loffice'
        self.__accordance['.docx'] = 'loffice'

        self.__dbus_commander = TDBusCommander()
        pass
    
    @staticmethod
    def __get_left_dot_position(filename):
        dot_position = -1
        for i in range(len(filename)-1, 0, -1):
            if filename[i] == '.':
                dot_position = i
                break
        
        return dot_position
        
    @staticmethod
    def __get_file_extension(filename):            
        dot_position = TFileOpener.__get_left_dot_position(filename)
        return filename[dot_position:]

    @staticmethod
    def __check_if_file_exists(filename):
        if not os.path.isfile(filename):
            print('Вы ввели имя несуществующего файла!')
            print('Пожалуйста, будте аккуратнее!')
            return False
        return True

    def open_file(self, filename):
        if not TFileOpener.__check_if_file_exists(filename):
            return

        extension = TFileOpener.__get_file_extension(filename)
        programm = self.__accordance.get(extension, 'ghex')

        print('filename:\t', filename)
        print('extension:\t', extension)

        print('File with extension {} will be opened with {}'.format(
            extension,
            programm    
        ))

        result = subprocess.run([programm], capture_output=True, text=True, check=True)
        self.__dbus_commander.sendMessage(programm, filename)
