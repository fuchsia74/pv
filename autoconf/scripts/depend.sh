#!/bin/sh
#
# Generate dependencies for a C source file.
#

CC="$1"
shift
file="$1"
shift
stem="$1"
shift
srcdir="$1"
abssrc=$(echo "$srcdir" | sed ':1
s,^\./,,g
t1')
shift

abssrc=$(echo "$abssrc" | sed 's,\.,\\.,g')
srcdir=$(echo "$srcdir" | sed 's,\.,\\.,g')

$CC -M -MG "$@" "$file" \
| sed \
  -e "s,^.*\.o:,${stem}.d ${stem}.o:," \
  -e 's,'"$srcdir"'/,,g' \
  -e 's,'"$abssrc"'/,,g' \
  -e 's, /[^ ]*,,g' \
  -e '/^ \\$/d' -e 's/ \\$//' \
| tr '\n' ' ' \
| tr -s ' '

echo

# EOF
