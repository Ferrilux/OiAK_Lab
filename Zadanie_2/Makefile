calculator: calculator.o
	# ld calculator.o -o calculator
	gcc -nostdlib -no-pie -o calculator calculator.o

calculator.o: calculator.s
	# as calculator.s -o calculator.o
	gcc -c calculator.s -o calculator.o -ggdb 

all: calculator

clean: 
	rm calculator