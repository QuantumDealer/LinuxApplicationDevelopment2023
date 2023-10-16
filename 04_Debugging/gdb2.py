gdb.execute("b 35")
gdb.execute("b 37")
gdb.execute("run -100 100 3 >/dev/null")
gdb.execute("watch i")
for i in range(28):
    gdb.execute("c")
for i in range(8):
    gdb.execute("info locals")
    gdb.execute("c")
