cl ns.c funs.c main.c
cat skel.vhd >o
ns >>o
cat end >>o
copy o prog.vhd
xst -ifn run.scr

