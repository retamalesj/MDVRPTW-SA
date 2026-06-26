import matplotlib.pyplot as plt

# Datos
instancias = [
    "(25) C101",
    "(100) C101",
    "(200) C1_2_1",
    "(400) C1_4_1",
    "(1000) C110_1"
]

tiempos = [3.77, 12.34, 19.70, 32.15, 84.05]

# 🔥 aumentar tamaño global de letra
plt.rcParams.update({
    "font.size": 13
})

# Crear figura
plt.figure(figsize=(11, 3.6))

# Gráfico de barras horizontal
bars = plt.barh(instancias, tiempos)

# Etiquetas
plt.xlabel("Tiempo promedio de ejecución (s)", fontsize=14)
plt.ylabel("Instancia", fontsize=14)
plt.title("Escalabilidad del tiempo de ejecución", fontsize=15)

# escala hasta 100 s
plt.xlim(0, 100)

# valores en barras
for bar, tiempo in zip(bars, tiempos):
    plt.text(
        tiempo + 0.8,
        bar.get_y() + bar.get_height() / 2,
        f"{tiempo:.2f} s",
        va="center",
        fontsize=13
    )

plt.tight_layout()

plt.savefig("figure002.png", dpi=300, bbox_inches="tight")
plt.show()