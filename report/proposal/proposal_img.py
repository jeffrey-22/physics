import pysketcher as ps
import numpy as np
from pysketcher import *
from pysketcher.backend.matplotlib import MatplotlibBackend


figure = ps.Figure(-1, 12, -1, 2, MatplotlibBackend)

boxA = ps.Circle(ps.Point(0.5, 0.5), 1)
boxB = ps.Circle(ps.Point(10.5, 0.5), 1)
boxA.style.line_width = 10
boxB.style.line_width = 10
arrowA = ps.Arrow(ps.Point(2, 0.5), ps.Point(3, 0.5))
arrowB = ps.Arrow(ps.Point(9, 0.5), ps.Point(8, 0.5))
arrowA.style.line_width = 5
arrowB.style.line_width = 5
txtA = ps.Text("1m/s", Point(2.5, 0.6))
txtA.style.font_size *= 2
txtB = ps.Text("1m/s", Point(8.5, 0.6))
txtB.style.font_size *= 2


figure.add(boxA)
figure.add(boxB)
figure.add(arrowA)
figure.add(arrowB)
figure.add(txtA)
figure.add(txtB)

figure.save('img1.png')

figure = ps.Figure(-1, 9, -1, 7, MatplotlibBackend)

a = Point(0, 0)
b = Point(0, 6)
c = Point(8, 0)
inc = Triangle(a, b, c)
inc.style.line_width = 10
arc = ps.Arc(c, 1, Angle(np.pi-np.arcsin(3/5)), Angle(np.arcsin(3/5)))
arc.style.line_width = 10
theta = ArcAnnotation("θ", arc)
theta.style.font_size *= 4
lp = Point(4 - 0.5 * 4/5, 3 + 0.5 * 3/5)
box = Rectangle(lp, 1, 1)
rbox = box.rotate(-np.arcsin(3/5), lp)
rbox.style.line_width = 10

figure.add(inc)
figure.add(arc)
figure.add(theta)
figure.add(rbox)

figure.save('img2.png')

figure = ps.Figure(-1, 8, -1, 11, MatplotlibBackend)

a = ps.Point(0, 10)
b = ps.Point(6, 2)
line = ps.Line(a, b)
line.style.line_width = 10
vert = ps.Line(a, ps.Point(0, 0))
vert.style.line_width = 10
vert.style.line_style = ps.Style.LineStyle(4)
ball = ps.Circle(b, 1)
ball.style.fill_color = ps.Style.Color.BLACK
arc = ps.Arc(a, 1, Angle(-np.pi / 2), Angle(np.arcsin(3/5)))
arc.style.line_width = 10
theta = ArcAnnotation("θ", arc)
theta.style.font_size *= 4

figure.add(line)
figure.add(ball)
figure.add(vert)
figure.add(arc)
figure.add(theta)

figure.save('img3.png')


figure = ps.Figure(-1, 3, -1, 6, MatplotlibBackend)

a = ps.Point(0, 0)
b = ps.Point(2, 0)
line = ps.Line(a, b)
line.style.line_width = 10
box = Rectangle(Point(0.5, 0.5), 1, 1)
box.style.line_width = 10
box2 = Rectangle(Point(0.5, 2.5), 1, 1)
box2.style.line_width = 10
txt = Text("···", Point(1, 4.5), Point(0, 1))
txt = txt.rotate(np.pi / 2, Point(1,4.5))
txt.style.font_size *= 8

figure.add(line)
figure.add(box)
figure.add(box2)
figure.add(txt)

figure.save('img4.png')