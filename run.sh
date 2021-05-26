clear
echo -e 'Running application...'
echo
rm log.txt
cd output
./matrix-app $1 &> ../log.txt
echo
echo -e '# Done!'
echo
