from scapy import *
from scapy.all import *
import os 

PASSWORD = 'admin'

def filters(packet):
    if packet[IP].dst == "255.255.255.255":
            if packet[Raw]:
                data = str(packet[Raw])
                if data[4:6]== '01':
                    if data[8:10] == '99':
                        print(f'verson : 1 | type : message | message : {data[10:len(data)-1]}')
                        if data[10:len(data)-1] == PASSWORD:
                            print(f'{packet[IP].src} | client attack the password !')
                        else:
                            os.system(f'./a.out {data[10:len(data)-1]}')

def recon():
    sniff(
        filter='icmp',
        iface=['wlan0','eth0',conf.route.route('0.0.0.0')[0]],
        prn=filters)
    


recon()
