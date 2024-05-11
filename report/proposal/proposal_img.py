import pysketcher as ps
import numpy as np
from pysketcher import *
from pysketcher.backend.matplotlib import MatplotlibBackend


figure = ps.Figure(-1, 12, -1, 2, MatplotlibBackend)

boxA = ps.Rectangle(ps.Point(0, 0), 1, 1)
boxB = ps.Rectangle(ps.Point(10, 0), 1, 1)
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


figure = ps.Figure(-1, 9, -1, 6.5, MatplotlibBackend)
lst = []
def addseg(lp, rp, id):
    segA = ps.Line(lp, rp)
    segA.style.line_width = 5
    txtA = ps.Text("l", ps.Point(lp.x, lp.y+0.1))
    txtA.style.font_size *= 6
    txtAA = ps.Text(str(id), ps.Point(lp.x+0.15, lp.y+0.05))
    txtAA.style.font_size *= 3
    txtB = ps.Text("r", ps.Point(rp.x, rp.y+0.1))
    txtB.style.font_size *= 6
    txtBB = ps.Text(str(id), ps.Point(rp.x+0.15, rp.y+0.05))
    txtBB.style.font_size *= 3
    figure.add(segA)
    figure.add(txtA)
    figure.add(txtAA)
    figure.add(txtB)
    figure.add(txtBB)
    lst.append((lp.x, "l" + str(id)))
    lst.append((rp.x, "r" + str(id)))
lp = ps.Point(0.5, 5.5)
rp = ps.Point(3.5, 5.5)
addseg(lp, rp, 1)
lp = ps.Point(2, 4.5)
rp = ps.Point(6, 4.5)
addseg(lp, rp, 2)
lp = ps.Point(4.5, 3.5)
rp = ps.Point(5.5, 3.5)
addseg(lp, rp, 3)
lp = ps.Point(6.5, 2.5)
rp = ps.Point(8.5, 2.5)
addseg(lp, rp, 4)
lp = ps.Point(7, 1.5)
rp = ps.Point(8, 1.5)
addseg(lp, rp, 5)
lst = sorted(lst)
segB = ps.Line(ps.Point(0.5, 0.2), ps.Point(8.5, 0.2))
figure.add(segB)
for (t, lbl) in lst:
    circ = ps.Circle(ps.Point(t, 0.2), radius=0.03)
    txt1 = ps.Text(lbl[0], ps.Point(t, 0.3))
    txt2 = ps.Text(lbl[1], ps.Point(t+0.15, 0.25))
    txt1.style.font_size *= 6
    txt2.style.font_size *= 3
    figure.add(circ)
    figure.add(txt1)
    figure.add(txt2)
figure.save('img5.png')