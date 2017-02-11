./src/tc -A $1 > tmp1
./src/tc -XA tmp1 >tmp2

diff tmp1 tmp2

rm tmp1
rm tmp2
