#Prova salvare e stampare un indirizzo ip
#Programma valido solo con indirizzi di classe c 
#salvare gli indirizzi ip in una lista ordinarla cancellare e aggiungere da pannello di controllo
import os
import subprocess

def ping_ip(ip_address):
    # Componi il comando ping
    if subprocess.call(['ping', '-c', '1', ip_address]) == 0:
        return True
    else:
        return False

# Funzione per salvare gli indirizzi IP su un file
def save_ip_addresses(ip_addresses):
    with open('ip_addresses.txt', 'w') as file:
        for ip in ip_addresses:
            file.write(ip + '\n')
    print("Indirizzi IP salvati su file.")

# Funzione per caricare gli indirizzi IP da un file
def load_ip_addresses():
    ip_addresses = []
    try:
        with open('ip_addresses.txt', 'r') as file:
            for line in file:
                ip = line.strip()
                ip_addresses.append(ip)
    except FileNotFoundError:
        pass
    return ip_addresses

# Inizializza la lista degli indirizzi IP
ip_addresses = load_ip_addresses()

while True:
    print("1. Aggiungi indirizzo IP")
    print("2. Rimuovi indirizzo IP")
    print("3. Effettua il ping su tutti gli indirizzi IP")
    print("4. Salva gli indirizzi IP su file")
    print("5. Esci")

    choice = input("Seleziona un'opzione: ")

    if choice == '1':
        ip = input("Inserisci l'indirizzo IP da aggiungere: ")
        ip_addresses.append(ip)
        print(f"L'indirizzo IP {ip} è stato aggiunto.")

    elif choice == '2':
        ip = input("Inserisci l'indirizzo IP da rimuovere: ")
        if ip in ip_addresses:
            ip_addresses.remove(ip)
            print(f"L'indirizzo IP {ip} è stato rimosso.")
        else:
            print(f"L'indirizzo IP {ip} non è presente nella lista.")

    elif choice == '3':
        print("Avvio il ping su tutti gli indirizzi IP:")
        for ip in ip_addresses:
            if ping_ip(ip):
                print(f"Il ping verso {ip} è riuscito.")
            else:
                print(f"Il ping verso {ip} ha fallito.")

    elif choice == '4':
        save_ip_addresses(ip_addresses)

    elif choice == '5':
        break

    else:
        print("Opzione non valida. Riprova.")
    
