import turtle

t=turtle.Pen()
direction=int(0);

while True:
    move = input("이동: ")
    sMove = str(move)

    if sMove == 'w' :
        t.left(90-direction)
        direction=90
        t.forward(100)
    elif sMove == 's' :
        t.left(-90-direction)
        direction=-90
        t.forward(100)
    elif sMove == 'd' :
        t.left(-direction)
        direction=0
        t.forward(100)
    elif sMove == 'a' :
        t.left(180-direction)
        direction=180
        t.forward(100)
    else :
        t.left(90)
        direction += 90
