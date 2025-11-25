import tkinter as tk
from tkinter import messagebox
import socket

class HexCalculatorClient:
    def __init__(self, root):
        self.root = root
        self.root.title("Шестнадцатеричный калькулятор")
        self.root.geometry("400x200")
        
        # Поля ввода и вывода
        tk.Label(root, text="Введите выражение (пример: F11+E8-8+10):").pack(pady=5)
        
        self.entry = tk.Entry(root, width=50, font=("Courier", 12))
        self.entry.pack(pady=10, padx=20)
        
        self.result_label = tk.Label(root, text="Результат: ", font=("Arial", 12))
        self.result_label.pack(pady=10)
        
        # Кнопка отправки
        self.submit_button = tk.Button(
            root,
            text="Вычислить",
            command=self.send_expression,
            bg="#4CAF50",
            fg="white",
            font=("Arial", 12),
            padx=20
        )
        self.submit_button.pack(pady=10)
        
        # Настройки соединения
        self.host = '127.0.0.1'
        self.port = 65432
        self.timeout = 5  # секунд
    
    def send_expression(self):
        expression = self.entry.get().strip()
        
        if not expression:
            messagebox.showwarning("Предупреждение", "Введите выражение!")
            return
        
        try:
            # Создаем сокет
            client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client.settimeout(self.timeout)
            
            # Подключаемся к серверу
            client.connect((self.host, self.port))
            
            # Отправляем выражение
            client.send(expression.encode('utf-8'))
            
            # Получаем результат
            result = client.recv(1024).decode('utf-8')
            
            client.close()
            
            if result == "ERROR":
                self.result_label.config(text="Результат: Ошибка вычисления", fg="red")
            else:
                self.result_label.config(
                    text=f"Результат: {result}",
                    fg="black"
                )
                
        except socket.timeout:
            messagebox.showerror("Ошибка", "Превышено время ожидания ответа от сервера!")
            self.result_label.config(text="Результат: ", fg="black")
            
        except ConnectionRefusedError:
            messagebox.showerror("Ошибка", "Не удалось подключиться к серверу!")
            self.result_label.config(text="Результат: ", fg="black")
            
        except Exception as e:
            messagebox.showerror("Ошибка", f"Произошла ошибка: {e}")
            self.result_label.config(text="Результат: ", fg="black")

def main():
    root = tk.Tk()
    app = HexCalculatorClient(root)
    root.mainloop()

if __name__ == "__main__":
    main()
