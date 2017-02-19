FNR == 1 { print "File: " FILENAME }
{
if (/^<header>/)
	printf "Header: %d: %s\n", FNR, $0;
else
	printf "%d: %s\n", FNR, $0;
}
