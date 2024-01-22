import math
import numpy as np
import matplotlib.pyplot as plt

def levy_flight(num, beta, sigma_u, sigma_v):
    x_delta, y_delta = 0, 0
    resX, resY = [], []

    for _ in range(num * 10):
        u = np.random.normal(0, sigma_u, 1)
        v = np.random.normal(0, sigma_v, 1)
        s = u / ((abs(v)) ** (1 / beta))

        x_delta += s[0]

        u = np.random.normal(0, sigma_u, 1)
        v = np.random.normal(0, sigma_v, 1)
        s = u / ((abs(v)) ** (1 / beta))

        y_delta += s[0]
        resX.append(x_delta)
        resY.append(y_delta)

    return resX, resY

# 设置参数
num_points = 1000  # 要生成的点的数量
beta = 1.5
sigma_u = (math.gamma(1 + beta) * math.sin(math.pi * beta / 2) / (
        math.gamma((1 + beta) / 2) * beta * (2 ** ((beta - 1) / 2)))) ** (1 / beta)
sigma_v = 1

# 生成Levy飞行的点
levy_x, levy_y = levy_flight(num_points, beta, sigma_u, sigma_v)

# 绘制Levy飞行的点
plt.plot(levy_x, levy_y, marker='o', linestyle='-')
plt.title('Levy Flight')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
plt.show()
