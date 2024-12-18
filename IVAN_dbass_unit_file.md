[Unit]
	Description=Юнит-файл для подъёма моего процесса в протоколе DBus...
	After=dbus.service 
[Service]
	Type=dbus
	BusName=org.example.laba_6_OS
	ExecStart=python3 /home/ivan/MAI/OS/laba_6/MAI_OS_labs_with_Titow/main.py
	Restart=always
	User=ivan
[Install]
	WantedBy=multi-user.target
