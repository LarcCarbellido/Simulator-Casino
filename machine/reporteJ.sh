#!/bin/bash
maq=$1
cont=0
lineasTot=0
for file in `ls -1v $maq`; do
	if ! [[ $file =~ ^(ANT_GRATISx2\.csv|ANT_GRATISx3\.csv|ANT_GRATISx4\.csv|ANT_GRATISx5\.csv|CEROCASIx3\.csv|CEROCASIx4\.csv|CEROCASIx5\.csv|GRATISx3\.csv|GRATISx4\.csv|GRATISx5\.csv|JUEGOx3\.csv|JUEGOx4\.csv|JUEGOx5\.csv|Table\.csv|facs\.csv|general\.txt)$  ]]; then
	file="$maq/$file"
	lineasFile=`wc -l $file|cut -d' ' -f1`
	((lineasTot=lineasTot+lineasFile))
	#echo $file
		tot=$(for ks in `rev $file |cut -d, -f'1'|rev`; do 
			if [ $ks -ge 1 ]; then  
				echo $ks;
			fi; 
		done | wc -l)
		((cont=cont+tot))
		#frec=`bc -l <<< $sumando/$lineasTot`
		grupo=`echo $file|rev|cut -d. -f3|rev|cut -d/ -f2`
		
		echo "$grupo,$tot"
		#echo "en este grupo:$tot sumando:$cont lineasFile:$lineasFile lineasTotales:$lineasTot" 
	fi
done
