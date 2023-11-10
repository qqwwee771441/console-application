# A → (B∧C),B → D |= A → D

print("-----+-----+-----+-----+---------+---------+---------")
print("  A  :  B  :  C  :  D  :A→(B∧C): B → D  : A → D  ")
print("-----+-----+-----+-----+---------+---------+---------")

for A in [True, False]:
    for B in [True, False]:
        for C in [True, False]:
            for D in [True, False]:
                A1 = not A or (B and C)
                if A1==False :
                    continue
                A2 = not B or D
                if A2==False :
                    continue
                C  = not A or D
                print("-----+-----+-----+-----+---------+---------+---------")
                print("%5s:%5s:%5s:%5s:%9s:%9s:%9s" % (A, B, C, D, A1, A2, C))
                print("-----+-----+-----+-----+---------+---------+---------")

