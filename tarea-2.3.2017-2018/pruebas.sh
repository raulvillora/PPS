#!/bin/bash -x

# ATENCION: ESTE es al fichero a modificar para añadir nuevas pruebas.
# ATENCION: ESTE es al fichero a modificar para añadir nuevas pruebas.
# ATENCION: ESTE es al fichero a modificar para añadir nuevas pruebas.
# ATENCION: ESTE es al fichero a modificar para añadir nuevas pruebas.
# ATENCION: ESTE es al fichero a modificar para añadir nuevas pruebas.
# ATENCION: ESTE es al fichero a modificar para añadir nuevas pruebas.
# ATENCION: ESTE es al fichero a modificar para añadir nuevas pruebas.

# Este script no es para ser usado independientemente,
# sino para ser cargado (source) desde el evaluador.sh

# Indique en esta variable los números de matrícula
# de los componentes del grupo.
MEMBERS='v13m047 v13m051'

# Indique en esta variable los nombres de los programas
# para los que han implementado casos de prueba.
PROGRAMAS="ejemplo delreves secuencia bocabajo primos factores analiza"


################## Funciones con las pruebas a un programa concreto.

# A modo de ejemplo, se proporcionan tres funciones con las pruebas
# a las que se somete a un programa de ejemplo llamado: ejemplo.c
# Para enterder lo que este programa hace, lea su fuente.

Pruebas_ejemplo_bien()
{
					# Título de la prueba.
	__ Ayuda
					# Se ejecuta el mandato.
	_x0 ./ejemplo -h
					# Debió terminar bien
					# Y
	T_Xtatus 0		&&
					# Las lineas producidas por el
					# descriptor 2 debieron ser 2 o más
					# Y
	T_Lines 2 -ge 2		&&
					# Las lineas producidas por el
					# descriptor 2 debieron comenzar como estas
					# Y
	T_Begx 2 << \EOF	&&
ejemplo: 
ejemplo: 
EOF
					# Las lineas producidas por el
					# descriptor 1 debieron ser igual a 0
					# Y
	T_Lines 1 -eq 0		&&
					# YaEstá ; Contabilizar esta prueba.
	: ; Test


	__ Ayuda con dos menos
	_x0 ./ejemplo --help
	T_Xtatus 0		&&
	T_Lines 2 -eq 4		&&
	T_Begx 2 << \EOF	&&
ejemplo: .*Uso:.*ejemplo
ejemplo: .*aleatorio
ejemplo: .*factorial
ejemplo: .*binomial
EOF
	T_Lines 1 -eq 0		&&
	: ; Test

	# BASH scripting. Existen variables enteras y bucles.
	local -i NUM=3
	local -i CNT
	for (( CNT=1; CNT<=NUM; CNT++ ))
	do
		__ Aleatorio $CNT/$NUM
		_x0 ./ejemplo
		T_Xtatus 0		&&
		T_Lines 2 -eq 0		&&
		T_Lines 1 -eq 1		&&
		T_Begx 1 << \EOF	&&
[ 	]*[0-9][ 	]*
EOF
		: ; Test
	done

	local PAIR
	local N
	local F
	for PAIR in '0 1' '1 1' '2 2' '3 6' '4 24'    '10  3628800' '11 39916800'
	do
		# bash extension "here string"
		read N F <<< "$PAIR"
		__ Factorial de $N es $F
		_x0 ./ejemplo $N
		T_Xtatus 0		&&
		T_Lines 2 -eq 0		&&
		T_Lines 1 -eq 1		&&
		T_Begx 1 <<  EOF	&&
[Ff]actorial.*(.*$N.*).*=.*$F
EOF
		: ; Test
	done

	local TRIO
	local N
	local K
	local B
	for TRIO in	'0 0 1' \
			'1 0 1' '1 1 1' \
			'2 0 1' '2 1 2' '2 2 1' \
			'3 0 1' '3 1 3' '3 2 3' '3 3 1' \
			'4 0 1' '4 1 4' '4 2 6' '4 3 4' '4 4 1' \
			'11 0 1' '11 1 11' '11 5 462' '11 10 11' '11 11 1'
	do
		# bash extension "here string"
		read N K B <<< "$TRIO"
		__ Binomial de $N y $K es $B
		_x0 ./ejemplo $N $K
		T_Xtatus 0		&&
		T_Lines 2 -eq 0		&&
		T_Lines 1 -eq 1		&&
		T_Begx 1 <<  EOF	&&
[Bb]inomial.*(.*$N,.*$K).*=.*$B
EOF
		: ; Test
	done

	:
}

