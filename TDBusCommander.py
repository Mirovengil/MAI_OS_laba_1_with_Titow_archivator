from pydbus import SessionBus

class TDBusCommander(object):
    def __init__(self):

        # имена прокси-объектов, соответствующих именам файлов
        self.__accordance = dict()
        self.__accordance['gedit'] = ['gedit']
        self.__accordance['code'] = ['gedit']
        self.__accordance['audacity'] = ['code']
        self.__accordance['vlc'] = ['audacity']
        self.__accordance['kolourpaint'] = ['audacity']
        self.__accordance['loffice'] = ['vlc']
        self.__accordance['ghex'] = ['vlc']
    
    def sendMessage(self, programm, filename):
        bus = SessionBus()
        runner = bus.get(
            'org.gnome.gedit',
            '/org/gnome/gedit'
        )
        runner.Activate(filename)

        # runner