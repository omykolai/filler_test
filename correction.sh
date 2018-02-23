homedir=$(pwd | rev | cut -f 2- -d / | rev)
player1=$(find $homedir -name $1)
filler_vm=$(find $homedir -name filler_vm)

filler()
{
	max=$4
	player2=$(find $homedir -name $2)
	map=$(find $homedir -name $3)

	if [ -z  $player2  ]
	then
		echo "\x1b[31m$2 wasn't found\x1b[0m"
	elif [ -z  $map ]
	then
		echo "\x1b[31m$3 wasn't found\x1b[0m"
	else
		printf "%b%-30b%b%b%b" "\033[0;36m>>> " "\033[1;36m$2" "\033[1;34m" "$3" " \033[0;36m<<<\033[m\n"
		for (( i=0; i < max; i++ ));
		do
			$filler_vm -p1 $player1 -p2 $player2 -f $map | ./test 0 0
		done
	fi
}

test_filler()
{
	filler $1 $2 map00 5
	filler $1 $2 map01 3
	filler $1 $2 map02 1
}

if [ "$#" == 1 ]
then
	make -C ..
	echo
	cat -e ../author
	norminette .. | grep Error
	echo
	gcc -o test test.c ../get_next_line/get_next_line.c ../libft/libft.a
	if [ -z  $filler_vm  ]
	then
		echo "\x1b[31mfiller_vm wasn't found\x1b[0m"
	elif [ -z  $player1  ]
	then
		echo "\x1b[31$1 wasn't found\x1b[0m"
	else
		filler $1 champely.filler map01 1
		filler $1 champely.filler map02 1
		test_filler $1 abanlin.filler
		test_filler $1 grati.filler
		test_filler $1 hcao.filler
		test_filler $1 superjeannot.filler
		test_filler $1 carli.filler
		rm filler.trace
		rm test
	fi
else
	echo "Usage: ./correction.sh player"
fi