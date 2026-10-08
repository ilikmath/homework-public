# 212-Терский-Илья-(пирамиды на 2D-плоскости: кластеры алгоритма «Волна»)
# Запуск: gnuplot -p plot.gp
# Или из окна gnuplot:  load 'C:\Users\ILIK\Projects\homework\08_pyramids\plot.gp'

set encoding utf8

if (strlen(system('if exist points.dat echo yes')) == 0) {  # если gnuplot открыт не из папки задания, перехожу в неё
    cd 'C:\Users\ILIK\Projects\homework\08_pyramids'
}

if (strlen(system('if exist points.dat echo yes')) == 0) {  # данных ещё нет — запускаю программу
    print "points.dat not found, running pyramids.exe"
    system '.\pyramids.exe'
}

load "grid.gp"  # отсюда берётся side — сторона квадрата

set title "212 Терский Илья: кластеры вторичных точек (алгоритм «Волна»)"
set xlabel "x"
set ylabel "y"
set xrange [-10:10]
set yrange [-10:10]
set size ratio -1
unset key

set linetype 1 lc rgb "#2b6cb0"  # свои цвета для больших кластеров
set linetype 2 lc rgb "#dd6b20"
set linetype 3 lc rgb "#38a169"
set linetype 4 lc rgb "#d53f8c"
set linetype 5 lc rgb "#805ad5"
set linetype 6 lc rgb "#d69e2e"
set linetype 7 lc rgb "#319795"
set linetype 8 lc rgb "#e53e3e"
set linetype cycle 8

plot "squares.dat" using ($3 + side / 2):($4 + side / 2):(side / 2):(side / 2) \
         with boxxyerror fs solid 0.15 noborder lc rgb "#a0aec0", \
     "points.dat" using 1:($4 == 0 ? $2 : NaN) with points pt 7 ps 0.3 lc rgb "#718096", \
     "points.dat" using 1:($4 > 0 ? $2 : NaN):4 with points pt 7 ps 0.3 lc variable, \
     "bases.dat" with lines lc rgb "#1a202c" lw 1.5
# серые квадраты — непустые клетки, серые точки — выбросы, цветные — большие кластеры, чёрные круги — основания
