F=sudoku
if [ "$1" != "" ]
then
    F=$1
fi
echo "Limbo / functional"
for f in $(ls -1 $F/*.fcnf); do cat $f | ./sat -e=0 -c=1 | grep -i satisfiable; done | ./sum.sh
echo "Limbo / propositional"
for f in $(ls -1 $F/*.cnf); do cat $f | ./sat -e=0 -c=1 | grep -i satisfiable; done | ./sum.sh
#echo "sat-cdcl / propositional"
#for f in $(ls -1 $F/*.cnf); do ../../../2017-08-COMP4418/SAT/sat-cdcl $f | grep -i satisfiable; done | ./sum.sh
#echo "MiniSAT / propositional"
#for f in $(ls -1 $F/*.cnf); do cat $f | ../../../Spielplatz/minisat/minisat | grep -i satisfiable; done | ./sum.sh

