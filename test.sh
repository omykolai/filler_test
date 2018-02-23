make -C .. > log
gcc -o gen generate_map.c
gcc -o test test.c ../get_next_line/get_next_line.c ../libft/libft.a
homedir=$(pwd | rev | cut -f 2- -d / | rev)
player1=$(find $homedir -name $1)
player2=$(find $homedir -name $2)
filler_vm=$(find $homedir -name filler_vm)
if [ -z  $player1  ]
then
	echo "\x1b[1;31mplayer1 wasn't found\x1b[0m"
elif [ -z  $player2  ]
then
	echo "\x1b[1;31mplayer2 wasn't found\x1b[0m"
	elif [ -z  $filler_vm  ]
then
	echo "\x1b[1;31filler_vm wasn't found\x1b[0m"
elif [ "$#" == 5 ]
then
	max=$5
	average=0
	for (( i=0; i < max; i++ ));
	do
		./gen $3 $4
		$filler_vm -p1 $player1 -p2 $player2 -f map > r
		./test $average 0 < r
		average=`cat a`
	done
	average=`echo "$average/$max" | bc`
	./test $average 1
	rm a
	rm filler.trace
	rm gen
	rm log
	rm map
	rm r
	rm test
else
	echo "Usage: ./test.sh player1 player2 mapRowCount mapColumnCount iterationCount"
fi