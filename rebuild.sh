#! /bin/sh

CPUCOUNT=$(grep -c "^processor" /proc/cpuinfo)

if [ ${CPUCOUNT} -lt 1 -o ${CPUCOUNT} -gt 32 ]
then
    echo "Unexpected value for number of CPUs, ${CPUCOUNT}, exiting ..."
    exit 16
fi

echo "This machine has ${CPUCOUNT} CPUs, will use make -j${CPUCOUNT} where possible"

make clean
make -j ${CPUCOUNT} cwg
