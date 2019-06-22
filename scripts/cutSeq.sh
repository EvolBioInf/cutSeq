./cutSeq -r 1-100  ../data/test.fasta > tmp.out
DIFF=$(diff tmp.out ../data/cutSeq1.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(cutSeq -r 1-100)\t\t\tpass\n"
else
    printf "Test(cutSeq -r 1-100)\t\t\tfail\n"
    echo ${DIFF}
fi

./cutSeq -r 1-100 -l 50  ../data/test.fasta > tmp.out
DIFF=$(diff tmp.out ../data/cutSeq2.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(cutSeq -r 1-100 -l 50)\t\tpass\n"
else
    printf "Test(cutSeq -r 1-100 -l 50)\t\tfail\n"
    echo ${DIFF}
fi

./cutSeq -r 500-600,700-1000  ../data/test.fasta > tmp.out
DIFF=$(diff tmp.out ../data/cutSeq3.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(cutSeq -r 500-600,700-1000)\tpass\n"
else
    printf "Test(cutSeq -r 500-600,700-1000)\tfail\n"
    echo ${DIFF}
fi

./cutSeq -r 500-600,700-1000 -s  ../data/test.fasta > tmp.out
DIFF=$(diff tmp.out ../data/cutSeq4.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(cutSeq -r 500-600,700-1000 -s)\tpass\n"
else
    printf "Test(cutSeq -r 500-600,700-1000 -s)\tfail\n"
    echo ${DIFF}
fi

rm tmp.out
