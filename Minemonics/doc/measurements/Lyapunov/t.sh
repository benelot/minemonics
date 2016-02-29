for f in walk* 
do
	cd $f
	pwd
	rename 's/0x[a-z0-9]{8}//' *.tsv
	rename 's/0x[a-z0-9]{7}//' *.tsv
	rename 's/]0/]/' *.tsv
	cd ..
done
