for file in $1*.tig
do

    ./src/tc -o -A --parse $file > tmp1
    ./src/tc -o -XA --parse tmp1 > tmp2
    diff tmp1 tmp2
    #rm tmp1
    #rm tmp2
done
