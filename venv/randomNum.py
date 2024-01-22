"""LCG 随机数生成和校验。"""

import numpy as np
import matplotlib.pyplot as plt


class Rng:

    _m = 2 ** 32
    _a = 1103515245
    _c = 12345

    def __init__(self, seed=10):
        self.x = seed

    def generate(self):
        """除以 m 后，输出结果在 0~1之间"""
        self.x = (self._a * self.x + self._c) % self._m
        return self.x / self._m


if __name__ == '__main__':
    SEED = 123  # 初始化
    N = 1000000  # 产生很多数
    AVG = 10  # 平均值
    rng = Rng(SEED)
    x = [rng.generate() * AVG for _ in range(N)]
    x = np.array(x)

    N = 1000000  # 有很多地铁

    tau = 10  # 每十分钟一班

    rng = Rng(123)
    x = [rng.generate() for _ in range(N)]
    x = np.array(x)
    arrive_times = N * tau * np.sort(x)  # 模拟地铁一趟一趟地到站时间

  