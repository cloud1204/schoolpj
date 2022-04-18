import numpy as np
import matplotlib.pyplot as plt
from math import sin, cos, acos, sqrt

pi = 3.1415926535897932384626433832
def calculate_angle(a, b, c):
    tmp = (b * b + c * c - a * a) / (2 * b * c)
    return acos(tmp)
def calculate_edge(a, b, theta):
    return sqrt(a * a + b * b - 2 * a * b * cos(theta))
def line(x1, y1, x2, y2):
    plt.plot([x1, x2], [y1, y2])
class qua:
    def __init__(self, _t): self.t = _t
    edge = [1, 1, 1, 1]
    angle = [pi / 2, pi / 2, pi / 2, pi / 2]
    history = []
    x = [1, 1, 0, 0]
    y = [1, 0, 0, 1]
    def cut(self, tar, dir, _area):
        if dir == 0:
            side = self.edge[tar]
            theta = self.angle[(tar + 3) % 4]
            cutlen = 2 * _area / (side * sin(theta))
            newside = calculate_edge(side, cutlen, theta)
            if cutlen > self.edge[(tar + 3) % 4]: return False
            self.x[(tar + 3) % 4] += (self.x[(tar + 2) % 4] - self.x[(tar + 3) % 4]) * cutlen / self.edge[(tar + 3) % 4]
            self.y[(tar + 3) % 4] += (self.y[(tar + 2) % 4] - self.y[(tar + 3) % 4]) * cutlen / self.edge[(tar + 3) % 4]
            self.angle[tar] -= calculate_angle(cutlen, side, newside)
            self.edge[tar] = newside
            self.edge[(tar + 3) % 4] -= cutlen
            self.angle[(tar + 3) % 4] = 2 * pi - self.angle[tar] - self.angle[(tar + 1) % 4] - self.angle[(tar + 2) % 4]
            line(self.x[tar], self.y[tar], self.x[(tar + 3) % 4], self.y[(tar + 3) % 4])
        else:
            side = self.edge[(tar + 1) % 4]
            theta = self.angle[(tar + 1) % 4]
            cutlen = 2 * _area / (side * sin(theta))
            newside = calculate_edge(side, cutlen, theta)
            if cutlen > self.edge[(tar + 2) % 4]: return False
            #print(self.x[(tar + 2) % 4], self.x[(tar + 1) % 4])
            self.x[(tar + 1) % 4] += (self.x[(tar + 2) % 4] - self.x[(tar + 1) % 4]) * cutlen / self.edge[(tar + 2) % 4]
            self.y[(tar + 1) % 4] += (self.y[(tar + 2) % 4] - self.y[(tar + 1) % 4]) * cutlen / self.edge[(tar + 2) % 4]
            self.angle[tar] -= calculate_angle(cutlen, side, newside)
            self.edge[(tar + 1) % 4] = newside
            self.edge[(tar + 2) % 4] -= cutlen
            self.angle[(tar + 1) % 4] = 2 * pi - self.angle[tar] - self.angle[(tar + 2) % 4] - self.angle[(tar + 3) % 4]
            line(self.x[tar], self.y[tar], self.x[(tar + 1) % 4], self.y[(tar + 1) % 4])
        self.t -= 1
        return True
    def area(self, tar):
        return self.edge[tar] * self.edge[(tar + 1) % 4] * sin(self.angle[tar]) / 2
    def split(self):
        a, b, c, d = self.area(0), self.area(1), self.area(2), self.area(3)
        if abs(a - c) < abs(b - d): line(self.x[1], self.y[1], self.x[3], self.y[3])
        else: line(self.x[0], self.y[0], self.x[2], self.y[2])
        return min(abs(a - c), abs(b - d))
def solve():
    n = int(input())
    cur = qua(n)
    piece = 1 / n
    for i in range (n - 2):
        tar, dir = map(int, input().split())
        success = cur.cut(tar, dir, piece)
        if not success:
            print("failed")
            return
    print(cur.split())
line(0, 0, 0, 1)
line(0, 0, 1, 0)
line(0, 1, 1, 1)
line(1, 0, 1, 1)
solve()
plt.show()