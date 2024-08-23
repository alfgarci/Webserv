#!/usr/bin/env python3

import time

print("Content-Type: text/html")
print()

# Bucle infinito
while True:
    print("<p>Este es un bucle infinito.</p>")
    time.sleep(1)  # Para evitar sobrecargar el servidor, agregamos una pausa de 1 segundo
