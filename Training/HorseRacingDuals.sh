#!/bin/bash
# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

read N
if [[ N -gt 500 ]]
then
    let "n=$N/500"
else
    n=$N
fi

let "space=10000000"
let "found=0"
horse=()

qsort() {
   (($#==0)) && return 0
   local stack=( 0 $(($#-1)) ) beg end i pivot smaller larger
   qsort_ret=("$@")
   while ((${#stack[@]})); do
      beg=${stack[0]}
      end=${stack[1]}
      stack=( "${stack[@]:2}" )
      smaller=() larger=()
      pivot=${qsort_ret[beg]}
      for ((i=beg+1;i<=end;++i)); do
         if [[ "${qsort_ret[i]}" -lt "$pivot" ]]; then
            smaller+=( "${qsort_ret[i]}" )
         else
            larger+=( "${qsort_ret[i]}" )
         fi
      done
      qsort_ret=( "${qsort_ret[@]:0:beg}" "${smaller[@]}" "$pivot" "${larger[@]}" "${qsort_ret[@]:end+1}" )
      if ((${#smaller[@]}>=2)); then stack+=( "$beg" "$((beg+${#smaller[@]}-1))" ); fi
      if ((${#larger[@]}>=2)); then stack+=( "$((end-${#larger[@]}+1))" "$end" ); fi
   done
}

for (( i=0; i<n; i++ )); do
    read Pi   
    horse[$i]=$Pi    
done
echo $n >&2

qsort "${horse[@]}"

echo ${horse[*]} >&2
echo ${qsort_ret[*]} >&2

for (( j=1; j<n; j++ )); do
    let "localSpace=${qsort_ret[$j]}-${qsort_ret[$j-1]}"
    if [[ $localSpace -lt $space ]]
    then
        space=$localSpace
    fi
done

# Write an action using echo
# To debug: echo "Debug messages..." >&2

echo $space
