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

    def open_file(self, filename):
        extension = TFileOpener.__get_file_extension(filename)
        
        print('filename:\t', filename)
        print('extension:\t', extension)

        print('File with extension {} will be opened with {}'.format(
            extension,
            self.__accordance.get(extension, 'ghex')
        ))