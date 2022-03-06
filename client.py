from scapy import * 
from scapy.all import *
import scapy,sys

def ethernet():
    return Ether(dst='ff:ff:ff:ff:ff:ff',
                 type=0x0800)

def Internet():
    return IP(dst='255.255.255.255',
        version= 4,
        ihl= None,
        tos= 0x0,
        id=1,
        frag= 0,
        ttl= 10,
        proto= 0x01,
        chksum= None,)

def internetmassage(version,types,message):
    text = b''
    if version == 1:
        text += b'\x01'
    if types == 0x99:
        text += b'\x99'
    pack = ICMP()/text/message
    return pack



sendp(ethernet()/Internet()/internetmassage(1,0x99,sys.argv[1]))
