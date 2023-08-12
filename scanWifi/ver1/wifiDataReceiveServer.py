import socket
import threading

UDP_IP_ADDRESS = "192.168.1.48"
UDP_PORT = 8000 

def sort_wifi_networks(networks, sort_by):
    if sort_by == 'ssid':
        sorted_networks = sorted(networks, key=lambda x: x['ssid'])
    elif sort_by == 'rssi':
        sorted_networks = sorted(networks, key=lambda x: x['rssi'], reverse=True)
    elif sort_by == 'ssid_rssi':
        sorted_networks = sorted(networks, key=lambda x: (x['ssid'], -x['rssi']))
    elif sort_by == 'rssi_ssid':
        sorted_networks = sorted(networks, key=lambda x: (-x['rssi'], x['ssid']))
    elif sort_by == 'channel':
        sorted_networks = sorted(networks, key=lambda x: x['channel'])
    else:
        raise ValueError("wrong input")

    return sorted_networks

def process_data(data):
    received_data = data.decode()
    networks = []
    for line in received_data.split('\n'):
        if line:
            ssid, rssi, channel, encryption = line.split('$')
            network = {
                'ssid': ssid,
                'rssi': int(rssi),
                'channel': int(channel),
                'encryption': encryption
            }
            networks.append(network)
    
    # sort_by=ssid/rssi/ssid_rssi/rssi_ssid/channel
    sorted_networks = sort_wifi_networks(networks, sort_by='ssid')

    for network in sorted_networks:
        print(network)
    print("\n")

def receive_data():
    serverSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    serverSock.bind((UDP_IP_ADDRESS, UDP_PORT))
    print("Listening for UDP packets on {}:{}".format(UDP_IP_ADDRESS, UDP_PORT))
    while True:
        data, addr = serverSock.recvfrom(1024)
        thread = threading.Thread(target=process_data, args=(data,))
        thread.start()

if __name__ == '__main__':
    receive_data()