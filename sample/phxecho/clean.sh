  
for path in `find /root/lpz/phxpaxos/sample/phxecho -regex ".*log.*"`
do
    rm -rf $path
done

mkdir log