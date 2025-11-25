import socket
import threading
import re

def evaluate_hex_expression(expression):
    """
    Вычисляет арифметическое выражение с шестнадцатеричными числами.
    Поддерживает + и -.
    """
    # Заменяем шестнадцатеричные числа на их десятичные эквиваленты
    def hex_to_dec(match):
        return str(int(match.group(0), 16))
    
    # Добавляем пробелы для корректного разделения
    expr = re.sub(r'([+-])', r' \1 ', expression)
    expr = expr.strip()
    
    # Преобразуем шестнадцатеричные числа
    expr = re.sub(r'[0-9A-Fa-f]+', hex_to_dec, expr)
    
    try:
        result = eval(expr)
        return hex(result).upper()[2:]  # Возвращаем в шестнадцатеричном виде без 0x
    except:
        return "ERROR"

def handle_client(client_socket, address):
    print(f"[+] Соединение от {address}")
    
    while True:
        try:
            data = client_socket.recv(1024).decode('utf-8').strip()
            if not data:
                break
            
            print(f"[*] Получено: {data}")
            result = evaluate_hex_expression(data)
            client_socket.send(result.encode('utf-8'))
            
        except Exception as e:
            print(f"[-] Ошибка с клиентом {address}: {e}")
            break
    
    client_socket.close()
    print(f"[-] Соединение с {address} закрыто")

def start_server(host='127.0.0.1', port=65432):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    try:
        server.bind((host, port))
        server.listen(5)
        print(f"[*] Сервер запущен на {host}:{port}")
        
        while True:
            client_sock, addr = server.accept()
            client_handler = threading.Thread(
                target=handle_client,
                args=(client_sock, addr)
            )
            client_handler.start()
            
    except Exception as e:
        print(f"[-] Ошибка сервера: {e}")
    finally:
        server.close()

if __name__ == "__main__":
    start_server()
