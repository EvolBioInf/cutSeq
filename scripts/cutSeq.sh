./cutSeq > tmp.out
DIFF=$(diff tmp.out ../data/cutSeq.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(cutSeq)\tpass\n"
else
    printf "Test(cutSeq)\tfail\n"
    echo ${DIFF}
fi

rm tmp.out