Pruebas_ejemplo_mal()
{
	# Las siguientes pruebas son las que deben terminar con error.

	__ Invocación con demasiados argumentos.
	_x0 ./ejemplo  1 2 3
	T_Xtatus EX_USAGE	&&
	T_Lines 2 -eq 2		&&
	T_Begx 2 << \EOF	&&
ejemplo: Error(EX_USAGE),
ejemplo+.*argumentos
EOF
	T_Lines 1 -eq 0		&&
	: ; Test


	local N
	for N in '-1' 'MAL' '8extra'
	do
		__ Factorial de numero no natural.
		_x0 ./ejemplo $N 
		T_Xtatus EX_USAGE	&&
		T_Lines 2 -eq 2		&&
		T_Begx 2 << \EOF	&&
ejemplo: Error(EX_USAGE),
ejemplo+.*no.*natural
EOF
		T_Lines 1 -eq 0		&&
		: ; Test
	done

	local PAIR
	local N
	local K
	for PAIR in '-1 1' '1 -1' 'a 0' '1 b' '4cuatro 2' '4 2dos'
	do
		# bash extension "here string"
		read N K <<< "$PAIR"
		__ Binomial de numeros no naturales.
		_x0 ./ejemplo $N $K
		T_Xtatus EX_USAGE	&&
		T_Lines 2 -eq 2		&&
		T_Begx 2 << \EOF	&&
ejemplo: Error(EX_USAGE),
ejemplo+.*no.*natural
EOF
		T_Lines 1 -eq 0		&&
		: ; Test
	done


	local PAIR
	local N
	local K
	for PAIR in '0 1' '1 2'
	do
		# bash extension "here string"
		read N K <<< "$PAIR"
		__ Binomial de N menor que K.
		_x0 ./ejemplo $N $K
		T_Xtatus EX_USAGE	&&
		T_Lines 2 -eq 2		&&
		T_Begx 2 << \EOF	&&
ejemplo: Error(EX_USAGE),
ejemplo+.*menor o igual
EOF
		T_Lines 1 -eq 0		&&
		: ; Test
	done

	:
}

Pruebas_ejemplo_xtra()
{
#	# deben ir bien
#	factorial 007 (como decimal)
#	factorial 008 (como decimal)
#	factorial +0
#	factorial -0
	local TRIO
	local T
	local -i N
	local F
	for TRIO in '007 7 5040' '008 8 40320' '+0 0 1' '-0 0 1' '++0 0 1' '--0 0 1'
	do
		# bash extension "here string"
		read T N F <<< "$TRIO"
		__ Factorial. Interpretación correcta de números extraños.
		_x0 ./ejemplo $T 
		T_Xtatus 0		&&
		T_Lines 2 -eq 0		&&
		T_Lines 1 -eq 1		&&
		T_Begx 1 <<  EOF	&&
[Ff]actorial.*(.*$N.*).*=.*$F
EOF
		: ; Test
	done


#	# deben ir bien pero irán mal si provocan desbordamiento.
#	depende del tipo de datos escogido para computar factorial.
	local TRIO N F T
	for TRIO in	'12 479001600 int_OK'			'13 6227020800 unsigned_BAD' \
			'14 87178291200 float_BAD' \
			'20 2432902008176640000 ULL_OK'		'21 51090942171709440000 ULL_BAD' \
			'22 1124000727777607680000 double_OK'	'23 2585201673888497....... double_BAD' \
			'30 265252859812191058636308480000000 huge_OK'
	do
		
		# bash extension "here string"
		read N F T <<< "$TRIO"
		__ Desbordamiento "($T)". Factorial de $N es $F
		_x0 ./ejemplo $N
		T_Xtatus 0		&&
		T_Lines 2 -eq 0		&&
		T_Lines 1 -eq 1		&&
		T_Begx 1 <<  EOF	&&
[Ff]actorial.*(.*$N.*).*=.*$F
EOF
		: ; Test	# || break	# Salir al primer fallo.
	done


#	# deben ir bien pero irán mal si hay desbordamiento.
#	depende de la implementación realizada para calcular binomial.
#	Se plantean como buenas soluciones aproximadas.
	local TRIO N K B
	for TRIO in	' 20  10  184756' \
			' 30  15  155117520' \
			' 40  20  1378465.....' \
			' 50  25  1264106........' \
			' 60  30  1182645...........' \
			' 70  35  1121862..............' \
			' 80  40  1075072.................' \
			' 90  45  103827.....................' \
			'100  50  100891........................' \
			'110  55  985272..........................' \
			'120  60  9661490............................' \
			'130  65  950676258279606.......................' \
			'140  70  938209696978400..........................' \
			'150  75  928260697367087.............................' \
			'160  80  92045125813734.................................' \
			'170  85  91448418451315....................................' \
			'180  90  91012248672832.......................................' \
			'190  95  90717484605833..........................................' \
			'200 100  90548514656103.............................................'
	do
		# bash extension "here string"
		read N K B <<< "$TRIO"
		__ Implementación. Binomial de $N y $K es $B
		_x0 ./ejemplo $N $K
		T_Xtatus 0		&&
		T_Lines 2 -eq 0		&&
		T_Lines 1 -eq 1		&&
		T_Begx 1 <<  EOF	&&
[Bb]inomial.*(.*$N.*,.*$K.*).*=.*$B
EOF
		: ; Test	# || break	# Salir al primer fallo.
	done

	:
}

###############################################################################
###############################################################################
