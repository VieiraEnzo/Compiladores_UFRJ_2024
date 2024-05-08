all: saida entrada.txt
	./saida < entrada.txt

lex.yy.c: mini_js.l
	lex min_js.l

y.tab.c: mini_js.y
	yacc mini_js.y

saida: lex.yy.c y.tab.c
	g++ -o saida y.tab.c -lfl